SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_opencvopencldilation

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCamOpenCVOpenCLDilation.c \
		chains_vipSingleCamOpenCVOpenCLDilation_priv.c

