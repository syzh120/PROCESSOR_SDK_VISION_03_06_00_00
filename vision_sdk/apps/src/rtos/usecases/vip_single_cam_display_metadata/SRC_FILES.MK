
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/vip_single_cam_display_metadata

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_vipSingleCam_Display_Metadata.c \
		chains_vipSingleCam_Display_Metadata_priv.c

