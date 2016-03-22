
PostProcessor = NewClass('PostProcessor')

function PostProcessor:init(app)
    self.frameBuffer = ccexp.FrameBuffer:create(1)
    self.frameBuffer:retain()
    
    self.camera = cc.Camera:create()
    self.camera:setOrthographic(0, 1, 0, 1, -1, 1)
    self.camera:setPosition3D(Vec(0, 0, -0.5))
    self.camera:retain()
    
    local builder = MeshBuilder:create()
    builder:addQuad(Vector(0, 0, 0), Vector(1, 0, 0), Vector(1, 1, 0), Vector(0, 1, 0))
    self.sprite = cc.Sprite3D:create()
    self.sprite:addMesh(builder:build())
    
    --[[self.sprite = cc.Sprite:create('pixel.png')
    self.sprite:setBlendFunc({src = 1, dst = 0})
    self.sprite:setAnchorPoint(0, 0)]]
            
    self.sprite:retain()
end

function PostProcessor:perform(state, outTarget)
    if self.outTarget ~= outTarget then
        self.frameBuffer:setSize(outTarget:getPixelsWide(), outTarget:getPixelsHigh())
        self.frameBuffer:attachRenderTarget(0, outTarget)
        self.outTarget = outTarget
    end
    
    if state.material == nil then
        state.material = cc.Material:createWithGLStateProgram(state)
        --state.material:getStateBlock()
        state.material:retain()
    end
    self.sprite:setMaterial(state.material)
    
    --self.sprite:setGLProgramState(state)
    --self.frameBuffer:clearFBO()
    
    self.camera:render(self.sprite, cc.CameraFlag.DEFAULT, RenderMode.Default, self.frameBuffer)
end