
PConfigView = Derive('PConfigView', ItemView)

function PConfigView:init()
    self.nameView = StringView:create()
    self.nameView:setAnchorPoint(0, 0)
    self:addChild(self.nameView)
    
    self.button = Button:create()
    self.button:setAnchorPoint(0, 0)
    self.button:setTitleText('X')
    self:addChild(self.button)
    
    self:setHeight(20)
end

function PConfigView:onResize(size)
    self:setHeight(size.height)
end

function PConfigView:setHeight(height)
    local buttonSide = height - 2
    local buttonSize = cc.size(buttonSide, buttonSide)
    self.button:onResize(buttonSize)
    self.nameView:onResize(cc.size('auto', height))
    self:setContentSize(0, height)
    self:refreshWidth()
end

function PConfigView:refreshWidth()
    local nameWidth = self.nameView:getContentSize().width
    local buttonWidth = self.button.size.width
    local spaceWidth = buttonWidth * 1.2
    self.button:setPosition(nameWidth + spaceWidth / 3, 0)
end

function PConfigView:setItem(item)
    local name = item.filePath
    if item.modified then
        name = name..'*'
    end
    self.nameView:setItem(name)
    self.nameView:autoSize()
    self:refreshWidth()
end

function PConfigView:setSelection(value)
    self.nameView:setSelection(value)
end