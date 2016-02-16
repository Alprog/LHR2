/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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
 ****************************************************************************/

#include "renderer/CCFrameBuffer.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "CCImage.h"

NS_CC_BEGIN
namespace experimental{
FrameBuffer* FrameBuffer::_defaultFBO = nullptr;
std::set<FrameBuffer*> FrameBuffer::_frameBuffers;

Viewport::Viewport(float left, float bottom, float width, float height)
: _left(left)
, _bottom(bottom)
, _width(width)
, _height(height)
{
}

Viewport::Viewport()
{
    _left = _bottom = 0.f;
    _width = _height = 1.0f;
}

RenderTargetBase::RenderTargetBase()
{
    
}

RenderTargetBase::~RenderTargetBase()
{
    
}

bool RenderTargetBase::init(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    return true;
}

RenderTarget* RenderTarget::create(unsigned int width, unsigned int height, Texture2D::PixelFormat format, int multisamples)
{
    auto result = new (std::nothrow) RenderTarget();
    if(result && result->init(width, height,format, multisamples))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool RenderTarget::init(unsigned int width, unsigned int height, Texture2D::PixelFormat format, int multisamples)
{
    if(!RenderTargetBase::init(width, height))
    {
        return false;
    }
    
    _texture = new (std::nothrow) Texture2D();
    if(nullptr == _texture) return false;
    //TODO: FIX me, get the correct bit depth for pixelformat
    auto dataLen = width * height * 4;
    auto data = malloc(dataLen);
    if( nullptr == data) return false;
	
    memset(data, 0, dataLen);
    if(_texture->initWithData(data, dataLen, format, width, height, Size(width, height), multisamples))
    {
        _texture->autorelease();
        CC_SAFE_RETAIN(_texture);
        free(data);
    }
    else
    {
        CC_SAFE_DELETE(_texture);
        free(data);
        return false;
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _rebuildTextureListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        auto dataLen = _width * _height * 4;
        auto data = malloc(dataLen);
        _texture->initWithData(data, dataLen,_texture->getPixelFormat(), _width, _height, Size(_width, _height));
        free(data);
        CCLOG("RenderTarget Texture recreated is %d", _texture->getName());
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_rebuildTextureListener, -1);
#endif
    return true;
}

RenderTarget::RenderTarget()
: _texture(nullptr)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _rebuildTextureListener(nullptr)
#endif
{
    _type = Type::Texture2D;
}

RenderTarget::~RenderTarget()
{
    CC_SAFE_RELEASE_NULL(_texture);
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_rebuildTextureListener);
#endif
}

RenderTargetRenderBuffer::RenderTargetRenderBuffer()
: _colorBuffer(0)
, _format(GL_RGBA4)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _reBuildRenderBufferListener(nullptr)
#endif
{
    _type = Type::RenderBuffer;
}

RenderTargetRenderBuffer::~RenderTargetRenderBuffer()
{
    if(glIsRenderbuffer(_colorBuffer))
    {
        glDeleteRenderbuffers(1, &_colorBuffer);
        _colorBuffer = 0;
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_reBuildRenderBufferListener);
#endif
}

bool RenderTargetRenderBuffer::init(unsigned int width, unsigned int height, int multisamples)
{
    if(!RenderTargetBase::init(width, height)) return false;
    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    //generate depthStencil
    glGenRenderbuffers(1, &_colorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
    //todo: this could have a param
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, _format, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _reBuildRenderBufferListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        /** listen the event that renderer was recreated on Android/WP8 */
        GLint oldRenderBuffer(0);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
        
        glGenRenderbuffers(1, &_colorBuffer);
        //generate depthStencil
        glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, _format, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
        CCLOG("RenderTargetRenderBuffer recreated, _colorBuffer is %d", _colorBuffer);
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_reBuildRenderBufferListener, -1);
#endif
    
    return true;
}


RenderTargetRenderBuffer* RenderTargetRenderBuffer::create(unsigned int width, unsigned int height, int multisample)
{
    auto result = new (std::nothrow) RenderTargetRenderBuffer();
    
    if(result && result->init(width, height, multisample))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

RenderTargetDepthStencil::RenderTargetDepthStencil()
: _depthStencilBuffer(0)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _reBuildDepthStencilListener(nullptr)
#endif
{
    _type = Type::RenderBuffer;
}

RenderTargetDepthStencil::~RenderTargetDepthStencil()
{
    if(glIsRenderbuffer(_depthStencilBuffer))
    {
        glDeleteRenderbuffers(1, &_depthStencilBuffer);
        _depthStencilBuffer = 0;
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_reBuildDepthStencilListener);
#endif
}

bool RenderTargetDepthStencil::init(unsigned int width, unsigned int height, int multisamples)
{
    if(!RenderTargetBase::init(width, height)) return false;
    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    //generate depthStencil
    glGenRenderbuffers(1, &_depthStencilBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _reBuildDepthStencilListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        /** listen the event that renderer was recreated on Android/WP8 */
        GLint oldRenderBuffer(0);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
        
        glGenRenderbuffers(1, &_depthStencilBuffer);
        //generate depthStencil
        glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
        CCLOG("RenderTargetDepthStencil recreated, _depthStencilBuffer is %d", _depthStencilBuffer);
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_reBuildDepthStencilListener, -1);
#endif
    
    return true;
}


RenderTargetDepthStencil* RenderTargetDepthStencil::create(unsigned int width, unsigned int height, int multisamples)
{
    auto result = new (std::nothrow) RenderTargetDepthStencil();
    
    if(result && result->init(width, height, multisamples))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool FrameBuffer::initWithGLView(GLView* view)
{
    if(view == nullptr)
    {
        return false;
    }
    GLint fbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbo);
    _fbo = fbo;
	_renderTargetCount = 1;
    return true;
}

FrameBuffer* FrameBuffer::getOrCreateDefaultFBO(GLView* view)
{
    if(nullptr == _defaultFBO)
    {
        auto result = new (std::nothrow) FrameBuffer();
        
        if(result && result->initWithGLView(view))
        {
            result->autorelease();
            result->_isDefault = true;
        }
        else
        {
            CC_SAFE_DELETE(result);
        }
        
        _defaultFBO = result;
    }
    
    return _defaultFBO;
}

void FrameBuffer::applyDefaultFBO()
{
    if(_defaultFBO)
    {
        _defaultFBO->applyFBO();
    }
}

void FrameBuffer::clearAllFBOs()
{
    for (auto fbo : _frameBuffers)
    {
        fbo->clearFBO();
    }
}

FrameBuffer* FrameBuffer::create(uint8_t fid, unsigned int width, unsigned int height)
{
    auto result = new (std::nothrow) FrameBuffer();
    if(result && result->init(fid, width, height))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool FrameBuffer::init(uint8_t fid, unsigned int width, unsigned int height)
{
    _fid = fid;
    _width = width;
    _height = height;
    
    GLint oldfbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldfbo);

    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, oldfbo);
    
//    _rt = RenderTarget::create(width, height);
//    if(nullptr == _rt) return false;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _dirtyFBOListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        if(isDefaultFBO()) return;
        GLint oldfbo;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldfbo);

