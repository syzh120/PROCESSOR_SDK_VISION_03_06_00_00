#
# This file is the makefile for building BSP McSPI library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = bsp_mcspi

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk bios xdc edma
INCLUDE_INTERNAL_INTERFACES = csl

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../bsp_lld_component.mk ../.gitignore
PACKAGE_SRCS_COMMON += ../docs/Doxyfile ../docs/doxygen/tilogo.gif
PACKAGE_SRCS_COMMON += ../docs/doxygen/titagline.gif ../docs/doxygen/tifooter.htm
PACKAGE_SRCS_COMMON += ../docs/doxygen/tiheader.htm
# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += bsp_mcspi.c bsp_mcspiEdma.c

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
