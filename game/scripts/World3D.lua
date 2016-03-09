
World3D = Derive("World3D", cc.Node)

function World3D:init()
    
    self.gBuffer = ccexp.FrameBuffer:create(1)
    
    
    self:keepObject(self.gBuffer)
    
    
    self:initShadowMap()
        
    self.frameBuffer = FrameBuffer:create(self, theApp.windowSize, function(sender, size)
        sender:attachNewTexture(0, size, cc.BGRA8888)
    end) 
end

function World3D:initShadowMap()
    local size = cc.size(1024, 1024)
    self.shadowMapBuffer = ccexp.FrameBuffer:create(1)
    self.shadowMapBuffer:setSize(size.width, size.height)
    self.shadowMapTexture = self:createTexture(size, cc.DEPTH24_STENCIL8)
    self.shadowMapBuffer:attachDepthStencil(self.shadowMapTexture)
    self:keepObject(self.shadowMapBuffer)
end

function World3D:createTexture(size, format)
    return cc.Texture2D:create(size.width, size.height, format or cc.BGRA8888, 0)
end

function World3D:initTextures(size)   
    
    self.historyTexture = self:createTexture(size)
end

function World3D:onResize(size)
    self.albedoTexture = self:createTexture(size)
    self.normalTexture = self:createTexture(size)
    self.idsTexture = self:createTexture(size)
    self.velocityTexture = self:createTexture(size, cc.RG16F)
    self.depthTexture = self:createTexture(size, cc.DEPTH24_STENCIL8)
    
    self.gBuffer:setSize(size.width, size.height)
    self.gBuffer:attachRenderTarget(0, self.albedoTexture)
    self.gBuffer:attachRenderTarget(1, self.normalTexture)
    self.gBuffer:attachRenderTarget(2, self.idsTexture)
    self.gBuffer:attachRenderTarget(3, self.velocityTexture)
    self.gBuffer:attachDepthStencil(self.depthTexture)
    
    self:setTransformUpdated()
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
end

function World3D:lighting()
    self.frameBuffer:clearFBO()
    
    
    --thePostProcessor:setup(self.gBuffer, self.shadowMapBuffer, self.frameBuffer, self.camera, self.lightCamera)
     
     
    thePostProcessor.frameBuffer = self.frameBuffer
     
    local shader = getShader('sprite', 'halflambert')
    local state = cc.GLProgramState:create(shader)

    
    local position = self.lightCamera:getPosition3D()  
    state:setUniformVec3('lightPosition', position)
    state:setUniformTexture('albedoTexture', self.albedoTexture)
    state:setUniformTexture('normalTexture', self.normalTexture)
    state:setUniformTexture('depthTexture', self.depthTexture)
    state:setUniformTexture('shadowMapTexture', self.shadowMapTexture)
    state:setUniformTexture('wrapTexture', getTexture('wrap2.png'))
    
    local screenToWorld = cc.mat4.getInversed(self.camera:getViewProjectionMatrix())
    state:setUniformMat4('screenToWorld', screenToWorld)
    
    if self.lightCamera then
        local worldToShadowMap = self.lightCamera:getViewProjectionMatrix()
        state:setUniformMat4('worldToShadowMap', worldToShadowMap)
    end
    
    thePostProcessor.sprite:setGLProgramState(state)
    thePostProcessor:perform()
    
        
    --[[local texelSize = Vec(1 / self.frameBuffer.width, 1 / self.frameBuffer.height)    
    state:setUniformVec2('texelSize', texelSize)
    local scale = math.min(0.33 / theApp:getDeltaTime(), 1)
    state:setUniformFloat('velocityScale', scale)]]
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