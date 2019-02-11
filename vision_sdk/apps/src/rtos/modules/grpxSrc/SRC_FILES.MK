
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/grpxSrc

SRCS_$(IPU_PRIMARY_CORE) += \
        grpxSrcLink_tsk.c \
        grpxSrcLink_cpu_load.c \

ifneq ($(RADAR_ONLY),yes)
  SRCS_$(IPU_PRIMARY_CORE) += \
        grpxSrcLink_srv_calib_layout.c \
        grpxSrcLink_sved_layout.c \
        grpxSrcLink_sv_sof_layout.c \
        grpxSrcLink_OF_layout.c \
        grpxSrcLink_stereo_layout.c \
        grpxSrcLink_stereo_multiFCalg_layout.c \
        grpxSrcLink_pd_tsr_ld_layout.c \
        grpxSrcLink_pd_tsr_ld_sof_layout.c \
        grpxSrcLink_pd_tsr_ld_sof_stereo_layout.c \
        grpxSrcLink_svStandalone_layout.c \
        grpxSrcLink_svStandalone_layout2.c \
        grpxSrcLink_fcAnalytics2_layout.c \
        grpxSrcLink_sfm.c \
        grpxSrcLink_Tda3x3DSv_layout.c \
        grpxSrcLink_Tda3x2D3DSv_layout.c \
        grpxSrcLink_Tda3xRearView3DSv_layout.c \
        grpxSrcLink_metadata_draw.c \
        grpxSrcLink_rvp_layout.c

ifeq ($(UC_semSeg),yes)
  SRCS_$(IPU_PRIMARY_CORE) += grpxSrcLink_sem_seg_layout.c
endif

ifeq ($(UC_tidl_OD),yes)
  SRCS_$(IPU_PRIMARY_CORE) += grpxSrcLink_tidl_od_layout.c
endif

endif


