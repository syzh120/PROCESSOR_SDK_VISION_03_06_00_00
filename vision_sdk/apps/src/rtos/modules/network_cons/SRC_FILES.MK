
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/network_cons

NETWORK_CONS_SRCS = \
		network_cons_tsk.c \
		network_cons_ipc.c 

SRCS_$(IPU_PRIMARY_CORE) += $(NETWORK_CONS_SRCS)
SRCS_a15_0 += $(NETWORK_CONS_SRCS)
		

