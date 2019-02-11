
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_multi_cam_view_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_lvdsVipMultiCam_Display_tda3xx_priv.c \
		chains_lvdsVipMultiCam_Display_tda3xx.c

