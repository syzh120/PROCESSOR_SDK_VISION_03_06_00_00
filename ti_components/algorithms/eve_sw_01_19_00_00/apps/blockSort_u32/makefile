#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Block Sort U32 ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Block Sort U32 TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ======== Block Sort U32 ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Block Sort U32 TEST =================
	gmake -C ./test -f makefile clean
