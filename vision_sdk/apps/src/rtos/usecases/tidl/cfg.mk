ALG_tidl=yes

NEED_PROC_IPU1_0=yes
NEED_PROC_EVE1=yes
NEED_PROC_DSP1=yes

ifeq ($(SOC),tda2xx)
    NEED_PROC_A15_0=yes
    NEED_PROC_EVE2=yes
endif
