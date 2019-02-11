#
# This file is the makefile for building the pmhal example which will switch
# the DPLL core input from SYSCLK1 to SYSCLK2.
# Applicable for only TDA3xx.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = pmhal_dpll_core_sysclk2_unit_test_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl pm_hal pm_lib
COMP_LIST_COMMON += stw_platform stw_uartconsole stw_examples_utility

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  SRCS_COMMON += main_tda3xx.c
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../makefile ../../stw_unit_test_component.mk

LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_m4.cmd

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
