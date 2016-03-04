
require 'Block.lua'

Section = Class('Section', cc.Node)
Section.serializeFields = { 'floors', 'x' }

function Section:init(level, x, z)
    self.level = level
    self.x, self.z = x, z
    
    self.data = {}
    self.data.a = 3
    print('a:', self.a)
    
    self.floors = {}
    self.floors[1] = Block:create(self, 1)
    
    self:setPosition3D(Vec(x, 0, z))
    level:addChild(self)
end