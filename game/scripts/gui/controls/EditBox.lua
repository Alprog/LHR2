
EditBox = Derive('EditBox', ccui.EditBox)

function EditBox:instantinate()
    local sprite = ccui.Scale9Sprite:create()
    return EditBox.__create(cc.size(200, 15), sprite)
end

function EditBox:init()
    self:setFontSize(22)
    self.changed = Event:create()
    
    self:registerScriptEditBoxHandler(function(event)
        if event == 'changed' then
            local text = self:getText()
            self.changed:raise(self, text)
        end
    end)
end

function EditBox:onResize(size)
   self:setContentSize(size)
   self:setFontSize(size.height)
end

function EditBox:setSelection(value)
    self:setFontColor(value and cc.YELLOW or cc.WHITE)
end



