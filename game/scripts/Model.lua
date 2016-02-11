
require 'Animate3D.lua'
require 'AnimateAction.lua'

Model = Derive("Model", cc.Sprite3D)

function Model:instantinate(modelPath, effectPath)
    return Model.__create(modelPath)
end

function Model:init(modelPath, actionSchemePath)
    if actionSchemePath == nil then
        actionSchemePath = changeExtension(modelPath, 'scheme')
    end
    
    self.modelPath = modelPath
    self.actionSchemePath = actionSchemePath
    
    self.animations = getAnimations(modelPath)
    self.actionScheme = getActionScheme(actionSchemePath)
    
    self.animates = {}
    self.fadeTimes = {}
    self.defaultFadeTime = 0.1
    self.curAnimate = nil
    self:setCullFaceEnabled(true)
    
    self:scheduleUpdate()
end

function Model:copy()
    local copy = Model:create(self.modelPath)
    copy:setPosition3D(self:getPosition3D())
    copy:setRotation3D(self:getRotation3D())
    copy:shareSkin(self)
    copy:unscheduleUpdate()
    return copy
end

function Model:update(dt)
    for i = #self.animates, 1, -1 do
        local animate = self.animates[i]
        self:checkFade(animate, dt)
            
        if animate.dead then
            animate:release()
            table.remove(self.animates, i)
        else
            animate:update(dt)
        end
    end
end

function Model:waitAnimation()
    while self.curAnimate and not self.curAnimate:isAtEnd() do
        coroutine.yield()
    end
end

function Model:setFadeTime(name, time)
    self.fadeTimes[name] = time
end

function Model:getFadeTime(name)
    if name then
        return self.fadeTimes[name] or self.defaultFadeTime
    else
        return self.defaultFadeTime
    end
end

function ChangeWeight(animate, delta)
    animate.weight = clamp(animate.weight + delta, 0, 1)
    animate:setWeight(animate.weight)
end

function Model:checkFade(animate, dt)
    if animate.fadeIn then
        ChangeWeight(animate, dt / animate.fadeTime)
        if animate.weight >= 1 then
            animate.fadeIn = false
        end
    end
    if animate.fadeOut then
        ChangeWeight(animate, -dt / animate.fadeTime)
        if animate.weight <= 0 then
            animate.fadeOut = false
            animate.dead = true
        end
    end
end

function Model:play(name, loop, speed)
    if self.curAnimate and self.curAnimate.name == name then
        return
    end
     
    local animation = self.animations[name]
    
    self.actionScheme[name] = self.actionScheme[name] or {}
    local actions = self.actionScheme[name]

    local animate = nil
    if animation then
        animate = Animate3D:create(animation, actions)
    else
        animate = cc.DelayTime:create(1)
        animate.setWeight = emptyFunction
    end
   
    animate:startWithTarget(self)
    animate:step(0)
    animate.name = name
    animate.fadeTime = self:getFadeTime(name)

    animate.loop = loop
    animate.speed = speed or 1
    animate:retain()
    table.insert(self.animates, animate)
    
    if self.curAnimate then
        self:fadeOut(self.curAnimate)
        self.curAnimate = animate
        self:fadeIn(self.curAnimate)
    else
        self.curAnimate = animate
    end
end

function Model:playLoop(name, speed)
   self:play(name, true, speed)
end

function Model:fadeIn(animate)
    animate.weight = 0
    animate.fadeIn = true
end

function Model:fadeOut(animate)
    animate.weight = 1
    animate.fadeOut = true
end

function Model:setShaders(vert, frag)
    local program = getShader(vert, frag)
    local state = cc.GLProgramState:create(program)
    local count = self:getMeshCount()
    for i = 0, count - 1 do
        local mesh = self:getMeshByIndex(i)
        if i == 0 then
            mesh:setGLProgramState(state)
        else
            mesh:setGLProgramState(state:clone())
        end
    end 
end

function Model:setUniformVec4(name, vec)
    local count = self:getMeshCount()
    for i = 0, count - 1 do
        local mesh = self:getMeshByIndex(i)
        local state = mesh:getGLProgramState()
        state:setUniformVec4(name, vec)
    end
end

function Model:clearEffects()
    for child in iter(self:getChildren()) do
        if child.className == 'ParticlesEffect' then
            child:kill()
        end
    end
end
