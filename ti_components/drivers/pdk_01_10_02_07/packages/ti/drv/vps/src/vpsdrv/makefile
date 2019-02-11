#
# This file is the makefile for building VPS Driver library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vpsdrv

SRCDIR = src captdrv captdrv/src vpedrv vpedrv/src dispdrv dispdrv/src m2mdrv/src
INCDIR = . m2mdrv/src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = vps_common vps_osal_tirtos vps_fvid2 vps_vpslib

# Common source files and CFLAGS across all platforms and cores
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS) $(VPSDRV_CFLAGS)

SRCS_COMMON =
ifneq ($(PACKAGE_SELECT),vps-hal-only)
SRCS_COMMON += vpsdrv_init.c vpsdrv_control.c
PACKAGE_SRCS_COMMON = makefile vpsdrv_control.h ../../../include/vps_control.h
PACKAGE_SRCS_COMMON += src
  ifeq ($(PACKAGE_VIP),yes)
    capt_drv = yes
  endif
  ifeq ($(PACKAGE_ISP),yes)
    ifneq ($(PACKAGE_VIP),yes)
        capt_drv = yes
    endif
  endif
  ifeq ($(capt_drv),yes)
    include captdrv/src_files_captdrv.mk
  endif
  ifeq ($(PACKAGE_VPE),yes)
    include vpedrv/src_files_vpedrv.mk
  endif
  ifeq ($(PACKAGE_DSS),yes)
    include dispdrv/src_files_dispdrv.mk
    include m2mdrv_dss/src_files_m2mdrv_dss.mk
  endif
  ifeq ($(PACKAGE_M2M),yes)
    include m2mdrv/src_files_m2mdrv.mk
  endif
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
