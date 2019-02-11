XDC_VERSION=3_32_01_22_core
NDK_VERSION=2_24_02_31
BIOS_VERSION=6_46_06_00
UIA_VERSION=2_00_05_50
EDMA3_VERSION=02_12_00_21


ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR    = ;
  TOOLS_DIR         ?= c:/ti
else
  # else, assume it is linux
  PATH_SEPARATOR    = :
  TOOLS_DIR         ?= /opt/ti
endif
COMPILER_DIR    ?= $(TOOLS_DIR)/ccsv7/tools/compiler

#
# Dependency components paths
#
XDC_ROOT        ?= $(TOOLS_DIR)/xdctools_$(XDC_VERSION)
NDK_ROOT        ?= $(TOOLS_DIR)/ndk_$(NDK_VERSION)
BIOS_ROOT       ?= $(TOOLS_DIR)/bios_$(BIOS_VERSION)
UIA_ROOT        ?= $(TOOLS_DIR)/uia_$(UIA_VERSION)
EDMA3_ROOT      ?= $(TOOLS_DIR)/edma3_lld_$(EDMA3_VERSION)

#
# CodeGen/Compiler tools paths
#
TIARMCGT_ROOT   ?= $(COMPILER_DIR)/ti-cgt-arm_16.9.2.LTS
GCC_ROOT        ?= $(COMPILER_DIR)/gcc-arm-none-eabi-4_9-2015q3
CGT6X_ROOT      ?= $(COMPILER_DIR)/ti-cgt-c6000_8.2.4

export XDC_ROOT
export NDK_ROOT
export BIOS_ROOT
export UIA_ROOT
export TIARMCGT_ROOT
export GCC_ROOT
export CGT6X_ROOT
export EDMA3_ROOT
export EDMA3_VERSION
