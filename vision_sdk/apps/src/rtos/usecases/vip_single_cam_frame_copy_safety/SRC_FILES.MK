
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_frame_copy_safety

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraSafeFrameCopy.c \
		chains_vipSingleCameraSafeFrameCopy_priv.c

