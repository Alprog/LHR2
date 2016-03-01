
Level = Class('Level', cc.Node)

function Level:init()
    self.sections = {{}}
    self:extend(cc.size(10, 10))
end

function Level:extend(size)
    while #self.sections < size.width do
        table.insert(self.sections, {})
    end
    
    for x = 1, #self.sections do
        local line = self.sections[x]
        for z = #line + 1, size.height do
            local section = Section:create()
            line[z] = section
            section:setPosition3D(Vec(x, 0, z))
            self:addChild(section)
        end
    end
end