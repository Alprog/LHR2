
FrameBuffer = Class('FrameBuffer', ccexp.FrameBuffer)

function FrameBuffer:instantinate()
    return FrameBuffer.__create(1)
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
        local format = i ~= 3 and cc.BGRA8888 or cc.RG16F
        if self.isBuffer then
            local buffer = ccexp.RenderBuffer:create(width, height, format, self.multiSamples)
            self:attachRenderTarget(i - 1, buffer)
        else
            local texture = cc.Texture2D:create(width, height, format, self.multiSamples)
            self:attachRenderTarget(i - 1, texture)
        end
    end
    if self.depthStencil then
        local rt = cc.Texture2D:create(width, height, cc.DEPTH24_STENCIL8, self.multiSamples)
        self:attachDepthStencil(rt)
    end
    
    self.width = width
    self.height = height
end

function FrameBuffer:getTexel(x, y)
    return ccexp.FrameBuffer.getTexel(self, x / self.downScale, y / self.downScale)
end