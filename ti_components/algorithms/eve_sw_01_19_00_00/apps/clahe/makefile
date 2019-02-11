#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== CLAHE U8 ALGO =================
	gmake -C ./algo -f makefile

	@echo ======== CLAHE U8 TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== CLAHE U8 ALGO =================
	gmake -C ./algo -f makefile clean

	@echo ======== CLAHE U8 TEST =================
	gmake -C ./test -f makefile clean
	
