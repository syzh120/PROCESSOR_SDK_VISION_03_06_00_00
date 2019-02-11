
include $(vision_sdk_PATH)/apps/configs/cfg.mk

RADAR_ALG = $(if $(call CHECK_YES, $($(alg))), $(vision_sdk_PATH)/apps/src/rtos/radar/src/alg_plugins/$(subst ALG_,,$(alg))/SRC_FILES.MK)
RADAR_ALGS = $(foreach alg,$(RADAR_ALG_LIST),$(RADAR_ALG))

RADAR_USECASE = $(if $(call CHECK_YES, $($(uc))), $(vision_sdk_PATH)/apps/src/rtos/radar/src/usecases/$(subst UC_,,$(uc))/SRC_FILES.MK)
RADAR_USECASES = $(foreach uc,$(RADAR_UC_LIST),$(RADAR_USECASE))

RADAR_ALG_FXN = $(if $(call CHECK_YES, $($(alg))), $(vision_sdk_PATH)/apps/src/rtos/radar/src/alg_plugins/alg_fxns/$(subst ALG_FXN_,,$(alg))/SRC_FILES.MK)
RADAR_ALG_FXNS = $(foreach alg,$(RADAR_ALG_FXN_LIST),$(RADAR_ALG_FXN))

include $(RADAR_ALGS)
include $(RADAR_USECASES)
include $(RADAR_ALG_FXNS)
include $(vision_sdk_PATH)/apps/src/rtos/radar/src/alg_plugins/alg_fxns/common/SRC_FILES.mk

SRCDIR += $(vision_sdk_PATH)/apps/src/rtos/radar/src/common

ifeq ($(RADAR_ONLY), yes)
SRCS_ipu1_0 += \
    chains_main_bios_radar.c  \
    chains_main_bios_settings_radar.c  \
    chains_common.c
endif

ifeq ($(A15_TARGET_OS), Linux)

ifneq ($(ROBUST_RVC_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
    app_ctrl_radar.c \
    chains_common_ar12xx.c \
    chains_common_sample_ar12xx_config.c \
    chains_common_cascade_ar12xx_config_mimo.c \
    chains_common_cascade_ar12xx_config_bf.c \
    chains_common_cascade_fpga.c \
    chains_common_radar.c \
    chains_radar_util_read_params.c

endif

else

SRCS_ipu1_0 += \
    chains_radar_main.c \
    chains_common_radar.c \
    chains_common_sample_ar12xx_config.c \
    chains_radar_file_io.c \
    chains_radar_util_read_params.c

ifeq ($(SOC), $(filter $(SOC), tda3xx tda2px))
SRCS_ipu1_0 += \
    chains_common_ar12xx.c
endif

ifeq ($(RADAR_BOARD),$(filter $(RADAR_BOARD), TDA2XX_CASCADE_RADAR))
SRCS_ipu1_0 += \
    chains_common_cascade_fpga.c \
    chains_common_cascade_ar12xx_config_mimo.c \
    chains_common_cascade_ar12xx_config_bf.c \
    chains_common_ar12xx.c
endif

endif

INCLUDE_INTERNAL_INTERFACES += radar
INCLUDE_EXTERNAL_INTERFACES += radarLink          \
                               radarFirmware

