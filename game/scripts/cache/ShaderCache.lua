
local shaders = {}
local sources = {}

local function getShaderSource(fileName)
    if sources[fileName] then
       return sources[fileName]
    end
    
    local fileUtils = cc.FileUtils:getInstance()
    local fullPath = fileUtils:fullPathForFilename(fileName)
    local source = fileUtils:getStringFromFile(fullPath)
    sources[fileName] = source
    return source
end

function getShader(vsName, psName)
    local key = vsName..'@'..psName
    if shaders[key] then
        return shaders[key]
    end
    
    local vsSource = getShaderSource('shaders/'..vsName..'.vs')
    local psSource = getShaderSource('shaders/'..psName..'.ps')
    
    local shader = cc.GLProgram:createWithByteArrays(vsSource, psSource)
    shader:retain()
    shaders[key] = shader
    return shader
end

function clearShaderCache()
    for i = 1, #shaders do
        shaders[i]:release()
    end
    shaders = {}
end
