
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(SGX_DRM_INC) -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/linux/include -I$($(MAKEAPPNAME)_PATH)

LIBS += $(LIB_BASE_DIR)/vision_sdk_linux_demo.a $(LIB_BASE_DIR)/system.a
LIBS += $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt)

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk

