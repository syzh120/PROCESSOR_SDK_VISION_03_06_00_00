#  ============================================================================
#  (C) Copyright 2016-2017 Texas Instruments, Inc.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  ============================================================================

# File: csl_component.mk
#       This file is component include make file of CSL library.
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
# <mod>_BOARD_DEPENDENCY - "yes": means the code for this module depends on
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
#
ifeq ($(csl_component_make_include), )

############################
# csl package
# List of components included under csl
# The components included here are built and will be part of csl
############################
csl_LIB_LIST = csl_init csl_intc csl csl_utils_common csl_uart_console csl_utils_i2c

############################
# csl package
# List of csl examples (apps) supported for below boards
############################
csl_BOARDLIST = evmAM572x idkAM572x idkAM571x evmDRA72x evmDRA75x evmDRA78x idkAM574x

############################
# csl example
# List of example under csl
# All the tests mentioned in list are built when test target is called
# List below all example for allowed values - note the list is populated in each example
############################
csl_EXAMPLE_LIST =

#
# CSL Modules
#

# CSL
csl_COMP_LIST = csl
csl_RELPATH = ti/csl
csl_PATH = $(PDK_CSL_COMP_PATH)
csl_LIBNAME = ti.csl
csl_LIBPATH = $(csl_PATH)/lib
csl_MAKEFILE = -fmakefile.mk
export csl_MAKEFILE
export csl_LIBNAME
export csl_LIBPATH
csl_BOARD_DEPENDENCY = no
csl_CORE_DEPENDENCY = no
export csl_COMP_LIST
export csl_BOARD_DEPENDENCY
export csl_CORE_DEPENDENCY
csl_PKG_LIST = csl
export csl_PKG_LIST
csl_INCLUDE = $(csl_PATH)
csl_SOCLIST = tda2xx tda2px am574x am572x dra75x tda2ex dra72x am571x tda3xx k2h k2k k2l k2e k2g c6678 c6657 am437x am335x dra78x omapl137 c6747 omapl138
export csl_SOCLIST
csl_$(SOC)_CORELIST = $(DEFAULT_$(SOC)_CORELIST)
ifeq ($(SOC),$(filter $(SOC), am572x am574x))
ifeq ($(BUILD_ARP32), yes)
csl_$(SOC)_CORELIST += arp32_1
endif
endif
export csl_$(SOC)_CORELIST

# CSL Init
csl_init_COMP_LIST = csl_init
csl_init_RELPATH = ti/csl/arch
csl_init_PATH = $(PDK_CSL_COMP_PATH)/arch
csl_init_LIBNAME = ti.csl.init
csl_init_LIBPATH = $(csl_PATH)/lib
csl_init_MAKEFILE = -fmakefile_init.mk
export csl_init_MAKEFILE
export csl_init_LIBNAME
export csl_init_LIBPATH
csl_init_BOARD_DEPENDENCY = no
csl_init_CORE_DEPENDENCY = no
export csl_init_COMP_LIST
export csl_init_BOARD_DEPENDENCY
export csl_init_CORE_DEPENDENCY
csl_init_PKG_LIST = csl_init
export csl_init_PKG_LIST
csl_init_INCLUDE = $(csl_init_PATH)
csl_init_SOCLIST = tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x k2h k2k k2e k2l k2g omapl137 c6747 omapl138
export csl_init_SOCLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x k2h k2k k2e k2l k2g))
csl_init_$(SOC)_CORELIST = a15_0
endif
ifeq ($(SOC),$(filter $(SOC), omapl137 c6747 omapl138))
csl_init_$(SOC)_CORELIST = arm9_0
endif
export csl_init_$(SOC)_CORELIST

# CSL INTC
csl_intc_COMP_LIST = csl_intc
csl_intc_RELPATH = ti/csl/src/intc
csl_intc_PATH = $(PDK_CSL_COMP_PATH)/src/intc
csl_intc_LIBNAME = ti.csl.intc
csl_intc_LIBPATH = $(csl_PATH)/lib
csl_intc_MAKEFILE = -fmakefile.mk
export csl_intc_MAKEFILE
export csl_intc_LIBNAME
export csl_intc_LIBPATH
csl_intc_BOARD_DEPENDENCY = no
csl_intc_CORE_DEPENDENCY = no
export csl_intc_COMP_LIST
export csl_intc_BOARD_DEPENDENCY
export csl_intc_CORE_DEPENDENCY
csl_intc_PKG_LIST = csl_intc
export csl_intc_PKG_LIST
csl_intc_INCLUDE = $(csl_intc_PATH)
csl_intc_SOCLIST = am574x am572x am571x k2h k2k k2l k2e k2g c6678 c6657 dra72x dra75x dra78x omapl137 c6747 omapl138
export csl_intc_SOCLIST
ifeq ($(SOC),$(filter $(SOC), am574x am572x am571x k2h k2k k2l k2e k2g c6678 c6657 dra72x dra75x dra78x))
csl_intc_$(SOC)_CORELIST = c66x
endif
ifeq ($(SOC),$(filter $(SOC), omapl137 c6747 omapl138))
csl_intc_$(SOC)_CORELIST = c674x
endif
export csl_intc_$(SOC)_CORELIST

# Utils Common
csl_utils_common_COMP_LIST = csl_utils_common
csl_utils_common_RELPATH = ti/csl/example/utils/common
csl_utils_common_PATH = $(PDK_CSL_COMP_PATH)/example/utils/common
csl_utils_common_LIBNAME = csl_utils_common
csl_utils_common_LIBPATH = $(csl_utils_common_PATH)/lib
export csl_utils_common_LIBNAME
export csl_utils_common_LIBPATH
csl_utils_common_BOARD_DEPENDENCY = no
csl_utils_common_CORE_DEPENDENCY = no
export csl_utils_common_COMP_LIST
export csl_utils_common_BOARD_DEPENDENCY
export csl_utils_common_CORE_DEPENDENCY
csl_utils_common_PKG_LIST = csl_utils_common
csl_utils_common_INCLUDE = $(csl_utils_common_PATH)
csl_utils_common_SOCLIST = tda2xx tda2px am572x dra75x tda2ex dra72x am571x tda3xx dra78x am574x
export csl_utils_common_SOCLIST
csl_utils_common_$(SOC)_CORELIST = $(DEFAULT_$(SOC)_CORELIST)
export csl_utils_common_$(SOC)_CORELIST

