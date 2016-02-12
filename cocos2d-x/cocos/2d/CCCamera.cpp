/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 Code based GamePlay3D's Camera: http://gameplay3d.org

 ****************************************************************************/
#include "2d/CCCamera.h"
#include "2d/CCCameraBackgroundBrush.h"
#include "base/CCDirector.h"
#include "platform/CCGLView.h"
#include "2d/CCScene.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCFrameBuffer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

Camera* Camera::_visitingCamera = nullptr;
Node* Camera::_visitingScene = nullptr;
Node* Camera::_lightNode = nullptr;

Camera* _defaultCamera = nullptr;

experimental::Viewport Camera::_defaultViewport;

Camera* Camera::getDefaultCamera()
{
    return _defaultCamera;
}

Camera* Camera::create()
{
    Camera* camera = new (std::nothrow) Camera();
    camera->initDefault();
    camera->autorelease();
    
	if (_defaultCamera == nullptr)
	{
		_defaultCamera = camera;
	}

    return camera;
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	initOrthographic(left, right, bottom, top, nearPlane, farPlane);
}

Camera* Camera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    auto ret = new (std::nothrow) Camera();
    if (ret)
    {
        ret->initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Camera* Camera::createOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    auto ret = new (std::nothrow) Camera();
    if (ret)
    {
        ret->initOrthographic(left, right, bottom, top, nearPlane, farPlane);
        ret->autorelease();
		return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Camera::Camera()
: _viewProjectionDirty(true)
, _cameraFlag(1)
, _frustumDirty(true)
{
    _frustum.setClipZ(true);
    _clearBrush = CameraBackgroundBrush::createDepthBrush(1.f);
    _clearBrush->retain();
}

Camera::~Camera()
{
    CC_SAFE_RELEASE(_clearBrush);
}

const Mat4& Camera::getProjectionMatrix() const
{
    return _projection;
}
const Mat4& Camera::getViewMatrix() const
{
    Mat4 viewInv(getNodeToWorldTransform());
    static int count = sizeof(float) * 16;
    if (memcmp(viewInv.m, _viewInv.m, count) != 0)
    {
        _viewProjectionDirty = true;
        _frustumDirty = true;
        _viewInv = viewInv;
        _view = viewInv.getInversed();
    }
    return _view;
}
void Camera::lookAt(const Vec3& lookAtPos, const Vec3& up)
{
    Vec3 upv = up;
    upv.normalize();
    Vec3 zaxis;
    Vec3::subtract(this->getPosition3D(), lookAtPos, &zaxis);
    zaxis.normalize();
    
    Vec3 xaxis;
    Vec3::cross(upv, zaxis, &xaxis);
    xaxis.normalize();
    
    Vec3 yaxis;
    Vec3::cross(zaxis, xaxis, &yaxis);
    yaxis.normalize();
    Mat4  rotation;
    rotation.m[0] = xaxis.x;
    rotation.m[1] = xaxis.y;
    rotation.m[2] = xaxis.z;
    rotation.m[3] = 0;
    
    rotation.m[4] = yaxis.x;
    rotation.m[5] = yaxis.y;
    rotation.m[6] = yaxis.z;
    rotation.m[7] = 0;
    rotation.m[8] = zaxis.x;
    rotation.m[9] = zaxis.y;
    rotation.m[10] = zaxis.z;
    rotation.m[11] = 0;
    
    Quaternion  quaternion;
    Quaternion::createFromRotationMatrix(rotation,&quaternion);
    quaternion.normalize();
    setRotationQuat(quaternion);
}

const Mat4& Camera::getViewProjectionMatrix() const
{
    getViewMatrix();
    if (_viewProjectionDirty)
    {
        _viewProjectionDirty = false;
        Mat4::multiply(_projection, _view, &_viewProjection);
    }
    
    return _viewProjection;
}

void Camera::setAdditionalProjection(const Mat4& mat)
{
    _projection = mat * _projection;
    getViewProjectionMatrix();
}

bool Camera::initDefault()
{
    auto size = Director::getInstance()->getWinSize();
    //create default camera
    auto projection = Director::getInstance()->getProjection();
    switch (projection)
    {
        case Director::Projection::_2D:
        {
            initOrthographic(0, size.width, 0, size.height, -1024, 1024);
            setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
            setRotation3D(Vec3(0.f, 0.f, 0.f));
            break;
        }
        case Director::Projection::_3D:
        {
            float zeye = Director::getInstance()->getZEye();
            initPerspective(60, (GLfloat)size.width / size.height, 10, zeye + size.height / 2.0f);
            Vec3 eye(size.width/2, size.height/2.0f, zeye), center(size.width/2, size.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
            setPosition3D(eye);
            lookAt(center, up);
            break;
        }
        default:
            CCLOG("unrecognized projection");
            break;
    }
    return true;
}

bool Camera::initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    _fieldOfView = fieldOfView;
    _aspectRatio = aspectRatio;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
    Mat4::createPerspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane, &_projection);
    _viewProjectionDirty = true;
    _frustumDirty = true;
    
    return true;
}

bool Camera::initOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    _nearPlane = nearPlane;
    _farPlane = farPlane;
    Mat4::createOrthographicOffCenter(left, right, bottom, top, _nearPlane, _farPlane, &_projection);
    _viewProjectionDirty = true;
    _frustumDirty = true;
    
    return true;
}

