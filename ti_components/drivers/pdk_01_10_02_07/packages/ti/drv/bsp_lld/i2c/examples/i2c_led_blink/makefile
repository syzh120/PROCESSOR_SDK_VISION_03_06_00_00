#
# This file is the makefile for building I2C LED blink sample application
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = bsp_examples_i2c_led_blink

SRCDIR = src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = csl vps_osal_tirtos vps_common vps_platforms \
                   vps_devices vps_boards vps_examples_utility \
                   i2c_lld bsp_i2c

# Enable XDC build for application by providing XDC CFG File per core
XDC_CFG_FILE_ipu1_0 = i2cSample.cfg

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = .

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = i2cSample_io.c i2cSample_main.c

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
