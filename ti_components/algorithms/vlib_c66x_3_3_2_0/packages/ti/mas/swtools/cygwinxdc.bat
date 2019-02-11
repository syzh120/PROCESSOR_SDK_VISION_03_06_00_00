@echo off
rem # *************************************************************************
rem #  FILE           : cygwinxdc.bat
rem #  DESCRIPTION    :
rem #
rem #     This DOS batch scripts ensures all tools required to compile nmu
rem #     are locally available or synchronized with the tools at server T:
rem #     This batch script should be run first before compiling nmu
rem #
rem # *************************************************************************

rem # *************************************************************************
rem # *** Set up tools version (which are root directory)
rem # *************************************************************************

@if  "%C54CODEGENBASE%"=="" (
   set C54CODEGENBASE=4-10
   )
@if  "%C55CODEGENBASE%"=="" (
   set C55CODEGENBASE=cgen401
   )
@if  "%C64CODEGENBASE%"=="" (
   set C64CODEGENBASE=cgen7_2_06
   )
@if  "%C674CODEGENBASE%"=="" (
   set C674CODEGENBASE=cgen7_2_06
   )
@if  "%C66CODEGENBASE%"=="" (
   set C66CODEGENBASE=cgen7_2_06
   )
@if  "%ARMCODEGENBASE%"=="" (
   set ARMCODEGENBASE=tms470
   )
@if  "%XDCBASE%"=="" (
   set XDCBASE=xdctools_3_20_05_76
   )
@if  "%COVBASE%"=="" (
   set COVBASE=prevent-mingw-3.8.0
   )
@if  "%PERLBASE%"=="" (
   set PERLBASE=gen\perl\activestate\5_6_1_635
   )
@if  "%XDAISBASE%"=="" (
   set XDAISBASE=xdais_5_21
   )
@if  "%SDOARCHBASE%"=="" (
   set SDOARCHBASE=sdoarch_standards_1_00_00
   )
@if  "%DOXYGENBASE%"=="" (
   set DOXYGENBASE=1.5.1-p1
   )
@if  "%GRAPHVIZBASE%"=="" (
   set GRAPHVIZBASE=2.12
   )
@if  "%HTML_HELP_WORKSHOP_BASE%"=="" (
   set HTML_HELP_WORKSHOP_BASE=10-01-2007
   )
@if  "%TI_TEMPLATES_BASE%"=="" (
   set TI_TEMPLATES_BASE=10-01-2007
   )
@if  "%SDOAPPSBASE%"=="" (
   set SDOAPPSBASE=cg_xml_v1_20_00
   )
@if  "%PHPBASE%"=="" (
   set PHPBASE=PHP_5_3_2_1000
   )
@if  "%ECLIPSEPLUGIN%"=="" (
   set ECLIPSEPLUGIN=xdc_eclipse_plugin_gen\20091203
   )
@if  "%INSTALLJAMMER%"=="" (
   set INSTALLJAMMER=InstallJammer\v1_2_15
   )
@if  "%CCSCGTVER%"=="" (
   set CCSCGTVER=7.2.6
   )
@if  "%CCSCGTVERC55%"=="" (
   set CCSCGTVERC55=4.3.8
   )
@if  "%CCSVERSION%"=="" (
   set CCSVERSION=CCSV4.2
   )
@if  "%CCSV4_INSTALL_DIR%"=="" (
   set CCSV4_INSTALL_DIR=c:/Program Files/Texas Instruments/ccsv4
   )
 if  "%CCSV5_INSTALL_DIR%"=="" (
   set CCSV5_INSTALL_DIR=c:/Program Files/Texas Instruments/ccsv5
   )  
@if  "%CGT_INSTALL_DIR%"=="" (
   set CGT_INSTALL_DIR=c:/Program Files/Texas Instruments/C6000 Code Generation Tools 7.2.6
   )

rem # *************************************************************************
rem # *** Tools Drive ***
rem # *************************************************************************
set LOCAL_TOOLSDIR_DOS=C:\tools
set LOCAL_TOOLSDIR_UNIX=//C/tools
set LOCAL_TOOLSDIR_GNUWIN=C:/tools
set TOOLSDRIVE_DOS=T:
set TOOLSDRIVE_UNIX=//T

rem # *************************************************************************
rem # *** cpytool.pl ***
rem # *************************************************************************
set CPYTOOLS=..\swtools\cpytools.pl