Vec2 Camera::project(const Vec3& src) const
{
    Vec2 screenPos;
    
    auto viewport = Director::getInstance()->getWinSize();
    Vec4 clipPos;
    getViewProjectionMatrix().transformVector(Vec4(src.x, src.y, src.z, 1.0f), &clipPos);
    
    CCASSERT(clipPos.w != 0.0f, "clipPos.w can't be 0.0f!");
    float ndcX = clipPos.x / clipPos.w;
    float ndcY = clipPos.y / clipPos.w;
    
    screenPos.x = (ndcX + 1.0f) * 0.5f * viewport.width;
    screenPos.y = (1.0f - (ndcY + 1.0f) * 0.5f) * viewport.height;
    return screenPos;
}

Vec2 Camera::projectGL(const Vec3& src) const
{
    Vec2 screenPos;
    
    auto viewport = Director::getInstance()->getWinSize();
    Vec4 clipPos;
    getViewProjectionMatrix().transformVector(Vec4(src.x, src.y, src.z, 1.0f), &clipPos);
    
    CCASSERT(clipPos.w != 0.0f, "clipPos.w can't be 0.0f!");
    float ndcX = clipPos.x / clipPos.w;
    float ndcY = clipPos.y / clipPos.w;
    
    screenPos.x = (ndcX + 1.0f) * 0.5f * viewport.width;
    screenPos.y = (ndcY + 1.0f) * 0.5f * viewport.height;
    return screenPos;
}

Vec3 Camera::unproject(const Vec3& src) const
{
    Vec3 dst;
    unproject(Director::getInstance()->getWinSize(), &src, &dst);
    return dst;
}

Vec3 Camera::unprojectGL(const Vec3& src) const
{
    Vec3 dst;
    unprojectGL(Director::getInstance()->getWinSize(), &src, &dst);
    return dst;
}

void Camera::unproject(const Size& viewport, const Vec3* src, Vec3* dst) const
{
    CCASSERT(src && dst, "vec3 can not be null");
    
    Vec4 screen(src->x / viewport.width, ((viewport.height - src->y)) / viewport.height, src->z, 1.0f);
    screen.x = screen.x * 2.0f - 1.0f;
    screen.y = screen.y * 2.0f - 1.0f;
    screen.z = screen.z * 2.0f - 1.0f;
    
    getViewProjectionMatrix().getInversed().transformVector(screen, &screen);
    if (screen.w != 0.0f)
    {
        screen.x /= screen.w;
        screen.y /= screen.w;
        screen.z /= screen.w;
    }
    
    dst->set(screen.x, screen.y, screen.z);
}

