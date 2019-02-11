# Filename: Makefile
#
# This file is the makefile for building the pm rtos example.
#
#   Copyright (C) 2015 - 2017 Texas Instruments Incorporated
#
#******************************************************************************
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = pm_core_loading_app

SRCDIR = src
INCDIR = . src inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk pm_example_utils bios xdc pm_lib vps_osal_tirtos \
                              vps_examples_utility vps_common

# List all the components required by the application
COMP_LIST_COMMON = csl pm_example_utils vps_osal_tirtos bios xdc pm_lib pm_hal \
                   vps_examples_utility vps_common

# Enable XDC build for application by providing XDC CFG File per core
CONFIG_BLD_XDC_a15 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/config_a15.bld
CONFIG_BLD_XDC_m4 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/config_m4.bld
CONFIG_BLD_XDC_c66 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/config_c66.bld
CONFIG_BLD_XDC_arp32 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/config_arp32.bld

ifeq ($(SOC),$(filter $(SOC), tda2ex tda2xx tda2px))
    ifeq ($(CORE),$(filter $(CORE), a15_0))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:Cortex_A15"
    XDC_CFG_FILE_a15_0 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_a15.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), ipu1_0))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_1_0"
    XDC_CFG_FILE_ipu1_0 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_ipu1_0.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), ipu1_1))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_1_1"
    XDC_CFG_FILE_ipu1_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_ipu1_1.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), ipu2_0))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_2_0"
    XDC_CFG_FILE_ipu2_0 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_ipu2_0.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), ipu2_1))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_2_1"
    XDC_CFG_FILE_ipu2_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_ipu2_1.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:DSP_1"
    XDC_CFG_FILE_c66xdsp_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_c66.cfg
    XDC_CFG_FILE_c66x      = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_c66.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), c66xdsp_2))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:DSP_2"
    XDC_CFG_FILE_c66xdsp_2 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_c66.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), arp32_1))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_1"
    XDC_CFG_FILE_arp32_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_arp32.cfg
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    endif
    ifeq ($(CORE),$(filter $(CORE), arp32_2))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_2"
    XDC_CFG_FILE_arp32_2 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_arp32.cfg
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    endif
    ifeq ($(CORE),$(filter $(CORE), arp32_3))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_3"
    XDC_CFG_FILE_arp32_3 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_arp32.cfg
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    endif
    ifeq ($(CORE),$(filter $(CORE), arp32_4))
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_4"
    XDC_CFG_FILE_arp32_4 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_arp32.cfg
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    endif
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
    ifeq ($(CORE),$(filter $(CORE), ipu1_0))
    PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_0"
    XDC_CFG_FILE_ipu1_0 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_ipu1_0.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), ipu1_1))
    PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_1"
    XDC_CFG_FILE_ipu1_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_ipu1_1.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1))
    PLATFORM_XDC = "ti.platforms.evmTDA3XX:DSP_1"
    XDC_CFG_FILE_c66xdsp_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_c66.cfg
    XDC_CFG_FILE_c66x      = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_c66.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), c66xdsp_2))
    PLATFORM_XDC = "ti.platforms.evmTDA3XX:DSP_2"
    XDC_CFG_FILE_c66xdsp_2 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_c66.cfg
    endif
    ifeq ($(CORE),$(filter $(CORE), arp32_1))
    PLATFORM_XDC = "ti.platforms.evmTDA3XX:EVE_1"
    XDC_CFG_FILE_arp32_1 = $(PDK_PM_COMP_PATH)/examples/core_loading/config/pm_arp32.cfg
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    endif
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += core_loading.c 
ifeq ($(CORE),$(filter $(CORE), a15_0 ipu1_0 ipu1_1 ipu2_0 ipu2_1))
SRCS_COMMON += dhrystone.c
endif
ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1 c66xdsp_2))
SRCS_COMMON += dsp_load_wrapper.c
SRCS_ASM_COMMON += dsp_cpu_load.asm
endif
ifeq ($(CORE),$(filter $(CORE), arp32_1 arp32_2 arp32_3 arp32_4))
SRCS_COMMON += eve_load_wrapper.c vcop_fft_1024_16x16t_kernel.c tlb_config_eve_common.c
endif
PACKAGE_SRCS_COMMON = .

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
