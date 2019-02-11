# File name: build_kernel.mk
#            This file builds the kernel & corresponding modules.
#            Also copies images to required folders (filesystem or $(DEST_ROOT)/hlos/linux/boot)
#

STRIP_M4  = $(CODEGEN_PATH_M4)/bin/armstrip -p
STRIP_DSP = $(CODEGEN_PATH_DSP)/bin/strip6x -p
STRIP_EVE = $(CODEGEN_PATH_EVE)/bin/strip-arp32 -p

kernel_build:
	$(MAKE) -C $(kernel_PATH) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) $(KERNEL_TARGET)

kernel_all:
	$(MAKE) -fbuild_kernel.mk kernel_clean
	$(MAKE) -fbuild_kernel.mk kernel

kernel:
	cd $(kernel_PATH) ;\
	./ti_config_fragments/defconfig_builder.sh -t ti_sdk_dra7x_release
	cd $(vision_sdk_PATH) ;\
	$(MAKE) -C $(kernel_PATH) ARCH=arm $(DEFAULT_KERNEL_CONFIG)
	$(MAKE) -fbuild_kernel.mk dtb
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET=zImage
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET=modules
	$(MAKE) -C $(memcache_PATH)/build/ modules
ifeq ($(CMEM_INCLUDE),yes)
	cd $(cmem_PATH) ;\
	./configure --enable-shared --host=arm-linux-gnueabihf  --prefix="/usr"
	cd $(vision_sdk_PATH) ;\
# build cmem related .so files
	$(MAKE) -C $(cmem_PATH)/src/cmem/api
# build cmem related .ko files
	$(MAKE) -C $(cmem_PATH)/src/cmem/module KERNEL_INSTALL_DIR=$(kernel_PATH) ARCH=arm TOOLCHAIN_PREFIX=arm-linux-gnueabihf- release
endif
ifeq ($(OPENCL_INCLUDE),yes)
	cd $(debugss_PATH); \
	ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) PLATFORM=DRA7xx_PLATFORM KERNEL_SRC=$(kernel_PATH) make
	cd $(gdbc6x_PATH); \
	ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) PLATFORM=DRA7xx_PLATFORM KERNEL_SRC=$(kernel_PATH) make
endif

dtb:
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET="$(DEFAULT_DTB)"

kernel_menuconfig:
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET=menuconfig
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET=zImage
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET=modules
	$(MAKE) -C $(memcache_PATH)/build/ modules
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET="$(DEFAULT_DTB)"

kernel_clean:
	$(MAKE) -C $(kernel_PATH) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) distclean
	$(MAKE) -C $(memcache_PATH)/build ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) clean
ifeq ($(CMEM_INCLUDE),yes)
	$(MAKE) -C $(cmem_PATH) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) clean
	$(MAKE) -C $(cmem_PATH)/src/cmem/module KERNEL_INSTALL_DIR=$(kernel_PATH) ARCH=arm TOOLCHAIN_PREFIX=arm-linux-gnueabihf- clean
endif
ifeq ($(OPENCL_INCLUDE),yes)
	cd $(debugss_PATH); \
	ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) PLATFORM=DRA7xx_PLATFORM KERNEL_SRC=$(kernel_PATH) make clean
	cd $(gdbc6x_PATH); \
	ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) PLATFORM=DRA7xx_PLATFORM KERNEL_SRC=$(kernel_PATH) make clean
endif

kernel_install:
	$(MAKE) -fbuild_kernel.mk kernel_build KERNEL_TARGET=modules_install INSTALL_MOD_PATH=$(LINUX_TARGETFS)
	install -d $(LINUX_BOOT_OUT_FILES)
	install -d $(LINUX_TARGETFS)/boot
	install  $(kernel_PATH)/arch/arm/boot/zImage $(LINUX_TARGETFS)/boot
	mkimage -A arm -O linux -C none  -T kernel -a 0x80008000 -e 0x80008000 -n 'Linux uImage' -d "$(kernel_PATH)/arch/arm/boot/zImage" "$(kernel_PATH)/arch/arm/boot/uImage"
	install  $(kernel_PATH)/arch/arm/boot/uImage $(LINUX_TARGETFS)/boot
	cd $(kernel_PATH)/arch/arm/boot/dts/; cp -v $(DEFAULT_DTB) $(LINUX_TARGETFS)/boot
	$(MAKE)  -C $(memcache_PATH)/build TARGET=install INSTALL_MOD_PATH=$(LINUX_TARGETFS)
ifeq ($(CMEM_INCLUDE),yes)
# install cmem related .so files
	$(MAKE) -C $(cmem_PATH)/src/cmem/api DESTDIR=$(LINUX_TARGETFS) install
# install cmem related .ko files
	$(MAKE) -C $(cmem_PATH)/src/cmem/module EXEC_DIR=$(LINUX_TARGETFS)/opt/vision_sdk install
endif
ifeq ($(OPENCL_INCLUDE),yes)
	cp $(kernel_addon_PATH)/fs-patches/opencl_fs_patches.tar.gz $(LINUX_TARGETFS)/
endif

