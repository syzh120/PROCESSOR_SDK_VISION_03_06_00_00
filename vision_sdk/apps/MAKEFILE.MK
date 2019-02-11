
include $(ROOTDIR)/build/rtos/makerules/platform.mk

# Application Algorithm plug in lib
APP_LIBS_$(IPU_PRIMARY_CORE) = $(DEST_ROOT)/lib/$(PLATFORM)/m4/$(PROFILE_$(IPU_PRIMARY_CORE))/app_alg_plugins.aem4
APP_LIBS_$(IPU_PRIMARY_CORE) += $(DEST_ROOT)/lib/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/app_libs.aem4
APP_LIBS_ipu1_1 = $(DEST_ROOT)/lib/$(PLATFORM)/m4/$(PROFILE_ipu1_1)/app_alg_plugins.aem4
APP_LIBS_$(IPU_SECONDARY_CORE) = $(DEST_ROOT)/lib/$(PLATFORM)/m4/$(PROFILE_$(IPU_SECONDARY_CORE))/app_alg_plugins.aem4
ifeq ($(AUTOSAR_APP), yes)
APP_LIBS_$(IPU_SECONDARY_CORE) += $(DEST_ROOT)/lib/$(PLATFORM)/$(IPU_SECONDARY_CORE)/$(PROFILE_$(IPU_SECONDARY_CORE))/app_libs.aem4
endif
APP_LIBS_c66xdsp_1 = $(DEST_ROOT)/lib/$(PLATFORM)/66/$(PROFILE_c66xdsp_1)/app_alg_plugins.ae66
APP_LIBS_c66xdsp_2 = $(DEST_ROOT)/lib/$(PLATFORM)/66/$(PROFILE_c66xdsp_2)/app_alg_plugins.ae66
APP_LIBS_arp32_1 = $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_1)/app_alg_plugins.aearp32F
APP_LIBS_arp32_2 = $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_2)/app_alg_plugins.aearp32F
APP_LIBS_arp32_3 = $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_3)/app_alg_plugins.aearp32F
APP_LIBS_arp32_4 = $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_4)/app_alg_plugins.aearp32F
APP_LIBS_a15_0 = $(DEST_ROOT)/lib/$(PLATFORM)/a15/$(PROFILE_a15_0)/app_alg_plugins.aa15fg

# Openvx libs
ifeq ($(OPENVX_INCLUDE),yes)

OPENVX_IPU_LIBS =
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_conformance_engine.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_conformance_tests.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_conformance_tests_testmodule.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_framework.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_kernels_host_utils.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_kernels_ivision.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_kernels_openvx_core.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_platform_vision_sdk_bios.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_tiovx_ivision_tests.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_tiovx_tests.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_tutorial.lib
OPENVX_IPU_LIBS += $(OpenVX_PATH)/lib/TDAX/M4/SYSBIOS/$(PROFILE)/vx_vxu.lib

OPENVX_DSP_LIBS =
OPENVX_DSP_LIBS += $(OpenVX_PATH)/lib/TDAX/C66/SYSBIOS/$(PROFILE)/vx_framework.lib
OPENVX_DSP_LIBS += $(OpenVX_PATH)/lib/TDAX/C66/SYSBIOS/$(PROFILE)/vx_kernels_target_utils.lib
OPENVX_DSP_LIBS += $(OpenVX_PATH)/lib/TDAX/C66/SYSBIOS/$(PROFILE)/vx_platform_vision_sdk_bios.lib
OPENVX_DSP_LIBS += $(OpenVX_PATH)/lib/TDAX/C66/SYSBIOS/$(PROFILE)/vx_target_kernels_openvx_core.lib
OPENVX_DSP_LIBS += $(OpenVX_PATH)/lib/TDAX/C66/SYSBIOS/$(PROFILE)/vx_target_kernels_openvx_core_bam.lib
OPENVX_DSP_LIBS += $(OpenVX_PATH)/lib/TDAX/C66/SYSBIOS/$(PROFILE)/vx_target_kernels_tutorial.lib
OPENVX_DSP_LIBS += $(VXLIB_PATH)/packages/ti/vxlib/lib/vxlib.ae66
OPENVX_DSP_LIBS += $(VXLIB_PATH)/packages/ti/vxlib/lib/vxlib_bamplugin.ae66
OPENVX_DSP_LIBS += $(algframework_PATH)/lib/dsp/$(PROFILE)/algframework.lib

