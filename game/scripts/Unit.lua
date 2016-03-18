
require 'Object.lua'
require 'Model.lua'
require 'Points.lua'

Unit = Derive('Unit', Object)

local walkTime = 0.33
local jumpTime = 0.5
local rotationSpeed = math.pi * 2.5

function Unit:init(modelName)
    self.base.init(self)
    self:loadModel(modelName)
    self.healthPoints = Points:create(100)
    self.motionPoints = Points:create(3)
    self.actionPoints = Points:create(2)
    self:setScale(0.01)
    self.isUnit = true
end

function Unit:loadModel(name)
    self.name = name
    self.portraitName = name
    
    local fileName = 'models/'.. name .. '.c3b'
        
    local model = Model:create(fileName)
    self:addChild(model)
   
      
    local material = cc.Material:create()
    
    -- default
    local state = createState('skin', 'defaultMRT')
    state:setUniformTexture('mainTexture', getTexture('models/diffuse.png'))
    state:setUniformVec2('u_id', self:getUniformId())
    local technique = cc.Technique:createWithGLProgramState(state)
    material:setTechnique(RenderMode.Default, technique)
    
    -- silhouette
    state = createState('fatskin', 'uColorMRT')
    state:setUniformVec4('u_color', Vec(1, 0, 1, 1))
    technique = cc.Technique:createWithGLProgramState(state)
    material:setTechnique(2, technique)
    
    model:setMaterial(material)
    
    local stateBlock = material:getStateBlock()
    
    
    ------------------------------------------
    
    model:play('idle', true)
    self.model = model
    
    return model
end

function Unit:setHighlight(color)
    --[[if color == nil then
        self.silhouette:setVisible(false)
    else
        self.silhouette:setVisible(true)
        self.silhouette:setUniformVec4('u_color', color)
    end]]
end

function Unit:setRotation(rotation)
    self.rotation = rotation
    local quat = yawPitchRoll(rotation, 0, 0)
    self:setRotationQuat(quat)
end

function Unit:checkRotation(rotation)
    if not cmpAngle(self.rotation, rotation) then
        self:stop()
        self:rotateTo(rotation)
        wait(0.05)
    end
end

function Unit:rotateTo(rotation, time, speed)
    local min = self.rotation - math.pi
    local max = self.rotation + math.pi
    rotation = repeatf(rotation, min, max)
    
    local startRotation = self.rotation
    time = time or math.abs(startRotation - rotation) / (speed or rotationSpeed)
    
    local t = 0
    while t < time do
        t = t + deltaTime
        if t > time then
           deltaTime = t - time
           break
        end
        local k = t / time
        local curRotation = startRotation * (1 - k) + rotation * k        
        self:setRotation(curRotation)
        coroutine.yield()
    end
        
    self:setRotation(rotation)
end

function Unit:rotateToCell(cell, time, speed)
    local angle = self:getAngle(self:getPosition3D(), cell:getPosition3D())
    self:rotateTo(angle, time, speed)
end

function Unit:teleportToCell(cell)
    self:setCell(cell)
    local pos = cell:getPosition3D()
    self:setPosition3D(pos)
end

function Unit:parabolaJump(pos, fullTime)
    local startPos = self:getPosition3D()
    local time = 0
    
    local g = 9.8
    local v = (pos.y - startPos.y) / fullTime -- speed without gravity
    v = v + g * fullTime -- compensate free fall
        
    while time < fullTime do
        time = time + deltaTime
        if time >= fullTime then
            deltaTime = time - fullTime
            break
        end
        local curPos = vecLerp(startPos, pos, time / fullTime)
        curPos.y = startPos.y + v * time - g * time * time
        self:setPosition3D(curPos)
        coroutine.yield()
    end
    self:setPosition3D(pos)
end

function Unit:linearMove(pos, fullTime)
    local startPos = self:getPosition3D()
    local time = 0
    while time < fullTime do
        time = time + deltaTime
        if time >= fullTime then
            deltaTime = time - fullTime
            break
        end
        local curPos = vecLerp(startPos, pos, time / fullTime)
        self:setPosition3D(curPos)
        coroutine.yield()
    end
    self:setPosition3D(pos)
end

function Unit:walkTo(cell)
    local pos = cell:getPosition3D()
    self.model:playLoop('run', self.walkAnimSpeed or 1)
    self:linearMove(pos, walkTime)    
    self:setCell(cell)
end

function Unit:jumpTo(cell)
    local pos = cell:getPosition3D()
    self.model:play('jump')
    
    self.arena.tasks:run(function()
        self:parabolaJump(pos, jumpTime)
    end)
    coroutine.yield()
    
    wait(jumpTime - self.model:getFadeTime('jump'))
    self.model:play('idle', true)
        
    self:setCell(cell)
    wait(0.2)
end

function Unit:stop()
    self.model:playLoop('idle')
end

function Unit:getAngle(srcPos, dstPos)
    local x = dstPos.x - srcPos.x
    local z = dstPos.z - srcPos.z
    return math.atan2(x, z)
end

function Unit:RotateAtWalkTask(move, nextMove)
    self.arena.tasks:run(function()
        self:rotateTo(move.angle, walkTime / 2)
        if nextMove then
            local angle = averageAngle(move.angle, nextMove.angle)
            self:rotateTo(angle, walkTime / 2)
        end
    end)
end

function Unit:followPath(path)    
    local moves = {}
    
    for i = 1, #path - 1 do
        local move = {}
        move.srcCell = path[i]
        move.dstCell = path[i + 1]
        
        local srcPos = move.srcCell:getPosition3D()
        local dstPos = move.dstCell:getPosition3D()
        move.angle = self:getAngle(srcPos, dstPos)
        
        local delta = dstPos.y - srcPos.y
        move.type = math.abs(delta) > 0.2 and 'jump' or 'walk'
        table.insert(moves, move)
    end
    
    self:checkRotation(moves[1].angle)
    for i = 1, #moves do
        local move = moves[i]
        local nextMove = moves[i + 1]
        
        if move.type == 'walk' then
            self:RotateAtWalkTask(move, nextMove)
            self:walkTo(move.dstCell)
        else
            self:checkRotation(move.angle)
            self:jumpTo(move.dstCell)
            if nextMove then
                self:checkRotation(nextMove.angle)
            end
        end
    end
    self:stop()
end

function Unit:followPathTask(path)
    self.arena.tasks:stopAll()
    self.arena.tasks:run(function()
        self:followPath(path)
    end) 
end

function Unit:attack(enemy)
    self:rotateToCell(enemy.cell)
    self.model:play('attack')
    self.model:waitAnimation()
    self.model:playLoop('idle')
end

function Unit:setSelection(value)
    self.selected = value
    self:setHighlight(value and Vec(1, 1, 0, 1) or nil)
end

function Unit:restoreRoundPoints()
    self.motionPoints:restore()
    self.actionPoints:restore()
end

function Unit:canAttack()
    return self.actionPoints.cur >= (self.attackCost or 1)
end

function Unit:damage(value)
    self.healthPoints:decrease(value)
    if self.healthPoints:empty() then
        self:die()
    end
end

function Unit:die()
    self.dead = true
    self.cell.object = nil
    self.cell = nil
    
    self.arena.tasks:run(function()
        self.model:play('die')
        self.model:waitAnimation()
        self:killGfx()
    end)
end

function Unit:onHover(value)
    
    local color = nil
    
    if self.selected then
        color = value and Vec(1, 1, 0, 1) or Vec(0.8, 0.8, 0, 1)
    else
        if value then
            color = Vec(1, 1, 1, 1)
        end
    end
    
    self:setHighlight(color)    
end