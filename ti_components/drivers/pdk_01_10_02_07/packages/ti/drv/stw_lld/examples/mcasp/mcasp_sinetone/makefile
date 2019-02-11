#
# This file is the makefile for building VPS DSS baremetal example application.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = drv_stw_lld_mcasp_sinetone_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl i2c_lld
COMP_LIST_COMMON += stw_platform stw_uartconsole stw_examples_utility

COMP_LIST_a15_0 = csl_init

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = mcasp_transmit_tda2xx.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = .

ifeq ($(CORE),a15_0)
 LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_a15.cmd
endif
ifeq ($(CORE),c66x)
 LNKCMD_FILE = $(PDK_CSL_COMP_PATH)/example/lnk_dsp.cmd
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
