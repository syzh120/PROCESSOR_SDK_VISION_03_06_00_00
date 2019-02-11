# File: vps_component.mk
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
ifeq ($(vps_component_make_include), )

vps_SOCLIST = tda2xx tda2px am572x dra75x tda2ex am571x dra72x tda3xx dra78x am574x
vps_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA75x evmAM572x idkAM572x idkAM571x tda2xx-rvp idkAM574x
#Doesn't include DRA boards as they are not yet enabled
vps_default_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmAM572x idkAM572x idkAM571x tda2xx-rvp idkAM574x
#TDA2xx and TDA2Ex + AM family
vps_tda2xx_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm evmAM572x idkAM572x idkAM571x tda2xx-rvp idkAM574x
#TDA3xx family
vps_tda3xx_BOARDLIST = tda3xx-evm
vps_tda2xx_CORELIST = ipu1_0
vps_tda2px_CORELIST = ipu1_0
vps_am572x_CORELIST = ipu1_0 a15_0 c66x
vps_dra75x_CORELIST = a15_0
vps_tda2ex_CORELIST = ipu1_0
vps_am571x_CORELIST = ipu1_0 a15_0 c66x
vps_dra72x_CORELIST = a15_0
vps_tda3xx_CORELIST = ipu1_0
vps_dra78x_CORELIST = ipu1_0
vps_am574x_CORELIST = ipu1_0 a15_0 c66x
vps_osal_baremetal_default_tda2xx_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 c66xdsp_1 c66xdsp_2
vps_osal_baremetal_default_tda2px_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 c66xdsp_1 c66xdsp_2
vps_osal_baremetal_default_tda2ex_CORELIST = a15_0 ipu1_0 ipu1_1 c66xdsp_1
vps_osal_baremetal_default_tda3xx_CORELIST = ipu1_0 ipu1_1 c66xdsp_1 c66xdsp_2
vps_osal_baremetal_default_am574x_CORELIST = ipu1_0 a15_0 c66x
vps_osal_baremetal_default_am572x_CORELIST = ipu1_0 a15_0 c66x
vps_osal_baremetal_default_am571x_CORELIST = ipu1_0 a15_0 c66x
vps_osal_baremetal_default_dra72x_CORELIST = a15_0 ipu1_0 ipu1_1 c66xdsp_1
vps_osal_baremetal_default_dra75x_CORELIST = a15_0 ipu1_0 ipu1_1 c66xdsp_1
vps_osal_baremetal_default_dra78x_CORELIST = ipu1_0 ipu1_1 c66xdsp_1 c66xdsp_2

############################
# vps package
# List of components included under vps lib
# The components included here are built and will be part of vps lib
############################
ifeq ($(SOC),$(filter $(SOC), am574x am572x am571x))
vps_LIB_LIST = vps_examples_utility_baremetal vps_osal_baremetal
else
vps_LIB_LIST = vps_osal_baremetal
endif

# DRA7xx devices only enable vps_osal_baremetal library build
ifneq ($(SOC),$(filter $(SOC), dra72x dra75x dra78x))
  vps_LIB_LIST += vps_common vpslib vpsdrv_baremetal
  ifneq ($(BUILD_OS_TYPE), baremetal)
    vps_LIB_LIST += fvid2 vps_osal_tirtos vps_osal_tirtos_smp vpsdrv vps_platforms vps_devices vps_boards vps_examples_utility
  endif
endif
############################
# vps examples
# List of examples under vps (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
vps_EXAMPLE_LIST =

#
# VPS Modules
#

# FVID2
fvid2_COMP_LIST = fvid2
fvid2_RELPATH = ti/drv/vps/src/fvid2
fvid2_PATH = $(PDK_VPS_COMP_PATH)/src/fvid2
fvid2_LIBNAME = fvid2
fvid2_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export fvid2_LIBNAME
export fvid2_LIBPATH
fvid2_BOARD_DEPENDENCY = no
fvid2_CORE_DEPENDENCY = no
export fvid2_COMP_LIST
export fvid2_BOARD_DEPENDENCY
export fvid2_CORE_DEPENDENCY
fvid2_PKG_LIST = fvid2
fvid2_INCLUDE = $(fvid2_PATH)
fvid2_SOCLIST = $(vps_SOCLIST)
export fvid2_SOCLIST
fvid2_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export fvid2_$(SOC)_CORELIST

# VPS COMMON
vps_common_COMP_LIST = vps_common
vps_common_RELPATH = ti/drv/vps/src/common
vps_common_PATH = $(PDK_VPS_COMP_PATH)/src/common
vps_common_LIBNAME = vps_common
vps_common_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_common_LIBNAME
export vps_common_LIBPATH
vps_common_BOARD_DEPENDENCY = no
vps_common_CORE_DEPENDENCY = no
export vps_common_COMP_LIST
export vps_common_BOARD_DEPENDENCY
export vps_common_CORE_DEPENDENCY
vps_common_PKG_LIST = vps_common
vps_common_INCLUDE = $(vps_common_PATH)
vps_common_SOCLIST = $(vps_SOCLIST)
export vps_common_SOCLIST
vps_common_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_common_$(SOC)_CORELIST

# TI RTOS VPS OSAL
vps_osal_tirtos_COMP_LIST = vps_osal_tirtos
vps_osal_tirtos_RELPATH = ti/drv/vps/src/osal/tirtos
vps_osal_tirtos_PATH = $(PDK_VPS_COMP_PATH)/src/osal/tirtos
vps_osal_tirtos_LIBNAME = vps_osal_tirtos
vps_osal_tirtos_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_osal_tirtos_LIBNAME
export vps_osal_tirtos_LIBPATH
vps_osal_tirtos_BOARD_DEPENDENCY = no
vps_osal_tirtos_CORE_DEPENDENCY = no
export vps_osal_tirtos_COMP_LIST
export vps_osal_tirtos_BOARD_DEPENDENCY
export vps_osal_tirtos_CORE_DEPENDENCY
vps_osal_tirtos_PKG_LIST = vps_osal_tirtos
vps_osal_tirtos_INCLUDE = $(vps_osal_tirtos_PATH)
vps_osal_tirtos_SOCLIST = $(vps_SOCLIST)
export vps_osal_tirtos_SOCLIST
vps_osal_tirtos_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
vps_osal_tirtos_$(SOC)_CORELIST += a15_0
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda3xx))
vps_osal_tirtos_$(SOC)_CORELIST += c66x arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
vps_osal_tirtos_$(SOC)_CORELIST += c66x
endif
export vps_osal_tirtos_$(SOC)_CORELIST

# TI RTOS VPS SMP OSAL
vps_osal_tirtos_smp_COMP_LIST = vps_osal_tirtos_smp
vps_osal_tirtos_smp_RELPATH = ti/drv/vps/src/osal/tirtos/smp
vps_osal_tirtos_smp_PATH = $(PDK_VPS_COMP_PATH)/src/osal/tirtos/smp
vps_osal_tirtos_smp_LIBNAME = vps_osal_tirtos_smp
vps_osal_tirtos_smp_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_osal_tirtos_smp_LIBNAME
export vps_osal_tirtos_smp_LIBPATH
vps_osal_tirtos_smp_BOARD_DEPENDENCY = no
vps_osal_tirtos_smp_CORE_DEPENDENCY = no
export vps_osal_tirtos_smp_COMP_LIST
export vps_osal_tirtos_smp_BOARD_DEPENDENCY
export vps_osal_tirtos_smp_CORE_DEPENDENCY
vps_osal_tirtos_smp_PKG_LIST = vps_osal_tirtos_smp
vps_osal_tirtos_smp_INCLUDE = $(vps_osal_tirtos_smp_PATH)
vps_osal_tirtos_smp_SOCLIST = tda2xx tda2px tda2ex
export vps_osal_tirtos_smp_SOCLIST
vps_osal_tirtos_smp_$(SOC)_CORELIST = a15_0
export vps_osal_tirtos_smp_$(SOC)_CORELIST

