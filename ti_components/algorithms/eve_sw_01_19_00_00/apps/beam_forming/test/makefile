#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################

EVEALGORITHMS   = "../../../apps"

ALGINCPATH = $(EVEALGORITHMS)/beam_forming/algo/inc
ALGLIBPATH = $(EVEALGORITHMS)/beam_forming/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
#SUBDIRS = ./src
SUBDIRS= ../../../common

CFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += ./src/beam_forming_tb.c
CFILES += ./src/report_utils.c
CFILES += ./src/beam_forming_config.c

CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE =./elf_out/test_eveBeamForming.eve.out
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

CFLAGS+= -I ../../../kernels/radarlib/vcop_beam_forming/inc
##############################################################


##############################################################
LDFLAGS+= -l "$(ALGLIBPATH)/libeveBeamForming.eve.lib"
LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

