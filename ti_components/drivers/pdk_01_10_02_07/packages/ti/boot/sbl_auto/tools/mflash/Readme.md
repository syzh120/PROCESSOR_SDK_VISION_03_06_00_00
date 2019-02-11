# Building mflash for TDA3xx

To build mflash in any environment a gcc compiler is required. Go to the directory pdk/packages/ti/boot/sbl_auto/tools/mflash
and run the following command to build the executable named “mflash”

$ gcc -o mflash mflash_uart.c

The executable mflash will be created in the same directory


# Flashing TDAxx via UART interface

To Flash sbl and AppImage in TDAxx in Peripheral Boot Mode:
1.  Build sbl_mflash and mflash for TDAxx if not already built as described in AppNote_mflash.
2.  Make the following connections:
    •   Connect a serial cable to the UART port of the EVM and the other end to the serial port of the PC
    •   For TDA3xx-evm, change the sysboot switches SW2[0:7] and SW3[8:15] to [00010000][100000001] and SW8 to [01000001]
    •   For TDA2xx-evm, change the sysboot switches SW2[0:7] and SW3[8:15] to [11001000][100000001] and SW5 to [00010000]
    •   For TDA2px-evm, change the sysboot switches SW3[0:7] and SW4[8:15] to [11001000][100000001] and SW6 to [00000000]
    •   For TDA2ex-evm, change the sysboot switches SW3[0:7] and SW4[8:15] to [11001000][100000001]
    •   For TDA3xx-rvp, no sys-boot settings are required
    •   Connect and Power Reset the board
3.  Note the appropriate COM Port as described previously.
4.  Reset the board
5.  Run the mflash_run_config.sh(.bat) file after providing appropriate parameters.
                                    OR
       Provide your own command in the following syntax:
$ ./mflash  -M <sbl_mflash_path   >             [Required]  {to give sbl_mflash path}
            -P <port_number>                    [Required]  {UART3 port_number}
            -S <soc>                            [Required]  {tda2px or tda3xx}
            -F <file_location> <file_offset>    [Required]  {file location and offset}
            -F <file_location> <file_offset>    [Optional]  
            -C                                  [Optional]  {to clear the flash memory}
e.g. mflash -M “sbl_mflash_tda3xx” -P “5” -S "tda3xx" -F “AppImage_BE” “0x80000” -F “sbl” “0x00” -C
6. Put the board in qspi boot mode(change the switch settings) and restart it to boot the sbl and AppImage from flash.

# Building sbl_mflash

To build sbl_mflash (sbl that is sent by PC side mflash utility to ROM code over uart)
1. Go to pdk/packages/ti/build
2. Use following build command for tda3xx-evm
    $ make -s -j sbl BOARD=tda3xx-evm BOOTMODE=uart SBL_TYPE=mflash
   Use following build command for tda2px-evm
    $ make -s -j sbl BOARD=tda2px-evm CORE=a15_0 BOOTMODE=uart SBL_TYPE=mflash
   Use following build command for tda2xx-evm
    $ make -s -j sbl BOARD=tda2xx-evm CORE=a15_0 BOOTMODE=uart SBL_TYPE=mflash
   Use following build command for tda2ex-evm
    $ make -s -j sbl BOARD=tda2ex-evm CORE=a15_0 BOOTMODE=uart SBL_TYPE=mflash
   Use following build command for tda3xx-rvp
    $ make -s -j sbl BOARD=tda3xx-rvp BOOTMODE=uart SBL_TYPE=mflash
3. Go to pdk/packages/ti/boot/sbl_auto/tools/mflash
    a. Ensure paths and profile mentioned in the script is right
    b. Execute sbl_mflash_create.sh(.bat) <soc_name> <profile> <boardType>
        e.g. sbl_mflash_create.sh tda3xx debug evm
4. sbl_mflash_<soc>-<boardType> is created in the same folder.
