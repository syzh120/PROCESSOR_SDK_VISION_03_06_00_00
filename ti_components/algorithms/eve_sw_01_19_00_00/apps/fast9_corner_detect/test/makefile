#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################


EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/fast9_corner_detect/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/fast9_corner_detect/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_evefast9CornerDetect.eve.out
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
CFLAGS+= -I../../../kernels/vlib/vcop_fast9/inc
CFLAGS += -I ../../../kernels/imgsiglib/vcop_bin_image_to_list/inc
##############################################################


##############################################################

LDFLAGS+= -l "$(ALGLIBPATH)/libeveFast9CornerDetect.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

