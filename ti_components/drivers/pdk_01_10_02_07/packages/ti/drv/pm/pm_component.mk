#*******************************************************************************
#                                                                              *
# Copyright (c) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/  *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: component.mk
#       This file is component include make file of PM library.
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
ifeq ($(pm_component_make_include), )

pmrtos_SOCLIST = am574x am572x dra72x dra75x am571x dra78x
pmrtos_BOARDLIST = evmDRA72x evmDRA75x evmDRA78x evmAM572x idkAM572x idkAM571x idkAM574x
pm_SOCLIST = $(pmrtos_SOCLIST) tda2xx tda2px tda2ex tda3xx
pm_BOARDLIST = $(pmrtos_BOARDLIST) tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
pm_tda2xx_CORELIST = a15_0 ipu1_0 c66x
pm_tda2px_CORELIST = a15_0 ipu1_0 c66x
pm_am574x_CORELIST = a15_0 ipu1_0 c66x
pm_am572x_CORELIST = a15_0 ipu1_0 c66x
pm_dra72x_CORELIST = a15_0 ipu1_0 c66x
pm_dra75x_CORELIST = a15_0 ipu1_0 c66x
pm_tda2ex_CORELIST = a15_0 ipu1_0 c66x
pm_am571x_CORELIST = a15_0 ipu1_0 c66x
pm_tda3xx_CORELIST = ipu1_0 c66x
pm_dra78x_CORELIST = ipu1_0 c66x

############################
# pm package
# List of components included under pm lib
# The components included here are built and will be part of pm lib
############################
pm_LIB_LIST = pm_hal pm_hal_optimized pm_lib pm_lib_optimized
ifeq ($(BUILD_OS_TYPE),tirtos)
pm_LIB_LIST += pm_rtos
endif

############################
# pm app lib package
# List of components included under pm app lib
# The components included here are built and will be part of pm app lib
############################
pm_APP_LIB_LIST = pm_example_utils

############################
# pm examples
# List of examples under pm (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
pm_EXAMPLE_LIST =

#
# PM Modules
#

# PM HAL
pm_hal_COMP_LIST = pm_hal
pm_hal_RELPATH = ti/drv/pm/src/pmhal
pm_hal_PATH = $(PDK_PM_COMP_PATH)/src/pmhal
pm_hal_LIBNAME = pm_hal
pm_hal_LIBPATH = $(PDK_PM_COMP_PATH)/lib
pm_hal_MAKEFILE = -f$(pm_hal_PATH)/makefile.mk
export pm_hal_LIBNAME
export pm_hal_LIBPATH
export pm_hal_MAKEFILE
pm_hal_BOARD_DEPENDENCY = no
pm_hal_CORE_DEPENDENCY = no
export pm_hal_COMP_LIST
export pm_hal_BOARD_DEPENDENCY
export pm_hal_CORE_DEPENDENCY
pm_hal_PKG_LIST = pm_hal
pm_hal_INCLUDE = $(pm_hal_PATH) $(PDK_PM_COMP_PATH)/include $(PDK_PM_COMP_PATH)/include/prcm
pm_hal_SOCLIST = $(pm_SOCLIST)
export pm_hal_SOCLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda3xx dra75x dra78x am572x am574x))
pm_hal_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST) arp32_1
else
pm_hal_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
endif
export pm_hal_$(SOC)_CORELIST

# PM HAL OPTIMIZED
pm_hal_optimized_COMP_LIST = pm_hal_optimized
pm_hal_optimized_RELPATH = ti/drv/pm/src/pmhal
pm_hal_optimized_PATH = $(PDK_PM_COMP_PATH)/src/pmhal
pm_hal_optimized_LIBNAME = pm_hal_optimized
pm_hal_optimized_LIBPATH = $(PDK_PM_COMP_PATH)/lib
pm_hal_optimized_OBJPATH = $(pm_hal_optimized_RELPATH)/optimized
pm_hal_optimized_MAKEFILE = -f$(pm_hal_optimized_PATH)/makefile_optimized.mk
export pm_hal_optimized_LIBNAME
export pm_hal_optimized_OBJPATH
export pm_hal_optimized_LIBPATH
export pm_hal_optimized_MAKEFILE
pm_hal_optimized_BOARD_DEPENDENCY = no
pm_hal_optimized_CORE_DEPENDENCY = no
export pm_hal_optimized_COMP_LIST
export pm_hal_optimized_BOARD_DEPENDENCY
export pm_hal_optimized_CORE_DEPENDENCY
pm_hal_optimized_PKG_LIST = pm_hal_optimized
pm_hal_optimized_INCLUDE = $(pm_hal_optimized_PATH) $(PDK_PM_COMP_PATH)/include $(PDK_PM_COMP_PATH)/include/prcm
pm_hal_optimized_SOCLIST = $(pm_SOCLIST)
export pm_hal_optimized_SOCLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda3xx dra75x dra78x am572x am574x))
pm_hal_optimized_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST) arp32_1
else
pm_hal_optimized_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
endif
export pm_hal_optimized_$(SOC)_CORELIST

