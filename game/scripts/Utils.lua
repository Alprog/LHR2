
require 'Bits.lua'

cclog = function(...)
    print(string.format(...))
end

function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

function emptyFunction()
end

function Vec(x, y, z, w)
    return { x = x, y = y, z = z, w = w }
end

local prevTime = nil

function timestamp()
    local time = os.clock()
    if prevTime ~= nil then
       timestampDelta = time - prevTime
    end
    prevTime = time
end

function multQuat(q1, q2)
    return {
        x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
        w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
    }
end

function multVecQuat(vec, quat)
    local qvec = Vector(quat.x, quat.y, quat.z)
    
    local uv = Vector.cross(qvec, vec)
    local uuv = Vector.cross(qvec, uv)

    return vec + uv * (2 * quat.w) + uuv * 2
end

function TableToString(object, tab)
	local i = 1
	local str = ''
	str = str .. '{'
	tab = tab or ''
	
	local keys, values = {}, {}
	for k, v in pairs(object) do
		table.insert(keys, k)
		table.insert(values, v)
	end
	
	local first = true
	for j = 1, #keys do
		local key = keys[j]
		local value = values[j]
	
		if first then
			first = false
		else
			str = str .. ','
		end
	    if #keys > 1 then
			str = str .. '\n' .. tab .. '    '
		end
		if key == i then
			i = i + 1
		else
			str = str .. key .. ' = '
		end
		if type(value) == 'table' then
			str = str .. TableToString( value, #keys > 1 and tab .. '    ' or tab )
		elseif type(value) == 'string' then
			str = str .. '\'' .. value .. '\''
        elseif type(value) == 'boolean' then
            str = str .. (value and 'true' or 'false')
		else
			str = str .. value
		end
	end

	if not first and #keys > 1 then
		str = str .. '\n' .. tab
	end
	str = str .. '}'

	return str
end

function lerp(v1, v2, t)
    return v1 + (v2 - v1) * t
end

function vecLerp(v1, v2, t)
    return {
        x = v1.x + (v2.x - v1.x) * t,
        y = v1.y + (v2.y - v1.y) * t,
        z = v1.z + (v2.z - v1.z) * t
    }
end

function vecLength(vec)
    return math.sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)
end

function clamp(value, min, max)
    if value < min then
        return min
    elseif value > max then
        return max
    else
        return value
    end
end

local polygonInfos = {}

function CreatePolygonSprite(name)
    local info = polygonInfos[name]
    if info == nil then
        info = cc.AutoPolygon:generatePolygon(name)
        polygonInfos[name] = info
    end
    return cc.Sprite:create(info)
end

function wait(time)
    local t = 0
    while t < time do
        t = t + deltaTime
        if t >= time then
            deltaTime = t - time
            break
        end
        coroutine.yield()
    end
end

function repeatf(value, min, max)
    value = value - min
    value = value % (max - min)
    value = value + min
    return value
end

function cmpAngle(a, b, epsilon)
    a = repeatf(a, 0, math.pi * 2)
    b = repeatf(b, 0, math.pi * 2)
    return math.abs(a - b) < (epsilon or 0.001)
end

function averageAngle(a, b)
    b = repeatf(b, a - math.pi, a + math.pi) 
    return (a + b) / 2
end

function copy(t)
    local o = {}
    for k, v in pairs(t) do
        o.k = v
    end
    return o
end

function exist(name)
    local file = io.open(name, "r")
    if file then
       io.close(file)
       return true
    end
    return false
end

function setDefaults(table, default)
    for key, value in pairs(default) do
        if table[key] == nil then
            table[key] = value
        end
    end
end

function round(value)
    if value >= 0 then 
        return math.floor(value + 0.5) 
    else
        return math.ceil(value - 0.5)
    end
end

function is(userdata, class)
    return getmetatable(userdata) == getmetatable(class)
end

function fadeTo(node, value, fullTime)
    local startValue = node:getOpacity()
    local time = 0
    while time < fullTime do
        time = time + deltaTime
        if time >= fullTime then
            deltaTime = time - fullTime
            break
        end
        local curValue = lerp(startValue, value, time / fullTime)
        node:setOpacity(curValue)
        coroutine.yield()
    end
    node:setOpacity(value)
end

function string:startWith(str)
    return self:sub(1, #str) == str
end

function string:endWith(str)
    return self:sub(-#str) == str
end

function string:toCamel()
    return self:sub(1, 1):lower() .. self:sub(2)
end

function table:randomItem()
   local index = math.random(1, #self)
   return self[index]
end

function table:contains(object)
    for i = 1, #self do
        if self[i] == object then
            return true
        end
    end
    return false
end

function table:indexOf(object)
    for i = 1, #self do
        if self[i] == object then
            return i
        end
    end
    return nil
end

function table:removeValue(value)
    for i = 1, #self do
        if self[i] == value then
            table.remove(self, i)
        end
    end
end

function table:clone()
    local clone = {}
    for k, v in pairs(self) do
        clone[k] = v
    end
    return clone
end

function table:join(delimiter)
    local str = tostring(self[1])
    for i = 2, #self do
        str = str..delimiter..tostring(self[i])
    end
    return str
end

function deepclone(object)
    if type(object) == 'table' then
        local clone = {}
        for k, v in pairs(object) do
            clone[deepcopy(k)] = deepcopy(v)
        end
        setmetatable(clone, getmetatable(object))
        return clone
    else
        return object
    end
end

function yawPitchRoll(yaw, pitch, roll)
    local resultQuat = nil
    
    function addAxisRotation(axis, value)
        if value ~= 0 then
            local quat = cc.quaternion_createFromAxisAngle(axis, value)
            if resultQuat then
                resultQuat = multQuat(quat, resultQuat)
            else
                resultQuat = quat
            end
        end
    end
    
    addAxisRotation(Vec(0, 1, 0), yaw)
    addAxisRotation(Vec(1, 0, 0), pitch)
    addAxisRotation(Vec(0, 0, 1), roll)
    
    return resultQuat or { 0, 0, 0, 1 }
end

function indexToBytes(index)
    c = index % 256
    index = (index - c) / 256
    b = index % 256
    a = (index - b) / 256
    return a, b, c
end

function bytesToIndex(a, b, c)
    return a * 65536 + b * 256 + c
end

function iter(t)
    local i = 0
    local count = #t
    return function()
        i = i + 1
        if i <= count then 
            return t[i]
        end
    end
end

function createWeakTable(mode)
    local t = {}
    local mt = {__mode = mode or "v"}
    setmetatable(t, mt)
    return t
end

function createMaterial(vsName, psName)
    local program = getShader(vsName, psName)
    local state = cc.GLProgramState:create(program)
    return cc.Material:createWithGLStateProgram(state)
end

function saveTableToFile(table, path, name)
    path = '../data/'..path
    name = name or 'data'
    
    local file = io.open(path, 'w+')
    local str = TableToString(table)
    file:write(name .. ' = ' .. str)
    io.close(file)
end

function loadTableFromFile(path, name)
    path = '../data/'..path
    name = name or 'data'
    
    _G[name] = nil
    if exist(path) then
        dofile(path)
        return _G[name]
    end
end

function changeExtension(path, extension)
    path = path:gsub('[.][^./\\]*$', '')
    return path .. '.' .. extension
end

-- work only on windows
function scandir(path)
    path = '../data/'..path
    
    local cmd = 'dir "'..path..'"'
    cmd = cmd .. ' /b'    -- bare format
    cmd = cmd .. ' /A:-D' -- no folders
    local names = {}
    for name in io.popen(cmd):lines() do
        table.insert(names, name)
    end
    return names
end
