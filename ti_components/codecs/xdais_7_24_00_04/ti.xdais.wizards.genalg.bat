@rem See packages/ti/xdais/quality/README.txt for further QualiTI documentation

@rem User: set this variable to point your XDC installation (3.00.05 or newer is recommended).
@if "%XDC_INSTALL_DIR%"=="" set XDC_INSTALL_DIR=c:\xdc_3_00_05

@for %%f in (%0) do @set thisDir=%%~dpf

"%XDC_INSTALL_DIR%\xs" --xdcpath="%thisDir%packages" ti.xdais.wizards.genalg -g %1 %2 %3 %4 %5 %6 %7 %8 %9
