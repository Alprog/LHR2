
PinBoard = Derive('PinBoard', cc.Node)

function PinBoard:init()
    self.pins = {}
    self.lastTouchTime = 0
    self:scheduleUpdate()
    self:listenTouches()
end

function PinBoard:update(delta)  
    self.lastTouchTime = self.lastTouchTime + delta
end

function PinBoard:onResize(size)
    self:refresh()
end

function PinBoard:setPinCount(count)
    for i = #self.pins + 1, count do
        self.pins[i] = self:createPin()
        self:addChild(self.pins[i])
    end
    for i = count + 1, #self.pins do
        self.pins[i]:removeFromParent()
        self.pins[i] = nil
    end
end

function PinBoard:onTouchBegan(touch, event)
    local pos = touch:getLocation()
    local localPos = self:convertToNodeSpace(pos)
    
    for pin in iter(self.pins) do
        if pin:hitTest(pos) then
            local sx, sy = pin:getPosition()
            self.pinShift = Vec(localPos.x - sx, localPos.y - sy)
            self:onSelectPin(pin)
            event:stopPropagation()
            self:refresh()
            return true
        end
    end
    
    if self:hitTest(pos) then
        if self.lastTouchTime < 0.2 then
            if self.onDoubleClick then
                self:onDoubleClick(localPos)
            end
        else
            if self.onClick then
                self:onClick(localPos)
            end
        end
        
        self:refresh()
        self.lastTouchTime = 0
        event:stopPropagation()
    end
end

function PinBoard:onTouchMoved(touch, event)   
    local location = touch:getLocation()
    local pos = self:convertToNodeSpace(location)
    pos.x = pos.x - self.pinShift.x
    pos.y = pos.y - self.pinShift.y
    self:onPinDrag(pos)
end

function PinBoard:refresh()
    
end
