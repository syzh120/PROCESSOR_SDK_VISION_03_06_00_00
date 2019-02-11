
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_lane_detection

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraLaneDetect_priv.c \
		chains_vipSingleCameraLaneDetect.c

