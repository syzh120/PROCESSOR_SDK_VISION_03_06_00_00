
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/ov490_vip_sv_standalone

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_ov490VipSurroundViewStandalone_priv.c \
		chains_ov490VipSurroundViewStandalone.c

