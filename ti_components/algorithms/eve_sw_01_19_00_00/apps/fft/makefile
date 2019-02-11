#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== FFT ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== FFT TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== FFT ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== FFT	 TEST =================
	gmake -C ./test -f makefile clean
	
