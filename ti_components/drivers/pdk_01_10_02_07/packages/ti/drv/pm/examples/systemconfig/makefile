# Filename: Makefile
#
# This file is the makefile for building the system config example.
#
#   Copyright (C) 2015 - 2016 Texas Instruments Incorporated
#
#******************************************************************************
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = pm_systemconfig_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = pm_example_utils

# List all the components required by the application
COMP_LIST_COMMON = csl pm_hal pm_lib pm_example_utils
COMP_LIST_a15_0 = csl_init

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra75x tda2ex am571x tda3xx dra78x am574x))
SRCS_COMMON += main.c
endif
PACKAGE_SRCS_COMMON = .

# a15
ifeq ($(CORE),$(filter $(CORE), a15_0))
 LNKCMD_FILE = $(PDK_PM_COMP_PATH)/examples/lnk_a15.cmd
endif

# m4
ifeq ($(CORE),$(filter $(CORE), ipu1_0))
 LNKCMD_FILE = $(PDK_PM_COMP_PATH)/examples/lnk_m4.cmd
endif

# c66x
ifeq ($(CORE),$(filter $(CORE), c66x))
 LNKCMD_FILE = $(PDK_PM_COMP_PATH)/examples/lnk_dsp.cmd
endif

LNKFLAGS_LOCAL_a15_0 += --entry Entry

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
