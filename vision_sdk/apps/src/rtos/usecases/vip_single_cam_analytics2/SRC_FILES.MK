
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_analytics2

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCameraAnalytics2_priv.c \
		chains_vipSingleCameraAnalytics2.c
