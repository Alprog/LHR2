
Animate3D = Derive('Animate3D', cc.Animate3D)

function Animate3D:instantinate(animation)
    return Animate3D.__create(animation)
end

function Animate3D:init(animation, actions)
    self.time = 0
    self.duration = self:getDuration()
    self.actions = actions
end

function Animate3D:isPlaying()
    return self.speed > 0
end

function Animate3D:isAtEnd()
    return self.time == self.duration
end

function Animate3D:togglePause()
    if not self:isPlaying() and self:isAtEnd() then
        self:restart()
        self.speed = 1
    else
        self.speed = 1 - self.speed
    end
end

function Animate3D:toggleLoop()
   self.loop = not self.loop 
end

function Animate3D:restart()
    local target = self:getTarget()
    self:startWithTarget(target)
    self.time = 0
end

function Animate3D:setTime(time)
    time = math.min(time, self.duration)
    
    local delta = time - self.time
    if delta >= 0 then
        self:step(delta)
    else
        self:restart()
        self:step(0) -- first tick ignored
        self:step(time)
    end
    self.time = time
end

function Animate3D:goToStart()
    self:setTime(0)
end

function Animate3D:goToEnd()
    self:setTime(self.duration)
end

function Animate3D:update(delta)
    delta = delta * self.speed
    
    if delta > 0 then
        self.time = self.time + delta
        self:checkActions(delta)
        
        if self.time < self.duration then
            self:step(delta)
        else
            if self.loop then
                self:restart()
                self.time = self.time % self.duration
                self:step(self.time)
                self:checkActions(delta)
            else
                self:step(delta)
                self.speed = 0
                self.time = self.duration
            end
        end
    end
end

function Animate3D:checkActions(delta)
    for action in iter(self.actions) do
        local time = self.time - action.time
        if time > 0 and time <= delta then
            action:perform(self, time)
        end
    end
end
