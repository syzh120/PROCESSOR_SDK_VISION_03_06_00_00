
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_sfm

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraSfm_priv.c \
		chains_vipSingleCameraSfm.c

