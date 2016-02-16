
require 'Object.lua'
require 'PathFinder.lua'
require 'Unit.lua'
require 'TaskManager.lua'
require 'SortedList.lua'
require 'Camera.lua'
require 'Terrain.lua'

Arena = Derive("Arena", cc.Node)

function Arena:init()
    self.unitLayer = self:createChild()
    self.lightNode = self:createChild()
    
    self:listenTouches()
    self:scheduleUpdate()
    
    self.tasks = TaskManager:create()
    self:initCamera()
    
    self.frameBuffer = FrameBuffer:create(1, true, 4)
    self.maskFrameBuffer = FrameBuffer:create(1, false, 0, 4)
    
    --self:getDefaultCamera():setVisible(false)
end

function Arena:initCamera()
    self.camera = Camera:create(self)   
    
    local far = 50 
    local angle = 30 * math.pi / 180
    local s = math.sin(angle)
    local height = math.sin(angle) * far
    local distance = math.cos(angle) * far
    local delta = math.sqrt(distance * distance / 2)
    self.camera:setPosition(Vec(-delta + 5, height, delta + 5))
        
    self.camera:lookAt(Vector(5, 0, 5), Vector(0, 1, 0))
end

function Arena:update(deltaTime)
    self.tasks:update(deltaTime)
    self.camera:update(deltaTime)
    
    self:renderMask()
    self:checkHover()
    self:sortUnits()
end

function Arena:renderMask()
    local pos = Input.mousePos
    local k = self.maskFrameBuffer.downScale
    local rect = cc.rect(pos.x / k - 1, pos.y / k - 1, 3, 3)
    
    --self.camera:setScissors(rect)
    self.camera:render(self, MASK_LAYER, self.lightNode, self.maskFrameBuffer)
end

function Arena:checkHover()
    local object = self:getObjectFromScreenPos(Input.mousePos)
    if self.hoverObject ~= object then
        if self.hoverObject then
            self.hoverObject:onHover(false) 
        end
        self.hoverObject = object
        if self.hoverObject then
            self.hoverObject:onHover(true)
        end
    end   
end

function Arena:getObjectFromScreenPos(pos)
    local texel = self.maskFrameBuffer:getTexel(pos.x, pos.y)
    local index = bytesToIndex(texel.x, texel.y, texel.z)
    return Object:fromIndex(index) 
end

function Arena:sortUnits()
    local units = self.unitLayer:getChildren()
    for unit in iter(units) do
        local order = unit.silhouette:isVisible() and 3 or 1
        unit.model:setGlobalZOrder(order)
        unit.silhouette:setGlobalZOrder(order)
    end
end

function Arena:onResize(size)
    self:setTransformUpdated()
    self.frameBuffer:resize(size)
    self.maskFrameBuffer:resize(size)
    self.camera.dirty = true
end

function Arena:addObject(object)
    object.arena = self
    self:addChild(object)
end

function Arena:onTouchEnded(touch, event)
    if touch.dragging then
       return 
    end
    
    local pos = touch:getLocation()    
    local object = self:getObjectFromScreenPos(pos)
    
    if object then
        if object.isUnit then
            self.battle:selectPlayer(object)
            self.battle.scene:updateUI()
        else
            self.battle:onCellClick(object)
        end    
    end
    
    pos = self:convertToNodeSpace(pos)
    self:onClick(pos)
end

function Arena:onClick(pos)    
    --print(pos)
end

function Arena:createTerrain()
    self.terrain = Terrain:create()
    self.terrain:initDefault()
    self.terrain:buildNavGraph()
    self:addChild(self.terrain)
end

function Arena:getRandomCell()
    return table.randomItem(self.terrain.cells)
end

function Arena:getRandomFreeCell()
    while true do
        local cell = self:getRandomCell()
        if not cell.object then
            return cell
        end
    end
end

function Arena:spawn(unit)
    local cell = self:getRandomFreeCell()
    unit:teleportToCell(cell)
    
    local angles = { 0, 90, 180, 270 }
    local angle = angles[math.random(#angles)]
    unit:setRotation(angle * math.pi / 180)
    
    unit.arena = self
    self.unitLayer:addChild(unit)
end

function Arena:destroy()
    local children = self:getChildren()
    for i = 1, #children do
        local child = children[i]
        if child.destroy then
            child:destroy()
        end
    end
    if self.maskFrameBuffer then
        self.maskFrameBuffer:destroy()
        self.maskFrameBuffer = nil
    end
end

function Arena:addObstacles()
    local map = {
        {2, 0, 0, 1, 6, 5, 4, 6, 5, 6 },
        {2, 0, 0, 0, 6, 4, 0, 0, 0, 6 },
        {4, 0, 0, 0, 5, 0, 0, 0, 0, 4 },
        {2, 0, 0, 0, 2, 0, 0, 0, 0, 6 },        
        {2, 0, 0, 0, 8, 0, 0, 0, 0, 4 },
        {2, 0, 0, 0, 2, 0, 0, 0, 4, 6 },
        {2, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
        {5, 3, 3, 3, 4, 3, 7, 3, 3, 5 },
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 9 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    }
    
    local floorMap = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0,11,11,10, 0 },
        {0, 0, 0, 0, 0, 0,12,11, 0, 0 },
        {0, 0, 0, 0, 0,11,11,11, 0, 0 },        
        {0, 0, 0, 0, 0,11,12,11, 0, 0 },
        {0, 0, 0, 0, 0,11,11,11, 0, 0 },
        {0, 0, 0, 0, 0,11,12,11, 0, 0 },
        {0, 0, 0, 0, 0,11,11,11, 0, 0 },
        {0, 0, 0, 0, 0,11,12,11,11,11 },
        {0, 0, 0, 0, 0,11,11,11,11,11 }
    }
    
    local pathes =
    {
        'models/obstacles/barrel01.c3b',
        'models/obstacles/wall_thin01_R.c3b',
        'models/obstacles/wall_thin01_L.c3b',
        'models/obstacles/wall_cube01.c3b',
        'models/obstacles/wall_blockWall.c3b',
        'models/obstacles/wall_blockSimple.c3b',
        'models/obstacles/door01_L.c3b',
        'models/obstacles/door01_R.c3b',
        'models/obstacles/chest_brown.c3b',
        'models/obstacles/chest_green.c3b',
        'models/obstacles/ground_stone.c3b',
        'models/obstacles/ground_grate.c3b',
    }
    
    
    for cell in iter(self.terrain.cells) do
        local pos = cell:getPosition3D()
        for j = 1, 2 do
            local arr = j == 1 and map or floorMap
            local index = arr[pos.z][pos.x]
            local path = pathes[index]
            if path then
                local obstacle = Model:create(path)
                obstacle:setScale(0.01)
                obstacle:setPosition3D(Vec(0, 0, 0))
                obstacle:setGlobalZOrder(-6)
                obstacle:setForceDepthWrite(true)
                if index == 7 or index == 8 then
                   --obstacle:play('Take 001', true, 0.4)
                   obstacle:setRotation3D(Vec(0, 0, 0))
                end
                if j ~= 2 then
                    cell.object = obstacle
                    obstacle.cell = cell
                else
                    local pos = obstacle:getPosition3D()
                    pos.y = pos.y + 0.002
                    obstacle:setPosition3D(pos)
                end
                cell:addChild(obstacle)
            end
        end
    end
end

function Arena:render()
    self.camera:render(self, cc.CameraFlag.DEFAULT, nil, self.frameBuffer) 
end
