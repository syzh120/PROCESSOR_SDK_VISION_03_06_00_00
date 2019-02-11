#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Pyramid LK Tracker APPLET =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Pyramid LK Tracker TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== Pyramid LK Tracker APPLET =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Pyramid LK Tracker TEST =================
	gmake -C ./test -f makefile clean
	
