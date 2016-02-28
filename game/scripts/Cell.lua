
Cell = Derive('Cell', Object)

function Cell:init()
    Object.init(self)
    
    self.gfx = Carcase:create('tiles/ground.png')
    
    local selection = Carcase:create('tiles/select.png')
    selection:setVisible(false)
    selection:setPosition3D(Vec(0, 0.05, 0))
    selection:setForceDepthWrite(true)
    self.selection = selection
    
    self:addChild(self.gfx)
    self:addChild(self.selection)
end