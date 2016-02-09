
BigRobot = Derive('BigRobot', Unit)

function BigRobot:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.motionPoints = Points:create(4)
end

function BigRobot:initGfx()
    local model = self:loadModel('bigrobot')
    self.gfx = model
    self:setScale(0.006)
    self.gfx:setPosition3D(Vec(0, 0, 0))
end