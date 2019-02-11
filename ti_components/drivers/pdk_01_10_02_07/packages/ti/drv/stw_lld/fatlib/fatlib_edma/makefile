#
# This file is the makefile for building STW FATLIB EDMA library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = stw_fatlib_edma

SRCDIR = fatlib_edma
INCDIR = fatlib_edma

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(STW_LLD_CFLAGS)
PACKAGE_SRCS_COMMON = fatlib_edma

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += hsmmcsd_edma.c

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
