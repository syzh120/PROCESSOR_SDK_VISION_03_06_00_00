#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################

EVEALGORITHMS   = "../../../apps"
EVEKERNELDB = ../../../kernels

ALGINCPATH = $(EVEALGORITHMS)/morphology/algo/inc
ALGLIBPATH = $(EVEALGORITHMS)/morphology/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
#SUBDIRS = ./src
SUBDIRS= ../../../common

CFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += ./src/morphology_tb.c
CFILES += ./src/report_utils.c
CFILES += ./src/morphology_config.c

CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE =./elf_out/test_eveMorphology.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards

CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_grayscale_morphology_flat/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_dilate_cross/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_dilate_mask/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_dilate_square/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_erode_cross/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_erode_mask/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_erode_square/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_vec_bin_image_morph_diff/inc

CFLAGS+= -I $(ALGINCPATH)

##############################################################


##############################################################

LDFLAGS+= -l "$(ALGLIBPATH)/libeveMorphology.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

