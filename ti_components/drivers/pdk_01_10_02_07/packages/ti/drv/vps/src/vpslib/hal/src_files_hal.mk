SRCS_COMMON += vpshal.c
PACKAGE_SRCS_COMMON += ../../../include/vps.h ../../../include/vps_cfgMem.h \
                       ../../../include/vps_dataTypes.h
ifeq ($(PACKAGE_VIP),yes)
  SRCS_COMMON += vpshal_csc.c vpshal_sc.c vpshal_vpdma.c
  SRCS_COMMON += vpshal_vipPort.c vpshal_vipTop.c
  PACKAGE_SRCS_COMMON += vpshal_vipPort.h vpshal_vipTop.h
  PACKAGE_SRCS_COMMON += vpshal_csc.h vpshal_sc.h                                  \
                         vpshal_vpdma.h vpshalVpdmaTda2xx.h vpshalVpdmaTI814x.h vpshalVpdmaTda3xx.h \
                         vpshal_cscDefaults.h vpshal_scDefaults.h vpshal_scPriv.h  \
                         vpshal_vpdmaPriv.h                                        \
                         vpshalVpdmaDefaultsTda2xx.h vpshalVpdmaDefaultsTI814x.h vpshalVpdmaDefaultsTda3xx.h \
                         vpshal_vpdmaFirmwareTda2xx_v1B8.h                       \
                         vpshal_vpdmaFirmwareTda2xx_v288.h
  PACKAGE_SRCS_COMMON += ../../../include/vip/vps_captureVipDataTypes.h \
                         ../../../include/vip/vps_cfgVipParser.h
  PACKAGE_SRCS_COMMON += ../../../include/vps_cfgCsc.h \
                         ../../../include/vps_cfgSc.h
endif

ifeq ($(PACKAGE_VPE),yes)
  ifneq ($(PACKAGE_VIP),yes)
    SRCS_COMMON += vpshal_csc.c vpshal_sc.c vpshal_vpdma.c
    PACKAGE_SRCS_COMMON += vpshal_csc.h vpshal_sc.h                                  \
                           vpshal_vpdma.h vpshalVpdmaTda2xx.h vpshalVpdmaTI814x.h vpshalVpdmaTda3xx.h \
                           vpshal_cscDefaults.h vpshal_scDefaults.h vpshal_scPriv.h  \
                           vpshal_vpdmaPriv.h                                        \
                           vpshalVpdmaDefaultsTda2xx.h vpshalVpdmaDefaultsTI814x.h vpshalVpdmaDefaultsTda3xx.h \
                           vpshal_vpdmaFirmwareTda2xx_v1B8.h                       \
                           vpshal_vpdmaFirmwareTda2xx_v288.h
  PACKAGE_SRCS_COMMON += ../../../include/vps_cfgCsc.h \
                         ../../../include/vps_cfgSc.h
  endif
  SRCS_COMMON += vpshal_vpeTop.c vpshal_dei.c vpshal_chrus.c
  PACKAGE_SRCS_COMMON += vpshal_chrus.h vpshal_dei.h vpshal_vpeTop.h           \
                         vpshalChrusDefaults.h vpshalDeiDefaults.h
  PACKAGE_SRCS_COMMON += ../../../include/vpe/vps_advCfgDei.h \
                         ../../../include/vpe/vps_cfgDei.h
endif

ifeq ($(PACKAGE_DSS),yes)
  ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x am572x tda2ex am571x am574x))
    SRCS_COMMON += vpshal_dssDispcVid.c vpshal_dssDispcOvly.c vpshal_dssHdmi.c
  endif
  ifeq ($(SOC),$(filter $(SOC), tda3xx))
    SRCS_COMMON += vpshal_dssDispcPipeTda3xx.c vpshal_dssDispcOvlyTda3xx.c vpshal_dssSdVenc.c
  endif
  PACKAGE_SRCS_COMMON += vpshal_dssDispcVid.h vpshal_dssDispcOvly.h vpshal_dssHdmi.h vpshal_dssSdVenc.h \
                         ../../../include/dss/vps_cfgDss.h ../../../include/vps_displayCtrlDataTypes.h
endif

ifeq ($(PACKAGE_ISS_COMMON),yes)
  SRCS_COMMON += vpshal_iss.c
  PACKAGE_SRCS_COMMON += vpshal_iss.h
endif

ifeq ($(PACKAGE_SIMCOP),yes)
  SRCS_COMMON += vpshal_issvtnf.c vpshal_isssimcop.c
  PACKAGE_SRCS_COMMON += vpshal_issvtnf.h vpshal_issldc.h vpshal_isssimcop.h
  ifeq ($(INCLUDE_WDR_LDC), yes)
    SRCS_COMMON += vpshal_issldc.c
  else
    SRCS_COMMON += vpshal_issldcdm.c
  endif
endif

ifeq ($(PACKAGE_CAL),yes)
  SRCS_COMMON += vpshal_isscal.c
  ifeq ($(SOC),$(filter $(SOC), tda3xx))
    SRCS_COMMON += vpshal_calCsi2Tda3x.c
  endif
  ifeq ($(SOC),$(filter $(SOC), tda2ex))
    SRCS_COMMON += vpshal_calCsi2Tda2ex.c
  endif
  ifeq ($(SOC),$(filter $(SOC), tda2px))
    SRCS_COMMON += vpshal_calCsi2Tda2px.c
  endif
  PACKAGE_SRCS_COMMON += vpshal_isscal.h vpshal_issCommon.h
  ifneq ($(PACKAGE_ISS_COMMON),yes)
    SRCS_COMMON += vpshal_iss.c
  endif
endif

ifeq ($(PACKAGE_ISP),yes)
  SRCS_COMMON += vpshal_issnsf3.c vpshal_isslvdsrx.c vpshal_issipipe.c \
                 vpshal_issisif.c vpshal_issrsz.c vpshal_issipipeif.c \
                 vpshal_issh3a.c
  PACKAGE_SRCS_COMMON += vpshal_issnsf3.h vpshal_isslvdsrx.h vpshal_issipipe.h \
                         vpshal_issisif.h vpshal_issrsz.h vpshal_issipipeif.h \
                         vpshal_issh3a.h vpshal_issglbce.h
  PACKAGE_SRCS_COMMON += ../../../include/iss/vps_cfgcal.h \
  ../../../include/iss/vps_cfgcnf.h ../../../include/iss/vps_cfgglbce.h \
  ../../../include/iss/vps_cfgh3a.h ../../../include/iss/vps_cfgipipe.h \
  ../../../include/iss/vps_cfgipipeif.h ../../../include/iss/vps_cfgisif.h \
  ../../../include/iss/vps_cfgisp.h ../../../include/iss/vps_cfgldc.h \
  ../../../include/iss/vps_cfgnsf3.h ../../../include/iss/vps_cfgrsz.h \
  ../../../include/iss/vps_cfgsimcop.h ../../../include/iss/vps_cfgvtnf.h \
  ../../../include/iss/vps_isscommon.h
  ifeq ($(INCLUDE_WDR_LDC), yes)
    SRCS_COMMON += vpshal_issglbce.c
  else
    SRCS_COMMON += vpshal_issglbcedm.c
  endif
endif

PACKAGE_SRCS_COMMON += $(SRCS_COMMON) vpshal.h src_files_hal.mk vpshal_platform.h
ifeq ($(INCLUDE_WDR_LDC), yes)
  SRCDIR += hal/src/wdrldc
  PACKAGE_SRCS_COMMON += src/wdrldc
endif
