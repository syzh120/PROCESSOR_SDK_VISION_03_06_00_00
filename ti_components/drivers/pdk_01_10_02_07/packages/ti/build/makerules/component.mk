#
# Copyright (c) 2013-2017, Texas Instruments Incorporated
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

# File: component.mk
#       This file is component include make file of PDK.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_BOARD_DEPENDENCY    - "yes": means the code for this module depends on
#                             board and the compiled obj/lib has to be kept
#                             under <board> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no board dependent code and hence
#                             the obj/libs are not kept under <board> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
# <mod>_FP_DEPENDENCY       - "yes": means the code for this module depends on
#                             target toolchain floating point support.  Enabling
#                             this option will enable floating point print
#                             support for toolchains which link out floating
#                             point print support to save memory.
#
ifeq ($(pdk_component_make_include), )

DEFAULT_tda2xx_CORELIST = a15_0 ipu1_0 c66x arp32_1
DEFAULT_tda2px_CORELIST = a15_0 ipu1_0 c66x arp32_1
DEFAULT_am572x_CORELIST = a15_0 ipu1_0 c66x
DEFAULT_am574x_CORELIST = a15_0 ipu1_0 c66x
DEFAULT_dra72x_CORELIST = a15_0 ipu1_0 c66x
DEFAULT_dra75x_CORELIST = a15_0 ipu1_0 c66x arp32_1
DEFAULT_tda2ex_CORELIST = a15_0 ipu1_0 c66x
DEFAULT_am571x_CORELIST = a15_0 ipu1_0 c66x
DEFAULT_tda3xx_CORELIST = ipu1_0 c66x arp32_1
DEFAULT_dra78x_CORELIST = ipu1_0 c66x arp32_1
DEFAULT_k2h_CORELIST    = a15_0 c66x
DEFAULT_k2k_CORELIST    = a15_0 c66x
DEFAULT_k2l_CORELIST    = a15_0 c66x
DEFAULT_k2e_CORELIST    = a15_0 c66x
DEFAULT_k2g_CORELIST    = a15_0 c66x
DEFAULT_c6678_CORELIST  = c66x
DEFAULT_c6657_CORELIST  = c66x
DEFAULT_am335x_CORELIST = a8host
DEFAULT_am437x_CORELIST = a9host
DEFAULT_omapl137_CORELIST = arm9_0 c674x
DEFAULT_omapl138_CORELIST = arm9_0 c674x

# Component specific CFLAGS
PDK_CFLAGS =
PDK_LNKFLAGS =

############################
# device pdk package
# List of components included under pdk lib
# The components included here are built and will be part of pdk lib
############################
pdk_LIB_LIST =

############################
# device pdk firmware
# List of components included under pdk firmware
# The components included here are built and will be part of pdk firmware
############################
pdk_FIRM_LIST =

############################
# device pdk application utility packages
# List of application utilities under pdk
# The components included here are built and will be part of pdk app_lib
############################
pdk_APP_LIB_LIST =

############################
# device pdk examples
# List of examples under pdk
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
pdk_EXAMPLE_LIST =

############################
# Duplicate example list which should not be built with "all" (since this is
# duplicate -j option will build both and result in .obj correuption) but needs
# to be still exposed to top level makefile so that user can individually call
# them. Also these duplicate targets doesn't support package option and hence
# should not be included when packaging
############################
pdk_DUP_EXAMPLE_LIST =

# Components included independent of OS type

#include each module component makefile
-include $(PDK_CSL_COMP_PATH)/csl_component.mk
ifneq ($(csl_LIB_LIST),)
  pdk_LIB_LIST += $(csl_LIB_LIST)
