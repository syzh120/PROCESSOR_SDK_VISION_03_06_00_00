# File name: build_sgx.mk
#            This file builds the sgx.

SGX_DRA7XX_MAKEFILE := $(sgx_PATH)/eurasia_km/eurasiacon/build/linux2/omap_linux

sgx_build:
	$(MAKE) -C $(SGX_DRA7XX_MAKEFILE) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) KERNELDIR=$(kernel_PATH) DISCIMAGE=$(LINUX_TARGETFS)

sgx_all:
	$(MAKE) -fbuild_sgx.mk sgx_clean
	$(MAKE) -fbuild_sgx.mk sgx

sgx:
	$(MAKE) -fbuild_sgx.mk sgx_build SGX_TARGET=sgx_build

sgx_clean:
	$(MAKE) -C $(SGX_DRA7XX_MAKEFILE) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX)  KERNELDIR=$(kernel_PATH) DISCIMAGE=$(LINUX_TARGETFS) clean

sgx_install:
	$(MAKE) -C $(SGX_DRA7XX_MAKEFILE) ARCH=arm CROSS_COMPILE=$(A15_TOOLCHAIN_PREFIX) KERNELDIR=$(kernel_PATH) DISCIMAGE=$(LINUX_TARGETFS) kbuild_install
	if [ -d  "$($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils" ]; then \
		cp $(pvr_PATH)/Tools/OGLES2/Build/Linux_armv7hf/ReleaseNullWS/libogles2tools.a $(LINUX_TARGETFS)/usr/lib; \
	fi
	mkdir -p $(LINUX_TARGETFS)/opt/vision_sdk
	cp $(vision_sdk_PATH)/build/hlos/scripts/linux/pvrscope $(LINUX_TARGETFS)/opt/vision_sdk

