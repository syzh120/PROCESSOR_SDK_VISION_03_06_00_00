# File: sbl_auto_component.mk
#       This file is component include make file of SBL.
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
ifeq ($(sbl_auto_component_make_include), )

sbllib_default_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
sbllib_default_tda2xx_CORELIST = a15_0 ipu1_0
sbllib_default_tda2px_CORELIST = a15_0 ipu1_0
sbllib_default_tda2ex_CORELIST = a15_0 ipu1_0
sbllib_default_tda3xx_CORELIST = ipu1_0
sbllib_default_dra72x_CORELIST = a15_0 ipu1_0
sbllib_default_dra75x_CORELIST = a15_0 ipu1_0
sbllib_default_dra78x_CORELIST = ipu1_0

sblutils_default_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
sblutils_default_tda2xx_CORELIST = a15_0
sblutils_default_tda2px_CORELIST = a15_0
sblutils_default_tda2ex_CORELIST = a15_0
sblutils_default_tda3xx_CORELIST = ipu1_0
sblutils_default_dra72x_CORELIST = a15_0
sblutils_default_dra75x_CORELIST = a15_0
sblutils_default_dra78x_CORELIST = ipu1_0

sbl_auto_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda3xx-evm-radar tda2xx-evm-radar tda2px-evm-radar tda3xx-ar12-booster tda3xx-ar12-alps tda3xx-ar12-rvp tda3xx-rvp tda2ex-eth-srv tda2xx-rvp tda2xx-cascade-radar
sbl_auto_tda2xx_CORELIST = a15_0
sbl_auto_tda2px_CORELIST = a15_0
sbl_auto_tda2ex_CORELIST = a15_0
sbl_auto_tda3xx_CORELIST = ipu1_0
sbl_auto_dra72x_CORELIST = a15_0
sbl_auto_dra75x_CORELIST = a15_0
sbl_auto_dra78x_CORELIST = ipu1_0

SBL_BOOTMODE_LIST_tda2xx = qspi sd nor
SBL_BOOTMODE_LIST_tda2px = qspi sd nor
SBL_BOOTMODE_LIST_tda2ex = qspi sd nor
SBL_BOOTMODE_LIST_tda3xx = qspi qspi_sd nor
SBL_BOOTMODE_LIST_dra72x = qspi sd nor
SBL_BOOTMODE_LIST_dra75x = qspi sd nor
SBL_BOOTMODE_LIST_dra78x = qspi qspi_sd nor

SBL_OPPMODE_LIST_tda2xx = opp_nom opp_od opp_high opp_low
SBL_OPPMODE_LIST_tda2px = opp_nom opp_od opp_high opp_low opp_plus
SBL_OPPMODE_LIST_tda2ex = opp_nom opp_od opp_high opp_plus
SBL_OPPMODE_LIST_tda3xx = opp_nom opp_od opp_high
SBL_OPPMODE_LIST_dra72x = opp_nom opp_od opp_high opp_low
SBL_OPPMODE_LIST_dra75x = opp_nom opp_od opp_high
SBL_OPPMODE_LIST_dra78x = opp_nom opp_od opp_high

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x))
SOC_SRC=tda2xx
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex dra72x))
SOC_SRC=tda2ex
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SOC_SRC=tda3xx
endif

############################
# sbl package
# List of components included under sbl
# The components included here are built and will be part of sbl
############################
sbl_auto_LIB_LIST = sbl_lib sbl_utils

############################
# sbl example
# List of examples under sbl (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
sbl_auto_EXAMPLE_LIST =
sbl_auto_DUP_EXAMPLE_LIST =

#
# SBL Modules
#

# SBL LIB
sbl_lib_COMP_LIST = sbl_lib
sbl_lib_RELPATH = ti/boot/sbl_auto/sbl_lib
sbl_lib_PATH = $(PDK_SBL_AUTO_COMP_PATH)/sbl_lib
sbl_lib_LIBNAME = sbl_lib
sbl_lib_LIBPATH = $(PDK_SBL_AUTO_COMP_PATH)/lib
sbl_lib_MAKEFILE = -fsrc/makefile
export sbl_lib_MAKEFILE
export sbl_lib_LIBNAME
export sbl_lib_LIBPATH
sbl_lib_BOARD_DEPENDENCY = yes
sbl_lib_CORE_DEPENDENCY = no
export sbl_lib_COMP_LIST
export sbl_lib_BOARD_DEPENDENCY
export sbl_lib_CORE_DEPENDENCY
sbl_lib_PKG_LIST = sbl_lib
sbl_lib_INCLUDE = $(sbl_lib_PATH)
sbl_lib_SOCLIST = $(sbllib_default_SOCLIST)
sbl_lib_BOARDLIST = $(sbl_auto_BOARDLIST)
export sbl_lib_SOCLIST
export sbl_lib_BOARDLIST
sbl_lib_$(SOC)_CORELIST = $(sbllib_default_$(SOC)_CORELIST)
export sbl_lib_$(SOC)_CORELIST

