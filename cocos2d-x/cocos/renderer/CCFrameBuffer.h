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

#ifndef __CC_FRAME_BUFFER_H__
#define __CC_FRAME_BUFFER_H__

#include "base/CCRef.h"
#include "platform/CCGL.h"
#include "renderer/CCTexture2D.h"
#include <set>

NS_CC_BEGIN

class GLView;
class EventListenerCustom;

namespace experimental {

/**
 Viewport is a normalized to FrameBufferObject
 But for default FBO, the size is absolute.
 */
struct CC_DLL Viewport
{
    Viewport(float left, float bottom, float width, float height);
    Viewport();
    
    float _left;
    float _bottom;
    float _width;
    float _height;
};
    
class CC_DLL RenderBuffer : public Ref
{
public:
    
    static RenderBuffer* create(unsigned int width, unsigned int height, Texture2D::PixelFormat format, unsigned int multisamples = 0);
    
    bool init(unsigned int width, unsigned int height, Texture2D::PixelFormat format, unsigned int multisamples);
    
	inline GLuint getName() const { return _name; }
	inline unsigned int getWidth() const { return _width; }
	inline unsigned int getHeight() const { return _height; }
	inline GLuint getFormat() const { return _format; }
	inline unsigned int getMultisamples() const { return _multisamples; }

CC_CONSTRUCTOR_ACCESS:
	RenderBuffer();
    virtual ~RenderBuffer();
    
protected:
	GLuint _name;
	unsigned int _width;
	unsigned int _height;
	GLuint _format;
	unsigned int _multisamples;
};

const int COLOR_TARGETS_COUNT = 4;
const int DEPTH_INDEX = 4;
const int STENCIL_INDEX = 5;
const int RENDER_TARGETS_COUNT = COLOR_TARGETS_COUNT + 2;

class CC_DLL FrameBuffer : public Ref
{
public:
    static FrameBuffer* create(uint8_t fid);
    
    bool init(uint8_t fid);
public:
	Vec4 getTexel(int x, int y);

    GLuint getFBO() const { return _fbo; }
    GLuint getFID() const { return _fid; }
    void clearFBO();
    void applyFBO();
    void setClearColor(const Color4F& color) { _clearColor = color;}
    void setClearDepth(float depth) { _clearDepth = depth; }
    void setClearStencil(int8_t stencil) { _clearStencil = stencil; }
    const Color4F& getClearColor() const { return _clearColor; }
    float getClearDepth() const { return _clearDepth; }
    int8_t getClearStencil() const { return _clearStencil; }
    
	Ref* getRenderTarget(int index = 0) const;
    
    bool isDefaultFBO() const { return _isDefault; }
    unsigned int getWidth() const { return _width; }
    unsigned int getHeight() const { return _height; }
	void setSize(int width, int height) { _width = width; _height = height; }

	void attachRenderTarget(int index, Ref* renderTarget);
	void attachDepth(Ref* renderTarget);
	void attachStencil(Ref* renderTarget);
	void attachDepthStencil(Ref* renderTarget);

CC_CONSTRUCTOR_ACCESS:
    FrameBuffer();
    virtual ~FrameBuffer();
    bool initWithGLView(GLView* view);
private:
    //openGL content for FrameBuffer
    GLuint _fbo;
    //dirty flag for fbo binding
    bool _fboBindingDirty;

	int _renderTargetCount;
    //
    uint8_t _fid;
    //
    Color4F _clearColor;
    float   _clearDepth;
    int8_t  _clearStencil;
    int _width;
    int _height;
    Ref* _renderTargets[RENDER_TARGETS_COUNT];
    bool _isDefault;

public:
    static FrameBuffer* getOrCreateDefaultFBO(GLView* glView);
	static FrameBuffer* getDefaultFBO() { return _defaultFBO; }
    static void applyDefaultFBO();
    static void clearAllFBOs();
private:
    //static GLuint _defaultFBO;
    static FrameBuffer* _defaultFBO;
    static std::set<FrameBuffer*> _frameBuffers;
    
private:
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _dirtyFBOListener;
#endif
};
} // end of namespace experimental

NS_CC_END

#endif /* defined(__CC_FRAME_BUFFER_H__) */