# PM LIB
pm_lib_COMP_LIST = pm_lib
pm_lib_RELPATH = ti/drv/pm/src/pmlib
pm_lib_PATH = $(PDK_PM_COMP_PATH)/src/pmlib
pm_lib_LIBNAME = pm_lib
pm_lib_LIBPATH = $(PDK_PM_COMP_PATH)/lib
pm_lib_MAKEFILE = -f$(pm_lib_PATH)/makefile.mk
export pm_lib_LIBNAME
export pm_lib_LIBPATH
export pm_lib_MAKEFILE
pm_lib_BOARD_DEPENDENCY = no
pm_lib_CORE_DEPENDENCY = no
export pm_lib_COMP_LIST
export pm_lib_BOARD_DEPENDENCY
export pm_lib_CORE_DEPENDENCY
pm_lib_PKG_LIST = pm_lib
pm_lib_INCLUDE = $(pm_lib_PATH) $(PDK_PM_COMP_PATH)/include
pm_lib_SOCLIST = $(pm_SOCLIST)
export pm_lib_SOCLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda3xx am572x am574x))
pm_lib_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST) arp32_1
else
pm_lib_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
endif
export pm_lib_$(SOC)_CORELIST

# PM LIB OPTIMIZED
pm_lib_optimized_COMP_LIST = pm_lib_optimized
pm_lib_optimized_RELPATH = ti/drv/pm/src/pmlib
pm_lib_optimized_PATH = $(PDK_PM_COMP_PATH)/src/pmlib
pm_lib_optimized_LIBNAME = pm_lib_optimized
pm_lib_optimized_LIBPATH = $(PDK_PM_COMP_PATH)/lib
pm_lib_optimized_OBJPATH = $(pm_lib_optimized_RELPATH)/optimized
pm_lib_optimized_MAKEFILE = -f$(pm_lib_optimized_PATH)/makefile_optimized.mk
export pm_lib_optimized_LIBNAME
export pm_lib_optimized_LIBPATH
export pm_lib_optimized_OBJPATH
export pm_lib_optimized_MAKEFILE
pm_lib_optimized_BOARD_DEPENDENCY = no
pm_lib_optimized_CORE_DEPENDENCY = no
export pm_lib_optimized_COMP_LIST
export pm_lib_optimized_BOARD_DEPENDENCY
export pm_lib_optimized_CORE_DEPENDENCY
pm_lib_optimized_PKG_LIST = pm_lib_optimized
pm_lib_optimized_INCLUDE = $(pm_lib_optimized_PATH) $(PDK_PM_COMP_PATH)/include
pm_lib_optimized_SOCLIST = $(pm_SOCLIST)
export pm_lib_optimized_SOCLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda3xx am572x am574x))
pm_lib_optimized_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST) arp32_1
else
pm_lib_optimized_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
endif
export pm_lib_optimized_$(SOC)_CORELIST

# PM RTOS
pm_rtos_COMP_LIST = pm_rtos
pm_rtos_RELPATH = ti/drv/pm
pm_rtos_PATH = $(PDK_PM_COMP_PATH)
pm_rtos_LIBNAME = pm_rtos
pm_rtos_LIBPATH = $(PDK_PM_COMP_PATH)/lib
pm_rtos_MAKEFILE = -fmakefile.mk
export pm_rtos_LIBNAME
export pm_rtos_LIBPATH
export pm_rtos_MAKEFILE
pm_rtos_BOARD_DEPENDENCY = no
pm_rtos_CORE_DEPENDENCY = no
export pm_rtos_COMP_LIST
export pm_rtos_BOARD_DEPENDENCY
export pm_rtos_CORE_DEPENDENCY
pm_rtos_PKG_LIST = pm_rtos
pm_rtos_INCLUDE = $(pm_rtos_PATH) $(PDK_PM_COMP_PATH)/include
pm_rtos_SOCLIST = $(pmrtos_SOCLIST)
export pm_rtos_SOCLIST
pm_rtos_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
export pm_rtos_$(SOC)_CORELIST