# SBL UTILS
sbl_utils_COMP_LIST = sbl_utils
sbl_utils_RELPATH = ti/boot/sbl_auto/sbl_utils
sbl_utils_PATH = $(PDK_SBL_AUTO_COMP_PATH)/sbl_utils
sbl_utils_LIBNAME = sbl_utils
sbl_utils_LIBPATH = $(PDK_SBL_AUTO_COMP_PATH)/lib
sbl_utils_MAKEFILE = -fsrc/makefile
export sbl_utils_MAKEFILE
export sbl_utils_LIBNAME
export sbl_utils_LIBPATH
sbl_utils_BOARD_DEPENDENCY = yes
sbl_utils_CORE_DEPENDENCY = no
export sbl_utils_COMP_LIST
export sbl_utils_BOARD_DEPENDENCY
export sbl_utils_CORE_DEPENDENCY
sbl_utils_PKG_LIST = sbl_utils
sbl_utils_INCLUDE = $(sbl_utils_PATH)
sbl_utils_SOCLIST = $(sblutils_default_SOCLIST)
sbl_utils_BOARDLIST = $(sbl_auto_BOARDLIST)
export sbl_utils_SOCLIST
export sbl_utils_BOARDLIST
sbl_utils_$(SOC)_CORELIST = $(sblutils_default_$(SOC)_CORELIST)
export sbl_utils_$(SOC)_CORELIST

#
# SBL Examples
#
# SBL
sbl_COMP_LIST = sbl
sbl_RELPATH = ti/boot/sbl_auto/sbl_app/src/$(SOC_SRC)
sbl_PATH = $(PDK_SBL_AUTO_COMP_PATH)/sbl_app/src/$(SOC_SRC)
sbl_MAKEFILE = -fmakefile
export sbl_MAKEFILE
sbl_BOARD_DEPENDENCY = yes
sbl_CORE_DEPENDENCY = no
export sbl_COMP_LIST
export sbl_BOARD_DEPENDENCY
export sbl_CORE_DEPENDENCY
sbl_PKG_LIST = sbl
sbl_INCLUDE = $(sbl_PATH)
sbl_BOARDLIST = $(sbl_auto_BOARDLIST)
export sbl_BOARDLIST
sbl_$(SOC)_CORELIST = $(sbl_auto_$(SOC)_CORELIST)
export sbl_$(SOC)_CORELIST
sbl_auto_EXAMPLE_LIST += sbl
sbl_SBL_IMAGEGEN = yes
export sbl_SBL_IMAGEGEN

# SBL All - dummy target to build all SBL apps
sbl_all_COMP_LIST = sbl_all
sbl_all_RELPATH = ti/boot/sbl_auto/sbl_app
sbl_all_PATH = $(PDK_SBL_AUTO_COMP_PATH)/sbl_app
sbl_all_MAKEFILE = -fmakefile_all.mk
export sbl_all_MAKEFILE
sbl_all_BOARD_DEPENDENCY = yes
sbl_all_CORE_DEPENDENCY = no
export sbl_all_COMP_LIST
export sbl_all_BOARD_DEPENDENCY
export sbl_all_CORE_DEPENDENCY
sbl_all_PKG_LIST = sbl_all
sbl_all_INCLUDE = $(sbl_all_PATH)
sbl_all_BOARDLIST = $(sbl_auto_BOARDLIST)
export sbl_all_BOARDLIST
# Core is taken care in the SBL top level makefile. Select all cores so that
# when make with default core builds the target
sbl_all_$(SOC)_CORELIST = a15_0 ipu1_0
export sbl_all_$(SOC)_CORELIST
sbl_auto_DUP_EXAMPLE_LIST += sbl_all

