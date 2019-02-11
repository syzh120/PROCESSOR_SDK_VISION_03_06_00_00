
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_dcan.h csl_dcan.h src/ip/dcan/src_files_dcan.mk
PACKAGE_SRCS_COMMON += src/ip/dcan/V0/cslr_dcan.h src/ip/dcan/V0/dcan.h src/ip/dcan/V0/priv
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x ))
PACKAGE_SRCS_COMMON += src/ip/dcan/V0/V0_0
SRCDIR += src/ip/dcan/V0/priv
INCDIR += src/ip/dcan/V0
SRCS_COMMON += dcan.c
INCDIR += . src/ip/dcan/V0/V0_0
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += src/ip/dcan/V0/V0_1
SRCDIR += src/ip/dcan/V0/priv
INCDIR += src/ip/dcan/V0
SRCS_COMMON += dcan.c
INCDIR += . src/ip/dcan/V0/V0_1
endif
