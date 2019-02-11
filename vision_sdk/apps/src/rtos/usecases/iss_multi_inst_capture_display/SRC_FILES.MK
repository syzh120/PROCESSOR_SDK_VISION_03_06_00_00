
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_multi_inst_capture_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_issMultiInstCapture_Display.c \
		chains_issMultiInstCapture_Display_priv.c
