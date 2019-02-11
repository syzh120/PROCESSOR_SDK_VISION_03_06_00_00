#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


#include Rules.make
# Default platform
# Supported values: vayu,vme
TARGET_SOC ?= vayu
# Default CORE
# Supported values: dsp, eve
CORE ?= eve
TARGET_PLATFORM ?= EVE
ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

SOURCE_DIR := drivers/src
CRED_SRC_DIR := drivers/devices/$(TARGET_SOC)/cred/src/$(CORE)1
CRED_INC_DIR := drivers/devices/$(TARGET_SOC)/cred/inc/$(CORE)1

ifeq ($(TARGET_PLATFORM) , PC)
  CFILES +=$(SOURCE_DIR)/host_pc/INTH.c
  CFILES +=$(SOURCE_DIR)/host_pc/mbox.c
  CFILES +=$(SOURCE_DIR)/host_pc/mmu.c
  CFILES +=$(SOURCE_DIR)/host_pc/pcache.c
  CFILES +=$(SOURCE_DIR)/host_pc/sctm.c
else
  ifeq ($(CORE) , eve)
    CFILES :=$(CRED_SRC_DIR)/cred.c
    CFILES +=$(SOURCE_DIR)/INTH.c
    CFILES +=$(SOURCE_DIR)/INTCTL.c
    CFILES +=$(SOURCE_DIR)/INTH_asm.asm
    CFILES +=$(SOURCE_DIR)/mbox.c
    CFILES +=$(SOURCE_DIR)/mmu.c
    CFILES +=$(SOURCE_DIR)/pcache.c
    CFILES +=$(SOURCE_DIR)/sctm.c
  else
    CFILES :=$(CRED_SRC_DIR)/cred.c
    CFILES +=$(SOURCE_DIR)/mbox.c
    CFILES +=$(SOURCE_DIR)/mmu.c
  endif
endif

ifeq ($(TARGET_PLATFORM) , PC)
  OUTFILE = ./libs/$(TARGET_PLATFORM)/$(TARGET_BUILD)/libevestarterware_eve.lib
  LIBDIR:=  "./libs/$(TARGET_PLATFORM)/$(TARGET_BUILD)"
  OUTDIR:=  "../elf_out"
else
  OUTFILE = ./libs/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)/libevestarterware_$(CORE).lib
  LIBDIR:=  "./libs/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)"
  OUTDIR:=  "../elf_out"
endif

ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

CFLAGS += -I $(BASE_ADDRESS_DIR) 
CFLAGS += -I ./drivers/inc
CFLAGS += -I ./inc
CFLAGS += -I $(CRED_INC_DIR)
CFLAGS += -I ./inc/edma_utils
CFLAGS += -I ./inc/edma_csl


##############################################################

$(OUTFILE) : libfile