void Camera::unprojectGL(const Size& viewport, const Vec3* src, Vec3* dst) const
{
    CCASSERT(src && dst, "vec3 can not be null");
    
    Vec4 screen(src->x / viewport.width, src->y / viewport.height, src->z, 1.0f);
    screen.x = screen.x * 2.0f - 1.0f;
    screen.y = screen.y * 2.0f - 1.0f;
    screen.z = screen.z * 2.0f - 1.0f;
    
    getViewProjectionMatrix().getInversed().transformVector(screen, &screen);
    if (screen.w != 0.0f)
    {
        screen.x /= screen.w;
        screen.y /= screen.w;
        screen.z /= screen.w;
    }
    
    dst->set(screen.x, screen.y, screen.z);
}

bool Camera::isVisibleInFrustum(const AABB* aabb) const
{
    if (_frustumDirty)
    {
        _frustum.initFrustum(this);
        _frustumDirty = false;
    }
    return !_frustum.isOutOfFrustum(*aabb);
}

float Camera::getDepthInView(const Mat4& transform) const
{
    Mat4 camWorldMat = getNodeToWorldTransform();
    const Mat4 &viewMat = camWorldMat.getInversed();
    float depth = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);
    return depth;
}

void Camera::render(Node* scene, CameraFlag flag, Node* lightNode, experimental::FrameBuffer* frameBuffer)
{
	auto director = Director::getInstance();
	auto renderer = director->getRenderer();
	
	applyViewport(frameBuffer);
	if (frameBuffer == nullptr)
	{
		frameBuffer = experimental::FrameBuffer::getDefaultFBO();
	}
	frameBuffer->applyFBO();
	applyScissors();

	_visitingCamera = this;
	_visitingScene = scene;
	_lightNode = lightNode;

	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_VIEWPROJECTION);
	director->loadVPMatrices(getViewMatrix(), getProjectionMatrix());
	
	clearBackground();
	scene->visit(renderer, scene->getNodeToParentTransform(), 0);
	renderer->render();
	
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_VIEWPROJECTION);

	_visitingCamera = nullptr;
	_visitingScene = nullptr;
}

void Camera::clearBackground()
{
    if (_clearBrush)
    {
        _clearBrush->drawBackground(this);
    }
}

void Camera::setScissors(Rect rect)
{
	_scissorsRect = rect;
}

void Camera::setViewport(float left, float bottom, float width, float height)
{
	auto viewport = experimental::Viewport(left, bottom, width, height);
	setViewport(viewport);
}

void Camera::applyViewport(experimental::FrameBuffer* frameBuffer)
{
    if(nullptr == frameBuffer)
    {
        glViewport(getDefaultViewport()._left, getDefaultViewport()._bottom, getDefaultViewport()._width, getDefaultViewport()._height);
    }
    else
    {
        glViewport(_viewport._left * frameBuffer->getWidth(), _viewport._bottom * frameBuffer->getHeight(),
                   _viewport._width * frameBuffer->getWidth(), _viewport._height * frameBuffer->getHeight());
    }
    
}

void Camera::applyScissors()
{
	if (_scissorsRect.size.width + _scissorsRect.size.height > 0)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(_scissorsRect.origin.x, _scissorsRect.origin.y, _scissorsRect.size.width, _scissorsRect.size.height);
	}
	else
	{
		glDisable(GL_SCISSOR_TEST);
	}
}

void Camera::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    _viewProjectionUpdated = _transformUpdated;
    return Node::visit(renderer, parentTransform, parentFlags);
}

void Camera::setBackgroundBrush(CameraBackgroundBrush* clearBrush)
{
    CC_SAFE_RETAIN(clearBrush);
    CC_SAFE_RELEASE(_clearBrush);
    _clearBrush = clearBrush;
}

NS_CC_END