# Baremetal VPS OSAL
vps_osal_baremetal_COMP_LIST = vps_osal_baremetal
vps_osal_baremetal_RELPATH = ti/drv/vps/src/osal/baremetal
vps_osal_baremetal_PATH = $(PDK_VPS_COMP_PATH)/src/osal/baremetal
vps_osal_baremetal_LIBNAME = vps_osal_baremetal
vps_osal_baremetal_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_osal_baremetal_LIBNAME
export vps_osal_baremetal_LIBPATH
vps_osal_baremetal_BOARD_DEPENDENCY = no
vps_osal_baremetal_CORE_DEPENDENCY = yes
export vps_osal_baremetal_COMP_LIST
export vps_osal_baremetal_BOARD_DEPENDENCY
export vps_osal_baremetal_CORE_DEPENDENCY
vps_osal_baremetal_PKG_LIST = vps_osal_baremetal
vps_osal_baremetal_INCLUDE = $(vps_osal_baremetal_PATH)
vps_osal_baremetal_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x am571x am572x am574x
export vps_osal_baremetal_SOCLIST
vps_osal_baremetal_$(SOC)_CORELIST = $(vps_osal_baremetal_default_$(SOC)_CORELIST)
export vps_osal_baremetal_$(SOC)_CORELIST

# VPS LIB
vpslib_COMP_LIST = vpslib
vpslib_RELPATH = ti/drv/vps/src/vpslib
vpslib_PATH = $(PDK_VPS_COMP_PATH)/src/vpslib
vpslib_LIBNAME = vpslib
vpslib_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vpslib_LIBNAME
export vpslib_LIBPATH
vpslib_BOARD_DEPENDENCY = no
vpslib_CORE_DEPENDENCY = no
export vpslib_COMP_LIST
export vpslib_BOARD_DEPENDENCY
export vpslib_CORE_DEPENDENCY
vpslib_PKG_LIST = vpslib
vpslib_INCLUDE = $(vpslib_PATH)
vpslib_SOCLIST = $(vps_SOCLIST)
export vpslib_SOCLIST
vpslib_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vpslib_$(SOC)_CORELIST

# VPS DRV
vpsdrv_COMP_LIST = vpsdrv
vpsdrv_RELPATH = ti/drv/vps/src/vpsdrv
vpsdrv_PATH = $(PDK_VPS_COMP_PATH)/src/vpsdrv
vpsdrv_LIBNAME = vpsdrv
vpsdrv_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vpsdrv_LIBNAME
export vpsdrv_LIBPATH
vpsdrv_BOARD_DEPENDENCY = no
vpsdrv_CORE_DEPENDENCY = no
export vpsdrv_COMP_LIST
export vpsdrv_BOARD_DEPENDENCY
export vpsdrv_CORE_DEPENDENCY
vpsdrv_PKG_LIST = vpsdrv
vpsdrv_INCLUDE = $(vpsdrv_PATH)
vpsdrv_SOCLIST = $(vps_SOCLIST)
export vpsdrv_SOCLIST
vpsdrv_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vpsdrv_$(SOC)_CORELIST

# VPS DRV - Baremetal
vpsdrv_baremetal_COMP_LIST = vpsdrv_baremetal
vpsdrv_baremetal_RELPATH = ti/drv/vps/src/vpslib/drv
vpsdrv_baremetal_PATH = $(PDK_VPS_COMP_PATH)/src/vpslib/drv
vpsdrv_baremetal_LIBNAME = vpsdrv_baremetal
vpsdrv_baremetal_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vpsdrv_baremetal_LIBNAME
export vpsdrv_baremetal_LIBPATH
vpsdrv_baremetal_BOARD_DEPENDENCY = no
vpsdrv_baremetal_CORE_DEPENDENCY = no
export vpsdrv_baremetal_COMP_LIST
export vpsdrv_baremetal_BOARD_DEPENDENCY
export vpsdrv_baremetal_CORE_DEPENDENCY
vpsdrv_baremetal_PKG_LIST = vpsdrv_baremetal
vpsdrv_baremetal_INCLUDE = $(vpsdrv_baremetal_PATH)
vpsdrv_baremetal_SOCLIST = tda2xx tda2px dra75x tda2ex dra72x tda3xx dra78x
export vpsdrv_baremetal_SOCLIST
vpsdrv_baremetal_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vpsdrv_baremetal_$(SOC)_CORELIST

# VPS Platforms
vps_platforms_COMP_LIST = vps_platforms
vps_platforms_RELPATH = ti/drv/vps/src/platforms
vps_platforms_PATH = $(PDK_VPS_COMP_PATH)/src/platforms
vps_platforms_LIBNAME = vps_platforms
vps_platforms_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_platforms_LIBNAME
export vps_platforms_LIBPATH
vps_platforms_BOARD_DEPENDENCY = no
vps_platforms_CORE_DEPENDENCY = no
export vps_platforms_COMP_LIST
export vps_platforms_BOARD_DEPENDENCY
export vps_platforms_CORE_DEPENDENCY
vps_platforms_PKG_LIST = vps_platforms
vps_platforms_INCLUDE = $(vps_platforms_PATH)
vps_platforms_SOCLIST = $(vps_SOCLIST)
export vps_platforms_SOCLIST
vps_platforms_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_platforms_$(SOC)_CORELIST

# VPS Devices
vps_devices_COMP_LIST = vps_devices
vps_devices_RELPATH = ti/drv/vps/src/devices
vps_devices_PATH = $(PDK_VPS_COMP_PATH)/src/devices
vps_devices_LIBNAME = vps_devices
vps_devices_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_devices_LIBNAME
export vps_devices_LIBPATH
vps_devices_BOARD_DEPENDENCY = no
vps_devices_CORE_DEPENDENCY = no
export vps_devices_COMP_LIST
export vps_devices_BOARD_DEPENDENCY
export vps_devices_CORE_DEPENDENCY
vps_devices_PKG_LIST = vps_devices
vps_devices_INCLUDE = $(vps_devices_PATH)
vps_devices_SOCLIST = $(vps_SOCLIST)
export vps_devices_SOCLIST
vps_devices_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_devices_$(SOC)_CORELIST

# VPS Boards
vps_boards_COMP_LIST = vps_boards
vps_boards_RELPATH = ti/drv/vps/src/boards
vps_boards_PATH = $(PDK_VPS_COMP_PATH)/src/boards
vps_boards_LIBNAME = vps_boards
vps_boards_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_boards_LIBNAME
export vps_boards_LIBPATH
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
vps_boards_BOARD_DEPENDENCY = yes
else
vps_boards_BOARD_DEPENDENCY = no
endif
vps_boards_CORE_DEPENDENCY = no
export vps_boards_COMP_LIST
export vps_boards_BOARD_DEPENDENCY
export vps_boards_CORE_DEPENDENCY
vps_boards_PKG_LIST = vps_boards
vps_boards_INCLUDE = $(vps_boards_PATH)
vps_boards_SOCLIST = $(vps_SOCLIST)
export vps_boards_SOCLIST
vps_boards_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_boards_$(SOC)_CORELIST

# VPS Example utility
vps_examples_utility_COMP_LIST = vps_examples_utility
vps_examples_utility_RELPATH = ti/drv/vps/examples/utility
vps_examples_utility_PATH = $(PDK_VPS_COMP_PATH)/examples/utility
vps_examples_utility_LIBNAME = vps_examples_utility
vps_examples_utility_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
export vps_examples_utility_LIBNAME
export vps_examples_utility_LIBPATH
ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
vps_examples_utility_BOARD_DEPENDENCY = yes
else
vps_examples_utility_BOARD_DEPENDENCY = no
endif
vps_examples_utility_CORE_DEPENDENCY = no
export vps_examples_utility_COMP_LIST
export vps_examples_utility_BOARD_DEPENDENCY
export vps_examples_utility_CORE_DEPENDENCY
vps_examples_utility_PKG_LIST = vps_examples_utility
vps_examples_utility_INCLUDE = $(vps_examples_utility_PATH)
vps_examples_utility_SOCLIST = $(vps_SOCLIST)
export vps_examples_utility_SOCLIST
vps_examples_utility_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_utility_$(SOC)_CORELIST

