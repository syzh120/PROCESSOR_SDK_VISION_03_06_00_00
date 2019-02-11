
MODULE_NAME = app_alg_plugins

app_alg_plugins_PLATFORM_DEPENDENCY = yes
app_alg_plugins_CORE_DEPENDENCY = no

INCDIR = $(MODULE_SRC_BASE_PATH)/commonutils/ \
		 $($(MAKEAPPNAME)_PATH)

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc ipc pdk xdais vision_sdk \
								edma vlib evealg dmautils \
								links_fw links_fw_rtos

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES =

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON =
SRCS_tda2xx =
CFLAGS_LOCAL_COMMON = $(vision_sdk_CFLAGS)

MODULE_SRC_BASE_PATH := $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins

include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk

SRCDIR  =

ALG = $(if $(call CHECK_YES, $($(alg))), $(MODULE_SRC_BASE_PATH)/$(subst ALG_,,$(alg))/SRC_FILES.MK)
ALGS = $(foreach alg,$(ALG_LIST),$(ALG))

include $(ALGS)

include $(MODULE_SRC_BASE_PATH)/common/SRC_FILES.MK

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