        glGenFramebuffers(1, &_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, oldfbo);
        CCLOG("Recreate FrameBufferObject _fbo is %d", _fbo);
        _fboBindingDirty = true;
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_dirtyFBOListener, -1);
#endif
    return true;
}

FrameBuffer::FrameBuffer()
: _clearColor(Color4F(0, 0, 0, 1))
, _clearDepth(1.0)
, _clearStencil(0)
, _fbo(0)
, _renderTargetCount(0)
, _rtDepthStencil(nullptr)
, _fboBindingDirty(true)
, _isDefault(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _dirtyFBOListener(nullptr)
#endif
{
    _frameBuffers.insert(this);
	for (int i = 0; i < MAX_RENDER_TARGET_COUNT; i++)
		_renderTargets[i] = nullptr;
}

FrameBuffer::~FrameBuffer()
{
    if(!isDefaultFBO())
    {
		for (int i = 0; i < MAX_RENDER_TARGET_COUNT; i++)
			CC_SAFE_RELEASE_NULL(_renderTargets[i]);
        CC_SAFE_RELEASE_NULL(_rtDepthStencil);
        glDeleteFramebuffers(1, &_fbo);
        _fbo = 0;
        _frameBuffers.erase(this);
#if CC_ENABLE_CACHE_TEXTURE_DATA
        Director::getInstance()->getEventDispatcher()->removeEventListener(_dirtyFBOListener);
#endif
    }
}

Vec4 FrameBuffer::getTexel(int x, int y)
{
	GLint oldFBO;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	uint8_t texel[4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, texel);

	glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);

	return Vec4(texel[0], texel[1], texel[2], texel[3]);
}

