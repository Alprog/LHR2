
ParameterGraph = Derive('ParameterGraph', PinBoard)

function ParameterGraph:init()
    ParameterGraph.base.init(self)
    self.canvas = Canvas:create()
    self:addChild(self.canvas)
end

function ParameterGraph:setItem(item)
    if self.item ~= item then
        self.item = item
        self.parameter = item and item.property:getValue(item.object)
        self.selectedIndex = 0
        self:refresh()
    end
end

function ParameterGraph:onSelectPin(pin)
    self:selectIndex(pin.index)
end

function ParameterGraph:selectIndex(index)
    self.selectedIndex = index
    self:redraw()
end

function ParameterGraph:createPin()
    local pin = cc.Sprite:create('pixel.png')
    pin:setScale(7, 7)
    return pin
end

function ParameterGraph:onDoubleClick(position)
    if not self.parameter then
        return
    end
    
    local keyframe = self:getKeyframeFromPosition(position)
    
    if #self.parameter == 0 then
        keyframe[1] = 0
    end
    
    local time = keyframe[1]
    local timeList = self.parameter[1]
    
    local index = 1
    while index <= #timeList do
        if time < timeList[index] then
            break
        end
        index = index + 1
    end
    self.parameter:insertKeyframe(index, keyframe)
    
    self:redraw()
    self:onEdited()
end

function ParameterGraph:onEdited()
    if self.item then
        self.item.object:onChanged()
    end
end

function ParameterGraph:getKeyframeFromPosition(position)
    return { position.x / self.scaleX, position.y / self.scaleY } 
end

function ParameterGraph:getPositionFromKeyframe(keyframe)
    return Vector(keyframe[1] * self.scaleX, keyframe[2] * self.scaleY) 
end

function ParameterGraph:refresh()
    self:refreshScale()
    self:redraw()
end

function ParameterGraph:refreshScale()
    if self.item then
        local size = self:getContentSize()
        local property = self.item.property
        self.scaleX = size.width / property.maxTime
        self.scaleY = size.height / property.maxValue
    end
end

function ParameterGraph:redraw()
    self.canvas:clear()
    if not self.item then
        self:setPinCount(0)
        return
    end
    
    local count = self.parameter:getKeyframeCount()
    self:setPinCount(count)
    
    local points = {}
    for i = 1, count do
        local keyframe = self.parameter:getKeyframe(i)
        local point = self:getPositionFromKeyframe(keyframe)
        local pin = self.pins[i]
        
        table.insert(points, point)
        pin:setPosition(point.x, point.y)
        pin.index = i        
        pin:setColor(self.selectedIndex == i and cc.YELLOW or cc.WHITE)
    end
    if #points > 0 then
        local x = self:getContentSize().width
        local y = points[#points].y
        table.insert(points, Vector(x, y))
        
        self.canvas:drawLineStrip(points, cc.RED)
    end
end

function ParameterGraph:onPinDrag(pos)
    local index = self.selectedIndex
    local area = self:getAllowedKeyframeArea(index)
    
    local keyframe = self:getKeyframeFromPosition(pos)
    keyframe[1] = clamp(keyframe[1], area.min.x, area.max.x)
    keyframe[2] = clamp(keyframe[2], area.min.y, area.max.y)
    self.parameter:updateKeyframe(index, keyframe)
    
    self:redraw()
    self:onEdited()
end

function ParameterGraph:getAllowedKeyframeArea(index)
    local area = { min = Vec(0, 0), max = Vec(0, 0) }
    
    local size = self:getContentSize()
    local maxPosition = Vec(size.width, size.height)
    local maxKey = self:getKeyframeFromPosition(maxPosition)
    area.min.y = 0; area.max.y = maxKey[2]
    
    if index > 1 then
        local prevKey = self.parameter:getKeyframe(index - 1)
        local nextKey = self.parameter:getKeyframe(index + 1)
        area.min.x = prevKey and prevKey[1] or 0
        area.max.x = nextKey and nextKey[1] or maxKey[1]
    end

    return area
end

function ParameterGraph:onKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_DELETE then
        local index = self.selectedIndex
        if index > 1 then
            self.parameter:removeKeyframe(index)
            self:selectIndex(index - 1)
            self:onEdited()
        end
    end
end