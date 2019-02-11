
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x tda3xx am574x am572x am571x dra78x))

PACKAGE_SRCS_COMMON += arch/c66x
ifeq ($(ARCH),c66x)
SRCDIR += ./arch/c66x/src
INCDIR += ./arch/c66x
SRCS_COMMON += interrupt.c dsp_wugen.c dsp_config.c
SRCS_ASM_COMMON += intvecs.asm
ifeq ($(SOC),$(filter $(SOC), am574x tda2xx tda2px tda2ex tda3xx))
SRCS_COMMON += dsp_ecc.c dsp_icfg.c dsp_usrSpvSupport.c
SRCS_ASM_COMMON += swenr.asm
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
SRCS_COMMON += dsp_xmc.c
endif
endif

endif
