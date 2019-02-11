SET sbl_mflash="sbl_mflash_tda2ex-evm"
SET board="tda2exevm"
SET appimage_location="AppImage_BE"
SET appimage_offset="0x80000"
SET sbl_location="sbl"
SET sbl_offset="0x00"
SET uart_port_number="34"
ECHO %time%
mflash -S %board% -M %sbl_mflash% -P %uart_port_number% -F %appimage_location% %appimage_offset% -F %sbl_location% %sbl_offset% -C
