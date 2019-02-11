
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= -I ../Include -I. -I ./OGLES2

CC_OPTS+= -fms-extensions

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk


