
BoolProperty = Derive('BoolProperty', Property)

function BoolProperty:getDefaultValue()
    return false
end

function BoolProperty:valueToText(value)
    return tostring(value)
end

function BoolProperty:textToValue(text)
    if text == '' or text == 'false' or text == '0' or text == 'f' then
        return false
    else
        return true
    end
end
