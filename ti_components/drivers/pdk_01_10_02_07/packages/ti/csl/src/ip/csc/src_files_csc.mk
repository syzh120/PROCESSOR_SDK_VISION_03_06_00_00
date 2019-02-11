
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_csc.h src/ip/csc/src_files_csc.mk src/ip/csc/V0
endif
