
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_sv_standalone

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_lvdsVipSurroundViewStandalone_priv.c \
		chains_lvdsVipSurroundViewStandalone.c

