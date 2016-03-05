
local function loadActionScheme(filePath)
    local scheme = deserializeFromFile(filePath) or {}
        
    for name, events in pairs(scheme) do
        for event in iter(events) do
            setmetatable(event, AnimateAction)
        end
    end
    
    return scheme
end

getActionScheme = getCacheVersionOf(loadActionScheme)