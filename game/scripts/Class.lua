
function NewClass(name)
    local class = {}
    class.className = name
    class.__index = class
    class.__call = class
    class.isLuaClass = true
    
    function class:create(...)
        local instance = {}
        setmetatable(instance, class)
        if instance.init then           
            instance:init(...)
        end
        return instance
    end
    
    setmetatable(class, { __call = function(...)
        return class.create(...)
    end})
    
    return class
end

function multiBaseIndex(table, key)
    local class = getmetatable(table)
    local value = rawget(class, key)
    if value then 
        return value 
    end
    
    local bases = rawget(class, 'bases')
    if bases then
        for i = 1, #bases do
            value = bases[i][key]
            if value then
                return value
            end
        end
    end
end

function deserialize(class, peer)
    local instance = class.__create()
    tolua.setpeer(instance, peer)
    setmetatable(peer, class)
    if instance.onDeserialize then
        instance:onDeserialize()
    end
    return instance
end

function Derive(name, base, ...)
    local class = nil
    
    if base.isLuaClass then
        class = NewClass(name)
    else
        class = {}
        
        if base[".isclass"] then
            class.__create = function(...) 
                return base:create(...)
            end
            class.x = deserialize
        end

        function class:create(...)
            local instance = nil
            if class.instantinate then
                instance = class:instantinate(...)
            else
                instance = class.__create()
            end
            
            local peer = {}
            tolua.setpeer(instance, peer)
            setmetatable(peer, class)
            
            if instance.init then
                instance:init(...)
            end
            return instance
        end
    end

    setmetatable(class, base)
    class.base = base
    class.className = name
 
    if #{...} > 0 then
        class.__index = multiBaseIndex
        class.bases = { base, ... }
    else
        class.__index = class
    end
    
    return class
end

function Class(name, base)
    if base then
        return Derive(name, base)
    else
        return NewClass(name)
    end
end

function setUnion(class, name)
    
    function class:__index(key) 
        local config = rawget(self, name)
        if config and config[key] then 
            return config[key]
        else
            return getmetatable(self)[key]
        end
    end

    function class:__newindex(key, value)
        local config = rawget(self, name)
        if config and config[key] then 
            config[key] = value
        else
            rawset(self, key, value)
        end
    end
end
