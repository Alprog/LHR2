
Camera = Class('Camera')

function Camera:init(space)
    self.space = space
    self.position = Vector(0, 0, 0)
    self.rotation = cc.quaternion(0, 0, 0, 1)
    self.perspective = 0
    self:setPassCount(1)
end

function Camera:setPassCount(count)
    self.passes = self.passes or {}
    
    for i = #self.passes + 1, count do
        local pass = cc.Camera:create()
        self.space:addChild(pass)
        self.passes[i] = pass
    end
    
    for i = #self.passes, count + 1, -1 do
        local pass = self.passes[i]
        pass:setScene(nil)
        pass:setFrameBufferObject(nil)
        pass:removeFromParent()
        self.passes[i] = nil
    end
    
    self.dirty = true
end
    
function Camera:setPassSettings(index, enabled, depth, mask, frameBuffer, scissorsRect)
    local pass = self.passes[index]
    pass:setVisible(enabled)
    pass.frameBuffer = frameBuffer
    if scissorsRect then
        pass:setScissors(scissorsRect)
    end
    self.dirty = true
end

function Camera:update(deltaTime)
    self:inputUpdate(deltaTime)
    
    if self.dirty then
        self:refreshView()
        self.dirty = false
    end
end

function Camera:inputUpdate(deltaTime)
    self:moveUpdate(deltaTime)
    self:rotationUpdate(deltaTime)
end

function Camera:moveUpdate(deltaTime)
    local speed = 10
    if Input.keys[cc.KeyCode.KEY_SHIFT] then
        speed = speed * 2
    end
        
    local delta = Vector(0, 0, 0)
    if Input.keys[cc.KeyCode.KEY_A] then
        delta = delta + Vector(-1, 0, 0)
    end
    if Input.keys[cc.KeyCode.KEY_D] then
        delta = delta + Vector(1, 0, 0)
    end
    if Input.keys[cc.KeyCode.KEY_R] then
        delta = delta + Vector(0, 1, 0)
    end
    if Input.keys[cc.KeyCode.KEY_F] then
        delta = delta + Vector(0, -1, 0)
    end
    if Input.keys[cc.KeyCode.KEY_W] then
        delta = delta + Vector(0, 0, -1)
    end
    if Input.keys[cc.KeyCode.KEY_S] then
        delta = delta + Vector(0, 0, 1)
    end
    
    if delta.x ~= 0 or delta.y ~= 0 or delta.z ~= 0 then
        local vector = delta * speed * deltaTime
        self:localMove(vector)
    end
end

function Camera:rotationUpdate(deltaTime)
    local yaw = 0
    local pitch = 0
    local roll = 0
    
    local k = math.pi * deltaTime / 4
    
    if Input.keys[cc.KeyCode.KEY_LEFT_ARROW] then
        yaw = yaw + k
    end
    if Input.keys[cc.KeyCode.KEY_RIGHT_ARROW] then
        yaw = yaw - k
    end
    if Input.keys[cc.KeyCode.KEY_UP_ARROW] then
        pitch = pitch + k
    end
    if Input.keys[cc.KeyCode.KEY_DOWN_ARROW] then
        pitch = pitch - k
    end
    if Input.keys[cc.KeyCode.KEY_Q] then
        roll = roll + k
    end
    if Input.keys[cc.KeyCode.KEY_E] then
        roll = roll - k
    end
    
    if yaw ~= 0 or pitch ~= 0 or roll ~= 0 then
        local quat = yawPitchRoll(yaw, pitch, roll)
        self.rotation = multQuat(self.rotation, quat)
        self.dirty = true
    end
end

function Camera:render(passIndex)
    local pass = self.passes[passIndex]
    theApp.scene:renderCamera(pass)
end

function Camera:localMove(vector)
    
    vector = multVecQuat(vector, self.rotation)
    
    self.position = self.position + vector
    self.dirty = true
end

function Camera:setPosition(position)
    self.position = position
    self.dirty = true
end

function Camera:lookAt(lookAtPos, up)
    local upv = up
    upv:normalize()
    local zaxis = self.position - lookAtPos
    zaxis:normalize()
    local xaxis = Vector.cross(upv, zaxis)
    xaxis:normalize()
    local yaxis = Vector.cross(zaxis, xaxis)
    yaxis:normalize()
    
    local trace = xaxis.x + yaxis.y + zaxis.z + 1.0
    if trace > 0.000001 then
        local s = 0.5 / math.sqrt(trace)
        self.rotation = cc.quaternion(
            (yaxis.z - zaxis.y) * s,
            (zaxis.x - xaxis.z) * s,
            (xaxis.y - yaxis.x) * s,
            0.25 / s
        )
    else
        if xaxis.x > yaxis.y and xaxis.x > zaxis.z then
            local s = 0.5 / math.sqrt(1.0 + xaxis.x - yaxis.y - zaxis.z)
            self.rotation = cc.quaternion(
                0.25 / s,
                (yaxis.x + xaxis.y) * s,
                (zaxis.x + xaxis.z) * s,
                (yaxis.z - zaxis.y) * s
            )
        elseif yaxis.y > zaxis.z then
            local s = 0.5 / math.sqrt(1.0 + yaxis.y - xaxis.x - zaxis.z)
            self.rotation = cc.quaternion(
                (yaxis.x + xaxis.y) * s,
                0.25 / s,
                (zaxis.y + yaxis.z) * s,
                (zaxis.x - xaxis.z) * s
            )
        else
            local s = 0.5 / math.sqrt(1.0 + zaxis.z - xaxis.x - yaxis.y)
            self.rotation = cc.quaternion(
                (zaxis.x + xaxis.z ) * s,
                (zaxis.y + yaxis.z ) * s,
                0.25 / s,
                (xaxis.y - yaxis.x ) * s
            )
        end
    end
        
    self.dirty = true
end

function Camera:refreshView()   
    local viewHeight = 9
    
    local wSize = theApp.windowSize
    local aspect = wSize.width / wSize.height
    local viewWidth = viewHeight * aspect
    
    --pass:setOrthographic(-viewWidth / 2, viewWidth / 2, -viewHeight / 2, viewHeight / 2, 0.1, 1000)
      
    
    local passPosition = self.position + multVecQuat(Vector(0, 0, 0), self.rotation)
    
    for i = 1, #self.passes do
        local pass = self.passes[i]
        pass:setPerspective(10, aspect, 0.1, 1000)
        pass:setPosition3D(passPosition)
        pass:setRotationQuat(self.rotation)
    end

end