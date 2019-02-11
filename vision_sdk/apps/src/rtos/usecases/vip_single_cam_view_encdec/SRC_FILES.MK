
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_view_encdec

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCam_EncDec_Display.c \
		chains_vipSingleCam_EncDec_Display_priv.c

