#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Edge Detector ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Edge Detector TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== Edge Detector ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Edge Detector TEST =================
	gmake -C ./test -f makefile clean
	
