
Property = Class('Property')

function Property:init(name)
    self.name = name
end

function Property:getValue(object)
    local value = object[self.name]
    if value == nil then
        return self:getDefaultValue()
    else
        return value
    end
end

function Property:setValue(object, value)
    object[self.name] = value
    object:onChanged()
end

function Property:getValueText(object)
    local value = self:getValue(object)
    return self:valueToText(value)
end

function Property:setValueText(object, text)
    local value = self:textToValue(text)
    if value ~= nil then
        self:setValue(object, value)
        return true
    end
end

function Property:getDefaultValue()
    return nil
end

function Property:valueToText(value)
    return tostring(value)
end

function Property:textToValue(text)
    return nil
end