# SBL All OPPS - dummy target to build all SBL apps and all opps
sbl_all_opps_COMP_LIST = sbl_all_opps
sbl_all_opps_RELPATH = ti/boot/sbl_auto/sbl_app
sbl_all_opps_PATH = $(PDK_SBL_AUTO_COMP_PATH)/sbl_app
sbl_all_opps_MAKEFILE = -fmakefile_opps.mk
export sbl_all_opps_MAKEFILE
sbl_all_opps_BOARD_DEPENDENCY = yes
sbl_all_opps_CORE_DEPENDENCY = no
export sbl_all_opps_COMP_LIST
export sbl_all_opps_BOARD_DEPENDENCY
export sbl_all_opps_CORE_DEPENDENCY
sbl_all_opps_PKG_LIST = sbl_all_opps
sbl_all_opps_INCLUDE = $(sbl_all_opps_PATH)
sbl_all_opps_BOARDLIST = $(sbl_auto_BOARDLIST)
export sbl_all_opps_BOARDLIST
# Core is taken care in the SBL top level makefile. Select all cores so that
# when make with default core builds the target
sbl_all_opps_$(SOC)_CORELIST = a15_0 ipu1_0
export sbl_all_opps_$(SOC)_CORELIST
sbl_auto_DUP_EXAMPLE_LIST += sbl_all_opps

sbl_multicore_mbx_COMP_LIST = sbl_multicore_mbx
sbl_multicore_mbx_RELPATH = ti/boot/sbl_auto/examples/sbl_multicore_mbx/$(SOC_SRC)
sbl_multicore_mbx_PATH = $(PDK_SBL_AUTO_COMP_PATH)/examples/sbl_multicore_mbx/$(SOC_SRC)
sbl_multicore_mbx_MAKEFILE = -fmakefile
export sbl_multicore_mbx_MAKEFILE
sbl_multicore_mbx_BOARD_DEPENDENCY = yes
sbl_multicore_mbx_CORE_DEPENDENCY = no
export sbl_multicore_mbx_COMP_LIST
export sbl_multicore_mbx_BOARD_DEPENDENCY
export sbl_multicore_mbx_CORE_DEPENDENCY
sbl_multicore_mbx_PKG_LIST = sbl_multicore_mbx
sbl_multicore_mbx_INCLUDE = $(sbl_multicore_mbx_PATH)
sbl_multicore_mbx_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm tda2xx-rvp
export sbl_multicore_mbx_BOARDLIST
ifeq ($(SOC), tda3xx)
sbl_multicore_mbx_$(SOC)_CORELIST = ipu1_0 ipu1_1 c66xdsp_1 c66xdsp_2 arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px))
sbl_multicore_mbx_$(SOC)_CORELIST = ipu1_0 ipu1_1 ipu2_0 ipu2_1 c66xdsp_1 c66xdsp_2 arp32_1 a15_0
endif
ifeq ($(SOC), tda2ex)
sbl_multicore_mbx_$(SOC)_CORELIST = ipu1_0 ipu1_1 c66xdsp_1 a15_0
endif
export sbl_multicore_mbx_$(SOC)_CORELIST
sbl_auto_EXAMPLE_LIST += sbl_multicore_mbx

export sbl_auto_LIB_LIST
export sbl_auto_EXAMPLE_LIST
export sbl_auto_DUP_EXAMPLE_LIST

#default values
BOOTMODE ?= qspi
OPPMODE ?= opp_nom
#default HS enable/disable
BUILD_HS ?= no
SBL_CONFIG ?= default
SBL_OPT_MODE ?= low
SBL_TRACE_MODE ?= low
SBL_BUILD_MODE ?= prod
FORCE_OPPMODE ?= FALSE

SBL_CFLAGS =

ifeq ($(SOC), dra72x)
    SBL_CFLAGS += -DSOC_TDA2EX
endif
ifeq ($(SOC), dra75x)
    SBL_CFLAGS += -DSOC_TDA2XX
endif
ifeq ($(SOC), dra78x)
    SBL_CFLAGS += -DSOC_TDA3XX
endif


#Boot flags
ifeq ($(BOOTMODE),qspi)
    SBL_CFLAGS += -DBOOTMODE_QSPI
endif
ifeq ($(BOOTMODE),qspi_sd)
    SBL_CFLAGS += -DBOOTMODE_QSPI_SD
endif
ifeq ($(BOOTMODE), sd)
    SBL_CFLAGS += -DBOOTMODE_SD
endif
ifeq ($(BOOTMODE),nor)
    SBL_CFLAGS += -DBOOTMODE_NOR
endif

# Different type of SBL, can be custom
ifeq ($(SBL_TYPE),mflash)
    SBL_CFLAGS += -DBOOTMODE_UART
endif

#SBL config
ifeq ($(SBL_CONFIG), default)
    SBL_CFLAGS += -DSBL_CONFIG_DEFAULT
endif
ifeq ($(SBL_CONFIG), custom1)
    SBL_CFLAGS += -DSBL_CONFIG_CUSTOM1
