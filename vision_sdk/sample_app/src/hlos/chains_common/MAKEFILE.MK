
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(LINUX_COMMON_INC) -I$(ipc_PATH)/linux/include -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi
INCLUDE+= $(LINK_API_INC) -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include  -I$(vision_sdk_PATH)/sample_app

LIBS += $(LIB_BASE_DIR)/links_a15_dup.a $(LIB_BASE_DIR)/links_a15_null.a $(LIB_BASE_DIR)/links_a15_nullSrc.a $(LIB_BASE_DIR)/$(MAKEAPPNAME).a $(LIB_BASE_DIR)/links_a15_gate.a $(LIB_BASE_DIR)/system.a
LIBS += $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt)

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
