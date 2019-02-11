#
# This file is the makefile for building CSL gpio app.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = sbl_multicore_mbx

SRCDIR = .
INCDIR =

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON += csl csl_utils_common csl_uart_console
COMP_LIST_a15_0 = csl_init

# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

ifeq ($(CORE),ipu1_0)
 SRCS_COMMON = sbl_mbx_ipu1_cpu0.c
 LNKCMD_FILE = lnk_ipu1_cpu0.cmd
endif
ifeq ($(CORE),ipu1_1)
 SRCS_COMMON = sbl_mbx_ipu1_cpu1.c
 LNKCMD_FILE = lnk_ipu1_cpu1.cmd
endif
ifeq ($(CORE),c66xdsp_1)
 SRCS_COMMON = sbl_mbx_dsp1.c
 LNKCMD_FILE = lnk_dsp1.cmd
endif
ifeq ($(CORE),a15_0)
 SRCS_COMMON = sbl_mbx_mpu_cpu0.c
 LNKCMD_FILE = lnk_mpu_cpu0.cmd
endif

LNKFLAGS_LOCAL_a15_0 += --entry Entry

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
