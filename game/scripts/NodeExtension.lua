
local Node = cc.Node

function Node:regCallback(listener, event, callback)
    local handler = function(...)
        if callback then
            return callback(self, ...)
        end
        return true
    end        
    listener:registerScriptHandler(handler, event)
end

function Node:regListener(listener)
    local dispatcher = self:getEventDispatcher()
    dispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function Node:listenTouches()
    local listener = cc.EventListenerTouchOneByOne:create()
    self:regCallback(listener, cc.Handler.EVENT_TOUCH_BEGAN, self.onTouchBegan)
    self:regCallback(listener, cc.Handler.EVENT_TOUCH_MOVED, self.onTouchMoved)
    self:regCallback(listener, cc.Handler.EVENT_TOUCH_ENDED, self.onTouchEnded)
    self:regListener(listener)
end

function Node:listenMouse()
    local listener = cc.EventListenerMouse:create()
    self:regCallback(listener, cc.Handler.EVENT_MOUSE_DOWN, self.onMouseDown)
    self:regCallback(listener, cc.Handler.EVENT_MOUSE_UP, self.onMouseUp)
    self:regListener(listener)
end

function Node:listenWheel()
    local listener = cc.EventListenerMouse:create()
    self:regCallback(listener, cc.Handler.EVENT_MOUSE_SCROLL, self.onMouseWheel)
    self:regListener(listener)
end

function Node:scheduleUpdate()
    function callback(delta)
        self:update(delta)
    end
    self:scheduleUpdateWithPriorityLua(callback, 0)
    --[[local scheduler = cc.Director:getInstance():getScheduler()
    local id = scheduler:scheduleScriptFunc(callback, 0, false)
    self.scheduleIds = self.scheduleIds or {}
    table.insert(self.scheduleIds, id)]]
end

--[[function Node:unscheduleAll()
    if self.scheduleIds then
        local scheduler = cc.Director:getInstance():getScheduler()
        for i = 1, #self.scheduleIds do
            local id = self.scheduleIds[i]
            scheduler:unscheduleScriptEntry(id)
        end
    end
end]]

function Node:selectChildren(func, nodes)
	nodes = nodes or {}

    local children = self:getChildren()
    for i = 1, #children do
        local child = children[i]
        if func(child) then
            table.insert(nodes, child)
        end
        child:selectChildren(func, nodes)
    end    
    
	return nodes
end

function Node:listenButtonClick(button)
    button:addTouchEventListener(function(object, eventtype)
        if eventtype == TOUCH_EVENT_ENDED then
            if self.onButtonClick then
                self:onButtonClick(object)
            end
        end
    end)
end

function Node:mapChildren()
    self:mapChildrenTo(self)
end

function Node:mapChildrenTo(table)
    local children = self:getChildren()
    for i = 1, #children do
        local child = children[i]
        local name = child:getName():toCamel()
        table[name] = child
    end 
end

function Node:isVisibleAtScene()
    local node = self
    while node do
        if not node:isVisible() then
            return false
        end
        node = node:getParent()
    end
    return true
end

function Node:hitTest(pos, flipY)
    local p = self:convertToNodeSpace(pos)
    if flipY then
        p.y = -p.y
    end
    local size = self:getContentSize()
    if p.x >= 0 and p.y >= 0 and p.x <= size.width and p.y <= size.height then
        return true
    end
end

function Node:getTouchDelta(touch)
    local p0 = self:convertToNodeSpace(touch:getPreviousLocation())
    local p1 = self:convertToNodeSpace(touch:getLocation())
    return Vector(p1.x - p0.x, p1.y - p0.y)  
end

function Node:bringToFront()
    local parent = self:getParent()
    self:pause()
    parent:reorderChild(self, 0)
    self:resume()
end

function Node:addMemberHandler(event, memberFunc)
    event:addHandler(bind(memberFunc, self))
end

function Node:createChild()
    local child = cc.Node:create()
    self:addChild(child)
    return child
end

function Node:keepObject(object)
    local container = self:getUserObject()
    if not container then
        container = cc.RefContainer:create()
        self:setUserObject(container)
    end
    container:add(object)
end