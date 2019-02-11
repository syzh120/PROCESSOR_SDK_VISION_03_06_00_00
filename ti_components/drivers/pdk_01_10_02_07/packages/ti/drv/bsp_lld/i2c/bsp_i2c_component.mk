# File: bsp_i2c_component.mk
#       This file is component include make file of BSP I2C LLD library.
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
ifeq ($(bsp_i2c_component_make_include), )

bsp_i2c_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
bsp_i2c_default_tda2xx_CORELIST = ipu1_0
bsp_i2c_default_tda2px_CORELIST = ipu1_0
bsp_i2c_default_tda2ex_CORELIST = ipu1_0
bsp_i2c_default_tda3xx_CORELIST = ipu1_0

############################
# bsp_i2c package
# List of components included under bsp_i2c
# The components included here are built and will be part of bsp_i2c lib
############################
bsp_i2c_LIB_LIST = bsp_i2c

############################
# bsp_i2c examples
# List of examples under bsp_i2c (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
bsp_i2c_EXAMPLE_LIST =

#
# BSP I2C Modules
#

# BSP I2C LIB
bsp_i2c_COMP_LIST = bsp_i2c
bsp_i2c_RELPATH = ti/drv/bsp_lld/i2c
bsp_i2c_PATH = $(PDK_BSP_I2C_COMP_PATH)
bsp_i2c_LIBNAME = bsp_i2c
bsp_i2c_LIBPATH = $(PDK_BSP_I2C_COMP_PATH)/lib
bsp_i2c_MAKEFILE = -fsrc/makefile
export bsp_i2c_MAKEFILE
export bsp_i2c_LIBNAME
export bsp_i2c_LIBPATH
bsp_i2c_BOARD_DEPENDENCY = no
bsp_i2c_CORE_DEPENDENCY = no
export bsp_i2c_COMP_LIST
export bsp_i2c_BOARD_DEPENDENCY
export bsp_i2c_CORE_DEPENDENCY
bsp_i2c_PKG_LIST = bsp_i2c
bsp_i2c_INCLUDE = $(bsp_i2c_PATH)
bsp_i2c_SOCLIST = $(bsp_i2c_default_SOCLIST)
export bsp_i2c_SOCLIST
bsp_i2c_$(SOC)_CORELIST = $(bsp_i2c_default_$(SOC)_CORELIST)
export bsp_i2c_$(SOC)_CORELIST

# I2C LED Blink Example
bsp_examples_i2c_led_blink_COMP_LIST = bsp_examples_i2c_led_blink
bsp_examples_i2c_led_blink_RELPATH = ti/drv/bsp_lld/i2c/examples/i2c_led_blink
bsp_examples_i2c_led_blink_PATH = $(PDK_BSP_I2C_COMP_PATH)/examples/i2c_led_blink
bsp_examples_i2c_led_blink_BOARD_DEPENDENCY = yes
bsp_examples_i2c_led_blink_CORE_DEPENDENCY = no
bsp_examples_i2c_led_blink_XDC_CONFIGURO = yes
export bsp_examples_i2c_led_blink_COMP_LIST
export bsp_examples_i2c_led_blink_BOARD_DEPENDENCY
export bsp_examples_i2c_led_blink_CORE_DEPENDENCY
export bsp_examples_i2c_led_blink_XDC_CONFIGURO
bsp_examples_i2c_led_blink_PKG_LIST = bsp_examples_i2c_led_blink
bsp_examples_i2c_led_blink_INCLUDE = $(bsp_examples_i2c_led_blink_PATH)
bsp_examples_i2c_led_blink_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export bsp_examples_i2c_led_blink_BOARDLIST
bsp_examples_i2c_led_blink_$(SOC)_CORELIST = ipu1_0
export bsp_examples_i2c_led_blink_$(SOC)_CORELIST
bsp_i2c_EXAMPLE_LIST += bsp_examples_i2c_led_blink
bsp_examples_i2c_led_blink_SBL_APPIMAGEGEN = yes
export bsp_examples_i2c_led_blink_SBL_APPIMAGEGEN

# I2C Utility Example
bsp_examples_i2c_utility_COMP_LIST = bsp_examples_i2c_utility
bsp_examples_i2c_utility_RELPATH = ti/drv/bsp_lld/i2c/examples/i2c_utility
bsp_examples_i2c_utility_PATH = $(PDK_BSP_I2C_COMP_PATH)/examples/i2c_utility
bsp_examples_i2c_utility_BOARD_DEPENDENCY = yes
bsp_examples_i2c_utility_CORE_DEPENDENCY = no
bsp_examples_i2c_utility_XDC_CONFIGURO = yes
export bsp_examples_i2c_utility_COMP_LIST
export bsp_examples_i2c_utility_BOARD_DEPENDENCY
export bsp_examples_i2c_utility_CORE_DEPENDENCY
export bsp_examples_i2c_utility_XDC_CONFIGURO
bsp_examples_i2c_utility_PKG_LIST = bsp_examples_i2c_utility
bsp_examples_i2c_utility_INCLUDE = $(bsp_examples_i2c_utility_PATH)
bsp_examples_i2c_utility_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export bsp_examples_i2c_utility_BOARDLIST
bsp_examples_i2c_utility_$(SOC)_CORELIST = ipu1_0
export bsp_examples_i2c_utility_$(SOC)_CORELIST
bsp_i2c_EXAMPLE_LIST += bsp_examples_i2c_utility
bsp_examples_i2c_utility_SBL_APPIMAGEGEN = yes
export bsp_examples_i2c_utility_SBL_APPIMAGEGEN

export bsp_i2c_LIB_LIST
export bsp_i2c_EXAMPLE_LIST

bsp_i2c_component_make_include := 1
endif
