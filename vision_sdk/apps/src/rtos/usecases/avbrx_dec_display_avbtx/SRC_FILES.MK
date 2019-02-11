
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/avbrx_dec_display_avbtx

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_avbRx_Dec_Display_AvbTx_priv.c \
        chains_avbRx_Dec_AvbTx_priv.c \
        chains_avbRx_Dec_Display_AvbTx.c


