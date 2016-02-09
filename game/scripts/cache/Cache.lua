
function getCacheVersionOf(func)    
    local cache = {}
 
    return function(key)
        local value = cache[key]
        if value ~= nil then
            return value
        else
            value = func(key)
            cache[key] = value
            return value
        end
    end
end