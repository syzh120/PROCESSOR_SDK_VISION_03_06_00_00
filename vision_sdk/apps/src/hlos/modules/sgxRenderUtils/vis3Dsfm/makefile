
include component.mk

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(LINUX_COMMON_INC) -I$(ipc_PATH)/linux/include -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi
INCLUDE+= $(LINK_API_INC) -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include -I$($(MAKEAPPNAME)_PATH)
INCLUDE+= $(SGX_DRM_INC) -I./include/gbm -I$(pvr_PATH)/Tools -I$(pvr_PATH)/Tools/OGLES2 -I$(pvr_PATH)/Include
INCLUDE+= -I$($(MAKEAPPNAME)_PATH)/src/hlos/module/sgxRenderUtils

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk

# Nothing beyond this point
