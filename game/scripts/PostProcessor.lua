
PostProcessor = NewClass('PostProcessor')

function PostProcessor:init(app)
    self.frameBuffer = ccexp.FrameBuffer:create(1)
    self.frameBuffer:retain()
    
    self.camera = cc.Camera:create()
    self.camera:setOrthographic(0, 1, 0, 1, -1, 1)
    self.camera:retain()
    
    self.sprite = cc.Sprite:create('pixel.png')
    self.sprite:setAnchorPoint(0, 0)    
    self.sprite:retain()
end

function PostProcessor:perform(state, outTarget)
    if self.outTarget ~= outTarget then
        self.frameBuffer:setSize(outTarget:getPixelsWide(), outTarget:getPixelsHigh())
        self.frameBuffer:attachRenderTarget(0, outTarget)
        self.outTarget = outTarget
    end
    
    self.sprite:setGLProgramState(state)
    self.camera:render(self.sprite, cc.CameraFlag.DEFAULT, RenderMode.Default, self.frameBuffer)
end