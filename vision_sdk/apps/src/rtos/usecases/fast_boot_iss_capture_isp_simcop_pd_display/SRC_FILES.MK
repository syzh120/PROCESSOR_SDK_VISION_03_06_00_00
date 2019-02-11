
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/fast_boot_iss_capture_isp_simcop_pd_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_fastBoot_issIspSimcop_pd_Display.c \
		chains_fastBoot_issIspSimcop_pd_Display_priv.c \
		chains_fastBoot_dspEvePowerDown.c
