
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_dewarp_stereo_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_issMultCaptIspDeWarp_Stereo_priv.c \
        chains_issMultCaptIspDeWarp_Stereo.c \
        chains_issMultCaptIspDeWarp_Stereo_Media.c