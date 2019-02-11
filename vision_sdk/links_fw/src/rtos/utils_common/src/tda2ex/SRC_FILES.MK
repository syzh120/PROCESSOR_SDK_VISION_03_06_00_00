
SRCDIR += tda2ex

SRCS_COMMON += utils_clk.c 

SRCS_$(IPU_PRIMARY_CORE) += \
		       utils_l3_emif_bw.c

SRCS_ipu1_1 += \

SRCS_$(IPU_SECONDARY_CORE) += \

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
	SRCS_COMMON += utils_prcm.c
endif

