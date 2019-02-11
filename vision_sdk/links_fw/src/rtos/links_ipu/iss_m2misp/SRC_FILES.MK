
ifeq ($(ISS_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
		issM2mIspLink_tsk.c issM2mIspLink_drv_apply_config.c \
		issM2mIspLink_drv_create_delete.c \
		issM2mIspLink_drv_process_frame.c
endif
