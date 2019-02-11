
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/split

SRCS_$(IPU_PRIMARY_CORE) += \
		splitLink_tsk.c \
		splitLink_tsk_create_multi_mbx.c \
		splitLink_tsk_create_single_mbx.c
