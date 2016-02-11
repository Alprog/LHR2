
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
        local fileUtils = cc.FileUtils:getInstance()
        local fileNames = fileUtils:list(self.direction, FileType.File)
        if self.extension then
            for i = #fileNames, 1, -1 do
                local extension = getExtension(fileNames[i])
                if extension ~= self.extension then
                    table.remove(fileNames, i)
                end
            end
        end
        self:setItems(fileNames)
    end
end