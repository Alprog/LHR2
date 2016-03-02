
require 'Object.lua'
require 'PathFinder.lua'
require 'Unit.lua'
require 'TaskManager.lua'
require 'SortedList.lua'
require 'Camera.lua'
require 'Terrain.lua'
require 'World3D.lua'

Scene3D = Derive("Scene3D", World3D)

function Scene3D:init()
    World3D.init(self)
    
    self.unitLayer = self:createChild()
    
    self:listenTouches()
    self:listenMouse()
    self:scheduleUpdate()
    
    self.tasks = TaskManager:create()
    self:initCamera()
        
    self.hoverEnabled = true

    self.level = Level:create()
    self:addChild(self.level)
    self:update(0)
    
end

function Scene3D:initCamera()
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

function Scene3D:update(deltaTime)
    self.tasks:update(deltaTime)
    self.camera:update(deltaTime)  
end
 
function Scene3D:setTechnique(index)
    local units = self.unitLayer:getChildren() 
    for unit in iter(units) do
        unit:selectTechnique(index)
    end
end

function Scene3D:checkHover()
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

function Scene3D:onMouseDown(event)
    print('down')
end

function Scene3D:onTouchEnded(touch, event)
   
    if self.hoveredObject then
        local object = self.hoveredObject
        
        print('id', touch:getButtonId())
        
        if object.className == 'Block' then
            local value = 0.25 * (touch:getButtonId() == 0 and 1 or -1)
            object:move(value)
        end
        
    end
    
    local pos = touch:getLocation()    
    pos = self:convertToNodeSpace(pos)
    self:onClick(pos)
end

function Scene3D:onClick(pos)    
    --print(pos)
end

function Scene3D:createTerrain()
    self.terrain = Terrain:create()
    self.terrain:initDefault()
    self.terrain:buildNavGraph()
    self:addChild(self.terrain)
end

function Scene3D:getRandomCell()
    return table.randomItem(self.terrain.cells)
end

function Scene3D:getRandomFreeCell()
    while true do
        local cell = self:getRandomCell()
        if not cell.object then
            return cell
        end
    end
end

function Scene3D:spawn(unit)
    local cell = self:getRandomFreeCell()
    unit:teleportToCell(cell)
    
    local angles = { 0, 90, 180, 270 }
    local angle = angles[math.random(#angles)]
    unit:setRotation(angle * math.pi / 180)
    
    unit.arena = self
    self.unitLayer:addChild(unit)
end