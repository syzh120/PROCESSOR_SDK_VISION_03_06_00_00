
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

ifeq ($(BUILD_OPENCV_SRC), yes)
OPENCV_INCLUDE = $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/include
else
OPENCV_INCLUDE = $(OpenCV_PREBUILD_PATH)/include
endif

INCLUDE+= -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/linux/include -I$($(MAKEAPPNAME)_PATH) -I$(OPENCV_INCLUDE)

LIBS += $(LIB_BASE_DIR)/vision_sdk_linux_demo.a
LIBS += $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt)

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
