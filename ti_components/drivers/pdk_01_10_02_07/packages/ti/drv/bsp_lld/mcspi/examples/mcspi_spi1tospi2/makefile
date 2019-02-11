#
# This file is the makefile for building McSPI SPI to SPI2  sample application
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = bsp_examples_mcspi_spi1tospi2

SRCDIR = src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk edma
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = csl vps_osal_tirtos vps_common vps_platforms \
                   vps_devices vps_boards vps_examples_utility \
                   i2c_lld bsp_i2c bsp_uart bsp_mcspi fvid2 pm_hal

#Link to EDMA pre-built libraries
EDMA_PLATFORM=$(BOARD)
ifeq ($(BOARD),$(filter $(BOARD), tda2xx tda2xx-evm tda2px tda2px-evm tda2ex tda2ex-evm tda2xx-rvp))
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
XDC_CFG_FILE_ipu1_0 = mcspiSample.cfg

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = .

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = mcspiSample_io.c mcspiSample_main.c

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
