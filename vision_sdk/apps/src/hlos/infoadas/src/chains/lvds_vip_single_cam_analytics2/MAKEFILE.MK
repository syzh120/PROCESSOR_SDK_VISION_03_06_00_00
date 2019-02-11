
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+=   $(LINK_API_INC) -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/hlos/include -I$(vision_sdk_PATH)/links_fw -I$(vision_sdk_PATH)/apps
INCLUDE+= -I$(infoadas_PATH)/include
INCLUDE+= -I$(infoadas_PATH)/ti-plugins/include
INCLUDE+= -I$(LINUX_TARGETFS)/usr/include

ifeq ($(BUILD_FOR_ANDROID), yes)
  INCLUDE += $(ANDROID_COMMON_INC)
endif

CC_OPTS+= -fms-extensions

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk

