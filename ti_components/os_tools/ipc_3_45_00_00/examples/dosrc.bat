@echo off
REM  This file is not required. It is optional.
REM  Use it to customize your Windows build environment.

set system=C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem
set xdctools=C:\Products\xdctools_3_30_04_52_core

PATH=%system%;%xdctools%;%xdctools%\bin
prompt $p$g 

doskey alias=doskey /macros
doskey make="%xdctools%\gmake.exe" $*
doskey xdc="%xdctools%\xdc.exe" $*
doskey xs="%xdctools%\xs.exe" $*

REM Cannot use doskey macro for tee command.
REM Note: Cannot use ^ with 2>&1 redirection.
REM make 2>&1 | %tee% Make.log
set tee=%xdctools%\bin\tee.exe

set system=
set xdctools=
