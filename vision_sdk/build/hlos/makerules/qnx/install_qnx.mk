# File name: install_qnx.mk
#            This file has rules to install firmware to qnx side
#

STRIP_M4  = $(CODEGEN_PATH_M4)/bin/armstrip -p
STRIP_DSP = $(CODEGEN_PATH_DSP)/bin/strip6x -p
STRIP_EVE = $(CODEGEN_PATH_EVE)/bin/strip-arp32 -p


firmware_clean:
ifeq ($(PLATFORM),tda2xx-evm)
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66
endif
ifeq ($(PLATFORM),tda2xx-rvp)
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66
endif
ifeq ($(PLATFORM),tda2px-evm)
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra76-ipu1-fw.xem4
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra76-dsp1-fw.xe66
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra76-dsp2-fw.xe66
endif
ifeq ($(PLATFORM),tda2ex-evm)
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1
	mkdir -p $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra72x-ipu1-fw.xem4
	-rm -rf $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra72x-dsp1-fw.xe66
endif

firmware_install: firmware_clean
ifeq ($(PLATFORM),tda2xx-evm)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4 $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4.map $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4.map
	$(STRIP_M4) $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66
endif
endif
ifeq ($(PLATFORM),tda2xx-rvp)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4 $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4.map $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4.map
	$(STRIP_M4) $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra7-ipu1-fw.xem4
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra7-dsp1-fw.xe66
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra7-dsp2-fw.xe66
endif
endif
ifeq ($(PLATFORM),tda2px-evm)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4 $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra76-ipu1-fw.xem4
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4.map $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra76-ipu1-fw.xem4.map
	$(STRIP_M4) $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra76-ipu1-fw.xem4
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra76-dsp1-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra76-dsp1-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra76-dsp1-fw.xe66
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra76-dsp2-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra76-dsp2-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp2/dra76-dsp2-fw.xe66
endif
endif
ifeq ($(PLATFORM),tda2ex-evm)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4 $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra72x-ipu1-fw.xem4
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4.map $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra72x-ipu1-fw.xem4.map
	$(STRIP_M4) $(QNX_TARGETFS)/armle-v7/lib/firmware/ipu1/dra72x-ipu1-fw.xem4
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66 $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra72x-dsp1-fw.xe66
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66.map $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra72x-dsp1-fw.xe66.map
	$(STRIP_DSP) $(QNX_TARGETFS)/armle-v7/lib/firmware/dsp1/dra72x-dsp1-fw.xe66
endif
endif

# Copy IPU1-0 generated memory map file to library include folder.
# If header file is not present then use previously generated file
header_install:
	cp -fRv $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/links_fw/src/hlos/osa/include

