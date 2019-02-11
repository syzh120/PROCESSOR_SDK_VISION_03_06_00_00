#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Hough For Lines ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== Hough For Lines TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== Hough For Lines ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== Hough For Lines TEST =================
	gmake -C ./test -f makefile clean
	
