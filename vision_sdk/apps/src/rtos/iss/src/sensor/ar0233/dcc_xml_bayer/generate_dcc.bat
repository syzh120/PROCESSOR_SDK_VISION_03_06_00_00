set DCC_TOOL_PATH=..\..\..\..\..\..\..\tools\dcc_tools
    del *.bin
    for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    copy /b *.bin sensor.bin
    %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\ar0233_dcc.h ar0233
    del *.bin

