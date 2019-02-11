
ifeq ($(AVB_INCLUDE),yes)
ifeq ($(NDK_PROC_TO_USE),ipu1_1)
  SRCS_ipu1_1 += avbTxLink_drv.c avbTxLink_tsk.c
endif

ifeq ($(NDK_PROC_TO_USE),ipu1_0)
  SRCS_ipu1_0 += avbTxLink_drv.c avbTxLink_tsk.c
endif

ifeq ($(NDK_PROC_TO_USE),ipu2)
  SRCS_ipu2 += avbTxLink_drv.c avbTxLink_tsk.c
endif

ifeq ($(NDK_PROC_TO_USE),a15_0)
  SRCS_a15_0  += avbTxLink_drv.c avbTxLink_tsk.c
endif
endif
