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

SOC_LIST_ALL = tda2xx tda2px tda2ex tda3xx
CORE_LIST_ALL = arp32_1 arp32_2 arp32_3 arp32_4 ipu1_0 ipu1_1 ipu2 c66xdsp_1 c66xdsp_2
ifeq ($(A15_TARGET_OS),Bios)
CORE_LIST_ALL += a15_0
endif
# List of the linksfw libs to build
linksfw_LIB_LIST =

# include all the components present
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/algorithm/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/avb_rx/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/avb_tx/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/dup/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/gate/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/ipcIn/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/ipcOut/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/merge/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/null/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/network_tx/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/network_rx/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/nullSrc/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/select/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/sync/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/tfdtp_rx/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/display/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/display_ctrl/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/iss_capture/component.mk
ifneq ($(RADAR_ONLY),yes)
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/iss_m2misp/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/iss_m2msimcop/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/iss_m2mresizer/component.mk
endif
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/iva/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/vip_capture/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/vpe/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/dss_m2mwb/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_common/system/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_dsp/system/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_eve/system/component.mk
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/system/component.mk
ifeq ($(A15_TARGET_OS),Bios)
-include $(vision_sdk_PATH)/links_fw/src/rtos/links_a15/system/component.mk
endif

export linksfw_LIB_LIST
export SOC_LIST_ALL
export CORE_LIST_ALL
