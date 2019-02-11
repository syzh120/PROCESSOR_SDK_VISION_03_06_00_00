
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/common_srv

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_common_srv_calib.c \
		chains_common_surround_view.c \
		chains_lens.c

