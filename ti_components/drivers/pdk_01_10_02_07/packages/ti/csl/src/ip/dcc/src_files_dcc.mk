
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_dcc.h csl_dcc.h src/ip/dcc/src_files_dcc.mk src/ip/dcc/V0
SRCDIR += src/ip/dcc/V0/priv
INCDIR += src/ip/dcc/V0
SRCS_COMMON += dcc.c
endif
