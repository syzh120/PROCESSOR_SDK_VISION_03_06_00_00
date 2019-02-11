@echo off

call common_variables.bat
    
xs -Dxpcom.bridge.executeOnDedicatedThread=yes -Dorg.eclipse.swt.browser.XULRunnerPath="%DEBUGSERVER%/../eclipse/xulrunner" -DXPCOM.RUNTIME="%DEBUGSERVER%/DebugServer/bin" -f %1 %~d0/%~p0/settings.xs %2 %3 %4 %5 %6 %7 