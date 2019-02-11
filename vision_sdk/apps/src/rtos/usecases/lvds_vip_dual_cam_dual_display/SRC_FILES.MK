
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/lvds_vip_dual_cam_dual_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_lvdsVipDualCam_DualDisplay_priv.c \
		chains_lvdsVipDualCam_DualDisplay.c