OPENVX_EVE_LIBS =
OPENVX_EVE_LIBS += $(OpenVX_PATH)/lib/TDAX/EVE/SYSBIOS/$(PROFILE)/vx_framework.lib
OPENVX_EVE_LIBS += $(OpenVX_PATH)/lib/TDAX/EVE/SYSBIOS/$(PROFILE)/vx_kernels_target_utils.lib
OPENVX_EVE_LIBS += $(OpenVX_PATH)/lib/TDAX/EVE/SYSBIOS/$(PROFILE)/vx_platform_vision_sdk_bios.lib
OPENVX_EVE_LIBS += $(OpenVX_PATH)/lib/TDAX/EVE/SYSBIOS/$(PROFILE)/vx_target_kernels_ivision.lib
OPENVX_EVE_LIBS += $(OpenVX_PATH)/lib/TDAX/EVE/SYSBIOS/$(PROFILE)/vx_target_kernels_ivision_common.lib

OPENVX_A15_LIBS =
OPENVX_A15_LIBS += $(OpenVX_PATH)/lib/TDAX/A15/SYSBIOS/$(PROFILE)/libvx_framework.a
OPENVX_A15_LIBS += $(OpenVX_PATH)/lib/TDAX/A15/SYSBIOS/$(PROFILE)/libvx_platform_vision_sdk_bios.a
endif

ifneq ($(RADAR_ONLY),yes)
APP_LIBS_c66xdsp_1 += $(VXLIB_PATH)/packages/ti/vxlib/lib/vxlib.ae66
APP_LIBS_c66xdsp_1 += $(VXLIB_PATH)/packages/ti/vxlib/lib/vxlib_bamplugin.ae66
APP_LIBS_c66xdsp_2 += $(VXLIB_PATH)/packages/ti/vxlib/lib/vxlib.ae66
APP_LIBS_c66xdsp_2 += $(VXLIB_PATH)/packages/ti/vxlib/lib/vxlib_bamplugin.ae66
endif


# Application libs for IPU_PRIMARY_CORE
ifneq ($(RADAR_ONLY),yes)
ifeq ($(ISS_INCLUDE),yes)
	APP_LIBS_$(IPU_PRIMARY_CORE) += $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/alg_plugins/iss_aewb/lib/aewb_ipu1_0_$(PROFILE_ipu1_0).aem4
	APP_LIBS_$(IPU_PRIMARY_CORE) += $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/alg_plugins/iss_aewb/lib/iss_dcc_ipu1_0_$(PROFILE_ipu1_0).aem4
	APP_LIBS_$(IPU_PRIMARY_CORE) += $(DEST_ROOT)/lib/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/iss_libs.aem4
	APP_LIBS_$(IPU_PRIMARY_CORE) += $(scene_obstruction_detect_PATH)/modules/ti_scene_obstruction_detect/lib/arm/$(PROFILE)/sceneObstructionDetect_algo.aem4
endif
	APP_LIBS_$(IPU_PRIMARY_CORE) += $(DEST_ROOT)/lib/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/video_sensor_libs.aem4
endif
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_$(IPU_PRIMARY_CORE) += $(OPENVX_IPU_LIBS)
endif

APP_LIBS_$(IPU_PRIMARY_CORE) += $(radarLink_PATH)/ti/control/mmwavelink/lib/mmwavelink_m4.lib

# Application libs for ipu1_1
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_ipu1_1 += $(OPENVX_IPU_LIBS)
endif

ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_c66xdsp_1 += $(OPENVX_DSP_LIBS)
endif

