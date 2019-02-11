
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_8_cam_view

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_lvdsVip8Cam_Display_priv.c \
        chains_lvdsVip8Cam_Display.c