# VPS Example utility - Baremetal
vps_examples_utility_baremetal_COMP_LIST = vps_examples_utility_baremetal
vps_examples_utility_baremetal_RELPATH = ti/drv/vps/examples/utility/
vps_examples_utility_baremetal_OBJPATH = ti/drv/vps/examples/utility/baremetal
vps_examples_utility_baremetal_PATH = $(PDK_VPS_COMP_PATH)/examples/utility
vps_examples_utility_baremetal_LIBNAME = vps_examples_utility_baremetal
vps_examples_utility_baremetal_LIBPATH = $(PDK_VPS_COMP_PATH)/lib
vps_examples_utility_baremetal_MAKEFILE = -fmakefile_baremetal.mk
export vps_examples_utility_baremetal_MAKEFILE
export vps_examples_utility_baremetal_LIBNAME
export vps_examples_utility_baremetal_LIBPATH
export vps_examples_utility_baremetal_OBJPATH
vps_examples_utility_baremetal_BOARD_DEPENDENCY = no
vps_examples_utility_baremetal_CORE_DEPENDENCY = no
export vps_examples_utility_baremetal_COMP_LIST
export vps_examples_utility_baremetal_BOARD_DEPENDENCY
export vps_examples_utility_baremetal_CORE_DEPENDENCY
vps_examples_utility_baremetal_PKG_LIST = vps_examples_utility_baremetal
vps_examples_utility_baremetal_INCLUDE = $(vps_examples_utility_baremetal_PATH)
vps_examples_utility_baremetal_SOCLIST = am571x am572x am574x
export vps_examples_utility_baremetal_SOCLIST
vps_examples_utility_baremetal_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_nonos_utility_$(SOC)_CORELIST

#
# VPS Bare metal Examples
#
# DSS baremetal test app
vps_examples_dss_baremetal_COMP_LIST = vps_examples_dss_baremetal
vps_examples_dss_baremetal_RELPATH = ti/drv/vps/examples/dss/dss_baremetal_app
vps_examples_dss_baremetal_PATH = $(PDK_VPS_COMP_PATH)/examples/dss/dss_baremetal_app
vps_examples_dss_baremetal_BOARD_DEPENDENCY = yes
vps_examples_dss_baremetal_CORE_DEPENDENCY = yes
export vps_examples_dss_baremetal_COMP_LIST
export vps_examples_dss_baremetal_BOARD_DEPENDENCY
export vps_examples_dss_baremetal_CORE_DEPENDENCY
vps_examples_dss_baremetal_PKG_LIST = vps_examples_dss_baremetal
vps_examples_dss_baremetal_INCLUDE = $(vps_examples_dss_baremetal_PATH)
vps_examples_dss_baremetal_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export vps_examples_dss_baremetal_BOARDLIST
vps_examples_dss_baremetal_$(SOC)_CORELIST = ipu1_0
export vps_examples_dss_baremetal_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_dss_baremetal
vps_examples_dss_baremetal_SBL_APPIMAGEGEN = yes
export vps_examples_dss_baremetal_SBL_APPIMAGEGEN

# DisplayDSS baremetal test app for AM57x boards
vps_examples_DisplayDssBareMetal_COMP_LIST = vps_examples_DisplayDssBareMetal
vps_examples_DisplayDssBareMetal_RELPATH = ti/drv/vps/examples/dss/displayDssBareMetal
vps_examples_DisplayDssBareMetal_PATH = $(PDK_VPS_COMP_PATH)/examples/dss/displayDssBareMetal
vps_examples_DisplayDssBareMetal_BOARD_DEPENDENCY = yes
vps_examples_DisplayDssBareMetal_CORE_DEPENDENCY = yes
export vps_examples_DisplayDssBareMetal_COMP_LIST
export vps_examples_DisplayDssBareMetal_BOARD_DEPENDENCY
export vps_examples_DisplayDssBareMetal_CORE_DEPENDENCY
vps_examples_DisplayDssBareMetal_PKG_LIST = vps_examples_DisplayDssBareMetal
vps_examples_DisplayDssBareMetal_INCLUDE = $(vps_examples_DisplayDssBareMetal_PATH)
vps_examples_DisplayDssBareMetal_BOARDLIST = idkAM572x idkAM571x evmAM572x idkAM574x
export vps_examples_DisplayDssBareMetal_BOARDLIST
vps_examples_DisplayDssBareMetal_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_DisplayDssBareMetal_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_DisplayDssBareMetal
vps_examples_DisplayDssBareMetal_SBL_APPIMAGEGEN = no
export vps_examples_DisplayDssBareMetal_SBL_APPIMAGEGEN

# Video loopback baremetal test app
vps_examples_loopback_baremetal_COMP_LIST = vps_examples_loopback_baremetal
vps_examples_loopback_baremetal_RELPATH = ti/drv/vps/examples/loopback_baremetal_app
vps_examples_loopback_baremetal_PATH = $(PDK_VPS_COMP_PATH)/examples/loopback_baremetal_app
vps_examples_loopback_baremetal_BOARD_DEPENDENCY = yes
vps_examples_loopback_baremetal_CORE_DEPENDENCY = yes
export vps_examples_loopback_baremetal_COMP_LIST
export vps_examples_loopback_baremetal_BOARD_DEPENDENCY
export vps_examples_loopback_baremetal_CORE_DEPENDENCY
vps_examples_loopback_baremetal_PKG_LIST = vps_examples_loopback_baremetal
vps_examples_loopback_baremetal_INCLUDE = $(vps_examples_loopback_baremetal_PATH)
vps_examples_loopback_baremetal_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export vps_examples_loopback_baremetal_BOARDLIST
vps_examples_loopback_baremetal_$(SOC)_CORELIST = ipu1_0
export vps_examples_loopback_baremetal_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_loopback_baremetal
vps_examples_loopback_baremetal_SBL_APPIMAGEGEN = yes
export vps_examples_loopback_baremetal_SBL_APPIMAGEGEN

# Video loopback baremetal test app for AM parts
vps_examples_loopbackBareMetal_COMP_LIST = vps_examples_loopbackBareMetal
vps_examples_loopbackBareMetal_RELPATH = ti/drv/vps/examples/loopbackBareMetal
vps_examples_loopbackBareMetal_PATH = $(PDK_VPS_COMP_PATH)/examples/loopbackBareMetal
vps_examples_loopbackBareMetal_BOARD_DEPENDENCY = yes
vps_examples_loopbackBareMetal_CORE_DEPENDENCY = yes
export vps_examples_loopbackBareMetal_COMP_LIST
export vps_examples_loopbackBareMetal_BOARD_DEPENDENCY
export vps_examples_loopbackBareMetal_CORE_DEPENDENCY
vps_examples_loopbackBareMetal_PKG_LIST = vps_examples_loopbackBareMetal
vps_examples_loopbackBareMetal_INCLUDE = $(vps_examples_loopbackBareMetal_PATH)
vps_examples_loopbackBareMetal_BOARDLIST = idkAM572x idkAM571x evmAM572x idkAM574x
vps_examples_loopbackBareMetal_SBL_APPIMAGEGEN = no
vps_examples_loopbackBareMetal_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_loopbackBareMetal_BOARDLIST
export vps_examples_loopbackBareMetal_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_loopbackBareMetal
export vps_examples_loopbackBareMetal_SBL_APPIMAGEGEN

# ISS Capture baremetal test app
vps_examples_isscapt_baremetal_COMP_LIST = vps_examples_isscapt_baremetal
vps_examples_isscapt_baremetal_RELPATH = ti/drv/vps/examples/iss/isscapt_baremetal_app
vps_examples_isscapt_baremetal_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/isscapt_baremetal_app
vps_examples_isscapt_baremetal_BOARD_DEPENDENCY = yes
vps_examples_isscapt_baremetal_CORE_DEPENDENCY = yes
export vps_examples_isscapt_baremetal_COMP_LIST
export vps_examples_isscapt_baremetal_BOARD_DEPENDENCY
export vps_examples_isscapt_baremetal_CORE_DEPENDENCY
vps_examples_isscapt_baremetal_PKG_LIST = vps_examples_isscapt_baremetal
vps_examples_isscapt_baremetal_INCLUDE = $(vps_examples_isscapt_baremetal_PATH)
vps_examples_isscapt_baremetal_BOARDLIST = tda3xx-evm
export vps_examples_isscapt_baremetal_BOARDLIST
vps_examples_isscapt_baremetal_tda3xx_CORELIST = ipu1_0
export vps_examples_isscapt_baremetal_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_isscapt_baremetal
vps_examples_isscapt_baremetal_SBL_APPIMAGEGEN = yes
export vps_examples_isscapt_baremetal_SBL_APPIMAGEGEN

#
# VPS Examples
#
# DSS Example
vps_examples_displayDss_COMP_LIST = vps_examples_displayDss
vps_examples_displayDss_RELPATH = ti/drv/vps/examples/dss/displayDss
vps_examples_displayDss_PATH = $(PDK_VPS_COMP_PATH)/examples/dss/displayDss
vps_examples_displayDss_BOARD_DEPENDENCY = yes
vps_examples_displayDss_CORE_DEPENDENCY = no
vps_examples_displayDss_XDC_CONFIGURO = yes
export vps_examples_displayDss_COMP_LIST
export vps_examples_displayDss_BOARD_DEPENDENCY
export vps_examples_displayDss_CORE_DEPENDENCY
export vps_examples_displayDss_XDC_CONFIGURO
vps_examples_displayDss_PKG_LIST = vps_examples_displayDss
vps_examples_displayDss_INCLUDE = $(vps_examples_displayDss_PATH)
vps_examples_displayDss_BOARDLIST = $(vps_default_BOARDLIST)
export vps_examples_displayDss_BOARDLIST
vps_examples_displayDss_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_displayDss_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_displayDss
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_displayDss_SBL_APPIMAGEGEN = yes
  export vps_examples_displayDss_SBL_APPIMAGEGEN
endif

# DSS Example for low latency display test
vps_examples_displayDssLowLatency_COMP_LIST = vps_examples_displayDssLowLatency
vps_examples_displayDssLowLatency_RELPATH = ti/drv/vps/examples/dss/displayDssLowLatency
vps_examples_displayDssLowLatency_PATH = $(PDK_VPS_COMP_PATH)/examples/dss/displayDssLowLatency
vps_examples_displayDssLowLatency_BOARD_DEPENDENCY = yes
vps_examples_displayDssLowLatency_CORE_DEPENDENCY = no
vps_examples_displayDssLowLatency_XDC_CONFIGURO = yes
export vps_examples_displayDssLowLatency_COMP_LIST
export vps_examples_displayDssLowLatency_BOARD_DEPENDENCY
export vps_examples_displayDssLowLatency_CORE_DEPENDENCY
export vps_examples_displayDssLowLatency_XDC_CONFIGURO
vps_examples_displayDssLowLatency_PKG_LIST = vps_examples_displayDssLowLatency
vps_examples_displayDssLowLatency_INCLUDE = $(vps_examples_displayDssLowLatency_PATH)
vps_examples_displayDssLowLatency_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export vps_examples_displayDssLowLatency_BOARDLIST
vps_examples_displayDssLowLatency_$(SOC)_CORELIST = ipu1_0
export vps_examples_displayDssLowLatency_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_displayDssLowLatency
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_displayDssLowLatency_SBL_APPIMAGEGEN = yes
  export vps_examples_displayDssLowLatency_SBL_APPIMAGEGEN
endif

# DSS WB Example
vps_examples_displayDssWb_COMP_LIST = vps_examples_displayDssWb
vps_examples_displayDssWb_RELPATH = ti/drv/vps/examples/dss/displayDssWb
vps_examples_displayDssWb_PATH = $(PDK_VPS_COMP_PATH)/examples/dss/displayDssWb
vps_examples_displayDssWb_BOARD_DEPENDENCY = yes
vps_examples_displayDssWb_CORE_DEPENDENCY = no
vps_examples_displayDssWb_XDC_CONFIGURO = yes
export vps_examples_displayDssWb_COMP_LIST
export vps_examples_displayDssWb_BOARD_DEPENDENCY
export vps_examples_displayDssWb_CORE_DEPENDENCY
export vps_examples_displayDssWb_XDC_CONFIGURO
vps_examples_displayDssWb_PKG_LIST = vps_examples_displayDssWb
vps_examples_displayDssWb_INCLUDE = $(vps_examples_displayDssWb_PATH)
vps_examples_displayDssWb_BOARDLIST = $(vps_default_BOARDLIST)
export vps_examples_displayDssWb_BOARDLIST
vps_examples_displayDssWb_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_displayDssWb_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_displayDssWb
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_displayDssWb_SBL_APPIMAGEGEN = yes
  export vps_examples_displayDssWb_SBL_APPIMAGEGEN
endif

# DSS M2M WB Example
vps_examples_m2mDssWb_COMP_LIST = vps_examples_m2mDssWb
vps_examples_m2mDssWb_RELPATH = ti/drv/vps/examples/dss/m2mDssWb
vps_examples_m2mDssWb_PATH = $(PDK_VPS_COMP_PATH)/examples/dss/m2mDssWb
vps_examples_m2mDssWb_BOARD_DEPENDENCY = yes
vps_examples_m2mDssWb_CORE_DEPENDENCY = no
vps_examples_m2mDssWb_XDC_CONFIGURO = yes
export vps_examples_m2mDssWb_COMP_LIST
export vps_examples_m2mDssWb_BOARD_DEPENDENCY
export vps_examples_m2mDssWb_CORE_DEPENDENCY
export vps_examples_m2mDssWb_XDC_CONFIGURO
vps_examples_m2mDssWb_PKG_LIST = vps_examples_m2mDssWb
vps_examples_m2mDssWb_INCLUDE = $(vps_examples_m2mDssWb_PATH)
vps_examples_m2mDssWb_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export vps_examples_m2mDssWb_BOARDLIST
vps_examples_m2mDssWb_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_m2mDssWb_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_m2mDssWb
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_m2mDssWb_SBL_APPIMAGEGEN = yes
  export vps_examples_m2mDssWb_SBL_APPIMAGEGEN
endif

# ISS Capture Example
vps_examples_captureIss_COMP_LIST = vps_examples_captureIss
vps_examples_captureIss_RELPATH = ti/drv/vps/examples/iss/captureIss
vps_examples_captureIss_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/captureIss
vps_examples_captureIss_BOARD_DEPENDENCY = yes
vps_examples_captureIss_CORE_DEPENDENCY = no
vps_examples_captureIss_XDC_CONFIGURO = yes
export vps_examples_captureIss_COMP_LIST
export vps_examples_captureIss_BOARD_DEPENDENCY
export vps_examples_captureIss_CORE_DEPENDENCY
export vps_examples_captureIss_XDC_CONFIGURO
vps_examples_captureIss_PKG_LIST = vps_examples_captureIss
vps_examples_captureIss_INCLUDE = $(vps_examples_captureIss_PATH)
vps_examples_captureIss_BOARDLIST = $(vps_tda3xx_BOARDLIST) tda2ex-evm tda2px-evm
export vps_examples_captureIss_BOARDLIST
vps_examples_captureIss_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_captureIss_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_captureIss
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_captureIss_SBL_APPIMAGEGEN = yes
  export vps_examples_captureIss_SBL_APPIMAGEGEN
