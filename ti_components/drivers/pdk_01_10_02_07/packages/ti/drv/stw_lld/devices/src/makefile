#
# This file is the makefile for building STW Devices library.
#
#   Copyright (c) Texas Instruments Incorporated 2016
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = stw_devices

SRCDIR = src src/ioexp
INCDIR = . src src/ioexp

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES =

# Common source files and CFLAGS across all platforms and cores
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(STW_LLD_CFLAGS)
PACKAGE_SRCS_COMMON = . ../stw_lld_component.mk  ../.gitignore ../makefile
SRCS_COMMON += stw_device.c stw_deviceI2c.c stw_deviceIoexpTca64xx.c

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
