
Warrior = Derive('Warrior', Unit)

function Warrior:init()
    Unit.init(self, 'jrpg')
    self.attackCost = 2
    self.attackPower = 40
    self.walkAnimSpeed = 2
    self.motionPoints = Points:create(4)
end
