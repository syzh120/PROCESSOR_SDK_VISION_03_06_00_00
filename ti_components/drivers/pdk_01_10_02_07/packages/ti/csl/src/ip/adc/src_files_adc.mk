
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_adc.h csl_adc.h src/ip/adc/src_files_adc.mk src/ip/adc/V0
SRCDIR += src/ip/adc/V0/priv
INCDIR += src/ip/adc/V0
SRCS_COMMON += adc.c
endif
