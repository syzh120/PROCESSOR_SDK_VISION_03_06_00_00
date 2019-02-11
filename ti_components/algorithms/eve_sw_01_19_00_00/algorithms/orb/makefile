#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== ORB ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== ORB TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== ORB ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== ORB TEST =================
	gmake -C ./test -f makefile clean
    
