
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/iss_monochrome_capt_isp_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_monochrome_issIsp_Display.c \
		chains_monochrome_issIsp_Display_priv.c 