endif
ifneq ($(csl_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(csl_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_BOARD_COMP_PATH)/board_component.mk
ifneq ($(board_LIB_LIST),)
  pdk_LIB_LIST += $(board_LIB_LIST)
endif
ifneq ($(board_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(board_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_PM_COMP_PATH)/pm_component.mk
ifneq ($(pm_LIB_LIST),)
  pdk_LIB_LIST += $(pm_LIB_LIST)
endif
ifneq ($(pm_APP_LIB_LIST),)
  pdk_APP_LIB_LIST += $(pm_APP_LIB_LIST)
endif
ifneq ($(pm_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(pm_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_AUD_COMP_PATH)/aud_component.mk
ifneq ($(aud_LIB_LIST),)
  pdk_LIB_LIST += $(aud_LIB_LIST)
endif
ifneq ($(aud_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(aud_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_SBL_COMP_PATH)/sbl_component.mk
ifneq ($(sbl_LIB_LIST),)
  pdk_LIB_LIST += $(sbl_LIB_LIST)
endif
ifneq ($(sbl_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(sbl_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_SBL_AUTO_COMP_PATH)/sbl_auto_component.mk
ifneq ($(sbl_auto_LIB_LIST),)
  pdk_LIB_LIST += $(sbl_auto_LIB_LIST)
endif
ifneq ($(sbl_auto_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(sbl_auto_EXAMPLE_LIST)
endif
ifneq ($(sbl_auto_DUP_EXAMPLE_LIST),)
  pdk_DUP_EXAMPLE_LIST += $(sbl_auto_DUP_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_CMB_COMP_PATH)/cmb_component.mk
ifneq ($(cmb_LIB_LIST),)
  pdk_LIB_LIST += $(cmb_LIB_LIST)
endif
ifneq ($(cmb_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(cmb_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_BOARD_IND_COMP_PATH)/board_ind_component.mk
ifneq ($(board_ind_LIB_LIST),)
  pdk_LIB_LIST += $(board_ind_LIB_LIST)
endif
ifneq ($(board_ind_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(board_ind_EXAMPLE_LIST)
endif

#Below applicable only for TDA devices

# - used to ignore include if component not present
-include $(PDK_DIAG_COMP_PATH)/diag_component.mk
ifneq ($(diag_LIB_LIST),)
  pdk_LIB_LIST += $(diag_LIB_LIST)
endif
ifneq ($(diag_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(diag_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_FIREWALL_L3L4_COMP_PATH)/firewall_l3l4_component.mk
ifneq ($(firewall_l3l4_LIB_LIST),)
  pdk_LIB_LIST += $(firewall_l3l4_LIB_LIST)
endif
ifneq ($(firewall_l3l4_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(firewall_l3l4_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_IPCLITE_COMP_PATH)/ipclite_component.mk
ifneq ($(ipclite_LIB_LIST),)
  pdk_LIB_LIST += $(ipclite_LIB_LIST)
endif
ifneq ($(ipclite_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(ipclite_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_TDA3X_SECURITY_COMP_PATH)/security_component.mk
ifneq ($(security_LIB_LIST),)
  pdk_LIB_LIST += $(security_LIB_LIST)
endif
ifneq ($(security_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(security_EXAMPLE_LIST)
endif

#Below applicable only for TDA devices for backward compatibility;not applicable for PRSDK

# - used to ignore include if component not present
-include $(PDK_NORFLASH_COMP_PATH)/norflash_component.mk
ifneq ($(norflash_LIB_LIST),)
  pdk_LIB_LIST += $(norflash_LIB_LIST)
endif
ifneq ($(norflash_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(norflash_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_QSPIFLASH_COMP_PATH)/qspiflash_component.mk
ifneq ($(qspiflash_LIB_LIST),)
  pdk_LIB_LIST += $(qspiflash_LIB_LIST)
endif
ifneq ($(qspiflash_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(qspiflash_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_STW_LLD_COMP_PATH)/stw_lld_component.mk
ifneq ($(stw_lld_LIB_LIST),)
  pdk_LIB_LIST += $(stw_lld_LIB_LIST)
endif
ifneq ($(stw_lld_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(stw_lld_EXAMPLE_LIST)
endif
ifneq ($(stw_lld_DUP_EXAMPLE_LIST),)
  pdk_DUP_EXAMPLE_LIST += $(stw_lld_DUP_EXAMPLE_LIST)
endif

# - used to ignore include if component not present
-include $(PDK_VPS_COMP_PATH)/vps_component.mk
ifneq ($(vps_LIB_LIST),)
  pdk_LIB_LIST += $(vps_LIB_LIST)
endif
ifneq ($(vps_EXAMPLE_LIST),)
  pdk_EXAMPLE_LIST += $(vps_EXAMPLE_LIST)
endif

# Components included for non-baremetal OS
ifneq ($(BUILD_OS_TYPE), baremetal)
  # - used to ignore include if component not present
  -include $(PDK_OSAL_COMP_PATH)/osal_component.mk
  ifneq ($(osal_LIB_LIST),)
    pdk_LIB_LIST += $(osal_LIB_LIST)
  endif
  ifneq ($(osal_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(osal_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_I2C_COMP_PATH)/i2c_component.mk
  ifneq ($(i2c_LIB_LIST),)
    pdk_LIB_LIST += $(i2c_LIB_LIST)
  endif
  ifneq ($(i2c_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(i2c_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_UART_COMP_PATH)/uart_component.mk
  ifneq ($(uart_LIB_LIST),)
    pdk_LIB_LIST += $(uart_LIB_LIST)
  endif
  ifneq ($(uart_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(uart_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_USB_COMP_PATH)/usb_component.mk
  ifneq ($(usb_LIB_LIST),)
    pdk_LIB_LIST += $(usb_LIB_LIST)
  endif
  ifneq ($(usb_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(usb_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_GPIO_COMP_PATH)/gpio_component.mk
  ifneq ($(gpio_LIB_LIST),)
    pdk_LIB_LIST += $(gpio_LIB_LIST)
  endif
  ifneq ($(gpio_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(gpio_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_PROFILING_COMP_PATH)/profiling_component.mk
  ifneq ($(profiling_LIB_LIST),)
    pdk_LIB_LIST += $(profiling_LIB_LIST)
  endif
  ifneq ($(profiling_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(profiling_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_NIMU_ICSS_COMP_PATH)/nimu_icss_component.mk
  ifneq ($(nimu_icss_LIB_LIST),)
    pdk_LIB_LIST += $(nimu_icss_LIB_LIST)
  endif
  ifneq ($(nimu_icss_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(nimu_icss_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_NIMU_COMP_PATH)/nimu_component.mk
  ifneq ($(nimu_LIB_LIST),)
    pdk_LIB_LIST += $(nimu_LIB_LIST)
  endif
  ifneq ($(nimu_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(nimu_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_FATFS_COMP_PATH)/fatfs_component.mk
  ifneq ($(fatfs_LIB_LIST),)
    pdk_LIB_LIST += $(fatfs_LIB_LIST)
  endif
  ifneq ($(fatfs_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(fatfs_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_MMCSD_COMP_PATH)/mmcsd_component.mk
  ifneq ($(mmcsd_LIB_LIST),)
    pdk_LIB_LIST += $(mmcsd_LIB_LIST)
  endif
  ifneq ($(mmcsd_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(mmcsd_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_PCIE_COMP_PATH)/pcie_component.mk
  ifneq ($(pcie_LIB_LIST),)
    pdk_LIB_LIST += $(pcie_LIB_LIST)
  endif
  ifneq ($(pcie_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(pcie_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_MCASP_COMP_PATH)/mcasp_component.mk
  ifneq ($(mcasp_LIB_LIST),)
    pdk_LIB_LIST += $(mcasp_LIB_LIST)
  endif
  ifneq ($(mcasp_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(mcasp_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_MCBSP_COMP_PATH)/mcbsp_component.mk
  ifneq ($(mcbsp_LIB_LIST),)
    pdk_LIB_LIST += $(mcbsp_LIB_LIST)
  endif
  ifneq ($(mcbsp_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(mcbsp_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_ICSS_EMAC_COMP_PATH)/icss_emac_component.mk
  ifneq ($(icss_emac_LIB_LIST),)
    pdk_LIB_LIST += $(icss_emac_LIB_LIST)
  endif
  ifneq ($(icss_emac_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(icss_emac_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_EMAC_COMP_PATH)/emac_component.mk
  ifneq ($(emac_LIB_LIST),)
    pdk_LIB_LIST += $(emac_LIB_LIST)
  endif
  ifneq ($(emac_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(emac_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_PRUSS_COMP_PATH)/pruss_component.mk
  ifneq ($(pruss_LIB_LIST),)
    pdk_LIB_LIST += $(pruss_LIB_LIST)
  endif
  ifneq ($(pruss_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(pruss_EXAMPLE_LIST)
  endif
  ifneq ($(pruss_FIRM_LIST),)
    pdk_FIRM_LIST += $(pruss_FIRM_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_SPI_COMP_PATH)/spi_component.mk
  ifneq ($(spi_LIB_LIST),)
    pdk_LIB_LIST += $(spi_LIB_LIST)
  endif
  ifneq ($(spi_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(spi_EXAMPLE_LIST)
  endif

  # - used to ignore include if component not present
  -include $(PDK_GPMC_COMP_PATH)/gpmc_component.mk
  ifneq ($(gpmc_LIB_LIST),)
    pdk_LIB_LIST += $(gpmc_LIB_LIST)
  endif
  ifneq ($(gpmc_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(gpmc_EXAMPLE_LIST)
  endif

  #Below applicable only for TDA devices for backward compatibility;not applicable for PRSDK
  # - used to ignore include if component not present
  -include $(PDK_BSP_LLD_COMP_PATH)/bsp_lld_component.mk
  ifneq ($(bsp_lld_LIB_LIST),)
    pdk_LIB_LIST += $(bsp_lld_LIB_LIST)
  endif
  ifneq ($(bsp_lld_EXAMPLE_LIST),)
    pdk_EXAMPLE_LIST += $(bsp_lld_EXAMPLE_LIST)
  endif

endif

pdk_PKG_LIST_ALL = $(pdk_EXAMPLE_LIST) $(pdk_LIB_LIST) $(pdk_APP_LIB_LIST) $(pdk_FIRM_LIST)

#
# PDK Modules
#

#
# PDK Examples
#

#Default to all if not set from rules.make or command line
ifeq ($(PACKAGE_SELECT), )
  PACKAGE_SELECT := all
endif

ifeq ($(CORE),ipu1_0)
  PDK_CFLAGS += -DBUILD_IPU1_0 -DBUILD_IPU1
  PDK_LNKFLAGS += --define=BUILD_IPU1_0 --define=BUILD_IPU1
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),ipu1_1)
  PDK_CFLAGS += -DBUILD_IPU1_1 -DBUILD_IPU1
  PDK_LNKFLAGS += --define=BUILD_IPU1_1 --define=BUILD_IPU1
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),ipu2_0)
  PDK_CFLAGS += -DBUILD_IPU2_0 -DBUILD_IPU2
  PDK_LNKFLAGS += --define=BUILD_IPU2_0 --define=BUILD_IPU2
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),ipu2_1)
  PDK_CFLAGS += -DBUILD_IPU2_1 -DBUILD_IPU2
  PDK_LNKFLAGS += --define=BUILD_IPU2_1 --define=BUILD_IPU2
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),arp32_1)
  PDK_CFLAGS += -DBUILD_ARP32 -DBUILD_ARP32_1
  PDK_LNKFLAGS += --define=BUILD_ARP32 --define=BUILD_ARP32_1
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),arp32_2)
  PDK_CFLAGS += -DBUILD_ARP32 -DBUILD_ARP32_2
  PDK_LNKFLAGS += --define=BUILD_ARP32 --define=BUILD_ARP32_2
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),arp32_3)
  PDK_CFLAGS += -DBUILD_ARP32 -DBUILD_ARP32_3
  PDK_LNKFLAGS += --define=BUILD_ARP32 --define=BUILD_ARP32_3
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),arp32_4)
  PDK_CFLAGS += -DBUILD_ARP32 -DBUILD_ARP32_4
  PDK_LNKFLAGS += --define=BUILD_ARP32 --define=BUILD_ARP32_4
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),a8host)
  PDK_CFLAGS += -DBUILD_A8
  PDK_LNKFLAGS += --define=BUILD_A8
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),a9host)
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),pru_0)
  PDK_CFLAGS += -DPRU0 -Dpru0
  PDK_LNKFLAGS += --define=PRU0 --define=pru0
  # List all the libraries to be built
  ifeq ($(SOC),$(filter $(SOC), am335x am437x))
    PRU_VERSION_LIST = REV1
  endif
  ifeq ($(SOC),$(filter $(SOC), am571x k2g am574x))
    PRU_VERSION_LIST = REV2
  endif
  ifeq ($(SOC),$(filter $(SOC), am572x))
    PRU_VERSION_LIST = REV1 REV2
  endif
endif

ifeq ($(CORE),pru_1)
  PDK_CFLAGS += -DPRU1 -Dpru1
  PDK_LNKFLAGS += --define=PRU1 --define=pru1
  # List all the libraries to be built
  ifeq ($(SOC),$(filter $(SOC), am335x am437x))
    PRU_VERSION_LIST = REV1
  endif
  ifeq ($(SOC),$(filter $(SOC), am571x k2g am574x))
    PRU_VERSION_LIST = REV2
  endif
  ifeq ($(SOC),$(filter $(SOC), am572x))
    PRU_VERSION_LIST = REV1 REV2
  endif
endif

ifeq ($(CORE),arm9_0)
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),a15_0)
  PDK_CFLAGS += -DBUILD_A15_0
  PDK_LNKFLAGS += --define=BUILD_A15_0
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
endif

ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1 c66xdsp_2))
  ifeq ($(CORE),$(filter $(CORE), c66xdsp_1))
    PDK_CFLAGS += -DBUILD_DSP_1
    PDK_LNKFLAGS += --define=BUILD_DSP_1
  endif
  ifeq ($(CORE),$(filter $(CORE), c66xdsp_2))
    PDK_CFLAGS += -DBUILD_DSP_2
    PDK_LNKFLAGS += --define=BUILD_DSP_2
  endif
  # List all the libraries to be built
  LIB_ENDIAN_LIST  = little
  ifeq ($(SOC),$(filter $(SOC), k2h k2k k2l k2e k2g c6678 c6657))
    LIB_ENDIAN_LIST  += big
  endif
endif

ifeq ($(CORE),c674x)
# List all the libraries to be built
LIB_ENDIAN_LIST  = little
endif

export PDK_CFLAGS
export PDK_LNKFLAGS

pdk_component_make_include := 1
endif
