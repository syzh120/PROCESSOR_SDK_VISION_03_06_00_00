
ifeq ($(ISS_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += issResizer_tsk.c issResizer_drv.c
endif

