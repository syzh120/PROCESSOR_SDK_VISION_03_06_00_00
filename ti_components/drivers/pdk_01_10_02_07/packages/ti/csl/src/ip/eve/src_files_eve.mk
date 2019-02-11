
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_eve.h src/ip/eve/src_files_eve.mk src/ip/eve/V0
endif
