
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
    
    self:scheduleUpdate()
    
    self.tasks = TaskManager:create()
    self:initCamera()   
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
