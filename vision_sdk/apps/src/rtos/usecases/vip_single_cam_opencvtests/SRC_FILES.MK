SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_opencvtests

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCamOpenCVTests.c \
		chains_vipSingleCamOpenCVTests_priv.c

