
PostProcessor = NewClass('PostProcessor')

function PostProcessor:init()
    self.camera = cc.Camera:create()
    self.camera:setOrthographic(0, 1, 0, 1, -1, 1)
end

function PostProcessor:perform()
    
end