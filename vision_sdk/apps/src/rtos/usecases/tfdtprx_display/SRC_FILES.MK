
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tfdtprx_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_tfdtpRx_Display_priv.c \
		chains_tfdtpRx_Display.c
