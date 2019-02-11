#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== TI PD FEATURE PLANE COMPUTATION ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== TI PD FEATURE PLANE COMPUTATION TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== TI PD FEATURE PLANE COMPUTATION ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== TI PD FEATURE PLANE COMPUTATION TEST =================
	gmake -C ./test -f makefile clean
	
