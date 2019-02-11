#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
ifneq ($(TARGET_PLATFORM) , PC)
	@echo .
	@echo ======== EVE NON BAM APPLETS =================
	gmake -C ./apps_nonbam -f makefile
	@echo .
endif
	@echo ======== MORPHOLOGY =================
	gmake -C ./morphology -f makefile
	@echo .
	@echo ======== Integral Image  APPLET =================
	gmake -C ./integralImage/algo -f makefile
	@echo .
	@echo ======== Integral Image  TEST =================
	gmake -C ./integralImage/test -f makefile
	@echo .
	@echo ======== BLOCK SORT APPLET =================
	gmake -C ./blockSort_u32/algo -f makefile
	@echo .
	@echo ======== BLOCK SORT TEST =================
	gmake -C ./blockSort_u32/test -f makefile
	@echo .
	@echo ======== BLOCK STATISTICS =================
	gmake -C ./block_statistics -f makefile
	@echo .
	@echo ======== CLAHE =================
	gmake -C ./clahe -f makefile
	@echo .
	@echo ======== MEDIAN FILTERING =================
	gmake -C ./median_filter -f makefile
	@echo .
	@echo ======== REMAP APPLET =================
	gmake -C ./remap_merge -f makefile
	@echo .
	@echo ======== IMAGE PYRAMID APPLET =================
	gmake -C ./imagePyramid_u8/algo -f makefile
	@echo .
	@echo ======== IMAGE PYRAMID  TEST =================
	gmake -C ./imagePyramid_u8/test -f makefile
	@echo .
	@echo ======== FAST9 CORNER DETECT ALGO =================
	gmake -C ./fast9_corner_detect/algo -f makefile
	@echo .
	@echo ======== FAST9 CORNER DETECT TEST =================
	gmake -C ./fast9_corner_detect/test -f makefile
	@echo .
	@echo ======== Harris Corner 32-bits  APPLET =================
	gmake -C ./harrisCornerDetection32/algo -f makefile
	@echo .
	@echo ======== Harris Corner 32-bits  TEST =================
	gmake -C ./harrisCornerDetection32/test -f makefile
	@echo .
	@echo ======== SPARSE HARRIS CORNER DETECT =================
	gmake -C ./harris_best_feature_to_front -f makefile
	@echo .
	@echo ======== Soft Isp16 applet =================
	gmake -C ./soft_isp16 -f makefile
	@echo .
	@echo ======== Pyramid LK Tracker APPLET =================
	gmake -C ./pyramid_lk_tracker/algo -f makefile
	@echo .
	@echo ======== Pyramid LK Tracker TEST =================
	gmake -C ./pyramid_lk_tracker/test -f makefile
	@echo .
	@echo ======== RBRIEF APPLET =================
	gmake -C ./rbrief/algo -f makefile
	@echo .
	@echo ======== RBRIEF TEST =================
	gmake -C ./rbrief/test -f makefile
	@echo .
	@echo ======== fast9_best_feature_to_front ALGO =================
	gmake -C ./fast9_best_feature_to_front/algo -f makefile
	@echo .
	@echo ======== fast9_best_feature_to_front TEST =================
	gmake -C ./fast9_best_feature_to_front/test -f makefile
	@echo .
	@echo ======== GLCM =================
	gmake -C ./glcm -f makefile
	@echo .
	@echo ======== yuv_padding ALGO =================
	gmake -C ./yuv_padding/algo -f makefile
	@echo .
	@echo ======== yuv_padding TEST =================
	gmake -C ./yuv_padding/test -f makefile
	@echo .
	@echo ======== yuv_scalar ALGO =================
	gmake -C ./yuv_scalar/algo -f makefile
	@echo .
	@echo ======== yuv_scalar TEST =================
	gmake -C ./yuv_scalar/test -f makefile
	@echo .
	@echo ======== Filter 2D ALGO =================
	gmake -C ./filter_2d/algo -f makefile
	@echo .
	@echo ======== Filter 2D TEST =================
	gmake -C ./filter_2d/test -f makefile
	@echo .
	@echo ======== ti_pd_feature_plane_computation ALGO =================
	gmake -C ./ti_pd_feature_plane_computation/algo -f makefile
	@echo .
	@echo ======== ti_pd_feature_plane_computation TEST =================
	gmake -C ./ti_pd_feature_plane_computation/test -f makefile
	@echo .
	@echo ======== SOFT ISP =================
	gmake -C ./soft_isp -f makefile
	@echo .
	@echo ======== HOUGH FOR LINES =================
	gmake -C ./hough_for_lines -f makefile
	@echo .
	@echo ======== NMS =================
	gmake -C ./nms -f makefile
	@echo .
	@echo ======== Disparity APPLET =================
	gmake -C ./disparity/algo -f makefile
	@echo .
	@echo ======== Disparity TEST =================
	gmake -C ./disparity/test -f makefile
	@echo .
	@echo ======== Census  APPLET =================
	gmake -C ./census/algo -f makefile
	@echo .
	@echo ======== Census  TEST =================
	gmake -C ./census/test -f makefile
	@echo .
	@echo ======== FEATURE MATCHING =================
	gmake -C ./feature_matching -f makefile
	@echo .
	@echo ======== HOUGH FOR CIRCLES =================
	gmake -C ./hough_for_circles -f makefile
	@echo .
	@echo ======== Edge Detector =================
	gmake -C ./edge_detector -f makefile
	@echo .
	@echo ======== Bin Img To List =================
	gmake -C ./bin_image_to_list -f makefile
	@echo .
	@echo ======== Template matching APPLET =================
	gmake -C ./templateMatching/algo -f makefile
	@echo .
	@echo ======== Template matching TEST =================
	gmake -C ./templateMatching/test -f makefile
	@echo .  
	@echo ======== FFT applet =================
	gmake -C ./fft -f makefile
	@echo .  
	@echo ======== Beam Forming applet =================
	gmake -C ./beam_forming -f makefile
	@echo .
	@echo ======== Peak Detection applet =================
	gmake -C ./peak_detection -f makefile
	@echo .  
