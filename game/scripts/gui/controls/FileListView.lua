
FileListView = Derive('FileListView', ListView)

function FileListView:setExtensionFilter(extension)
    if self.extension ~= extension then
        self.extension = extension
        self:refresh()
    end
end

function FileListView:setDirection(direction)
    if self.direction ~= direction then
        self.direction = direction
        self:refresh()
    end
end

function FileListView:refresh()
    if self.direction then
        local fileNames = scandir(self.direction)
        if self.extension then
            local ending = '.' .. self.extension
            local index = -#ending
            for i = #fileNames, 1, -1 do
                if fileNames[i]:sub(index) ~= ending then
                    table.remove(fileNames, i)
                end
            end
        end
        self:setItems(fileNames)
    end
end