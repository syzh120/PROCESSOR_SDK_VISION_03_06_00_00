
include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk

apps:
	$(MAKE) -fMAKEFILE_adas.MK libs TARGET=depend
	$(MAKE) -fMAKEFILE_adas.MK libs TARGET=lib
	$(MAKE) -fMAKEFILE_adas.MK kermod
	$(MAKE) -fMAKEFILE_adas.MK demo TARGET=exe

vision_sdk_linux_demo:
ifeq ($(TARGET),depend)
# Copy IPU generated memory map file to library include folder.
# If header file is not present then use previously generated file
	-cp $(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/links_fw/src/hlos/osa/include
endif
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/common MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/common MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
ifeq ($(UC_vip_single_cam_sgx_display_autosar_app),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_sgx_display_autosar_app MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_sgx_display_autosar_app/autosar_mcal_testApp MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_multi_cam_8ch_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_8ch_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_single_cam_view_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_single_cam_view_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_enc_dec_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_view_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_vpe_enc_null MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
ifeq ($(UC_avb_rx_multi_cam_decode_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/avb_rx_multi_cam_decode_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/rtos/common_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/rtos/modules/network_ctrl MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/rtos/modules/osal MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
ifeq ($(UC_avb_rx_multi_cam_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/avb_rx_multi_cam_3d_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_srv_calibration),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/srv_calibration MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_multi_cam_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_3d_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_multi_cam_3d_adaptive_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_3d_adaptive_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_multi_cam_2mp_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_2mp_3d_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_avbrx_sv_display_avbtx),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/avbrx_sv_display_avbtx MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_csi2Cal_multi_cam_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/csi2Cal_multi_cam_3d_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
ifeq ($(UC_csi2Cal_multi_cam_3d_srv_cbb),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/csi2Cal_multi_cam_3d_srv_cbb MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif
ifeq ($(UC_csi2Cal_multi_cam_view),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/csi2Cal_multi_cam_view MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_lvds_vip_multi_cam_3d_perception),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/lvds_vip_multi_cam_3d_perception MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_vip_single_cam_framecopyEve_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_framecopyEve_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_ov490_vip_multi_cam_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/ov490_vip_multi_cam_3d_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_vip_single_cam_framecopy_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_framecopy_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_vip_single_cam_connectorLinksA15_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_connectorLinksA15_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_null_src_decode_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/null_src_decode_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_disp_dist_src_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/disp_dist_src_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_vip_single_cam_dualSgxDisplay),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_dualSgxDisplay MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(ENABLE_OPENCV),yes)
ifeq ($(UC_vip_single_cam_opencvcanny_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_opencvcanny_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_vip_single_cam_opencvopencldilation_sgx_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_opencvopencldilation_sgx_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif
ifeq ($(OPENCL_INCLUDE),yes)
ifeq ($(UC_vip_single_cam_openclframe_copy),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/vip_single_cam_openclframe_copy MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif

ifeq ($(ISS_INCLUDE),yes)
ifeq ($(UC_iss_capture_isp_simcop_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/iss_capture_isp_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_iss_multi_cam_isp_sgx_3d_srv_display),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/iss_multi_cam_isp_sgx_3d_srv_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_iss_multi_cam_isp_sgx_2mp_3d_srv),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/iss_multi_cam_isp_sgx_2mp_3d_srv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(UC_iss_multi_cam_isp_sgx_2mp_3d_srv_adaptive),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/iss_multi_cam_isp_sgx_2mp_3d_srv_adaptive MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif

ifeq ($(UC_cascade_radar_capture_linux_only),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/cascade_radar_capture_linux_only MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif

ifeq ($(UC_cascade_radar_datacollect),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/cascade_radar_datacollect MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif

# Add modules here
ifeq "$(or $(ALG_structurefrommotion),$(ALG_surroundview))""yes"
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
ifeq ($(ALG_structurefrommotion),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils/vis3Dsfm MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif

ifeq ($(ALG_surroundview),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgx3Dsrv MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(ALG_structurefrommotion),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgx3Dsfm MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif

# Add Algplugins here
ifeq ($(ALG_framecopy),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/alg_plugins/framecopy MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(ENABLE_OPENCV),yes)
ifeq ($(ALG_opencvcanny),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/alg_plugins/opencvcanny MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
ifeq ($(ALG_opencvopencldilation),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/alg_plugins/opencvopencldilation MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif
ifeq ($(OPENCL_INCLUDE),yes)
ifeq ($(ALG_openclframecopy),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/alg_plugins/openclframecopy MODNAME=$(MAKEAPPNAME) opencl_build
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/alg_plugins/openclframecopy MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)
endif
endif

	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/modules/dataCollect MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)

libs: vision_sdk_linux_demo

demo:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/common MODNAME=$(MAKEAPPNAME) CORE=a15_0 $(TARGET)

clean:
	$(MAKE) -fMAKEFILE_adas.MK libs TARGET=clean

all: clean demo

.PHONY: libs clean demo all vision_sdk_linux_demo kermod kermod_clean kermod_build

