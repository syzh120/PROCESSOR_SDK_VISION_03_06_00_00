#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Peak Detection ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Peak Detection TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== Peak Detection ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Peak Detection	 TEST =================
	gmake -C ./test -f makefile clean
	
