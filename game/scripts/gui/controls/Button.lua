
Button = Derive('Button', ccui.Button)

function Button:instantinate()
    local n = 'Default/Button_Normal.png'
    local p = 'Default/Button_Press.png'
    local d = 'Default/Button_Disabled.png'
    return Button.__create(n, p, d) 
end

function Button:init(name, titleText, fontSize)
    self:setScale9Enabled(true)
    
    fontSize = fontSize or 12
    self:setTitleFontSize(fontSize)
    self:setTitleColor(cc.BLACK)
    self:setAnchorPoint(0, 0)
    if name then
        self:setName(name)
    end
    if titleText then
        self:setTitleText(titleText)
    end
    self.size = self:getContentSize()
end

function Button:onResize(size)
    self:setContentSize(size)
    self.size = size
end