@echo off

call common_variables.bat
    
xs -Dxpcom.bridge.executeOnDedicatedThread=yes -Dorg.eclipse.swt.browser.XULRunnerPath="%DEBUGSERVER%/DebugServer/win32" -DXPCOM.RUNTIME="%DEBUGSERVER%/DebugServer/win32" -f %1 %~d0/%~p0/settings.xs %2 %3
