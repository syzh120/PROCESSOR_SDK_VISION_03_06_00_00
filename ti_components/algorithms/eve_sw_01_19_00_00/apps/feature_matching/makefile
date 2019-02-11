#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== FEATURE MATCHING ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== FEATURE MATCHING TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== FEATURE MATCHING ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== FEATURE MATCHING TEST =================
	gmake -C ./test -f makefile clean
	
