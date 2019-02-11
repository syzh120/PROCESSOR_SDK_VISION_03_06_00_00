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

ALGBASE_PATH ?= $(abspath ../)

SOURCE_DIR = drivers/src
CRED_SRC_DIR = drivers/devices/$(TARGET_SOC)/cred/src/$(CORE)1
CRED_INC_DIR = drivers/devices/$(TARGET_SOC)/cred/inc/$(CORE)1

CFILES +=$(SOURCE_DIR)/dma_funcs.c
CFILES +=$(SOURCE_DIR)/dma_resource_allocator.c
CFILES +=$(SOURCE_DIR)/edma3lld_support.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils_autoincrement.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils_autoincrement_v2.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils_autoincrement_1d.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils_memcpy.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils_scatterGather.c
CFILES +=$(SOURCE_DIR)/edma_utils/edma_utils_state.c

ifeq ($(TARGET_PLATFORM) , PC)
LIBDIR  = .\libs\PC\$(CORE)\$(TARGET_BUILD)
else
LIBDIR  = .\libs\$(CORE)\$(TARGET_BUILD)
endif
OUTFILE = $(LIBDIR)\dmautils.lib

include $(ALGBASE_PATH)/makerules/rules.mk

CFLAGS += -I ./drivers/inc
CFLAGS += -I ./inc
CFLAGS += -I $(CRED_INC_DIR)
CFLAGS += -I ./inc/edma_utils
CFLAGS += -I ./inc/edma_csl


ifeq ($(CORE) , dsp)
CFLAGS += -DCORE_C6XX
endif

ifeq ($(CORE) , eve)
CFLAGS += -DCORE_EVE
endif
##############################################################

$(OUTFILE) : libfile
