set DCC_TOOL_PATH=..\..\..\..\..\..\..\tools\dcc_tools
IF "%1" == "SinglePass" (
    del *.bin
    for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    CD OnePassWdr
    for %%X in (*.xml) do .\..\%DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
    copy /b *.bin sensor.bin
    %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\ar0140_dcc_1pass.h ar0140_1pass
    del *.bin
) ELSE (
    del *.bin
    for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    CD TwoPassWdr
    for %%X in (*.xml) do .\..\%DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
    copy /b *.bin sensor.bin
    %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\ar0140_dcc.h ar0140
    del *.bin
)


