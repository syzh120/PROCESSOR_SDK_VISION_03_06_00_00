
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx am335x am437x dra78x))
PACKAGE_SRCS_COMMON += cslr_uart.h csl_uart.h src/ip/uart/src_files_uart.mk src/ip/uart/V1
SRCS_COMMON += uart.c
SRCDIR += src/ip/uart/V1/priv
INCDIR += . src/ip/uart/V1
endif

ifeq ($(SOC),$(filter $(SOC), k2h k2k k2l k2e k2g c6657 c6678 omapl137 omapl138))
PACKAGE_SRCS_COMMON += cslr_uart.h src/ip/uart/src_files_uart.mk src/ip/uart/V0
SRCS_COMMON += uart.c
SRCDIR += src/ip/uart/V0/priv
INCDIR += . src/ip/uart/V0
endif
