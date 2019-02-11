
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x tda3xx dra78x am574x))
PACKAGE_SRCS_COMMON += cslr_ocmc_ecc.h csl_ocmc_ecc.h src/ip/ocmc/src_files_ocmc.mk src/ip/ocmc/V0
SRCDIR += src/ip/ocmc/V0/priv
INCDIR += src/ip/ocmc/V0
SRCS_COMMON += ocmc_ecc_l1.c ocmc_ecc_l2.c
endif
