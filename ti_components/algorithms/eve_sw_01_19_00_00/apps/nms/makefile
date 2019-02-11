#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== nms ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== nms TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== nms ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== nms TEST =================
	gmake -C ./test -f makefile clean
	
