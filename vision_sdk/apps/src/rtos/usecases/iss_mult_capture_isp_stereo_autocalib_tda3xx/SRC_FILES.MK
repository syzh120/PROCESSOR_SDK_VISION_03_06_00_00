
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_stereo_autocalib_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_stereoAutoCalib_tda3x_priv.c \
        chains_stereoAutoCalib_tda3x.c 


