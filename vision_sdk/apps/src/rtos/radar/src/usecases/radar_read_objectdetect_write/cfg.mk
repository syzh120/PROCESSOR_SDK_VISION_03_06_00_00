ALG_FXN_radarfft2=yes
ALG_FXN_radarpeakdetect=yes
ALG_FXN_radarbeamform=yes
ALG_radarprocess=yes
ALG_FXN_radardraw=yes

NEED_PROC_IPU1_0=yes
NEED_PROC_DSP1=yes
NEED_PROC_EVE1=yes
NEED_PROC_A15_0=yes

ifeq ($(NDK_PROC_TO_USE), ipu1_1)
    NEED_PROC_IPU1_1=yes
endif
