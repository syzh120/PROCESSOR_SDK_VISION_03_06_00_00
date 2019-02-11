#
# This file is the makefile for building MCAN unit test application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = csl_mcan_unit_test_app

SRCDIR = testApp testLib
INCDIR = testInput testLib

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl pm_hal pm_lib csl_utils_common
COMP_LIST_COMMON += csl_uart_console  csl_arch

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = st_mcanApp.c st_mcanParser.c st_mcanCommon.c st_mcanTxApp.c st_mcanRxApp.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../csl_test_component.mk

ifeq ($(CORE),ipu1_0)
 LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_m4.cmd
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

