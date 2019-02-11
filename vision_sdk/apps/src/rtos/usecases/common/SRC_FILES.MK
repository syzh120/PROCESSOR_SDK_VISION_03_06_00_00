
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/common

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_common.c

ifneq ($(RADAR_ONLY),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
        chains_common_vision.c \
        chains_common_stereo.c \
        chains_common_sfm.c \
        chains_common_fc_analytics2.c \
        chains_common_rear_view_panorama.c \
        chains_common_dewarp.c \
        chains_common_tidl.c
endif

