
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/semSeg

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_semSeg_priv.c \
        chains_semSeg.c
