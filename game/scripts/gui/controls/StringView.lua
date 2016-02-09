
StringView = Derive('StringView', ItemView)

function StringView:init(text)
    self.label = ccui.Text:create()
    self.label:setFontSize(22)
    self.label:setAnchorPoint(0, 0.5)
    self:addChild(self.label)
    
    self.label:setString('I')
    self.labelHeight = self.label:getContentSize().height
        
    self:setItem(text or '')
    self:setTouchEnabled(true)
end

function StringView:autoSize()
    local size = self.label:getContentSize()
    local scale = self.label:getScale()
    size.width = size.width * scale
    size.height = size.height * scale
    self:setContentSize(size)
end

function StringView:setItem(item)
    self.item = item
    self.label:setString(item)
end

function StringView:setSelection(value)
    self.label:setTextColor(value and cc.YELLOW or cc.WHITE)
end

function StringView:onResize(size)
    self.label:setPosition(0, size.height / 2)
    local scale = size.height / self.labelHeight
    self.label:setScale(scale)
   
    if size.width == 'auto' then
        size.width = self.label:getContentSize().width * scale
    end
   
    self:setContentSize(size)
end