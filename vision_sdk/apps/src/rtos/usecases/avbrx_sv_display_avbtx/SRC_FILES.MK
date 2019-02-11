
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/avbrx_sv_display_avbtx

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_avbRxSrvAvbTx_priv.c \
        chains_avbRxSrvDisplay_priv.c \
        chains_avbRxSrv_Display_AvbTx.c

