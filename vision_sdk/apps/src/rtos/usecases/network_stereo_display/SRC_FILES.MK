
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/network_stereo_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_networkStereoDisplay.c \
		chains_networkStereoDisplay_priv.c
