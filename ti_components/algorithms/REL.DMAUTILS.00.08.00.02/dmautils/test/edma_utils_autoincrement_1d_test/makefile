#*******************************************************************************
#* module name       :DMA Utils                                                   *
#*                                                                             *
#* module descripton :DMA Utility functions for EVE and DSP targeted for imaging and vision    *
#*                    applications                                             *
#*                                                                             *
#* Copyright (C) 2009-2017 Texas Instruments Incorporated - http://www.ti.com/ *
#*                                                                             *
#* ALL RIGHTS RESERVED                                                         *
#*                                                                             *
#*                                                                             *
#*******************************************************************************


##############################################################

##############################################################
ALGBASE_PATH ?= $(abspath ../../../)
COMMON_PATH:= ../../../common

ifeq ($(TARGET_PLATFORM) , PC)
ifndef C6XSIM_PATH
$(error You must define C6XSIM_PATH for host emulation relative to current directory!)
endif
endif

CORE=dsp
SUBDIRS= ./src


CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))
HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))


ifeq ($(TARGET_PLATFORM) , PC)
ifeq ($(CORE) , dsp)
SUBDIRS +=$(C6XSIM_PATH)
CFLAGS+= -I $(C6XSIM_PATH)
endif
endif

ifeq ($(CORE) , eve)
CFILES += $(COMMON_PATH)/eve/eve_profile.c
CFILES += $(COMMON_PATH)/eve/curve_fitting.c
CFILES += $(COMMON_PATH)/eve/eve_sctm.c
CFILES += $(COMMON_PATH)/eve/ti_stats_collector.c
CFILES += $(COMMON_PATH)/eve/cred.c
CFILES += $(COMMON_PATH)/eve/boot_arp32.asm
CFLAGS+= -I $(DSP_COMMON_DIR)/eve
else ifeq ($(CORE) , dsp)
CFILES += $(COMMON_PATH)/cache.c
CFILES += $(COMMON_PATH)/profile.c
CFILES += $(COMMON_PATH)/dsp_tsc_h.asm
endif


OUTFILE=elf_out/test_edmaUtilsAutoincrement1dTest.out
##############################################################




##############################################################
include $(ALGBASE_PATH)/makerules/rules.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ../inc
CFLAGS+= -I $(DMAUTILS_PATH)/inc
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_utils
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_csl
CFLAGS+= -I $(COMMON_PATH)


##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
DMAUTILS_LIB  := $(DMAUTILS_PATH)/libs/PC/$(CORE)/$(TARGET_BUILD)/dmautils.lib
else
DMAUTILS_LIB  := $(DMAUTILS_PATH)/libs/$(CORE)/$(TARGET_BUILD)/dmautils.lib
endif

ifneq ($(TARGET_PLATFORM) , PC)
ifeq ($(CORE) , eve)
LDFLAGS+= -l $(ARP32_TOOLS)/lib/rtsarp32_v200.lib
else ifeq ($(CORE) , dsp)
LDFLAGS+= -cr -x
LDFLAGS+= -l $(DSP_TOOLS)/lib/rts6600_elf.lib
endif
LDFLAGS+= -l "./linker_$(CORE).cmd"
endif
LDFLAGS+= -l $(DMAUTILS_LIB)

LDFLAGS := $(call  CHANGE_PATHSEP,$(LDFLAGS))
##############################################################

##############################################################
OUTDIR =  "elf_out"

$(OUTFILE) : outfile
##############################################################

