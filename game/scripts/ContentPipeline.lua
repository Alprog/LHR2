
function isUpToDate(filePath, sourcePath)
    if theFileUtils:isFileExist(filePath) then
        local time = theFileUtils:getFileModificationTime(filePath)
        local sourceTime = theFileUtils:getFileModificationTime(sourcePath)
        return time > sourceTime
    end
end

function convertModels(directory, recursive)
    local fileNames = theFileUtils:list(directory, FileType.File)
    for fileName in iter(fileNames) do
        local filePath = directory..'\\'..fileName
        local extension = getExtension(filePath)
        if extension == 'fbx' then
            local convertedPath = changeExtension(filePath, 'c3b')
            if not isUpToDate(convertedPath, filePath) then
                processFbx(filePath)
            end
        end
    end
end

function processFbx(filePath)    
    local convPath = '..\\..\\tools\\fbx-conv.exe'
    local fullPath = theFileUtils:fullPathForFilename(filePath)
    
    theFileUtils:removeFile(changeExtension(fullPath, 'c3b'))
    theFileUtils:removeFile(changeExtension(fullPath, 'c3t'))
    
    local command = convPath..' -a "'..fullPath..'"'
    os.execute(command)
end

function contentPipeline()
    convertModels('models')
end
