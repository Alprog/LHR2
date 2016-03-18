
Control = Class('Control')

local KEYBOARD = 1
local GAMEPAD = 2

function Control:init(input)
    self.input = input
    self.layout = {}
    
    self.buttonBoost = InputButton:create()
    self.buttonBoost:addOption(input.devices[KEYBOARD], KEY_SHIFT)
    
    ----------------------
    
    a = InputButton:create()
    a:addOption(input.devices[KEYBOARD], KEY_D)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.DPad_Right)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.L_Right)
    
    b = InputButton:create()
    b:addOption(input.devices[KEYBOARD], KEY_A)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.DPad_Left)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.L_Left)
    
    x = InputAxis:create(a, b)

    a = InputButton:create()
    a:addOption(input.devices[KEYBOARD], KEY_R)

    b = InputButton:create()
    b:addOption(input.devices[KEYBOARD], KEY_F)
    
    y = InputAxis:create(a, b)

    a = InputButton:create()
    a:addOption(input.devices[KEYBOARD], KEY_S)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.DPad_Down)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.L_Down)

    b = InputButton:create()
    b:addOption(input.devices[KEYBOARD], KEY_W)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.DPad_Up)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.L_Up)
    
    z = InputAxis:create(a, b)
    
    self.trackMove = InputTrack(x, y, z)
    
    ----------------------
    
    a = InputButton:create()
    a:addOption(input.devices[KEYBOARD], KEY_LEFT_ARROW)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.R_Left)
    
    b = InputButton:create()
    b:addOption(input.devices[KEYBOARD], KEY_RIGHT_ARROW)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.R_Right)
    
    x = InputAxis:create(a, b)

    a = InputButton:create()
    a:addOption(input.devices[KEYBOARD], KEY_UP_ARROW)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.R_Up)

    b = InputButton:create()
    b:addOption(input.devices[KEYBOARD], KEY_DOWN_ARROW)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.R_Down)
    
    y = InputAxis:create(a, b)

    a = InputButton:create()
    a:addOption(input.devices[KEYBOARD], KEY_Q)
    a:addOption(input.devices[GAMEPAD], GamePad.Keys.L2)
    
    b = InputButton:create()
    b:addOption(input.devices[KEYBOARD], KEY_E)
    b:addOption(input.devices[GAMEPAD], GamePad.Keys.R2)
    
    z = InputAxis:create(a, b)
    
    self.trackRotate = InputTrack(x, y, z)
    
end

function Control:loadLayout()
    
end

function Control:saveLayout()
    
end

theControl = Control:create(theInput)