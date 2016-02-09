
Battle = Class('Battle')

function Battle:init()
    self.teams = {}
    self.mode = nil
end

function Battle:setTeamCount(count)
    for i = 1, count do
        self.teams[i] = self.teams[i] or {}
    end
    self.currentTeam = self.teams[1]
end

function Battle:spawnTeams()
    for i = 1, #self.teams do
        local team = self.teams[i]
        for j = 1, #team do
            local unit = team[j]
            self.arena:spawn(unit)
        end 
    end
end

function Battle:setArena(arena)
    arena.battle = self
    self.arena = arena
end

function Battle:setScene(scene)
    scene.battle = self
    self.scene = scene
end

function Battle:endRound()
    if self.wait then
        return
    end
    
    self:selectPlayer(nil)
    
    local team = self:getNextTeam()
    for i = 1, #team do
        team[i]:restoreRoundPoints()
    end
    self.currentTeam = team
    
    for i = 1, #team do
        if not team[i].dead then
           self:selectPlayer(team[i])
           break
        end
    end
end

function Battle:getNextTeam()
    local index = table.indexOf(self.teams, self.currentTeam)
    index = index + 1
    if index > #self.teams then
        index = 1
    end
    return self.teams[index]    
end

function Battle:setZoneSelection(zone, value, color)
    for i = 1, #zone do
        zone[i].selection:setVisible(value)
        if color then
            zone[i].selection:setColor(color)
        end
    end 
end

function Battle:toggleMode(mode)
    if self.mode == mode then
        self:exitMode()
    else
        if self.player then
            self:exitMode()
            if mode == 'motion' then
                self:enterMotionMode()
            elseif mode == 'attack' then
                if self.player:canAttack() then
                    self:enterAttackMode()
                end
            end
        end
    end
end

function Battle:enterMotionMode()
    self.zone = MarkZone(self.player.cell, self.player.motionPoints.cur)
    self:setZoneSelection(self.zone, true, cc.GREEN)
    self.mode = 'motion'
end

function Battle:getAllEnemies()
    local enemies = {}
    for i = 1, #self.teams do
        local team = self.teams[i]
        if team ~= self.currentTeam then
            for j = 1, #team do
                local enemy = team[j]
                if not enemy.dead then
                    table.insert(enemies, enemy)
                end
            end
        end
    end
    return enemies
end

function getDistance(a, b)
    local dx = b.x - a.x
    local dy = b.y - a.y
    return math.sqrt(dx * dx + dy * dy)
end

function Battle:enterAttackMode()   
    local zone = {}
    local enemies = self:getAllEnemies()
    for i = 1, #enemies do
        local enemy = enemies[i]
        local cell = enemy.cell
        
        local allow = true 
        if self.player.attackDistance then
            local dist = getDistance(self.player:getPosition3D(), cell:getPosition3D())
            allow = dist <= self.player.attackDistance
        end
        if allow then
            table.insert(zone, cell)
        end
    end
    self:setZoneSelection(zone, true, cc.RED)
    self.zone = zone
    self.mode = 'attack'
end

function Battle:exitMode()
    if self.zone then
        UnmarkZone(self.zone)
        self:setZoneSelection(self.zone, false)
        self.zone = nil
    end
    self.mode = nil
end

function Battle:onMotionCellClick(cell)
    local path = FindPathTo(cell)
    if #path >= 1 then
        if #path >= 2 then
            local player = self.player
            player.motionPoints:decrease(cell.distance)
            self:doTask(function()
                player:followPath(path)
            end)
        end
        self:exitMode()
    end
end

function Battle:onAttackCellClick(cell)
    if table.contains(self.zone, cell) then        
        local player = self.player
        player.actionPoints:decrease(player.attackCost)
        local enemy = cell.object
        self:doTask(function()
            player:attack(enemy)
            enemy:damage(player.attackPower)
        end)
    end
end

function Battle:doTask(task)
    local player = self.player
    self:selectPlayer(nil)
    self.scene:updateUI()
            
    self.wait = true
    self.arena.tasks:run(function()
        task()
        self.wait = false
        self:selectPlayer(player)
        self.scene:updateUI()
    end)
end

function Battle:onCellClick(cell)
    if self.mode == 'motion' then
        self:onMotionCellClick(cell)
    elseif self.mode == 'attack' then
        self:onAttackCellClick(cell)
    end
end

function Battle:highlightUnit(unit)
    
end

function Battle:selectPlayer(player)
    if self.wait or self.player == player then
        return
    end
    
    if self.player then
        self:exitMode()
        self.player:setSelection(false)
        self.player = nil
    end
    self.player = player
    if self.player then
        self.player:setSelection(true)
    end
end
    
function Battle:selectPlayerByIndex(index)
    local team = self.currentTeam
    local unit = team and team[index]
    if unit then
        self:selectPlayer(unit)
    end
end

function Battle:selectNext()
    if self.player and self.currentTeam then
        local team = self.currentTeam
        local index = table.indexOf(team, self.player)
        while true do
            index = index + 1
            if index > #team then
                index = 1
            end
            local unit = team[index]
            if not unit.dead then
               self:selectPlayer(unit)
               return
            end
        end
    end
end

function Battle:turnPlayer(direction)
    local player = self.player
    self:doTask(function()
        local rotation = player.rotation + math.pi / 2 * direction
        player:rotateTo(rotation)
    end)
end

