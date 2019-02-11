#******************************************************************************
#*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== disparity ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== disparity TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ======== disparity ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== disparity TEST =================
	gmake -C ./test -f makefile clean
