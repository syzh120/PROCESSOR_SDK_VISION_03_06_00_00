
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_view

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCam_Display.c \
		chains_vipSingleCam_Display_priv.c

