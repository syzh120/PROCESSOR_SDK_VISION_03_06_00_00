#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGORITHMS = "../../../apps"

##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= ./src/stereoVision_tb.c
CFILES+= ./src/stereoVision_testfuncs.c
CFILES+= ./src/stereoVision_config.c
CFILES+= ./src/rectify.c
CFILES+= ../../../apps/remap_merge/test/src/remap_merge_natc.c
CFILES+= ./src/rectMapLeft_int_converted.c
CFILES+= ./src/rectMapRight_int_converted.c

CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_stereoVision.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I $(EVEALGORITHMS)/remap_merge/test/convert_map/algo/inc
CFLAGS+= -I $(EVEALGORITHMS)/remap_merge/test/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_remap/inc

CFLAGS+= -I $(EVEALGORITHMS)/census/algo/inc
CFLAGS+= -I $(EVEALGORITHMS)/disparity/algo/inc
CFLAGS+= -I $(EVEALGORITHMS)/remap_merge/algo/inc
##############################################################


##############################################################
LDFLAGS+= -l "$(EVEALGORITHMS)/census/algo/lib/$(TARGET_BUILD)/libeveCensus.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/disparity/algo/lib/$(TARGET_BUILD)/libeveDisparity.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/remap_merge/algo/lib/$(TARGET_BUILD)/libeveRemapMerge.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/remap_merge/test/convert_map/algo/lib/$(TARGET_BUILD)/libeveConvertMap.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

