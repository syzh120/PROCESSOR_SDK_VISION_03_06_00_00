
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/common

ifeq ($(A15_TARGET_OS), Bios)
SRCS_$(IPU_PRIMARY_CORE) += \
		board_tda2xx_ti_evm.c
endif

ifeq ($(A15_TARGET_OS), Linux)
SRCS_$(IPU_PRIMARY_CORE) += \
		chain_main_linux.c
endif        
