
require 'Debug.lua'

Input = Class('Input')

local function OnMouseMove(event)
    theInput.mousePos = Vec(event:getCursorX(), event:getCursorY())
end

local function OnKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_F1 then
        theApp:toggleStatistics()
    elseif keyCode == cc.KeyCode.KEY_F7 then
        theRenderer.temporalAAEnabled = not theRenderer.temporalAAEnabled
    elseif keyCode == cc.KeyCode.KEY_F10 then
        ToggleDebug()
    elseif keyCode == cc.KeyCode.KEY_F11 then
        theApp:toggleFullscreen()
    elseif keyCode == cc.KeyCode.KEY_F12 then
        theApp:toggleWidescreen()
    else
        theApp.sceneManager:onKeyPress(keyCode)
    end    
end

local function OnGPadDown(keyCode)
    print(keyCode)
end

local function OnGPadUp(keyCode)
    print(keyCode)
end

function getAxisValue(positive, negative)
    local value = 0
    if theInput.devices[1].values[positive] == 1 then
        value = value + 1
    end
    if  theInput.devices[1].values[negative] == 1 then
       value = value - 1 
    end
    return value
end

function Input:getValue(deviceIndex, keyCode)
    return self.devices[deviceIndex].values[keyCode] or 0
end

function Input:getPrevValue(deviceIndex, keyCode)
    return self.devices[deviceIndex].prevValues[keyCode] or 0
end

function Input:init()
    self.devices = {} 
    self.devices[1] = Keyboard:create()
    self.devices[2] = GamePad:create(0)
    
    self.mousePos = Vector(0, 0)
    
    self.gamepad = cc.GamePad:create(0)
    self.gamepad:retain()
    
    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    
    local keyListener = cc.EventListenerKeyboard:create()
    keyListener:registerScriptHandler(OnKeyPress, cc.Handler.EVENT_KEYBOARD_PRESSED)
    keyListener:registerScriptHandler(OnKeyRelease, cc.Handler.EVENT_KEYBOARD_RELEASED)
    dispatcher:addEventListenerWithFixedPriority(keyListener, 1)
    
    local mouseListener = cc.EventListenerMouse:create()
    mouseListener:registerScriptHandler(OnMouseMove, cc.Handler.EVENT_MOUSE_MOVE)
    dispatcher:addEventListenerWithFixedPriority(mouseListener, 1)   
end

function Input:update()
    for device in iter(self.devices) do
        device:update()
    end
end

theInput = Input:create()
