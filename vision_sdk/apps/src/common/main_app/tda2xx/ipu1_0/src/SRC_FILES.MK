
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/common/main_app/tda2xx/ipu1_0/src
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/common/app_init

SRCS_ipu1_0 += main_ipu1_0.c

ifeq ($(IPU_SECONDARY_CORE), ipu1_0)
SRCS_$(IPU_SECONDARY_CORE) += app_init_ipu_secondary.c
endif
ifeq ($(IPU_PRIMARY_CORE), ipu1_0)
SRCS_$(IPU_PRIMARY_CORE) += app_init_ipu_primary.c
endif
