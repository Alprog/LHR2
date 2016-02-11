
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
    local scale = 0.01
    self:setScale(scale)
    
    local children = self.gfx:getChildren()
    self.gfx:setTexture('models/soldier4.png')
    self.gfx:setShaders('default3d', 'default')
end