/* get buffer as Image */
Image* FrameBuffer::newImage(bool fliimage)
{
	auto texture = _renderTargets[0]->getTexture();
	const Size& s = texture->getContentSizeInPixels();

	// to get the image size to save
	//        if the saving image domain exceeds the buffer texture domain,
	//        it should be cut
	int savedBufferWidth = (int)s.width;
	int savedBufferHeight = (int)s.height;

	GLubyte *buffer = nullptr;
	GLubyte *tempData = nullptr;
	Image *image = new (std::nothrow) Image();

	do
	{
		CC_BREAK_IF(!(buffer = new (std::nothrow) GLubyte[savedBufferWidth * savedBufferHeight * 4]));

		if (!(tempData = new (std::nothrow) GLubyte[savedBufferWidth * savedBufferHeight * 4]))
		{
			delete[] buffer;
			buffer = nullptr;
			break;
		}

		GLint oldFBO;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

		// TODO: move this to configration, so we don't check it every time
		/*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
		*/
		/*if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
		{
			// -- bind a temporary texture so we can clear the render buffer without losing our texture
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureCopy->getName(), 0);
			CHECK_GL_ERROR_DEBUG();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
		}*/
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, savedBufferWidth, savedBufferHeight, GL_RGBA, GL_UNSIGNED_BYTE, tempData);
		glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);

		if (fliimage) // -- flip is only required when saving image to file
		{
			// to get the actual texture data
			// #640 the image read from rendertexture is dirty
			for (int i = 0; i < savedBufferHeight; ++i)
			{
				memcpy(&buffer[i * savedBufferWidth * 4],
					&tempData[(savedBufferHeight - i - 1) * savedBufferWidth * 4],
					savedBufferWidth * 4);
			}

			image->initWithRawData(buffer, savedBufferWidth * savedBufferHeight * 4, savedBufferWidth, savedBufferHeight, 8);
		}
		else
		{
			image->initWithRawData(tempData, savedBufferWidth * savedBufferHeight * 4, savedBufferWidth, savedBufferHeight, 8);
		}

	} while (0);

	CC_SAFE_DELETE_ARRAY(buffer);
	CC_SAFE_DELETE_ARRAY(tempData);

	return image;
}

void FrameBuffer::clearFBO()
{
    applyFBO();
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClearDepth(_clearDepth);
    glClearStencil(_clearStencil);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    applyDefaultFBO();
}

RenderTargetBase* FrameBuffer::getRenderTarget(int index) const
{
	if (index >= 0 && index < MAX_RENDER_TARGET_COUNT)
	{
		return _renderTargets[index];
	}
	return nullptr;
}

void FrameBuffer::attachRenderTarget(RenderTargetBase* rt, int index)
{
    if(isDefaultFBO())
    {
        CCLOG("Can not apply render target to default FBO");
        return;
    }
    CC_ASSERT(rt);
    if(rt->getWidth() != _width || rt->getHeight() != _height)
    {
        CCLOG("Error, attach a render target with different size, Skip.");
        return;
    }
    CC_SAFE_RETAIN(rt);
    CC_SAFE_RELEASE(_renderTargets[index]);
	_renderTargets[index] = rt;
    _fboBindingDirty = true;
}

void FrameBuffer::applyFBO()
{
    CHECK_GL_ERROR_DEBUG();
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    CHECK_GL_ERROR_DEBUG();
    if(_fboBindingDirty && !isDefaultFBO())
    {
        CHECK_GL_ERROR_DEBUG();
		
		for (int i = 0; i < MAX_RENDER_TARGET_COUNT; i++)
		{
			auto rt = _renderTargets[i];

			if (rt)
			{
				if (RenderTargetBase::Type::Texture2D == rt->getType())
				{ 
					auto texture = rt->getTexture();
					auto textarget = texture->getMultisamples() > 0 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, textarget, texture->getName(), 0);
				}
				else
				{
					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_RENDERBUFFER, rt->getBuffer());
				}
			}
			else
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
			}

			CHECK_GL_ERROR_DEBUG();
		
			auto a = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (a == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
			{
				a = 0;
			}
		}

		_renderTargetCount = 0;
		for (int i = 0; i < MAX_RENDER_TARGET_COUNT; i++)
		{
			if (_renderTargets[i])
				_renderTargetCount++;
			else
				break;
		}

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, nullptr == _rtDepthStencil ? 0 : _rtDepthStencil->getBuffer());
        CHECK_GL_ERROR_DEBUG();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, nullptr == _rtDepthStencil ? 0 : _rtDepthStencil->getBuffer());
        CHECK_GL_ERROR_DEBUG();
        _fboBindingDirty = false;
    }
    if(GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
    {
        CCLOG("FrameBuffer Status Error %d", (int)glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    CHECK_GL_ERROR_DEBUG();

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT };
	glDrawBuffers(_renderTargetCount, buffers);
}

void FrameBuffer::attachDepthStencilTarget(RenderTargetDepthStencil* rt)
{
    if(isDefaultFBO())
    {
        CCLOG("Can not apply depth stencil target to default FBO");
        return;
    }
    
    if(nullptr != rt && (rt->getWidth() != _width || rt->getHeight() != _height))
    {
        CCLOG("Error, attach a render target Depth stencil with different size, Skip.");
        return;
    }
    CC_SAFE_RETAIN(rt);
    CC_SAFE_RELEASE(_rtDepthStencil);
    _rtDepthStencil = rt;
    _fboBindingDirty = true;
}
} //end of namespace experimental
NS_CC_END
