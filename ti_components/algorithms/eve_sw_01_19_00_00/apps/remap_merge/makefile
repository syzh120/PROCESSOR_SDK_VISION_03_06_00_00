#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== Remap and Merge ALGO =================
	gmake -C ./algo -f makefile
	@echo .
	@echo ======= Remap and Merge TEST ConvertMap =======
	gmake -C ./test/convert_map/algo -f makefile
	@echo .
	@echo ======== Remap and Merge TEST =================
	gmake -C ./test -f makefile
	@echo .
	@echo ======== Remap Convert table TEST =================
	gmake -C ./test -f makefileConvertTable
	@echo .
	@echo ======== Remap Execute TEST =================
	gmake -C ./test -f makefileRemapExecute

.IGNORE: clean
clean:
	@echo .
	@echo ======== Remap and Merge ALGO =================
	gmake -C ./algo -f makefile clean
	@echo .
	@echo ======= Remap and Merge TEST ConvertMap =======
	gmake -C ./test/convert_map/algo -f makefile clean
	echo .
	@echo ======== Remap and Merge TEST =================
	gmake -C ./test -f makefile clean
	echo .
	@echo ======== Remap Convert table TEST =================
	gmake -C ./test -f makefileConvertTable clean
	echo .
	@echo ======== Remap Execute TEST =================
	gmake -C ./test -f makefileRemapExecute clean
	echo .
