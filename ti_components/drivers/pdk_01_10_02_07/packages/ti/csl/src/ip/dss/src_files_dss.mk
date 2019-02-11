
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_dss.h src/ip/dss/src_files_dss.mk
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x))
PACKAGE_SRCS_COMMON += src/ip/dss/V1
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += src/ip/dss/V2
endif
