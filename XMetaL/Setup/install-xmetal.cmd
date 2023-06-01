@ECHO OFF
CD /D "%~dp0"
ECHO Uninstalling XMetaL 9.0 ...
CD XMetaL9
msiexec /quiet /uninstall "XMetaL Author Essential.msi"
ECHO Installing XMetaL 17.0 ...
CD ..\XMetaL17
msiexec /quiet /package "XMetaL Author Essential (x64).msi"
ECHO Installation successful!
PAUSE
IF EXIST xmetal-20230125.exe (
  ECHO Patching XMetaL 17.0 ...
  COPY xmetal-20230125.exe "c:\Program Files\XMetaL 17.0\Author\xmetal.exe" /Y
  ECHO Patch successful!
  PAUSE
)
