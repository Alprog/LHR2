
InputTrack = Class('InputTrack')

function InputTrack:init(axisX, axisY, axisZ)
    self.axisX = axisX
    self.axisY = axisY
    self.axisZ = axisZ
end

function InputTrack:getValue()
    return Vector(
        self.axisX and self.axisX:getValue() or 0,
        self.axisY and self.axisY:getValue() or 0,
        self.axisZ and self.axisZ:getValue() or 0
    )
end