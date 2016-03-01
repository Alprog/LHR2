
require 'Block.lua'

Section = Class('Section', cc.Node)

function Section:init()
    self.ground = Block:create()
    self:addChild(self.ground)
end