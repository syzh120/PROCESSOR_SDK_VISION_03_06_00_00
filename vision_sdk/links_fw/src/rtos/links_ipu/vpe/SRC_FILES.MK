
ifeq ($(VPE_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += vpeLink_tsk.c vpeLink_drvCommon.c
SRCS_$(IPU_PRIMARY_CORE) += vpeLink_drv.c
endif

