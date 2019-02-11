
ifeq ($(SOC),$(filter $(SOC), tda3xx tda2ex dra78x dra72x am571x))
PACKAGE_SRCS_COMMON += cslr_cal.h src/ip/cal/src_files_cal.mk src/ip/cal/V0
endif
