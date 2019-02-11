#
# Copyright (c) 2013-2018, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#Default build environment, (Windows_NT / linux)
#if nothing is defined, default to linux as in windows this variable is defined
export OS ?= linux

ifeq ($(OS),Windows_NT)
    SDK_INSTALL_PATH ?= $(abspath ../../../../../..)
else
    #Paths for linux machine
    SDK_INSTALL_PATH ?=$(abspath ../../../../../..)
endif
TOOLS_INSTALL_PATH ?= $(SDK_INSTALL_PATH)

#Default BUILD_OS_TYPE (tirtos/baremetal)
export BUILD_OS_TYPE ?= tirtos

# Default board
# Supported values are printed in "make -s help" option. Below are the list for reference.
#                   evmDRA72x, evmDRA75x, evmDRA78x,
#                   evmAM572x, idkAM571x, idkAM572x idkAM574x
#                   evmK2H, evmK2K, evmK2E, evmK2L, evmK2G, evmC6678, evmC6657,
#                   evmAM335x, icev2AM335x, iceAMIC110, skAM335x, bbbAM335x,
#                   evmAM437x idkAM437x skAM437x evmOMAPL137 lcdkOMAPL138
#                   And also refer $(BOARD_LIST_J6_TDA) below
#
ifeq ($(LIMIT_BOARDS),)
  # TDA parts do not define this environment variable, default board and soc for TDA parts
  export BOARD ?= tda2xx-evm
  export SOC ?= tda2xx
else
  # default board and soc for Catalog parts
  export BOARD ?= idkAM572x
  export SOC   ?= am572x
endif

################################################################################
# Other user configurable variables
################################################################################

# Default to m4 build depending on BOARD selected!!
ifeq ($(BOARD),$(filter $(BOARD), evmAM572x idkAM572x idkAM571x idkAM574x))
  CORE ?= a15_0
endif
CORE ?= ipu1_0
export CORE

# Default Build Profile
# Supported Values: debug | release
export BUILD_PROFILE ?= release

# Treat compiler warning as error
# Supported Values: yes | no
export TREAT_WARNINGS_AS_ERROR ?= yes

#Various boards support for J6 TDA family of devices
BOARD_LIST_J6_TDA = tda2xx-evm tda2ex-evm tda3xx-evm tda2px-evm
BOARD_LIST_J6_TDA += tda2xx-evm-radar tda2px-evm-radar tda3xx-evm-radar
BOARD_LIST_J6_TDA += tda3xx-ar12-booster tda3xx-ar12-alps tda3xx-ar12-rvp
BOARD_LIST_J6_TDA += tda2ex-eth-srv tda2xx-rvp tda3xx-rvp
BOARD_LIST_J6_TDA += tda2xx-cascade-radar

################################################################################
# Configure toolchain paths
################################################################################
ifeq ($(BOARD),$(filter $(BOARD), $(BOARD_LIST_J6_TDA)))
  # This section applies to J6 TDA SOCs in Processor SDK VISION release.
  # For remaining SOC/BOARDS skip to the else part.
  # SoC & Version of PDK for TDA builds
  PDK_SOC=
  PDK_VERSION=01_10_02_07

  #Tool versions for TDA builds
  GCC_CROSS_TOOL_PREFIX=arm-none-eabi-
  GCC_CROSS_TOOL_TAG=4_9-2015q3
  CGT_VERSION=8.2.4
  GCC_VERSION_FPULIB=4.9.3
  CGT_ARM_VERSION=16.9.2.LTS
  CGT_ARP32_VERSION=1.0.7

  #Component versions for TDA builds
  BIOS_VERSION=6_46_06_00
  EDMA_VERSION=02_12_00_21
  XDC_VERSION=3_32_01_22_core
  MSHIELD_VERSION=4_5_3
  export mmwavelink_version=mmwave_dfp_01_02_00_00

  export GCC_FLOAT_PATH ?= FPU
