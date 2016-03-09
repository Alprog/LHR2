
require 'Object.lua'
require 'PathFinder.lua'
require 'Unit.lua'
require 'TaskManager.lua'
require 'SortedList.lua'
require 'Camera.lua'
require 'Terrain.lua'
require 'World3D.lua'
require 'CameraTarget.lua'

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
    
    self.target = CameraTarget:create()
    self.target:setPosition3D(Vec(5, 1, 5))
    self.target:setRotation3D(Vec(0, -45, 0))
    self:addChild(self.target)
    
    self.camera:follow(self.target, 50, 30 * deg2rad)
    
    self.lightCamera = Camera:create(self)
    self.lightCamera:setPosition(Vec(-20, 50, 70))
    self.lightCamera:lookAt(Vector(5, 0, 5), Vector(0, 1, 0))
end

function Scene3D:update(deltaTime)
    self.tasks:update(deltaTime)
    self.camera:update(deltaTime)
    self.target:update(deltaTime)
    
    --[[local p = self.lightCamera.position
    p.x = p.x + deltaTime * 40
    self.lightCamera:setPosition(p)
    self.lightCamera:lookAt(Vector(5, 0, 5), Vector(0, 1, 0))]]
end

function Scene3D:checkHover()
    local object = self.renderer:getObjectFromScreenPos(Input.mousePos)
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

function Scene3D:clearHovered()
    self.hoveredObject = nil
end