
require 'SortedList.lua'
require 'Utils.lua'

function MarkZone(start, maxDistance)
    start.distance = 0
    
    local sortedList = SortedList:create('distance')
    sortedList:insert(start)
    
    local zone = { start }
    
    while #sortedList > 0 do
        local curCell = table.remove(sortedList, 1)
        for i = 1, #curCell.ways do
            local way = curCell.ways[i]
            local cell = way.cell
            if not cell.object then
                local yDelta = cell:getPosition3D().y - curCell:getPosition3D().y
                local passable = yDelta > -1 and yDelta <= 0.4 
                if passable then
                    local newDistance = curCell.distance + 1
                    if newDistance <= maxDistance then
                        if cell.distance == nil or newDistance < cell.distance then
                            
                            if cell.distance then
                                table.removeValue(sortedList, cell)
                            else
                                table.insert(zone, cell)
                            end
                            
                            cell.from = curCell
                            cell.distance = newDistance
                            sortedList:insert(cell, 'distance')
                        end
                    end
                end
            end
        end
    end
    
    return zone
end

function FindPathTo(cell)
    local path = {}
    
    if cell.distance then
        while cell do
            table.insert(path, 1, cell)
            cell = cell.from
        end
    end
    
    return path
end

function UnmarkZone(zone)
    for i = 1, #zone do
        zone[i].distance = nil
        zone[i].from = nil
    end
end

function FindPath(srcCell, dstCell)
    local zone = MarkZone(srcCell, 20)    
    local path = FindPathTo(dstCell)
    UnmarkZone(zone)
    return path
end