# PM Example Utils
pm_example_utils_COMP_LIST = pm_example_utils
pm_example_utils_RELPATH = ti/drv/pm/examples/utils
pm_example_utils_PATH = $(PDK_PM_COMP_PATH)/examples/utils
pm_example_utils_LIBNAME = pm_example_utils
pm_example_utils_LIBPATH = $(PDK_PM_COMP_PATH)/lib
export pm_example_utils_LIBNAME
export pm_example_utils_LIBPATH
pm_example_utils_BOARD_DEPENDENCY = no
pm_example_utils_CORE_DEPENDENCY = no
export pm_example_utils_COMP_LIST
export pm_example_utils_BOARD_DEPENDENCY
export pm_example_utils_CORE_DEPENDENCY
pm_example_utils_PKG_LIST = pm_example_utils
pm_example_utils_INCLUDE = $(pm_example_utils_PATH)
pm_example_utils_SOCLIST = tda2xx tda2px am572x dra72x dra75x tda2ex am571x tda3xx dra78x am574x
export pm_example_utils_SOCLIST
pm_example_utils_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
export pm_example_utils_$(SOC)_CORELIST

#
# PM Examples
#

# PM Systemconfig App
pm_systemconfig_app_COMP_LIST = pm_systemconfig_app
pm_systemconfig_app_RELPATH = ti/drv/pm/examples/systemconfig
pm_systemconfig_app_PATH = $(PDK_PM_COMP_PATH)/examples/systemconfig
pm_systemconfig_app_BOARD_DEPENDENCY = yes
pm_systemconfig_app_CORE_DEPENDENCY = no
pm_systemconfig_app_XDC_CONFIGURO = yes
export pm_systemconfig_app_COMP_LIST
export pm_systemconfig_app_BOARD_DEPENDENCY
export pm_systemconfig_app_CORE_DEPENDENCY
export pm_systemconfig_app_XDC_CONFIGURO
pm_systemconfig_app_PKG_LIST = pm_systemconfig_app
pm_systemconfig_app_INCLUDE =
pm_systemconfig_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA78x tda2xx-rvp
export pm_systemconfig_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), evmDRA78x))
pm_systemconfig_app_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
else
pm_systemconfig_app_tda2xx_CORELIST = a15_0 ipu1_0
pm_systemconfig_app_tda2px_CORELIST = a15_0 ipu1_0
pm_systemconfig_app_tda2ex_CORELIST = a15_0 ipu1_0
pm_systemconfig_app_tda3xx_CORELIST = ipu1_0
endif
export pm_systemconfig_app_$(SOC)_CORELIST
pm_EXAMPLE_LIST += pm_systemconfig_app

# PM arp32 cpu idle test app
pm_arp32_cpuidle_app_COMP_LIST = pm_arp32_cpuidle_app
pm_arp32_cpuidle_app_RELPATH = ti/drv/pm/examples/arp32_cpuidle
pm_arp32_cpuidle_app_PATH = $(PDK_PM_COMP_PATH)/examples/arp32_cpuidle
pm_arp32_cpuidle_app_BOARD_DEPENDENCY = yes
pm_arp32_cpuidle_app_CORE_DEPENDENCY = no
pm_arp32_cpuidle_app_XDC_CONFIGURO = yes
export pm_arp32_cpuidle_app_COMP_LIST
export pm_arp32_cpuidle_app_BOARD_DEPENDENCY
export pm_arp32_cpuidle_app_CORE_DEPENDENCY
export pm_arp32_cpuidle_app_XDC_CONFIGURO
pm_arp32_cpuidle_app_PKG_LIST = pm_arp32_cpuidle_app
pm_arp32_cpuidle_app_INCLUDE =
pm_arp32_cpuidle_app_BOARDLIST = tda2xx-evm tda2px-evm tda3xx-evm tda2xx-rvp
export pm_arp32_cpuidle_app_BOARDLIST
pm_arp32_cpuidle_app_$(SOC)_CORELIST = arp32_1
export pm_arp32_cpuidle_app_$(SOC)_CORELIST
pm_EXAMPLE_LIST += pm_arp32_cpuidle_app

