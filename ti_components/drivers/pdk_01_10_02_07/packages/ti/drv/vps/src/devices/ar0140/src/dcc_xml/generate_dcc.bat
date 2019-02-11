IF "%1" == "SinglePass" (
    del *.bin
    for %%X in (*.xml) do ..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    CD OnePassWdr
    for %%X in (*.xml) do ..\..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
    copy /b *.bin sensor.bin
    ..\..\..\..\..\docs\tda3xx\bin2c.exe sensor.bin ..\bspdrv_ar0140Dcc_1pass.h ar0140_1pass
    del *.bin
) ELSE (
    del *.bin
    for %%X in (*.xml) do ..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    CD TwoPassWdr
    for %%X in (*.xml) do ..\..\..\..\..\..\docs\tda3xx\dcc_gen_win.exe %%X
    MOVE *.bin ..\
    CD ..
    copy /b *.bin sensor.bin
    ..\..\..\..\..\docs\tda3xx\bin2c.exe sensor.bin ..\bspdrv_ar0140Dcc.h ar0140
    del *.bin
)


