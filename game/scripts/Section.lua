
require 'Block.lua'

Section = Class('Section', cc.Node)
Section.serializableFields = { 'floors' }

function Section:init(level, x, z)
    self.level = level
    self.x, self.z = x, z
    
    self.floors = {}
    self.floors[1] = Block:create(self, 1)
    
    self:setPosition3D(Vec(x, 0, z))
    level:addChild(self)
end

function Section:onDeserialize()
    for i, block in ipairs(self.floors) do
        block.section = section
        block.floor = i
        self:addChild(block)
    end
end

function Section:getLevel()
    return self:getParent()
end
