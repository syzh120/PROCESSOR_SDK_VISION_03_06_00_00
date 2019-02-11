
apps:
	$(MAKE) -fMAKEFILE.MK libs TARGET=depend
	$(MAKE) -fMAKEFILE.MK libs TARGET=lib


vision_sdk_linux_lib:
ifeq ($(TARGET),depend)
# Copy IPU generated memory map file to library include folder.
# If header file is not present then use previously generated file
	-cp $(vision_sdk_PATH)/binaries/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/links_fw/src/hlos/osa/include
endif
ifeq ($(TARGET),clean)
	$(MAKE) -C $(vision_sdk_PATH)/links_fw/src/hlos linkfw_libs_clean
else
	$(MAKE) -C $(vision_sdk_PATH)/links_fw/src/hlos linkfw_libs
endif

libs: vision_sdk_linux_lib

clean:
	$(MAKE) -fMAKEFILE.MK libs TARGET=clean

all: clean apps

.PHONY: libs clean all vision_sdk_linux_lib

