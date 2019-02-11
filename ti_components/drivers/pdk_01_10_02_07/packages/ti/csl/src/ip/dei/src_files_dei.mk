
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x))
PACKAGE_SRCS_COMMON += cslr_dei.h src/ip/dei/src_files_dei.mk src/ip/dei/V0
endif
