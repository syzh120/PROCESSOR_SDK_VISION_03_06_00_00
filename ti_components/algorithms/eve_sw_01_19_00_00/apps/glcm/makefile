#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== GLCM ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== GLCM TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== GLCM ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== GLCM TEST =================
	gmake -C ./test -f makefile clean
	
