
ifeq ($(CAL_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
		issCaptureLink_tsk.c issCaptureLink_drv.c
endif
