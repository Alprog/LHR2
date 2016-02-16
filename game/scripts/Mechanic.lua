
Mechanic = Derive('Mechanic', Unit)

function Mechanic:init()
    Unit.init(self)
    self.attackCost = 2
    self.attackPower = 40
    self.walkAnimSpeed = 2
    self.motionPoints = Points:create(4)
end

function Mechanic:initGfx()
    local model = self:loadModel('soldier')
    self.gfx = model
    local scale = 1
    self:setScale(scale, 0.9)
    self:setScaleZ(scale)
    
    local children = self.gfx:getChildren()
    --self.gfx:setTexture(getTexture('models/soldier4.png'))
    self.gfx:setShaders('skin', 'default3d')
    self.gfx:setUniformTexture('mainTexture', getTexture('models/soldier4.png'))
end