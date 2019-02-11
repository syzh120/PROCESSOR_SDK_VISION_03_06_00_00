@echo off
REM *************************************************************************
REM  Update this path to point to the absolute install location of the 
REM  Debug Server
REM  Only set the paths once. Create the 'PATHS_SET' environment variable to
REM  indicate that the paths have been set already.
REM *************************************************************************
set DEBUGSERVER=C:\ccs\ccsv5\ccs_base
REM *************************************************************************
set PATH=%DEBUGSERVER%\scripting;%XDCROOT%
set PATH=%DEBUGSERVER%\common;%PATH%
set PATH=%DEBUGSERVER%\DebugServer\packages\;%PATH%
set PATH=%DEBUGSERVER%\common\uscif;%PATH%
set PATH=%DEBUGSERVER%\common\IDE;%PATH%
set PATH=%DEBUGSERVER%\common\bin;%PATH%
set PATH=%DEBUGSERVER%\DebugServer\bin\win32;%PATH%
set PATH=%DEBUGSERVER%\DebugServer\win32\components;%PATH%
set XDCPATH=%DEBUGSERVER%/DebugServer/packages;../;../../../imports
REM *************************************************************************
