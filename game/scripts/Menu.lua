
Menu = Derive('Menu', Scene)

function Menu:init()
    Scene.init(self, 'Menu')
end

function Menu:onButtonClick(button)
    print('click + '..button:getName())
    
    local name = button:getName()
    if name == 'ContinueButton' then        
        theSceneManager:pop()
    elseif name == 'ExitToMainMenuButton' then
        theApp.tasks:run(function()  
            theSceneManager:pop()
            theSceneManager:goTo(TitleScreen:create())
        end)
    end
    
end
