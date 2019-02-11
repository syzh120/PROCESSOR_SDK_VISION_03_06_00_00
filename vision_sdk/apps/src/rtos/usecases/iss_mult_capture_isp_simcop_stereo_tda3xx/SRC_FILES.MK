
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_simcop_stereo_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_issMultCaptIspSimcop_Stereo_priv.c \
        chains_issMultCaptIspSimcop_Stereo.c
