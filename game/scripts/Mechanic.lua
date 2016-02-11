
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
    local scale = 0.005
    self:setScale(scale)
    self.gfx:setPosition3D(Vec(0, 0, 0))

    local children = self.gfx:getChildren()
    for i = 1, #children do
        local child = children[i]
        if child.setTexture then
            child:setTexture('models/soldier.png')
            child:setForceDepthWrite(true)
        end
        --print(i, child.setSkeleton)
        child:setVisible(false)
    end
    children[12]:setVisible(true)
    
end