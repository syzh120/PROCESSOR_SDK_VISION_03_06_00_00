PACKAGE_SRCS_COMMON += cslr_mmc.h cslr_mmchs.h csl_mmcsd.h src/ip/mmc/src_files_mmc.mk

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx am335x am437x dra78x))
PACKAGE_SRCS_COMMON +=src/ip/mmc/V0
SRCS_COMMON += mmcsd.c
SRCDIR += src/ip/mmc/V0/priv
INCDIR += . src/ip/mmc/V0
endif

ifeq ($(SOC),$(filter $(SOC), omapl137 omapl138))
PACKAGE_SRCS_COMMON +=src/ip/mmc/V1
SRCS_COMMON += mmcsd.c
SRCDIR += src/ip/mmc/V1/priv
INCDIR += . src/ip/mmc/V1
endif