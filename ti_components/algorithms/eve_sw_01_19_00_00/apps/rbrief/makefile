#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== RBRIEF ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== RBRIEF TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== RBRIEF ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== RBRIEF TEST =================
	gmake -C ./test -f makefile clean
	
