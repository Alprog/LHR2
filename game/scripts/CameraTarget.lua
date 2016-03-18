
CameraTarget = Class('CameraTarget', cc.Node)

function CameraTarget:update(deltaTime)
    self:inputUpdate(deltaTime)
end

function CameraTarget:inputUpdate(deltaTime)
    local speed = 4
    
    if theControl.buttonBoost:isPressed() then
        speed = speed * 4
    end
    
    local delta = theControl.trackMove:getValue()
    
    local axis = getAxisValue(KEY_Q, KEY_E) + getAxisValue(KEY_LEFT_ARROW, KEY_RIGHT_ARROW)  
    if axis ~= 0 then
        local quat = self:getRotationQuat()
        local angle = axis * math.pi * deltaTime / 16 * speed
        quat = multQuat(yawPitchRoll(angle, 0, 0), quat)
        
        self:setRotationQuat(quat)
    end
    
    if delta.x ~= 0 or delta.y ~= 0 or delta.z ~= 0 then
        local vector = delta * speed * deltaTime
        self:localMove(vector)
    end
    
end

function CameraTarget:localMove(vector)
    local position = self:getPosition3D()
    local rotation = self:getRotationQuat()
    position = position + multVecQuat(vector, rotation)
    self:setPosition3D(position)
end