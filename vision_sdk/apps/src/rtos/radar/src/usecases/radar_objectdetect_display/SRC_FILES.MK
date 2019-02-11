SRCDIR += $(vision_sdk_PATH)/apps/src/rtos/radar/src/usecases/radar_objectdetect_display

SRCS_ipu1_0 += chains_radarobjectdetectdisplay.c \
               chains_radarobjectdetectdisplay_priv.c

INCLUDE_EXTERNAL_INTERFACES += radarLink          \
                               radarFirmware
