
require 'Class.lua'

SortedList = Class('SortedList')

function SortedList:init(sortProperty)
    self.sortProperty = sortProperty or 'sortValue'
end

function SortedList:insert(item)
    local sortValue = item[self.sortProperty]
    for i = 1, #self do
        if sortValue < self[i][self.sortProperty] then
            table.insert(self, i, item)
            return
        end
    end
    table.insert(self, item)
end

function SortedList:remove(item)
    for i = 1, #self do
        if self[i] == item then
            table.remove(self, i)
        end
    end
end