#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=      "../../../algframework"
EVESTARTERWARE=    "../../../starterware"


EVEKERNELDB=     "../../../kernels"
EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/templateMatching/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/templateMatching/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_templateMatching.eve.out
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

CFLAGS+= -I $(EVEKERNELDB)/inc

CFLAGS+= -I $(ALGINCPATH)
CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I../../../kernels/vlib/vcop_ncc/inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LDFLAGS+= -l $(ARP32_TOOLS)/lib/rtsarp32_v200.lib
LDFLAGS+= -l "$(ALGLIBPATH)/libeveTemplateMatching.eve.lib"
LDFLAGS+= -l "$(EVEKERNELDB)/lib/$(TARGET_BUILD)/libevekernels.eve.lib"
LDFLAGS+= -l "$(EVEKERNELDB)/lib/$(TARGET_BUILD)/libevenatckernels.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

