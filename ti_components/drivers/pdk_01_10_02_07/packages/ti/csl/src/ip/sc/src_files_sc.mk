
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra75x tda2ex dra72x am571x tda3xx dra78x am574x))
PACKAGE_SRCS_COMMON += cslr_sc.h src/ip/sc/src_files_sc.mk src/ip/sc/V0
endif
