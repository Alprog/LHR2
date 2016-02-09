
Event = Class('Event')

function Event:raise(...)
    if self.handlers then
        for handler in iter(self.handlers) do
            handler(...)
        end
    end
end

function Event:addHandler(handler)
    self.handlers = self.handlers or {}
    table.insert(self.handlers, handler)
end

function Event:bindHandler(func, ...)
    self:addHandler(bind(func, ...))
end