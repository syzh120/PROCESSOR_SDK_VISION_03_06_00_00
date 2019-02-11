#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== BEAM FORMING ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======== BEAM FORMING TEST =================
	gmake -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== BEAM FORMING ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======== BEAM FORMING	 TEST =================
	gmake -C ./test -f makefile clean
	
