#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################


EVEKERNELDB=     "../../../kernels"
EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/soft_isp/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/soft_isp/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveSoftISP.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc

CFLAGS+= -I $(EVEKERNELDB)/inc

CFLAGS+= -I $(ALGINCPATH)
CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I../../../kernels/imgsiglib/vcop_soft_isp/inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LDFLAGS+= -l "$(ALGLIBPATH)/libeveSoftISP.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

