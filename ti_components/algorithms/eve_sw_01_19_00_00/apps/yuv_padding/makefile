#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== YUV PADDING ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== YUV PADDING TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== YUV PADDING ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== YUV PADDING TEST =================
	gmake -C ./test -f makefile clean
	
