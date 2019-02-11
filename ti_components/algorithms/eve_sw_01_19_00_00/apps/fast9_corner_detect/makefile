#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== FAST9 ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== FAST9 TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== FAST9 ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== FAST9 TEST =================
	gmake -C ./test -f makefile clean
	
