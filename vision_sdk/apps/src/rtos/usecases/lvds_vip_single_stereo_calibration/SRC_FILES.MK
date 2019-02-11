
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_single_stereo_calibration

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_lvdsVipSingleStereoCalibration.c \
		chains_lvdsVipSingleStereoCalibration_priv.c
