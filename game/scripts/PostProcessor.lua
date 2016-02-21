
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

function PostProcessor:setup(gBuffer, outBuffer)
    
    self.frameBuffer = outBuffer
    
    local shader = getShader('flippedSprite', 'post')
    local state = cc.GLProgramState:create(shader)
    
    local texelSize = Vec(1 / self.frameBuffer.width, 1 / self.frameBuffer.height)    
    state:setUniformVec2('texelSize', texelSize)
    local scale = math.min(0.33 / theApp:getDeltaTime(), 1)
    state:setUniformFloat('velocityScale', scale)
    
    state:setUniformTexture('colorTexture', gBuffer:getTexture(1))
    state:setUniformTexture('velocityTexture', gBuffer:getTexture(3))
    
    self.sprite:setGLProgramState(state)
    
    --local rt = gBuffer:getRenderTarget(0)
    --self.frameBuffer:attachRenderTarget(rt, i - 1)
    
end

function PostProcessor:perform()
    self.camera:render(self.sprite, cc.CameraFlag.DEFAULT, self.frameBuffer)
end