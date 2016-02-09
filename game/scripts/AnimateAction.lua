
AnimateAction = Class('AnimateAction')

function AnimateAction:init(type, time, filePath)
    self.time = time
    self.type = type
    self.filePath = filePath
end

function AnimateAction:perform(animate, time)
    if self.type == 'SoundEffect' then
        Audio:playSound('sounds/'..self.filePath, self.volume)
    elseif self.type == 'ParticlesEffect' then
        local model = animate:getTarget()
        
        for child in iter(model:getChildren()) do
            if child.action == self then
                child:reset()
                return
            end
        end
        
        local effect = ParticlesEffect:create(model, self.filePath, time)
        effect.action = self
        effect:setCameraMask(model:getCameraMask())
        model:addChild(effect)
        
        effect:setScale(50)
        effect:setRotation3D(Vec(0, 0, 0))
        
        self.position = self.position or {0,0,0}
        effect:setPosition3D(Vec(unpack(self.position)))
    end
end

function AnimateAction:getDuration()
    if self.type == 'SoundEffect' then
        return Audio:getDuration('sounds/'..self.filePath)
    elseif self.type == 'ParticlesEffect' then
        return 0
    end
end

function AnimateAction:getProperties()
    AnimateAction.soundProperties = AnimateAction.soundProperties or
    {
        StringProperty:create('filePath'),
        NumberProperty:create('volume')
    }
    AnimateAction.particlesProperties = AnimateAction.particlesProperties or
    {
        StringProperty:create('filePath'),
        VectorProperty:create(3, 'position')
    }
    
    if self.type == 'SoundEffect' then
        return AnimateAction.soundProperties
    elseif self.type == 'ParticlesEffect' then
        return AnimateAction.particlesProperties
    end
end

function AnimateAction:onChanged()
    
end