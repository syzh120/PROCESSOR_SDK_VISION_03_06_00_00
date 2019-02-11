
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_2d_3d_sv_tda3x

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_issMultCaptIsp2d3dSv_Display.c \
		chains_issMultCaptIsp2d3dSv_priv.c \
		chains_issMultCaptIsp2d3dSv_Media.c 