rem # *************************************************************************
rem # *** PERL ***
rem #
rem # NOTE: If you wish to run perl from your local hard drive, you must
rem #       relocate perl to local drive. To relocate perl, go to 
rem #       T:\gen\perl\activestate\5_6_1_635\bin and run 
rem #       "reloc_perl -t -a C:\tools\gen\perl\activestate\5_6_1_635 
rem #       T:\gen\perl\activestate\5_6_1_635".
rem #       This will install perl in C:\tools. You can change the following
rem #       two paths to point to C:\tools\gen\perl\activestate\5_6_1_635.
rem #
rem #       CCPERL cannot run reflection page script (clrcase/refpage/refpage.pl)
rem #       because it has a bug in its regexp engine that crashes on some of 
rem #       the complicated regexp in the script.
rem #
rem # *************************************************************************
set PERLEXE=%PERLBASE%\bin\perl.exe

if not exist "%LOCAL_TOOLSDIR_DOS%\%PERLEXE%" goto remoteperl

:localperl
rem # ** Currently perl is run from the local copy
set PERLDOS=%LOCAL_TOOLSDIR_DOS%\%PERLEXE%
set PERLPATH=%LOCAL_TOOLSDIR_DOS%\%PERLBASE%
goto endperl

:remoteperl
rem # ** Currently perl is run from the networked copy
set PERLDOS=%TOOLSDRIVE_DOS%\%PERLEXE%
set PERLPATH=%TOOLSDRIVE_DOS%\%PERLBASE%

:endperl

rem # *************************************************************************
rem # ** Create source and destination for all tools required to compile nmu
rem # ** nmu needs XDC, CGEN, and XDAIS
rem # *************************************************************************

rem # XDC Tools
set TOOLXDCSRC=%TOOLSDRIVE_DOS%\gen\xdc\%XDCBASE%
set TOOLXDCDST=%LOCAL_TOOLSDIR_DOS%\gen\xdc\%XDCBASE%

rem # Coverity
set TOOLCOVSRC=%TOOLSDRIVE_DOS%\gen\coverity\%COVBASE%
set TOOLCOVDST=%LOCAL_TOOLSDIR_DOS%\gen\coverity\%COVBASE%
set COVPATH=%TOOLCOVDST%

rem # C54 Codegen Tools
set TOOLC54XSRC=%TOOLSDRIVE_DOS%\c54x\ti-c\%C54CODEGENBASE%\cgtools
set TOOLC54XDST=%LOCAL_TOOLSDIR_DOS%\c54x\ti-c\%C54CODEGENBASE%\cgtools
set C54CODEGENTOOL=%TOOLC54XDST%

rem # C55 Codegen Tools
set TOOLC55XSRC=%TOOLSDRIVE_DOS%\c5xx\%C55CODEGENBASE%\c5500
set TOOLC55XDST=%LOCAL_TOOLSDIR_DOS%\c5xx\%C55CODEGENBASE%\c5500
set C55CODEGENTOOL=%TOOLC55XDST%\cgtools

rem # C64+ Codegen Tools
set TOOLC64XPLUSSRC=%TOOLSDRIVE_DOS%\c6xx\%C64CODEGENBASE%\c6000
set TOOLC64XPLUSDST=%LOCAL_TOOLSDIR_DOS%\c6xx\%C64CODEGENBASE%\c6000
set C64CODEGENTOOL=%TOOLC64XPLUSDST%\cgtools

rem # C674x Codegen Tools
set TOOLC674XSRC=%TOOLSDRIVE_DOS%\c6xx\%C674CODEGENBASE%\c6000
set TOOLC674XDST=%LOCAL_TOOLSDIR_DOS%\c6xx\%C674CODEGENBASE%\c6000
set C674CODEGENTOOL=%TOOLC674XDST%\cgtools

rem # C66x Codegen Tools
set TOOLC66XSRC=%TOOLSDRIVE_DOS%\c6xx\%C66CODEGENBASE%\c6000
set TOOLC66XDST=%LOCAL_TOOLSDIR_DOS%\c6xx\%C66CODEGENBASE%\c6000
set C66CODEGENTOOL=%TOOLC66XDST%\cgtools

rem # ARM Codegen Tools
rem #set Arm11TITool=C:\Program Files\Texas Instruments\CCSv4\tools\compiler\tms470



rem # DSP/BIOS
set TOOLXDAISSRC=%TOOLSDRIVE_DOS%\Xdais\%XDAISBASE%
set TOOLXDAISDST=%LOCAL_TOOLSDIR_DOS%\Xdais\%XDAISBASE%

