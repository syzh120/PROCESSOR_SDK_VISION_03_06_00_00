ALG_census=yes
ALG_disparityhamdist=yes
ALG_stereo_postprocessing=yes
ALG_dmaSwMs=yes

NEED_PROC_IPU1_0=yes
NEED_PROC_A15_0=yes
NEED_PROC_DSP1=yes
NEED_PROC_EVE2=yes
NEED_PROC_EVE3=yes

ifeq ($(NDK_PROC_TO_USE), none)
    $(error NDK_PROC_TO_USE should be enabled to run this use-case)
endif
ifeq ($(NDK_PROC_TO_USE), ipu1_1)
    NEED_PROC_IPU1_1=yes
endif
