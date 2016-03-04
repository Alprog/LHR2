
function table.serialize(t, format, tab, keys)
	local i = 1
	local str = ''
	str = str .. '{'
	tab = tab or ''
	
    if not keys then
        keys = {}
        for k in pairs(t) do
            table.insert(keys, k)
        end
    end
	
    local multiline = format and #keys > 1
    
	local first = true
	for key in iter(keys) do
		local value = t[key]
	
		if first then
			first = false
		else
			str = str .. ','
		end
	    if multiline then
			str = str .. '\n' .. tab .. '    '
		end
		if key == i then
			i = i + 1
		else
            if type(key) == 'string' then
                str = str .. key
            else
                str = str.. '[' .. key .. ']'
            end
            str = str .. (format and ' = ' or '=')
		end
        if type(value) == 'table' then
			str = str .. table.serialize(value, format, multiline and tab .. '    ' or tab)
		elseif type(value) == 'string' then
			str = str .. '\'' .. value .. '\''
        elseif type(value) == 'boolean' then
            str = str .. (value and 'true' or 'false')
		elseif type(value) == 'userdata' then
            if value.serializeFields then
                str = str .. table.serialize(value, format, tab, value.serializeFields)
            else
                str = str .. '"userdata"'
            end
        else
			str = str .. value
		end
	end

	if multiline and not first then
		str = str .. '\n' .. tab
	end
	str = str .. '}'

	return str
end