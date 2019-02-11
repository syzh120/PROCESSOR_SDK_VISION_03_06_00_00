#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Median Filter ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Median Filter TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ======== Median Filter ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Median Filter TEST =================
	gmake -C ./test -f makefile clean
