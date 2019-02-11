
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_mult_capture_isp_dewarp_stereoplus_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_issMultCaptIspDeWarp_StereoPlus_priv.c \
        chains_issMultCaptIspDeWarp_StereoPlus.c \
        chains_issMultCaptIspDeWarp_StereoPlus_Media.c