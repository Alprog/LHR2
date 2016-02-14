
require 'Cell.lua'

Terrain = Derive('Terrain', Object)

function Terrain:init()
    self.floors = {}
    
    self.cells = {}
end

function Terrain:extend(size)
    for i, floor in pairs(self.floors) do
        self:extendFloor(floor, size)
    end
end

function Terrain:extendFloor(floor, size)
    floor.size = floor.size or Vec(0, 0)
    for x = floor.size.x + 1, size.x do
        floor[x] = floor[x] or {}
        for y = floor.size.y + 1, size.y do
            floor[x][y] = floor[x][y] or {}
        end
    end   
    floor.size.x = math.max(floor.size.x, size.x)
    floor.size.y = math.max(floor.size.y, size.y)
end

function Terrain:initDefault()
    local floor = {}
    self:extendFloor(floor, Vec(10, 10))
    self.floors = { floor }
    
    local size = floor.size
    for x = 1, size.x do
        for z = 1, size.y do
            local cell = Cell:create()
            local pos = Vec(x, 0, z)
            
            if z == 8 and x == 2 then pos.y = 0.16 end
            if z == 8 and x == 3 then pos.y = 0.32 end
            if z == 8 and x == 4 then pos.y = 0.48 end
            if z == 8 and x == 5 then pos.y = 0.64 end
                        
            cell:setPosition3D(pos)
            cell.ways = {}
            floor[pos.x][pos.z] = cell
            self:addChild(cell)
            
            table.insert(self.cells, cell)
        end
    end
    
    self:batch()
end

function connectCells(a, b)
    local delta = b:getPosition3D().y - a:getPosition3D().y
    table.insert(a.ways, { cell = b, height = delta } )
    table.insert(b.ways, { cell = a, height = -delta } ) 
end

function Terrain:buildNavGraph()
    local floor = self.floors[1]
    local size = floor.size
    for x = 1, size.x do
        local line = floor[x]
        local nextLine = floor[x + 1]
        for y = 1, size.y - 1 do
            connectCells(line[y], line[y + 1])
        end
        if nextLine then
            for y = 1, size.y do
                connectCells(line[y], nextLine[y])
            end
        end
    end
end

function Terrain:getColorFromIndex(index)
    local r, g, b = indexToBytes(index)
    return cc.c4f(r / 255, g / 255, b / 255, 1) 
end

function Terrain:batch()
    local infos = {}
        
    for cell in iter(self.cells) do
        cell.gfx:setVisible(false)
        
        local info = 
        {
            mesh = cell.gfx:getMeshByIndex(0),
            transform = cell.gfx:getNodeToWorldTransform(),
            texTranslate = Vec(0, 1),
            texScale = Vec(1, -1),
            color = self:getColorFromIndex(cell.index)
        }

        table.insert(infos, info)
    end
    
    local mesh = combineMesh(infos)
    
    local batchGfx = Carcase:create('tiles/ground.png', mesh)
    batchGfx:setForceDepthWrite(true)
    batchGfx:setGlobalZOrder(-6)
    batchGfx:setCullFaceEnabled(false)
    self:addChild(batchGfx)
    
    local material = createMaterial('default', 'vColor')
    local batchMask = Carcase:create(nil, mesh, material)
    batchMask:setCameraMask(MASK_LAYER)
    batchMask:setForceDepthWrite(true)
    batchMask:setGlobalZOrder(-6)
    self:addChild(batchMask)
end


