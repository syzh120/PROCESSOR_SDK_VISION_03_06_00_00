IF "%1" == "SinglePass" (
del *.bin
for %%X in (*.xml) do ..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    CD OnePassWdr
    for %%X in (*.xml) do ..\..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
copy /b *.bin sensor.bin
..\..\..\..\..\docs\tda3xx\bin2c.exe sensor.bin ..\bspdrv_ov10640Dcc_1pass.h ov10640_1pass
del *.bin
) ELSE (
    del *.bin
    for %%X in (*.xml) do ..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    CD TwoPassWdr
    for %%X in (*.xml) do ..\..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
    copy /b *.bin sensor.bin
    ..\..\..\..\..\docs\tda3xx\bin2c.exe sensor.bin ..\bspdrv_ov10640Dcc.h ov10640
    del *.bin
)


