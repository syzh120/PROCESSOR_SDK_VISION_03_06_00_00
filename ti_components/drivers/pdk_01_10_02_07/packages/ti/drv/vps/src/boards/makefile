#
# This file is the makefile for building VPS boards library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vps_boards

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl vps_common vps_osal_tirtos fvid2 vps_devices

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS) $(VPSDRV_CFLAGS)
PACKAGE_SRCS_COMMON = . ../../include/boards

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = bsp_board.c
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex tda3xx))
  ifeq ($(BOARD), $(filter $(BOARD), tda2xx-rvp))
    SRCS_COMMON += bsp_boardTda2xxRvp.c
  else
    SRCS_COMMON += bsp_boardTda2xx.c
  endif
  SRCS_COMMON += bsp_boardTda2ex.c bsp_boardTda3xx.c
endif

ifeq ($(SOC),$(filter $(SOC), am574x am572x am571x))
  SRCS_COMMON += bsp_boardAm572x.c
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
