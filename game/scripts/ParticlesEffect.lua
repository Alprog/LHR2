
require 'ParticlesParameter.lua'

ParticlesEffect = Derive('ParticlesEffect', cc.ParticleSystemNode)

function ParticlesEffect:instantinate()
    return ParticlesEffect.__create(200)
end

function ParticlesEffect:init(model, filePath, deltaTime)
    self.model = model
    self.filePath = filePath
    
    self.config = getParticlesConfig(filePath)
    self:initFromConfig(self.config)
    
    local shader = getShader('particle', 'particle')
    local state = cc.GLProgramState:create(shader)
    self:setGLProgramState(state)
    
    self:step(deltaTime)
    self:scheduleUpdate()
end

function ParticlesEffect:refreshParameter()
    self:initFromConfig(self.config)
end

function ParticlesEffect:initFromConfig(config)   
    self:setBlendAdditive(config.additive)
    
    local texture = getTexture(config.texturePath)
    self:setTexture(texture)
    
    for property in iter(config:getProperties()) do
        if property.className == 'GraphProperty' then
            local name = property.name
            self:setParameterGraph(pp[name], unpack(config[name]))
        end
    end
    
    self:setParameterGraph(pp.OverLifeColor, {0, 1}, {1, 0}, {0.5, 0}, {0.15, 0}, {1, 1})
    
    self.version = config.version or 0
end

function ParticlesEffect:decouple(parameter)
    local componentCount = 2
    
    local lists = {}
    for i = 1, componentCount do
        local list = {}
        for j = 1, #parameter do
            list[j] = parameter[j][i]
        end
        lists[i] = list
    end
    
    return lists
end

function ParticlesEffect:update(delta)
    if self.config.version > self.version then
        self:refreshParameter()
    end
    
    self:step(delta)
    local count = self:getParticleCount()
    if self.started then
        if count == 0 then
            self:kill()
        end
    else
        if count > 0 then
            self.started = true
        end
    end
end

function ParticlesEffect:kill()
    self:unscheduleUpdate()
    self:removeFromParent() 
end