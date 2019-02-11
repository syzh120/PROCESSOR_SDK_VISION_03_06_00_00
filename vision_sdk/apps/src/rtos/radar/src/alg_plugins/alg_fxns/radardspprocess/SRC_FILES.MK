SRCDIR += $(vision_sdk_PATH)/apps/src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess
SRCDIR += $(vision_sdk_PATH)/apps/src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/priv
INCLUDE_EXTERNAL_INTERFACES += dsplib mmwavelib mathlib

SRCS_RADAR_DSP = radarDspProcess.c \
                 radarDspProcessEdmaUtils.c \
                 radarDspSecondDimFft_priv.c \
                 radarDspProcessCfar_priv.c \
                 radarDspProcessAoa_priv.c
#CFLAGS_radarDspSecondDimFft_priv = --symdebug:none
#CFLAGS_radarDspProcessAoa_priv = --symdebug:none
#CFLAGS_radarDspProcessCfar_priv = --symdebug:none
                 
SRCS_c66xdsp_1 += $(SRCS_RADAR_DSP)

SRCS_c66xdsp_2 += $(SRCS_RADAR_DSP)
