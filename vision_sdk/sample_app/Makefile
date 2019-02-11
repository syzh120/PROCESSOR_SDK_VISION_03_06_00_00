
MODULE_NAME = sample_app_libs

$(MODULE_NAME)_PLATFORM_DEPENDENCY = yes
$(MODULE_NAME)_CORE_DEPENDENCY = yes

INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk ipc vision_sdk fc xdais edma \
	starterware_hal fat_lib utils_platform starterware_pm_hal \
	starterware_pm_lib links_fw links_fw_rtos

MODULE_SRC_BASE_PATH := $($(MAKEAPPNAME)_PATH)/src/

# List all the components required by the application
COMP_LIST_$(CORE) = bios xdc ipc pdk fc vision_sdk

CFLAGS_LOCAL_$(CORE) = $(vision_sdk_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON =
SRCS_tda2xx =
CFLAGS_LOCAL_COMMON = $(vision_sdk_CFLAGS)

include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk

USECASE = $(if $(call CHECK_YES, $($(uc))), $(MODULE_SRC_BASE_PATH)/rtos/usecases/$(subst UC_,,$(uc))/SRC_FILES.MK)
USECASES = $(foreach uc,$(UC_LIST),$(USECASE))

include $(MODULE_SRC_BASE_PATH)/common/SRC_FILES.MK
include $(MODULE_SRC_BASE_PATH)/rtos/modules/link_stats_monitor/SRC_FILES.MK
ifeq ($(A15_TARGET_OS), Bios)
include $(MODULE_SRC_BASE_PATH)/rtos/chains_common/SRC_FILES.MK
include $(USECASES)
endif
# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
