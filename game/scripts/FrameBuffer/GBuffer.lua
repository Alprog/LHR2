
GBuffer = Derive('GBuffer', FrameBuffer)

GBuffer.Index =
{
    Albedo = 0,
    Normal = 1,
    Ids = 2,
    Velocity = 3,
    DepthStencil = 4
}

function GBuffer:onResize(size)
    self:setSize(size.width, size.height)
    self:attachNewTexture(GBuffer.Index.Albedo, size, cc.BGRA8888)
    self:attachNewTexture(GBuffer.Index.Normal, size, cc.BGRA8888)
    self:attachNewTexture(GBuffer.Index.Ids, size, cc.BGRA8888)
    self:attachNewTexture(GBuffer.Index.Velocity, size, cc.RG16F)
    self:attachNewTexture(GBuffer.Index.DepthStencil, size, cc.DEPTH24_STENCIL8)
end

function GBuffer:getAlbedoTexture()
    return self:getRenderTarget(GBuffer.Index.Albedo)
end

function GBuffer:getNormalTexture()
    return self:getRenderTarget(GBuffer.Index.Normal)
end

function GBuffer:getIdsTexture()
    return self:getRenderTarget(GBuffer.Index.Ids)
end

function GBuffer:getVelocityTexture()
    return self:getRenderTarget(GBuffer.Index.Velocity)
end

function GBuffer:getDepthStencilTexture()
    return self:getRenderTarget(GBuffer.Index.DepthStencil)
end

