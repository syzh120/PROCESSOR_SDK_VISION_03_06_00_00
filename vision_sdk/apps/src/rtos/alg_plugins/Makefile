
MODULE_NAME = app_alg_plugins

app_alg_plugins_PLATFORM_DEPENDENCY = yes
app_alg_plugins_CORE_DEPENDENCY = no

INCDIR = $(MODULE_SRC_BASE_PATH)/commonutils/

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc ipc pdk vision_sdk fc xdais jpegvdec \
								jpegvenc edma vlib lane_detect object_detect \
								scene_obstruction_detect object_classification \
								evealg stereo_postprocess gpe sfm clr fcw tidl dmautils \
								tiop links_fw links_fw_rtos

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES =

ifeq ($(OPENCL_INCLUDE),yes)
INCLUDE_INTERNAL_INTERFACES += opencl
endif

ifeq ($(BUILD_ADAM_CAR),yes)
INCLUDE_EXTERNAL_INTERFACES += adam_car
endif

ifeq ($(DCAN_INCLUDE),yes)
INCLUDE_EXTERNAL_INTERFACES += sys_config uartConsole utils_platform
endif

ifeq ($(ENABLE_OPENCV),yes)
INCLUDE_INTERNAL_INTERFACES += opencv
endif

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

OPENCL_SRCDIR += $(foreach alg, $(ALGS), $(subst SRC_FILES.MK,,$(abspath $(alg))))
KERNEL_DIRS = $(foreach dir, $(OPENCL_SRCDIR), $(wildcard $(dir)kernel))

ifeq ($(ROBUST_RVC_INCLUDE),yes)
include $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/swcrc/SRC_FILES.MK
include $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/rvcDiags/SRC_FILES.MK
endif

include $($(MAKEAPPNAME)_PATH)/src/rtos/radar/SRC_FILES.MK
include $($(MAKEAPPNAME)_PATH)/src/rtos/draw2d/SRC_FILES.MK
include $($(MAKEAPPNAME)_PATH)/src/rtos/modules/network_ctrl/SRC_FILES.MK
include $($(MAKEAPPNAME)_PATH)/src/rtos/modules/network_cons/SRC_FILES.MK
include $($(MAKEAPPNAME)_PATH)/src/rtos/modules/osal/SRC_FILES.MK
ifneq ($(RADAR_ONLY),yes)
include $($(MAKEAPPNAME)_PATH)/src/rtos/modules/lz4CompDecomp/SRC_FILES.MK
endif
include $(MODULE_SRC_BASE_PATH)/common/SRC_FILES.MK

ifeq ($(ALG_surroundview),yes)
include $(MODULE_SRC_BASE_PATH)/commonutils/SRC_FILES.MK
endif

ifeq ($(DCAN_INCLUDE),yes)
include $($(MAKEAPPNAME)_PATH)/src/rtos/modules/dcan/SRC_FILES.MK
endif

ifeq ($(BUILD_ADAM_CAR),yes)
include $($(MAKEAPPNAME)_PATH)/src/rtos/adam_car/SRC_FILES.MK
INCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/adam_car/
endif

ifeq ($(RTI_INCLUDE),yes)
INCLUDE_EXTERNAL_INTERFACES += sys_config
include $($(MAKEAPPNAME)_PATH)/src/rtos/modules/rti/SRC_FILES.MK
endif

ifeq ($(OPENVX_INCLUDE),yes)
INCLUDE_EXTERNAL_INTERFACES += openvx
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

$(KERNEL_DIRS):
	cp $(vision_sdk_PATH)/binaries/apps/tda2xx_evm_bios_opencx/vision_sdk/bin/tda2xx-evm/dsp.syms ../opencl/usr/share/ti/opencl/
	cp $(vision_sdk_PATH)/binaries/apps/tda2xx_evm_bios_opencx/vision_sdk/bin/tda2xx-evm/dsp_syms.obj ../opencl/usr/share/ti/opencl/
	$(MAKE) -C$@

opencl_build: $(KERNEL_DIRS)

# Nothing beyond this point
