
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

function PostProcessor:perform()
    self.camera:render(self.sprite, cc.CameraFlag.DEFAULT, self.frameBuffer)
end