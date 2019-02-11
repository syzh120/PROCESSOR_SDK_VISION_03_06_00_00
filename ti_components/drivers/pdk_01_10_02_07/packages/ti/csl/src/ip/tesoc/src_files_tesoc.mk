
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_tesoc.h csl_tesoc.h src/ip/tesoc/src_files_tesoc.mk src/ip/tesoc/V0
SRCDIR += src/ip/tesoc/V0/priv
INCDIR += src/ip/tesoc/V0
SRCS_COMMON += tesoc.c
endif
