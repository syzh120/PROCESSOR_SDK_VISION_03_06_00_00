#
# This file is the makefile for building VPS library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vpslib

SRCDIR = drv common common/src hal hal/src                                     \
         captcore captcore/src                                                 \
         vpecore vpecore/src                                                   \
         dispcore dispcore/src                                                 \
         isscore isscore/src                                                   \
         calcore calcore/src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl vps_common vps_osal_tirtos

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS)
PACKAGE_SRCS_COMMON = makefile ../../vps_component.mk ../../.gitignore ../../makefile ../../docs

include hal/src_files_hal.mk
ifneq ($(PACKAGE_SELECT),vps-hal-only)
  include common/src_files_common.mk
  ifeq ($(PACKAGE_VIP),yes)
    include captcore/src_files_captcore.mk
  endif
  ifeq ($(PACKAGE_VPE),yes)
    include vpecore/src_files_vpecore.mk
  endif
  ifeq ($(PACKAGE_DSS),yes)
    include dispcore/src_files_dispcore.mk
  endif
  ifeq ($(PACKAGE_ISS_COMMON), yes)
    include isscore/src_files_isscore.mk
  endif
  ifeq ($(PACKAGE_CAL), yes)
      include calcore/src_files_calcore.mk
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
