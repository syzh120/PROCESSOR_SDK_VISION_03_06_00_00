
SRCS_COMMON += bspdrv_ar12xx.c \
               bspdrv_ar12xxPriv.c \
               bspdrv_ar12xxMcspiCfgPriv.c \
               bspdrv_ar12xxGpioCfgPriv.c  \
               bspdrv_ar12xxOsalPriv.c \
               bspdrv_ar12xxUartCfgPriv.c \
               bspdrv_ar12xxFmwPriv.c \
               bspdrv_ar1243cfg.c   \
               bspdrv_ar12xxCrc.c \
               bspdrv_ar12xxInternal.c

SRCDIR += radar_ar12xx/src
INCDIR += radar_ar12xx/src

INCLUDE_EXTERNAL_INTERFACES += radarLink radarFirmware edma
