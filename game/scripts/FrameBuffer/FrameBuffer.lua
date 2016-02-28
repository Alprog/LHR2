
FrameBuffer = Class('FrameBuffer', ccexp.FrameBuffer)

FrameBuffer.Index =
{
    DepthStencil = 4    
}

function FrameBuffer:instantinate()
    return FrameBuffer.__create(1)
end

function FrameBuffer:init(parent, onResize)
    parent:keepObject(self)
    if onResize then
        self.onResize = onResize
    end
    if self.onResize then
        self:onResize(theApp.windowSize)
    end
end

function FrameBuffer:attachNewTexture(index, size, format, multisamples)
    self:attachNewTarget(cc.Texture2D, index, size, format, multisamples)
end

function FrameBuffer:attachNewBuffer(index, size, format, multisamples)
    self:attachNewTarget(cc.RenderBuffer, index, size, format, multisamples)
end

function FrameBuffer:attachNewTarget(class, index, size, format, multisamples)
    multisamples = multisamples or 0
    local texture = class:create(size.width, size.height, format, multisamples)
    self:attachRenderTarget(index, texture)
end