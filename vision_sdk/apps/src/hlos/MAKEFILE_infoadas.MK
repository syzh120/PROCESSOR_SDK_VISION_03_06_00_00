include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk

export fw_VERS=03_01_00_00
export fw_PATH=$(vision_sdk_PATH)/binaries/apps/temp/visionsdk-fw
STRIP_M4  = $(CODEGEN_PATH_M4)/bin/armstrip -p
STRIP_DSP = $(CODEGEN_PATH_DSP)/bin/strip6x -p
STRIP_EVE = $(CODEGEN_PATH_EVE)/bin/strip-arp32 -p
export MODULENAME=apps

apps:
	$(MAKE) -fMAKEFILE_infoadas.MK libs TARGET=depend
	$(MAKE) -fMAKEFILE_infoadas.MK libs TARGET=lib
	$(MAKE) -fMAKEFILE_infoadas.MK demo TARGET=depend
	$(MAKE) -fMAKEFILE_infoadas.MK demo TARGET=lib
	$(MAKE) -fMAKEFILE_infoadas.MK demo TARGET=so
	$(MAKE) -fMAKEFILE_infoadas.MK package

vision_sdk_linux_lib:
ifeq ($(TARGET),depend)
# Copy IPU generated memory map file to library include folder.
# If header file is not present then use previously generated file
	-cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/links_fw/src/hlos/osa/include
endif
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/modules/sgx3Dsrv CORE=a15_0 MODNAME=$(MODULENAME) $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils CORE=a15_0 MODNAME=$(MODULENAME) $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/common CORE=a15_0 MODNAME=$(MODULENAME) $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/ti-plugins CORE=a15_0 MODNAME=$(MODULENAME) $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/common CORE=a15_0 MODNAME=$(MODULENAME) $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/rtos/common_srv MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/rtos/modules/osal MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/rtos/modules/network_ctrl MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/Tools MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/Tools/OGLES2 MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
ifeq ($(UC_srv_calibration),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/adas/src/usecases/srv_calibration MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_2d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_2d_srv MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_3d_srv MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_single_cam),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_single_cam MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_multi_cam),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_multi_cam MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_a15source_2d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/a15source_2d_srv MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_a15source_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/a15source_3d_srv MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_single_cam_analytics),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_single_cam_analytics MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_buf_loop),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/buf_loop MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_single_cam_analytics2),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_single_cam_analytics2 MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_csi2Cal_multi_cam_view),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/csi2Cal_multi_cam_view MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_iss_multi_cam_isp_sgx_3d_srv_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/iss_multi_cam_isp_sgx_3d_srv_display MODNAME=$(MODULENAME) CORE=a15_0 $(TARGET)
endif

libs: vision_sdk_linux_lib


package:
	mkdir -p $(fw_PATH)
	mkdir -p $(fw_PATH)/lib
	mkdir -p $(fw_PATH)/include
	mkdir -p $(fw_PATH)/fw
	mkdir -p $(fw_PATH)/utils

	$(shell $(vision_sdk_PATH)/apps/src/hlos/infoadas/fw-version.sh)
	mv `pwd`/VERSION.txt $(fw_PATH)/

ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4 $(fw_PATH)/fw/dra7-ipu1-fw.xem4
	$(STRIP_M4) $(fw_PATH)/fw/dra7-ipu1-fw.xem4
endif
ifeq ($(PROC_IPU2_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu2_$(PROFILE_ipu2).xem4 $(fw_PATH)/fw/dra7-ipu2-fw.xem4
	$(STRIP_M4) $(fw_PATH)/fw/dra7-ipu2-fw.xem4
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66 $(fw_PATH)/fw/dra7-dsp1-fw.xe66
	$(STRIP_DSP) $(fw_PATH)/fw/dra7-dsp1-fw.xe66
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66 $(fw_PATH)/fw/dra7-dsp2-fw.xe66
	$(STRIP_DSP) $(fw_PATH)/fw/dra7-dsp2-fw.xe66
endif
	echo "Creating shared library"
	cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/libapps.so $(fw_PATH)/lib/libadas.so

	#copy libadas.a
	cp -fR $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/models $(fw_PATH)/utils/
	cp $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/VertShader.vsh $(fw_PATH)/utils
	cp $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/FragShader.fsh $(fw_PATH)/utils

	#copy header files
	cp $(vision_sdk_PATH)/links_fw/include/link_api/system_const.h $(fw_PATH)/include/
	cp $(vision_sdk_PATH)/links_fw/include/link_api/system_link_info.h $(fw_PATH)/include/
	cp $(vision_sdk_PATH)/links_fw/include/link_api/system_buffer.h $(fw_PATH)/include/
	cp $(vision_sdk_PATH)/links_fw/src/hlos/osa/include/osa_types.h $(fw_PATH)/include/
	cp $(vision_sdk_PATH)/links_fw/src/hlos/osa/include/osa_debug.h $(fw_PATH)/include/
	cp $(vision_sdk_PATH)/links_fw/src/hlos/osa/include/osa_mem_shared.h $(fw_PATH)/include/
	cp $(vision_sdk_PATH)/links_fw/src/hlos/system/system_pvrscope_if.h $(fw_PATH)/include/

	mv $(fw_PATH)/VERSION.txt $(fw_PATH)/fw
ifeq ($(PLATFORM),tda2xx-evm)
	mv $(fw_PATH)/lib $(fw_PATH)/lib-dra75x
	mv $(fw_PATH)/fw $(fw_PATH)/fw-dra75x
endif
ifeq ($(PLATFORM),tda2xx-rvp)
	mv $(fw_PATH)/lib $(fw_PATH)/lib-dra75x
	mv $(fw_PATH)/fw $(fw_PATH)/fw-dra75x
endif
ifeq ($(PLATFORM),tda2ex-evm)
	mv $(fw_PATH)/lib $(fw_PATH)/lib-dra72x
	mv $(fw_PATH)/fw $(fw_PATH)/fw-dra72x
endif
ifeq ($(PLATFORM),tda2px-evm)
	mv $(fw_PATH)/lib $(fw_PATH)/lib-dra76x
	mv $(fw_PATH)/fw $(fw_PATH)/fw-dra76x
endif

	@echo \# Creating tar for firmwares !!!
	tar -czf $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/visionsdk-fw-$(fw_VERS).tar.gz  -C $(fw_PATH)/.. .
	rm -Rf $(fw_PATH)/

demo:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/infoadas/src/common MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)

clean:
	$(MAKE) -fMAKEFILE_infoadas.MK libs TARGET=clean

all: clean demo

.PHONY: libs clean demo all vision_sdk_linux_lib

