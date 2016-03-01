
TitleScreen = Derive('TitleScreen', Scene)

function TitleScreen:init()
    Scene.init(self, 'TitleScreen')
    
    if theApp.settings.music then
        cc.SimpleAudioEngine:getInstance():playMusic("breach.mp3", true)
    end    
end

function TitleScreen:onButtonClick(button)
    local name = button:getName()
    if name == 'StartGameButton' then    
        local battleScreen = BattleScreen:create()
        theSceneManager:goTo(battleScreen)
    elseif name == 'SettingsButton' then
        local levelEditor = LevelEditor:create()
        theSceneManager:goTo(levelEditor)
    elseif name == 'EffectLabButton' then
        local effectLab = EffectLab:create()
        theSceneManager:goTo(effectLab)
    elseif name == 'QuitButton' then
        theApp:close()
    end
end