rem # SDO Architecture
set SDOARCHSRC=%TOOLSDRIVE_DOS%\gen\xdcgtx\%SDOARCHBASE%
set SDOARCHDST=%LOCAL_TOOLSDIR_DOS%\gen\xdcgtx\%SDOARCHBASE%

rem # SDO APPS
set SDOAPPSSRC= %TOOLSDRIVE_DOS%\SDOApps\cg_xml\%SDOAPPSBASE%\bin
set SDOAPPSDST= %LOCAL_TOOLSDIR_DOS%\SDOApps\cg_xml\%SDOAPPSBASE%\bin

rem # Doxygen
set TOOLDOXYGENSRC=%TOOLSDRIVE_DOS%\Doxygen\doxygen\%DOXYGENBASE%
set TOOLDOXYGENDST=%LOCAL_TOOLSDIR_DOS%\Doxygen\doxygen\%DOXYGENBASE%

rem # Graphviz
set TOOLGRAPHVIZSRC=%TOOLSDRIVE_DOS%\Doxygen\Graphviz\%GRAPHVIZBASE%
set TOOLGRAPHVIZDST=%LOCAL_TOOLSDIR_DOS%\Doxygen\Graphviz\%GRAPHVIZBASE%

rem # HTML Help Workshop
set TOOLHTMLHWSRC=%TOOLSDRIVE_DOS%\Doxygen\HTML_Help_Workshop\%HTML_HELP_WORKSHOP_BASE%
set TOOLHTMLHWDST=%LOCAL_TOOLSDIR_DOS%\Doxygen\HTML_Help_Workshop\%HTML_HELP_WORKSHOP_BASE%

rem # TI_Templates
set TOOLTITEMPSRC=%TOOLSDRIVE_DOS%\Doxygen\TI_Templates\%TI_TEMPLATES_BASE%
set TOOLTITEMPDST=%LOCAL_TOOLSDIR_DOS%\Doxygen\TI_Templates\%TI_TEMPLATES_BASE%
set TI_DOXYGEN_TEMPLATES=%LOCAL_TOOLSDIR_GNUWIN%/Doxygen/TI_Templates/%TI_TEMPLATES_BASE%


if "%PERLDOS%" == "" goto environment

rem # *************************************************************************
rem # *** Tools Copy / Validation ***
rem # *************************************************************************

rem # If "bypass" option is provided the skip tools validation
if "%1" == "bypass" goto environment

rem # If "bypass" option is not provided them validate the tools, but don't copy
if "%1" == "" goto toolcheck

rem # If "enable_write" is specified copy the tools
if "%1" == "enable_write" goto toolcopy

rem # Invalid argument supplied
echo ERROR: Option "%1" supplied is invalid...
echo .
echo . Usage: %0 [bypass enable_write]
echo .
echo .     "bypass"       : Configures environment without checking the tools
echo .     "enable_write" : Erase non-matching files and replace with correct tools
goto end

:toolcheck
echo Verifying local tools...
goto toolperl

:toolcopy
echo Updating local tools...

:toolperl

rem # NOTE: in windows "errorlevel 1" means "retval >= 1"

%PERLDOS% %CPYTOOLS% %TOOLXDCSRC% %TOOLXDCDST% %1
rem note: "errorlevel 1" means "retval >= 1"
if errorlevel 1 goto error

rem # Verify or copy Coverity Prevent static analysis tool
%PERLDOS% %CPYTOOLS% %TOOLCOVSRC% %TOOLCOVDST% %1
rem note: "errorlevel 1" means "retval >= 1"
if errorlevel 1 goto error

rem # Verify or copy the codegen tools
%PERLDOS% %CPYTOOLS% %TOOLC54XSRC% %TOOLC54XDST% %1
if errorlevel 1 goto error

%PERLDOS% %CPYTOOLS% %TOOLC55XSRC% %TOOLC55XDST% %1
if errorlevel 1 goto error

%PERLDOS% %CPYTOOLS% %TOOLC64XPLUSSRC% %TOOLC64XPLUSDST% %1
if errorlevel 1 goto error

%PERLDOS% %CPYTOOLS% %TOOLC66XSRC% %TOOLC66XDST% %1
if errorlevel 1 goto error

%PERLDOS% %CPYTOOLS% %TOOLC674XSRC% %TOOLC674XDST% %1
if errorlevel 1 goto error

rem # Verify or copy XDAIS
%PERLDOS% %CPYTOOLS% %TOOLXDAISSRC% %TOOLXDAISDST% %1
if errorlevel 1 goto error