#Uart Console
csl_uart_console_COMP_LIST = csl_uart_console
csl_uart_console_RELPATH = ti/csl/example/utils/uart_console
csl_uart_console_PATH = $(PDK_CSL_COMP_PATH)/example/utils/uart_console
csl_uart_console_LIBNAME = csl_uart_console
csl_uart_console_LIBPATH = $(csl_uart_console_PATH)/lib
export csl_uart_console_LIBNAME
export csl_uart_console_LIBPATH
csl_uart_console_BOARD_DEPENDENCY = no
csl_uart_console_CORE_DEPENDENCY = no
export csl_uart_console_COMP_LIST
export csl_uart_console_BOARD_DEPENDENCY
export csl_uart_console_CORE_DEPENDENCY
csl_uart_console_PKG_LIST = csl_uart_console
csl_uart_console_INCLUDE = $(csl_uart_console_PATH)
csl_uart_console_SOCLIST = tda2xx tda2px am572x dra75x tda2ex dra72x am571x tda3xx dra78x am574x
export csl_uart_console_SOCLIST
csl_uart_console_$(SOC)_CORELIST = $(DEFAULT_$(SOC)_CORELIST)
export csl_uart_console_$(SOC)_CORELIST

# Utils I2C
csl_utils_i2c_COMP_LIST = csl_utils_i2c
csl_utils_i2c_RELPATH = ti/csl/example/utils/i2c
csl_utils_i2c_PATH = $(PDK_CSL_COMP_PATH)/example/utils/i2c
csl_utils_i2c_LIBNAME = csl_utils_i2c
csl_utils_i2c_LIBPATH = $(csl_utils_i2c_PATH)/lib
export csl_utils_i2c_LIBNAME
export csl_utils_i2c_LIBPATH
csl_utils_i2c_BOARD_DEPENDENCY = no
csl_utils_i2c_CORE_DEPENDENCY = no
export csl_utils_i2c_COMP_LIST
export csl_utils_i2c_BOARD_DEPENDENCY
export csl_utils_i2c_CORE_DEPENDENCY
csl_utils_i2c_PKG_LIST = csl_utils_i2c
csl_utils_i2c_INCLUDE = $(csl_utils_i2c_PATH)
csl_utils_i2c_SOCLIST = tda2xx tda2px am572x dra75x tda2ex dra72x am571x tda3xx dra78x am574x
export csl_utils_i2c_SOCLIST
csl_utils_i2c_$(SOC)_CORELIST = $(DEFAULT_$(SOC)_CORELIST)
export csl_utils_i2c_$(SOC)_CORELIST

#
# CSL Examples
#

# EDMA test app
csl_edma_test_app_COMP_LIST = csl_edma_test_app
csl_edma_test_app_RELPATH = ti/csl/example/edma/edma_test
csl_edma_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/edma/edma_test
csl_edma_test_app_BOARD_DEPENDENCY = yes
csl_edma_test_app_CORE_DEPENDENCY = no
export csl_edma_test_app_COMP_LIST
export csl_edma_test_app_BOARD_DEPENDENCY
export csl_edma_test_app_CORE_DEPENDENCY
csl_edma_test_app_PKG_LIST = csl_edma_test_app
csl_edma_test_app_INCLUDE = $(csl_edma_test_app_PATH)
csl_edma_test_app_BOARDLIST = tda2xx-evm tda2px-evm idkAM572x evmAM572x tda2ex-evm idkAM571x tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_edma_test_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm idkAM571x idkAM572x evmAM572x evmDRA72x evmDRA75x tda2xx-rvp idkAM574x))
csl_edma_test_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_edma_test_app_$(SOC)_CORELIST = ipu1_0 c66x
endif
export csl_edma_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_edma_test_app

# I2C led blink app
csl_i2c_led_blink_app_COMP_LIST = csl_i2c_led_blink_app
csl_i2c_led_blink_app_RELPATH = ti/csl/example/i2c/i2c_led_blink
csl_i2c_led_blink_app_PATH = $(PDK_CSL_COMP_PATH)/example/i2c/i2c_led_blink
csl_i2c_led_blink_app_BOARD_DEPENDENCY = yes
csl_i2c_led_blink_app_CORE_DEPENDENCY = no
export csl_i2c_led_blink_app_COMP_LIST
export csl_i2c_led_blink_app_BOARD_DEPENDENCY
export csl_i2c_led_blink_app_CORE_DEPENDENCY
csl_i2c_led_blink_app_PKG_LIST = csl_i2c_led_blink_app
csl_i2c_led_blink_app_INCLUDE = $(csl_i2c_led_blink_app_PATH)
csl_i2c_led_blink_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_i2c_led_blink_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_i2c_led_blink_app_$(SOC)_CORELIST = a15_0
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x idkAM571x evmDRA72x evmDRA75x idkAM574x))
csl_i2c_led_blink_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_i2c_led_blink_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_i2c_led_blink_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_i2c_led_blink_app

# MAILBOX test app
csl_mailbox_sender_receiver_app_COMP_LIST = csl_mailbox_sender_receiver_app
csl_mailbox_sender_receiver_app_RELPATH = ti/csl/example/mailbox/mailbox_sender_receiver_app
csl_mailbox_sender_receiver_app_PATH = $(PDK_CSL_COMP_PATH)/example/mailbox/mailbox_sender_receiver_app
csl_mailbox_sender_receiver_app_BOARD_DEPENDENCY = yes
csl_mailbox_sender_receiver_app_CORE_DEPENDENCY = no
export csl_mailbox_sender_receiver_app_COMP_LIST
export csl_mailbox_sender_receiver_app_BOARD_DEPENDENCY
export csl_mailbox_sender_receiver_app_CORE_DEPENDENCY
csl_mailbox_sender_receiver_app_PKG_LIST = csl_mailbox_sender_receiver_app
csl_mailbox_sender_receiver_app_INCLUDE = $(csl_mailbox_sender_receiver_app_PATH)
csl_mailbox_sender_receiver_app_BOARDLIST = tda2xx-evm tda2px-evm idkAM574x idkAM572x evmAM572x tda2ex-evm idkAM571x tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp
export csl_mailbox_sender_receiver_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm idkAM571x idkAM572x idkAM574x evmAM572x evmDRA72x evmDRA75x tda2xx-rvp))
csl_mailbox_sender_receiver_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_mailbox_sender_receiver_app_$(SOC)_CORELIST = ipu1_0 c66x
endif
export csl_mailbox_sender_receiver_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mailbox_sender_receiver_app

