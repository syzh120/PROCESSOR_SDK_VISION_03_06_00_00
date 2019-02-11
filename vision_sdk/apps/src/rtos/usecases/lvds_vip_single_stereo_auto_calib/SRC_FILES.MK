
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_single_stereo_auto_calib

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_lvdsVipSingleStereoAutoCalib.c \
        chains_lvdsVipSingleStereoAutoCalib_priv.c
