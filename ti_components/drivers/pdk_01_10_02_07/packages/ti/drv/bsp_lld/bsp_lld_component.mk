# File: bsp_lld_component.mk
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
ifeq ($(bsp_lld_component_make_include), )

#Sub component path
PDK_BSP_I2C_COMP_PATH = $(PDK_BSP_LLD_COMP_PATH)/i2c
export PDK_BSP_I2C_COMP_PATH
PDK_BSP_UART_COMP_PATH = $(PDK_BSP_LLD_COMP_PATH)/uart
export PDK_BSP_UART_COMP_PATH
PDK_BSP_MCSPI_COMP_PATH = $(PDK_BSP_LLD_COMP_PATH)/mcspi
export PDK_BSP_MCSPI_COMP_PATH

#include sub component.mk file
-include $(PDK_BSP_LLD_COMP_PATH)/i2c/bsp_i2c_component.mk
-include $(PDK_BSP_LLD_COMP_PATH)/uart/bsp_uart_component.mk
-include $(PDK_BSP_LLD_COMP_PATH)/mcspi/bsp_mcspi_component.mk

############################
# bsp_lld package
# List of components included under bsp_lld
# The components included here are built and will be part of bsp_lld lib
############################
bsp_lld_LIB_LIST =
ifneq ($(bsp_i2c_LIB_LIST),)
  bsp_lld_LIB_LIST += $(bsp_i2c_LIB_LIST)
endif
ifneq ($(bsp_uart_LIB_LIST),)
  bsp_lld_LIB_LIST += $(bsp_uart_LIB_LIST)
endif
ifneq ($(bsp_mcspi_LIB_LIST),)
  bsp_lld_LIB_LIST += $(bsp_mcspi_LIB_LIST)
endif

############################
# bsp_lld examples
# List of examples under bsp_lld (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
bsp_lld_EXAMPLE_LIST =
ifneq ($(bsp_i2c_EXAMPLE_LIST),)
  bsp_lld_EXAMPLE_LIST += $(bsp_i2c_EXAMPLE_LIST)
endif
ifneq ($(bsp_uart_EXAMPLE_LIST),)
  bsp_lld_EXAMPLE_LIST += $(bsp_uart_EXAMPLE_LIST)
endif
ifneq ($(bsp_mcspi_EXAMPLE_LIST),)
  bsp_lld_EXAMPLE_LIST += $(bsp_mcspi_EXAMPLE_LIST)
endif

export bsp_lld_LIB_LIST
export bsp_lld_EXAMPLE_LIST

bsp_lld_component_make_include := 1
endif
