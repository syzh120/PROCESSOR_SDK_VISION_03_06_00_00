# Source files and CFLAGS across all platforms and cores

SRCDIR += prcm src/pmlib/prcm
INCDIR += prcm src/pmlib/prcm

ifeq ($(SOC),$(filter $(SOC), tda2xx am572x dra72x dra75x tda2ex am571x))
SRCDIR += prcm/V0 src/pmlib/prcm/V0
INCDIR += prcm/V0 src/pmlib/prcm/V0
endif
ifeq ($(SOC),$(filter $(SOC), tda2px am574x))
SRCDIR += prcm/V5 src/pmlib/prcm/V5
INCDIR += prcm/V5 src/pmlib/prcm/V5
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SRCDIR += prcm/V2 src/pmlib/prcm/V2
INCDIR += prcm/V2 src/pmlib/prcm/V2
endif

SRCS_COMMON += pmlib_sysconfig.c pmlib_clkrate.c pmlib_boardconfig.c pmlib_videopll_data.c pmlib_videopll.c
SRCS_a15_0 += pmlib_cpuidle_a15host.c
SRCS_ipu1_0 += pmlib_cpuidle_m4.c
SRCS_ipu1_1 += pmlib_cpuidle_m4.c
SRCS_c66x += pmlib_cpuidle_c66x.c
SRCS_c66xdsp_1 += pmlib_cpuidle_c66x.c
SRCS_arp32_1 += pmlib_cpuidle_arp32.c
SRCS_arp32_2 += pmlib_cpuidle_arp32.c
SRCS_arp32_3 += pmlib_cpuidle_arp32.c
SRCS_arp32_4 += pmlib_cpuidle_arp32.c

ifeq ($(SOC),$(filter $(SOC), tda2xx am572x dra75x))
SRCS_COMMON +=  pmlib_clk_rate_data_tda2xx.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2px am574x))
SRCS_COMMON +=  pmlib_clk_rate_data_tda2px.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2ex dra72x am571x))
SRCS_COMMON +=  pmlib_clk_rate_data_tda2ex.c
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SRCS_COMMON +=  pmlib_clk_rate_data_tda3xx.c
endif

SRCS_ASM_a15_0 += pmlib_cpuidle_utils_a15host.asm
SRCS_ASM_ipu1_0 += pmlib_cpuidle_utils_m4.asm
SRCS_ASM_ipu1_1 += pmlib_cpuidle_utils_m4.asm

# Nothing beyond this point