# UART test app
csl_uart_test_app_COMP_LIST = csl_uart_test_app
csl_uart_test_app_RELPATH = ti/csl/example/uart/uart_test
csl_uart_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/uart/uart_test
csl_uart_test_app_BOARD_DEPENDENCY = yes
csl_uart_test_app_CORE_DEPENDENCY = no
export csl_uart_test_app_COMP_LIST
export csl_uart_test_app_BOARD_DEPENDENCY
export csl_uart_test_app_CORE_DEPENDENCY
csl_uart_test_app_PKG_LIST = csl_uart_test_app
csl_uart_test_app_INCLUDE = $(csl_uart_test_app_PATH)
csl_uart_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x evmAM572x idkAM571x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_uart_test_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_uart_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x evmAM572x idkAM571x evmDRA72x evmDRA75x idkAM574x))
csl_uart_test_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_uart_test_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_uart_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_uart_test_app

# UART intr test app
csl_uart_intr_test_app_COMP_LIST = csl_uart_intr_test_app
csl_uart_intr_test_app_RELPATH = ti/csl/example/uart/uart_intr
csl_uart_intr_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/uart/uart_intr
csl_uart_intr_test_app_BOARD_DEPENDENCY = yes
csl_uart_intr_test_app_CORE_DEPENDENCY = no
export csl_uart_intr_test_app_COMP_LIST
export csl_uart_intr_test_app_BOARD_DEPENDENCY
export csl_uart_intr_test_app_CORE_DEPENDENCY
csl_uart_intr_test_app_PKG_LIST = csl_uart_intr_test_app
csl_uart_intr_test_app_INCLUDE = $(csl_uart_intr_test_app_PATH)
csl_uart_intr_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_uart_intr_test_app_BOARDLIST
csl_uart_intr_test_app_$(SOC)_CORELIST = ipu1_0
export csl_uart_intr_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_uart_intr_test_app

# UART edma test app
csl_uart_edma_test_app_COMP_LIST = csl_uart_edma_test_app
csl_uart_edma_test_app_RELPATH = ti/csl/example/uart/uart_edma
csl_uart_edma_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/uart/uart_edma
csl_uart_edma_test_app_BOARD_DEPENDENCY = yes
csl_uart_edma_test_app_CORE_DEPENDENCY = no
export csl_uart_edma_test_app_COMP_LIST
export csl_uart_edma_test_app_BOARD_DEPENDENCY
export csl_uart_edma_test_app_CORE_DEPENDENCY
csl_uart_edma_test_app_PKG_LIST = csl_uart_edma_test_app
csl_uart_edma_test_app_INCLUDE = $(csl_uart_edma_test_app_PATH)
csl_uart_edma_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_uart_edma_test_app_BOARDLIST
csl_uart_edma_test_app_$(SOC)_CORELIST = ipu1_0
export csl_uart_edma_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_uart_edma_test_app

# MCASP transmit app
csl_mcasp_transmit_app_COMP_LIST = csl_mcasp_transmit_app
csl_mcasp_transmit_app_RELPATH = ti/csl/example/mcasp/mcasp_transmit
csl_mcasp_transmit_app_PATH = $(PDK_CSL_COMP_PATH)/example/mcasp/mcasp_transmit
csl_mcasp_transmit_app_BOARD_DEPENDENCY = yes
csl_mcasp_transmit_app_CORE_DEPENDENCY = no
export csl_mcasp_transmit_app_COMP_LIST
export csl_mcasp_transmit_app_BOARD_DEPENDENCY
export csl_mcasp_transmit_app_CORE_DEPENDENCY
csl_mcasp_transmit_app_PKG_LIST = csl_mcasp_transmit_app
csl_mcasp_transmit_app_INCLUDE = $(csl_mcasp_transmit_app_PATH)
csl_mcasp_transmit_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp
export csl_mcasp_transmit_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm evmDRA72x evmDRA75x tda2xx-rvp))
csl_mcasp_transmit_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_mcasp_transmit_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_mcasp_transmit_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mcasp_transmit_app

# MCSPI masterSlave app
csl_mcspi_masterslave_app_COMP_LIST = csl_mcspi_masterslave_app
csl_mcspi_masterslave_app_RELPATH = ti/csl/example/mcspi/mcspiMasterSlave
csl_mcspi_masterslave_app_PATH = $(PDK_CSL_COMP_PATH)/example/mcspi/mcspiMasterSlave
csl_mcspi_masterslave_app_BOARD_DEPENDENCY = yes
csl_mcspi_masterslave_app_CORE_DEPENDENCY = no
export csl_mcspi_masterslave_app_COMP_LIST
export csl_mcspi_masterslave_app_BOARD_DEPENDENCY
export csl_mcspi_masterslave_app_CORE_DEPENDENCY
csl_mcspi_masterslave_app_PKG_LIST = csl_mcspi_masterslave_app
csl_mcspi_masterslave_app_INCLUDE = $(csl_mcspi_masterslave_app_PATH)
csl_mcspi_masterslave_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp
export csl_mcspi_masterslave_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm evmDRA72x evmDRA75x tda2xx-rvp))
csl_mcspi_masterslave_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_mcspi_masterslave_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_mcspi_masterslave_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mcspi_masterslave_app

# SPINLOCK test app
csl_spinlock_test_app_COMP_LIST = csl_spinlock_test_app
csl_spinlock_test_app_RELPATH = ti/csl/example/spinlock/spinlock_test
csl_spinlock_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/spinlock/spinlock_test
csl_spinlock_test_app_BOARD_DEPENDENCY = yes
csl_spinlock_test_app_CORE_DEPENDENCY = no
export csl_spinlock_test_app_COMP_LIST
export csl_spinlock_test_app_BOARD_DEPENDENCY
export csl_spinlock_test_app_CORE_DEPENDENCY
csl_spinlock_test_app_PKG_LIST = csl_spinlock_test_app
csl_spinlock_test_app_INCLUDE = $(csl_spinlock_test_app_PATH)
csl_spinlock_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_spinlock_test_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x tda2xx-rvp idkAM574x))
csl_spinlock_test_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_spinlock_test_app_$(SOC)_CORELIST = ipu1_0 c66x
endif
export csl_spinlock_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_spinlock_test_app

