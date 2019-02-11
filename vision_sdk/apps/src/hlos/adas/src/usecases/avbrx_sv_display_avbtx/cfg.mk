ALG_dmaSwMs=yes
ALG_surroundview=yes
ALG_autocalibration=yes

NEED_PROC_IPU1_0=yes
NEED_PROC_IPU1_1=yes
NEED_PROC_DSP1=yes

ifeq ($(NDK_PROC_TO_USE), none)
    $(error NDK_PROC_TO_USE should be enabled to run this use-case)
endif
