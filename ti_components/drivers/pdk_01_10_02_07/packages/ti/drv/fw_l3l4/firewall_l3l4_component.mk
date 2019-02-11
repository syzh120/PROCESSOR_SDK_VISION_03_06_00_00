# File: firewall_l3l4_component.mk
#       This file is component include make file of L3/L4 firewall library.
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
ifeq ($(firewall_l3l4_component_make_include), )

firewall_l3l4_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
firewall_l3l4_default_tda2xx_CORELIST = a15_0 ipu1_0 c66x arp32_1
firewall_l3l4_default_tda2px_CORELIST = a15_0 ipu1_0 c66x arp32_1
firewall_l3l4_default_tda2ex_CORELIST = a15_0 c66x ipu1_0
firewall_l3l4_default_tda3xx_CORELIST = ipu1_0 c66x arp32_1
firewall_l3l4_app_default_tda2xx_CORELIST = a15_0 ipu1_0
firewall_l3l4_app_default_tda2px_CORELIST = a15_0 ipu1_0
firewall_l3l4_app_default_tda2ex_CORELIST = a15_0 ipu1_0
firewall_l3l4_app_default_tda3xx_CORELIST = ipu1_0

############################
# firewall_l3l4 package
# List of components included under firewall_l3l4
# The components included here are built and will be part of firewall_l3l4 lib
############################
firewall_l3l4_LIB_LIST = firewall_l3l4

############################
# firewall_l3l4 examples
# List of examples under firewall_l3l4 (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
firewall_l3l4_EXAMPLE_LIST =

#
# L3/L4 Firewall Modules
#

# L3/L4 Firewall LIB
firewall_l3l4_COMP_LIST = firewall_l3l4
firewall_l3l4_RELPATH = ti/drv/fw_l3l4
firewall_l3l4_PATH = $(PDK_FIREWALL_L3L4_COMP_PATH)
firewall_l3l4_LIBNAME = firewall_l3l4
firewall_l3l4_LIBPATH = $(PDK_FIREWALL_L3L4_COMP_PATH)/lib
firewall_l3l4_MAKEFILE = -fsrc/makefile
export firewall_l3l4_MAKEFILE
export firewall_l3l4_LIBNAME
export firewall_l3l4_LIBPATH
firewall_l3l4_BOARD_DEPENDENCY = no
firewall_l3l4_CORE_DEPENDENCY = no
export firewall_l3l4_COMP_LIST
export firewall_l3l4_BOARD_DEPENDENCY
export firewall_l3l4_CORE_DEPENDENCY
firewall_l3l4_PKG_LIST = firewall_l3l4
firewall_l3l4_INCLUDE = $(firewall_l3l4_PATH)
firewall_l3l4_SOCLIST = $(firewall_l3l4_default_SOCLIST)
export firewall_l3l4_SOCLIST
firewall_l3l4_$(SOC)_CORELIST = $(firewall_l3l4_default_$(SOC)_CORELIST)
export firewall_l3l4_$(SOC)_CORELIST

#
# Firewall Examples
#
# L4 Firewall Example
drv_firewall_l4_test_app_COMP_LIST = drv_firewall_l4_test_app
drv_firewall_l4_test_app_RELPATH = ti/drv/fw_l3l4/examples/l4_firewall
drv_firewall_l4_test_app_PATH = $(PDK_FIREWALL_L3L4_COMP_PATH)/examples/l4_firewall
drv_firewall_l4_test_app_BOARD_DEPENDENCY = no
drv_firewall_l4_test_app_CORE_DEPENDENCY = yes
export drv_firewall_l4_test_app_COMP_LIST
export drv_firewall_l4_test_app_BOARD_DEPENDENCY
export drv_firewall_l4_test_app_CORE_DEPENDENCY
drv_firewall_l4_test_app_PKG_LIST = drv_firewall_l4_test_app
drv_firewall_l4_test_app_INCLUDE = $(drv_firewall_l4_test_app_PATH)
drv_firewall_l4_test_app_SOCLIST = $(firewall_l3l4_default_SOCLIST)
export drv_firewall_l4_test_app_SOCLIST
drv_firewall_l4_test_app_$(SOC)_CORELIST = $(firewall_l3l4_app_default_$(SOC)_CORELIST)
export drv_firewall_l4_test_app_$(SOC)_CORELIST
firewall_l3l4_EXAMPLE_LIST += drv_firewall_l4_test_app

#
# Firewall Examples
#
# L3 Firewall Example
drv_firewall_l3_test_app_COMP_LIST = drv_firewall_l3_test_app
drv_firewall_l3_test_app_RELPATH = ti/drv/fw_l3l4/examples/l3_firewall
drv_firewall_l3_test_app_PATH = $(PDK_FIREWALL_L3L4_COMP_PATH)/examples/l3_firewall
drv_firewall_l3_test_app_BOARD_DEPENDENCY = no
drv_firewall_l3_test_app_CORE_DEPENDENCY = yes
export drv_firewall_l3_test_app_COMP_LIST
export drv_firewall_l3_test_app_BOARD_DEPENDENCY
export drv_firewall_l3_test_app_CORE_DEPENDENCY
drv_firewall_l3_test_app_PKG_LIST = drv_firewall_l3_test_app
drv_firewall_l3_test_app_INCLUDE = $(drv_firewall_l3_test_app_PATH)
drv_firewall_l3_test_app_SOCLIST = $(firewall_l3l4_default_SOCLIST)
export drv_firewall_l3_test_app_SOCLIST
drv_firewall_l3_test_app_$(SOC)_CORELIST = $(firewall_l3l4_app_default_$(SOC)_CORELIST)
export drv_firewall_l3_test_app_$(SOC)_CORELIST
firewall_l3l4_EXAMPLE_LIST += drv_firewall_l3_test_app

# L3 Firewall  MreqDomain Setup Example: A15
drv_l3_firewall_mreqDomain_test_app_COMP_LIST = drv_l3_firewall_mreqDomain_test_app
drv_l3_firewall_mreqDomain_test_app_RELPATH = ti/drv/fw_l3l4/examples/l3_firewall_mreqDomain
drv_l3_firewall_mreqDomain_test_app_PATH = $(PDK_FIREWALL_L3L4_COMP_PATH)/examples/l3_firewall_mreqDomain
drv_l3_firewall_mreqDomain_test_app_BOARD_DEPENDENCY = no
drv_l3_firewall_mreqDomain_test_app_CORE_DEPENDENCY = yes
export drv_l3_firewall_mreqDomain_test_app_COMP_LIST
export drv_l3_firewall_mreqDomain_test_app_BOARD_DEPENDENCY
export drv_l3_firewall_mreqDomain_test_app_CORE_DEPENDENCY
drv_l3_firewall_mreqDomain_test_app_PKG_LIST = drv_l3_firewall_mreqDomain_test_app
drv_l3_firewall_mreqDomain_test_app_INCLUDE = $(drv_l3_firewall_mreqDomain_test_app_PATH)
drv_l3_firewall_mreqDomain_test_app_SOCLIST = tda2px
export drv_l3_firewall_mreqDomain_test_app_SOCLIST
drv_l3_firewall_mreqDomain_test_app_$(SOC)_CORELIST = a15_0 arp32_1
export drv_l3_firewall_mreqDomain_test_app_$(SOC)_CORELIST
firewall_l3l4_EXAMPLE_LIST += drv_l3_firewall_mreqDomain_test_app

export firewall_l3l4_LIB_LIST
export firewall_l3l4_EXAMPLE_LIST

firewall_l3l4_component_make_include := 1
endif
