@echo off
REM *************************************************************************
REM  Update this path to point to the absolute install location of the 
REM  Debug Server
REM  Only set the paths once. Create the 'PATHS_SET' environment variable to
REM  indicate that the paths have been set already.
REM *************************************************************************
set DEBUGSERVER=%CCSV5_INSTALL_DIR%\ccs_base
REM *************************************************************************
set PATH=%DEBUGSERVER%\scripting;%XDCROOT%;%PATH%
set PATH=%DEBUGSERVER%\common;%PATH%
set PATH=%DEBUGSERVER%\DebugServer\packages\;%PATH%
set PATH=%DEBUGSERVER%\common\uscif;%PATH%
set PATH=%DEBUGSERVER%\common\IDE;%PATH%
set PATH=%DEBUGSERVER%\common\bin;%PATH%
set PATH=%DEBUGSERVER%\DebugServer\bin;%PATH%
set PATH=%DEBUGSERVER%\DebugServer\components;%PATH%
set PATH=%DEBUGSERVER%\..\eclipse\jre\bin;%PATH%
set XDCPATH=%DEBUGSERVER%/DebugServer/packages;../;%XDCPATH%
REM *************************************************************************
