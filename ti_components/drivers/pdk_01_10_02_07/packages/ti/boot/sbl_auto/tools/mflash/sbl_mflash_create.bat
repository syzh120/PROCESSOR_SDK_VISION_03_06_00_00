SET soc=%1
SET profile=release
SET var=%3

IF "%var%"=="" goto default_board
goto main
:default_board
SET var=evm

:main
IF "%soc%"=="" goto soc_3xx
IF "%soc%"=="tda3xx" goto soc_3xx
IF "%soc%"=="tda2px" goto soc_2px
IF "%soc%"=="tda2xx" goto soc_2xx
IF "%soc%"=="tda2ex" goto soc_2ex
ECHO "Invalid SoC"

:soc_3xx
SET soc=tda3xx
SET core=ipu1_0
SET ext=xem4
goto commonexit

:soc_2xx
SET soc=tda2xx
SET core=a15_0
SET ext=xa15fg
goto commonexit

:soc_2px
SET soc=tda2px
SET core=a15_0
SET ext=xa15fg
goto commonexit

:soc_2ex
SET soc=tda2ex
SET core=a15_0
SET ext=xa15fg
goto commonexit

:commonexit
SET EXTERNAL_SW_ROOT = C:
SET PDK_ROOTDIR=%PWD%\..\..\..\..

SET Gcc_Tools_Path=%EXTERNAL_SW_ROOT%\gcc-arm-none-eabi-4_9-2015q3\bin

SET Sbl_Elf_Path=%PDK_ROOTDIR%\binary\sbl\mflash_uart\%soc%-%var%
SET Sbl_Out_Path=%PWD%\mflash_%soc%

IF NOT EXIST %Sbl_Out_Path%\ mkdir %Sbl_Out_Path%

DEL %Sbl_Out_Path%\sbl_mflash

"%Gcc_Tools_Path%\arm-none-eabi-objcopy.exe" --gap-fill=0xff -O binary %Sbl_Elf_Path%\sbl_mflash_uart_%core%_%profile%.%ext% %Sbl_Out_Path%\SBL.bin

rename %Sbl_Out_Path%\SBL.bin %Sbl_Out_Path%\sbl_mflash_%soc%-%var%