else
  # This section applies to all broader set of boards with SOCs beyond TDA class
  # in Processor SDK RTOS release

  #Tool versions for non-TDA builds
  GCC_CROSS_TOOL_PREFIX=arm-none-eabi-
  GCC_CROSS_TOOL_TAG=6-2017-q1-update
  CGT_VERSION=8.2.2
  GCC_VERSION_HARDLIB=6.3.1
  CGT_ARM_VERSION=16.9.3.LTS
  CGT_ARP32_VERSION=1.0.8
  CG_XML_VERSION=2_41_00

  #Component versions for non-TDA builds
  BIOS_VERSION=6_52_00_12
  EDMA_VERSION=2_12_05_30C
  XDC_VERSION=3_50_03_33_core
  MSHIELD_VERSION=4_5_3
  CGT_PRU_VERSION=2.2.1
  #Hardcode IPC version if it is not set already
  IPC_VERSION ?= 3_47_01_00
  NDK_VERSION=2_26_00_08
  UIA_VERSION=2_21_02_07
  XDAIS_VERSION=7_24_00_04
  AER_VERSION=17_0_0_0

  # C674x DSP libraries sould be used for OMAPL13x platform
ifeq ($(SOC),$(filter $(SOC), omapl137 omapl138))
  DSPLIB_VERSION ?= c674x_3_4_0_0
  IMGLIB_VERSION ?= c674x_3_1_1_0
  MATHLIB_VERSION ?= c674x_3_1_1_0
else
  DSPLIB_VERSION ?= c66x_3_4_0_0
  IMGLIB_VERSION ?= c66x_3_1_1_0
  MATHLIB_VERSION ?= c66x_3_1_1_0
endif

  export GCC_FLOAT_PATH ?= HARD
endif

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
# This could be in CCS install directory as in c:/ti/ccsv7/utils/cygwin or
# the XDC install bin folder $(XDC_INSTALL_PATH)/bin
ifeq ($(OS),Windows_NT)
  export utils_PATH ?= c:/ti/ccsv7/utils/cygwin
endif

################################################################################
# Dependent toolchain paths variables
################################################################################
# Version of GCC
GCC_VERSION=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
GCC_VERSION_ARM_A15=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
ifeq ($(BOARD),$(filter $(BOARD), $(BOARD_LIST_J6_TDA)))
  # This section applies to J6 TDA SOCs in Processor SDK VISION release.
  # For remaining SOC/BOARDS skip to the else part.
  ifeq ($(OS),Windows_NT)
    OS_FOLDER=windows
  else
    OS_FOLDER=linux
  endif
  export TOOLCHAIN_PATH_GCC        ?= $(SDK_INSTALL_PATH)/ti_components/cg_tools/$(OS_FOLDER)/gcc-$(GCC_VERSION)
  export TOOLCHAIN_PATH_A15        ?= $(SDK_INSTALL_PATH)/ti_components/cg_tools/$(OS_FOLDER)/gcc-$(GCC_VERSION_ARM_A15)
  export TOOLCHAIN_PATH_M4         ?= $(SDK_INSTALL_PATH)/ti_components/cg_tools/$(OS_FOLDER)/ti-cgt-arm_$(CGT_ARM_VERSION)
  export C6X_GEN_INSTALL_PATH      ?= $(SDK_INSTALL_PATH)/ti_components/cg_tools/$(OS_FOLDER)/ti-cgt-c6000_$(CGT_VERSION)
  export TOOLCHAIN_PATH_EVE        ?= $(SDK_INSTALL_PATH)/ti_components/cg_tools/$(OS_FOLDER)/arp32_$(CGT_ARP32_VERSION)
  export PDK_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/ti_components/drivers/pdk_$(PDK_VERSION)/packages
  export EDMA3LLD_BIOS6_INSTALLDIR ?= $(SDK_INSTALL_PATH)/ti_components/drivers/edma3_lld_$(EDMA_VERSION)
  export BIOS_INSTALL_PATH         ?= $(SDK_INSTALL_PATH)/ti_components/os_tools/bios_$(BIOS_VERSION)
  export XDC_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/ti_components/os_tools/$(OS_FOLDER)/xdctools_$(XDC_VERSION)
  export RADARLINK_INSTALL_PATH    ?= $(SDK_INSTALL_PATH)/ti_components/radar/$(mmwavelink_version)
  export MSHIELD_DK_DIR            ?= $(SDK_INSTALL_PATH)/ti_components/mshield-dk_std_$(MSHIELD_VERSION)
  export TI_SECURE_DEV_PKG         := $(MSHIELD_DK_DIR)
