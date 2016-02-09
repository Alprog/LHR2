
TimelinePin = Derive('TimelinePin', cc.Node)

function TimelinePin:init()
    self.background = cc.Sprite:create('pixel.png')
    self.background:setAnchorPoint(0, 0)
    self:addChild(self.background)
    
    self.icon = cc.Sprite:create('pixel.png')
    self.icon:setAnchorPoint(0, 0)
    self:addChild(self.icon)
    
    self:setAnchorPoint(0, 1)    
end

function TimelinePin:setSize(size)
    self:setContentSize(size)
    self.background:setScale(size.width, size.height)
    self.icon:setScale(size.height, size.height)
end

function TimelinePin:setAction(action)
    self.action = action
    local texture = getTexture('gui/'..action.type..'.png')
    self.icon:setTexture(texture)
end

function TimelinePin:setSelection(value)
    self.background:setColor(value and cc.YELLOW or cc.WHITE)
end