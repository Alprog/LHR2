
function NewClass(name)
    local cls = {}
    cls.className = name
    cls.__index = cls
    cls.__setindex = cls
    cls.__call = cls
    cls.isLuaClass = true
    
    function cls:create(...)
        local instance = {}
        setmetatable(instance, cls)
        if instance.init then           
            instance:init(...)
        end
        return instance
    end
    
    setmetatable(cls, { __call = function(...)
        return cls.create(...)
    end})
    
    return cls
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

function Derive(name, base, ...)
    local cls = nil
    
    if base.isLuaClass then
        cls = NewClass(name)
    else
        cls = {}
        
        if base[".isclass"] then
            cls.__create = function(...) 
                return base:create(...)
            end
        end

        function cls:create(...)
            local instance = nil
            if cls.instantinate then
                instance = cls:instantinate(...)
            else
                instance = cls.__create()
            end
            
            local peer = {}
            tolua.setpeer(instance, peer)
            setmetatable(peer, cls)
            
            if instance.init then
                instance:init(...)
            end
            return instance
        end
    end

    setmetatable(cls, base)
    cls.base = base
    cls.className = name
 
    if #{...} > 0 then
        cls.__index = multiBaseIndex
        cls.bases = { base, ... }
    else
        cls.__index = cls
    end
    
    return cls
end

function Class(name, base)
    if base then
        return Derive(name, base)
    else
        return NewClass(name)
    end
end

function setUnion(class, name)
    local __index = class.__index

    function class:__index(key) 
        local config = rawget(self, name)
        if config and config[key] then 
            return config[key]
        else
            return __index[key]
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
