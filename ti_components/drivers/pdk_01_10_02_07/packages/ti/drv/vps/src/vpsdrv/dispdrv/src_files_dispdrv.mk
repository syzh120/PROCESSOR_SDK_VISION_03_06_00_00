SRCS_COMMON += vpsdrv_displayApi.c vpsdrv_displayProc.c vpsdrv_displayCore.c vpsdrv_displayPriv.c vpsdrv_dctrl.c
PACKAGE_SRCS_COMMON += dispdrv ../../../include/vps_display.h ../../../include/vps_displayCtrl.h
ifeq ($(PACKAGE_DSS),yes)
PACKAGE_SRCS_COMMON += ../../../include/dss/vps_captureDssWb.h ../../../include/dss/vps_displayDss.h ../../../include/dss/vps_m2mDss.h
endif
