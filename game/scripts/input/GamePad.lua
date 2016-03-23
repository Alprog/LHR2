
GamePad = Derive('GamePad', InputDevice)

GamePad.Keys = 
{
    A = 1,
    B = 2,
    X = 3,
    Y = 4,
    L1 = 5,
    R1 = 6,
    Option = 7,
    Start = 8,
    L3 = 9,
    R3 = 10,
    DPad_Up = 11,
    DPad_Right = 12,
    DPad_Down = 13,
    DPad_Left = 14,
    
    L_Right = 101,
    L_Left = 102,
    L_Down = 103,
    L_Up = 104,
    L2 = 105,
    R2 = 106,
    R_Down = 107,
    R_Up = 108,
    R_Right = 109,
    R_Left = 110,
}

function GamePad:init(id)
    GamePad.base.init(self)
    self.cObj = cc.GamePad:create(id)
    self.cObj:retain()
end

function GamePad:update()
    self.prevValues = table.clone(self.values)
    
    if self.cObj:isPresent() then
        local buttons = self.cObj:getButtons()
        for i = 1, #buttons do
            self.values[i] = buttons[i]
        end
        
        local axis = self.cObj:getAxis()
        local index = 101
        for i = 1, #axis do
            local value = axis[i]
            self.values[index] = value > 0.2 and value or 0
            self.values[index + 1] = value < -0.2 and -value or 0
            index = index + 2
        end        
    end    
end
