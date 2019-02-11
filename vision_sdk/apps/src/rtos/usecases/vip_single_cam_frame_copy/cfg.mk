ALG_framecopy=yes

NEED_PROC_IPU1_0=yes

ifeq ($(SOC),tda3xx)
NEED_PROC_DSP1=yes
NEED_PROC_EVE1=yes
endif

ifeq ($(SOC),tda2xx)
NEED_PROC_A15_0=yes
NEED_PROC_DSP1=yes
NEED_PROC_EVE1=yes
endif

ifeq ($(SOC),tda2ex)
NEED_PROC_A15_0=yes
NEED_PROC_DSP1=yes
endif