DSP_ALG_LIBS += $(dsplib_PATH)/packages/ti/dsplib/lib/dsplib.ae66
DSP_ALG_LIBS += $(mmwavelib_PATH)/packages/ti/alg/mmwavelib/lib/libmmwavealg_xwr16xx.ae674
DSP_ALG_LIBS += $(mathlib_PATH)/packages/ti/mathlib/lib/mathlib.ae66
# Application libs for c66xdsp
ifeq ($(RADAR_ONLY),no)
DSP_ALG_LIBS += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/commonutils/lib/commonutils_c66xdsp_$(PROFILE_c66xdsp_1).ae66
DSP_ALG_LIBS += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/structurefrommotion/lib/structurefrommotion_c66xdsp_$(PROFILE_c66xdsp_1).ae66
DSP_ALG_LIBS += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/surroundview/lib/surroundview_c66xdsp_$(PROFILE_c66xdsp_1).ae66
DSP_ALG_LIBS += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/autocalibration/lib/autocalibration_c66xdsp_$(PROFILE_c66xdsp_1).ae66
DSP_ALG_LIBS += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/autoremap/lib/autoremap_c66xdsp_$(PROFILE_c66xdsp_1).ae66
DSP_ALG_LIBS += $(vlib_PATH)/packages/ti/vlib/lib/vlib.ae66
DSP_ALG_LIBS += $(vlib_PATH)/packages/ti/vlib/lib/vlib_cn.ae66
DSP_ALG_LIBS += $(vlib_PATH)/packages/ti/vlib/lib/common.lib
DSP_ALG_LIBS += $(lane_detect_PATH)/modules/ti_lane_detection/lib/dsp/$(PROFILE)/lane_detection_algo.lib
DSP_ALG_LIBS += $(gpe_PATH)/modules/ti_ground_plane_estimation/lib/dsp/$(PROFILE)/ti_gpe_algo.lib
DSP_ALG_LIBS += $(sfm_PATH)/modules/ti_sfm/lib/dsp/$(PROFILE)/ti_sfm_algo.lib
DSP_ALG_LIBS += $(clr_PATH)/modules/ti_circular_light_recognition/lib/dsp/$(PROFILE)/ti_circular_light_recognition_algo.lib
DSP_ALG_LIBS += $(fcw_PATH)/modules/ti_forward_collision_warning/lib/dsp/$(PROFILE)/ti_fcw_algo.lib
DSP_ALG_LIBS += $(object_detect_PATH)/modules/ti_object_detection/lib/dsp/$(PROFILE)/ti_object_detection.lib
DSP_ALG_LIBS += $(object_classification_PATH)/modules/ti_object_classification/lib/dsp/$(PROFILE)/ti_object_classification.lib
DSP_ALG_LIBS += $(dmautils_PATH)/libs/dsp/$(PROFILE)/dmautils.lib
DSP_ALG_LIBS += $(stereo_postprocess_PATH)/modules/ti_stereovision/lib/dsp/$(PROFILE)/stereovision_algo.lib
DSP_ALG_LIBS += $(scene_obstruction_detect_PATH)/modules/ti_scene_obstruction_detect/lib/dsp/$(PROFILE)/sceneObstructionDetect_algo.lib
ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px tda3xx))
	DSP_ALG_LIBS += $(tidl_PATH)/modules/ti_dl/lib/dsp/$(PROFILE)/tidl_algo.lib
	DSP_ALG_LIBS += $(tiop_PATH)/modules/ti_object_propagation/lib/dsp/$(PROFILE)/tiop_algo.ae66
endif
APP_LIBS_c66xdsp_1 +=$($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/rear_view_panorama/lib/rear_view_panorama_c66xdsp_$(PROFILE_c66xdsp_1).ae66
APP_LIBS_c66xdsp_2 +=$($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/rear_view_panorama/lib/rear_view_panorama_c66xdsp_$(PROFILE_c66xdsp_2).ae66
APP_LIBS_c66xdsp_1 +=$($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/stereo_app/lib/stereo_app_c66xdsp_$(PROFILE_c66xdsp_1).ae66
APP_LIBS_c66xdsp_2 +=$($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/stereo_app/lib/stereo_app_c66xdsp_$(PROFILE_c66xdsp_2).ae66
endif

ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_c66xdsp_2 += $(OPENVX_DSP_LIBS)
endif

# Application libs for dsp1
APP_LIBS_c66xdsp_1 += $(DSP_ALG_LIBS)

# Application libs for dsp2
APP_LIBS_c66xdsp_2 += $(DSP_ALG_LIBS)


# EVE algorithms libs
EVE_ALG_LIBS = $(algframework_PATH)/lib/eve/$(PROFILE)/algframework.lib
EVE_ALG_LIBS += $(dmautils_PATH)/libs/eve/$(PROFILE)/dmautils.lib
EVE_ALG_LIBS += $(evealg_PATH)/kernels/lib/$(PROFILE_arp32_1)/libevekernels.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/kernels/lib/$(PROFILE_arp32_1)/libevenatckernels.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/apps_nonbam/lib/$(PROFILE_arp32_1)/libeveapps.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/ti_pd_feature_plane_computation/algo/lib/$(PROFILE_arp32_1)/libeveFeaturePlaneComputation.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/clahe/algo/lib/$(PROFILE_arp32_1)/libeveClahe.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/soft_isp/algo/lib/$(PROFILE_arp32_1)/libeveSoftISP.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/census/algo/lib/$(PROFILE_arp32_1)/libeveCensus.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/disparity/algo/lib/$(PROFILE_arp32_1)/libeveDisparity.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/remap_merge/algo/lib/$(PROFILE_arp32_1)/libeveRemapMerge.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/imagePyramid_u8/algo/lib/$(PROFILE_arp32_1)/libeveImagePyramid_u8.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/harrisCornerDetection32/algo/lib/$(PROFILE_arp32_1)/libeveHarrisCornerDetection32.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/fft/algo/lib/$(PROFILE_arp32_1)/libeveFFT.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/peak_detection/algo/lib/$(PROFILE_arp32_1)/libevePeakDetection.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/beam_forming/algo/lib/$(PROFILE_arp32_1)/libeveBeamForming.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/pyramid_lk_tracker/algo/lib/$(PROFILE_arp32_1)/libevePyramidLKTracker.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/fast9_best_feature_to_front/algo/lib/$(PROFILE_arp32_1)/libeveFAST9BestFeatureToFront.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/fast9_corner_detect/algo/lib/$(PROFILE_arp32_1)/libeveFast9CornerDetect.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/yuv_padding/algo/lib/$(PROFILE_arp32_1)/libeveYUVPAdding.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/starterware/libs/vayu/eve/$(PROFILE_arp32_1)/libevestarterware_eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/algorithms/pyramid_lk_sof/algo/lib/$(PROFILE_arp32_1)/libevesof.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/filter_2d/algo/lib/$(PROFILE_arp32_1)/libeveFilter2D.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/yuv_scalar/algo/lib/$(PROFILE_arp32_1)/libeveYUVScalar.eve.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/bin_image_to_list/algo/lib/$(PROFILE_arp32_1)/libeveBinImageToList.eve.lib
ifeq ($(RADAR_ONLY),no)
EVE_ALG_LIBS += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/denseopticalflow/lib/libeveapps_opticalflow.eve.lib
ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px tda3xx))
	EVE_ALG_LIBS += $(tidl_PATH)/modules/ti_dl/lib/eve/$(PROFILE)/tidl_algo.lib
endif
endif

# Application libs for arp32_1
ifeq ($(RADAR_ONLY),no)
APP_LIBS_arp32_1 += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/edgedetection/lib/edgedetection_$(PROFILE_arp32_1).aearp32F
endif
APP_LIBS_arp32_1 += $(EVE_ALG_LIBS)
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_arp32_1 += $(OPENVX_EVE_LIBS)
endif

# Application libs for arp32_2
ifeq ($(RADAR_ONLY),no)
APP_LIBS_arp32_2 += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/edgedetection/lib/edgedetection_$(PROFILE_arp32_2).aearp32F
endif
APP_LIBS_arp32_2 += $(EVE_ALG_LIBS)
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_arp32_2 += $(OPENVX_EVE_LIBS)
endif

# Application libs for arp32_3
ifeq ($(RADAR_ONLY),no)
APP_LIBS_arp32_3 += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/edgedetection/lib/edgedetection_$(PROFILE_arp32_3).aearp32F
endif
APP_LIBS_arp32_3 += $(EVE_ALG_LIBS)
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_arp32_3 += $(OPENVX_EVE_LIBS)
endif

# Application libs for arp32_4
ifeq ($(RADAR_ONLY),no)
APP_LIBS_arp32_4 += $($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins/edgedetection/lib/edgedetection_$(PROFILE_arp32_4).aearp32F
endif
APP_LIBS_arp32_4 += $(EVE_ALG_LIBS)
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_arp32_4 += $(OPENVX_EVE_LIBS)
endif

# Application libs for a15_0
ifeq ($(OPENVX_INCLUDE),yes)
	APP_LIBS_a15_0 += $(OPENVX_A15_LIBS)
endif

ifeq ($(ENABLE_OPENCV),yes)

OpenCV_PATH =
ifeq ($(BUILD_OPENCV_SRC),yes)
OpenCV_PATH = $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/lib
else
OpenCV_PATH = $(OpenCV_PREBUILD_PATH)/libs_bios
endif

_OPENCVAPP_LIBS_a15_0 =
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_imgproc.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_imgcodecs.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_core.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PREBUILD_PATH)/libs_bios/libzlib.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PREBUILD_PATH)/libs_bios/libpng.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_genericio.a

ifeq ($(ENABLE_OPENCV_TESTS),yes)
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_calib3d.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_core.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_features2d.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_imgcodecs.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_imgproc.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_objdetect.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_photo.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_stitching.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_superres.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_video.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_perf_videoio.a

_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_calib3d.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_core.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_features2d.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_flann.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_highgui.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_imgcodecs.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_imgproc.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_ml.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_objdetect.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_photo.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_shape.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_stitching.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_superres.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_video.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_test_videoio.a
_OPENCVAPP_LIBS_a15_0 +=$(OpenCV_PATH)/libopencv_ts.a
endif
endif

export APP_LIBS_ipu1_0
export APP_LIBS_ipu1_1
export APP_LIBS_ipu2
export APP_LIBS_c66xdsp_1
export APP_LIBS_c66xdsp_2
export APP_LIBS_arp32_1
export APP_LIBS_arp32_2
export APP_LIBS_arp32_3
export APP_LIBS_arp32_4
export APP_LIBS_a15_0
export _OPENCVAPP_LIBS_a15_0
export OPENCLAPP_LIBS_a15_0

app_libs:
ifeq ($(PROC_IPU1_0_BUILD_INCLUDE),yes)
ifeq ($(IPU_PRIMARY_CORE),ipu1_0)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH) CORE=$(IPU_PRIMARY_CORE) $(TARGET)
endif
endif
endif

