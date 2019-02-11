
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x dra75x tda2ex dra72x am571x am574x))
PACKAGE_SRCS_COMMON += cslr_vpe.h src/ip/vpe/src_files_vpe.mk src/ip/vpe/V0
endif
