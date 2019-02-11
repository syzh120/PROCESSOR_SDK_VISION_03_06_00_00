#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGORITHMS = "../../../apps"


EVEKERNELDB=     "../../../kernels"


ALGINCPATH= $(EVEALGORITHMS)/ti_pd_feature_plane_computation/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/ti_pd_feature_plane_computation/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += ../../../common/configparser.c
CFILES += ../../../common/ti_mem_manager.c
CFILES += ../../../common/boot_arp32.asm
HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveFeaturePlaneComputation.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ../../../common


CFLAGS+= -I $(ALGINCPATH)
CFLAGS += -I ../../yuv_padding/algo/inc
CFLAGS+= -I ../../../kernels/imgsiglib/vcop_yuv_scalar/inc
CFLAGS += -I ../../yuv_scalar/algo/inc
CFLAGS += -I ../../filter_2d/algo/inc

##############################################################


##############################################################

LDFLAGS+= -l "$(ALGLIBPATH)/libeveFeaturePlaneComputation.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/yuv_padding/algo/lib/$(TARGET_BUILD)/libeveYUVPAdding.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/yuv_scalar/algo/lib/$(TARGET_BUILD)/libeveYUVScalar.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/filter_2d/algo/lib/$(TARGET_BUILD)/libeveFilter2D.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

