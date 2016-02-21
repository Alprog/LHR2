
FrameBuffer = Class('FrameBuffer', ccexp.FrameBuffer)

function FrameBuffer:instantinate()
    return FrameBuffer.__create(1, 0, 0)
end

function FrameBuffer:init(parent, rtCount, depthStencil, multiSamples, downScale, isBuffer)
    parent:keepObject(self)
    
    self.rtCount = rtCount
    self.depthStencil = depthStencil
    self.multiSamples = multiSamples or 0
    self.downScale = downScale or 1
    self.isBuffer = isBuffer
    self:resize(theApp.windowSize)
end

function FrameBuffer:resize(size)
    self:setSize(size.width / self.downScale, size.height / self.downScale)
end

function FrameBuffer:setSize(width, height)
    if self.width == width and self.height == height then
        return
    end
    
    ccexp.FrameBuffer.setSize(self, width, height)
    
    for i = 1, self.rtCount do
        if self.isBuffer then
            local rt = ccexp.RenderTargetRenderBuffer:create(width, height, self.multiSamples)
            self:attachRenderTarget(rt, i - 1)
        else
            local format = i ~= 3 and cc.TEXTURE2_D_PIXEL_FORMAT_BGR_A8888 or cc.TEXTURE2_D_PIXEL_FORMAT_RG16F
            local rt = ccexp.RenderTarget:create(width, height, format, self.multiSamples)
            self:attachRenderTarget(rt, i - 1)
        end
    end
    if self.depthStencil then
        self.rtDS = ccexp.RenderTargetDepthStencil:create(width, height, self.multiSamples)
        self:attachDepthStencilTarget(self.rtDS)
    end
    
    self.width = width
    self.height = height
end

function FrameBuffer:getTexture(index)
    index = index or 1
    return self:getRenderTarget(index - 1):getTexture()
end

function FrameBuffer:getTexel(x, y)
    return ccexp.FrameBuffer.getTexel(self, x / self.downScale, y / self.downScale)
end