
local shaders = {}
local sources = {}

local function processIncludes(source)
	local fileUtils = cc.FileUtils:getInstance()

	while true do
        local index = source:find("#include")
		if index == nil then
            return source
        end
		
		local qStart = source:find('"', index)
		local qEnd = source:find('"', qStart + 1)
		local fileName = 'shaders/includes/' .. source:sub(qStart + 1, qEnd - 1)

		local fullPath = fileUtils:fullPathForFilename(fileName)
        local content = fileUtils:getStringFromFile(fullPath)
    
		source = source:sub(1, index - 1) .. content .. source:sub(qEnd + 1)
	end
    
end

local function getShaderSource(fileName)
    if sources[fileName] then
       return sources[fileName]
    end
    
    local fileUtils = cc.FileUtils:getInstance()
    local fullPath = fileUtils:fullPathForFilename(fileName)
    local source = fileUtils:getStringFromFile(fullPath)
    source = processIncludes(source)
    sources[fileName] = source
    return source
end

function getShader(vsName, psName)
    local key = vsName..'@'..psName
    if shaders[key] then
        return shaders[key]
    end
    
    local vsSource = getShaderSource('shaders/vertex/'..vsName..'.vs')
    local psSource = getShaderSource('shaders/pixel/'..psName..'.ps')
    
    local shader = cc.GLProgram:createWithByteArrays(vsSource, psSource)
    if shader then
        shader:retain()
        shaders[key] = shader
    else
        return
    end
    return shader
end

function clearShaderCache()
    for i = 1, #shaders do
        shaders[i]:release()
    end
    shaders = {}
end

function createState(vsName, psName)
    local program = getShader(vsName, psName)
    return cc.GLProgramState:create(program)
end
