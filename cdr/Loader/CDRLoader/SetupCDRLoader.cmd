@echo off
echo Copying CDRLoader Files
set XM_DESTINATION=C:\Program Files\SoftQuad\XMetaL 3
set DESK_DESTINATION=%ALLUSERSPROFILE%\Desktop
copy unzip.exe  "%XM_DESTINATION%"
copy CDRLoader.exe "%XM_DESTINATION%"
copy CDRLoader.ini "%XM_DESTINATION%"
copy CDRLoader.cmd "%XM_DESTINATION%"
copy CDRLoader.lnk "%DESK_DESTINATION%"
echo Finished copying CDRLoader Files
echo You may now delete the CDRLdrInstall directory.
pause
