
SRCS_COMMON += ipcInLink_tsk.c ipcInLink_drv.c

SRCS_MULTI_MBX = ipcInLink_tsk_create_multi_mbx.c
SRCS_SINGLE_MBX = ipcInLink_tsk_create_single_mbx.c

SRCS_arp32_1   += $(SRCS_MULTI_MBX)
SRCS_arp32_2   += $(SRCS_MULTI_MBX)
SRCS_arp32_3   += $(SRCS_MULTI_MBX)
SRCS_arp32_4   += $(SRCS_MULTI_MBX)
SRCS_c66xdsp_1 += $(SRCS_MULTI_MBX)
SRCS_c66xdsp_2 += $(SRCS_MULTI_MBX)

SRCS_a15_0     += $(SRCS_SINGLE_MBX)
SRCS_ipu1_1    += $(SRCS_SINGLE_MBX)

SRCS_$(IPU_PRIMARY_CORE)    += $(SRCS_SINGLE_MBX)
SRCS_$(IPU_SECONDARY_CORE)  += $(SRCS_SINGLE_MBX)
