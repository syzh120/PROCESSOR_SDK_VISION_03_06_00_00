# File: env.mk. This file contains all the paths and other ENV variables

#
# Module paths
#

# Directory where all internal software packages are located; typically 
#  those that are checked into version controlled repository. In this case all
#  the OMX components and SDK/OMX demo.
INTERNAL_SW_ROOT ?= /data/datalocal1_videoapps01/user/pdp_jenkin_build/edma_release_build/edma3_lld_02_12_00_21

# Directory where all external (imported) software packages are located; typically 
#  those that are NOT checked into version controlled repository. In this case,
#  compiler tool chains, BIOS, XDC, Syslink, IPC, FC, CE, drivers, codecs, etc.
EXTERNAL_SW_ROOT ?= /datalocal1/ti_components

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
#DEST_ROOT = E:/Temp/edma3_lld_02_11_02_03

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
UTILS_INSTALL_DIR = $(EXTERNAL_SW_ROOT)/os_tools/linux/xdctools_3_32_01_22_core

# Set path separator, etc based on the OS
# On windows if sh.exe is installed (cygwin installs) make will execute
# commands on sh or it executes on windows cmd prompt. When executing on sh,
# unix style command seperator is used.
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/bin/
  ifeq (cygwin,$(findstring cygwin,$(PATH)))
  COMMAND_SEPERATOR = ;
  else
  COMMAND_SEPERATOR = &
  endif
else 
  # else, assume it is linux
  PATH_SEPARATOR = :
  COMMAND_SEPERATOR = ;
endif

# BIOS
bios_PATH = $(EXTERNAL_SW_ROOT)/os_tools/bios_6_46_04_53
bios_INCLUDE = $(bios_PATH)/packages

# XDC
xdc_PATH = $(EXTERNAL_SW_ROOT)/os_tools/linux/xdctools_3_32_01_22_core
xdc_INCLUDE = $(xdc_PATH)/packages

# EDMA3 LLD
edma3_lld_PATH = $(INTERNAL_SW_ROOT)
include $(edma3_lld_PATH)/packages/component.mk

#
# Tools paths
#
# Cortex-M3
CODEGEN_PATH_M3 = $(EXTERNAL_SW_ROOT)/cg_tools/linux/ti-cgt-arm_16.9.2.LTS
CODEGEN_PATH_M3_COFF = $(EXTERNAL_SW_ROOT)/cg_tools/linux/ti-cgt-arm_5.2.5
# Cortex-M4
CODEGEN_PATH_M4 = $(EXTERNAL_SW_ROOT)/cg_tools/linux/ti-cgt-arm_16.9.2.LTS
CODEGEN_PATH_M4_COFF = $(EXTERNAL_SW_ROOT)/cg_tools/linux/ti-cgt-arm_5.2.5
# Cortex-A8
CODEGEN_PATH_A8 = $(EXTERNAL_SW_ROOT)/cg_tools/linux/ti-cgt-arm_16.9.2.LTS
# Cortex-A8 GCC
CODEGEN_PATH_A8_GCC = $(EXTERNAL_SW_ROOT)/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3

# Cortex-A15
CODEGEN_PATH_A15 = $(EXTERNAL_SW_ROOT)/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3
# Cortex-A15_GCC
CODEGEN_PATH_A15_GCC = $(EXTERNAL_SW_ROOT)/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3

# ARM-9
CODEGEN_PATH_ARM9 = $(EXTERNAL_SW_ROOT)/cg_tools/linux/ti-cgt-arm_16.9.2.LTS
# ARM-9 GCC
CODEGEN_PATH_A9_GCC = $(EXTERNAL_SW_ROOT)/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3

# DSP - Since same toolchain does not support COFF and ELF, there are two entries
#        This would go away when one version supports both formats
CODEGEN_PATH_DSP = $(EXTERNAL_SW_ROOT)/cg_tools/linux/C6000_7.4.2
CODEGEN_PATH_DSPELF = $(EXTERNAL_SW_ROOT)/cg_tools/linux/C6000_7.4.2

# ARP32
CODEGEN_PATH_ARP32 = $(EXTERNAL_SW_ROOT)/cg_tools/linux/arp32_1.0.7

# Commands commonly used within the make files

RM = $(UTILSPATH)rm
RMDIR = $(UTILSPATH)rm -rf
MKDIR = $(UTILSPATH)mkdir

ifeq ($(OS),Windows_NT)
ECHO = $(UTILSPATH)echo
else
ECHO = /bin/echo
endif

# MAKE = $(UTILSPATH)make
EGREP = $(UTILSPATH)egrep
CP = $(UTILSPATH)cp

# This is to avoid using full blown cygwin - chmod is really needed only linux
ifeq ($(OS),Windows_NT)
CHMOD = @echo
else
CHMOD = $(UTILSPATH)chmod
endif

#
# XDC specific ENV variables
#

# XDC Config.bld file (required for configuro) ; Derives from top-level omx_PATH
CONFIG_BLD_XDC_674 = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_64p = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_64t = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_a8 = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_arm9 = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_66 = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_m3 = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_m4 = $(edma3_lld_PATH)/packages/_config.bld
CONFIG_BLD_XDC_a15 = $(edma3_lld_PATH)/packages/_config.bld

XDCPATH = $(bios_PATH)/packages;$(xdc_PATH)/packages;$(edma3_lld_PATH)/packages;
export XDCPATH

XDCROOT = $(xdc_PATH)
XDCTOOLS = $(xdc_PATH)
export XDCROOT
export XDCTOOLS

TMS470_CGTOOLS = $(CODEGEN_PATH_M3)
CGTOOLS = $(CODEGEN_PATH_DSP)
CGTOOLS_ELF = $(CODEGEN_PATH_DSPELF)
export TMS470_CGTOOLS

CODESOURCERYCGTOOLS = $(CODEGEN_PATH_A8)
export CODESOURCERYCGTOOLS

# Nothing beyond this point
