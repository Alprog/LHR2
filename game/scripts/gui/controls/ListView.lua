
ListView = Derive('ListView', ccui.ListView)

local BACK_COLOR = cc.c3b(75, 75, 125)
local defaultRowHeight = 15

function ListView:init()
    self.items = {}
    self.views = {}
    self.itemSelected = Event:create()
    self:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
    self:setBackGroundColor(BACK_COLOR)
    self:addEventListener(self.eventListener)
    self.rowHeight = defaultRowHeight
    self:listenTouches()    
end

function ListView:setItems(items)
    if self.items ~= items then
        self.items = items or {}
        self:selectItem(nil)
        self:refresh()
    end
end

function ListView:refresh()
    self.items = self.items or {}
    self:setViewCount(#self.items)
    for i = 1, #self.items do
        self.views[i]:setItem(self.items[i])
    end
end

function ListView:createView()
    return StringView:create()
end

function ListView:setViewCount(count)
    local size = self:getContentSize()
    local rowSize = cc.size(size.width, self.rowHeight)
    
    for i = #self.views + 1, count do
        local view = self:createView()
        if view.onResize then
            view:onResize(rowSize)
        end
        self:pushBackCustomItem(view)
        table.insert(self.views, view)
    end
    for i = #self.views, count + 1, -1 do
        if self.items[i] == self.selectedItem then
            self:selectItem(nil)
        end
        self:removeItem(i - 1)
        self.views[i] = nil
    end
end

function ListView:selectIndex(index)
    self:selectItem(self.items[index])
end

function ListView:selectItem(item)
    self.selectedItem = item
    for i = 1, #self.views do
        local view = self.views[i]
        view:setSelection(item == self.items[i])
    end
    self.itemSelected:raise(self, item)
    if self.onSelectItem then
        self:onSelectItem(item)
    end
end

function ListView:eventListener(eventType)
    if eventType == 0 then
        local index = self:getCurSelectedIndex() + 1
        self:selectIndex(index)
    end
end

function ListView:onResize(size)
    local rowSize = cc.size(size.width, self.rowHeight)
    for view in iter(self.views) do
        if view.onResize then
            view:onResize(rowSize)
        end
    end
    self:setContentSize(size)
end
