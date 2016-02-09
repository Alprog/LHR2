
Renegade = Derive('Renegade', Unit)

function Renegade:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.motionPoints = Points:create(4)
end

function Renegade:initGfx()
    local model = self:loadModel('renegade')
    self.gfx = model
    self:setScale(0.006)
    self.gfx:setPosition3D(Vec(0, 0, 0))
end