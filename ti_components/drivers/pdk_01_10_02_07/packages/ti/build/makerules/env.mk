#
# Copyright (c) 2013-2016, Texas Instruments Incorporated
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

# File: env.mk. This file contains all the paths and other ENV variables

#
# Module paths
#

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
DEST_ROOT ?= $(pdk_PATH)/ti/binary

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
UTILS_INSTALL_DIR ?= $(utils_PATH)

# Set path separator, etc based on the OS
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/
  export SHELL := $(UTILSPATH)sh.exe
else
  # else, assume it is linux
  PATH_SEPARATOR = :
  UTILSPATH = /bin/
endif

ifeq ($(BUILD_OS_TYPE),tirtos)
  # BIOS
  bios_INCLUDE = $(bios_PATH)/packages
  export bios_INCLUDE

  # XDC
  xdc_INCLUDE = $(xdc_PATH)/packages
  export xdc_INCLUDE

  # EDMA
  edma_INCLUDE = $(edma3_lld_PATH)/packages
  export edma_INCLUDE
  # - used to ignore include if component not present
  -include $(edma3_lld_PATH)/packages/component.mk

  # NDK
  ndk_INCLUDE = $(ndk_PATH)/packages
  export ndk_INCLUDE
endif

#Below applicable only for TDA devices
# Radar mmwavelink
radarLink_INCLUDE = $(radarLink_PATH) \
                    $(radarLink_PATH)/ti/control/mmwavelink/include \
                    $(radarLink_PATH)/ti/control/mmwavelink/src     \
                    $(radarLink_PATH)/ti/control/mmwavelink
radarFirmware_INCLUDE = $(radarMssFirmware_PATH) $(radarBssFirmware_PATH)   \
                        $(radarLink_PATH)/firmware
export radarLink_INCLUDE
export radarFirmware_INCLUDE

# PDK
pdk_INCLUDE = $(pdk_PATH)