rem # Verify or copy SDO Architecture
%PERLDOS% %CPYTOOLS% %SDOARCHSRC% %SDOARCHDST% %1
if errorlevel 1 goto error

rem # Verify or copy SDO APPS
%PERLDOS% %CPYTOOLS% %SDOAPPSSRC% %SDOAPPSDST% %1
if errorlevel 1 goto error



rem # Verify or copy Doxygen\Doxygen
%PERLDOS% %CPYTOOLS% %TOOLDOXYGENSRC% %TOOLDOXYGENDST% %1
if errorlevel 1 goto error

rem # Verify or copy Doxygen\Graphviz
%PERLDOS% %CPYTOOLS% %TOOLGRAPHVIZSRC% %TOOLGRAPHVIZDST% %1
if errorlevel 1 goto error

rem # Verify or copy Doxygen\HTML_Help_Workshop
%PERLDOS% %CPYTOOLS% %TOOLHTMLHWSRC% %TOOLHTMLHWDST% %1
if errorlevel 1 goto error

rem # Verify or copy Doxygen\TI_Templates
%PERLDOS% %CPYTOOLS% %TOOLTITEMPSRC% %TOOLTITEMPDST% %1

if errorlevel 1 goto error

echo Local tools are good...

rem # **************************************************************************
rem # Establish environment
rem # **************************************************************************

:environment

rem # *************************************************************************
rem # ** Set the PATH
rem # *************************************************************************

rem # Windows path
set PATH=%SystemRoot%;%SystemRoot%\system32

rem # Add XDC path
set PATH=%PATH%;%LOCAL_TOOLSDIR_DOS%\gen\xdc\%XDCBASE%

rem # Add PHP path
set PATH=%PATH%;%TOOLSDRIVE_DOS%\gen\php\%PHPBASE%
set PHPRC=%TOOLSDRIVE_DOS%\gen\php\%PHPBASE%

rem # Add clearcase path
set PATH=%PATH%;C:\Program Files\Rational\ClearCase\bin;C:\Program Files\Rational\common;C:\Program Files\IBM\RationalSDLC\common;C:\Program Files\IBM\RationalSDLC\ClearCase\bin

rem # Add install jammer path
set INSTALLJAMBASE=T:\gen\%INSTALLJAMMER%
set PATH=%PATH%;%INSTALLJAMBASE%

rem # Add Doxygen path
set PATH=%PATH%;%LOCAL_TOOLSDIR_DOS%\Doxygen\doxygen\%DOXYGENBASE%\bin
set PATH=%PATH%;%LOCAL_TOOLSDIR_DOS%\Doxygen\Graphviz\%GRAPHVIZBASE%\bin
set PATH=%PATH%;%LOCAL_TOOLSDIR_DOS%\Doxygen\HTML_Help_Workshop\%HTML_HELP_WORKSHOP_BASE%
set PATH=%PATH%;%LOCAL_TOOLSDIR_DOS%\SDOApps\cg_xml\cg_xml_v1_20_00\bin

rem # Add GNU tools path
set PATH=%PATH%;T:\gen\gnu\99-11-01\cygwin-b20\H-i586-cygwin32\bin

rem # Add PERL path
set PATH=%PATH%;%PERLPATH%\bin

rem # Add CCSV4 Java Path
set PATH=C:\Program Files\Texas Instruments\ccsv4\eclipse\jre\bin;%PATH%

rem # *************************************************************************
rem # ** Create environment variables for XDC
rem # *************************************************************************
set XDCCGROOT=C:/tools/
rem # After RTSC tools have been set up properly the drive letter should be removed
set xdc=\tools\gen\xdc\%XDCBASE%\xdc.exe $*

rem # set XDAIS path
set XDAIS_INSTALL_DIR=%LOCAL_TOOLSDIR_DOS%\Xdais\%XDAISBASE%
set XDCPATH=%XDAIS_INSTALL_DIR%\packages

rem # set Eclipse plugin path
set ECLIPSE_PLUGIN_INSTALL_DIR=%TOOLSDRIVE_DOS%\gen\xdc\%ECLIPSEPLUGIN%
set XDCPATH=%XDCPATH%;%ECLIPSE_PLUGIN_INSTALL_DIR%

rem # set SDO Architecture path
rem #set SDO_ARCH_INSTALL_DIR=%LOCAL_TOOLSDIR_DOS%\gen\xdcgtx\%SDOARCHBASE%
rem #set XDCPATH=%XDCPATH%;%SDO_ARCH_INSTALL_DIR%\packages

