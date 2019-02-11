# File: bsp_uart_component.mk
#       This file is component include make file of VPS library.
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
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
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
ifeq ($(bsp_uart_component_make_include), )

bsp_uart_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
bsp_uart_default_tda2xx_CORELIST = ipu1_0
bsp_uart_default_tda2px_CORELIST = ipu1_0
bsp_uart_default_tda2ex_CORELIST = ipu1_0
bsp_uart_default_tda3xx_CORELIST = ipu1_0

############################
# bsp_uart package
# List of components included under bsp_uart
# The components included here are built and will be part of bsp_uart lib
############################
bsp_uart_LIB_LIST = bsp_uart

############################
# bsp_uart examples
# List of examples under bsp_uart (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
bsp_uart_EXAMPLE_LIST =

#
# BSP UART Modules
#

# BSP UART LIB
bsp_uart_COMP_LIST = bsp_uart
bsp_uart_RELPATH = ti/drv/bsp_lld/uart
bsp_uart_PATH = $(PDK_BSP_UART_COMP_PATH)
bsp_uart_LIBNAME = bsp_uart
bsp_uart_LIBPATH = $(PDK_BSP_UART_COMP_PATH)/lib
bsp_uart_MAKEFILE = -fsrc/makefile
export bsp_uart_MAKEFILE
export bsp_uart_LIBNAME
export bsp_uart_LIBPATH
bsp_uart_BOARD_DEPENDENCY = no
bsp_uart_CORE_DEPENDENCY = no
export bsp_uart_COMP_LIST
export bsp_uart_BOARD_DEPENDENCY
export bsp_uart_CORE_DEPENDENCY
bsp_uart_PKG_LIST = bsp_uart
bsp_uart_INCLUDE = $(bsp_uart_PATH)
bsp_uart_SOCLIST = $(bsp_uart_default_SOCLIST)
export bsp_uart_SOCLIST
bsp_uart_$(SOC)_CORELIST = $(bsp_uart_default_$(SOC)_CORELIST)
export bsp_uart_$(SOC)_CORELIST

# UART Echo Example
bsp_examples_uart_echo_COMP_LIST = bsp_examples_uart_echo
bsp_examples_uart_echo_RELPATH = ti/drv/bsp_lld/uart/examples/uart_echo
bsp_examples_uart_echo_PATH = $(PDK_BSP_UART_COMP_PATH)/examples/uart_echo
bsp_examples_uart_echo_BOARD_DEPENDENCY = yes
bsp_examples_uart_echo_CORE_DEPENDENCY = no
bsp_examples_uart_echo_XDC_CONFIGURO = yes
export bsp_examples_uart_echo_COMP_LIST
export bsp_examples_uart_echo_BOARD_DEPENDENCY
export bsp_examples_uart_echo_CORE_DEPENDENCY
export bsp_examples_uart_echo_XDC_CONFIGURO
bsp_examples_uart_echo_PKG_LIST = bsp_examples_uart_echo
bsp_examples_uart_echo_INCLUDE = $(bsp_examples_uart_echo_PATH)
bsp_examples_uart_echo_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export bsp_examples_uart_echo_BOARDLIST
bsp_examples_uart_echo_$(SOC)_CORELIST = ipu1_0
export bsp_examples_uart_echo_$(SOC)_CORELIST
bsp_uart_EXAMPLE_LIST += bsp_examples_uart_echo
bsp_examples_uart_echo_SBL_APPIMAGEGEN = yes
export bsp_examples_uart_echo_SBL_APPIMAGEGEN

#Include UT application
-include $(PDK_BSP_UART_COMP_PATH)/unit_test/bsp_uart_ut_component.mk

export bsp_uart_LIB_LIST
export bsp_uart_EXAMPLE_LIST

BSPUART_CFLAGS += -DTRACE_ENABLE
ifeq ($(BUILD_PROFILE_$(CORE)),debug)
# Enable asserts for debug build
  BSPUART_CFLAGS += -DASSERT_ENABLE
endif
ifeq ($(BUILD_PROFILE_$(CORE)),release)
# Enable asserts for release build
  BSPUART_CFLAGS += -DASSERT_ENABLE
endif

export BSPUART_CFLAGS

bsp_uart_component_make_include := 1
endif
