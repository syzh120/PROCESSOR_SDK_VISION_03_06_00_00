#
# This file is the makefile for building QSPI unit test application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = qspi_unit_test_app

SRCDIR = testApp testLib
INCDIR = testInput testLib

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl pm_hal pm_lib
COMP_LIST_COMMON += stw_platform stw_uartconsole stw_examples_utility
COMP_LIST_COMMON += diag qspiflash_lib

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = st_qspiApp.c st_qspiParser.c st_qspiTestCase.c st_qspiPlatform.c st_qspiCommon.c st_qspiNegativeTestCase.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../stw_unit_test_component.mk

LNKCMD_FILE = lnk_m4.cmd

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
