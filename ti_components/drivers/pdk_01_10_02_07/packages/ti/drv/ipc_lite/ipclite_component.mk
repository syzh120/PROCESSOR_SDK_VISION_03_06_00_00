# File: ipclite_component.mk
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
ifeq ($(ipclite_component_make_include), )

#default values
INCLUDE_SYSBIOS ?= no

ipc_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
ipc_default_tda2xx_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 c66xdsp_1 c66xdsp_2 arp32_1 arp32_2 arp32_3 arp32_4
ipc_default_tda2px_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 c66xdsp_1 c66xdsp_2 arp32_1 arp32_2
ipc_default_tda2ex_CORELIST = a15_0 ipu1_0 ipu1_1 ipu2_0 c66xdsp_1
ipc_default_tda3xx_CORELIST = ipu1_0 ipu1_1 c66xdsp_1 c66xdsp_2 arp32_1

IPCLIB_CFLAGS=
ifeq ($(INCLUDE_SYSBIOS), yes)
IPCLIB_CFLAGS+=-DSYSBIOS
endif

############################
# ipc package
# List of components included under ipc
# The components included here are built and will be part of ipc lib
############################
ipclite_LIB_LIST = ipc_lib

############################
# ipc examples
# List of examples under ipc (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
ipclite_EXAMPLE_LIST =

#
# IPC Modules
#

# IPC LIB
ipc_lib_COMP_LIST = ipc_lib
ipc_lib_RELPATH = ti/drv/ipc_lite
ipc_lib_PATH = $(PDK_IPCLITE_COMP_PATH)
ipc_lib_LIBNAME = ipc_lib
ipc_lib_LIBPATH = $(PDK_IPCLITE_COMP_PATH)/lib
ipc_lib_MAKEFILE = -fsrc/makefile
export ipc_lib_MAKEFILE
export ipc_lib_LIBNAME
export ipc_lib_LIBPATH
ipc_lib_BOARD_DEPENDENCY = no
ipc_lib_CORE_DEPENDENCY = yes
export ipc_lib_COMP_LIST
export ipc_lib_BOARD_DEPENDENCY
export ipc_lib_CORE_DEPENDENCY
ipc_lib_PKG_LIST = ipc_lib
ipc_lib_INCLUDE = $(ipc_lib_PATH)
ipc_lib_SOCLIST = $(ipc_default_SOCLIST)
export ipc_lib_SOCLIST
ipc_lib_$(SOC)_CORELIST = $(ipc_default_$(SOC)_CORELIST)
export ipc_lib_$(SOC)_CORELIST

#
# IPC Examples
#
# IPC Multicore mailbox Example
ipc_lite_mbx_test_app_COMP_LIST = ipc_lite_mbx_test_app
ipc_lite_mbx_test_app_RELPATH = ti/drv/ipc_lite/examples/ipc_mbx
ipc_lite_mbx_test_app_PATH = $(PDK_IPCLITE_COMP_PATH)/examples/ipc_mbx
ipc_lite_mbx_test_app_BOARD_DEPENDENCY = no
ipc_lite_mbx_test_app_CORE_DEPENDENCY = yes
export ipc_lite_mbx_test_app_COMP_LIST
export ipc_lite_mbx_test_app_BOARD_DEPENDENCY
export ipc_lite_mbx_test_app_CORE_DEPENDENCY
ipc_lite_mbx_test_app_PKG_LIST = ipc_lite_mbx_test_app
ipc_lite_mbx_test_app_INCLUDE = $(ipc_lite_mbx_test_app_PATH)
ipc_lite_mbx_test_app_SOCLIST = $(ipc_default_SOCLIST)
export ipc_lite_mbx_test_app_SOCLIST
ipc_lite_mbx_test_app_$(SOC)_CORELIST = $(ipc_default_$(SOC)_CORELIST)
export ipc_lite_mbx_test_app_$(SOC)_CORELIST
ipclite_EXAMPLE_LIST += ipc_lite_mbx_test_app

export ipclite_LIB_LIST
export ipclite_EXAMPLE_LIST
export IPCLIB_CFLAGS

ipclite_component_make_include := 1
endif
