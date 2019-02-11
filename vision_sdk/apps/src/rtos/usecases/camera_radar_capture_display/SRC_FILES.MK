
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/camera_radar_capture_display

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_cameraRadarCapture_display.c \
		chains_cameraRadarCapture_display_priv.c 

INCLUDE_INTERNAL_INTERFACES += radar
INCLUDE_EXTERNAL_INTERFACES += radarLink     \
                               radarFirmware \
                               evealg
