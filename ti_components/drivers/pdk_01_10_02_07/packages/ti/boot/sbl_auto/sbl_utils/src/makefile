#
# This file is the makefile for building sbl utils library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = sbl_utils

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
SRCDIR = src src/tda2xx
INCDIR = . src src/tda2xx
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SRCDIR = src src/tda3xx
INCDIR = . src src/tda3xx
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)
PACKAGE_SRCS_COMMON = .

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = sbl_utils_common.c
SRCS_tda3xx = sbl_utils_tda3xx.c sbl_utils_tda3xx_i2c.c sbl_utils_tda3xx_ddr_config.c
SRCS_tda2xx = sbl_utils_tda2xx.c sbl_utils_tda2xx_ddr_config.c sbl_utils_tda2xx_iodelay.c
SRCS_tda2px = sbl_utils_tda2xx.c sbl_utils_tda2px_ddr_config.c sbl_utils_tda2xx_iodelay.c
SRCS_tda2ex = sbl_utils_tda2xx.c sbl_utils_tda2ex_ddr_config.c sbl_utils_tda2xx_iodelay.c
SRCS_dra78x = sbl_utils_tda3xx.c sbl_utils_tda3xx_i2c.c sbl_utils_tda3xx_ddr_config.c
SRCS_dra75x = sbl_utils_tda2xx.c sbl_utils_tda2xx_ddr_config.c sbl_utils_tda2xx_iodelay.c
SRCS_dra72x = sbl_utils_tda2xx.c sbl_utils_tda2ex_ddr_config.c sbl_utils_tda2xx_iodelay.c

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
