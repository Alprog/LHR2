
World3D = Derive("World3D", cc.Node)

function World3D:init()
    self.shadowMapBuffer = FrameBuffer:create(self, cc.size(1024, 1024), function(sender, size)
        sender:attachNewTexture(FrameBuffer.Index.DepthStencil, size, cc.DEPTH24_STENCIL8)
    end)
        
    self.gBuffer = GBuffer:create(self, theApp.windowSize)
    self.frameBuffer = FrameBuffer:create(self, theApp.windowSize, function(sender, size)
        sender:attachNewTexture(0, size, cc.BGRA8888)
    end) 
end

function World3D:createTexture(size, format)
    return cc.Texture2D:create(size.width, size.height, format or cc.BGRA8888)
end

function World3D:initTextures(size)
    self.albedoTexture = createTexture(size)
    self.normalTexture = createTexture(size)
    self.idsTexture = createTexture(size)
    self.velocityTexture = createTexture(size, cc.RG16F)
    self.depthStencil = createTexture(size, cc.DEPTH24_STENCIL8)
    
    self.shadowMapTexture = createTexture(cc.size(1024, 1024), cc.DEPTH24_STENCIL8)
    self.historyTexture = createTexture(size)
end

function World3D:onResize(size)
    self:setTransformUpdated()
    self.gBuffer:resize(size)
    self.frameBuffer:resize(size)
    self.camera:setWindowAspect()
end

function World3D:render()
    self:renderGeometry()
    self:bakeShadows()
    self:lighting()
    self:renderTranparent()
    self:temporalAA()
end

function World3D:renderGeometry()
    self.gBuffer:clearFBO()
    self.camera:render(self, cc.CameraFlag.DEFAULT, self.gBuffer)
end

function World3D:bakeShadows()
    self.shadowMapBuffer:clearFBO()
    if self.lightCamera then
        self.lightCamera:render(self, cc.CameraFlag.DEFAULT, self.shadowMapBuffer)
    end

    self.frameBuffer:clearFBO()
    thePostProcessor:setup(self.gBuffer, self.shadowMapBuffer, self.frameBuffer, self.camera, self.lightCamera)
    thePostProcessor:perform()
end

function World3D:lighting()
    
end

function World3D:renderTranparent()
    
end

function World3D:temporalAA()
    
end

function World3D:getObjectFromScreenPos(pos)
    local texel = self.gBuffer:getTexel(GBuffer.Index.Ids, pos.x, pos.y)
    local index = bytesToIndex(texel.x, texel.y)
    return Object:fromIndex(index)
end