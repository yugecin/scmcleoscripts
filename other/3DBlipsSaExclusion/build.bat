@ECHO OFF
CALL "C:\Users\Robin\broftware\Microsoft Visual Studio 8\VC\bin\vcvars32.bat"
REM my vcvars returns errorlevel 9009 (attempted to execute a non-existing command), so skipping next check
REM IF %ERRORLEVEL% NEQ 0 GOTO:ERR
NASM -f win32 ZZ3DBlipsSARemoveHouseIcons.asm
IF %ERRORLEVEL% NEQ 0 GOTO:ERR
LINK /NOLOGO /DLL /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib" /ENTRY:dllmain /OUT:ZZ3DBlipsSARemoveHouseIcons.asi Kernel32.lib User32.lib ZZ3DBlipsSARemoveHouseIcons.obj
IF %ERRORLEVEL% NEQ 0 GOTO:ERR
GOTO:EOF
:ERR
ECHO.
ECHO.
ECHO FAILURE
