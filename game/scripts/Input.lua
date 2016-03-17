
require 'Debug.lua'

Input = Class('Input')

local function OnMouseMove(event)
    Input.mousePos = Vec(event:getCursorX(), event:getCursorY())
end

local function OnKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_F1 then
        theApp:toggleStatistics()
    elseif keyCode == cc.KeyCode.KEY_F10 then
        ToggleDebug()
    elseif keyCode == cc.KeyCode.KEY_F11 then
        theApp:toggleFullscreen()
    elseif keyCode == cc.KeyCode.KEY_F12 then
        theApp:toggleWidescreen()
    else
        theApp.sceneManager:onKeyPress(keyCode)
    end
    
    Input.keys[keyCode] = true
end

local function OnKeyRelease(keyCode)
    Input.keys[keyCode] = nil
end

local function OnGPadDown(keyCode)
    print(keyCode)
end

local function OnGPadUp(keyCode)
    print(keyCode)
end

function getAxisValue(positive, negative)
    local value = 0
    if Input.keys[positive] then
        value = value + 1
    end
    if Input.keys[negative] then
       value = value - 1 
    end
    return value
end

function Input:init()
    self.keys = {}
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
    if self.gamepad:isPresent() then
        local buttons = self.gamepad:getButtons()
        local axis = self.gamepad:getAxis()
        
        --print(unpack(buttons))
        --print(unpack(axis))
    end
end

Input:init()
