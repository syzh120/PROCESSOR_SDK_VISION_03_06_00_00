#
# This file is the makefile for building VPS baremetal driver library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vpsdrv_baremetal

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS)
PACKAGE_SRCS_COMMON = .

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += vps_initDrv.c
ifeq ($(PACKAGE_VIP),yes)
  SRCS_COMMON += vps_vipDrv.c
  PACKAGE_SRCS_COMMON += ../../../include/vip/vps_vipDrv.h
endif
ifeq ($(PACKAGE_DSS),yes)
  SRCS_COMMON += vps_dctrlDrv.c vps_dssDrv.c
  PACKAGE_SRCS_COMMON += ../../../include/dss/vps_dctrlDrv.h ../../../include/dss/vps_dssDrv.h
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
