
InputButton = Class('InputButton')

function InputButton:init()
    self.options = {}
end

function InputButton:addOption(device, keyCode)
    table.insert(self.options, {
        device = device,
        keyCode = keyCode
    })
end

function InputButton:getValue()
    local value = 0
    for i = 1, #self.options do
        local option = self.options[i]
        value = math.max(value, option.device.values[option.keyCode] or 0)
    end
    return value
end

function InputButton:getPrevValue()
    local value = 0
    for i = 1, #self.options do
        local option = self.options[i]
        value = math.max(value, option.device.values[option.keyCode] or 0)
    end
    return value
end

function InputButton:isPressed()
    return self:getValue() > 0
end

function InputButton:wasPressed()
    return self:getPrevValue() > 0
end

function InputButton:onPress()
    return self:isPressed() and not self:wasPressed()
end

