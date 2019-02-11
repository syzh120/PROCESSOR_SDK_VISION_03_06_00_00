sbl_mflash="sbl_mflash_tda2ex-evm"
board="tda2exevm"
appimage_location="AppImage_BE"
appimage_offset="0x80000"
sbl_location="sbl"
sbl_offset="0x00"
uart_port_number="14"
sudo ./mflash -M $sbl_mflash -S $board -P $uart_port_number -F $appimage_location $appimage_offset -F $sbl_location $sbl_offset -C
