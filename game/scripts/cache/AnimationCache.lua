
local function loadAnimations(filePath)
    local list = cc.Animation3D:loadAnimations(filePath)
    local animations = {}
    
    for i = 1, #list do
        local animation = list[i]
        animation:retain()
        local name = animation:getName()
        
        local index = name:find('|')
        if index ~= nil then
            name = name:sub(index + 1)
            print(name)
        end
        
        while animations[name] do
            name = name..'2'
        end
        
        animations[name] = animation
    end
    
    return animations
end

getAnimations = getCacheVersionOf(loadAnimations)
