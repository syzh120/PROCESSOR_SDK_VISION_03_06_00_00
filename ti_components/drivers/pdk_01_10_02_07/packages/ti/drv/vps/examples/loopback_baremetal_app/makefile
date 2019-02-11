#
# This file is the makefile for building VPS loopback baremetal example application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = vps_examples_loopback_baremetal

SRCDIR = src
INCDIR = . src inc

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl vpslib vpsdrv_baremetal vps_common pm_hal pm_lib
COMP_LIST_COMMON += vps_osal_baremetal

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = app_frameBufMgmt.c app_videoLoopbackConfigure.c main.c

#TDA specific libraries/files
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  SRCS_COMMON += app_tda_board_config.c
  COMP_LIST_COMMON += stw_uartconsole stw_platform i2c_lld stw_boards
  COMP_LIST_COMMON += stw_devices stw_examples_utility
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS)
PACKAGE_SRCS_COMMON = .

LNKCMD_FILE = $(PDK_VPS_COMP_PATH)/examples/utility/lnk_m4.cmd

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
