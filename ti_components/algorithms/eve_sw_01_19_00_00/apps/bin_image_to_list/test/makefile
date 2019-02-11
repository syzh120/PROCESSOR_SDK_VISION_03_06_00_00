#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################


EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/bin_image_to_list/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/bin_image_to_list/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveBinImageToList.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ../../../common
CFLAGS+= -I $(EVEALGFRAMEWORK)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_utils
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_csl


CFLAGS+= -I $(ALGINCPATH)
CFLAGS += -I ../../../kernels/imgsiglib/vcop_binary_masking/inc
CFLAGS += -I ../../../kernels/imgsiglib/vcop_bin_image_to_list/inc
CFLAGS += -I ../../../kernels/imgsiglib/vcop_select_list_elements/inc
##############################################################


##############################################################

LDFLAGS+= -l "$(ALGLIBPATH)/libeveBinImageToList.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

