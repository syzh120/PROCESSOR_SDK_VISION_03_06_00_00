
include $(vision_sdk_PATH)/hlos/build/linux/common_header_a15.mk


INCLUDE+= $(LINUX_COMMON_INC) -I$(ipc_PATH)/linux/include -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi 
INCLUDE+= $(LINK_API_INC) -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include
INCLUDE+= $(SGX_DRM_INC) -I$(LINUX_TARGETFS)/usr/include/omap -I$(LINUX_TARGETFS)/usr/include/gbm
ifeq ($(BUILD_INFOADAS), yes)
INCLUDE+=-I$(infoadas_PATH)/include
endif
include $(vision_sdk_PATH)/hlos/build/linux/common_footer_a15.mk