else
  export GCC_VERSION_ARM_A8=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
  export GCC_VERSION_ARM_A9=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
  export CROSS_TOOL_PRFX           ?= $(GCC_CROSS_TOOL_PREFIX)
  export C6X_GEN_INSTALL_PATH      ?= $(SDK_INSTALL_PATH)/ti-cgt-c6000_$(CGT_VERSION)
  export CL_PRU_INSTALL_PATH       ?= $(SDK_INSTALL_PATH)/ti-cgt-pru_$(CGT_PRU_VERSION)
  export TOOLCHAIN_PATH_A8         ?= $(SDK_INSTALL_PATH)/gcc-$(GCC_VERSION_ARM_A8)
  export TOOLCHAIN_PATH_A9         ?= $(SDK_INSTALL_PATH)/gcc-$(GCC_VERSION_ARM_A9)
  export TOOLCHAIN_PATH_Arm9       ?= $(SDK_INSTALL_PATH)/ti-cgt-arm_$(CGT_ARM_VERSION)
  export TOOLCHAIN_PATH_A15        ?= $(SDK_INSTALL_PATH)/gcc-$(GCC_VERSION_ARM_A15)
  export TOOLCHAIN_PATH_EVE        ?= $(TOOLS_INSTALL_PATH)/arp32_$(CGT_ARP32_VERSION)
  export TOOLCHAIN_PATH_M4         ?= $(SDK_INSTALL_PATH)/ti-cgt-arm_$(CGT_ARM_VERSION)
  export TOOLCHAIN_PATH_GCC        ?= $(SDK_INSTALL_PATH)/gcc-$(GCC_VERSION)
  export BIOS_INSTALL_PATH         ?= $(SDK_INSTALL_PATH)/bios_$(BIOS_VERSION)
  export DSPLIB_INSTALL_PATH       ?= $(SDK_INSTALL_PATH)/dsplib_$(DSPLIB_VERSION)
  export EDMA3LLD_BIOS6_INSTALLDIR ?= $(SDK_INSTALL_PATH)/edma3_lld_$(EDMA_VERSION)
  export IMGLIB_INSTALL_PATH       ?= $(SDK_INSTALL_PATH)/imglib_$(IMGLIB_VERSION)
  export IPC_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/ipc_$(IPC_VERSION)
  export MATHLIB_INSTALL_PATH      ?= $(SDK_INSTALL_PATH)/mathlib_$(MATHLIB_VERSION)
  export NDK_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/ndk_$(NDK_VERSION)
  export PDK_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/pdk_$(PDK_SOC)_$(PDK_VERSION)/packages
  export UIA_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/uia_$(UIA_VERSION)
  export XDC_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/xdctools_$(XDC_VERSION)
  export UTILS_INSTALL_DIR         ?= $(XDC_INSTALL_PATH)/bin
  export RADARLINK_INSTALL_PATH    ?= $(SDK_INSTALL_PATH)/$(mmwavelink_version)
  export CG_XML_BIN_INSTALL_PATH   ?= $(SDK_INSTALL_PATH)/cg_xml_$(CG_XML_VERSION)/bin
  export MSHIELD_DK_DIR            ?= $(SDK_INSTALL_PATH)/mshield-dk_std_$(MSHIELD_VERSION)
  export TI_SECURE_DEV_PKG         ?= $(MSHIELD_DK_DIR)
  export XDAIS_INSTALL_PATH        ?= $(SDK_INSTALL_PATH)/xdais_$(XDAIS_VERSION)
  export AER_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/aer_c64Px_obj_$(AER_VERSION)
