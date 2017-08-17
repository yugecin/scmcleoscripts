@echo off

set MSBuild=C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe
set VisualStudioVersion=12.0

color 18
:b
del Release/*.cleo
set Theme=1
set ReleaseVersion=standard
"%MSBuild%" plpanel.vcxproj /p:Configuration=Release /p:VisualStudioVersion=%VisualStudioVersion%
set Theme=2
set ReleaseVersion=classic
"%MSBuild%" plpanel.vcxproj /p:Configuration=Release /p:VisualStudioVersion=%VisualStudioVersion%
set Theme=3
set ReleaseVersion=robin
"%MSBuild%" plpanel.vcxproj /p:Configuration=Release /p:VisualStudioVersion=%VisualStudioVersion%
cd >nul
pause
cls
goto b
