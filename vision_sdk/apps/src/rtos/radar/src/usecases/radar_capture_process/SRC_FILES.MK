SRCDIR += $(vision_sdk_PATH)/apps/src/rtos/radar/src/usecases/radar_capture_process

SRCS_ipu1_0 += chains_radarcaptureprocess.c \
               chains_radarcaptureprocess_priv.c

INCLUDE_EXTERNAL_INTERFACES += radarLink          \
                               radarFirmware
