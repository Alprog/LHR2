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

RenderBuffer::RenderBuffer()
: _name(0)
, _width(0)
, _height(0)
, _format(GL_RGBA8)
, _multisamples(0)
{
}

RenderBuffer::~RenderBuffer()
{
    if(glIsRenderbuffer(_name))
    {
        glDeleteRenderbuffers(1, &_name);
		_name = 0;
    }
}

RenderBuffer* RenderBuffer::create(unsigned int width, unsigned int height, Texture2D::PixelFormat format, unsigned int multisample)
{
	auto result = new (std::nothrow) RenderBuffer();

	if (result && result->init(width, height, format, multisample))
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

bool RenderBuffer::init(unsigned int width, unsigned int height, Texture2D::PixelFormat format, unsigned int multisamples)
{
	_width = width;
	_height = height;
	_format = Texture2D::_pixelFormatInfoTables.at(format).internalFormat;
	_multisamples = multisamples;

    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    glGenRenderbuffers(1, &_name);
    glBindRenderbuffer(GL_RENDERBUFFER, _name);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, _format, width, height);

    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    
    return true;
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

FrameBuffer* FrameBuffer::create(uint8_t fid)
{
    auto result = new (std::nothrow) FrameBuffer();
    if(result && result->init(fid))
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

bool FrameBuffer::init(uint8_t fid)
{
    _fid = fid;
    _width = 0;
    _height = 0;
    
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
, _fboBindingDirty(true)
, _isDefault(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _dirtyFBOListener(nullptr)
#endif
{
    _frameBuffers.insert(this);
	for (int i = 0; i < RENDER_TARGETS_COUNT; i++)
		_renderTargets[i] = nullptr;
}

FrameBuffer::~FrameBuffer()
{
    if(!isDefaultFBO())
    {
		for (int i = 0; i < RENDER_TARGETS_COUNT; i++)
			CC_SAFE_RELEASE_NULL(_renderTargets[i]);
        glDeleteFramebuffers(1, &_fbo);
        _fbo = 0;
        _frameBuffers.erase(this);
#if CC_ENABLE_CACHE_TEXTURE_DATA
        Director::getInstance()->getEventDispatcher()->removeEventListener(_dirtyFBOListener);
#endif
    }
}

Vec4 FrameBuffer::getTexel(int colorTarget, int x, int y)
{
	static GLuint pboids[2] = { 0, 0 };
	static int pboIndex = 0;

	if (pboids[0] == 0)
	{
		glGenBuffers(2, pboids);
		for (int i = 0; i < 2; i++)
		{
			glBindBuffer(GL_PIXEL_PACK_BUFFER, pboids[i]);
			glBufferData(GL_PIXEL_PACK_BUFFER, 4, 0, GL_STREAM_READ);
		}
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	}

	GLint oldFBO;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	uint8_t texel[4];
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pboids[pboIndex]);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + colorTarget);
	glReadPixels(x, y, 1, 1, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glBindBuffer(GL_PIXEL_PACK_BUFFER, pboids[1 - pboIndex]);

	uint8_t* src = (uint8_t*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
	if (src)
	{
		for (int i = 0; i < 4; i++)
		{
			texel[i] = src[i];
		}
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
	}
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
	pboIndex = 1 - pboIndex;

	return Vec4(texel[2], texel[1], texel[0], texel[3]);
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

Ref* FrameBuffer::getRenderTarget(int index) const
{
	if (index >= 0 && index < RENDER_TARGETS_COUNT)
	{
		return _renderTargets[index];
	}
	return nullptr;
}

void FrameBuffer::attachDepth(Ref* renderTarget)
{
	attachRenderTarget(DEPTH_INDEX, renderTarget);
}

void FrameBuffer::attachStencil(Ref* renderTarget)
{
	attachRenderTarget(STENCIL_INDEX, renderTarget);
}

void FrameBuffer::attachDepthStencil(Ref* renderTarget)
{
	attachRenderTarget(DEPTH_INDEX, renderTarget);
	attachRenderTarget(STENCIL_INDEX, renderTarget);
}

void FrameBuffer::attachRenderTarget(int index, Ref* renderTarget)
{
	if (_renderTargets[index] == renderTarget)
	{
		return;
	}
		
	CC_SAFE_RELEASE(_renderTargets[index]);
	_renderTargets[index] = renderTarget;
	CC_SAFE_RETAIN(renderTarget);
	_fboBindingDirty = true;
}

void FrameBuffer::applyFBO()
{
    CHECK_GL_ERROR_DEBUG();
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    CHECK_GL_ERROR_DEBUG();

	if (isDefaultFBO())
	{
		return;
	}

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT };

	if (_fboBindingDirty)
	{
		for (int i = 0; i < RENDER_TARGETS_COUNT; i++)
		{
			GLint attachment = buffers[i];
			auto renderTarget = _renderTargets[i];
			
			auto texture = dynamic_cast<Texture2D*>(renderTarget);

			if (texture)
			{
				auto textarget = texture->getMultisamples() > 0 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textarget, texture->getName(), 0);
				CHECK_GL_ERROR_DEBUG();
				continue;
			}

			auto buffer = dynamic_cast<RenderBuffer*>(renderTarget);
			auto name = buffer ? buffer->getName() : 0;
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, name);
			CHECK_GL_ERROR_DEBUG();
		}

		_renderTargetCount = 0;
		for (int i = 0; i < COLOR_TARGETS_COUNT; i++)
		{
			if (_renderTargets[i])
				_renderTargetCount++;
			else
				break;
		}

		if(GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
		{
			CCLOG("FrameBuffer Status Error %d", (int)glCheckFramebufferStatus(GL_FRAMEBUFFER));
		}

		_fboBindingDirty = false;
	}
	
	glDrawBuffers(_renderTargetCount, buffers);
}

} //end of namespace experimental
NS_CC_END
