#******************************************************************************
#*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Census ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Census TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ======== Census ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Census TEST =================
	gmake -C ./test -f makefile clean
