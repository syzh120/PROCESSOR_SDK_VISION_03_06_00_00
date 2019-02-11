SRCS_COMMON += vps_evtMgr.c vps_resrcMgr.c vps_graph.c
PACKAGE_SRCS_COMMON += common

ifeq ($(SOC),$(filter $(SOC), tda2px))
  SRCS_COMMON += vpslib_initTda2px.c
else ifeq ($(SOC),$(filter $(SOC), tda3xx))
  SRCS_COMMON += vpslib_initTda3xx.c
else
  SRCS_COMMON += vpslib_init.c
endif

ifeq ($(PACKAGE_ISS_COMMON),yes)
  SRCS_COMMON += iem_evtmgr.c
  PACKAGE_SRCS_COMMON += iem_evtmgr.h
endif

ifeq ($(PACKAGE_CAL), yes)
  SRCS_COMMON += irm_resrcMgr.c
  PACKAGE_SRCS_COMMON += irm_resrcMgr.h

  ifeq ($(SOC),$(filter $(SOC), tda2px))
  SRCS_COMMON += cal_evtmgr.c
  PACKAGE_SRCS_COMMON += cal_evtmgr.h
  endif

  ifeq ($(SOC),$(filter $(SOC), tda2ex))
  SRCS_COMMON += cal_evtmgr.c
  PACKAGE_SRCS_COMMON += cal_evtmgr.h
  endif
endif