# GPIO test app - GPIO toggle
csl_gpio_toggle_app_COMP_LIST = csl_gpio_toggle_app
csl_gpio_toggle_app_RELPATH = ti/csl/example/gpio/gpio_toggle
csl_gpio_toggle_app_PATH = $(PDK_CSL_COMP_PATH)/example/gpio/gpio_toggle
csl_gpio_toggle_app_BOARD_DEPENDENCY = yes
csl_gpio_toggle_app_CORE_DEPENDENCY = no
export csl_gpio_toggle_app_COMP_LIST
export csl_gpio_toggle_app_BOARD_DEPENDENCY
export csl_gpio_toggle_app_CORE_DEPENDENCY
csl_gpio_toggle_app_PKG_LIST = csl_gpio_toggle_app
csl_gpio_toggle_app_INCLUDE = $(csl_gpio_toggle_app_PATH)
csl_gpio_toggle_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_gpio_toggle_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_gpio_toggle_app_$(SOC)_CORELIST = a15_0
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x idkAM574x))
csl_gpio_toggle_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_gpio_toggle_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_gpio_toggle_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_gpio_toggle_app

# GPIO test app - GPIO interrupt
csl_gpio_interrupt_app_COMP_LIST = csl_gpio_interrupt_app
csl_gpio_interrupt_app_RELPATH = ti/csl/example/gpio/gpio_interrupt
csl_gpio_interrupt_app_PATH = $(PDK_CSL_COMP_PATH)/example/gpio/gpio_interrupt
csl_gpio_interrupt_app_BOARD_DEPENDENCY = yes
csl_gpio_interrupt_app_CORE_DEPENDENCY = no
export csl_gpio_interrupt_app_COMP_LIST
export csl_gpio_interrupt_app_BOARD_DEPENDENCY
export csl_gpio_interrupt_app_CORE_DEPENDENCY
csl_gpio_interrupt_app_PKG_LIST = csl_gpio_interrupt_app
csl_gpio_interrupt_app_INCLUDE = $(csl_gpio_interrupt_app_PATH)
csl_gpio_interrupt_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_gpio_interrupt_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_gpio_interrupt_app_$(SOC)_CORELIST = a15_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm))
csl_gpio_interrupt_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_gpio_interrupt_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_gpio_interrupt_app

# XMC MPU test app
csl_xmc_mpu_test_app_COMP_LIST = csl_xmc_mpu_test_app
csl_xmc_mpu_test_app_RELPATH = ti/csl/example/xmc_mpu/xmc_mpu_test_app
csl_xmc_mpu_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/xmc_mpu/xmc_mpu_test_app
csl_xmc_mpu_test_app_BOARD_DEPENDENCY = yes
csl_xmc_mpu_test_app_CORE_DEPENDENCY = no
export csl_xmc_mpu_test_app_COMP_LIST
export csl_xmc_mpu_test_app_BOARD_DEPENDENCY
export csl_xmc_mpu_test_app_CORE_DEPENDENCY
csl_xmc_mpu_test_app_PKG_LIST = csl_xmc_mpu_test_app
csl_xmc_mpu_test_app_INCLUDE = $(csl_xmc_mpu_test_app_PATH)
csl_xmc_mpu_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_xmc_mpu_test_app_BOARDLIST
csl_xmc_mpu_test_app_$(SOC)_CORELIST = c66x
export csl_xmc_mpu_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_xmc_mpu_test_app

# MMCSD raw access app
csl_mmc_raw_access_app_COMP_LIST = csl_mmc_raw_access_app
csl_mmc_raw_access_app_RELPATH = ti/csl/example/mmcsd/mmc_raw_access
csl_mmc_raw_access_app_PATH = $(PDK_CSL_COMP_PATH)/example/mmcsd/mmc_raw_access
csl_mmc_raw_access_app_BOARD_DEPENDENCY = yes
csl_mmc_raw_access_app_CORE_DEPENDENCY = no
export csl_mmc_raw_access_app_COMP_LIST
export csl_mmc_raw_access_app_BOARD_DEPENDENCY
export csl_mmc_raw_access_app_CORE_DEPENDENCY
csl_mmc_raw_access_app_PKG_LIST = csl_mmc_raw_access_app
csl_mmc_raw_access_app_INCLUDE = $(csl_mmc_raw_access_app_PATH)
csl_mmc_raw_access_app_BOARDLIST = tda2xx-evm tda2px-evm idkAM572x evmAM572x tda2ex-evm idkAM571x tda2xx-rvp idkAM574x
export csl_mmc_raw_access_app_BOARDLIST
csl_mmc_raw_access_app_$(SOC)_CORELIST = a15_0
export csl_mmc_raw_access_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mmc_raw_access_app

# DCAN test app
csl_dcan_loopback_app_COMP_LIST = csl_dcan_loopback_app
csl_dcan_loopback_app_RELPATH = ti/csl/example/dcan/dcanLoopback/baremetal/
csl_dcan_loopback_app_PATH = $(PDK_CSL_COMP_PATH)/example/dcan/dcanLoopback/baremetal/
csl_dcan_loopback_app_BOARD_DEPENDENCY = yes
csl_dcan_loopback_app_CORE_DEPENDENCY = no
export csl_dcan_loopback_app_COMP_LIST
export csl_dcan_loopback_app_BOARD_DEPENDENCY
export csl_dcan_loopback_app_CORE_DEPENDENCY
csl_dcan_loopback_app_PKG_LIST = csl_dcan_loopback_app
csl_dcan_loopback_app_INCLUDE = $(csl_dcan_loopback_app_PATH)
csl_dcan_loopback_app_BOARDLIST = tda2xx-evm tda2px-evm idkAM572x idkAM571x tda2ex-evm evmAM572x tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_dcan_loopback_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_dcan_loopback_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x idkAM574x))
csl_dcan_loopback_app_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_dcan_loopback_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_dcan_loopback_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_dcan_loopback_app

