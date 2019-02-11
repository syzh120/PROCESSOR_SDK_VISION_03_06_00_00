ifeq ($(AVB_INCLUDE),yes)
UC_avbtx_vip_single_cam=yes
UC_avbrx_dec_display_avbtx=yes
UC_avbrx_sv_display_avbtx=yes
endif

UC_srv_calibration=yes
UC_lvds_vip_multi_cam_view=yes
UC_lvds_vip_sv_standalone=yes
UC_network_rx_tx=yes
UC_saveDisFrame=yes
UC_vip_single_cam_frame_copy=yes
UC_vip_single_cam_frame_copy_safety=yes
UC_vip_single_cam_tlr=yes
UC_vip_single_cam_view=yes
UC_csi2_cal_multi_cam_view=yes
UC_vip_single_cam_view_encdec=yes
UC_csi2_cal_sv_standalone=yes
UC_null_src_dec_display=yes
UC_null_src_display=yes

ifeq ($(OPENVX_INCLUDE),yes)
# OpenVX Usecase
UC_vip_single_cam_openvx=yes
endif