# PM clock rate test App
pm_clkrate_app_COMP_LIST = pm_clkrate_app
pm_clkrate_app_RELPATH = ti/drv/pm/examples/clkrate_manager
pm_clkrate_app_PATH = $(PDK_PM_COMP_PATH)/examples/clkrate_manager
pm_clkrate_app_BOARD_DEPENDENCY = yes
pm_clkrate_app_CORE_DEPENDENCY = no
pm_clkrate_app_XDC_CONFIGURO = yes
export pm_clkrate_app_COMP_LIST
export pm_clkrate_app_BOARD_DEPENDENCY
export pm_clkrate_app_CORE_DEPENDENCY
export pm_clkrate_app_XDC_CONFIGURO
pm_clkrate_app_PKG_LIST = pm_clkrate_app
pm_clkrate_app_INCLUDE =
pm_clkrate_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export pm_clkrate_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda3xx))
pm_clkrate_app_$(SOC)_CORELIST = ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
pm_clkrate_app_$(SOC)_CORELIST = ipu1_0 a15_0
endif
export pm_clkrate_app_$(SOC)_CORELIST
pm_EXAMPLE_LIST += pm_clkrate_app

# PM cpu idle test App
pm_cpuidle_app_COMP_LIST = pm_cpuidle_app
pm_cpuidle_app_RELPATH = ti/drv/pm/examples/cpuidle
pm_cpuidle_app_PATH = $(PDK_PM_COMP_PATH)/examples/cpuidle
pm_cpuidle_app_BOARD_DEPENDENCY = yes
pm_cpuidle_app_CORE_DEPENDENCY = no
pm_cpuidle_app_XDC_CONFIGURO = yes
export pm_cpuidle_app_COMP_LIST
export pm_cpuidle_app_BOARD_DEPENDENCY
export pm_cpuidle_app_CORE_DEPENDENCY
export pm_cpuidle_app_XDC_CONFIGURO
pm_cpuidle_app_PKG_LIST = pm_cpuidle_app
pm_cpuidle_app_INCLUDE =
pm_cpuidle_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export pm_cpuidle_app_BOARDLIST
pm_cpuidle_app_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
export pm_cpuidle_app_$(SOC)_CORELIST
pm_EXAMPLE_LIST += pm_cpuidle_app

# PM junction temperature sensor test App
pm_junction_temp_app_COMP_LIST = pm_junction_temp_app
pm_junction_temp_app_RELPATH = ti/drv/pm/examples/junction_temp_sensor
pm_junction_temp_app_PATH = $(PDK_PM_COMP_PATH)/examples/junction_temp_sensor
pm_junction_temp_app_BOARD_DEPENDENCY = yes
pm_junction_temp_app_CORE_DEPENDENCY = no
pm_junction_temp_app_XDC_CONFIGURO = yes
export pm_junction_temp_app_COMP_LIST
export pm_junction_temp_app_BOARD_DEPENDENCY
export pm_junction_temp_app_CORE_DEPENDENCY
export pm_junction_temp_app_XDC_CONFIGURO
pm_junction_temp_app_PKG_LIST = pm_junction_temp_app
pm_junction_temp_app_INCLUDE =
pm_junction_temp_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pm_junction_temp_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda3xx))
pm_junction_temp_app_$(SOC)_CORELIST = ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
pm_junction_temp_app_$(SOC)_CORELIST = a15_0
endif
export pm_junction_temp_app_$(SOC)_CORELIST
pm_EXAMPLE_LIST += pm_junction_temp_app

# PM ina226 test App
pm_ina226_app_COMP_LIST = pm_ina226_app
pm_ina226_app_RELPATH = ti/drv/pm/examples/ina226_power_measure
pm_ina226_app_PATH = $(PDK_PM_COMP_PATH)/examples/ina226_power_measure
pm_ina226_app_BOARD_DEPENDENCY = yes
pm_ina226_app_CORE_DEPENDENCY = no
pm_ina226_app_XDC_CONFIGURO = yes
export pm_ina226_app_COMP_LIST
export pm_ina226_app_BOARD_DEPENDENCY
export pm_ina226_app_CORE_DEPENDENCY
export pm_ina226_app_XDC_CONFIGURO
pm_ina226_app_PKG_LIST = pm_ina226_app
pm_ina226_app_INCLUDE =
pm_ina226_app_BOARDLIST = tda2xx-evm
export pm_ina226_app_BOARDLIST
pm_ina226_app_$(SOC)_CORELIST = a15_0
export pm_ina226_app_$(SOC)_CORELIST
pm_EXAMPLE_LIST += pm_ina226_app

