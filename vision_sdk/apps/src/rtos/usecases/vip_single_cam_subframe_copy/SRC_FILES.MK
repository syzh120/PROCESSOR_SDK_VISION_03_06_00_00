
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_subframe_copy

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraSubFrameCopy.c \
		chains_vipSingleCameraSubFrameCopy_priv.c

