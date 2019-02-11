#
# This file is the makefile for building CSL init library.
#

.PHONY : gensizes

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = csl_init

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk csl

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES += csl

# Common source files and CFLAGS across all platforms and cores

#Include src files for only the modules defined under csl_intc_COMP_LIST
SRCS_COMMON =
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON += makefile_init.mk

# A15 Init modules
-include $(PDK_CSL_COMP_PATH)/arch/a15/src/src_files_a15init.mk

#Arm9 modules
-include $(PDK_CSL_COMP_PATH)/arch/arm9/src/src_files_arm9init.mk
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
