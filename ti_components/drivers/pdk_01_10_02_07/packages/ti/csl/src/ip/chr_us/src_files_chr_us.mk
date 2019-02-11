
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x))
PACKAGE_SRCS_COMMON += cslr_chr_us.h src/ip/chr_us/src_files_chr_us.mk src/ip/chr_us/V0
endif