linux_app_install:
	mkdir -p $(LINUX_TARGETFS)/lib/firmware
	-rm -rf $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.xem4
	-rm -rf $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4
	-rm -rf $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66
	-rm -rf $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66
	-rm -rf $(LINUX_TARGETFS)/lib/firmware/*.lzop
	-rm -rf $(LINUX_TARGETFS)/lib/firmware/*.rsc
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4 $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.xem4
	$(STRIP_M4) $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.xem4
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.xem4 > $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.lzop
	objcopy -I elf32-little -j .resource_table $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.xem4 $(LINUX_TARGETFS)/lib/firmware/dra7-ipu1-fw.xem4.rsc 2> /dev/null
endif
ifeq ($(PROC_IPU2_INCLUDE),yes)
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu2_$(PROFILE_ipu2).xem4 $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4
	$(STRIP_M4) $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4 > $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.lzop
	objcopy -I elf32-little -j .resource_table $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4 $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4.rsc 2> /dev/null
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66
	$(STRIP_DSP) $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66 > $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.lzop
	objcopy -I elf32-little -j .resource_table $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66.rsc 2> /dev/null
else
ifeq ($(OPENCL_INCLUDE),yes)
	cp $(LINUX_TARGETFS)/lib/firmware/opencl_prebuilt/dra7-dsp1-fw.xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66
	$(STRIP_DSP) $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66 > $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.lzop
	objcopy -I elf32-little -j .resource_table $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp1-fw.xe66.rsc 2> /dev/null
endif
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66
	$(STRIP_DSP) $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66 > $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.lzop
	objcopy -I elf32-little -j .resource_table $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66.rsc 2> /dev/null
else
ifeq ($(OPENCL_INCLUDE),yes)
	cp $(LINUX_TARGETFS)/lib/firmware/opencl_prebuilt/dra7-dsp2-fw.xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66
	$(STRIP_DSP) $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66 > $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.lzop
	objcopy -I elf32-little -j .resource_table $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66 $(LINUX_TARGETFS)/lib/firmware/dra7-dsp2-fw.xe66.rsc 2> /dev/null
endif
endif
	mkdir -p $(LINUX_TARGETFS)/opt/vision_sdk
	mkdir -p $(LINUX_TARGETFS)/opt/ipks/
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/hdmiReceiverConfig.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/ub964Init.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/ov106x3Config.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/disableDssInterruptsOnA15.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/enableIpu2CCSConectivity.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/VipClockInversion.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/tda2exEnableAVB.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/vision_sdk_load.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/init-demo.sh $(LINUX_TARGETFS)/home/root/
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/decode_ipumm.sh $(LINUX_TARGETFS)/home/root/
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/load_ocl_kos.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/opencl_env.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/vision_sdk_unload.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/vision_sdk_ov490_pinmux.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/setupUltrasonicPinMux.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/$(MAKEAPPNAME).out $(LINUX_TARGETFS)/opt/vision_sdk
ifeq ($(OPENCL_INCLUDE),yes)
	cd $(debugss_PATH); \
	cp $(debugss_PATH)/debugss_kmodule.ko $(LINUX_TARGETFS)/opt/vision_sdk
	cd $(gdbc6x_PATH); \
	cp $(gdbc6x_PATH)/gdbserverproxy.ko $(LINUX_TARGETFS)/opt/vision_sdk
endif
	if [ -d  "$($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils" ]; then \
		cp -fR $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/models $(LINUX_TARGETFS)/opt/vision_sdk/ ; \
		cp $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/VertShader.vsh $(LINUX_TARGETFS)/opt/vision_sdk ; \
		cp $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/FragShader.fsh $(LINUX_TARGETFS)/opt/vision_sdk ; \
		cp $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/vis3Dsfm/VertShader3Dsfm.vsh $(LINUX_TARGETFS)/opt/vision_sdk ; \
		cp $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/vis3Dsfm/FragShader3Dsfm.fsh $(LINUX_TARGETFS)/opt/vision_sdk ; \
		cp $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/vis3Dsfm/jeep2.bmp $(LINUX_TARGETFS)/opt/vision_sdk ; \
		cp $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/vis3Dsfm/car.pod $(LINUX_TARGETFS)/opt/vision_sdk ; \
	fi
	cp $(kernel_addon_PATH)/scripts/memcache_load.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(kernel_addon_PATH)/scripts/memcache_unload.sh $(LINUX_TARGETFS)/opt/vision_sdk
#	cp $(kernel_addon_PATH)/bin/ipks/*.ipk  $(LINUX_TARGETFS)/opt/ipks/
ifeq ($(BUILD_ADAM_CAR),yes)
	cp $(vision_sdk_PATH)/apps/src/hlos/adam_car/scripts/*.sh $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/*.out $(LINUX_TARGETFS)/opt/vision_sdk
endif
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/enableImx290.sh $(LINUX_TARGETFS)/opt/vision_sdk

	cp $(kernel_addon_PATH)/scripts/powervr.ini $(LINUX_TARGETFS)/etc/
	mkdir -p $(LINUX_TARGETFS)/opt/vision_sdk/bin
	cp $(memcache_PATH)/build/memcache.ko $(LINUX_TARGETFS)/opt/vision_sdk/bin

# Copy IPU1-0 generated memory map file to library include folder.
# If header file is not present then use previously generated file
header_install:
	cp -fRv $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/links_fw/src/hlos/osa/include

autosar_app_install:
ifeq ($(PROC_IPU2_INCLUDE),yes)
	cp $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu2_$(PROFILE_ipu2).xem4 $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4
	$(STRIP_M4) $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4
	lzop -9 -c $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.xem4 > $(LINUX_TARGETFS)/lib/firmware/dra7-ipu2-fw.lzop
endif



