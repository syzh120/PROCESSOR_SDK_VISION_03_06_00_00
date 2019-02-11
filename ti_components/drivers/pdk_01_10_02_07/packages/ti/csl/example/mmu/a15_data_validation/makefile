#
# This file is the makefile for building A15 MMU Data Validation App.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = csl_mmu_a15_data_validation_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk csl_arch

# List all the components required by the application
COMP_LIST_COMMON += csl csl_utils_common csl_uart_console
COMP_LIST_a15_0 = csl_init

# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .
SRCS_COMMON = mmu_a15_data_validation_app_main.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

ifeq ($(CORE),a15_0)
 LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_a15.cmd
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
