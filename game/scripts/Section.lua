
require 'Block.lua'

Section = Class('Section', cc.Node)

function Section:init(level, x, z)
    self.level = level
    self.x, self.z = x, z
    
    self.floors = {}
    self.floors[1] = Block:create(self, 1)
    
    self:setPosition3D(Vec(x, 0, z))
    level:addChild(self)
end