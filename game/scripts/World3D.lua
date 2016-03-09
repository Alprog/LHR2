
require 'Renderer.lua'

World3D = Derive("World3D", cc.Node)

function World3D:init()
    self.renderer = Renderer:create()
end

function World3D:render()
    self.renderer:render(self)
end

function World3D:onResize(size)
    self.renderer:onResize(size)
    self:setTransformUpdated()
    self.camera:setWindowAspect()
end