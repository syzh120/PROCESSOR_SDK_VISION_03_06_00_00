ALG_deWarp=yes
ALG_census=yes
ALG_disparityhamdist=yes
ALG_stereo_postprocessing=yes
ALG_dmaSwMs=yes
ALG_stereo_app=yes
ALG_iss_aewb=yes

NEED_PROC_IPU1_0=yes
NEED_PROC_DSP1=yes
NEED_PROC_DSP2=yes
NEED_PROC_EVE1=yes

ifeq ($(NDK_PROC_TO_USE), ipu1_1)
    NEED_PROC_IPU1_1=yes
endif
