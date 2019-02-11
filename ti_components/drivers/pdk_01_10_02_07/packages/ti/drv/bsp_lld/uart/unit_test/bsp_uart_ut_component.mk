# File: bsp_uart_ut_component.mk
#       This file is component include make file of BSP UART unit test.
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
ifeq ($(bsp_uart_ut_component_make_include), )

# UART unit test
bsp_test_uart_COMP_LIST = bsp_test_uart
bsp_test_uart_RELPATH = ti/drv/bsp_lld/uart/unit_test/uartUt
bsp_test_uart_PATH = $(PDK_BSP_UART_COMP_PATH)/unit_test/uartUt
bsp_test_uart_BOARD_DEPENDENCY = yes
bsp_test_uart_CORE_DEPENDENCY = no
bsp_test_uart_XDC_CONFIGURO = yes
export bsp_test_uart_COMP_LIST
export bsp_test_uart_BOARD_DEPENDENCY
export bsp_test_uart_CORE_DEPENDENCY
export bsp_test_uart_XDC_CONFIGURO
bsp_test_uart_PKG_LIST = bsp_test_uart
bsp_test_uart_INCLUDE = $(bsp_test_uart_PATH)
bsp_test_uart_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export bsp_test_uart_BOARDLIST
bsp_test_uart_$(SOC)_CORELIST = $(bsp_uart_default_$(SOC)_CORELIST)
export bsp_test_uart_$(SOC)_CORELIST
bsp_uart_EXAMPLE_LIST += bsp_test_uart

bsp_uart_ut_component_make_include := 1
endif
