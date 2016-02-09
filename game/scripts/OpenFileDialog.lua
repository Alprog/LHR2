
require 'gui/init.lua'

OpenFileDialog = Class('OpenFileDialog', Scene)

function OpenFileDialog:instantinate()
    return OpenFileDialog.__create()
end

function OpenFileDialog:init(directory, extension)
    Scene.init(self, 'ListDialog')

    local fileListView = FileListView:create()
    fileListView:setExtensionFilter(extension)
    fileListView:setDirection(directory)
    self.modelListView = modelListView
    
    
    self:tie(fileListView, 'ListViewArea')    
    self.fileListView = fileListView
end

function OpenFileDialog:onButtonClick(button)
    local name = button:getName()
    if name == 'OkButton' then
        local result = self.fileListView.selectedItem
        self:close(result)
    else
        self:close()
    end
end

