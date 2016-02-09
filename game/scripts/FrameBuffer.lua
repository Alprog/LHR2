
FrameBuffer = Class('FrameBuffer')

function FrameBuffer:init()
    self.downScale = 4
    self:resize(theApp.windowSize)
end

function FrameBuffer:resize(size)
    self:setSize(size.width / self.downScale, size.height / self.downScale)
end

function FrameBuffer:setSize(width, height)
    if self.width == width and self.height == height then
        return
    end
    
    self.cObj = ccexp.FrameBuffer:create(1, width, height)
    self.rt = ccexp.RenderTarget:create(width, height)
    self.rtDS = ccexp.RenderTargetDepthStencil:create(width, height)
    self.cObj:attachRenderTarget(self.rt)
    self.cObj:attachDepthStencilTarget(self.rtDS)
    
    self.width = width
    self.height = height
end

function FrameBuffer:getTexture()
    return self.cObj:getRenderTarget():getTexture()
end

function FrameBuffer:getTexel(x, y)
    return self.cObj:getTexel(x / self.downScale, y / self.downScale)
end