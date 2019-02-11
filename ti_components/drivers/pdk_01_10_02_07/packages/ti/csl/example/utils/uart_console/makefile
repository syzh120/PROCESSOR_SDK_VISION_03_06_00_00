#
# This file is the makefile for building CSL example UART utils library.
#
#   Copyright (c) Texas Instruments Incorporated 2015
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = csl_uart_console

SRCDIR = . ./src
INCDIR = . ./inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES =

# Common source files and CFLAGS across all platforms and cores
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x tda3xx dra78x am574x))
PACKAGE_SRCS_COMMON = . ../../lnk_a15.cmd ../../lnk_dsp.cmd ../../lnk_m4.cmd ../../lnk_arp32.cmd
SRCS_COMMON += uartConfig.c
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
