#******************************************************************************
#*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Soft Isp16 ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Soft Isp16 TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ========  Soft Isp16 ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Soft Isp16 TEST =================
	gmake -C ./test -f makefile clean

