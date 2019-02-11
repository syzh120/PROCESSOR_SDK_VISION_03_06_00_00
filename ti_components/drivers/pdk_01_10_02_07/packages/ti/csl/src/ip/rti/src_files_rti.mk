
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_rti.h csl_rti.h src/ip/rti/src_files_rti.mk src/ip/rti/V0
SRCDIR += src/ip/rti/V0/priv
INCDIR += src/ip/rti/V0
SRCS_COMMON += rti.c
endif
