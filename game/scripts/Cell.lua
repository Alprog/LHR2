
Cell = Derive('Cell', Object)

function Cell:initGfx()
    self.gfx = Carcase:create('tiles/ground.png')
    
    --[[self.gfx = Model:create('tiles/ground.c3b')
    self.gfx:setScale(0.01)
    self.gfx:setPosition3D(Vec(0, 0, 0))]]
    
    self.gfx:setGlobalZOrder(-6)
    self.gfx:setForceDepthWrite(true)
    
    local selection = Carcase:create('tiles/select.png')
    selection:setVisible(false)
    selection:setPosition3D(Vec(0, 0.05, 0))
    self.selection = selection
    
    self:addChild(self.gfx)
    self:addChild(self.selection)
end