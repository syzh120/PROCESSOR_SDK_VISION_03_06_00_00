SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/mcal
INCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/mcal/include

SRCS_$(IPU_SECONDARY_CORE) += mcal_tx.c mcal_rx.c mcal_ipc_lib.c