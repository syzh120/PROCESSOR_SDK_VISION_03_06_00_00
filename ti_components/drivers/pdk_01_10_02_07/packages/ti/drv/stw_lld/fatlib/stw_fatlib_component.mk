# File: stw_fatlib_component.mk
#       This file is component include make file of STW FATLIB library.
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
ifeq ($(stw_fatlib_component_make_include), )

stw_fatlib_default_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
stw_fatlib_default_tda2xx_CORELIST = a15_0 ipu1_0
stw_fatlib_default_tda2px_CORELIST = a15_0 ipu1_0
stw_fatlib_default_tda2ex_CORELIST = a15_0 ipu1_0
stw_fatlib_default_tda3xx_CORELIST = ipu1_0
stw_fatlib_default_dra72x_CORELIST = a15_0 ipu1_0
stw_fatlib_default_dra75x_CORELIST = a15_0 ipu1_0
stw_fatlib_default_dra78x_CORELIST = ipu1_0

############################
# stw_fatlib package
# List of components included under stw_fatlib
# The components included here are built and will be part of stw_fatlib lib
############################
stw_fatlib_LIB_LIST = stw_fatlib stw_fatlib_edma

############################
# stw_fatlib examples
# List of examples under stw_fatlib (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
stw_fatlib_EXAMPLE_LIST =

#
# FATLIB Modules
#

# FATLIB LIB
stw_fatlib_COMP_LIST = stw_fatlib
stw_fatlib_RELPATH = ti/drv/stw_lld/fatlib
stw_fatlib_PATH = $(PDK_STW_FATLIB_COMP_PATH)
stw_fatlib_LIBNAME = stw_fatlib
stw_fatlib_LIBPATH = $(PDK_STW_FATLIB_COMP_PATH)/lib
stw_fatlib_MAKEFILE = -fsrc/makefile
export stw_fatlib_MAKEFILE
export stw_fatlib_LIBNAME
export stw_fatlib_LIBPATH
stw_fatlib_BOARD_DEPENDENCY = no
stw_fatlib_CORE_DEPENDENCY = no
export stw_fatlib_COMP_LIST
export stw_fatlib_BOARD_DEPENDENCY
export stw_fatlib_CORE_DEPENDENCY
stw_fatlib_PKG_LIST = stw_fatlib
stw_fatlib_INCLUDE = $(stw_fatlib_PATH)
stw_fatlib_SOCLIST = $(stw_fatlib_default_SOCLIST)
export stw_fatlib_SOCLIST
stw_fatlib_$(SOC)_CORELIST = $(stw_fatlib_default_$(SOC)_CORELIST)
export stw_fatlib_$(SOC)_CORELIST

# FATLIB EDMA LIB
stw_fatlib_edma_COMP_LIST = stw_fatlib_edma
stw_fatlib_edma_RELPATH = ti/drv/stw_lld/fatlib
stw_fatlib_edma_PATH = $(PDK_STW_FATLIB_COMP_PATH)
stw_fatlib_edma_LIBNAME = stw_fatlib_edma
stw_fatlib_edma_LIBPATH = $(PDK_STW_FATLIB_COMP_PATH)/lib
stw_fatlib_edma_MAKEFILE = -ffatlib_edma/makefile
export stw_fatlib_edma_MAKEFILE
export stw_fatlib_edma_LIBNAME
export stw_fatlib_edma_LIBPATH
stw_fatlib_edma_BOARD_DEPENDENCY = no
stw_fatlib_edma_CORE_DEPENDENCY = no
export stw_fatlib_edma_COMP_LIST
export stw_fatlib_edma_BOARD_DEPENDENCY
export stw_fatlib_edma_CORE_DEPENDENCY
stw_fatlib_edma_PKG_LIST = stw_fatlib_edma
stw_fatlib_edma_INCLUDE = $(stw_fatlib_edma_PATH)
stw_fatlib_edma_SOCLIST = $(stw_fatlib_default_SOCLIST)
export stw_fatlib_edma_SOCLIST
stw_fatlib_edma_$(SOC)_CORELIST = $(stw_fatlib_default_$(SOC)_CORELIST)
export stw_fatlib_edma_$(SOC)_CORELIST

export stw_fatlib_LIB_LIST
export stw_fatlib_EXAMPLE_LIST

stw_fatlib_component_make_include := 1
endif
