#
#module name       :TI FCW
#
#module descripton :Forward COllision Warning using TIs C66x DSP  
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
	@echo ======== FCW ALGO =================
	$(MAKE) -C ./algo -f makefile
	@echo .
	@echo ======== FCW TEST =================
	$(MAKE) -C ./test -f makefile
	
.IGNORE: clean
clean:
	@echo .
	@echo ======== FCW ALGO =================
	$(MAKE) -C ./algo -f makefile clean
	@echo .
	@echo ======== FCW TEST =================
	$(MAKE) -C ./test -f makefile clean
	
