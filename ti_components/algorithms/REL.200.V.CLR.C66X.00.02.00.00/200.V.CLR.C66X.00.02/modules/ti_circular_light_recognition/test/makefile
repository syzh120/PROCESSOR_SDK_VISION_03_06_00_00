#
#module name       :TI CLR 
#
#module descripton :Circular Light Recognition using TIs C66x DSP  
#
#Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/ 
#
# ALL RIGHTS RESERVED 
#
##############################################################
ALGBASE_PATH ?= $(abspath ../../../)
include $(ALGBASE_PATH)/makerules/config.mk


DSP_COMMON_DIR= ../../../common
DSP_MODULES = "../../ti_circular_light_recognition"
OPENCV_INSTALL_DIR = D:\opencv_3.1.0\opencv
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += $(DSP_COMMON_DIR)/configparser.c
CFILES += $(DSP_COMMON_DIR)/ti_draw_utils.c
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(DSP_COMMON_DIR)/ti_file_io.c))

CFILES += $(DSP_COMMON_DIR)/ti_mem_manager.c

CFILES += $(DSP_COMMON_DIR)/cache.c
CFILES += $(DSP_COMMON_DIR)/profile.c
CFILES += $(DSP_COMMON_DIR)/dsp_tsc_h.asm

ifeq ($(TARGET_PLATFORM), PC)
CFILES:= $(filter-out %ti_file_io.c, $(CFILES))
CFILES:= $(filter-out %eve_sctm.c, $(CFILES))
endif

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\out\ti_circular_light_recognition_algo.out
##############################################################


##############################################################

include $(ALGBASE_PATH)/makerules/rules.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ../inc
CFLAGS+= -I $(XDAIS_PACKAGE_DIR)
CFLAGS+= -I $(DSP_COMMON_DIR)
CFLAGS+= -I $(DMAUTILS_PATH)/inc
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_utils
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_csl
CFLAGS+= -I $(DSP_COMMON_DIR)/baseaddress/$(TARGET_SOC)/$(CORE)
CFLAGS+= -I $(DMAUTILS_PATH)/drivers/inc
##############################################################


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
LDFLAGS+= -l "./linker.cmd"
endif

ifeq ($(TARGET_PLATFORM) , PC)
LDFLAGS+= "$(DSP_MODULES)/lib/PC/$(CORE)/$(TARGET_BUILD)/ti_circular_light_recognition_algo.lib"
else
LDFLAGS+= -l "$(DSP_MODULES)/lib/$(CORE)/$(TARGET_BUILD)/ti_circular_light_recognition_algo.lib"
endif
LDFLAGS += $(DMAUTILS_LIB)

ifeq ($(TARGET_PLATFORM) , PC)
LDFLAGS+= "$(VLIB_INSTALL_DIR)/ti/vlib/lib/common.a86"
LDFLAGS+= "$(VLIB_INSTALL_DIR)/ti/vlib/lib/vlib.a86"
LDFLAGS+= "$(VLIB_INSTALL_DIR)/ti/vlib/lib/vlib_cn.a86"
else
LDFLAGS+= -l "$(VLIB_INSTALL_DIR)/ti/vlib/lib/common.ae66"
LDFLAGS+= -l "$(VLIB_INSTALL_DIR)/ti/vlib/lib/vlib.ae66"
LDFLAGS+= -l "$(VLIB_INSTALL_DIR)/ti/vlib/lib/vlib_cn.ae66"
endif

##############################################################


##############################################################
OUTDIR =  ".\out"

$(OUTFILE) : outfile
##############################################################

