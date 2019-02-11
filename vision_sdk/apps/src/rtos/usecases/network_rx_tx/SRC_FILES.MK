
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/network_rx_tx

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_networkRxDisplay.c \
		chains_networkTxCapture.c \
		chains_networkTxMultiCamCapture.c \
		chains_networkTxEncCapture.c \
		chains_networkRxDecDisplay.c \
		chains_networkRxDisplay_priv.c \
		chains_networkTxCapture_priv.c \
		chains_networkTxEncCapture_priv.c \
		chains_networkTxMultiCamCapture_priv.c \
		chains_networkRxDecDisplay_priv.c \
		chains_networkRxTx.c

