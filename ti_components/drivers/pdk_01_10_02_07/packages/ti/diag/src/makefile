#
# This file is the makefile for building SAFETY DIAG library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = diag

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = diagLib_adc.h diagLib_can.h diagLib_crc.h diagLib_ecc.h
PACKAGE_SRCS_COMMON += diagLib_mcspi.h diag_component.mk docs src .gitignore

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += diagLib_utils.c
SRCS_COMMON += diagLib_ecc.c diagLib_eccEmif.c diagLib_eccOcmc.c
SRCS_COMMON += diagLib_mcspi.c
SRCS_COMMON += diagLib_can.c
SRCS_tda3xx += diagLib_adc.c diagLib_crc.c
SRCS_tda3xx += diagLib_eccIpu.c

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
