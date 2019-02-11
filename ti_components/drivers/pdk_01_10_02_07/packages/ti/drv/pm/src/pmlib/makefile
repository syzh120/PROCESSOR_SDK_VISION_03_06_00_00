#
# This file is the makefile for building PM HAL library.
#
#   Copyright (c) Texas Instruments Incorporated 2015
#

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk csl

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON +=
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra75x tda2ex am571x dra72x tda3xx dra78x am574x))
    include prcm/src_files.mk
endif

PACKAGE_SRCS_COMMON = . ../../makefile ../../makefile.mk ../../pm_component.mk \
                      ../../pmhal.h ../../pmlib.h \
                      ../../docs/ReleaseNotes_PM_LLD.pdf ../../docs/Doxyfile \
                      ../../docs/doxygen \
                      ../../include
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
