
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/csi2_cal_sv_standalone

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_csi2CalSVStandalone_priv.c \
		chains_csi2CalSVStandalone.c

ifeq ($(ISS_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += chains_csi2CalSVStandalone_issRsz_priv.c
endif

