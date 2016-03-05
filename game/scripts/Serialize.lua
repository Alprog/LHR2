
function serializeTable(t, replacements, keys)
    if keys == nil then
        keys = {}
        for key in pairs(t) do
            table.insert(keys, key)
        end
    end
  
    local str = ''
    
    local index = 1
    for i = 1, #keys do
        local key = keys[i]
        local value = t[key]
        if value ~= nil then
            if key == index then
                index = index + 1
            else
                str = str .. serializeKey(key) .. '='
            end
            str = str .. serializeValue(value, replacements)
            
            if i < #keys then
                str = str .. ','
            end
        end
    end
   
    return '{' .. str .. '}'
end

function serializeObject(object, replacements)
    local replacement = replacements and replacements[object]
    if replacement then
        return replacement
    end
    
    local objectType = type(object)
    if objectType == 'table' then
        return serializeTable(object, replacements)
    elseif objectType == 'userdata' then
        local peer = tolua.getpeer(object)
        if peer then
            local content = serializeTable(peer, replacements, object.serializableFields)
            return object.className .. ':x(' .. content .. ')'
        else
            return '{}'
        end
    end
    
end

function serializeValue(value, replacements)
    local valueType = type(value)
    if valueType == 'number' then
        return value
    elseif valueType == 'string' then
        return "'"..value .."'"
    elseif valueType == 'boolean' then
        return value and 'true' or 'false'
    else
        return serializeObject(value, replacements)
    end
end

function serializeKey(key)
    local keyType = type(key)
    if keyType == 'string' then
        return key
    else
        return '['..key..']'
    end
end

-- object should be userdata or table
function refCounting(object, refsTable, orderTable)
	refsTable[object] = (refsTable[object] or 0) + 1
	if refsTable[object] == 1 then
		table.insert(orderTable, object)
    else
        return
	end
    
    if type(object) == 'userdata' then
        object = tolua.getpeer(object)
        if object == nil then
            return
        end
    end
    
	for key, value in pairs(object) do
        local valueType = type(value)
		if valueType == 'table' or valueType == 'userdata' then
			refCounting(value, refsTable, orderTable)
		end
	end
end

-- object should be userdata or table
function serialize(object)
	local refsTable = {}
	local orderTable = {}
	refCounting(object, refsTable, orderTable)
    
    local str = ''
	local index = 0
	local replacements = {}
       
	for i = #orderTable, 1, -1 do
		local object = orderTable[i]
		if i == 1 or refsTable[object] > 1 then
			index = index + 1
			local name = 'object' .. index
			str = str .. 'local ' .. name .. '='..serializeValue(object, replacements) .. '\n'
			replacements[object] = name 
		end
	end
	
	return str
end
