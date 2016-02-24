
package.path = package.path .. ';../scripts/zerobrane/?.lua'
package.cpath = package.cpath .. ';../scripts/zerobrane/?.dll'

local debugger = require('mobdebug.mobdebug')

dump = function(t)
    print(debugger.dump(t))
end

debugger.line = function(a) 
    return tostring(a)
end

function StartDebug()
    debugger.start()
    debugger.enabled = true
    print('Debug Start')
    print(debugger.start)
end

function StopDebug()
    print('Debug Stop')
    debugger.done()
    debugger.enabled = false
end

function ToggleDebug()
    if debugger.enabled then
        StopDebug()
    else
        StartDebug()
    end
end

function WithoutDebug(func)
    if debugger.enabled then
        debugger.done()
        timestamp()
        func()
        timestamp()
        debugger.start()
        print('Time: '..timestampDelta)
    else
        func()
    end
end

if debugEnabled then
    StartDebug()
end