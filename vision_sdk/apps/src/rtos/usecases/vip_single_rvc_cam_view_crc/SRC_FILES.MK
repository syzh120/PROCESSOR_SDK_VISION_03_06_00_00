SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_rvc_cam_view_crc

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleRvcCamCrc_Display.c \
		chains_vipSingleRvcCamCrc_Display_priv.c
