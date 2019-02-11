#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

all:
#ifneq ($(TARGET_PLATFORM) , PC)
#	@echo .
#	@echo ======== EVE ALGORITHMS =================
#	gmake -C ./src -f makefile
#	@echo .
#	@echo ======== EVE ALGORITHMS TEST =================
#	gmake -C ./test -f makefile
#endif
	@echo .
	@echo ======== Pyramid LK SOF ALGO =================
	gmake -C ./pyramid_lk_sof/algo -f makefile
	@echo .
	@echo ======== Pyramid LK SOF TEST =================
	gmake -C ./pyramid_lk_sof/test -f makefile
	@echo .
	@echo ======== ORB ALGO =================
	gmake -C ./orb/algo -f makefile
	@echo .
	@echo ======== ORB TEST =================
	gmake -C ./orb/test -f makefile
	@echo .
	@echo ======== STEREO TEST =================
	gmake -C ./stereoVision/test -f makefile

.IGNORE: clean
clean:
#ifneq ($(TARGET_PLATFORM) , PC)
#	@echo .
#	@echo ======== EVE ALGORITHMS TEST =================
#	gmake -C ./test -f makefile clean
#	@echo .
#	@echo ======== EVE ALGORITHMS =================
#	gmake -C ./src -f makefile clean
#endif
	@echo .
	@echo ======== Pyramid LK SOF ALGO =================
	gmake -C ./pyramid_lk_sof/algo -f makefile clean
	@echo .
	@echo ======== Pyramid LK SOF TEST =================
	gmake -C ./pyramid_lk_sof/test -f makefile clean
	@echo .
	@echo ======== ORB ALGO CLEAN =================
	gmake -C ./orb/algo -f makefile clean
	@echo .
	@echo ======== ORB TEST CLEAN =================
	gmake -C ./orb/test -f makefile clean
	@echo .
	@echo ======== STEREO TEST CLEAN =================
	gmake -C ./stereoVision/test -f makefile clean

