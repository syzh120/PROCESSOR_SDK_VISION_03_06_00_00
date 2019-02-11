
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/display_multi_pipe

SRCS_$(IPU_PRIMARY_CORE) += \
		displayMultiPipe_tsk.c \
		displayMultiPipe_drv.c
