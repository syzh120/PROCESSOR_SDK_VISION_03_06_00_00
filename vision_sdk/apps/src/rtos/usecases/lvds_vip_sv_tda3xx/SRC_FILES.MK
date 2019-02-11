
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_sv_tda3xx

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_lvdsVipSurroundView_priv.c \
		chains_lvdsVipSurroundView.c
