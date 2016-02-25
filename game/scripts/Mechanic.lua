
Mechanic = Derive('Mechanic', Unit)

function Mechanic:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.walkAnimSpeed = 2
    self.motionPoints = Points:create(4)
end

function Mechanic:initGfx()
    local model = self:loadModel('jrpg')
    self.gfx = model
    self:setScale(0.01)     
end