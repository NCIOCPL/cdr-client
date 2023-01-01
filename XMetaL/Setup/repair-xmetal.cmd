@REM Remove and reinstall XMetal 17
@ECHO OFF
CD /D "%~dp0"
CD XMetaL17
ECHO Removing XMetal 17.0 ...
msiexec /quiet /uninstall "XMetaL Author Essential (x64).msi"
ECHO Installing XMetal 17.0 ...
msiexec /quiet /package "XMetaL Author Essential (x64).msi"
ECHO Reinstallation successful!
PAUSE
