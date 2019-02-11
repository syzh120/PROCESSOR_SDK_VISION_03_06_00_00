
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/early_capture_late_weston

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_earlyCaptureLateWeston_priv.c \
        chains_earlyCaptureLateWeston.c
