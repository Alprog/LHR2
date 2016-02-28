
PostProcessor = NewClass('PostProcessor')

function PostProcessor:init(app)
    self.camera = cc.Camera:create()
    self.camera:setOrthographic(0, 1, 0, 1, -1, 1)
    self.camera:retain()
    
    self.sprite = cc.Sprite:create('pixel.png')
    self.sprite:setAnchorPoint(0, 0)
    
    self.sprite:retain()
    
    --self.frameBuffer = ccexp.FrameBuffer:create(1, 0, 0)
    --self.frameBuffer:retain()
end

function PostProcessor:setup(gBuffer, outBuffer, sceneCamera, lightCamera)
    
    self.frameBuffer = outBuffer
    
    local shader = getShader('flippedSprite', 'halflambert')
    local state = cc.GLProgramState:create(shader)
    
    --[[local texelSize = Vec(1 / self.frameBuffer.width, 1 / self.frameBuffer.height)    
    state:setUniformVec2('texelSize', texelSize)
    local scale = math.min(0.33 / theApp:getDeltaTime(), 1)
    state:setUniformFloat('velocityScale', scale)]]
    
    local position = Vec(-20, 50, 70)    
    state:setUniformVec3('lightPosition', position)
    
    state:setUniformTexture('albedoTexture', gBuffer:getAlbedoTexture())
    state:setUniformTexture('normalTexture', gBuffer:getNormalTexture())
    state:setUniformTexture('depthTexture', gBuffer:getDepthStencilTexture())
    --state:setUniformTexture('velocityTexture', gBuffer:getRenderTarget(3))
    
    self.sprite:setGLProgramState(state)
    
    
    state:setUniformTexture('normalTexture', gBuffer:getRenderTarget(1))
    state:setUniformTexture('wrapTexture', getTexture('wrap.png'))
    
    local worldToScreen = sceneCamera:getProjectionMatrix()
    local proj = Vec(worldToScreen[0], worldToScreen[5], worldToScreen[10], worldToScreen[11])
    state:setUniformVec4('proj', proj)
    
    local projectedToWorld = cc.mat4.getInversed(sceneCamera:getViewProjectionMatrix())
    local worldToShadowMap = lightCamera:getViewProjectionMatrix()
    state:setUniformMat4('projectedToWorld', projectedToWorld)
    state:setUniformMat4('viewToWorld', cc.mat4.getInversed(sceneCamera:getViewMatrix()))
    state:setUniformMat4('worldToShadowMap', worldToShadowMap)
    
    state:setUniformMat4('view', sceneCamera:getViewMatrix())
    state:setUniformMat4('projection', sceneCamera:getProjectionMatrix())
    state:setUniformMat4('viewProjection', sceneCamera:getViewProjectionMatrix())
    
    --local rt = gBuffer:getRenderTarget(0)
    --self.frameBuffer:attachRenderTarget(rt, i - 1)
end


function PostProcessor:perform()
    self.camera:render(self.sprite, cc.CameraFlag.DEFAULT, self.frameBuffer)
end