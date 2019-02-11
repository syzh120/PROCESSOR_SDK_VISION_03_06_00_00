
ifeq ($(NSP_TFDTP_INCLUDE),yes)
ifeq ($(NDK_PROC_TO_USE),ipu1_1)
  SRCS_ipu1_1 += tfdtpRxLink_drv.c tfdtpRxLink_tsk.c
endif

ifeq ($(NDK_PROC_TO_USE),ipu1_0)
  SRCS_ipu1_0 += tfdtpRxLink_drv.c tfdtpRxLink_tsk.c
endif

ifeq ($(NDK_PROC_TO_USE),ipu2)
  SRCS_ipu2 += tfdtpRxLink_drv.c tfdtpRxLink_tsk.c
endif

ifeq ($(NDK_PROC_TO_USE),a15_0)
  SRCS_a15_0  += tfdtpRxLink_drv.c tfdtpRxLink_tsk.c
endif
endif
