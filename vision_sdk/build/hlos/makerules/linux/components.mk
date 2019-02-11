# List of component definitions for use with apps and modules
# A component requirement defines additional:
#  $(CFLAGS)
#  $(LDFLAGS)
#  recursive component requirements

ALL_COMPONENTS += ipc
ipc_component_CFLAGS := -I$(ipc_PATH)/hlos_common/include -I$(ipc_PATH)/packages -I$(ipc_PATH)/linux/include

ALL_COMPONENTS += link_api
link_api_component_CFLAGS := -I$(vision_sdk_PATH)/links_fw/include/link_api -I$(vision_sdk_PATH)/links_fw

ALL_COMPONENTS += linux
linux_component_CFLAGS := -I$(LINUX_TARGETFS)/usr/include

ALL_COMPONENTS += osa
osa_component_CFLAGS := -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include

ALL_COMPONENTS += osa_kermod
osa_kermod_component_CFLAGS := -I$(memcache_PATH)/include -I$(memcache_PATH)/include/osa

ALL_COMPONENTS += sgx
sgx_component_CFLAGS := -I$(LINUX_TARGETFS)/usr/include/libdrm -I$(LINUX_TARGETFS)/usr/include/EGL
sgx_component_CFLAGS += -I$(pvr_PATH)/Tools -I$(pvr_PATH)/Tools/OGLES2 -I$(pvr_PATH)/Include
sgx_component_CFLAGS += -I$(LINUX_TARGETFS)/usr/include/gbm -I$(LINUX_TARGETFS)/usr/include/omap
sgx_component_CFLAGS += -I$(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils
sgx_component_LDFLAGS := -lEGL -lGLESv2 -lgbm -ldrm -ldrm_omap -logles2tools
sgx_component_COMPONENT_DEPS := linux

ALL_COMPONENTS += uapi
uapi_component_CFLAGS := -I$(kernel_PATH)/include/generated/uapi
