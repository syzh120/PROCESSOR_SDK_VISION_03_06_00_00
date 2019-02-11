#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################

EVEALGORITHMS   = "../../../apps"

ALGINCPATH = $(EVEALGORITHMS)/fft/algo/inc
ALGLIBPATH = $(EVEALGORITHMS)/fft/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
#SUBDIRS = ./src
SUBDIRS= ../../../common

CFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += ./src/fft_tb.c
CFILES += ./src/fft32o_cn.c
CFILES += ./src/report_utils.c
CFILES += ./src/fft_config.c

CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE =./elf_out/test_eveFFT.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I $(KERNELS_DIR)/inc

CFLAGS+= -I $(ALGINCPATH)
CFLAGS+= -I $(KERNELS_DIR)
CFLAGS+= -I ../../../kernels/radarlib/vcop_dcoffset_windowing/inc
CFLAGS+= -I ../../../kernels/radarlib/vcop_fft_npt_16ix16o/inc
CFLAGS+= -I ../../../kernels/radarlib/vcop_fft_npt_16ix32o/inc
##############################################################


##############################################################
LDFLAGS+= -l "$(ALGLIBPATH)/libeveFFT.eve.lib"
LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

