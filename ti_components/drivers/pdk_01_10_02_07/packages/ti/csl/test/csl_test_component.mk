# File: csl_test_component.mk
#       This file is component include make file of STW unit test.
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
ifeq ($(csl_test_component_make_include), )

csl_test_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
csl_test_default_tda2xx_CORELIST = a15_0
csl_test_default_tda2px_CORELIST = a15_0
csl_test_default_tda2ex_CORELIST = a15_0
csl_test_default_tda3xx_CORELIST = ipu1_0

############################
# csl_test package
# List of components included under csl_test
# The components included here are built and will be part of csl_test lib
############################
csl_test_LIB_LIST =

############################
# csl_test examples
# List of examples under csl_test (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
csl_test_EXAMPLE_LIST =

# MCAN unit test app
csl_mcan_unit_test_app_COMP_LIST = csl_mcan_unit_test_app
csl_mcan_unit_test_app_RELPATH = ti/csl/test/mcanUt
csl_mcan_unit_test_app_PATH = $(PDK_CSL_COMP_PATH)/test/mcanUt
csl_mcan_unit_test_app_BOARD_DEPENDENCY = yes
csl_mcan_unit_test_app_CORE_DEPENDENCY = yes
export csl_mcan_unit_test_app_COMP_LIST
export csl_mcan_unit_test_app_BOARD_DEPENDENCY
export csl_mcan_unit_test_app_CORE_DEPENDENCY
csl_mcan_unit_test_app_PKG_LIST = csl_mcan_unit_test_app
csl_mcan_unit_test_app_INCLUDE = $(csl_mcan_unit_test_app_PATH)
csl_mcan_unit_test_app_BOARDLIST = tda3xx-evm tda2px-evm
export csl_mcan_unit_test_app_BOARDLIST
csl_mcan_unit_test_app_$(SOC)_CORELIST = ipu1_0
export csl_mcan_unit_test_app_$(SOC)_CORELIST
csl_test_EXAMPLE_LIST += csl_mcan_unit_test_app
csl_mcan_unit_test_app_SBL_APPIMAGEGEN = yes
export csl_mcan_unit_test_app_SBL_APPIMAGEGEN

export csl_test_LIB_LIST
export csl_test_EXAMPLE_LIST

csl_test_component_make_include := 1
endif
