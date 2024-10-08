@ECHO OFF
CD /D "%~dp0"
ECHO Installing XMetaL 17.0 ...
CDR XMetaL17
msiexec /x "XMetaL Author Essential (x64).msi" /qn
msiexec /i "XMetaL Author Essential (x64).msi" /qn
ECHO Installation successful!
PAUSE
