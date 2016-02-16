
FrameBuffer = Class('FrameBuffer')

function FrameBuffer:init(rtCount, depthStencil, multiSamples, downScale)
    self.rtCount = rtCount
    self.depthStencil = depthStencil
    self.multiSamples = multiSamples or 0
    self.downScale = downScale or 1
    self:resize(theApp.windowSize)
end

function FrameBuffer:resize(size)
    self:setSize(size.width / self.downScale, size.height / self.downScale)
end

function FrameBuffer:setSize(width, height)
    if self.width == width and self.height == height then
        return
    end
    
    self:releaseCObj()
    
    self.cObj = ccexp.FrameBuffer:create(1, width, height)   
    for i = 1, self.rtCount do
        local rt = ccexp.RenderTarget:create(width, height, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888, self.multiSamples)
        self.cObj:attachRenderTarget(rt, i - 1)
    end
    if self.depthStencil then
        self.rtDS = ccexp.RenderTargetDepthStencil:create(width, height, self.multiSamples)
        self.cObj:attachDepthStencilTarget(self.rtDS)
    end
    self.cObj:retain()
        
    self.width = width
    self.height = height
end

function FrameBuffer:getTexture(index)
    index = index or 1
    return self.cObj:getRenderTarget(index - 1):getTexture()
end

function FrameBuffer:getTexel(x, y)
    return self.cObj:getTexel(x / self.downScale, y / self.downScale)
end

function FrameBuffer:releaseCObj()
    if self.cObj then
        self.cObj:release()
        self.cObj = nil
    end
end

function FrameBuffer:destroy()
    self:releaseCObj()
end