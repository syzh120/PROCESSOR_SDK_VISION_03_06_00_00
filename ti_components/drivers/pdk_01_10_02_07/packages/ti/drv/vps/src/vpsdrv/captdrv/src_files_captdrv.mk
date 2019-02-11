SRCS_COMMON += vpsdrv_captureApi.c vpsdrv_captureProc.c vpsdrv_captureCore.c vpsdrv_capturePriv.c
PACKAGE_SRCS_COMMON += captdrv ../../../include/vps_capture.h
ifeq ($(PACKAGE_VIP),yes)
PACKAGE_SRCS_COMMON += ../../../include/vip/vps_captureVip.h
endif
ifeq ($(PACKAGE_ISP),yes)
PACKAGE_SRCS_COMMON += ../../../include/iss/vps_captureIss.h
endif