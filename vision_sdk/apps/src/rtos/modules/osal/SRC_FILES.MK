
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/osal

OSAL_SRCS = \
		chains_common_osal.c
 

SRCS_$(IPU_PRIMARY_CORE) += $(OSAL_SRCS)
SRCS_a15_0 += $(OSAL_SRCS)


