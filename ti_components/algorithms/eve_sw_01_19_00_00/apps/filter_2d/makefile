#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Filter 2D ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Filter 2D TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== Filter 2D ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Filter 2D TEST =================
	gmake -C ./test -f makefile clean
	
