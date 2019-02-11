#
# This file is the makefile for building PM unit test application (PMHAL VM).
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = pmhal_vm_unit_test_app

SRCDIR = . src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = csl pm_hal pm_lib
COMP_LIST_COMMON += stw_platform stw_uartconsole stw_examples_utility
COMP_LIST_a15_0 = csl_init

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  SRCS_COMMON += main_tda2xx.c
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  SRCS_COMMON += main_tda3xx.c
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../makefile ../../stw_unit_test_component.mk

ifeq ($(CORE),a15_0)
  LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_a15.cmd
endif
ifeq ($(CORE),ipu1_0)
  LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_m4.cmd
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
