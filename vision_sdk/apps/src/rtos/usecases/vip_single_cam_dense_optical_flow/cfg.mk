ALG_denseopticalflow=yes

NEED_PROC_IPU1_0=yes
NEED_PROC_DSP1=yes
NEED_PROC_EVE1=yes

ifeq ($(SOC),tda2xx)
NEED_PROC_EVE2=yes
#NEED_PROC_EVE3=yes
#NEED_PROC_EVE4=yes
endif