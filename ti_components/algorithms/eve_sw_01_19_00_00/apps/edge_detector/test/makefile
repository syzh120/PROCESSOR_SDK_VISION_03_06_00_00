#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################


EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/edge_detector/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/edge_detector/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveEdgeDetector.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc


CFLAGS+= -I $(ALGINCPATH)
CFLAGS += -I ../../../kernels/imgsiglib/vcop_sobel_xy/inc
CFLAGS += -I ../../../kernels/imgsiglib/vcop_yuv420_fir2d_separable/inc
CFLAGS += -I ../../../kernels/vlib/vcop_vec_gradients_xy_and_magnitude/inc
CFLAGS += -I ../../../kernels/vlib/vcop_canny_non_maximum_suppression/inc
##############################################################


##############################################################

LDFLAGS+= -l "$(ALGLIBPATH)/libeveEdgeDetector.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

