
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_tlr

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_vipSingleCameraTlr_priv.c \
        chains_vipSingleCameraTlr.c

