
Keyboard = Derive('Keyboard', InputDevice)

function Keyboard:init()
    Keyboard.base.init(self)
    
    self.events = {}
    self:regEvents()
end

function Keyboard:regEvents()
   
    local function onKeyPress(keyCode)
        table.insert(self.events, {keyCode, 1})
    end
    
    local function onKeyRelease(keyCode)
        table.insert(self.events, {keyCode, nil})
    end
   
    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(onKeyPress, cc.Handler.EVENT_KEYBOARD_PRESSED)
    listener:registerScriptHandler(onKeyRelease, cc.Handler.EVENT_KEYBOARD_RELEASED)
    dispatcher:addEventListenerWithFixedPriority(listener, 1)
   
end

function Keyboard:update()
    self.prevValues = table.clone(self.values)
    for event in iter(self.events) do
        self.values[event[1]] = event[2]
    end
    self.events = {}
end
