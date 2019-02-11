
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_dewarp_3dsv_rearview_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_issMultCaptIspDeWarpRearView3dSv_Display.c \
		chains_issMultCaptIspDeWarpRearView3dSv_priv.c \
		chains_issMultCaptIspDeWarpRearView3dSv_grpx_priv.c \
		chains_issMultCaptIspDeWarpRearView3dSv_Media.c
