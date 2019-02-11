#******************************************************************************
#*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=      "../../../algframework"
EVESTARTERWARE=    "../../../starterware"

EVEKERNELDB=     ../../../kernels
EVE_COMMON_DIR= "../../../common"
##############################################################

##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ./src/bam_helper

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libeveRemapMerge.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc
CFLAGS+= -I ./src/bam_helper
CFLAGS+= -I $(EVEALGFRAMEWORK)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_csl
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_utils

CFLAGS+= -I $(EVEKERNELDB)/inc
CFLAGS+= -I $(EVEKERNELDB)/common
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_remap/inc
CFLAGS+= -I $(EVEKERNELDB)/vlib/vcop_remap/bam_helper
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_yuv_420nv12_to_422uyvy/inc
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_yuv_420nv12_to_422uyvy/bam_helper
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_yuv_422uyvy_to_420nv12/inc
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_yuv_422uyvy_to_420nv12/bam_helper
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_alpha_blend_yuv420nv12/inc
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_alpha_blend_yuv420nv12/bam_helper
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_alpha_blend_yuv422i/inc
CFLAGS+= -I $(EVEKERNELDB)/imgsiglib/vcop_alpha_blend_yuv422i/bam_helper

CFLAGS+= -I $(EVE_COMMON_DIR)
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
CFLAGS+= -DINPUTTILE
##############################################################

##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

