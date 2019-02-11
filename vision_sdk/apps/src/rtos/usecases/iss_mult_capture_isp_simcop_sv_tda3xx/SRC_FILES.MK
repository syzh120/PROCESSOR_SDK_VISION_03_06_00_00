
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_simcop_sv_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_issMultCaptIspSimcopSv_Display.c \
		chains_issMultCaptIspSimcopSv_Display_priv.c 
