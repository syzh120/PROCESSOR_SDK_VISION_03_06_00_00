
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk
ifeq ($(BUILD_INFOADAS), yes)
DEFINE += -DBUILD_INFOADAS
endif
INCLUDE+= -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/linux/include -I$(vision_sdk_PATH)/links_fw -I$($(MAKEAPPNAME)_PATH)

LIBS += $(LIB_BASE_DIR)/$(MAKEAPPNAME).a  $(LIB_BASE_DIR)/system.a
LIBS += $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt)

ifeq ($(BUILD_FOR_ANDROID), yes)
  INCLUDE += $(ANDROID_COMMON_INC)
endif

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
