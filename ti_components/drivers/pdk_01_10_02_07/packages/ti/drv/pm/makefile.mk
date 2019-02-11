#
# This file is the makefile for building PM HAL library.
#
#   Copyright (c) Texas Instruments Incorporated 2015
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = pm_rtos

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk csl
INCLUDE_INTERNAL_INTERFACES += pm_hal pm_lib

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON +=
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra72x dra75x tda2ex am571x tda3xx dra78x am574x))
    include src/pmrtos/prcm/src_files.mk
    include src/pmhal/prcm/src_files.mk
    include src/pmlib/prcm/src_files.mk
endif

PACKAGE_SRCS_COMMON = makefile makefile.mk pm_component.mk .gitignore \
                      pmhal.h pmlib.h Power.h PowerDevice.h PowerExtended.h \
                      docs/doxygen docs/Doxyfile docs/ReleaseNotes_PM_LLD.pdf \
                      docs/training examples include src
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(PM_CFLAGS)

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
