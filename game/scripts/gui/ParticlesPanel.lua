
ParticlesPanel = Derive('ParticlesPanel', ccui.Widget)

local buttonsHeight = 20

function ParticlesPanel:init()
    self.list = ListView:create()
    self.list.createView = self.createListView
    self:addChild(self.list)
    
    self.saveButton = Button:create('SaveButton', 'Save')
    self:listenButtonClick(self.saveButton)
    self:addChild(self.saveButton)
    
    self.revertButton = Button:create('RevertButton', 'Revert')
    self:listenButtonClick(self.revertButton)
    self:addChild(self.revertButton)
    
    self:scheduleUpdate()
end

function ParticlesPanel:update()
    self.list:refresh()
end

function ParticlesPanel:createListView()
    return PConfigView:create()
end

function ParticlesPanel:onResize(size)
    size.height = size.height - buttonsHeight - 2
    self.list:onResize(size)
    self.list:setPosition(0, buttonsHeight)
    
    local buttonSize = cc.size(size.width * 0.44, buttonsHeight)   
    self.saveButton:onResize(buttonSize)
    self.revertButton:onResize(buttonSize)
    self.saveButton:setPosition(size.width * 0.04, 0)
    self.revertButton:setPosition(size.width * 0.52, 0)
end

function ParticlesPanel:addAndSelect(config)
    local items = self.list.items
    if not table.contains(items, config) then
        table.insert(items, config)
        self.list:refresh()
    end
    
    self.list:selectItem(config)
end

function ParticlesPanel:onButtonClick(button)
    local name = button:getName()
    
    if name == 'SaveButton' then
        if self.list.selectedItem then
            self.list.selectedItem:save()
        end
    elseif name == 'RevertButton' then
        if self.list.selectedItem then
            self.list.selectedItem:reload()
        end
    end
    
end