endif

# ISS Capture OTF Example
vps_examples_captureIssOtf_COMP_LIST = vps_examples_captureIssOtf
vps_examples_captureIssOtf_RELPATH = ti/drv/vps/examples/iss/captureIssOtf
vps_examples_captureIssOtf_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/captureIssOtf
vps_examples_captureIssOtf_BOARD_DEPENDENCY = yes
vps_examples_captureIssOtf_CORE_DEPENDENCY = no
vps_examples_captureIssOtf_XDC_CONFIGURO = yes
export vps_examples_captureIssOtf_COMP_LIST
export vps_examples_captureIssOtf_BOARD_DEPENDENCY
export vps_examples_captureIssOtf_CORE_DEPENDENCY
export vps_examples_captureIssOtf_XDC_CONFIGURO
vps_examples_captureIssOtf_PKG_LIST = vps_examples_captureIssOtf
vps_examples_captureIssOtf_INCLUDE = $(vps_examples_captureIssOtf_PATH)
vps_examples_captureIssOtf_BOARDLIST = $(vps_tda3xx_BOARDLIST)
export vps_examples_captureIssOtf_BOARDLIST
vps_examples_captureIssOtf_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_captureIssOtf_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_captureIssOtf
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_captureIssOtf_SBL_APPIMAGEGEN = yes
  export vps_examples_captureIssOtf_SBL_APPIMAGEGEN
endif

# ISS Loopback Example
vps_examples_issLoopback_COMP_LIST = vps_examples_issLoopback
vps_examples_issLoopback_RELPATH = ti/drv/vps/examples/iss/loopback
vps_examples_issLoopback_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/loopback
vps_examples_issLoopback_BOARD_DEPENDENCY = yes
vps_examples_issLoopback_CORE_DEPENDENCY = no
vps_examples_issLoopback_XDC_CONFIGURO = yes
export vps_examples_issLoopback_COMP_LIST
export vps_examples_issLoopback_BOARD_DEPENDENCY
export vps_examples_issLoopback_CORE_DEPENDENCY
export vps_examples_issLoopback_XDC_CONFIGURO
vps_examples_issLoopback_PKG_LIST = vps_examples_issLoopback
vps_examples_issLoopback_INCLUDE = $(vps_examples_issLoopback_PATH)
vps_examples_issLoopback_BOARDLIST = $(vps_tda3xx_BOARDLIST) tda2px-evm
export vps_examples_issLoopback_BOARDLIST
vps_examples_issLoopback_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_issLoopback_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_issLoopback
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_issLoopback_SBL_APPIMAGEGEN = yes
  export vps_examples_issLoopback_SBL_APPIMAGEGEN
endif

# ISS M2M Example
vps_examples_m2mIss_COMP_LIST = vps_examples_m2mIss
vps_examples_m2mIss_RELPATH = ti/drv/vps/examples/iss/m2mIss
vps_examples_m2mIss_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/m2mIss
vps_examples_m2mIss_BOARD_DEPENDENCY = yes
vps_examples_m2mIss_CORE_DEPENDENCY = no
vps_examples_m2mIss_XDC_CONFIGURO = yes
export vps_examples_m2mIss_COMP_LIST
export vps_examples_m2mIss_BOARD_DEPENDENCY
export vps_examples_m2mIss_CORE_DEPENDENCY
export vps_examples_m2mIss_XDC_CONFIGURO
vps_examples_m2mIss_PKG_LIST = vps_examples_m2mIss
vps_examples_m2mIss_INCLUDE = $(vps_examples_m2mIss_PATH)
vps_examples_m2mIss_BOARDLIST = $(vps_tda3xx_BOARDLIST) tda2px-evm
export vps_examples_m2mIss_BOARDLIST
vps_examples_m2mIss_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_m2mIss_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_m2mIss
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_m2mIss_SBL_APPIMAGEGEN = yes
  export vps_examples_m2mIss_SBL_APPIMAGEGEN
endif

# Simcop LDC Example
vps_examples_m2mSimcopLdcVtnf_COMP_LIST = vps_examples_m2mSimcopLdcVtnf
vps_examples_m2mSimcopLdcVtnf_RELPATH = ti/drv/vps/examples/iss/m2mSimcopLdcVtnf
vps_examples_m2mSimcopLdcVtnf_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/m2mSimcopLdcVtnf
vps_examples_m2mSimcopLdcVtnf_BOARD_DEPENDENCY = yes
vps_examples_m2mSimcopLdcVtnf_CORE_DEPENDENCY = no
vps_examples_m2mSimcopLdcVtnf_XDC_CONFIGURO = yes
export vps_examples_m2mSimcopLdcVtnf_COMP_LIST
export vps_examples_m2mSimcopLdcVtnf_BOARD_DEPENDENCY
export vps_examples_m2mSimcopLdcVtnf_CORE_DEPENDENCY
export vps_examples_m2mSimcopLdcVtnf_XDC_CONFIGURO
vps_examples_m2mSimcopLdcVtnf_PKG_LIST = vps_examples_m2mSimcopLdcVtnf
vps_examples_m2mSimcopLdcVtnf_INCLUDE = $(vps_examples_m2mSimcopLdcVtnf_PATH)
vps_examples_m2mSimcopLdcVtnf_BOARDLIST = $(vps_tda3xx_BOARDLIST) tda2px-evm
export vps_examples_m2mSimcopLdcVtnf_BOARDLIST
vps_examples_m2mSimcopLdcVtnf_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_m2mSimcopLdcVtnf_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_m2mSimcopLdcVtnf
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_m2mSimcopLdcVtnf_SBL_APPIMAGEGEN = yes
  export vps_examples_m2mSimcopLdcVtnf_SBL_APPIMAGEGEN
endif

# ISS M2M WDR
vps_examples_m2mIssWdr_COMP_LIST = vps_examples_m2mIssWdr
vps_examples_m2mIssWdr_RELPATH = ti/drv/vps/examples/iss/m2mWdr
vps_examples_m2mIssWdr_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/m2mWdr
vps_examples_m2mIssWdr_BOARD_DEPENDENCY = yes
vps_examples_m2mIssWdr_CORE_DEPENDENCY = no
vps_examples_m2mIssWdr_XDC_CONFIGURO = yes
export vps_examples_m2mIssWdr_COMP_LIST
export vps_examples_m2mIssWdr_BOARD_DEPENDENCY
export vps_examples_m2mIssWdr_CORE_DEPENDENCY
export vps_examples_m2mIssWdr_XDC_CONFIGURO
vps_examples_m2mIssWdr_PKG_LIST = vps_examples_m2mIssWdr
vps_examples_m2mIssWdr_INCLUDE = $(vps_examples_m2mIssWdr_PATH)
vps_examples_m2mIssWdr_BOARDLIST = $(vps_tda3xx_BOARDLIST) tda2px-evm
export vps_examples_m2mIssWdr_BOARDLIST
vps_examples_m2mIssWdr_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_m2mIssWdr_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_m2mIssWdr
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_m2mIssWdr_SBL_APPIMAGEGEN = yes
  export vps_examples_m2mIssWdr_SBL_APPIMAGEGEN
endif

