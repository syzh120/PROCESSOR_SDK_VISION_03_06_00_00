# File: stw_platform_component.mk
#       This file is component include make file of STW Platform library.
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
ifeq ($(stw_platform_component_make_include), )

stw_platform_default_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
stw_platform_default_tda2xx_CORELIST = a15_0 ipu1_0 c66x arp32_1
stw_platform_default_tda2px_CORELIST = a15_0 ipu1_0 c66x arp32_1
stw_platform_default_tda2ex_CORELIST = a15_0 ipu1_0 c66x
stw_platform_default_tda3xx_CORELIST = ipu1_0 c66x arp32_1
stw_platform_default_dra72x_CORELIST = a15_0 ipu1_0 c66x
stw_platform_default_dra75x_CORELIST = a15_0 ipu1_0 c66x arp32_1
stw_platform_default_dra78x_CORELIST = ipu1_0 c66x arp32_1

############################
# stw_platform package
# List of components included under stw_platform
# The components included here are built and will be part of stw_platform lib
############################
stw_platform_LIB_LIST = stw_platform

############################
# stw_platform examples
# List of examples under stw_platform (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
stw_platform_EXAMPLE_LIST =

#
# PLATFORM Modules
#

# PLATFORM LIB
stw_platform_COMP_LIST = stw_platform
stw_platform_RELPATH = ti/drv/stw_lld/platform
stw_platform_PATH = $(PDK_STW_PLATFORM_COMP_PATH)
stw_platform_LIBNAME = stw_platform
stw_platform_LIBPATH = $(PDK_STW_PLATFORM_COMP_PATH)/lib
stw_platform_MAKEFILE = -fsrc/makefile
export stw_platform_MAKEFILE
export stw_platform_LIBNAME
export stw_platform_LIBPATH
stw_platform_BOARD_DEPENDENCY = no
stw_platform_CORE_DEPENDENCY = no
export stw_platform_COMP_LIST
export stw_platform_BOARD_DEPENDENCY
export stw_platform_CORE_DEPENDENCY
stw_platform_PKG_LIST = stw_platform
stw_platform_INCLUDE = $(stw_platform_PATH)
stw_platform_SOCLIST = $(stw_platform_default_SOCLIST)
export stw_platform_SOCLIST
stw_platform_$(SOC)_CORELIST = $(stw_platform_default_$(SOC)_CORELIST)
export stw_platform_$(SOC)_CORELIST

export stw_platform_LIB_LIST
export stw_platform_EXAMPLE_LIST

stw_platform_component_make_include := 1
endif
