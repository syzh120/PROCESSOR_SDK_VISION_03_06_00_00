#
# This file is the makefile for building VPS OV sensor baremetal example application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = vps_examples_ovsensor_baremetal

SRCDIR = src
INCDIR = . src inc

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl pm_hal pm_lib
COMP_LIST_COMMON += i2c_lld vps_osal_baremetal stw_platform stw_uartconsole
COMP_LIST_COMMON += stw_boards stw_devices stw_examples_utility

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = sensorconfig.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS)
PACKAGE_SRCS_COMMON = .

LNKCMD_FILE = $(PDK_STW_EXAMPLE_COMP_PATH)/utility/lnk_m4.cmd

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