endif
ifeq ($(SBL_CONFIG), disable_safety)
    SBL_CFLAGS += -DSBL_CONFIG_DISABLE_SAFETY_FEATURES
endif

# SBL optimization level
ifeq ($(SBL_OPT_MODE), low)
    SBL_CFLAGS += -DSBL_OPT_LEVEL=0
    SBL_TRACE_MODE = medium
else ifeq ($(SBL_OPT_MODE), medium)
    SBL_CFLAGS += -DSBL_OPT_LEVEL=1
    SBL_TRACE_MODE = low
else ifeq ($(SBL_OPT_MODE), high)
    SBL_CFLAGS += -DSBL_OPT_LEVEL=2
    SBL_TRACE_MODE = imp_info
else
    SBL_CFLAGS += -DSBL_OPT_LEVEL=0
endif

#Build mode flags
ifeq ($(SBL_BUILD_MODE), prod)
    SBL_CFLAGS += -DSBL_PROD_BUILD
endif
ifeq ($(SBL_BUILD_MODE), dev)
    SBL_CFLAGS += -DSBL_DEV_BUILD
endif

# Trace mode Mapping:
# low:    SBLLIB_TRACE_LEVEL_INFO
# medium: SBLLIB_TRACE_LEVEL_INFO1
# high:   SBLLIB_TRACE_LEVEL_DEBUG
# For prints Trace levels medium and high are considered only when optimization
# level is low in current implementation.
ifeq ($(SBL_TRACE_MODE), high)
    SBL_CFLAGS += -DTRACE_LEVEL=4
else ifeq ($(SBL_TRACE_MODE), medium)
    SBL_CFLAGS += -DTRACE_LEVEL=3
else ifeq ($(SBL_TRACE_MODE), low)
    SBL_CFLAGS += -DTRACE_LEVEL=2
else
    SBL_CFLAGS += -DTRACE_LEVEL=1
endif

ifeq ($(BUILD_HS), yes)
    SBL_CFLAGS += -DDEVICE_TYPE_HS
endif

ifeq ($(SBL_TEST_AUTO), yes)
    SBL_CFLAGS += -DSBL_TEST_AUTO_BUILD
endif

# Flag to set EMIF MODE
# Keep values in sync with sbl_lib_tda2xx.h
# DUAL_EMIF_2X512MB   => SBLLIB_DUAL_EMIF_2X512MB   = (0U)
# DUAL_EMIF_1GB_512MB => SBLLIB_DUAL_EMIF_1GB_512MB = (1U)
# SINGLE_EMIF_256MB   => SBLLIB_SINGLE_EMIF_256MB   = (2U)
# SINGLE_EMIF_512MB   => SBLLIB_SINGLE_EMIF_512MB   = (3U)
# If this is not set, TDA2XX_EMIF_MODE is defined as per sbl_lib_config_tda2xx.h
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x))
  ifeq ($(EMIFMODE), DUAL_EMIF_2X512MB)
      SBL_CFLAGS += -DTDA2XX_EMIF_MODE=0
  else ifeq ($(EMIFMODE), DUAL_EMIF_1GB_512MB)
      SBL_CFLAGS += -DTDA2XX_EMIF_MODE=1
  else ifeq ($(EMIFMODE), SINGLE_EMIF_256MB)
      SBL_CFLAGS += -DTDA2XX_EMIF_MODE=2
  else ifeq ($(EMIFMODE), SINGLE_EMIF_512MB)
      SBL_CFLAGS += -DTDA2XX_EMIF_MODE=3
  endif
endif

# TDA3XX RVP boards
ifeq ($(BOARD), $(filter $(BOARD), tda3xx-rvp tda3xx-ar12-rvp))
	SBL_CFLAGS += -DBOARD_TYPE_TDA3XX_RVP
endif

ifeq ($(BOARD), $(filter $(BOARD), tda2xx-cascade-radar))
	SBL_CFLAGS += -DBOARD_TYPE_TDA2XX_CASCADE_RADAR
endif

# TDA3XX boards
ifeq ($(SOC), tda3xx)
  ifeq ($(BOARD), $(filter $(BOARD), tda3xx-rvp tda3xx-ar12-rvp))
    ifeq ($(EMIFMODE), SINGLE_EMIF_1GB)
      SBL_CFLAGS += -DTDA3XX_AMMU_CONFIG_MAP_DDR_1GB
    else
      SBL_CFLAGS += -DTDA3XX_AMMU_CONFIG_MAP_DDR_512MB
    endif
  endif
endif

export SBL_CFLAGS
export SBL_TYPE
export BUILD_HS

sbl_auto_component_make_include := 1
endif
