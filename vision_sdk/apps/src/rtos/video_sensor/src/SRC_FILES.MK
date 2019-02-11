
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor/src
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor/src/ov10635
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor/src/hdmiRec
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor/src/tvp5158

SRCS_$(IPU_PRIMARY_CORE) += \
		vid_sensor_ov10635.c \
		vid_sensor.c \
		hdmi_recvr.c \
		video_decdr.c
