
#
# This file lists all possible modules that can be included in the build of Vision SDK
#
# Modules includes
# - algplugins
# - use-cases
#
# Config files present in vision_sdk/build/configs/<config-name>/
# select the exact modules that are included in the final Vision SDK build
#
# if <config-name> file does not mark a module as "yes", i.e its
# marked "no" or not defined then the module does not get included in the
# Vision SDK build
#


CHECK_YES = $(filter yes, $(subst emptyreplacement,,$(1)))
export CHECK_YES

include $($(MAKEAPPNAME)_PATH)/configs/$(MAKECONFIG)/cfg.mk

ALG_LIST = \
   ALG_autocalibration  \
   ALG_autoremap \
   ALG_census \
   ALG_clr \
   ALG_colortogray \
   ALG_crc \
   ALG_denseopticalflow \
   ALG_deWarp \
   ALG_disparityhamdist \
   ALG_dmaSwMs \
   ALG_vpeSwMs \
   ALG_drawRearview \
   ALG_edgedetection \
   ALG_framecopy \
   ALG_lanedetection \
   ALG_objectdetection \
   ALG_rear_view_panorama \
   ALG_remapmerge \
   ALG_safe_framecopy \
   ALG_sceneobstruction \
   ALG_sfm \
   ALG_softisp \
   ALG_sparseopticalflow \
   ALG_stereo_postprocessing \
   ALG_structurefrommotion \
   ALG_subframecopy \
   ALG_surroundview \
   ALG_opencvcanny \
   ALG_opencvopencldilation \
   ALG_opencvtests \
   ALG_openclcannyedge \
   ALG_openclframecopy \
   ALG_swcrc \
   ALG_rvcDiags \
   ALG_stereo_app \
   ALG_openvx \
   ALG_tidl \
   ALG_tiop \

RADAR_ALG_LIST = \
    ALG_radarprocess

ISS_ALG_LIST = \
    ALG_iss_aewb \
    ALG_iss_aewb2

RADAR_ALG_FXN_LIST = \
    ALG_FXN_radarframecopy \
    ALG_FXN_radardraw \
    ALG_FXN_radardspprocess \
    ALG_FXN_radardrawfftheatmap \
    ALG_FXN_radarfft2 \
    ALG_FXN_radarpeakdetect \
    ALG_FXN_radarbeamform

ifneq ($(RADAR_ONLY),yes)
UC_LIST = \
    UC_avbrx_sv \
    UC_avbrx_dec_display_avbtx \
    UC_avbrx_sv_display_avbtx \
    UC_avbtx_vip_single_cam \
    UC_fast_boot_iss_capture_isp_simcop_pd_display \
    UC_iss_capture_isp_simcop_display \
    UC_iss_monochrome_capt_isp_display \
    UC_iss_mult_capture_isp_2d_3d_sv_tda3x \
    UC_iss_mult_capture_isp_dewarp_3dsv_tda3xx \
    UC_iss_mult_capture_isp_dewarp_3dsv_rearview_tda3xx \
    UC_iss_mult_capture_isp_dewarp_stereo_tda3xx \
    UC_iss_mult_capture_isp_dewarp_stereoplus_tda3xx \
    UC_iss_mult_capture_isp_simcop_stereo_tda3xx \
    UC_iss_mult_capture_isp_simcop_sv_tda3xx \
    UC_iss_mult_capture_isp_stereo_autocalib_tda3xx \
    UC_iss_multi_inst_capture_display \
    UC_srv_calibration \
    UC_lvds_vip_dual_cam_dual_display \
    UC_lvds_vip_single_cam_view \
    UC_lvds_vip_multi_cam_view \
    UC_lvds_vip_8_cam_view \
    UC_lvds_vip_multi_cam_view_tda3xx \
    UC_lvds_vip_sv_analytics_us \
    UC_lvds_vip_sv_standalone \
    UC_lvds_vip_single_stereo \
    UC_lvds_vip_single_stereo_auto_calib \
    UC_lvds_vip_single_stereo_calibration \
    UC_lvds_vip_sv_tda3xx \
    UC_network_rx_tx \
    UC_network_stereo_display \
    UC_null_src_dec_display \
    UC_null_src_display \
    UC_tfdtprx_display \
    UC_ov490_vip_sv_standalone \
    UC_rear_view_panorama_tda3xx \
    UC_saveDisFrame \
    UC_vip_single_cam_analytics2 \
    UC_vip_single_cam_dense_optical_flow \
    UC_vip_single_cam_dual_display \
    UC_vip_single_cam_edge_detection \
    UC_vip_single_cam_frame_copy \
    UC_vip_single_cam_frame_copy_safety \
    UC_vip_single_cam_lane_detection \
    UC_vip_single_cam_object_detection2 \
    UC_vip_single_cam_sfm \
    UC_vip_single_cam_sparse_optical_flow \
    UC_vip_single_cam_subframe_copy \
    UC_vip_single_cam_tlr \
    UC_vip_single_cam_view \
    UC_vip_single_cam_view_autosar_app \
    UC_vip_single_cam_view_dsswb \
    UC_vip_single_cam_view_encdec \
    UC_vip_single_cam_display_metadata \
    UC_vip_single_cam_openclcanny_edge \
    UC_vip_single_cam_openclframe_copy \
    UC_vip_single_cam_opencvcanny \
    UC_vip_single_cam_opencvopencldilation \
    UC_vip_single_cam_opencvtests \
    UC_csi2_cal_multi_cam_view \
    UC_vip_single_rvc_cam_view_crc \
    UC_csi2_cal_sv_standalone \
    UC_vip_single_cam_openvx \
    UC_tidl \
    UC_nullSrc_null \
    UC_semSeg \
    UC_tidl_OD \
    UC_camera_radar_capture_display \
    UC_tidl_OD_radar_process_display \
    UC_early_capture_late_weston
else
UC_LIST =
endif

LINUX_TDA2XX_UC_LIST = \
	UC_avb_rx_multi_cam_decode_sgx_display \
	UC_avb_rx_multi_cam_3d_srv \
	UC_lvds_vip_multi_cam_3d_perception \
	UC_lvds_vip_multi_cam_3d_srv \
	UC_lvds_vip_multi_cam_2mp_3d_srv \
	UC_csi2Cal_multi_cam_3d_srv \
	UC_csi2Cal_multi_cam_3d_srv_cbb \
	UC_csi2Cal_multi_srv_calibration \
	UC_csi2Cal_multi_cam_view \
	UC_lvds_vip_multi_cam_3d_adaptive_srv \
	UC_lvds_vip_multi_cam_view_sgx_display \
	UC_lvds_vip_multi_cam_vpe_enc_null \
	UC_null_src_decode_display \
	UC_disp_dist_src_display \
	UC_ov490_vip_multi_cam_3d_srv \
	UC_vip_single_cam_connectorLinksA15_sgx_display \
	UC_vip_single_cam_dualSgxDisplay \
	UC_vip_single_cam_enc_dec_sgx_display \
	UC_vip_single_cam_framecopy_sgx_display \
	UC_vip_single_cam_framecopyEve_sgx_display \
	UC_vip_single_cam_opencvcanny_sgx_display \
	UC_vip_single_cam_opencvopencldilation_sgx_display \
	UC_vip_single_cam_sgx_display \
        UC_vip_single_cam_sgx_display_autosar_app \
	UC_iss_multi_cam_isp_sgx_3d_srv_display \
	UC_iss_multi_cam_isp_sgx_2mp_3d_srv \
	UC_iss_multi_cam_isp_sgx_2mp_3d_srv_adaptive \
	UC_lvds_vip_multi_cam_8ch_sgx_display \
	UC_lvds_vip_single_cam_view_sgx_display \
	UC_cascade_radar_capture_linux_only \
	UC_cascade_radar_datacollect

LINUX_DRA7XX_UC_LIST = \
    UC_a15source_2d_srv \
    UC_a15source_3d_srv \
    UC_buf_loop \
    UC_lvds_vip_2d_srv \
    UC_lvds_vip_3d_srv \
    UC_lvds_vip_multi_cam \
    UC_lvds_vip_single_cam \
    UC_lvds_vip_single_cam_analytics \
    UC_lvds_vip_single_cam_analytics2

RADAR_UC_LIST = \
    UC_radar_capture_only  \
    UC_radar_read_fft_write \
    UC_radar_objectdetect_display  \
    UC_radar_objectdetect_null  \
    UC_radar_capture_process \
    UC_multi_radar_capture_fft_display \
    UC_radar_read_objectdetect_write \
    UC_cascade_radar_capture_only \
	UC_cascade_radar_object_detect

ifeq ($(MAKECONFIG), $(filter $(MAKECONFIG), tda3xx_evm_bios_iss tda3xx_rvp_bios_iss tda2px_evm_bios_iss))
UC_LIST =
ISS_UC_LIST = \
    UC_iss_capture_isp_simcop_display
else
ISS_UC_LIST =
endif

UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/$(subst UC_,,$(uc))/cfg.mk)
UC_CFGS = $(foreach uc,$(UC_LIST),$(UC_CFG))

RADAR_UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/rtos/radar/src/usecases/$(subst UC_,,$(uc))/cfg.mk)
RADAR_UC_CFGS = $(foreach uc,$(RADAR_UC_LIST),$(RADAR_UC_CFG))

LINUX_TDA2XX_UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/hlos/adas/src/usecases/$(subst UC_,,$(uc))/cfg.mk)
LINUX_TDA2XX_UC_CFGS = $(foreach uc,$(LINUX_TDA2XX_UC_LIST),$(LINUX_TDA2XX_UC_CFG))

LINUX_DRA7XX_UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/hlos/infoadas/src/chains/$(subst UC_,,$(uc))/cfg.mk)
LINUX_DRA7XX_UC_CFGS = $(foreach uc,$(LINUX_DRA7XX_UC_LIST),$(LINUX_DRA7XX_UC_CFG))

#TESTSUITE_UC_ALG_CFG = $(if ($(vision_sdk_PATH)/testsuite/testsuite_cfg.mk),$(vision_sdk_PATH)/testsuite/testsuite_cfg.mk)

ISS_UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/rtos/iss_usecases/$(subst UC_,,$(uc))/cfg.mk)
ISS_UC_CFGS = $(foreach uc,$(ISS_UC_LIST),$(ISS_UC_CFG))

ALL_UC_LIST = $(UC_LIST) $(RADAR_UC_LIST) $(LINUX_TDA2XX_UC_LIST) $(LINUX_DRA7XX_UC_LIST) $(ISS_UC_LIST)

ifeq ($(A15_TARGET_OS), $(filter $(A15_TARGET_OS), Bios))
  include $(UC_CFGS) $(RADAR_UC_CFGS) $(TESTSUITE_UC_ALG_CFG) $(ISS_UC_CFGS)
else
  include $(UC_CFGS) $(RADAR_UC_CFGS) $(LINUX_TDA2XX_UC_CFGS) $(LINUX_DRA7XX_UC_CFGS) $(TESTSUITE_UC_ALG_CFG) $(ISS_UC_CFGS)
endif
