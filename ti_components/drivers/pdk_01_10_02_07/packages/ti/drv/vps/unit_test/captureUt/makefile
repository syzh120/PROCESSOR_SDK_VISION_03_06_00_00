#
# This file is the makefile for building VPS VIP unit test application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = vps_test_capture

SRCDIR = testApp testLib
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = csl fvid2 vps_osal_tirtos vps_common vpslib vpsdrv vps_platforms \
                   vps_devices vps_boards pm_hal pm_lib vps_examples_utility
ifeq ($(VPS_USE_TI_RTOS_I2C),yes)
  COMP_LIST_COMMON += i2c
else
  COMP_LIST_COMMON += i2c_lld bsp_i2c
endif
ifeq ($(VPS_USE_TI_RTOS_UART),yes)
  COMP_LIST_COMMON += uart
  ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
    COMP_LIST_COMMON += uart_console
  endif
else
  COMP_LIST_COMMON += bsp_uart
endif
ifeq ($(VPS_USE_TI_RTOS_OSAL),yes)
  COMP_LIST_COMMON += osal_tirtos
endif
ifeq ($(VPS_USE_TI_RTOS_MMCSD),yes)
  COMP_LIST_COMMON += fatfs_indp mmcsd
else
  COMP_LIST_COMMON += stw_fatlib stw_platform
endif
COMP_LIST_am571x = board
COMP_LIST_am572x = board
COMP_LIST_am574x = board

#Link to EDMA pre-built libraries
EDMA_PLATFORM=$(BOARD)
ifeq ($(BOARD),$(filter $(BOARD), tda2xx tda2xx-evm tda2px tda2px-evm tda2ex tda2ex-evm tda2xx-rvp evmAM572x idkAM572x idkAM571x idkAM574x))
  EDMA_PLATFORM=tda2xx-evm
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx tda3xx-evm))
  EDMA_PLATFORM=tda3xx-evm
endif

EXT_LIB_LIST_COMMON  = $(edma3_lld_drv_PATH)/lib/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_drv.$(LIBEXT)
EXT_LIB_LIST_COMMON += $(edma3_lld_drv_sample_PATH)/lib/$(EDMA_PLATFORM)/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_drv_sample.$(LIBEXT)
EXT_LIB_LIST_COMMON += $(edma3_lld_rm_PATH)/lib/$(EDMA_PLATFORM)/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_rm.$(LIBEXT)
EXT_LIB_LIST_COMMON += $(edma3_lld_rm_sample_PATH)/lib/$(EDMA_PLATFORM)/$(ISA_EXT)/$(BUILD_PROFILE_$(CORE))/edma3_lld_rm_sample.$(LIBEXT)

# Enable XDC build for application by providing XDC CFG File per core
XDC_CFG_FILE_ipu1_0 = st_capture.cfg
XDC_CFG_FILE_c66x   = st_capture_c66x.cfg
XDC_CFG_FILE_a15_0  = st_capture_a15.cfg

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS) $(VPSDRV_CFLAGS)
PACKAGE_SRCS_COMMON = . ../vps_ut_component.mk

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = st_captureApp.c st_captureCommon.c st_captureParser.c st_captureTestCase.c

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
