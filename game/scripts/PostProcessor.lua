
require 'QuadMesh.lua'

PostProcessor = NewClass('PostProcessor')

function PostProcessor:init(app)
    self.frameBuffer = ccexp.FrameBuffer:create(1)
    self.frameBuffer:retain()
    
    self.camera = cc.Camera:create()
    self.camera:setOrthographic(0, 1, 0, 1, -1, 1)
    self.camera:setPosition3D(Vec(0, 0, -0.5))
    self.camera:retain()
    
    self.sprite = cc.Sprite3D:create()
    self.sprite:addMesh(getQuadMesh())
    self.sprite:retain()
end

function PostProcessor:perform(material, outTarget)
    if self.outTarget ~= outTarget then
        self.frameBuffer:setSize(outTarget:getPixelsWide(), outTarget:getPixelsHigh())
        self.frameBuffer:attachRenderTarget(0, outTarget)
        self.outTarget = outTarget
    end
    
    self.sprite:setMaterial(material)
    self.camera:render(self.sprite, cc.CameraFlag.DEFAULT, RenderMode.Default, self.frameBuffer)
end