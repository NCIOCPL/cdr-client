@REM Install Python 3.12 with Windows/scripting support.
@ECHO OFF

REM Set up the values we'll need
CD /D "%~dp0"
CD PythonFiles
SET PYTHON_DIR=%SystemDrive%\Python312
SET AXSCRIPT=%PYTHON_DIR%\lib\site-packages\win32comext\axscript
SET PYSCRIPT=%AXSCRIPT%\client\pyscript.py
SET INSTALLER=python-3.12.3-amd64.exe
SET INSTALL_OPTS=InstallAllUsers=1 PrependPath=1 CompileAll=1 AssociateFiles=1 Include_test=0

REM Start with a clean slate, just in case.
ECHO Uninstalling Python ...........................
%INSTALLER% /uninstall /quiet > uninstall.log

REM Perform the actual installation.
ECHO Installing Python .............................
%INSTALLER% /quiet TargetDir=%PYTHON_DIR% %INSTALL_OPTS%

REM Add contributed packages we'll need.
ECHO Installing third-party libraries ..............
py -m ensurepip --upgrade >> pip.log
py -m pip install -r requirements.txt >> pip.log

REM We need a search path for our custom modules which defers expansion of APPDATA.
ECHO Setting Python search path ....................
setx /M PYTHONPATH %PYTHON_DIR%\DLLs;%%APPDATA%%\SoftQuad\XMetaL\17.0\Macros > setx.log

REM Register Python as a scripting language XMetaL can use.
ECHO Registering Python Windows scripting engine ...
py %PYSCRIPT% > pyscript.log
IF ERRORLEVEL 1 ECHO Registration failed && EXIT /B 1

REM Make sure everything is working.
ECHO Verifying Python Windows scripting engine .....
PATH %PYTHON_DIR%;%PATH%
cscript test.pys > cscript.log
IF ERRORLEVEL 1 ECHO Python scripting test failed && EXIT /B 1

REM All done.
ECHO Python installation complete!
PAUSE
