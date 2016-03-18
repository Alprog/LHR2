
Camera = Class('Camera', cc.Camera)

function Camera:instantinate()
    return Camera.__create()
end

function Camera:init(space)
    space:addChild(self)
    self.aspect = 1
    self.perspective = 10
    self.offset = Vec(0, 0)
    self.dirty = true
end
   
function Camera:update(deltaTime)
    if self.free then
        self:freeMoveUpdate(deltaTime)
        self:freeRotationUpdate(deltaTime)
    else
        self:followUpdate(deltaTime)
    end
end

function Camera:freeMoveUpdate(deltaTime)
    local speed = 10
    if theControl.buttonBoost:isPressed() then
        speed = speed * 2
    end
        
    local delta = theControl.trackMove:getValue()
    
    if delta.x ~= 0 or delta.y ~= 0 or delta.z ~= 0 then
        local vector = delta * speed * deltaTime
        self:localMove(vector)
    end
end

function Camera:freeRotationUpdate(deltaTime)
    local yaw = 0
    local pitch = 0
    local roll = 0
    
    local k = math.pi * deltaTime / 4
    if theControl.buttonBoost:isPressed() then
        k = k * 4
    end
    
    local rotate = theControl.trackRotate:getValue()
    
    yaw = yaw + k * rotate.x
    pitch = pitch + k * rotate.y
    roll = roll + k * rotate.z
        
    if yaw ~= 0 or pitch ~= 0 or roll ~= 0 then
        local rotation = self:getRotationQuat()
        local quat = yawPitchRoll(yaw, pitch, roll)
        rotation = multQuat(rotation, quat)
        self:setRotationQuat(rotation)
    end
end

function Camera:localMove(vector)
    local position = self:getPosition3D()
    local rotation = self:getRotationQuat()
    position = position + multVecQuat(vector, rotation)
    self:setPosition3D(position)
end

function Camera:lookAt(lookAtPos, up)
    lookAtPos = Vector(lookAtPos.x, lookAtPos.y, lookAtPos.z)
    
    local pos = self:getPosition3D() 
    
    local upv = up
    upv:normalize()
    local zaxis = Vector(pos.x, pos.y, pos.z) - lookAtPos
    zaxis:normalize()
    local xaxis = Vector.cross(upv, zaxis)
    xaxis:normalize()
    local yaxis = Vector.cross(zaxis, xaxis)
    yaxis:normalize()
    
    local rotation = nil
    local trace = xaxis.x + yaxis.y + zaxis.z + 1.0
    if trace > 0.000001 then
        local s = 0.5 / math.sqrt(trace)
        rotation = cc.quaternion(
            (yaxis.z - zaxis.y) * s,
            (zaxis.x - xaxis.z) * s,
            (xaxis.y - yaxis.x) * s,
            0.25 / s
        )
    else
        if xaxis.x > yaxis.y and xaxis.x > zaxis.z then
            local s = 0.5 / math.sqrt(1.0 + xaxis.x - yaxis.y - zaxis.z)
            rotation = cc.quaternion(
                0.25 / s,
                (yaxis.x + xaxis.y) * s,
                (zaxis.x + xaxis.z) * s,
                (yaxis.z - zaxis.y) * s
            )
        elseif yaxis.y > zaxis.z then
            local s = 0.5 / math.sqrt(1.0 + yaxis.y - xaxis.x - zaxis.z)
            rotation = cc.quaternion(
                (yaxis.x + xaxis.y) * s,
                0.25 / s,
                (zaxis.y + yaxis.z) * s,
                (zaxis.x - xaxis.z) * s
            )
        else
            local s = 0.5 / math.sqrt(1.0 + zaxis.z - xaxis.x - yaxis.y)
            rotation = cc.quaternion(
                (zaxis.x + xaxis.z ) * s,
                (zaxis.y + yaxis.z ) * s,
                0.25 / s,
                (xaxis.y - yaxis.x ) * s
            )
        end
    end
        
    self:setRotationQuat(rotation)
end

function Camera:followUpdate(deltaTime)
    local options = self.followOptions
    local speed = theControl.buttonBoost:isPressed() and 4 or 1
    
    local y = theControl.trackRotate:getValue().y
    if y ~= 0 then
        local delta = y * math.pi / 4 * deltaTime * speed
        options.angle = clamp(options.angle + delta, 0, math.pi / 2)
        self:refreshFollowPosition()
    end
    
    axis = getAxisValue(KEY_KP_MINUS, KEY_KP_PLUS)
    if axis ~= 0 then
        local delta = axis * 25 * deltaTime * speed
        options.far = clamp(options.far + delta, 10, 100)
        self:refreshFollowPosition()
    end
    
end

function Camera:setWindowAspect()
    local size = theApp.windowSize
    local aspect = size.width / size.height
    self:setAspect(aspect)
end

function Camera:setAspect(aspect)
    self.aspect = aspect
    self.dirty = true
end

function Camera:setOffset(offset)
    self.offset = offset
    self.dirty = true
end

function Camera:refreshView()
    cc.Camera.setPerspective(self, self.perspective, self.aspect, 10, 1000, self.offset)
end

function Camera:follow(target, far, angle)
    self:removeFromParent()
    target:addChild(self)
    
    self.followOptions =
    {
        target = target,
        far = far,
        angle = angle
    }
    
    self:refreshFollowPosition()
end

function Camera:refreshFollowPosition()
    local far, angle = self.followOptions.far, self.followOptions.angle
    local s = math.sin(angle)
    local dz = math.cos(angle) * far
    local dy = math.sin(angle) * far
    self:setPosition3D(Vec(0, dy, dz))
    self:lookAt(Vector(0, 0, 0), Vector(0, 1, 0))
end

function Camera:render(scene, flag, renderMode, frameBuffer)
    flag = flag or cc.CameraFlag.DEFAULT
    renderMode = renderMode or 0
    
    if self.dirty then
        self:refreshView()
        self.dirty = false
    end
    
    cc.Camera.render(self, scene, flag, renderMode, frameBuffer)
end