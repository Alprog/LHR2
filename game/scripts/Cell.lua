
Cell = Derive('Cell', Object)

function Cell:initGfx()
    self.gfx = Carcase:create('tiles/ground.png')
    
    self.gfx:setForceDepthWrite(true)
    
    local selection = Carcase:create('tiles/select.png')
    selection:setVisible(false)
    selection:setPosition3D(Vec(0, 0.05, 0))
    selection:setForceDepthWrite(true)
    self.selection = selection
    
    self:addChild(self.gfx)
    self:addChild(self.selection)
end