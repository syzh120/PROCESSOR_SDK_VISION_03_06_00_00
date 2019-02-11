#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################


EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/yuv_scalar/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/yuv_scalar/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += ../../../common/boot_arp32.asm
HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveYUVScalar.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT

$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I .
CFLAGS+= -I inc

CFLAGS+= -I ../../../kernels/imgsiglib/vcop_yuv_scalar/inc

CFLAGS+= -I $(ALGINCPATH)

##############################################################


##############################################################

LDFLAGS+= -l "$(ALGLIBPATH)/libeveYUVScalar.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

