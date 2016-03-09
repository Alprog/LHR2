
local function index(table, key)
    local map = rawget(table, 'map')
    
    if not map then
        map = {}
        rawset(table, 'map', map)
    end
    
    local value = map[key]
    if value then
        return value
    else
        return getmetatable(table)[key]
    end
end

local function newindex(table, key, value)
    local map = rawget(table, 'map')
    
    local ref = map[key]
    if type(ref) == 'userdata' then
        if ref.release then
            ref:release()
        end
    end
    
    map[key] = value
    
    if type(value) == 'userdata' then
        if value.retain then
            value:retain()
        end
    end
end

function keepRefFields(class)
    class.__index = index
    class.__newindex = newindex
end