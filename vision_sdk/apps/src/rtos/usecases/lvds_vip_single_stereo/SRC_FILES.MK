
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_single_stereo

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_lvdsVipSingleStereo.c \
        chains_lvdsVipSingleStereo_priv.c
