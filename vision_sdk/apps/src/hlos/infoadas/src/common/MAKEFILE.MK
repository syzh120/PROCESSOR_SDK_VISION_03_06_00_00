
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(LINK_API_INC) -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/linux/include -I$(vision_sdk_PATH)/apps/ -I$(vision_sdk_PATH)/links_fw/ -I$(infoadas_PATH)/include

LIBS += -Wl,--start-group $(LIB_BASE_DIR)/$(MAKEAPPNAME).a  $(LIB_BASE_DIR)/system.a $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt) -Wl,--end-group

CC_OPTS+= -fms-extensions

ifeq ($(BUILD_FOR_ANDROID), yes)
  INCLUDE += $(ANDROID_COMMON_INC)
endif

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
