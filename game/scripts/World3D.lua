
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

function World3D:onResize(size)
    self:setTransformUpdated()
    self.gBuffer:resize(size)
    self.frameBuffer:resize(size)
    self.camera:setWindowAspect()
end

function World3D:render()
    -- G Buffer
    self.gBuffer:clearFBO()
    self.camera:render(self, cc.CameraFlag.DEFAULT, self.gBuffer)
    
    -- Shadows
    self.shadowMapBuffer:clearFBO()
    self.lightCamera:render(self, cc.CameraFlag.DEFAULT, self.shadowMapBuffer)

    self.frameBuffer:clearFBO()
    thePostProcessor:setup(self.gBuffer, self.shadowMapBuffer, self.frameBuffer, self.camera, self.lightCamera)
    thePostProcessor:perform()
end