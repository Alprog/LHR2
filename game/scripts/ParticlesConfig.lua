
ParticlesConfig = Class('ParticlesConfig')
setUnion(ParticlesConfig, 'data')

function ParticlesConfig:init(filePath)
    self.filePath = filePath
    self.version = 0
    self:reload()
end

function ParticlesConfig:initDefault()
    local data = self.data
    data.additive = false
    data.texturePath = 'particles/sphere.png'
    data.EmissionFrequency = data.EmissionFrequency or {{0, 0.1, 0.11}, {200, 200, 0}}
    data.ParticleLifetime = data.ParticleLifetime or {{ 0, 1 }, { 0.5, 0.5 }}
    data.OverLifeSize = data.OverLifeSize or {{ 0, 0.2, 0.5 }, { 0, 2, 0 }}
    data.OverLifeSpeed = data.OverLifeSpeed or {{ 0, 1 }, { 16, 16 }}
    
    setmetatable(data.EmissionFrequency, Parameter)
    setmetatable(data.ParticleLifetime, Parameter)
    setmetatable(data.OverLifeSize, Parameter)
    setmetatable(data.OverLifeSpeed, Parameter)
end

function ParticlesConfig:save()
    serializeToFile(self.data, self.filePath)
    self.modified = false
end

function ParticlesConfig:reload()
    self.data = deserializeFromFile(self.filePath) or {}
    self:initDefault()
    self:onChanged()
    self.modified = false
end

function ParticlesConfig:onChanged()
    self.modified = true
    self.version = self.version + 1
end

function ParticlesConfig:getProperties()
    ParticlesConfig.properties = ParticlesConfig.properties or
    {
        StringProperty:create('texturePath'),
        BoolProperty:create('additive'),
        GraphProperty:create('EmissionFrequency', 4, 400),
        GraphProperty:create('ParticleLifetime', 4, 4),
        GraphProperty:create('OverLifeSize', 1, 20),
        GraphProperty:create('OverLifeSpeed', 1, 40)
    }
    return ParticlesConfig.properties
end

getParticlesConfig = getCacheVersionOf(function(filePath)
    return ParticlesConfig:create(filePath)
end)
