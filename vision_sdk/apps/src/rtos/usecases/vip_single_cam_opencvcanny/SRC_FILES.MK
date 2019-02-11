SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_opencvcanny

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCamOpenCVCanny.c \
		chains_vipSingleCamOpenCVCanny_priv.c

