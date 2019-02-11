#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Image Pyramid ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Image Pyramid TEST =================
	gmake -C ./test -f makefile

.IGNORE: clean
clean:
	@echo .
	@echo ======== Image Pyramid ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Image Pyramid TEST =================
	gmake -C ./test -f makefile clean
