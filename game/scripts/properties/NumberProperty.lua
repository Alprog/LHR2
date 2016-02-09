
NumberProperty = Derive('NumberProperty', Property)

function NumberProperty:getDefaultValue()
    return 0
end

function NumberProperty:valueToText(value)
    return tostring(value)
end

function NumberProperty:textToValue(text)
    return tonumber(text)
end