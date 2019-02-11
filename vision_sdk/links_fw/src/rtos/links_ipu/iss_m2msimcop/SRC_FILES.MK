
ifeq ($(ISS_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
		issM2mSimcopLink_tsk.c issM2mSimcopLink_drv.c
endif
