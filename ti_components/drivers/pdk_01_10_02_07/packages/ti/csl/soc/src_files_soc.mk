PACKAGE_SRCS_COMMON += soc/src_files_soc.mk

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x tda3xx dra78x))
  PACKAGE_SRCS_COMMON += soc/common soc/$(SOC)
  SRCDIR += ./soc/common
  INCDIR += ./soc
  SRCS_COMMON += csl_device_xbar.c csl_device_common.c
else
  ifeq ($(SOC),$(filter $(SOC), am571x am572x am574x))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src
    SRCS_COMMON += csl_device_xbar.c csl_version.c csl_device_common.c
  endif

  ifeq ($(SOC),$(filter $(SOC), k2h k2k))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src
    SRCS_COMMON += csl_version.c csl_aif2GetBaseAddress.c csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c csl_cpIntcGetBaseAddress.c csl_srioGetBaseAddress.c
    SRCS_COMMON += csl_timerGetBaseAddress.c csl_pllcGetBaseAddress.c csl_mpuGetBaseAddress.c
    SRCS_COMMON += csl_emif4fGetBaseAddress.c
  endif

  ifeq ($(SOC),$(filter $(SOC), k2l))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/srcls

    SRCS_COMMON += csl_cpIntcGetBaseAddress.c  csl_edma3GetBaseAddress.c csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c csl_timerGetBaseAddress.c
    SRCS_COMMON += csl_emif4fGetBaseAddress.c csl_mpuGetBaseAddress.c
    SRCS_COMMON += csl_racGetBaseAddress.c csl_version.c
  endif

  ifeq ($(SOC),$(filter $(SOC), k2e))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src

    SRCS_COMMON += csl_cpIntcGetBaseAddress.c  csl_emif4fGetBaseAddress.c  csl_mpuGetBaseAddress.c
    SRCS_COMMON += csl_timerGetBaseAddress.c  csl_version.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c   csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c  csl_tsipGetBaseAddress.c
  endif

  ifeq ($(SOC),$(filter $(SOC), k2g))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src
    SRCS_COMMON += csl_cpIntcGetBaseAddress.c  csl_emif4fGetBaseAddress.c
    SRCS_COMMON += csl_mpuGetBaseAddress.c   csl_timerGetBaseAddress.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c   csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c  csl_version.c
  endif

  ifeq ($(SOC),$(filter $(SOC), omapl137))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src
    SRCS_COMMON += csl_emif4fGetBaseAddress.c
    SRCS_COMMON += csl_mpuGetBaseAddress.c   csl_timerGetBaseAddress.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c   csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c csl_version.c
  endif

  ifeq ($(SOC),$(filter $(SOC), omapl138))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src
#   SRCS_COMMON += csl_emif4fGetBaseAddress.c
    SRCS_COMMON += csl_mpuGetBaseAddress.c   csl_timerGetBaseAddress.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c   csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c csl_version.c
  endif

  ifeq ($(SOC),$(filter $(SOC), c6678))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src

    SRCS_COMMON += csl_cpIntcGetBaseAddress.c  csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c  csl_timerGetBaseAddress.c  csl_version.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c   csl_mpuGetBaseAddress.c
	SRCS_COMMON += csl_srioGetBaseAddress.c  csl_tsipGetBaseAddress.c
  endif

  ifeq ($(SOC),$(filter $(SOC), c6657))
    PACKAGE_SRCS_COMMON += soc/$(SOC)/src
    SRCDIR += ./soc/$(SOC)/src
    INCDIR += ./soc/$(SOC)/src

    SRCS_COMMON += csl_cpIntcGetBaseAddress.c  csl_gpioGetBaseAddress.c
    SRCS_COMMON += csl_pllcGetBaseAddress.c  csl_timerGetBaseAddress.c
    SRCS_COMMON += csl_edma3GetBaseAddress.c   csl_mpuGetBaseAddress.c
    SRCS_COMMON += csl_srioGetBaseAddress.c  csl_version.c
  endif

endif
