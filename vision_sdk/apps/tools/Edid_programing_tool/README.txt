EDID programming steps
===========================

Programs EDID for 1080p-60.
TDA2x: 'edid_programming_tda2x_1080p_60.xa15fg' 
TDA3x: 'edid_programmer_tda3x_1080p_60.xem4' 

Refer User Guide for more details

TDA2x Execution steps
---------------------
1. Change pins 1 and 2 of SW1 (on vision app board, near CPLD2) to ON.
2. Connect UART cable from board to PC and setup UART for logs (11500 baud).
3. Connect CCS to a15 core and load 'edid_programming_tda2x_1080p_60.xa15fg' binary.
4. Run the core and wait till "EDID programming successfull" message comes on UART.
5. Before Running Vision SDK binaries, change pins 1 and 2 of SW1 to OFF (towards numbers 1 and 2).

TDA3x Execution steps
---------------------
1. Change pins 1 and 2 of SW8000 (near HDMI IN connector) to ON.
2. Connect UART cable from board to PC and setup UART for logs (11500 baud).
3. Connect CCS to IPU1-0 core and load 'edid_programmer_tda3x_1080p_60.xem4' binary.
4. Run the core and wait till "EDID programming successfull" message comes on UART.
5. Before Running Vision SDK binaries, change pins 1 and 2 of SW8000 to OFF (towards numbers 1 and 2).