
CurryFunc = Class('CurryFunc')

function CurryFunc:init(func, ...)
    self.func = func
    self.bindedArgs = {...}
end

function CurryFunc:__call(...)
    local args = table.clone(self.bindedArgs)
    for arg in iter({...}) do
        table.insert(args, arg)
    end
    self.func(unpack(args))
end

function bind(func, ...)
    return CurryFunc:create(func, ...)
end