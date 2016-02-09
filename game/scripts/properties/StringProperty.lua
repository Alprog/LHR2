
StringProperty = Derive('StringProperty', Property)

function StringProperty:getDefaultValue()
    return ''
end

function StringProperty:valueToText(value)
    return value
end

function StringProperty:textToValue(text)
    return text
end