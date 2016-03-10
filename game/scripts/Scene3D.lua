
require 'Object.lua'
require 'PathFinder.lua'
require 'Unit.lua'
require 'TaskManager.lua'
require 'SortedList.lua'
require 'Camera.lua'
require 'Terrain.lua'
require 'CameraTarget.lua'

Scene3D = Derive("Scene3D", cc.Node)

function Scene3D:init()
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
    
    self.lightCamera:setOrthographic(-5, 5, -5, 5, 0, 50)
    self.lightCamera.dirty = false
end

function Scene3D:update(deltaTime)
    self.tasks:update(deltaTime)
    self.camera:update(deltaTime)
    self.target:update(deltaTime)
    
    
    self.lightCamera.angle = (self.lightCamera.angle or 0) + deltaTime / 2
    local a = self.lightCamera.angle
    local dist = 7
    self.lightCamera:setPosition3D(Vec(math.cos(a) * dist + 5, 5, math.sin(a) * dist + 5))
    self.lightCamera:lookAt(Vector(5, 0, 5), Vector(0, 1, 0))
end

function Scene3D:onResize(size)
    theRenderer:onResize(size)
    self:setTransformUpdated()
    self.camera:setWindowAspect() 
end

function Scene3D:render()
    theRenderer:render(self)
end

function Scene3D:checkHover()
    local object = theRenderer:getObjectFromScreenPos(Input.mousePos)
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

function Scene3D:setRenderMode(index)
    for child in iter(self:getChildren()) do
        if child.getMeshCount then
            local count = child:getMeshCount()
            for i = 0, count - 1 do
                child:getMaterial(i):selectTechnique(index) 
            end
        end
        Scene3D.setRenderMode(child, index)
    end
end