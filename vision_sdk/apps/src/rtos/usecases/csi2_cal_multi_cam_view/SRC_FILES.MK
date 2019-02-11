
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/csi2_cal_multi_cam_view

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_csi2CalMultiCam.c \
		chains_csi2CalMultiCam_priv.c

