
PropertyView = Derive('PropertyView', ItemView)

function PropertyView:init()
    self.nameView = StringView:create()
    self.nameView:setAnchorPoint(0, 0)
    self:addChild(self.nameView)
    
    self.valueView = EditBox:create()
    self.valueView:setAnchorPoint(0, 0)
    self:addChild(self.valueView)
    
    self.button = Button:create()
    self.button:setAnchorPoint(0, 0)
    self.button:setContentSize(cc.size(15, 15))
    self.button:setTitleText('...')
    self:addChild(self.button)
    
    self.valueView.changed:bindHandler(self.onTextChanged, self)
end

function PropertyView:onTextChanged(editBox, text)
    self.property:setValueText(self.object, text)
    self:refresh()
end

function PropertyView:onResize(size)
    local side = size.height - 2
    local buttonSize = cc.size(side, side)
    self.button:onResize(buttonSize)
    self.button:setPosition(size.width - side, 0)

    local viewWidth = (size.width - side) / 2
    local viewSize = cc.size(viewWidth, size.height)
    
    self.nameView:onResize(viewSize)
    
    if self.valueView then
        self.valueView:setPosition(viewWidth, 0)
        self.valueView:onResize(viewSize)
    end
    
    self:setContentSize(size)
end

function PropertyView:setItem(item)
    self.object = item.object
    self.property = item.property
    self:refresh()
end

function PropertyView:refresh()
    self.nameView:setItem(self.property.name)
    local text = self.property:getValueText(self.object)
    self.valueView:setText(text)
end

function PropertyView:setSelection(value)
    self.nameView:setSelection(value)
    self.valueView:setSelection(value)
end
