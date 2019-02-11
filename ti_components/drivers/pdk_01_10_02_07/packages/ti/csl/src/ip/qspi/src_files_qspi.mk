
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx am335x am437x dra78x))
PACKAGE_SRCS_COMMON += cslr_qspi.h csl_qspi.h src/ip/qspi/src_files_qspi.mk src/ip/qspi/V1
SRCS_COMMON += qspi.c
SRCDIR += src/ip/qspi/V1/priv
INCDIR += . src/ip/qspi/V1
endif

ifeq ($(SOC),$(filter $(SOC), k2h k2k k2e k2l k2g c6657 c6678))
PACKAGE_SRCS_COMMON += cslr_qspi.h csl_qspi.h src/ip/qspi/src_files_qspi.mk src/ip/qspi/V0
SRCS_COMMON += qspi.c
SRCDIR += src/ip/qspi/V0/priv
INCDIR += . src/ip/qspi/V0
endif
