
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x tda3xx dra78x am574x))
PACKAGE_SRCS_COMMON += cslr_mcasp.h csl_mcasp.h src/ip/mcasp/src_files_mcasp.mk src/ip/mcasp/V0
SRCS_COMMON += mcasp.c
SRCDIR += src/ip/mcasp/V0/priv
INCDIR += . src/ip/mcasp/V0
endif

ifeq ($(SOC),$(filter $(SOC), am335x am437x k2g omapl137 omapl138))
PACKAGE_SRCS_COMMON += cslr_mcasp.h csl_mcasp.h src/ip/mcasp/src_files_mcasp.mk src/ip/mcasp/V1
SRCS_COMMON += mcasp.c
SRCDIR += src/ip/mcasp/V1/priv
INCDIR += . src/ip/mcasp/V1
endif
