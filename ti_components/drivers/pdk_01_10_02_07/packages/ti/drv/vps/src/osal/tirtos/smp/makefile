#
# This file is the makefile for building VPS SMP OSAL library for TI RTOS.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vps_osal_tirtos_smp

SRCDIR = . ..
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk
INCLUDE_INTERNAL_INTERFACES = vps_common

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += bsp_osal.c
ifeq ($(INCLUDE_DUMMY_OSAL),yes)
  SRCS_COMMON += bsp_safety_osal.c
endif

PACKAGE_SRCS_COMMON = . ../../../../include/osal
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) -DBSP_OSAL_SMP_MODE_ENABLE

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