
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_single_cam_view

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_lvdsVipSingleCam_Display_priv.c \
        chains_lvdsVipSingleCam_Display.c