endif

ifeq ($(SOC),$(filter $(SOC), am335x))
  export HARDLIB_PATH ?= $(TOOLCHAIN_PATH_A8)/lib/gcc/arm-none-eabi/$(GCC_VERSION_HARDLIB)/hard
  export FPULIB_PATH ?= $(TOOLCHAIN_PATH_A8)/lib/gcc/arm-none-eabi/$(GCC_VERSION_FPULIB)/fpu
else ifeq  ($(SOC),$(filter $(SOC), am437x))
  export HARDLIB_PATH ?= $(TOOLCHAIN_PATH_A9)/lib/gcc/arm-none-eabi/$(GCC_VERSION_HARDLIB)/hard
  export FPULIB_PATH ?= $(TOOLCHAIN_PATH_A9)/lib/gcc/arm-none-eabi/$(GCC_VERSION_FPULIB)/fpu
else
  export HARDLIB_PATH ?= $(TOOLCHAIN_PATH_A15)/lib/gcc/arm-none-eabi/$(GCC_VERSION_HARDLIB)/hard
  export FPULIB_PATH ?= $(TOOLCHAIN_PATH_A15)/lib/gcc/arm-none-eabi/$(GCC_VERSION_FPULIB)/fpu
endif

export CGTOOLS=$(C6X_GEN_INSTALL_PATH)
export XDCCGROOT=$(C6X_GEN_INSTALL_PATH)

################################################################################
# Other advanced configurable variables
################################################################################

# Set Core Build Profile depending on BUILD_PROFILE value
export BUILD_PROFILE_$(CORE) ?= $(BUILD_PROFILE)

# Default PACKAGE_SELECT build flag
# Supported values: all, vps-hal-only, vps-vip-only, vps-vpe-only, vps-dss-only, vps-vip-dss, vps-vip-vpe
export PACKAGE_SELECT ?= all

# Disable recursive building of example dependencies
export DISABLE_RECURSE_DEPS ?= no

# Default C++ build flag, yes or no
export CPLUSPLUS_BUILD ?= no

#use <module>_PATH variable as makefile internally expects PATH variable this way for external component path
export pdk_PATH := $(PDK_INSTALL_PATH)
export bios_PATH := $(BIOS_INSTALL_PATH)
export xdc_PATH := $(XDC_INSTALL_PATH)
export edma3_lld_PATH := $(EDMA3LLD_BIOS6_INSTALLDIR)
export ndk_PATH := $(NDK_INSTALL_PATH)
export radarLink_PATH := $(RADARLINK_INSTALL_PATH)

export ROOTDIR := $(pdk_PATH)
XDCPATH =
ifeq ($(BUILD_OS_TYPE),tirtos)
  XDCPATH = $(bios_PATH)/packages;$(xdc_PATH)/packages;$(edma3_lld_PATH)/packages;$(ndk_PATH)/packages;$(pdk_PATH);
endif
export XDCPATH

#Default SECTTI SIZE INFORMATION
export SECTTI_SIZE_INFO ?= no

#Default SECTTI tool
export SECTTI ?= $(CG_XML_BIN_INSTALL_PATH)/sectti

# include other dependent files
include $(PDK_INSTALL_PATH)/ti/build/comp_paths.mk
ifeq ($(MAKERULEDIR), )
  #Makerule path not defined, define this and assume relative path from ROOTDIR
  export MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
endif
include $(MAKERULEDIR)/build_config.mk
include $(MAKERULEDIR)/platform.mk
include $(MAKERULEDIR)/env.mk
