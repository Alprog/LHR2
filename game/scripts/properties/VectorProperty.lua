
VectorProperty = Derive('VectorProperty', Property)

function VectorProperty:init(componentCount, name)
    Property.init(self, name)
    self.componentCount = componentCount
end

function VectorProperty:getDefaultValue(value)
    local vector = {}
    for i = 1, self.componentCount do
        vector[i] = 0
    end
    return vector
end

function VectorProperty:valueToText(value)
    return table.join(value, ',')
end

function VectorProperty:textToValue(text)
    
    local arr = text:split(',')
    
    for i = 1, #arr do
        local s = arr[i]:trim()
        arr[i] = tonumber(s)
    end
    
    if #arr ~= self.componentCount then
        return nil
    end
    
    return arr
end