
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/common/main_app/tda2xx/ipu2/src
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/common/app_init

SRCS_ipu2 += main_ipu2.c

ifeq ($(IPU_SECONDARY_CORE), ipu2)
SRCS_$(IPU_SECONDARY_CORE) += app_init_ipu_secondary.c
endif
ifeq ($(IPU_PRIMARY_CORE), ipu2)
SRCS_$(IPU_PRIMARY_CORE) += app_init_ipu_primary.c
endif