.IGNORE: clean
clean:
ifneq ($(TARGET_PLATFORM) , PC)
	@echo .
	@echo ======== EVE NON BAM APPLETS =================
	gmake -C ./apps_nonbam -f makefile clean
	@echo .
endif
	@echo ======== MORPHOLOGY =================
	gmake -C ./morphology -f makefile clean
	@echo .
	@echo ======== Integral Image  APPLET =================
	gmake -C ./integralImage/algo -f makefile clean
	@echo .
	@echo ======== Integral Image  TEST =================
	gmake -C ./integralImage/test -f makefile clean
	@echo .
	@echo ======== BLOCK SORT APPLET =================
	gmake -C ./blockSort_u32/algo -f makefile clean
	@echo .
	@echo ======== BLOCK SORT TEST =================
	gmake -C ./blockSort_u32/test -f makefile clean
	@echo .
	@echo ======== BLOCK STATISTICS =================
	gmake -C ./block_statistics -f makefile clean
	@echo .
	@echo ======== CLAHE =================
	gmake -C ./clahe -f makefile clean
	@echo .
	@echo ======== MEDIAN FILTERING =================
	gmake -C ./median_filter -f makefile clean
	@echo .
	@echo ======== REMAP APPLET =================
	gmake -C ./remap_merge -f makefile clean
	@echo .
	@echo ======== IMAGE PYRAMID APPLET =================
	gmake -C ./imagePyramid_u8/algo -f makefile clean
	@echo .
	@echo ======== IMAGE PYRAMID TEST =================
	gmake -C ./imagePyramid_u8/test -f makefile clean
	@echo .
	@echo ======== FAST9 CORNER DETECT ALGO =================
	gmake -C ./fast9_corner_detect/algo -f makefile clean
	echo .
	@echo ======== FAST9 CORNER DETECT TEST =================
	gmake -C ./fast9_corner_detect/test -f makefile clean
	@echo .
	@echo ======== Harris Corner 32-bits  APPLET =================
	gmake -C ./harrisCornerDetection32/algo -f makefile clean
	@echo .
	@echo ======== Harris Corner 32-bits  TEST =================
	gmake -C ./harrisCornerDetection32/test -f makefile clean
	@echo .
	@echo ======== Pyramid LK Tracker APPLET =================
	gmake -C ./pyramid_lk_tracker/algo -f makefile clean
	@echo .
	@echo ======== Pyramid LK Tracker TEST =================
	gmake -C ./pyramid_lk_tracker/test -f makefile clean
	@echo .
	@echo ======== SPARSE HARRIS CORNER DETECT =================
	gmake -C ./harris_best_feature_to_front -f makefile clean
	@echo .
	@echo ======== RBRIEF APPLET =================
	gmake -C ./rbrief/algo -f makefile clean
	@echo .
	@echo ======== RBRIEF TEST =================
	gmake -C ./rbrief/test -f makefile clean
	@echo .
	@echo ======== fast9_best_feature_to_front ALGO =================
	gmake -C ./fast9_best_feature_to_front/algo -f makefile clean
	@echo .
	@echo ======== fast9_best_feature_to_front TEST =================
	gmake -C ./fast9_best_feature_to_front/test -f makefile clean
	@echo .
	@echo ======== GLCM =================
	gmake -C ./glcm -f makefile clean
	@echo .
	@echo ======== ti_pd_feature_plane_computation ALGO =================
	gmake -C ./ti_pd_feature_plane_computation/algo -f makefile clean
	@echo .
	@echo ======== ti_pd_feature_plane_computation TEST =================
	gmake -C ./ti_pd_feature_plane_computation/test -f makefile clean
	@echo .
	@echo ======== yuv_padding ALGO =================
	gmake -C ./yuv_padding/algo -f makefile clean
	@echo .
	@echo ======== yuv_padding TEST =================
	gmake -C ./yuv_padding/test -f makefile clean
	@echo .
	@echo ======== yuv_scalar ALGO =================
	gmake -C ./yuv_scalar/algo -f makefile clean
	@echo .
	@echo ======== yuv_scalar TEST =================
	gmake -C ./yuv_scalar/test -f makefile clean
	@echo .
	@echo ======== Filter 2D ALGO =================
	gmake -C ./filter_2d/algo -f makefile clean
	@echo .
	@echo ======== Filter 2D TEST =================
	gmake -C ./filter_2d/test -f makefile clean
	@echo .
	@echo ======== SOFT ISP =================
	gmake -C ./soft_isp -f makefile clean
	@echo .
	@echo ======== Soft Isp16 applet =================
	gmake -C ./soft_isp16/algo -f makefile clean
	@echo .
	@echo ======== HOUGH FOR LINES =================
	gmake -C ./hough_for_lines -f makefile clean
	@echo .
	@echo ======== NMS =================
	gmake -C ./nms -f makefile clean
	@echo .  
	@echo ======== Disparity APPLET =================
	gmake -C ./disparity/algo -f makefile clean
	@echo .
	@echo ======== Disparity TEST =================
	gmake -C ./disparity/test -f makefile clean
	@echo .
	@echo ======== Census APPLET =================
	gmake -C ./census/algo -f makefile clean
	@echo .
	@echo ======== Census TEST =================
	gmake -C ./census/test -f makefile clean
	@echo .
	@echo ======== FEATURE MATCHING =================
	gmake -C ./feature_matching -f makefile clean
	@echo .
	@echo ======== Template matching APPLET =================
	gmake -C ./templateMatching/algo -f makefile clean
	@echo .
	@echo ======== Template matching TEST =================
	gmake -C ./templateMatching/test -f makefile clean
	@echo .  
	@echo ======== HOUGH FOR CIRCLES =================
	gmake -C ./hough_for_circles -f makefile clean
	@echo .
	@echo ======== Edge Detector =================
	gmake -C ./edge_detector -f makefile clean
	@echo .
	@echo ======== Bin Img To List =================
	gmake -C ./bin_image_to_list -f makefile clean
	@echo .
	@echo ======== FFT applet =================
	gmake -C ./fft -f makefile clean
	@echo .
	@echo ======== Beam foring applet =================
	gmake -C ./beam_forming -f makefile clean
	@echo .
	@echo ======== Peak Detection applet =================
	gmake -C ./peak_detection -f makefile clean
    
