#
# This file is the makefile for building ddr test app.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = csl_ddr_test_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl
COMP_LIST_COMMON += csl_utils_common csl_uart_console

COMP_LIST_a15_0 = csl_init

# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .
SRCS_COMMON = main.c ddr_test.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

ifeq ($(CORE),a15_0)
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px))
 LNKCMD_FILE = ./lnk_a15_ocmc.cmd
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
 LNKCMD_FILE = ./lnk_tda2ex_a15_ocmc.cmd
endif
endif
ifeq ($(CORE),ipu1_0)
ifeq ($(SOC),$(filter $(SOC), tda3xx))
 LNKCMD_FILE = ./lnk_tda3xx_m4_ocmc.cmd
endif
endif

LNKFLAGS_LOCAL_a15host += --entry Entry

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