# QSPI test app
csl_qspi_test_app_COMP_LIST = csl_qspi_test_app
csl_qspi_test_app_RELPATH = ti/csl/example/qspi/qspi_test
csl_qspi_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/qspi/qspi_test
csl_qspi_test_app_BOARD_DEPENDENCY = yes
csl_qspi_test_app_CORE_DEPENDENCY = no
export csl_qspi_test_app_COMP_LIST
export csl_qspi_test_app_BOARD_DEPENDENCY
export csl_qspi_test_app_CORE_DEPENDENCY
csl_qspi_test_app_PKG_LIST = csl_qspi_test_app
csl_qspi_test_app_INCLUDE = $(csl_qspi_test_app_PATH)
csl_qspi_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_qspi_test_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm idkAM572x idkAM571x evmDRA72x evmDRA75x tda2xx-rvp idkAM574x))
csl_qspi_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_qspi_test_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_qspi_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_qspi_test_app

# GPMC test app
csl_nor_read_write_app_COMP_LIST = csl_nor_read_write_app
csl_nor_read_write_app_RELPATH = ti/csl/example/gpmc/nor_read_write
csl_nor_read_write_app_PATH = $(PDK_CSL_COMP_PATH)/example/gpmc/nor_read_write
csl_nor_read_write_app_BOARD_DEPENDENCY = yes
csl_nor_read_write_app_CORE_DEPENDENCY = no
export csl_nor_read_write_app_COMP_LIST
export csl_nor_read_write_app_BOARD_DEPENDENCY
export csl_nor_read_write_app_CORE_DEPENDENCY
csl_nor_read_write_app_PKG_LIST = csl_nor_read_write_app
csl_nor_read_write_app_INCLUDE = $(csl_nor_read_write_app_PATH)
csl_nor_read_write_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp
export csl_nor_read_write_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm evmDRA72x evmDRA75x tda2xx-rvp))
csl_nor_read_write_app_$(SOC)_CORELIST = a15_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_nor_read_write_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_nor_read_write_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_nor_read_write_app

# WDTIMER test app
csl_wdtimer_reset_app_COMP_LIST = csl_wdtimer_reset_app
csl_wdtimer_reset_app_RELPATH = ti/csl/example/wdtimer/wdtimer_reset_app
csl_wdtimer_reset_app_PATH = $(PDK_CSL_COMP_PATH)/example/wdtimer/wdtimer_reset_app
csl_wdtimer_reset_app_BOARD_DEPENDENCY = yes
csl_wdtimer_reset_app_CORE_DEPENDENCY = no
export csl_wdtimer_reset_app_COMP_LIST
export csl_wdtimer_reset_app_BOARD_DEPENDENCY
export csl_wdtimer_reset_app_CORE_DEPENDENCY
csl_wdtimer_reset_app_PKG_LIST = csl_wdtimer_reset_app
csl_wdtimer_reset_app_INCLUDE = $(csl_wdtimer_reset_app_PATH)
csl_wdtimer_reset_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm idkAM572x idkAM571x evmAM572x tda2xx-rvp idkAM574x
export csl_wdtimer_reset_app_BOARDLIST
csl_wdtimer_reset_app_$(SOC)_CORELIST = a15_0
export csl_wdtimer_reset_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_wdtimer_reset_app

# TIMER test app
csl_timer_app_COMP_LIST = csl_timer_app
csl_timer_app_RELPATH = ti/csl/example/timer/timer_app
csl_timer_app_PATH = $(PDK_CSL_COMP_PATH)/example/timer/timer_app
csl_timer_app_BOARD_DEPENDENCY = yes
csl_timer_app_CORE_DEPENDENCY = no
export csl_timer_app_COMP_LIST
export csl_timer_app_BOARD_DEPENDENCY
export csl_timer_app_CORE_DEPENDENCY
csl_timer_app_PKG_LIST = csl_timer_app
csl_timer_app_INCLUDE = $(csl_timer_app_PATH)
csl_timer_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_timer_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm))
csl_timer_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x tda2xx-rvp idkAM574x))
csl_timer_app_$(SOC)_CORELIST = a15_0 c66x ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_timer_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_timer_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_timer_app

# PCIE EP WRITE test app
csl_pcie_ep_write_loopback_app_COMP_LIST = csl_pcie_ep_write_loopback_app
csl_pcie_ep_write_loopback_app_RELPATH = ti/csl/example/pcie/write_loopback/ep
csl_pcie_ep_write_loopback_app_PATH = $(PDK_CSL_COMP_PATH)/example/pcie/write_loopback/ep
csl_pcie_ep_write_loopback_app_BOARD_DEPENDENCY = yes
csl_pcie_ep_write_loopback_app_CORE_DEPENDENCY = no
export csl_pcie_ep_write_loopback_app_COMP_LIST
export csl_pcie_ep_write_loopback_app_BOARD_DEPENDENCY
export csl_pcie_ep_write_loopback_app_CORE_DEPENDENCY
csl_pcie_ep_write_loopback_app_PKG_LIST = csl_pcie_ep_write_loopback_app
csl_pcie_ep_write_loopback_app_INCLUDE = $(csl_pcie_ep_write_loopback_app_PATH)
csl_pcie_ep_write_loopback_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm idkAM572x idkAM571x evmAM572x tda2xx-rvp idkAM574x
export csl_pcie_ep_write_loopback_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm))
csl_pcie_ep_write_loopback_app_$(SOC)_CORELIST = a15_0
csl_pcie_ep_write_loopback_app_SBL_APPIMAGEGEN = yes
export csl_pcie_ep_write_loopback_app_SBL_APPIMAGEGEN
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x tda2xx-rvp idkAM574x))
csl_pcie_ep_write_loopback_app_$(SOC)_CORELIST = a15_0 c66x ipu1_0
endif
export csl_pcie_ep_write_loopback_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_pcie_ep_write_loopback_app

