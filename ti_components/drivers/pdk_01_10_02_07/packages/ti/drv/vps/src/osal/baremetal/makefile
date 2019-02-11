#
# This file is the makefile for building baremetal VPS OSAL library.
#
#   Copyright (c) Texas Instruments Incorporated 2016
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vps_osal_baremetal

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES =

# Common source files and CFLAGS across all platforms and cores
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../../../include/osal
ifeq ($(BOARD),$(filter $(BOARD),evmDRA75x))
  PACKAGE_SRCS_COMMON += ../../../makefile ../../../vps_component.mk
endif
ifeq ($(SOC),$(filter $(SOC), am571x am572x am574x))
SRCS_COMMON += osal_am57x.c
else
SRCS_COMMON += osal.c osal_cache.c
endif

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
