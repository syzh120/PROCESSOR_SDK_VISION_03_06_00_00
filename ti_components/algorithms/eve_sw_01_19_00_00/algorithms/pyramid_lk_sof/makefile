#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

all:
	@echo .
	@echo ======== Pyramid LK SOF ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Pyramid LK SOF TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
#ifneq ($(TARGET_PLATFORM) , PC)
#	@echo .
#	@echo ======== EVE ALGORITHMS TEST =================
#	gmake -C ./test -f makefile clean
#	@echo .
#	@echo ======== EVE ALGORITHMS =================
#	gmake -C ./src -f makefile clean
#endif
	@echo .
	@echo ======== Pyramid LK SOF ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Pyramid LK SOF TEST =================
	gmake -C ./test -f makefile clean
