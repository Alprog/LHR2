
MDI = Derive('MDI', cc.Node)

function MDI:addWindow(name, control, fixedSingle)
    local window = Window:create(name, control, fixedSingle)
    window.mdi = self
    self:addChild(window)
end

function MDI:selectWindow(window)
    if self.selectedWindow == window then
        return
    end
    
    if self.selectedWindow ~= nil then
        self.selectedWindow:setSelection(false)
    end
    self.selectedWindow = window
    if self.selectedWindow ~= nil then
        self.selectedWindow:setSelection(true)
        self.selectedWindow:bringToFront()
    end
end

function MDI:onKeyPress(keyCode)
    if self.selectedWindow then
        if self.selectedWindow.control.onKeyPress then
            self.selectedWindow.control:onKeyPress(keyCode)
        end
    end 
end

function MDI:saveLayout(path)
    local layout = {}
    for window in iter(self:getChildren()) do
        local x, y = window:getPosition()
        local wndData = { 
            name = window.name,
            x = x, 
            y = y,
            w = window.size.width,
            h = window.size.height
        }
        table.insert(layout, wndData)
    end
    
    serializeToFile(layout, path)
end

function MDI:loadLayout(path)
    local layout = deserializeFromFile(path) or {}
    for i = 1, #layout do
        local wndData = layout[i]
        layout[wndData.name] = wndData
    end
    for window in iter(self:getChildren()) do
        local data = layout[window.name]
        if data then
            window:onResize(cc.size(data.w, data.h))
            window:setPosition(data.x, data.y)
        end
    end
end
