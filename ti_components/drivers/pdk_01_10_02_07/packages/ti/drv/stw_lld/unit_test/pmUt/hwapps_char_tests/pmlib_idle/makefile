#
# This file is the makefile for building PM unit test application (PMLIB Idle).
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = pmlib_idle_unit_test_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl pm_lib
COMP_LIST_COMMON += stw_platform stw_uartconsole stw_examples_utility

# Common source files and CFLAGS across all platforms and cores
SRCS_c66x += main_c66x.c
SRCS_arp32_1 += main_arp32.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../../makefile ../../../stw_unit_test_component.mk

ifeq ($(CORE),c66x)
  COMP_LIST_COMMON += pm_hal
  LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_dsp.cmd
endif
ifeq ($(CORE),arp32_1)
  LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_arp32.cmd
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
