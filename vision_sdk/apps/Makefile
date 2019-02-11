
MODULE_NAME = app_libs

$(MODULE_NAME)_PLATFORM_DEPENDENCY = yes
$(MODULE_NAME)_CORE_DEPENDENCY = yes

INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk ipc vision_sdk fc xdais edma \
	starterware_hal fat_lib utils_platform starterware_pm_hal \
	starterware_pm_lib links_fw links_fw_rtos

ifeq ($(OPENVX_INCLUDE),yes)
INCLUDE_EXTERNAL_INTERFACES += openvx
endif

MODULE_SRC_BASE_PATH := $($(MAKEAPPNAME)_PATH)/src/

# List all the components required by the application
COMP_LIST_$(CORE) = bios xdc ipc pdk fc vision_sdk

CFLAGS_LOCAL_$(CORE) = $(vision_sdk_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON =
SRCS_tda2xx =
CFLAGS_LOCAL_COMMON = $(vision_sdk_CFLAGS)

include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk
include $($(MAKEAPPNAME)_PATH)/configs/autorules_footer_cfg.mk

ifeq ($(MAKECONFIG), $(filter $(MAKECONFIG), tda3xx_evm_bios_iss tda3xx_rvp_bios_iss tda2px_evm_bios_iss))
USECASE = $(if $(call CHECK_YES, $($(uc))), $(MODULE_SRC_BASE_PATH)/rtos/iss_usecases/$(subst UC_,,$(uc))/SRC_FILES.MK)
USECASES = $(foreach uc,$(ISS_UC_LIST),$(USECASE))
else
USECASE = $(if $(call CHECK_YES, $($(uc))), $(MODULE_SRC_BASE_PATH)/rtos/usecases/$(subst UC_,,$(uc))/SRC_FILES.MK)
USECASES = $(foreach uc,$(UC_LIST),$(USECASE))
endif

-include $(MODULE_SRC_BASE_PATH)/rtos/common/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/board/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/grpxSrc/SRC_FILES.MK
ifeq ($(AUTOSAR_APP), yes)
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/autosar_ipcOut/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/autosar_ipcIn/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/mcal/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/autosar_mcal_testApp/SRC_FILES.MK
endif
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/split/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/link_stats_monitor/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/devices/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/display_multi_pipe/SRC_FILES.MK
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/devcontrol/SRC_FILES.MK
ifeq ($(EARLY_USECASE_ENABLE), yes)
-include $(USECASES)
-include $(MODULE_SRC_BASE_PATH)/rtos/usecases/common/SRC_FILES.MK
endif
ifeq ($(A15_TARGET_OS), Bios)
-include $(MODULE_SRC_BASE_PATH)/rtos/usecases/common/SRC_FILES.MK
-include $(USECASES)
endif
ifeq ($(ROBUST_RVC_INCLUDE), yes)
-include $(MODULE_SRC_BASE_PATH)/rtos/usecases/common/SRC_FILES.MK
include $(USECASES)
endif

ifneq ($(RADAR_ONLY),yes)
-include $(MODULE_SRC_BASE_PATH)/rtos/common_srv/SRC_FILES.MK
endif

ifeq ($(DATA_VIS_INCLUDE),yes)
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/data_vis/SRC_FILES.MK
endif

ifeq ($(ULTRASONIC_INCLUDE),yes)
-include $(MODULE_SRC_BASE_PATH)/rtos/modules/ultrasonic_capture/SRC_FILES.MK
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
-include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
