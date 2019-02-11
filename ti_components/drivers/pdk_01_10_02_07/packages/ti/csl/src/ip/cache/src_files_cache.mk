
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x))
PACKAGE_SRCS_COMMON += cslr_cache.h src/ip/cache/src_files_cache.mk src/ip/cache/ipu/V0
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_cache.h src/ip/cache/src_files_cache.mk src/ip/cache/ipu/V1
endif
