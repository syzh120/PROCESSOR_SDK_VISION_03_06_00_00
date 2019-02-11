
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/chains_common

ifeq ($(A15_TARGET_OS), Bios)
SRCS_$(IPU_PRIMARY_CORE) += \
		chains_common.c chain_main.c
endif
