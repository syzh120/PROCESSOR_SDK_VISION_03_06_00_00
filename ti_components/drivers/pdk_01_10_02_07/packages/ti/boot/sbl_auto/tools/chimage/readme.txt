Steps to create TDA3x Configuration Header for QSPI4 boot Mode at 64MHz.

1. Create binary image(sbl.bin) with GP Header for QSPI4 boot mode.
2. Create a new binary(sbl.bin.ch) by combining tda3x_chqspi_clock64mhz.bin binary at offset 0x0 and 
   QSPI4 binary image(sbl.bin) at offset 0x200.
   (GP header of QSPI4 image should be at offset 0x200 in sbl.bin.ch)
3. Program flash memory with sbl.bin.ch image, for QSPI4 boot mode at 64MHz. 