
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x tda2px))
PACKAGE_SRCS_COMMON += cslr_mcan.h csl_mcan.h src/ip/mcan/src_files_mcan.mk src/ip/mcan/V0
SRCDIR += src/ip/mcan/V0/priv
INCDIR += src/ip/mcan/V0
SRCS_COMMON += mcan.c
endif
