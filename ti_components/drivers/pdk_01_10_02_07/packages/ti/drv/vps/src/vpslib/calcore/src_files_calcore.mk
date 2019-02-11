ifeq ($(PACKAGE_CAL),yes)
  ifeq ($(SOC),$(filter $(SOC), tda2px))
  PACKAGE_SRCS_COMMON += calcore
  SRCS_COMMON += vpscore_calapi.c
  endif
  ifeq ($(SOC),$(filter $(SOC), tda2ex))
  PACKAGE_SRCS_COMMON += calcore
  SRCS_COMMON += vpscore_calapi.c
  endif
endif

