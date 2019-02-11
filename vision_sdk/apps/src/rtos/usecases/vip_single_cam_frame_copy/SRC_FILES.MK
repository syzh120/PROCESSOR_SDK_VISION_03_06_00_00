
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_frame_copy

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraFrameCopy.c \
		chains_vipSingleCameraFrameCopy_priv.c

