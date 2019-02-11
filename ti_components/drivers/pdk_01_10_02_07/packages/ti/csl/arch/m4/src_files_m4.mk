
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x tda3xx am574x am572x am571x dra78x))

PACKAGE_SRCS_COMMON += arch/m4 cslr_unicache_cfg.h
  ifeq ($(ARCH),armv7m)
  SRCDIR += ./arch/m4/src
  INCDIR += ./arch/m4
  SRCS_COMMON += interrupt.c ipu_wugen.c ammu.c unicache.c
    ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
      SRCS_COMMON += ipu_ecc.c
    endif
  endif

endif
