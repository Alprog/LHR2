
GBuffer = Derive('GBuffer', FrameBuffer)

GBuffer.Indexes =
{
    Albedo = 0,
    Normal = 1,
    Ids = 2,
    Velocity = 3,
    DepthStencil = 4
}

function GBuffer:onResize(size)
    self:setSize(size.width, size.height)
    self:attachNewTexture(GBuffer.Indexes.Albedo, size, cc.BGRA8888)
    self:attachNewTexture(GBuffer.Indexes.Normal, size, cc.BGRA8888)
    self:attachNewTexture(GBuffer.Indexes.Ids, size, cc.BGRA8888)
    self:attachNewTexture(GBuffer.Indexes.Velocity, size, cc.RG16F)
    self:attachNewTexture(GBuffer.Indexes.DepthStencil, size, cc.DEPTH24_STENCIL8)
end

function GBuffer:getAlbedoTexture()
    return self:getRenderTarget(GBuffer.Indexes.Albedo)
end

function GBuffer:getNormalTexture()
    return self:getRenderTarget(GBuffer.Indexes.Normal)
end

function GBuffer:getIdsTexture()
    return self:getRenderTarget(GBuffer.Indexes.Ids)
end

function GBuffer:getVelocityTexture()
    return self:getRenderTarget(GBuffer.Indexes.Velocity)
end

function GBuffer:getDepthStencilTexture()
    return self:getRenderTarget(GBuffer.Indexes.DepthStencil)
end

