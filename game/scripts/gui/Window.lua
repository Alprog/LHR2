
Window = Derive('Window', Scene)

local borderSize = cc.size(7, 26)

function Window:instantinate()
    return Window.__create()
end

function Window:init(name, control, fixedSingle)
    Scene.init(self, 'Window')
    
    self.background = self:getChildByName('Background')
    self.titleLabel = self:getChildByName('TitleLabel')
    self.closeButton = self:getChildByName('CloseButton')
    self.clientArea = self:getChildByName('ClientArea')
    self.touchCover = self:getChildByName('TouchCover')

    if name then
        self.name = name
        self.titleLabel:setString(name)
    end
    if control then
        self:tie(control, 'ClientArea')
        self.touchCover:bringToFront()
        self.control = control
        control.window = self
    end
     
    self.touchCover.onTouchBegan = function(cover, touch, event)
        if cc.Node.hitTest(cover, touch:getLocation()) then
            self:focus()
        end
    end
    self.touchCover:listenTouches()
    
    local size = cc.size(300, 300)
    if fixedSingle then
        size = control:getContentSize()
        size.width = size.width + borderSize.width
        size.height = size.height + borderSize.height
        self.minSize = size
        self.maxSize = size
        self.closeButton:setVisible(false)
    else
        self.minSize = cc.size(100, 70)
        self.maxSize = cc.size(1366, 768)
    end
    
    self:onResize(size)
    self:listenTouches()
end

function Window:onTouchBegan(touch, event)
    local p = touch:getLocation()
    p = self:convertToNodeSpace(p)
    p.y = -p.y
    local s = self.size
    if p.x >= 0 and p.y >= 0 and p.x <= s.width and p.y <= s.height then
        local border = borderSize.width / 2
        
        local r = {
            left = p.x <= border,
            right = p.x >= s.width - border,
            bottom = p.y >= s.height - border
        }
        
        if r.left or r.right or r.bottom then
            self.resizing = r
        else
            self.resizing = nil
        end
        
        event:stopPropagation()
        
        return true
    end
end

function Window:onTouchMoved(touch, event)
    local delta = self:getTouchDelta(touch)
    
    if self.resizing then
        if self.resizing.bottom then
            self.size.height = self.size.height - delta.y
        end
        if self.resizing.left then
            self.size.width = self.size.width - delta.x
            local x, y = self:getPosition()
            self:setPosition(x + delta.x, y)
        end
        if self.resizing.right then
            self.size.width = self.size.width + delta.x
        end
    
        self:onResize(self.size)
    else
        -- drag
        local x, y = self:getPosition()
        self:setPosition(x + delta.x, y + delta.y)
    end    
end

function Window:onResize(size)
    size.width = clamp(size.width, self.minSize.width, self.maxSize.width)
    size.height = clamp(size.height, self.minSize.height, self.maxSize.height)

    self.size = size
    
    self.background:setContentSize(size.width, size.height)
    self.touchCover:setContentSize(size.width, size.height)
    self.closeButton:setPosition(size.width, 0)
    
    local w = size.width - borderSize.width
    local h = size.height - borderSize.height
    self.clientArea:setContentSize(w, h)
    
    Scene.onResize(self, size)
end

function Window:onButtonClick(button)
    local name = button:getName()
    if name == 'CloseButton' then
        self:setVisible(false)
    end
end

function Window:focus()
    self.mdi:selectWindow(self)
end

function Window:setSelection(value)
    self.titleLabel:setColor(value and cc.YELLOW or cc.WHITE)
end
