@ECHO OFF
CD /D "%~dp0"
ECHO Uninstalling XMetaL 9.0 ...
CD XMetaL9
msiexec /quiet /uninstall "XMetaL Author Essential.msi"
ECHO Installing XMetaL 17.0 ...
CD ..\XMetaL17
msiexec /quiet /package "XMetaL Author Essential (x64).mxi"
ECHO Installation successful!
PAUSE
