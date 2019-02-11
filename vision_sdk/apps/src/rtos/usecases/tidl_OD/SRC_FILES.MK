
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl_OD

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_tidlOD_priv.c \
        chains_tidlOD.c