# Add additional pdk include paths if sub-components are in different directories
ifneq ($(PDK_CSL_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_CSL_ROOT_PATH)
endif
ifneq ($(PDK_PM_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_PM_ROOT_PATH)
endif
ifneq ($(PDK_OSAL_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_OSAL_ROOT_PATH)
endif
ifneq ($(PDK_I2C_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_I2C_ROOT_PATH)
endif
ifneq ($(PDK_VPS_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_VPS_ROOT_PATH)
endif
ifneq ($(PDK_GPIO_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_GPIO_ROOT_PATH)
endif
ifneq ($(PDK_FATFS_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_FATFS_ROOT_PATH)
endif
ifneq ($(PDK_MMCSD_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_MMCSD_ROOT_PATH)
endif
ifneq ($(PDK_PCIE_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_PCIE_ROOT_PATH)
endif
ifneq ($(PDK_USB_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_USB_ROOT_PATH)
endif
ifneq ($(PDK_MCASP_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_MCASP_ROOT_PATH)
endif
ifneq ($(PDK_MCBSP_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_MCBSP_ROOT_PATH)
endif
ifneq ($(PDK_PROFILING_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_PROFILING_ROOT_PATH)
endif
ifneq ($(PDK_PRUSS_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_PRUSS_ROOT_PATH)
endif
ifneq ($(PDK_NIMU_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_NIMU_ROOT_PATH)
endif
ifneq ($(PDK_NIMU_ICSS_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_NIMU_ICSS_ROOT_PATH)
endif
ifneq ($(PDK_ICSS_EMAC_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_ICSS_EMAC_ROOT_PATH)
endif
ifneq ($(PDK_EMAC_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_EMAC_ROOT_PATH)
endif
ifneq ($(PDK_UART_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_UART_ROOT_PATH)
endif
ifneq ($(PDK_SPI_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_SPI_ROOT_PATH)
endif
ifneq ($(PDK_BOARD_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_BOARD_ROOT_PATH)
endif
ifneq ($(PDK_GPMC_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_GPMC_ROOT_PATH)
endif

#Below are used for TDA/DRA SBL
ifneq ($(PDK_STW_LLD_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_STW_LLD_ROOT_PATH)
endif
ifneq ($(PDK_SBL_AUTO_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_SBL_AUTO_ROOT_PATH)
endif
ifneq ($(PDK_NORFLASH_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_NORFLASH_ROOT_PATH)
endif
ifneq ($(PDK_QSPIFLASH_ROOT_PATH), $(pdk_PATH))
  pdk_INCLUDE += $(PDK_QSPIFLASH_ROOT_PATH)
endif
export pdk_INCLUDE

include $(pdk_PATH)/ti/build/makerules/component.mk

# Package Relative path and destination directory
PACKAGE_RELPATH = pdk_/packages
PACKAGE_ROOT = $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_RELPATH)
export PACKAGE_RELPATH
export PACKAGE_ROOT

#
# Tools paths
#

# Cortex-A8
CODEGEN_PATH_A8 =

# DSP
CODEGEN_PATH_C674 = $(C6X_GEN_INSTALL_PATH)


# Commands commonly used within the make files
RM = $(UTILSPATH)rm
MV = $(UTILSPATH)mv
RMDIR = $(UTILSPATH)rm -rf
MKDIR = $(UTILSPATH)mkdir
ECHO = @$(UTILSPATH)echo

#emake provides detailed info for build analysis.
EMAKE = emake --emake-emulation=gmake --emake-gen-subbuild-db=1 --emake-annodetail=waiting

ifeq ($(OS),Windows_NT)
  MAKE = gmake
#  MAKE =  $(EMAKE)
else
  MAKE = make
endif
EGREP = $(UTILSPATH)egrep
CP = $(UTILSPATH)cp
ifeq ($(OS),Windows_NT)
  CHMOD = $(UTILSPATH)echo
else
  CHMOD = $(UTILSPATH)chmod
endif

ifeq ($(BUILD_OS_TYPE),tirtos)
  #
  # XDC specific ENV variables
  #
  # XDC Config.bld file (required for configuro); Derives from top-level pdk_PATH
  ifeq ($(SOC),tda2xx)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx_c66.bld
    endif
  endif

  ifeq ($(SOC),tda2px)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx_c66.bld
    endif
  endif

  ifeq ($(SOC),dra75x)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda2xx/config_tda2xx_c66.bld
    endif
  endif

  ifeq ($(SOC),tda2ex)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/tda2ex/config_tda2ex_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/tda2ex/config_tda2ex.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda2ex/config_tda2ex_c66.bld
    endif
  endif

  ifeq ($(SOC),dra72x)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/tda2ex/config_tda2ex_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/tda2ex/config_tda2ex.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda2ex/config_tda2ex_c66.bld
    endif
  endif

  ifeq ($(SOC),tda3xx)
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4   = $(pdk_PATH)/ti/build/tda3xx/config_tda3xx.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda3xx/config_tda3xx_c66.bld
    endif
  endif

  ifeq ($(SOC),dra78x)
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4   = $(pdk_PATH)/ti/build/tda3xx/config_tda3xx.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/tda3xx/config_tda3xx_c66.bld
    endif
  endif

  ifeq ($(SOC),am571x)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/am571x/config_am571x_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/am571x/config_am571x.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/am571x/config_am571x_c66.bld
    endif
  endif

  ifeq ($(SOC),am572x)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/am572x/config_am572x_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/am572x/config_am572x.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/am572x/config_am572x_c66.bld
    endif
  endif

  ifeq ($(SOC),am574x)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/am574x/config_am574x_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_m4),)
        CONFIG_BLD_XDC_m4     = $(pdk_PATH)/ti/build/am574x/config_am574x.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66     = $(pdk_PATH)/ti/build/am574x/config_am574x_c66.bld
    endif
  endif

  ifeq ($(SOC),am335x)
    ifeq ($(CONFIG_BLD_XDC_a8),)
     CONFIG_BLD_XDC_a8 = $(pdk_PATH)/ti/build/am335x/config_am335x_a8.bld
    endif
  endif

  ifeq ($(SOC),am437x)
    ifeq ($(CONFIG_BLD_XDC_a9),)
     CONFIG_BLD_XDC_a9 = $(pdk_PATH)/ti/build/am437x/config_am437x_a9.bld
    endif
  endif

  ifeq ($(SOC),k2g)
    ifeq ($(CONFIG_BLD_XDC_a15),)
     CONFIG_BLD_XDC_a15 = $(pdk_PATH)/ti/build/k2g/config_k2g_a15.bld
    endif
    ifeq ($(CONFIG_BLD_XDC_c66),)
      CONFIG_BLD_XDC_c66 = $(pdk_PATH)/ti/build/k2g/config_k2g_c66.bld
    endif
  endif

  XDCROOT = $(xdc_PATH)
  XDCTOOLS = $(xdc_PATH)
  BIOSROOT = $(bios_PATH)
  export XDCROOT
  export XDCTOOLS
  export BIOSROOT
endif

CGTOOLS = $(TOOLCHAIN_PATH_M4)
export CGTOOLS

CGTOOLS_DSP = $(CODEGEN_PATH_C674)
export CGTOOLS_DSP

CGTOOLS_A8 = $(TOOLCHAIN_PATH_A8)
export CGTOOLS_A8

CGTOOLS_A9 = $(TOOLCHAIN_PATH_A9)
export CGTOOLS_A9

CGTOOLS_ARM9 = $(TOOLCHAIN_PATH_Arm9)
export CGTOOLS_ARM9

CGTOOLS_A15 = $(TOOLCHAIN_PATH_A15)
export CGTOOLS_A15

CGTOOLS_EVE = $(TOOLCHAIN_PATH_EVE)
export CGTOOLS_EVE

STRIP470 = $(TOOLCHAIN_PATH_M4)/bin/strip470 -p
STRIP6x = $(CODEGEN_PATH_C674)/bin/strip6x -p
STRIP_ALL_ARM = $(CODEGEN_PREFIX)strip -s
STRIP_DEBUG_ARM = $(CODEGEN_PREFIX)strip --strip-debug

# Nothing beyond this point
