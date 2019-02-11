#
# This file is the makefile for building RTI unit test application (rti_dwwd_wz_50).
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = rti_dwwd_wz_50_unit_test_app

SRCDIR = . ../rti_common
INCDIR = . ../rti_common

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON  = csl
COMP_LIST_COMMON += stw_platform stw_uartconsole stw_examples_utility

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += rti_testcase.c rti_dwwd_wz50_main.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON = . ../makefile ../rti_common
PACKAGE_SRCS_COMMON += ../../lnk_m4.cmd ../../lnk_dsp.cmd ../../lnk_arp32.cmd
PACKAGE_SRCS_COMMON += ../../stw_unit_test_component.mk

ifeq ($(CORE),ipu1_0)
  LNKCMD_FILE = ../../lnk_m4.cmd
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
