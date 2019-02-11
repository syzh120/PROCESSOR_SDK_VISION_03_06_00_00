set DCC_TOOL_PATH=..\..\..\..\..\..\..\..\tools\dcc_tools
IF "%1" == "SinglePass" (
    CD wdr_1Pass
    del *.bin
    for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
    copy /b *.bin sensor.bin
    %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\..\imx390_dcc_1PassWDR.h.h imx390_1Pass
    del *.bin
    CD ..
) ELSE (
    IF "%1" == "TwoPassWDR" (
        CD wdr_2Pass
        del *.bin
        for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
        copy /b *.bin sensor.bin
        %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\..\imx390_dcc_2PassWDR.h imx390_2Pass
        del *.bin
        CD ..
    ) ELSE (
        IF "%1" == "Linear" (
            CD linear
            del *.bin
            for %%X in (*.xml) do %DCC_TOOL_PATH%\dcc_gen_win.exe %%X
            copy /b *.bin sensor.bin
            %DCC_TOOL_PATH%\bin2c.exe sensor.bin ..\..\imx390_dcc_linear.h imx390
            del *.bin
            CD ..
        ) ELSE (
            echo "Unsupported Argument"
        )
    )
)


