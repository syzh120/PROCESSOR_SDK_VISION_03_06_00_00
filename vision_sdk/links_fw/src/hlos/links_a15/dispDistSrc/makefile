
include component.mk

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(LINUX_COMMON_INC) -I$(ipc_PATH)/linux/include -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi -I$(kernel_PATH)/include/uapi
INCLUDE+= $(LINK_API_INC) -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include
INCLUDE+= -I$(LINUX_TARGETFS)/usr/include/libdrm -I$(LINUX_TARGETFS)/usr/include

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk

# Nothing beyond this point