# ISS CAL M2M Example
vps_examples_m2mIssCal_COMP_LIST = vps_examples_m2mIssCal
vps_examples_m2mIssCal_RELPATH = ti/drv/vps/examples/iss/m2mIssCal
vps_examples_m2mIssCal_PATH = $(PDK_VPS_COMP_PATH)/examples/iss/m2mIssCal
vps_examples_m2mIssCal_BOARD_DEPENDENCY = yes
vps_examples_m2mIssCal_CORE_DEPENDENCY = no
vps_examples_m2mIssCal_XDC_CONFIGURO = yes
export vps_examples_m2mIssCal_COMP_LIST
export vps_examples_m2mIssCal_BOARD_DEPENDENCY
export vps_examples_m2mIssCal_CORE_DEPENDENCY
export vps_examples_m2mIssCal_XDC_CONFIGURO
vps_examples_m2mIssCal_PKG_LIST = vps_examples_m2mIssCal
vps_examples_m2mIssCal_INCLUDE = $(vps_examples_m2mIssCal_PATH)
vps_examples_m2mIssCal_BOARDLIST = tda2px-evm
export vps_examples_m2mIssCal_BOARDLIST
vps_examples_m2mIssCal_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_m2mIssCal_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_m2mIssCal
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_m2mIssCal_SBL_APPIMAGEGEN = yes
  export vps_examples_m2mIssCal_SBL_APPIMAGEGEN
endif

# Loopback Example
vps_examples_loopback_COMP_LIST = vps_examples_loopback
vps_examples_loopback_RELPATH = ti/drv/vps/examples/loopback
vps_examples_loopback_PATH = $(PDK_VPS_COMP_PATH)/examples/loopback
vps_examples_loopback_BOARD_DEPENDENCY = yes
vps_examples_loopback_CORE_DEPENDENCY = no
vps_examples_loopback_XDC_CONFIGURO = yes
export vps_examples_loopback_COMP_LIST
export vps_examples_loopback_BOARD_DEPENDENCY
export vps_examples_loopback_CORE_DEPENDENCY
export vps_examples_loopback_XDC_CONFIGURO
vps_examples_loopback_PKG_LIST = vps_examples_loopback
vps_examples_loopback_INCLUDE = $(vps_examples_loopback_PATH)
vps_examples_loopback_BOARDLIST = $(vps_default_BOARDLIST)
export vps_examples_loopback_BOARDLIST
vps_examples_loopback_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_loopback_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_loopback
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_loopback_SBL_APPIMAGEGEN = yes
  export vps_examples_loopback_SBL_APPIMAGEGEN
endif

# Sync Loopback Example
vps_examples_syncLoopback_COMP_LIST = vps_examples_syncLoopback
vps_examples_syncLoopback_RELPATH = ti/drv/vps/examples/syncLoopback
vps_examples_syncLoopback_PATH = $(PDK_VPS_COMP_PATH)/examples/syncLoopback
vps_examples_syncLoopback_BOARD_DEPENDENCY = yes
vps_examples_syncLoopback_CORE_DEPENDENCY = no
vps_examples_syncLoopback_XDC_CONFIGURO = yes
export vps_examples_syncLoopback_COMP_LIST
export vps_examples_syncLoopback_BOARD_DEPENDENCY
export vps_examples_syncLoopback_CORE_DEPENDENCY
export vps_examples_syncLoopback_XDC_CONFIGURO
vps_examples_syncLoopback_PKG_LIST = vps_examples_syncLoopback
vps_examples_syncLoopback_INCLUDE = $(vps_examples_syncLoopback_PATH)
vps_examples_syncLoopback_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export vps_examples_syncLoopback_BOARDLIST
vps_examples_syncLoopback_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_syncLoopback_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_syncLoopback
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_syncLoopback_SBL_APPIMAGEGEN = yes
  export vps_examples_syncLoopback_SBL_APPIMAGEGEN
endif

# VIP Example
vps_examples_captureVip_COMP_LIST = vps_examples_captureVip
vps_examples_captureVip_RELPATH = ti/drv/vps/examples/vip/captureVip
vps_examples_captureVip_PATH = $(PDK_VPS_COMP_PATH)/examples/vip/captureVip
vps_examples_captureVip_BOARD_DEPENDENCY = yes
vps_examples_captureVip_CORE_DEPENDENCY = no
vps_examples_captureVip_XDC_CONFIGURO = yes
export vps_examples_captureVip_COMP_LIST
export vps_examples_captureVip_BOARD_DEPENDENCY
export vps_examples_captureVip_CORE_DEPENDENCY
export vps_examples_captureVip_XDC_CONFIGURO
vps_examples_captureVip_PKG_LIST = vps_examples_captureVip
vps_examples_captureVip_INCLUDE = $(vps_examples_captureVip_PATH)
vps_examples_captureVip_BOARDLIST = $(vps_default_BOARDLIST)
export vps_examples_captureVip_BOARDLIST
vps_examples_captureVip_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_captureVip_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_captureVip
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_captureVip_SBL_APPIMAGEGEN = yes
  export vps_examples_captureVip_SBL_APPIMAGEGEN
endif

# VIP Sub-frame Example
vps_examples_subFrmCaptureVip_COMP_LIST = vps_examples_subFrmCaptureVip
vps_examples_subFrmCaptureVip_RELPATH = ti/drv/vps/examples/vip/subFrmCaptureVip
vps_examples_subFrmCaptureVip_PATH = $(PDK_VPS_COMP_PATH)/examples/vip/subFrmCaptureVip
vps_examples_subFrmCaptureVip_BOARD_DEPENDENCY = yes
vps_examples_subFrmCaptureVip_CORE_DEPENDENCY = no
vps_examples_subFrmCaptureVip_XDC_CONFIGURO = yes
export vps_examples_subFrmCaptureVip_COMP_LIST
export vps_examples_subFrmCaptureVip_BOARD_DEPENDENCY
export vps_examples_subFrmCaptureVip_CORE_DEPENDENCY
export vps_examples_subFrmCaptureVip_XDC_CONFIGURO
vps_examples_subFrmCaptureVip_PKG_LIST = vps_examples_subFrmCaptureVip
vps_examples_subFrmCaptureVip_INCLUDE = $(vps_examples_subFrmCaptureVip_PATH)
vps_examples_subFrmCaptureVip_BOARDLIST = $(vps_default_BOARDLIST)
export vps_examples_subFrmCaptureVip_BOARDLIST
vps_examples_subFrmCaptureVip_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_subFrmCaptureVip_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_subFrmCaptureVip
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_subFrmCaptureVip_SBL_APPIMAGEGEN = yes
  export vps_examples_subFrmCaptureVip_SBL_APPIMAGEGEN
endif

# VPE Example
vps_examples_m2mVpeScale_COMP_LIST = vps_examples_m2mVpeScale
vps_examples_m2mVpeScale_RELPATH = ti/drv/vps/examples/vpe/m2mVpeScale
vps_examples_m2mVpeScale_PATH = $(PDK_VPS_COMP_PATH)/examples/vpe/m2mVpeScale
vps_examples_m2mVpeScale_BOARD_DEPENDENCY = yes
vps_examples_m2mVpeScale_CORE_DEPENDENCY = no
vps_examples_m2mVpeScale_XDC_CONFIGURO = yes
export vps_examples_m2mVpeScale_COMP_LIST
export vps_examples_m2mVpeScale_BOARD_DEPENDENCY
export vps_examples_m2mVpeScale_CORE_DEPENDENCY
export vps_examples_m2mVpeScale_XDC_CONFIGURO
vps_examples_m2mVpeScale_PKG_LIST = vps_examples_m2mVpeScale
vps_examples_m2mVpeScale_INCLUDE = $(vps_examples_m2mVpeScale_PATH)
vps_examples_m2mVpeScale_BOARDLIST = $(vps_tda2xx_BOARDLIST)
export vps_examples_m2mVpeScale_BOARDLIST
vps_examples_m2mVpeScale_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_m2mVpeScale_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_m2mVpeScale
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_examples_m2mVpeScale_SBL_APPIMAGEGEN = yes
  export vps_examples_m2mVpeScale_SBL_APPIMAGEGEN
endif

# VPS CCS Projects
vps_examples_ccsProjectMetaFiles_COMP_LIST = vps_examples_ccsProjectMetaFiles
vps_examples_ccsProjectMetaFiles_RELPATH = ti/drv/vps/examples/ccsprojects
vps_examples_ccsProjectMetaFiles_PATH = $(PDK_VPS_COMP_PATH)/examples/ccsprojects
vps_examples_ccsProjectMetaFiles_BOARD_DEPENDENCY = no
vps_examples_ccsProjectMetaFiles_CORE_DEPENDENCY = no
vps_examples_ccsProjectMetaFiles_XDC_CONFIGURO = no
export vps_examples_ccsProjectMetaFiles_COMP_LIST
export vps_examples_ccsProjectMetaFiles_BOARD_DEPENDENCY
export vps_examples_ccsProjectMetaFiles_CORE_DEPENDENCY
export vps_examples_ccsProjectMetaFiles_XDC_CONFIGURO
vps_examples_ccsProjectMetaFiles_PKG_LIST = vps_examples_ccsProjectMetaFiles
vps_examples_ccsProjectMetaFiles_INCLUDE = $(vps_examples_ccsProjectMetaFiles_PATH)
vps_examples_ccsProjectMetaFiles_SOCLIST = am571x am572x am574x dra75x dra78x
export vps_examples_ccsProjectMetaFiles_SOCLIST
vps_examples_ccsProjectMetaFiles_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_examples_ccsProjectMetaFiles_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_examples_ccsProjectMetaFiles

#Include UT application
-include $(PDK_VPS_COMP_PATH)/unit_test/vps_ut_component.mk

#Override example list as non of the example in VPS supports baremetal; only lib is baremetal support
ifeq ($(BUILD_OS_TYPE), baremetal)
  vps_EXAMPLE_LIST =
endif

export vps_LIB_LIST
export vps_EXAMPLE_LIST

VPSLIB_CFLAGS =
VPSDRV_CFLAGS =

VPSLIB_CFLAGS += -DTRACE_ENABLE
ifeq ($(BUILD_PROFILE_$(CORE)),debug)
# Enable asserts for debug build
  VPSLIB_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(BUILD_PROFILE_$(CORE)),release)
# Enable asserts for release build
  VPSLIB_CFLAGS += -DASSERT_ENABLE
endif

#Use PACKAGE_SELECT input
ifeq ($(PACKAGE_SELECT),all)
  PACKAGE_VIP ?= yes
  PACKAGE_VPE ?= yes
  ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x am572x tda2ex am571x tda3xx am574x))
    PACKAGE_DSS ?= yes
  endif
  PACKAGE_ISS ?= yes
  ifeq ($(SOC),tda2ex)
    PACKAGE_CAL ?= yes
  endif
else
  # Set default packaging for differenet moduels, select none
  PACKAGE_VIP ?= no
  PACKAGE_VPE ?= no
  PACKAGE_DSS ?= no
  PACKAGE_ISS ?= no
  ifeq ($(SOC),tda2ex)
    PACKAGE_CAL ?= no
  endif
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx tda2px))
 PACKAGE_ISS_COMMON ?= $(PACKAGE_ISS)
 PACKAGE_ISP ?= $(PACKAGE_ISS)
 PACKAGE_M2M ?= $(PACKAGE_ISS)
 PACKAGE_SIMCOP ?= $(PACKAGE_ISS)
 PACKAGE_CAL ?= $(PACKAGE_ISS)
endif

ifeq ($(PACKAGE_SELECT),vps-hal-only)
  PACKAGE_VIP = yes
  PACKAGE_VPE = yes
  PACKAGE_DSS = yes
  ifeq ($(SOC),$(filter $(SOC), tda3xx tda2px))
    PACKAGE_ISS_COMMON = yes
    PACKAGE_ISP = yes
    PACKAGE_SIMCOP = yes
    PACKAGE_CAL = yes
  endif

  ifeq ($(SOC),tda2ex)
    PACKAGE_CAL = yes
  endif
endif

ifeq ($(PACKAGE_SELECT),vps-vip-only)
  PACKAGE_VIP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vpe-only)
  PACKAGE_VPE = yes
endif
ifeq ($(PACKAGE_SELECT),vps-dss-only)
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-dss)
  PACKAGE_VIP = yes
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-vpe)
  PACKAGE_VIP = yes
  PACKAGE_VPE = yes
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx tda2px))
ifeq ($(PACKAGE_SELECT),vps-iss-only)
  PACKAGE_ISS_COMMON = yes
  PACKAGE_M2M = yes
  PACKAGE_ISP = yes
  PACKAGE_SIMCOP = yes
  PACKAGE_DSS = yes
  PACKAGE_CAL = yes
endif
ifeq ($(PACKAGE_SELECT),vps-simcop-only)
  PACKAGE_ISS_COMMON = yes
  PACKAGE_M2M = yes
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-isp-only)
  PACKAGE_ISS_COMMON = yes
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-hal-only)
  PACKAGE_ISS_COMMON = yes
  PACKAGE_ISP = yes
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-iss-dss-only)
  PACKAGE_ISS_COMMON = yes
  PACKAGE_M2M = yes
  PACKAGE_ISP = yes
  PACKAGE_SIMCOP = yes
  PACKAGE_DSS = yes
  PACKAGE_CAL = yes
endif
endif

ifeq ($(PACKAGE_SELECT), vps-cal-only)
  ifeq ($(SOC),tda3xx)
    PACKAGE_ISS_COMMON = no
    PACKAGE_CAL = yes
  endif

  ifeq ($(SOC),tda2ex)
    PACKAGE_ISS_COMMON = no
    PACKAGE_CAL = yes
  endif
endif

#Override packages based on SOC
ifneq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x am572x tda2ex am571x tda3xx am574x))
  PACKAGE_VIP = no
  PACKAGE_DSS = no
endif
ifneq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x am572x tda2ex am571x am574x))
  PACKAGE_VPE = no
endif
ifneq ($(SOC),$(filter $(SOC), tda2ex am571x tda3xx tda2px))
  PACKAGE_CAL = no
endif
ifneq ($(SOC),$(filter $(SOC), tda3xx tda2px))
  PACKAGE_ISP = no
  PACKAGE_ISS_COMMON = no
  PACKAGE_M2M = no
  PACKAGE_SIMCOP = no
endif

# user can set these through command line while building
# usage gmake -s <target> PACKAGE_VIP1_BUILD=<yes/no> PACKAGE_VIP2_BUILD=<yes/no> PACKAGE_VIP3_BUILD=<yes/no>
# if $(PACKAGE_VIP)=no (i.e. PACKAGE_SELECT=<non-vip build>, then these variables are all set to "no" internally
ifeq ($(PACKAGE_VIP),yes)
  ifeq ($(PACKAGE_VIP1_BUILD),)
    PACKAGE_VIP1_BUILD = yes
  endif
  ifeq ($(PACKAGE_VIP2_BUILD),)
    PACKAGE_VIP2_BUILD = yes
  endif
  ifeq ($(PACKAGE_VIP3_BUILD),)
    PACKAGE_VIP3_BUILD = yes
  endif
endif
ifeq ($(PACKAGE_VIP),no)
  PACKAGE_VIP1_BUILD = no
  PACKAGE_VIP2_BUILD = no
  PACKAGE_VIP3_BUILD = no
endif

#Override packages based on SOC
ifeq ($(SOC),$(filter $(SOC), tda2ex am571x tda3xx))
  PACKAGE_VIP2_BUILD = no
  PACKAGE_VIP3_BUILD = no
endif
ifeq ($(SOC),$(filter $(SOC), tda2px am574x))
  PACKAGE_VIP3_BUILD = no
endif

# Set compiler build macros based on package select variables
ifeq ($(PACKAGE_VIP),yes)
  VPSLIB_CFLAGS += -DVPS_VIP_BUILD
  VPSDRV_CFLAGS += -DVPS_CAPT_BUILD
endif
ifeq ($(PACKAGE_VIP1_BUILD),yes)
  VPSLIB_CFLAGS += -DVPS_VIP1_BUILD
