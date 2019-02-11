
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_esm.h csl_esm.h src/ip/esm/src_files_esm.mk src/ip/esm/V0
SRCDIR += src/ip/esm/V0/priv
INCDIR += src/ip/esm/V0
SRCS_COMMON += esm.c
endif
