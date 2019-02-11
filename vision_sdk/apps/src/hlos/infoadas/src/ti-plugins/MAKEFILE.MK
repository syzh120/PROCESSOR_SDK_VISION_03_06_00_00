
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(LINUX_COMMON_INC) -I$(ipc_PATH)/linux/include -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi
INCLUDE+= $(LINK_API_INC) -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include
INCLUDE+= $(SGX_DRM_INC) -I./include/gbm
INCLUDE+= -I$(infoadas_PATH)/include
INCLUDE+= -I$(infoadas_PATH)/ti-plugins/include
INCLUDE+= -I$(infoadas_PATH)/ti-plugins/srv
INCLUDE+= -I$(infoadas_PATH)/ti-plugins/preview
INCLUDE+= -I$(infoadas_PATH)/ti-plugins/sca
INCLUDE+= -I$(LINUX_TARGETFS)/usr/include

CC_OPTS+= -fms-extensions

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk


