ifeq ($(OPENCL_INCLUDE),yes)
UC_vip_single_cam_openclcanny_edge=yes
UC_vip_single_cam_openclframe_copy=yes
endif

ifeq ($(ENABLE_OPENCV),yes)
UC_vip_single_cam_opencvcanny=yes
UC_vip_single_cam_opencvopencldilation=yes
ifeq ($(ENABLE_OPENCV_TESTS),yes)
    UC_vip_single_cam_opencvtests=yes
endif
endif

