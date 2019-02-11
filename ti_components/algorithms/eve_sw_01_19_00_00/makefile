#******************************************************************************
#*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
#
# This makefile expects the following environment variables from the user:
# ARP32_TOOLS     : Directory pointing to ARP32 compiler
# DSP_TOOLS       : Directory pointing to DSP compiler
# xdais_PATH      : Directory pointing to root of XDAIS installation.
# EVE_SW_ROOT     : Directory pointing to the root of the EVE SW installation.
#                   This is optional and is current directory by default.
# UTILS_PATH      : Directory pointing to util commands mkdir and rm
#                   (CCS users can find them at ccsv5/utils/cygwin)
#
# Please note that the path names should use forward slash (/) and should
# not contain quotes and spaces. As an example, if we want to set ARP32 compiler
# path as C:/Program Files/Texas Instruments/ARP32_tools, use
#     set ARP32_TOOLS=C:/PROGRA~1/TEXASI~1/ARP32_tools
#
#******************************************************************************

ifdef SystemRoot
START_TIME := $(shell echo . |time|findstr [0-9])
START_TIME := $(lastword $(START_TIME))
else
START_TIME = $(shell date +%H:%M:%S)
endif
$(info  START_TIME $(START_TIME))
##############################################################
#optional : only for: gmake format
FORMATTER = "C:/Tools/AStyle/bin/AStyle.exe"
FORMATOPT = --recursive --suffix=none --style=allman --convert-tabs --min-conditional-indent=1 --indent-col1-comments --align-pointer=name
##############################################################
export EVE_SW_ROOT ?= $(CURDIR)
export ARP32_TOOLS ?= C:/ti/ARP32_tools
export DSP_TOOLS ?= C:/ti/ccsv5/tools/compiler/c6000_7.4.2
export xdais_PATH ?= C:/ti/xdais_7_23_00_06
export UTILS_PATH ?= C:/ti/ccsv5/utils/cygwin

all:
	@echo ======== STARTERWARE =================
	gmake -C ./starterware -f Makefile TARGET_SOC=vayu CORE=eve
	gmake -C ./starterware -f Makefile TARGET_SOC=vayu CORE=dsp
	gmake -C ./starterware -f Makefile TARGET_SOC=vme CORE=eve
	gmake -C ./starterware -f Makefile TARGET_SOC=vme CORE=dsp
	@echo .
	@echo ======== KERNELS =================
	gmake -C ./kernels -f makefile
	@echo ======== APPS =================
	gmake -C ./apps -f makefile
	@echo ======== ALGORITHMS =================
	gmake -C ./algorithms -f makefile
	@echo The  start  time is: $(START_TIME)
ifdef SystemRoot
	@echo . |time|findstr [0-9]
else
	@echo The  end  time is: `date +%H:%M:%S`
endif	
	

.IGNORE: clean
clean:
	@echo ======== STARTERWARE =================
	gmake -C ./starterware -f Makefile clean TARGET_SOC=vayu CORE=eve
	gmake -C ./starterware -f Makefile clean TARGET_SOC=vayu CORE=dsp
	gmake -C ./starterware -f Makefile clean TARGET_SOC=vme CORE=eve
	gmake -C ./starterware -f Makefile clean TARGET_SOC=vme CORE=dsp
	rmdir /S /Q ./starterware/libs
	@echo ======== KERNELS =================
	gmake -C ./kernels -f makefile clean
	@echo ======== APPS =================
	gmake -C ./apps -f makefile clean
	@echo ======== ALGORITHMS =================
	gmake -C ./algorithms -f makefile clean
	@echo The  start  time is: $(START_TIME)
ifdef SystemRoot
	@echo . |time|findstr [0-9]
else
	@echo The  end  time is: `date +%H:%M:%S`
endif

scrub: clean
ifdef SystemRoot
	attrib  +r +s ./kernels/inc/evekernels_include.h
	$(UTILS_PATH)/rm -rf ./kernels/inc/*
	attrib  -r -s ./kernels/inc/evekernels_include.h
	$(UTILS_PATH)/rm -rf ./out
else
	mv ./kernels/inc/evekernels_include.h ./out
	rm -rf ./kernels/inc/*
	mv  ./out/evekernels_include.h ./kernels/inc
	rm -rf ./out
endif	

format:
	$(FORMATTER) $(FORMATOPT) "./coresw/*.c" "./coresw/*.h"
	$(FORMATTER) $(FORMATOPT) "./algorithms/*.h" "./algorithms/*.c"