# PCIE RC WRITE test app
csl_pcie_rc_write_loopback_app_COMP_LIST = csl_pcie_rc_write_loopback_app
csl_pcie_rc_write_loopback_app_RELPATH = ti/csl/example/pcie/write_loopback/rc
csl_pcie_rc_write_loopback_app_PATH = $(PDK_CSL_COMP_PATH)/example/pcie/write_loopback/rc
csl_pcie_rc_write_loopback_app_BOARD_DEPENDENCY = yes
csl_pcie_rc_write_loopback_app_CORE_DEPENDENCY = no
export csl_pcie_rc_write_loopback_app_COMP_LIST
export csl_pcie_rc_write_loopback_app_BOARD_DEPENDENCY
export csl_pcie_rc_write_loopback_app_CORE_DEPENDENCY
csl_pcie_rc_write_loopback_app_PKG_LIST = csl_pcie_rc_write_loopback_app
csl_pcie_rc_write_loopback_app_INCLUDE = $(csl_pcie_rc_write_loopback_app_PATH)
csl_pcie_rc_write_loopback_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm idkAM572x idkAM571x evmAM572x tda2xx-rvp idkAM574x
export csl_pcie_rc_write_loopback_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_pcie_rc_write_loopback_app_$(SOC)_CORELIST = a15_0
csl_pcie_rc_write_loopback_app_SBL_APPIMAGEGEN = yes
export csl_pcie_rc_write_loopback_app_SBL_APPIMAGEGEN
endif
ifeq ($(BOARD),$(filter $(BOARD), idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x idkAM574x))
csl_pcie_rc_write_loopback_app_$(SOC)_CORELIST = a15_0 c66x ipu1_0
endif
export csl_pcie_rc_write_loopback_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_pcie_rc_write_loopback_app

# MMU test app
csl_mmu_tlb_twl_app_COMP_LIST = csl_mmu_tlb_twl_app
csl_mmu_tlb_twl_app_RELPATH = ti/csl/example/mmu/mmu_tlb_twl
csl_mmu_tlb_twl_app_PATH = $(PDK_CSL_COMP_PATH)/example/mmu/mmu_tlb_twl
csl_mmu_tlb_twl_app_BOARD_DEPENDENCY = yes
csl_mmu_tlb_twl_app_CORE_DEPENDENCY = no
export csl_mmu_tlb_twl_app_COMP_LIST
export csl_mmu_tlb_twl_app_BOARD_DEPENDENCY
export csl_mmu_tlb_twl_app_CORE_DEPENDENCY
csl_mmu_tlb_twl_app_PKG_LIST = csl_mmu_tlb_twl_app
csl_mmu_tlb_twl_app_INCLUDE = $(csl_mmu_tlb_twl_app_PATH)
csl_mmu_tlb_twl_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmAM572x evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_mmu_tlb_twl_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda3xx))
csl_mmu_tlb_twl_app_$(SOC)_CORELIST = c66x arp32_1
else
csl_mmu_tlb_twl_app_$(SOC)_CORELIST = c66x
endif
export csl_mmu_tlb_twl_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mmu_tlb_twl_app

# MMU a15 data validation test app
csl_mmu_a15_data_validation_app_COMP_LIST = csl_mmu_a15_data_validation_app
csl_mmu_a15_data_validation_app_RELPATH = ti/csl/example/mmu/a15_data_validation
csl_mmu_a15_data_validation_app_PATH = $(PDK_CSL_COMP_PATH)/example/mmu/a15_data_validation
csl_mmu_a15_data_validation_app_BOARD_DEPENDENCY = yes
csl_mmu_a15_data_validation_app_CORE_DEPENDENCY = no
export csl_mmu_a15_data_validation_app_COMP_LIST
export csl_mmu_a15_data_validation_app_BOARD_DEPENDENCY
export csl_mmu_a15_data_validation_app_CORE_DEPENDENCY
csl_mmu_a15_data_validation_app_PKG_LIST = csl_mmu_a15_data_validation_app
csl_mmu_a15_data_validation_app_INCLUDE = $(csl_mmu_a15_data_validation_app_PATH)
csl_mmu_a15_data_validation_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp
export csl_mmu_a15_data_validation_app_BOARDLIST
csl_mmu_a15_data_validation_app_$(SOC)_CORELIST = a15_0
export csl_mmu_a15_data_validation_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mmu_a15_data_validation_app

# MMU translation fault handle test app
csl_mmu_translation_fault_handle_app_COMP_LIST = csl_mmu_translation_fault_handle_app
csl_mmu_translation_fault_handle_app_RELPATH = ti/csl/example/mmu/translation_fault_handle
csl_mmu_translation_fault_handle_app_PATH = $(PDK_CSL_COMP_PATH)/example/mmu/translation_fault_handle
csl_mmu_translation_fault_handle_app_BOARD_DEPENDENCY = yes
csl_mmu_translation_fault_handle_app_CORE_DEPENDENCY = no
export csl_mmu_translation_fault_handle_app_COMP_LIST
export csl_mmu_translation_fault_handle_app_BOARD_DEPENDENCY
export csl_mmu_translation_fault_handle_app_CORE_DEPENDENCY
csl_mmu_translation_fault_handle_app_PKG_LIST = csl_mmu_translation_fault_handle_app
csl_mmu_translation_fault_handle_app_INCLUDE = $(csl_mmu_translation_fault_handle_app_PATH)
csl_mmu_translation_fault_handle_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_mmu_translation_fault_handle_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda3xx))
csl_mmu_translation_fault_handle_app_$(SOC)_CORELIST = ipu1_0 c66x
else
csl_mmu_translation_fault_handle_app_$(SOC)_CORELIST = c66x a15_0
endif
export csl_mmu_translation_fault_handle_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mmu_translation_fault_handle_app

# CRC test app
csl_crc_semicpu_test_app_COMP_LIST = csl_crc_semicpu_test_app
csl_crc_semicpu_test_app_RELPATH = ti/csl/example/crc/crc_semicputest_app
csl_crc_semicpu_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/crc/crc_semicputest_app
csl_crc_semicpu_test_app_BOARD_DEPENDENCY = yes
csl_crc_semicpu_test_app_CORE_DEPENDENCY = no
export csl_crc_semicpu_test_app_COMP_LIST
export csl_crc_semicpu_test_app_BOARD_DEPENDENCY
export csl_crc_semicpu_test_app_CORE_DEPENDENCY
csl_crc_semicpu_test_app_PKG_LIST = csl_crc_semicpu_test_app
csl_crc_semicpu_test_app_INCLUDE = $(csl_crc_semicpu_test_app_PATH)
csl_crc_semicpu_test_app_BOARDLIST = tda3xx-evm evmDRA78x
export csl_crc_semicpu_test_app_BOARDLIST
csl_crc_semicpu_test_app_$(SOC)_CORELIST = ipu1_0 c66x
export csl_crc_semicpu_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_crc_semicpu_test_app

