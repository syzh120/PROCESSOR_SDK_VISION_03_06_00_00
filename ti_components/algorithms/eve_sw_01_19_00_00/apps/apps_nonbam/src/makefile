#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

EVEALGFRAMEWORK = ../../../algframework
EVESTARTERWARE = ../../../starterware

EVEKERNELIB=     "../../../kernels"

##############################################################

SUBDIRS += ./common
SUBDIRS += .

CFILES_TEMP = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES_TEMP += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
#remove any kernel test bench files
CFILES= $(filter-out %_tb.c, $(CFILES_TEMP))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))


OUTFILE = ../lib/$(TARGET_BUILD)/libeveapps.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I $(EVESTARTERWARE)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_utils
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_csl

CFLAGS+= -I $(EVEALGFRAMEWORK)/inc
CFLAGS+= -I $(EVEKERNELIB)/inc
CFLAGS+= -I ../inc
CFLAGS+= -I ./common
##############################################################


##############################################################
LIBDIR:=  "../lib/$(TARGET_BUILD)"
OUTDIR:=  "../elf_out"

$(OUTFILE) : libfile
##############################################################
