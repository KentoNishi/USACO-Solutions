:start
set /p name=Problem name: 
GOTO makeFiles

:makeFiles
echo > %CD%\..\%name%\main.cpp
powershell -Command "(gc %CD%\..\template\main.cpp) -replace 'template', '%name%' | Out-File -encoding ASCII %CD%\..\%name%\main.cpp"
mkdir %CD%\..\%name%
copy %CD%\..\template\template.in %CD%\..\%name%\%name%.in
copy %CD%\..\template\template.out %CD%\..\%name%\%name%.out
