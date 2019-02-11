#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== EVE NON BAM APPLETS =================
	gmake -C ./src -f makefile
	@echo .
	@echo ======== EVE NON BAM APPLETS TEST =================
	gmake -C ./test -f makefile
	@echo .
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== EVE NON BAM APPLETS TEST =================
	gmake -C ./test -f makefile clean
	@echo .
	@echo ======== EVE NON BAM APPLETS =================
	gmake -C ./src -f makefile clean
	@echo .	
