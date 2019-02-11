
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= -I$(LINUX_TARGETFS)/usr/include -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/packages -I$(ipc_PATH)/linux/include -I$($(MAKEAPPNAME)_PATH)

LIB_OCL= $(LINUX_TARGETFS)/usr/lib

LIBS += $(LIB_BASE_DIR)/vision_sdk_linux_demo.a
LIBS += $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt)

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk

opencl_build:
	$(MAKE) -B -Ckernel