# ECC test app
csl_ecc_test_app_COMP_LIST = csl_ecc_test_app
csl_ecc_test_app_RELPATH = ti/csl/example/ecc/ecc_test_app
csl_ecc_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/ecc/ecc_test_app
csl_ecc_test_app_BOARD_DEPENDENCY = yes
csl_ecc_test_app_CORE_DEPENDENCY = no
export csl_ecc_test_app_COMP_LIST
export csl_ecc_test_app_BOARD_DEPENDENCY
export csl_ecc_test_app_CORE_DEPENDENCY
csl_ecc_test_app_PKG_LIST = csl_ecc_test_app
csl_ecc_test_app_INCLUDE = $(csl_ecc_test_app_PATH)
csl_ecc_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp idkAM574x
export csl_ecc_test_app_BOARDLIST
csl_ecc_test_app_$(SOC)_CORELIST = ipu1_0
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm))
csl_ecc_test_app_$(SOC)_CORELIST += c66x
endif
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp idkAM574x))
csl_ecc_test_app_$(SOC)_CORELIST += c66x a15_0
endif
export csl_ecc_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_ecc_test_app

# OCMC test app
csl_ocmc_basic_test_app_COMP_LIST = csl_ocmc_basic_test_app
csl_ocmc_basic_test_app_RELPATH = ti/csl/example/ocmc/ocmc_basic
csl_ocmc_basic_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/ocmc/ocmc_basic
csl_ocmc_basic_test_app_BOARD_DEPENDENCY = yes
csl_ocmc_basic_test_app_CORE_DEPENDENCY = no
export csl_ocmc_basic_test_app_COMP_LIST
export csl_ocmc_basic_test_app_BOARD_DEPENDENCY
export csl_ocmc_basic_test_app_CORE_DEPENDENCY
csl_ocmc_basic_test_app_PKG_LIST = csl_ocmc_basic_test_app
csl_ocmc_basic_test_app_INCLUDE = $(csl_ocmc_basic_test_app_PATH)
csl_ocmc_basic_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2xx-rvp
export csl_ocmc_basic_test_app_BOARDLIST
csl_ocmc_basic_test_app_$(SOC)_CORELIST = ipu1_0
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm evmDRA72x evmDRA75x tda2xx-rvp))
csl_ocmc_basic_test_app_$(SOC)_CORELIST += a15_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm evmDRA78x))
csl_ocmc_basic_test_app_$(SOC)_CORELIST += c66x
endif
export csl_ocmc_basic_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_ocmc_basic_test_app

# ESM test app
csl_esm_eve_reset_test_app_COMP_LIST = csl_esm_eve_reset_test_app
csl_esm_eve_reset_test_app_RELPATH = ti/csl/example/esm/esm_eve_reset_test_app
csl_esm_eve_reset_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/esm/esm_eve_reset_test_app
csl_esm_eve_reset_test_app_BOARD_DEPENDENCY = yes
csl_esm_eve_reset_test_app_CORE_DEPENDENCY = no
export csl_esm_eve_reset_test_app_COMP_LIST
export csl_esm_eve_reset_test_app_BOARD_DEPENDENCY
export csl_esm_eve_reset_test_app_CORE_DEPENDENCY
csl_esm_eve_reset_test_app_PKG_LIST = csl_esm_eve_reset_test_app
csl_esm_eve_reset_test_app_INCLUDE = $(csl_esm_eve_reset_test_app_PATH)
csl_esm_eve_reset_test_app_BOARDLIST = tda3xx-evm evmDRA78x
export csl_esm_eve_reset_test_app_BOARDLIST
csl_esm_eve_reset_test_app_$(SOC)_CORELIST = ipu1_0
export csl_esm_eve_reset_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_esm_eve_reset_test_app

# DCC test app
csl_dcc_singleshotmode_app_COMP_LIST = csl_dcc_singleshotmode_app
csl_dcc_singleshotmode_app_RELPATH = ti/csl/example/dcc/dcc_singleshotmode_app
csl_dcc_singleshotmode_app_PATH = $(PDK_CSL_COMP_PATH)/example/dcc/dcc_singleshotmode_app
csl_dcc_singleshotmode_app_BOARD_DEPENDENCY = yes
csl_dcc_singleshotmode_app_CORE_DEPENDENCY = no
export csl_dcc_singleshotmode_app_COMP_LIST
export csl_dcc_singleshotmode_app_BOARD_DEPENDENCY
export csl_dcc_singleshotmode_app_CORE_DEPENDENCY
csl_dcc_singleshotmode_app_PKG_LIST = csl_dcc_singleshotmode_app
csl_dcc_singleshotmode_app_INCLUDE = $(csl_dcc_singleshotmode_app_PATH)
csl_dcc_singleshotmode_app_BOARDLIST = tda3xx-evm evmDRA78x
export csl_dcc_singleshotmode_app_BOARDLIST
csl_dcc_singleshotmode_app_$(SOC)_CORELIST = ipu1_0
export csl_dcc_singleshotmode_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_dcc_singleshotmode_app

# RTI test app
csl_rti_dwwd_test_app_COMP_LIST = csl_rti_dwwd_test_app
csl_rti_dwwd_test_app_RELPATH = ti/csl/example/rti/rti_dwwdtest_app
csl_rti_dwwd_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/rti/rti_dwwdtest_app
csl_rti_dwwd_test_app_BOARD_DEPENDENCY = yes
csl_rti_dwwd_test_app_CORE_DEPENDENCY = no
export csl_rti_dwwd_test_app_COMP_LIST
export csl_rti_dwwd_test_app_BOARD_DEPENDENCY
export csl_rti_dwwd_test_app_CORE_DEPENDENCY
csl_rti_dwwd_test_app_PKG_LIST = csl_rti_dwwd_test_app
csl_rti_dwwd_test_app_INCLUDE = $(csl_rti_dwwd_test_app_PATH)
csl_rti_dwwd_test_app_BOARDLIST = tda3xx-evm evmDRA78x
export csl_rti_dwwd_test_app_BOARDLIST
csl_rti_dwwd_test_app_$(SOC)_CORELIST = ipu1_0
export csl_rti_dwwd_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_rti_dwwd_test_app

# ADC test app
csl_adc_singleshot_test_app_COMP_LIST = csl_adc_singleshot_test_app
csl_adc_singleshot_test_app_RELPATH = ti/csl/example/adc/adc_singleshot_test_app
csl_adc_singleshot_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/adc/adc_singleshot_test_app
csl_adc_singleshot_test_app_BOARD_DEPENDENCY = yes
csl_adc_singleshot_test_app_CORE_DEPENDENCY = no
export csl_adc_singleshot_test_app_COMP_LIST
export csl_adc_singleshot_test_app_BOARD_DEPENDENCY
export csl_adc_singleshot_test_app_CORE_DEPENDENCY
csl_adc_singleshot_test_app_PKG_LIST = csl_adc_singleshot_test_app
csl_adc_singleshot_test_app_INCLUDE = $(csl_adc_singleshot_test_app_PATH)
csl_adc_singleshot_test_app_BOARDLIST = tda3xx-evm evmDRA78x
export csl_adc_singleshot_test_app_BOARDLIST
csl_adc_singleshot_test_app_$(SOC)_CORELIST = ipu1_0
export csl_adc_singleshot_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_adc_singleshot_test_app

# EPWM test app
csl_epwm_duty_cycle_test_app_COMP_LIST = csl_epwm_duty_cycle_test_app
csl_epwm_duty_cycle_test_app_RELPATH = ti/csl/example/epwm/epwm_duty_cycle_test_app
csl_epwm_duty_cycle_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/epwm/epwm_duty_cycle_test_app
csl_epwm_duty_cycle_test_app_BOARD_DEPENDENCY = yes
csl_epwm_duty_cycle_test_app_CORE_DEPENDENCY = no
export csl_epwm_duty_cycle_test_app_COMP_LIST
export csl_epwm_duty_cycle_test_app_BOARD_DEPENDENCY
export csl_epwm_duty_cycle_test_app_CORE_DEPENDENCY
csl_epwm_duty_cycle_test_app_PKG_LIST = csl_epwm_duty_cycle_test_app
csl_epwm_duty_cycle_test_app_INCLUDE = $(csl_epwm_duty_cycle_test_app_PATH)
csl_epwm_duty_cycle_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_epwm_duty_cycle_test_app_BOARDLIST
csl_epwm_duty_cycle_test_app_$(SOC)_CORELIST = ipu1_0
export csl_epwm_duty_cycle_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_epwm_duty_cycle_test_app

# MCAN test app
csl_mcan_evm_loopback_app_COMP_LIST = csl_mcan_evm_loopback_app
csl_mcan_evm_loopback_app_RELPATH = ti/csl/example/mcan/mcanEvmLoopback
csl_mcan_evm_loopback_app_PATH = $(PDK_CSL_COMP_PATH)/example/mcan/mcanEvmLoopback
csl_mcan_evm_loopback_app_BOARD_DEPENDENCY = yes
csl_mcan_evm_loopback_app_CORE_DEPENDENCY = no
export csl_mcan_evm_loopback_app_COMP_LIST
export csl_mcan_evm_loopback_app_BOARD_DEPENDENCY
export csl_mcan_evm_loopback_app_CORE_DEPENDENCY
csl_mcan_evm_loopback_app_PKG_LIST = csl_mcan_evm_loopback_app
csl_mcan_evm_loopback_app_INCLUDE = $(csl_mcan_evm_loopback_app_PATH)
csl_mcan_evm_loopback_app_BOARDLIST = tda3xx-evm evmDRA78x tda2px-evm
export csl_mcan_evm_loopback_app_BOARDLIST
csl_mcan_evm_loopback_app_$(SOC)_CORELIST = ipu1_0
export csl_mcan_evm_loopback_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_mcan_evm_loopback_app
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm tda2px-evm))
csl_mcan_evm_loopback_app_SBL_APPIMAGEGEN = yes
export csl_mcan_evm_loopback_app_SBL_APPIMAGEGEN
endif

# DDR test app
csl_ddr_test_app_COMP_LIST = csl_ddr_test_app
csl_ddr_test_app_RELPATH = ti/csl/example/ddr/ddr_test_app
csl_ddr_test_app_PATH = $(PDK_CSL_COMP_PATH)/example/ddr/ddr_test_app
csl_ddr_test_app_BOARD_DEPENDENCY = yes
csl_ddr_test_app_CORE_DEPENDENCY = yes
export csl_ddr_test_app_COMP_LIST
export csl_ddr_test_app_BOARD_DEPENDENCY
export csl_ddr_test_app_CORE_DEPENDENCY
csl_ddr_test_app_PKG_LIST = csl_ddr_test_app
csl_ddr_test_app_INCLUDE = $(csl_ddr_test_app_PATH)
csl_ddr_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export csl_ddr_test_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
csl_ddr_test_app_$(SOC)_CORELIST = a15_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm))
csl_ddr_test_app_$(SOC)_CORELIST = ipu1_0
endif
export csl_ddr_test_app_$(SOC)_CORELIST
csl_EXAMPLE_LIST += csl_ddr_test_app
csl_ddr_test_app_SBL_APPIMAGEGEN = yes
export csl_ddr_test_app_SBL_APPIMAGEGEN

#include sub component.mk file
-include $(PDK_CSL_COMP_PATH)/test/csl_test_component.mk

ifneq ($(csl_test_LIB_LIST),)
  csl_LIB_LIST += $(csl_test_LIB_LIST)
endif
ifneq ($(csl_test_EXAMPLE_LIST),)
  csl_EXAMPLE_LIST += $(csl_test_EXAMPLE_LIST)
endif

export csl_LIB_LIST
export csl_EXAMPLE_LIST

csl_component_make_include := 1
endif
