# File: linksfw_component.mk
#       This file is component include make file of links framework libraries.
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

SOC_LIST_ALL = tda2xx tda2px tda2ex
CORE_LIST_ALL = a15_0

# List of the linksfw libs to build
linksfw_LIB_LIST =

# include all the components present
ifeq ($(BUILD_INFOADAS),yes)
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/ep/component.mk
endif
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/algorithm/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/dup/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/gate/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/ipcIn/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/ipcOut/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/merge/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/nullSrc/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/null/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/select/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/sgxFrmcpy/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/sync/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/dispDistSrc/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/utils/multiproc/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/utils/network/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/system/component.mk
-include $(vision_sdk_PATH)/links_fw/src/hlos/osa/src/component.mk


export linksfw_LIB_LIST
export SOC_LIST_ALL
export CORE_LIST_ALL
