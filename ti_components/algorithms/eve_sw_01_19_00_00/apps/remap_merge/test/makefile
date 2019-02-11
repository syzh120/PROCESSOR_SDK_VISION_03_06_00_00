#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=      "../../../algframework"
EVESTARTERWARE=    "../../../starterware"


EVEKERNELDB=     ../../../kernels
EVEALGORITHMS = ../../../apps

##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../apps_nonbam/test/common

CFILES += ./src/remap_merge_tb.c
CFILES += ./src/remap_merge_config.c
CFILES += ./src/test_print.c
CFILES += ./src/report_utils.c
CFILES += ./src/remap_merge_natc.c

CFILES += ./src/remapCoordSmall_int.c
ifeq ($(TEST_MODE), file_test)
CFILES += ./src/remapCoordBig_int.c
endif

CFILES += ../../../common/ti_mem_manager.c
CFILES += ../../../common/configparser.c
CFILES += ../../../common/ti_file_io.c
CFILES += ../../../common/eve_profile.c
CFILES += ../../../common/ti_stats_collector.c

CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveRemapMerge.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
ifeq ($(TEST_MODE), file_test)
CFLAGS+= -DFILE_TEST
endif
CFLAGS+= -I inc
CFLAGS+= -I ../algo/inc
CFLAGS+= -I ../dma/inc
CFLAGS+= -I ../../../common
CFLAGS+= -I convert_map/algo/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_remap/inc
CFLAGS+= -I $(EVEALGFRAMEWORK)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_utils
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_csl

CFLAGS+= -I $(EVEKERNELDB)/inc

CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LDFLAGS+= -l $(ARP32_TOOLS)/lib/rtsarp32_v200.lib
LDFLAGS+= -l "$(EVEKERNELDB)/lib/$(TARGET_BUILD)/libevekernels.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/remap_merge/algo/lib/$(TARGET_BUILD)/libeveRemapMerge.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/remap_merge/test/convert_map/algo/lib/$(TARGET_BUILD)/libeveConvertMap.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

