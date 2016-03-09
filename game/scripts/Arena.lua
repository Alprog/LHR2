
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
    
    self:listenTouches()
    self:scheduleUpdate()
    
    self.tasks = TaskManager:create()
    self:initCamera()
        
    self.hoverEnabled = true
    
    WithoutDebug(function()
        self:createTerrain()
    end)
    self:update(0)

end

function Arena:initCamera()
    self.camera = Camera:create(self)   
    self.camera:setWindowAspect()
    
    local far = 50
    local angle = 30 * math.pi / 180
    local s = math.sin(angle)
    local height = math.sin(angle) * far
    local distance = math.cos(angle) * far
    local delta = math.sqrt(distance * distance / 2)
    self.camera:setPosition(Vec(-delta + 5, height, delta + 5))
        
    self.camera:lookAt(Vector(5, 0, 5), Vector(0, 1, 0))
    
    self.lightCamera = Camera:create(self)
    self.lightCamera:setPosition(Vec(-20, 50, 70))
    self.lightCamera:lookAt(Vector(5, 0, 5), Vector(0, 1, 0))
end

function Arena:update(deltaTime)
    self.tasks:update(deltaTime)
    self.camera:update(deltaTime)
    
    if self.hoverEnabled then
        self:checkHover()
    end
    
    --[[local pos = self.terrain:getPosition3D()
    pos.x = pos.x - deltaTime * 1
    self.terrain:setPosition3D(pos)]]
end

function Arena:setTechnique(index)
    local units = self.unitLayer:getChildren() 
    for unit in iter(units) do
        unit:selectTechnique(index)
    end
end

function Arena:checkHover()
    local object = self:getObjectFromScreenPos(Input.mousePos)
    if self.hoveredObject ~= object then
        if self.hoveredObject then
            self.hoveredObject:onHover(false) 
        end
        self.hoveredObject = object
        if self.hoveredObject then
            self.hoveredObject:onHover(true)
        end
    end   
end

function Arena:onTouchEnded(touch, event)

    local pos = touch:getLocation()    
    
    if self.hoveredObject then
        if self.hoveredObject.isUnit then
            self.battle:selectPlayer(self.hoveredObject)
            self.battle.scene:updateUI()
        else
            self.battle:onCellClick(self.hoveredObject)
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