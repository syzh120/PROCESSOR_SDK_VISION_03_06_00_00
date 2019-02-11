
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_capture_isp_simcop_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_issIspSimcop_Display.c \
		chains_issIspSimcop_Display_priv.c 
