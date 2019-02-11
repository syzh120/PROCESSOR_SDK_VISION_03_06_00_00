
include component.mk

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include $(LINUX_COMMON_INC) $(OSA_KERMOD_INC)
ifeq ($(BUILD_INFOADAS), yes)
INCLUDE+= -I$(shm_PATH)
endif

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk

# Nothing beyond this point