endif
ifeq ($(PACKAGE_VIP2_BUILD),yes)
  VPSLIB_CFLAGS += -DVPS_VIP2_BUILD
endif
ifeq ($(PACKAGE_VIP3_BUILD),yes)
  VPSLIB_CFLAGS += -DVPS_VIP3_BUILD
endif

ifeq ($(PACKAGE_VPE),yes)
  VPSLIB_CFLAGS += -DVPS_VPE_BUILD
endif

ifeq ($(PACKAGE_DSS),yes)
  VPSLIB_CFLAGS += -DVPS_DSS_BUILD
  VPSDRV_CFLAGS += -DVPS_DISP_BUILD
endif

ifeq ($(PACKAGE_M2M),yes)
  VPSDRV_CFLAGS += -DVPS_M2M_BUILD
endif

ifeq ($(PACKAGE_CAL),yes)
  VPSLIB_CFLAGS += -DVPS_CAL_BUILD
  VPSDRV_CFLAGS += -DVPS_CAPT_BUILD
endif

ifeq ($(PACKAGE_ISS_COMMON),yes)
  VPSLIB_CFLAGS += -DVPS_ISS_BUILD
  VPSLIB_CFLAGS += -DVPS_ISS_ISP_DEF
  ifeq ($(SOC),$(filter $(SOC), tda2px))
    VPSLIB_CFLAGS += -DVPS_ISS_CALM2M_BUILD
  endif
endif

ifeq ($(PACKAGE_ISP),yes)
  VPSLIB_CFLAGS += -DVPS_ISS_BUILD
endif

ifeq ($(PACKAGE_SIMCOP),yes)
  VPSLIB_CFLAGS += -DVPS_SIMCOP_BUILD
endif

# Enable custom frame buffer memory size
ifneq ($(CUSTOM_MEM_FRAME_HEAP_SIZE), )
  VPSDRV_CFLAGS += -DCUSTOM_MEM_FRAME_HEAP_SIZE=$(CUSTOM_MEM_FRAME_HEAP_SIZE)
endif

INCLUDE_WDR_LDC ?= yes

#Include empty functions for Safety OSAL APIs used within OSAL APIs
#Application may override this to define own SAFETY_OSAL implementation
#Refer VisionSDK for example implementation of custom SAFETY_OSAL
INCLUDE_DUMMY_OSAL ?= yes

#I2C disable make flag - needed for linux build to control I2C through linux driver
VPS_DISABLE_I2C0 ?= no
VPS_DISABLE_I2C1 ?= no
VPS_DISABLE_I2C2 ?= no
VPS_DISABLE_I2C3 ?= no
VPS_DISABLE_I2C4 ?= no
VPS_USE_LINUX_INTC_NUMBERS ?= no
VSDK_OPTIM_SENSOR_INIT ?= no
ifeq ($(VPS_DISABLE_I2C0),yes)
  VPSDRV_CFLAGS += -DBSP_DISABLE_I2C0
endif
ifeq ($(VPS_DISABLE_I2C1),yes)
  VPSDRV_CFLAGS += -DBSP_DISABLE_I2C1
endif
ifeq ($(VPS_DISABLE_I2C2),yes)
  VPSDRV_CFLAGS += -DBSP_DISABLE_I2C2
endif
ifeq ($(VPS_DISABLE_I2C3),yes)
  VPSDRV_CFLAGS += -DBSP_DISABLE_I2C3
endif
ifeq ($(VPS_DISABLE_I2C4),yes)
  VPSDRV_CFLAGS += -DBSP_DISABLE_I2C4
endif
ifeq ($(VPS_USE_LINUX_INTC_NUMBERS),yes)
  VPSDRV_CFLAGS += -DVPS_USE_LINUX_INTC_NUMBERS
endif
ifeq ($(VSDK_SENSOR_INIT),yes)
  VPSDRV_CFLAGS += -DVSDK_OPTIM_SENSOR_INIT
endif
VPS_USE_TI_RTOS_I2C := no
VPS_USE_TI_RTOS_UART := no
VPS_USE_TI_RTOS_OSAL := no
VPS_USE_TI_RTOS_MMCSD := no
#use TI RTOS drivers for AM build
ifeq ($(SOC),$(filter $(SOC), am574x am572x am571x dra75x dra78x))
  VPS_USE_TI_RTOS_I2C := yes
  VPS_USE_TI_RTOS_UART := yes
  VPS_USE_TI_RTOS_OSAL := yes
  VPS_USE_TI_RTOS_MMCSD := yes
  VPSDRV_CFLAGS += -DVPS_TI_RTOS_I2C
  VPSDRV_CFLAGS += -DVPS_TI_RTOS_UART
  VPSDRV_CFLAGS += -DVPS_TI_RTOS_OSAL
  VPSDRV_CFLAGS += -DVPS_TI_RTOS_MMCSD
endif

#RADAR related defines and flags
ifeq ($(BOARD), $(filter $(BOARD), tda3xx-evm-radar tda2xx-evm-radar tda2px-evm-radar tda3xx-ar12-booster tda3xx-ar12-alps tda3xx-ar12-rvp tda2xx-cascade-radar))
  VPS_RADAR_INCLUDE ?= yes
else
  VPS_RADAR_INCLUDE ?= no
endif
radarMssFirmware_PATH=$(radarLink_PATH)/firmware/masterss
radarBssFirmware_PATH=$(radarLink_PATH)/firmware/radarss
radarFirmware_INCLUDE = $(radarMssFirmware_PATH) $(radarBssFirmware_PATH)   \
                        $(radarLink_PATH)/firmware
export radarFirmware_INCLUDE
ifeq ($(BOARD), $(filter $(BOARD), tda3xx-ar12-alps))
  VPSDRV_CFLAGS += -DBOARD_TYPE_TDA3XX_AR12_ALPS
endif
ifeq ($(BOARD), $(filter $(BOARD), tda3xx-ar12-booster))
  VPSDRV_CFLAGS += -DBOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER
endif
ifeq ($(BOARD), $(filter $(BOARD), tda3xx-rvp))
  VPSDRV_CFLAGS += -DBOARD_TYPE_TDA3XX_RVP
endif
ifeq ($(BOARD), $(filter $(BOARD), tda2xx-rvp))
  VPSDRV_CFLAGS += -DBOARD_TYPE_TDA2XX_RVP
endif
ifeq ($(BOARD), $(filter $(BOARD), tda3xx-ar12-rvp))
  VPSDRV_CFLAGS += -DBOARD_TYPE_TDA3XX_RVP -DBOARD_TYPE_TDA3XX_RADAR_RVP
endif
ifeq ($(BOARD), $(filter $(BOARD), tda2xx-cascade-radar))
  VPSDRV_CFLAGS += -DBOARD_TYPE_TDA2XX_CASCADE_RADAR
endif

export VPSLIB_CFLAGS
export VPSDRV_CFLAGS
export PACKAGE_VIP
export PACKAGE_VPE
export PACKAGE_DSS
export PACKAGE_ISS
export PACKAGE_M2M
export PACKAGE_CAL
export PACKAGE_ISS_COMMON
export PACKAGE_ISP
export PACKAGE_SIMCOP
export PACKAGE_VIP1_BUILD
export PACKAGE_VIP2_BUILD
export PACKAGE_VIP3_BUILD
export INCLUDE_WDR_LDC
export INCLUDE_DUMMY_OSAL
export VPS_DISABLE_I2C0
export VPS_DISABLE_I2C1
export VPS_DISABLE_I2C2
export VPS_DISABLE_I2C3
export VPS_DISABLE_I2C4
export VPS_USE_TI_RTOS_I2C
export VPS_USE_TI_RTOS_UART
export VPS_USE_TI_RTOS_OSAL
export VPS_USE_TI_RTOS_MMCSD
export radarMssFirmware_PATH
export radarBssFirmware_PATH
export VPS_RADAR_INCLUDE

vps_component_make_include := 1
endif
