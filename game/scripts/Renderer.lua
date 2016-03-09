
Renderer = Class("Renderer")

function Renderer:init()
    self.gBuffer = ccexp.FrameBuffer:create(1)
    self.gBuffer:retain()
        
    self:initShadowMap()
end

function Renderer:initShadowMap()
    local size = cc.size(1024, 1024)
    self.shadowMapBuffer = ccexp.FrameBuffer:create(1)
    self.shadowMapBuffer:setSize(size.width, size.height)
    self.shadowMapTexture = self:createTexture(size, cc.DEPTH24_STENCIL8)
    self.shadowMapBuffer:attachDepthStencil(self.shadowMapTexture)
    self.shadowMapBuffer:retain()
end

function Renderer:createTexture(size, format)
    return cc.Texture2D:create(size.width, size.height, format or cc.BGRA8888, 0)
end

function Renderer:onResize(size)
    self.primaryTexture = self:createTexture(size)
    self.secondaryTexture = self:createTexture(size)
    self.historyTexture = self:createTexture(size)
    
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
end

function Renderer:render(scene)
    self.scene = scene
    self:renderGeometry()
    self:bakeShadows()
    self:lighting()
    self:renderTranparent()
    self:temporalAA()
end

function Renderer:renderGeometry()
    self.gBuffer:clearFBO()
    self.scene.camera:render(self.scene, cc.CameraFlag.DEFAULT, self.gBuffer)
end

function Renderer:bakeShadows()
    self:renderShadowMap()
    self:renderScreenShadow()
end

function Renderer:renderShadowMap()
    self.shadowMapBuffer:clearFBO()
    self.scene.lightCamera:render(self.scene, cc.CameraFlag.DEFAULT, self.shadowMapBuffer)
end

function Renderer:renderScreenShadow()
    local state = createState('sprite', 'shadow')
    state:setUniformTexture('depthTexture', self.depthTexture)
    state:setUniformTexture('shadowMapTexture', self.shadowMapTexture)
    local screenToWorld = cc.mat4.getInversed(self.scene.camera:getViewProjectionMatrix())
    state:setUniformMat4('screenToWorld', screenToWorld)
    state:setUniformMat4('worldToShadowMap', self.scene.lightCamera:getViewProjectionMatrix())
    thePostProcessor:perform(state, self.primaryTexture)
end

function Renderer:swapTextures()
   self.primaryTexture, self.secondaryTexture = self.secondaryTexture, self.primaryTexture
end

function Renderer:lighting()   
    local state = createState('sprite', 'halflambert')
    
    local position = self.scene.lightCamera:getPosition3D()  
    state:setUniformVec3('lightPosition', position)
    state:setUniformTexture('albedoTexture', self.albedoTexture)
    state:setUniformTexture('normalTexture', self.normalTexture)
    state:setUniformTexture('depthTexture', self.depthTexture)
    state:setUniformTexture('shadowMapTexture', self.shadowMapTexture)
    state:setUniformTexture('wrapTexture', getTexture('wrap2.png'))
    
    local screenToWorld = cc.mat4.getInversed(self.scene.camera:getViewProjectionMatrix())
    state:setUniformMat4('screenToWorld', screenToWorld)
    
    if self.lightCamera then
        local worldToShadowMap = self.scene.lightCamera:getViewProjectionMatrix()
        state:setUniformMat4('worldToShadowMap', worldToShadowMap)
    end
    
    thePostProcessor:perform(state, self.primaryTexture)
    
        
    --[[local texelSize = Vec(1 / self.frameBuffer.width, 1 / self.frameBuffer.height)    
    state:setUniformVec2('texelSize', texelSize)
    local scale = math.min(0.33 / theApp:getDeltaTime(), 1)
    state:setUniformFloat('velocityScale', scale)]]
end

function Renderer:renderTranparent()
    
end

function Renderer:temporalAA()
    
end

function Renderer:getObjectFromScreenPos(pos)
    local texel = self.gBuffer:getTexel(GBuffer.Index.Ids, pos.x, pos.y)
    local index = bytesToIndex(texel.x, texel.y)
    return Object:fromIndex(index)
end