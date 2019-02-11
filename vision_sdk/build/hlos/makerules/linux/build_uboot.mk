# File name: build_uboot.mk
#            This file builds the uboot.


uboot_build:
	$(MAKE) -C $(uboot_PATH) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) $(UBOOT_TARGET)

uboot_all:
	$(MAKE) -fbuild_uboot.mk uboot_clean
	$(MAKE) -fbuild_uboot.mk uboot

uboot:
	$(MAKE) -fbuild_uboot.mk uboot_build UBOOT_TARGET=$(DEFAULT_UBOOT_CONFIG)
	$(MAKE) -fbuild_uboot.mk uboot_build 

uboot_clean:
	$(MAKE) -C $(uboot_PATH) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) distclean

uboot_install:
	install -d $(LINUX_BOOT_OUT_FILES)
	install $(uboot_PATH)/MLO $(LINUX_BOOT_OUT_FILES)
	install $(uboot_PATH)/u-boot.img $(LINUX_BOOT_OUT_FILES)
#	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/uenv_nfs.txt $(LINUX_BOOT_OUT_FILES)/uenv.txt
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/uenv_sd.txt $(LINUX_BOOT_OUT_FILES)/uenv.txt
