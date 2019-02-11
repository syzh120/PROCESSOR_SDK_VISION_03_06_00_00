
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_sparse_optical_flow

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraSparseOpticalFlow_priv.c \
		chains_vipSingleCameraSparseOpticalFlow.c

