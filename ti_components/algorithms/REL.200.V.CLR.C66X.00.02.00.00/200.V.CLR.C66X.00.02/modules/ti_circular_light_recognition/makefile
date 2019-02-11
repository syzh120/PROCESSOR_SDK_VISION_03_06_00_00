#
#module name       :TI CLR 
#
#module descripton :Circular Light Recognition using TIs C66x DSP  
#
#Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/ 
#
# ALL RIGHTS RESERVED 
#

ifdef SystemRoot
    MAKE = gmake
else
    ifeq ($(shell uname), Linux)
      MAKE = make
    endif
endif

all:
	@echo .
	@echo ======== tidl ALGO =================
	$(MAKE) -C ./algo -f makefile
	@echo .
	@echo ======== tidl TEST =================
	$(MAKE) -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== tidl ALGO =================
	$(MAKE) -C ./algo -f makefile clean
	@echo .
	@echo ======== tidl TEST =================
	$(MAKE) -C ./test -f makefile clean
	
