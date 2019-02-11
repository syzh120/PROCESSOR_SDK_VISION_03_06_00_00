
ifeq ($(SOC),$(filter $(SOC), k2h k2k k2l k2e k2g))

PACKAGE_SRCS_COMMON += csl_mdioAux.h  csl_mdio_def.h  csl_mdio.h  cslr_mdio.h
PACKAGE_SRCS_COMMON += src/ip/mdio/V0/csl_mdioAux.h src/ip/mdio/V0/csl_mdio.h
PACKAGE_SRCS_COMMON += src/ip/mdio/V0/cslr_mdio.h
PACKAGE_SRCS_COMMON += src/ip/mdio/src_files_mdio.mk src/ip/mdio/V0
SRCS_COMMON += cslr_mdio_resetread.c
SRCDIR += src/ip/mdio/V0
INCDIR += . src/ip/mdio/V0

endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_mdio.h src/ip/mdio/src_files_mdio.mk src/ip/mdio/V2
endif
