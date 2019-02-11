ifeq ($(OPENCL_INCLUDE),yes)
UC_vip_single_cam_openclframe_copy=yes
UC_vip_single_cam_framecopy_sgx_display=yes
endif

ifeq ($(ENABLE_OPENCV),yes)
UC_vip_single_cam_opencvcanny_sgx_display=yes
UC_vip_single_cam_opencvopencldilation_sgx_display=yes
endif
