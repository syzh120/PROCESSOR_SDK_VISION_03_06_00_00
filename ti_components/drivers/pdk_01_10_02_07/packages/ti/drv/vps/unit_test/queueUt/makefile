#
# This file is the makefile for building VPS VIP example application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = vps_test_queue_utils

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = vps_common vps_examples_utility vps_osal_tirtos

ifeq ($(VPS_USE_TI_RTOS_UART),yes)
  COMP_LIST_COMMON += uart
  ifeq ($(SOC),$(filter $(SOC), tda2xx tda3xx))
    COMP_LIST_COMMON += uart_console
  endif
else
  COMP_LIST_COMMON += bsp_uart
endif
ifeq ($(VPS_USE_TI_RTOS_OSAL),yes)
  COMP_LIST_COMMON += osal_tirtos
endif

# Enable XDC build for application by providing XDC CFG File per core
XDC_CFG_FILE_ipu1_0 = queueUt.cfg

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS) $(VPSDRV_CFLAGS)
PACKAGE_SRCS_COMMON = . ../vps_ut_component.mk

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c

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
