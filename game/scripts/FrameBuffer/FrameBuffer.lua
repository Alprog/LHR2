
FrameBuffer = Class('FrameBuffer', ccexp.FrameBuffer)

FrameBuffer.Index =
{
    DepthStencil = 4    
}

function FrameBuffer:instantinate()
    return FrameBuffer.__create(1)
end

function FrameBuffer:init(parent, size, onResize)
    parent:keepObject(self)
    if onResize then
        self.onResize = onResize
    end
    self:resize(size)
end

function FrameBuffer:resize(size)
    if self:getWidth() ~= size.width or self:getHeight() ~= size.height then
        self:setSize(size.width, size.height)
        if self.onResize then
            self:onResize(size)
        end
    end   
end

function FrameBuffer:getDepthStencilTexture()
    return self:getRenderTarget(FrameBuffer.Index.DepthStencil)
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