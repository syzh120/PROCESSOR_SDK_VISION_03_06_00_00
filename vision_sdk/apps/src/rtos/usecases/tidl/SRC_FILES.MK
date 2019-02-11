
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl

ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px))
    SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl/UsecaseDsp
    SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl/UsecaseEve

    SRCS_$(IPU_PRIMARY_CORE) += \
            chains_tidlDsp_priv.c \
            chains_tidlEve_priv.c \
            chains_tidl.c
endif

ifeq ($(SOC),tda3xx)
    SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl/UsecaseDspTda3x
    SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl/UsecaseEveTda3x

    SRCS_$(IPU_PRIMARY_CORE) += \
            chains_tidlDspTda3x_priv.c \
            chains_tidlEveTda3x_priv.c \
            chains_tidl.c
endif



