
Marine = Derive('Marine', Unit)

function Marine:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.motionPoints = Points:create(4)
end

function Marine:initGfx()
    local model = self:loadModel('marine')
    self.gfx = model
    self:setScale(0.007)
    self.gfx:setPosition3D(Vec(0, 0, 0))
end