rem # set XDC path
set XDC_INSTALL_DIR=%LOCAL_TOOLSDIR_DOS%\gen\xdc\%XDCBASE%
set XDCPATH=%XDCPATH%;%XDC_INSTALL_DIR%\packages



rem # set config.bld for XDC
xs -f setconfig.js
if errorlevel 1 goto end

rem # call tempcfg.bat
call tempcfg
rem # remove tempcfg.bat
rm tempcfg.bat

echo Environment successfully configured...
echo .
echo .  XDCVERSION          = %XDCBASE%
echo .  COVERITY VERSION    = %COVBASE%
echo .  C54 CODEGENVERSION  = %C54CODEGENBASE%
echo .  C55 CODEGENVERSION  = %C55CODEGENBASE%
echo .  C64 CODEGENVERSION  = %C64CODEGENBASE%
echo .  C674 CODEGENVERSION  = %C674CODEGENBASE%
echo .  C66 CODEGENVERSION  = %C66CODEGENBASE%
echo .  SDO ARCHITECTURE    = %SDOARCHBASE%
echo .  XDAISVERSION        = %XDAISBASE%
echo .  XDCCGROOT           = %XDCCGROOT%
echo .  DOXYGENVERSION      = %DOXYGENBASE%
echo .  GRAPGVIZVERSION     = %GRAPHVIZBASE%
echo .  HTMLHELPWORKSHOP    = %HTML_HELP_WORKSHOP_BASE%
echo .  TITEMPLATES         = %TI_TEMPLATES_BASE%
echo .

rem # MSVC Codegen Tools
@if not "%VS100COMNTOOLS%"=="" (
   set VC98TOOL=%VS100COMNTOOLS%/../../
   @call "%VS100COMNTOOLS%/vsvars32.bat"
   )

goto end

rem ************************** Bad Tools *************************************
rem Tools are bad; deconfigure environment and print error
rem **************************************************************************
:error

set MAKEDEPPATH=

echo .
echo .
echo . ERROR: Bad tools. Build environment is NOT configured. 
echo .        You may re-run the script with following options:
echo .
echo . %0 bypass
echo . 
echo .    This option configures the environment without checking the tools.
echo .    This is used when user manually configures the tools.
echo .
echo . %0 enable_write
echo .
echo .    [CAUTION]: 1) This option recursively deletes non-identical files in the 
echo .                  following directories:
echo .                  %TOOLXDCDST%
echo .                  %TOOLCOVDST%
echo .                  %TOOLC54XDST%
echo .                  %TOOLC55XDST%
echo .                  %TOOLC64XPLUSDST% 
echo .                  %SDOARCHDST% 
echo .                  %TOOLXDAISDST%
echo .
echo .               2) And copies the unmatched files from the following directories.
echo .                  %TOOLXDCSRC%
echo .                  %TOOLCOVSRC%
echo .                  %TOOLC54XSRC%
echo .                  %TOOLC55XSRC%
echo .                  %TOOLC64XPLUSSRC% 
echo .                  %SDOARCHSRC% 
echo .                  %TOOLXDAISSRC%
echo .

goto end

:end

rem # *************************************************************************
rem # Remove all unused environment variables
rem # *************************************************************************
set CPYTOOLS=
set LOCAL_TOOLSDIR_DOS=
set LOCAL_TOOLSDIR_UNIX=
set TOOLSDRIVE_DOS=
set TOOLSDRIVE_UNIX=
set PERLEXE=
set PERLDOS=
set PERLPATH=
set TOOLXDCSRC=
set TOOLXDCDST=
set TOOLCOVSRC=
set TOOLCOVDST=
set TOOLC64XPLUSSRC=
set TOOLC64XPLUSDST=
set TOOLC674XSRC=
set TOOLC674XDST=
set TOOLC66XSRC=
set TOOLC66XDST=
set TOOLC XDST=
set TOOLXDAISSRC=
set TOOLXDAISDST=
set SDOARCHSRC=
set SDOARCHDST=
set SDOAPPSSRC=
set SDOAPPSSRC=
set TOOLDOXYGENSRC=
set TOOLDOXYGENDST=
set TOOLGRAPHVIZSRC=
set TOOLGRAPHVIZDST=
set TOOLHTMLHWSRC=
set TOOLHTMLHWDST=
set TOOLTITEMPSRC=
set TOOLTITEMPDST=

rem # End of file

