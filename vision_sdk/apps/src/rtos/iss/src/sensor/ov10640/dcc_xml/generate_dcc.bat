set DCC_TOOL_PATH=..\..\..\..\..\..\..\tools\dcc_tools
IF "%1" == "SinglePass" (
del *.bin
for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    CD OnePassWdr
    for %%X in (*.xml) do .\..\%DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
copy /b *.bin sensor.bin
%DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\ov10640_dcc_1pass.h ov10640_1pass
del *.bin
) ELSE (
    del *.bin
    for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    CD TwoPassWdr
    for %%X in (*.xml) do .\..\%DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
    copy /b *.bin sensor.bin
    %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\ov10640_dcc.h ov10640
    del *.bin
)


