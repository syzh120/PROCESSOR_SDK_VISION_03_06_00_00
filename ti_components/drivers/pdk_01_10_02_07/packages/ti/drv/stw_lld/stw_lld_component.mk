# File: stw_lld_component.mk
#       This file is component include make file of STW LLD library.
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
stw_lld_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
stw_lld_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda2ex-eth-srv tda2xx-rvp
stw_lld_tda2xx_CORELIST = a15_0 c66 ipu1_0
stw_lld_tda2px_CORELIST = a15_0 c66 ipu1_0
stw_lld_tda2ex_CORELIST = a15_0 c66 ipu1_0
stw_lld_tda3xx_CORELIST = c66 ipu1_0
stw_lld_dra72x_CORELIST = a15_0 c66 ipu1_0
stw_lld_dra75x_CORELIST = a15_0 c66 ipu1_0
stw_lld_dra78x_CORELIST = c66 ipu1_0

############################
# stw_lld package
# List of components included under stw_lld
# The components included here are built and will be part of stw_lld
############################
stw_lld_LIB_LIST = i2c_lld stw_platform stw_uartconsole stw_fatlib stw_fatlib_edma stw_boards stw_devices stw_examples_utility

ifeq ($(stw_lld_component_make_include), )

#Sub component path
PDK_STW_I2C_LLD_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/i2clld
export PDK_STW_I2C_LLD_COMP_PATH
PDK_STW_PLATFORM_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/platform
export PDK_STW_PLATFORM_COMP_PATH
PDK_STW_UARTCONSOLE_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/uartconsole
export PDK_STW_UARTCONSOLE_COMP_PATH
PDK_STW_FATLIB_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/fatlib
export PDK_STW_FATLIB_COMP_PATH
PDK_STW_BOARDS_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/boards
export PDK_STW_BOARDS_COMP_PATH
PDK_STW_DEVICES_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/devices
export PDK_STW_DEVICES_COMP_PATH
PDK_STW_EXAMPLE_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/examples
export PDK_STW_EXAMPLE_COMP_PATH
PDK_STW_UNIT_TEST_COMP_PATH = $(PDK_STW_LLD_COMP_PATH)/unit_test
export PDK_STW_UNIT_TEST_COMP_PATH

#include sub component.mk file
-include $(PDK_STW_LLD_COMP_PATH)/i2clld/i2c_lld_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/platform/stw_platform_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/uartconsole/stw_uartconsole_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/fatlib/stw_fatlib_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/boards/stw_boards_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/devices/stw_devices_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/examples/stw_examples_component.mk
-include $(PDK_STW_LLD_COMP_PATH)/unit_test/stw_unit_test_component.mk

############################
# stw_lld package
# List of components included under stw_lld
# The components included here are built and will be part of stw_lld lib
############################
stw_lld_LIB_LIST =
ifneq ($(i2c_lld_LIB_LIST),)
  stw_lld_LIB_LIST += $(i2c_lld_LIB_LIST)
endif
ifneq ($(stw_platform_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_platform_LIB_LIST)
endif
ifneq ($(stw_uartconsole_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_uartconsole_LIB_LIST)
endif
ifneq ($(stw_fatlib_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_fatlib_LIB_LIST)
endif
ifneq ($(stw_boards_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_boards_LIB_LIST)
endif
ifneq ($(stw_devices_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_devices_LIB_LIST)
endif
ifneq ($(stw_examples_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_examples_LIB_LIST)
endif
ifneq ($(stw_unit_test_LIB_LIST),)
  stw_lld_LIB_LIST += $(stw_unit_test_LIB_LIST)
endif

############################
# stw_lld examples
# List of examples under stw_lld (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
stw_lld_EXAMPLE_LIST =
ifneq ($(i2c_lld_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(i2c_lld_EXAMPLE_LIST)
endif
ifneq ($(stw_platform_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_platform_EXAMPLE_LIST)
endif
ifneq ($(stw_uartconsole_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_uartconsole_EXAMPLE_LIST)
endif
ifneq ($(stw_fatlib_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_fatlib_EXAMPLE_LIST)
endif
ifneq ($(stw_boards_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_boards_EXAMPLE_LIST)
endif
ifneq ($(stw_devices_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_devices_EXAMPLE_LIST)
endif
ifneq ($(stw_examples_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_examples_EXAMPLE_LIST)
endif
ifneq ($(stw_unit_test_EXAMPLE_LIST),)
  stw_lld_EXAMPLE_LIST += $(stw_unit_test_EXAMPLE_LIST)
endif

############################
# stw_lld duplicate examples
# List of examples under stw_lld (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
stw_lld_DUP_EXAMPLE_LIST =
ifneq ($(stw_unit_test_DUP_EXAMPLE_LIST),)
  stw_lld_DUP_EXAMPLE_LIST += $(stw_unit_test_DUP_EXAMPLE_LIST)
endif

STW_LLD_CFLAGS =

ifeq ($(SOC), dra72x)
    STW_LLD_CFLAGS = -DSOC_TDA2EX
endif
ifeq ($(SOC), dra75x)
    STW_LLD_CFLAGS = -DSOC_TDA2XX
endif
ifeq ($(SOC), dra78x)
    STW_LLD_CFLAGS = -DSOC_TDA3XX
endif

export STW_LLD_CFLAGS
export stw_lld_LIB_LIST
export stw_lld_EXAMPLE_LIST
export stw_lld_DUP_EXAMPLE_LIST

stw_lld_component_make_include := 1
endif
