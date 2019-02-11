
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_multi_cam_view

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_lvdsVipMultiCam_Display_priv.c \
        chains_lvdsVipMultiCam_Display.c
