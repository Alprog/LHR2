
Level = Class('Level', cc.Node)

function Level:init()
    self.sections = {{}}
    self:extend(cc.size(10, 10))
    self:initGfx()
    
    self:scheduleUpdate()
    self.dirtyBlocks = {}
end

function Level:extend(size)
    while #self.sections < size.width do
        table.insert(self.sections, {})
    end
    
    for x = 1, #self.sections do
        local line = self.sections[x]
        for z = #line + 1, size.height do
            line[z] = Section:create(self, x, z)
        end
    end
end

function Level:getSection(x, z)
    local line = self.sections[x]
    if line then
        return line[z]
    end
end

function Level:getBlock(x, z, floor)
    local section = self:getSection(x, z)
    if section then
        return section.floors[floor]
    end
end

function Level:onReliefChange(block)
    table.insert(self.dirtyBlocks, block)
    for _, neighbor in pairs(block:getNeighbors()) do
        table.insert(self.dirtyBlocks, neighbor)
    end
end

function Level:getNeighbors(x, z, floor)
    local neighbors = {}
    neighbors[1] = self:getBlock(x, z + 1, floor) -- bottom
    neighbors[2] = self:getBlock(x + 1, z, floor) -- right
    neighbors[3] = self:getBlock(x, z - 1, floor) -- top
    neighbors[4] = self:getBlock(x - 1, z, floor) -- left
    return neighbors
end

function Level:initGfx()
    for line in iter(self.sections) do
        for section in iter(line) do
            for block in iter(section.floors) do
                block:initGfx()
            end
        end
    end
end

function Level:update()
    if #self.dirtyBlocks then
        for block in iter(self.dirtyBlocks) do
            block:recreateGfx()
        end
        self.dirtyBlocks = {}
    end
end