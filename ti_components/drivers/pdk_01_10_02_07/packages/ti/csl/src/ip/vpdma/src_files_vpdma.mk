
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra75x tda2ex dra72x am571x tda3xx dra78x am574x))
PACKAGE_SRCS_COMMON += cslr_vpdma.h src/ip/vpdma/src_files_vpdma.mk src/ip/vpdma/V0
endif
