#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Harris Corner Detection ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Harris Corner Detection TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ======== Harris Corner Detection ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Harris Corner Detection TEST =================
	gmake -C ./test -f makefile clean
