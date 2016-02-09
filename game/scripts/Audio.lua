
Audio = Class('Audio')

local durationCache = {}

function Audio:playSound(filePath, volume)
    volume = volume or 100
    return ccexp.AudioEngine:play2d(filePath, false, volume / 100)
end

function Audio:stopSound(id)
    ccexp.AudioEngine:stop(id)
end

function Audio:getDuration(filePath)
    local duration = durationCache[filePath]
    
    while not duration or duration < 0 do
        local engine = ccexp.AudioEngine
        local id = engine:play2d(filePath)
        duration = engine:getDuration(id)
        engine:stop(id)
        
        durationCache[filePath] = duration
    end
    
    return duration
end