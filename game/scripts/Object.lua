
local tileWidth = 120

Object = Class('Object', cc.Node)

local globalIndex = 0
local objects = createWeakTable('v')

function Object:init()
    globalIndex = globalIndex + 1
    self.index = globalIndex
    self:setDebugIndex()
    objects[self.index] = self
end

function Object:fromIndex(index)
    return objects[index]
end

function Object:setDebugIndex()
    local index = nil 
    repeat
        index = math.random(0, 65535)
    until not objects[index]
    self.index = index
end

function Object:setCell(cell)
    if self.cell then
        self.cell.object = nil
    end    
    self.cell = cell
    cell.object = self
end

function Object:onHover(state)
end