ifeq ($(PROC_IPU2_BUILD_INCLUDE),yes)
ifeq ($(IPU_PRIMARY_CORE),ipu2)
ifeq ($(PROC_IPU2_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH) CORE=$(IPU_PRIMARY_CORE) $(TARGET)
endif
endif
endif

ifeq ($(PROC_IPU2_BUILD_INCLUDE),yes)
ifeq ($(IPU_SECONDARY_CORE),ipu2)
ifeq ($(PROC_IPU2_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH) CORE=$(IPU_SECONDARY_CORE) $(TARGET)
endif
endif
endif

apps:
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/rtos apps

clean:
	$(MAKE) -fMAKEFILE.MK app_libs TARGET=clean

all: clean app_libs apps

iss_libs:
ifeq ($(ISS_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH)/src/rtos/iss CORE=$(IPU_PRIMARY_CORE) $(TARGET)
endif

iss_libs_clean:
ifeq ($(ISS_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH)/src/rtos/iss CORE=$(IPU_PRIMARY_CORE) $(TARGET)
endif

video_sensor_libs:
	$(MAKE) -C $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor CORE=$(IPU_PRIMARY_CORE) $(TARGET)


video_sensor_libs_clean:
	$(MAKE) -C $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor CORE=$(IPU_PRIMARY_CORE) $(TARGET)
