
InputAxis = Class('InputAxis')

function InputAxis:init(positiveButton, negativeButton)
    self.positiveButton = positiveButton
    self.negativeButton = negativeButton
end

function InputAxis:getValue()
    return self.positiveButton:getValue() - self.negativeButton:getValue()
end