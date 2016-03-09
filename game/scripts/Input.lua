
require 'Debug.lua'

Input = {}
Input.keys = {}
Input.mousePos = Vector(0, 0)

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

local function Init()
    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(OnKeyPress, cc.Handler.EVENT_KEYBOARD_PRESSED)
    listener:registerScriptHandler(OnKeyRelease, cc.Handler.EVENT_KEYBOARD_RELEASED)
    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    dispatcher:addEventListenerWithFixedPriority(listener, 1)
    
    listener = cc.EventListenerMouse:create()
    listener:registerScriptHandler(OnMouseMove, cc.Handler.EVENT_MOUSE_MOVE)
    dispatcher:addEventListenerWithFixedPriority(listener, 1)
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

Init()
