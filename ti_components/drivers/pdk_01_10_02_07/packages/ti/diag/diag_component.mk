# File: diag_component.mk
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
ifeq ($(diag_component_make_include), )

diag_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
diag_default_tda2xx_CORELIST = ipu1_0
diag_default_tda2px_CORELIST = ipu1_0
diag_default_tda2ex_CORELIST = ipu1_0
diag_default_tda3xx_CORELIST = ipu1_0

############################
# diag package
# List of components included under diag
# The components included here are built and will be part of diag lib
############################
diag_LIB_LIST = diag

############################
# diag examples
# List of examples under diag (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
diag_EXAMPLE_LIST = diag_ipu_ecc_test

#
# DIAG Modules
#

# DIAG LIB
diag_COMP_LIST = diag
diag_RELPATH = ti/diag
diag_PATH = $(PDK_DIAG_COMP_PATH)
diag_LIBNAME = diag
diag_LIBPATH = $(PDK_DIAG_COMP_PATH)/lib
diag_MAKEFILE = -fsrc/makefile
export diag_MAKEFILE
export diag_LIBNAME
export diag_LIBPATH
diag_BOARD_DEPENDENCY = no
diag_CORE_DEPENDENCY = no
export diag_COMP_LIST
export diag_BOARD_DEPENDENCY
export diag_CORE_DEPENDENCY
diag_PKG_LIST = diag
diag_INCLUDE = $(diag_PATH)
diag_SOCLIST = $(diag_default_SOCLIST)
export diag_SOCLIST
diag_$(SOC)_CORELIST = $(diag_default_$(SOC)_CORELIST)
export diag_$(SOC)_CORELIST

#
# DIAG Examples
#
# diag lib ipu ecc Test
diag_ipu_ecc_test_COMP_LIST = diag_ipu_ecc_test
diag_ipu_ecc_test_RELPATH = ti/diag/examples/diag_ipu_ecc_test
diag_ipu_ecc_test_PATH = $(PDK_DIAG_COMP_PATH)/examples/diag_ipu_ecc_test
diag_ipu_ecc_test_BOARD_DEPENDENCY = no
diag_ipu_ecc_test_CORE_DEPENDENCY = yes
diag_ipu_ecc_test_XDC_CONFIGURO = no
export diag_ipu_ecc_test_COMP_LIST
export diag_ipu_ecc_test_BOARD_DEPENDENCY
export diag_ipu_ecc_test_CORE_DEPENDENCY
export diag_ipu_ecc_test_XDC_CONFIGURO
diag_ipu_ecc_test_PKG_LIST = diag_ipu_ecc_test
diag_ipu_ecc_test_INCLUDE = $(diag_ipu_ecc_test_PATH)
diag_ipu_ecc_test_SOCLIST = tda3xx
export diag_ipu_ecc_test_SOCLIST
diag_ipu_ecc_test_$(SOC)_CORELIST = $(diag_default_$(SOC)_CORELIST)
export diag_ipu_ecc_test_$(SOC)_CORELIST
diag_ipu_ecc_test_SBL_APPIMAGEGEN = yes
export diag_ipu_ecc_test_SBL_APPIMAGEGEN

export diag_LIB_LIST
export diag_EXAMPLE_LIST

diag_component_make_include := 1
endif
