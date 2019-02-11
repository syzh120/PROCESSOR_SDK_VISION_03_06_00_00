# Dependency Versions
XDC_VERSION=3_32_00_06_core
NDK_VERSION=2_24_02_31
BIOS_VERSION=6_46_00_23
UIA_VERSION=2_00_05_50
EDMA3_VERSION=02_12_00_20
NSP_VERSION=4_15_00_00

ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR    = ;
  TOOLS_DIR         ?= c:/ti
else
  # else, assume it is linux
  PATH_SEPARATOR    = :
  TOOLS_DIR         ?= /opt/ti
endif
COMPILER_DIR    ?= $(TOOLS_DIR)/ccsv6/tools/compiler

#
# Dependency components paths
#
XDC_ROOT        ?= $(TOOLS_DIR)/xdctools_$(XDC_VERSION)
NDK_ROOT        ?= $(TOOLS_DIR)/ndk_$(NDK_VERSION)
BIOS_ROOT       ?= $(TOOLS_DIR)/bios_$(BIOS_VERSION)
UIA_ROOT        ?= $(TOOLS_DIR)/uia_$(UIA_VERSION)
EDMA3_ROOT      ?= $(TOOLS_DIR)/edma3_lld_$(EDMA3_VERSION)
NSP_ROOT        ?= $(TOOLS_DIR)/nsp_gmacsw_$(NSP_VERSION)

#
# CodeGen/Compiler tools paths
#
TIARMCGT_ROOT   ?= $(COMPILER_DIR)/ti-cgt-arm_5.2.5
GCC_ROOT        ?= $(COMPILER_DIR)/gcc-arm-none-eabi-4_9-2015q3
CGT6X_ROOT      ?= $(COMPILER_DIR)/C6000_7.4.2

export XDC_ROOT
export NDK_ROOT
export BIOS_ROOT
export UIA_ROOT
export NSP_ROOT
export TIARMCGT_ROOT
export GCC_ROOT
export CGT6X_ROOT
export EDMA3_ROOT
export EDMA3_VERSION
