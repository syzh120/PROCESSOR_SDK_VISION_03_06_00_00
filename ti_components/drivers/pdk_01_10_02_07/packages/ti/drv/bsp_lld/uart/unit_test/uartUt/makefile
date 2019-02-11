#
# This file is the makefile for building BSP UART unit test application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = bsp_test_uart

SRCDIR = testApp testLib
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk edma
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = csl stw_platform fvid2 vps_osal_tirtos vps_common vps_platforms \
                   vps_devices vps_boards pm_hal pm_lib vps_examples_utility
COMP_LIST_COMMON += i2c_lld bsp_i2c
COMP_LIST_COMMON += bsp_uart
#Link to EDMA pre-built libraries
EDMA_PLATFORM=$(BOARD)
ifeq ($(BOARD),$(filter $(BOARD), tda2xx tda2xx-evm tda2px tda2px-evm tda2ex tda2ex-evm))
  EDMA_PLATFORM=tda2xx-evm
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx tda3xx-evm))
  EDMA_PLATFORM=tda3xx-evm
endif
EXT_LIB_LIST_COMMON  = $(edma3_lld_drv_PATH)/lib/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_drv.$(LIBEXT)
EXT_LIB_LIST_COMMON += $(edma3_lld_drv_sample_PATH)/lib/$(EDMA_PLATFORM)/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_drv_sample.$(LIBEXT)
EXT_LIB_LIST_COMMON += $(edma3_lld_rm_PATH)/lib/$(EDMA_PLATFORM)/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_rm.$(LIBEXT)
EXT_LIB_LIST_COMMON += $(edma3_lld_rm_sample_PATH)/lib/$(EDMA_PLATFORM)/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_rm_sample.$(LIBEXT)

# XDC CFG File
XDC_CFG_FILE_ipu1_0 = st_uart.cfg

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(BSPUART_CFLAGS)
PACKAGE_SRCS_COMMON = . ../bsp_uart_ut_component.mk

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = st_uartApp.c st_uartCommon.c st_uartParser.c st_uartTestCase.c st_uartPlatform.c

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
