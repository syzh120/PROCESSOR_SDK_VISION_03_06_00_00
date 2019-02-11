include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/linux/include -I$(vision_sdk_PATH)/links_fw -I$(infoadas_PATH)/include -I$(infoadas_PATH)/ti-plugins/include -I$(infoadas_PATH)/ti-plugins/srv $(SGX_DRM_INC) -I$(vision_sdk_PATH)/apps -I$(vision_sdk_PATH)/links_fw/include/link_api

ifeq ($(BUILD_FOR_ANDROID), yes)
  INCLUDE += $(ANDROID_COMMON_INC)
endif

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
