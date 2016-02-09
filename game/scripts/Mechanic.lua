
Mechanic = Derive('Mechanic', Unit)

function Mechanic:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.motionPoints = Points:create(4)
end

function Mechanic:initGfx()
    local model = self:loadModel('dark_templar_knight')
    self.gfx = model
    local scale = 0.00001
    self:setScale(scale, scale * 1.3)
    self:setScaleZ(scale)
    self.gfx:setPosition3D(Vec(0, 0, 0))
end