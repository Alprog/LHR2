
function getTexture(filePath)
    local cache = theApp.director:getTextureCache()
    return cache:addImage(filePath)
end
