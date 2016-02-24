
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
    
    local children = self.gfx:getChildren()
    --self.gfx:setTexture(getTexture('models/soldier4.png'))
    self.gfx:setShaders('skin', 'uColor3d')
    self.gfx:setUniformVec4('u_color', Vec(1, 1, 1, 1))
end