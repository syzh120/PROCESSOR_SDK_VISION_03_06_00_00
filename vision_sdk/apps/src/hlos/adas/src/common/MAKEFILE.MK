
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(kernel_PATH)/include/generated/uapi $(OSA_INC) -I$(ipc_PATH)/linux/include -I$($(MAKEAPPNAME)_PATH)

LIBS += -Wl,--start-group $(LIB_BASE_DIR)/$(MAKEAPPNAME).a  $(LIB_BASE_DIR)/system.a $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt) -Wl,--end-group

ifeq ($(OPENVX_INCLUDE),yes)
OPENVX_LIBS_DIR = $(OpenVX_PATH)/lib/TDAX/A15/LINUX/$(PROFILE)/
OPENVX_LIBS = -Wl,--start-group 
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_conformance_engine.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_conformance_tests.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_conformance_tests_testmodule.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_framework.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_kernels_host_utils.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_kernels_ivision.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_kernels_openvx_core.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_platform_vision_sdk_linux.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_tiovx_ivision_tests.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_tiovx_tests.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_tutorial.a
OPENVX_LIBS += $(OPENVX_LIBS_DIR)/libvx_vxu.a
OPENVX_LIBS += -lticmem -lc -lm -lgcc -Wl,--end-group

LIBS += $(OPENVX_LIBS)
endif

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