# A15 Core Loading Software
pm_core_loading_app_COMP_LIST = pm_core_loading_app
pm_core_loading_app_RELPATH = ti/drv/pm/examples/core_loading
pm_core_loading_app_PATH = $(PDK_PM_COMP_PATH)/examples/core_loading
pm_core_loading_app_BOARD_DEPENDENCY = yes
pm_core_loading_app_CORE_DEPENDENCY = no
pm_core_loading_app_XDC_CONFIGURO = yes
pm_core_loading_app_SBL_APPIMAGEGEN = yes
export pm_core_loading_app_SBL_APPIMAGEGEN
export pm_core_loading_app_COMP_LIST
export pm_core_loading_app_BOARD_DEPENDENCY
export pm_core_loading_app_CORE_DEPENDENCY
export pm_core_loading_app_XDC_CONFIGURO
pm_core_loading_app_PKG_LIST = pm_core_loading_app
pm_core_loading_app_INCLUDE = $(pm_core_loading_app_PATH) $(PDK_PM_COMP_PATH)/include
pm_core_loading_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pm_core_loading_app_BOARDLIST
pm_core_loading_app_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
ifeq ($(SOC),$(filter $(SOC), tda2px))
pm_core_loading_app_$(SOC)_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 ipu2_1 c66x c66xdsp_1 c66xdsp_2 arp32_1 arp32_2
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx))
pm_core_loading_app_$(SOC)_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 ipu2_1 c66x c66xdsp_1 c66xdsp_2 arp32_1 arp32_2 arp32_3 arp32_4
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
pm_core_loading_app_$(SOC)_CORELIST = ipu1_0 ipu1_1 c66x c66xdsp_1 c66xdsp_2 arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
pm_core_loading_app_$(SOC)_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 ipu2_1 c66x c66xdsp_1
endif
export pm_core_loading_app_$(SOC)_CORELIST
ifeq ($(BUILD_OS_TYPE),tirtos)
pm_EXAMPLE_LIST += pm_core_loading_app
endif

# PM RTOS App
pm_rtos_app_COMP_LIST = pm_rtos_app
pm_rtos_app_RELPATH = ti/drv/pm/examples/pmrtos
pm_rtos_app_PATH = $(PDK_PM_COMP_PATH)/examples/pmrtos
pm_rtos_app_BOARD_DEPENDENCY = yes
pm_rtos_app_CORE_DEPENDENCY = no
pm_rtos_app_XDC_CONFIGURO = yes
export pm_rtos_app_COMP_LIST
export pm_rtos_app_BOARD_DEPENDENCY
export pm_rtos_app_CORE_DEPENDENCY
export pm_rtos_app_XDC_CONFIGURO
pm_rtos_app_PKG_LIST = pm_rtos_app
pm_rtos_app_INCLUDE = $(pm_rtos_app_PATH) $(PDK_PM_COMP_PATH)/include
pm_rtos_app_BOARDLIST = evmAM572x
export pm_rtos_app_BOARDLIST
pm_rtos_app_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
pm_rtos_app_$(SOC)_CORELIST = ipu1_0
endif
export pm_rtos_app_$(SOC)_CORELIST
ifeq ($(BUILD_OS_TYPE),tirtos)
pm_EXAMPLE_LIST += pm_rtos_app
endif


# PM RTOS Thermal App
pm_rtos_thermal_app_COMP_LIST = pm_rtos_thermal_app
pm_rtos_thermal_app_RELPATH = ti/drv/pm/examples/pmrtos_thermal
pm_rtos_thermal_app_PATH = $(PDK_PM_COMP_PATH)/examples/pmrtos_thermal
pm_rtos_thermal_app_BOARD_DEPENDENCY = yes
pm_rtos_thermal_app_CORE_DEPENDENCY = no
pm_rtos_thermal_app_XDC_CONFIGURO = yes
pm_rtos_thermal_app_FP_DEPENDENCY = yes
export pm_rtos_thermal_app_COMP_LIST
export pm_rtos_thermal_app_BOARD_DEPENDENCY
export pm_rtos_thermal_app_CORE_DEPENDENCY
export pm_rtos_thermal_app_XDC_CONFIGURO
export pm_rtos_thermal_app_FP_DEPENDENCY
pm_rtos_thermal_app_PKG_LIST = pm_rtos_thermal_app
pm_rtos_thermal_app_INCLUDE = $(pm_rtos_thermal_app_PATH) $(PDK_PM_COMP_PATH)/include
pm_rtos_thermal_app_BOARDLIST = evmAM572x
export pm_rtos_thermal_app_BOARDLIST
pm_rtos_thermal_app_$(SOC)_CORELIST = $(pm_$(SOC)_CORELIST)

export pm_rtos_thermal_app_$(SOC)_CORELIST
ifeq ($(BUILD_OS_TYPE),tirtos)
pm_EXAMPLE_LIST += pm_rtos_thermal_app
endif

export pm_LIB_LIST
export pm_EXAMPLE_LIST

PM_CFLAGS =

export PM_CFLAGS

pm_component_make_include := 1
endif
