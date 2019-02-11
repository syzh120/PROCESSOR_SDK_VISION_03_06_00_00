ifeq ($(PACKAGE_ISS_COMMON), yes)
   PACKAGE_SRCS_COMMON += isscore
   SRCS_COMMON += vpscore_isscommon.c
endif

ifeq ($(PACKAGE_CAL),yes)
  ifeq ($(SOC),$(filter $(SOC), tda3xx))
    SRCS_COMMON += vpscore_captureapi.c
  endif
endif

ifeq ($(PACKAGE_SIMCOP),yes)
  SRCS_COMMON += vpscore_simcop.c
endif
ifeq ($(PACKAGE_ISP),yes)
  SRCS_COMMON += vpscore_ispapi.c vpscore_isp.c
endif

ifeq ($(PACKAGE_ISS_COMMON), yes)
  ifeq ($(SOC),$(filter $(SOC), tda2px))
    SRCS_COMMON += vpscore_calm2m.c
  endif
endif
