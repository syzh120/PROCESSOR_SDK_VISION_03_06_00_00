
SRCS_$(IPU_PRIMARY_CORE) += \
        system_bsp_init.c \
        system_ipu1_0.c \
        systemLink_tsk_ipu1.c \
		
SRCS_ipu1_1 += \
        system_ipu1_1.c \
        systemLink_tsk_ipu1.c

SRCS_$(IPU_SECONDARY_CORE) += \
        system_ipu2.c \
        systemLink_tsk_ipu2.c		
		