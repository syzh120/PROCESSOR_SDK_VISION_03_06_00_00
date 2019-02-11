#Following paths are expected from the user for using this make file :
# ARP32_TOOLS : Directory pointing to ARP32 compiler ( can be found inside CCS installation at following location
# ccsv5/tools/compiler/ )
# DSP_TOOLS   : Directory pointing to DSP compiler ( can be found inside CCS installation at following location
# ccsv5/tools/compiler/ )
# EVE_SW_ROOT : Directory pointing to the root of the EVE package. The starterware folder should be present here.
# UTILS_PATH  : Directory pointing to util commands like mkdir, rm

ifeq ($(OS),Windows_NT)
    OS := Windows
else
    UNAME := $(shell uname)
    ifeq ($(UNAME),Linux)
        OS := Linux
    endif
endif

ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif

STARTERWARE_DIR := $(EVE_SW_ROOT)/starterware

RM_FILE_CMD := $(UTILS_PATH)/rm
MKDIR_CMD   := $(UTILS_PATH)/mkdir

# Default TARGET_SOC
# Supported values: vayu,vme
ifeq ($(TARGET_SOC), )
    TARGET_SOC := vayu
endif

# Default CORE
# Supported values: dsp, eve
ifeq ($(CORE), )
    CORE := eve
endif

ifeq ($(TARGET_BUILD), )
    TARGET_BUILD := release
endif

# EVE C compiler
SOURCE_DIR := $(STARTERWARE_DIR)/drivers/src

ifeq ($(CORE),eve)
    COMPILE_PATH=$(ARP32_TOOLS)
    TARGETCC = $(COMPILE_PATH)/bin/cl-arp32
    TARGETCC_FLAGS = -O3 --silicon_version=v210 --symdebug:none
    TARGETDC_FLAGS = -g --silicon_version=v210
    CC=$(COMPILE_PATH)/bin/cl-arp32
    AR=$(COMPILE_PATH)/bin/ar-arp32
    LN=$(COMPILE_PATH)/bin/lnk-arp32
    CORE_LIB=$(COMPILE_PATH)/lib/rtsarp32_v200.lib
    EDMA3_LLD_LIB=$(EDMA3_LLD_ROOT)/packages/ti/sdo/edma3/rm/lib/tda2xx-evm/arp32/$(TARGET_BUILD)/edma3_lld_rm.aearp32f
endif

ifeq ($(CORE),dsp)
    COMPILE_PATH=$(DSP_TOOLS)
    TARGETCC = $(COMPILE_PATH)/bin/cl6x
    TARGETCC_FLAGS = -O3 -mv6740+ -ml3 -DUSE_LEVEL_1_MACROS
    TARGETDC_FLAGS = -mv6740+ -ml3 -g -DUSE_LEVEL_1_MACROS
    CC=$(COMPILE_PATH)/bin/cl6x
    AR=$(COMPILE_PATH)/bin/ar6x
    LN=$(COMPILE_PATH)/bin/lnk6x
    CORE_LIB=$(COMPILE_PATH)/lib/rts6740.lib
    EDMA3_LLD_LIB=$(EDMA3_LLD_ROOT)/packages/ti/sdo/edma3/rm/lib/tda2xx-evm/66/$(TARGET_BUILD)/edma3_lld_rm.ae66
endif

OBJ_DIR := $(STARTERWARE_DIR)/drivers/objs/$(TARGET_SOC)/$(CORE)
CRED_SRC_DIR := $(STARTERWARE_DIR)/drivers/devices/$(TARGET_SOC)/cred/src/$(CORE)1
CRED_INC_DIR := $(STARTERWARE_DIR)/drivers/devices/$(TARGET_SOC)/cred/inc/$(CORE)1
BASE_ADDRESS_DIR := $(STARTERWARE_DIR)/inc/baseaddress/$(TARGET_SOC)/$(CORE)
LIB := $(STARTERWARE_DIR)/libs/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)/libevestarterware_$(CORE).lib

#if TARGET_SOC is vayu
ifeq ($(TARGET_SOC),vayu)
    DEFINE_FLAGS := VAYU_PLATFORM
endif

#if TARGET_SOC is vme
ifeq ($(TARGET_SOC),vme)
    DEFINE_FLAGS := VME_PLATFORM
endif
ARFLAGS = a
#if for host emulation
ifeq ($(TARGET_PLATFORM) , PC)
    CRED_SRC_DIR := $(STARTERWARE_DIR)/drivers/devices/vayu/cred/src/$(CORE)1
    CRED_INC_DIR := $(STARTERWARE_DIR)/drivers/devices/vayu/cred/inc/$(CORE)1
    BASE_ADDRESS_DIR := $(STARTERWARE_DIR)/inc/baseaddress/vayu/$(CORE)

    COMPILE_PATH=$(GCC_TOOL)
    TARGETCC = $(COMPILE_PATH)/bin/g++
    TARGETCC_FLAGS = -O3
    TARGETDC_FLAGS = -g
    CC=$(COMPILE_PATH)/bin/g++ -c
    AR=$(COMPILE_PATH)/bin/ar
    ARFLAGS = rvs
    DEFINE_FLAGS := VCOP_HOST_EMULATION
    LIB := $(STARTERWARE_DIR)/libs/host_pc/$(CORE)/$(TARGET_BUILD)/libevestarterware_$(CORE).lib
endif

ifeq ($(TARGET_BUILD),release)
    CFLAGS  = $(TARGETCC_FLAGS)
else
    CFLAGS  = $(TARGETDC_FLAGS)
endif

CFLAGS += -D$(DEFINE_FLAGS)
CFLAGS += -I"$(COMPILE_PATH)/include" -I"$(STARTERWARE_DIR)/inc" -I"$(STARTERWARE_DIR)/drivers/inc"
CFLAGS += -I"$(COMPILE_PATH)/include/vcop"
CFLAGS += -I"$(BASE_ADDRESS_DIR)" -I"$(CRED_INC_DIR)"
CFLAGS += -I"$(STARTERWARE_DIR)/inc/edma_utils"
CFLAGS += -I"$(STARTERWARE_DIR)/inc/edma_csl"
CFLAGS += -I $(EDMA3_LLD_ROOT)/packages/ti/sdo/edma3/rm
CFLAGS += -I $(EDMA3_LLD_ROOT)/packages


MISRA_FLAG_BUGS=-6.2,-8.12,-9.2,-10.1,-12.8,-12.9,-19.15
MISRA_FLAG_WAIVER=-10.3,-1.1,-19.7,-17.4,-8.5

MISRA_FLAG=--check_misra=all,$(MISRA_FLAG_BUGS),$(MISRA_FLAG_WAIVER)

ifeq ($(TARGET_PLATFORM) ,PC)
CFLAGS+= -I"$(ARP32_TOOLS)/include/vcop"
else
CFLAGS+=$(MISRA_FLAG)
endif
