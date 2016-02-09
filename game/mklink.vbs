set shell = WScript.CreateObject("WScript.Shell")
curDir = shell.CurrentDirectory
linkPath = curDir  + "/lhr2.lnk"
set link = shell.CreateShortcut(linkPath) 
link.TargetPath = curDir + "/bin/lhr2.exe"
link.WorkingDirectory = curDir + "/bin"
link.Save