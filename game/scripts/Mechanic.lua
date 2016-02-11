
Mechanic = Derive('Mechanic', Unit)

function Mechanic:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.motionPoints = Points:create(4)
end

function Mechanic:initGfx()
    local model = self:loadModel('soldier')
    self.gfx = model
    local scale = 0.0001
    self:setScale(scale)
    
    local children = self.gfx:getChildren()
    self.gfx:setTexture('models/soldier4.png')
    self.gfx:setShaders('skin', 'default')
end