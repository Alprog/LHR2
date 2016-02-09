
GraphProperty = Derive('GraphProperty', Property)

function GraphProperty:init(name, maxTime, maxValue)
    Property.init(self, name)
    self.maxTime = maxTime
    self.maxValue = maxValue
end

function GraphProperty:valueToText(value)
    return 'graph'
end

function GraphProperty:textToValue(text)
    return nil
end