# Common source files and CFLAGS across all platforms and cores

SRCDIR += prcm prcm/common src/pmhal/prcm src/pmhal/prcm/common
INCDIR += prcm prcm/common src/pmhal/prcm src/pmhal/prcm/common

ifeq ($(SOC),$(filter $(SOC), tda2xx am572x dra72x dra75x tda2ex am571x))
SRCDIR += prcm/V0 src/pmhal/prcm/V0
INCDIR += prcm/V0 src/pmhal/prcm/V0
endif
ifeq ($(SOC),$(filter $(SOC), tda2px am574x))
SRCDIR += prcm/V5 src/pmhal/prcm/V5
INCDIR += prcm/V5 src/pmhal/prcm/V5
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SRCDIR += prcm/V2 src/pmhal/prcm/V2
INCDIR += prcm/V2 src/pmhal/prcm/V2
endif

SRCS_COMMON +=  pmhal_vm.c                                                     \
                hw_pmhal_vmdata.c                                              \
                hw_pmhal_data.c                                                \
                hw_pmhal_data_names.c                                          \
                pmhal_pmic.c                                                   \
                pmhal_pmicComm.c                                               \
                pmhal_i2cComm.c                                                \
                pmhal_mm.c                                                     \
                pmhal_prm_int.c                                                \
                pmhal_bgap.c                                                   \
                hw_pmhal_bgap_data.c                                           \
                pmhal_pdm.c                                                    \
                pmhal_rm.c                                                     \
                pmhal_sd.c                                                     \
                pmhal_cm.c                                                     \
                hw_pmhal_bgap_common_data.c                                    \
                hw_pmhal_prmdata.c                                             \
                pm_utils.c                                                     \
                hw_pmhal_clocktree_data.c                                      \
                pmhal_prcm_stats.c                                             \
                pmhal_clocktree.c

ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SRCS_COMMON +=  pmhal_tps65917.c                                               \
                pmhal_lp8731.c                                                 \
                pmhal_lp8733.c                                                 \
                pmhal_lp8731_lp3907.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra72x dra75x tda2ex am571x am574x ))
SRCS_COMMON +=  pmhal_videopll.c                                               \
                hw_pmhal_videopll_data.c                                       \
                hw_pmhal_ina226data.c                                          \
                pmhal_ina226.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx dra75x))
SRCS_COMMON += pmhal_tps659039.c
SRCS_COMMON += pmhal_tps65917.c
SRCS_COMMON += pmhal_tps659037.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2px))
SRCS_COMMON += pmhal_lp87565.c
SRCS_COMMON += pmhal_tps65917.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2ex dra72x))
SRCS_COMMON += pmhal_tps65917.c
SRCS_COMMON += pmhal_lp8733.c pmhal_tps659039.c
endif

ifeq ($(SOC),$(filter $(SOC), am571x am572x am574x))
SRCS_COMMON += pmhal_tps659037.c
endif
SRCS_a15_0 += pmhal_mpu_lprm.c
