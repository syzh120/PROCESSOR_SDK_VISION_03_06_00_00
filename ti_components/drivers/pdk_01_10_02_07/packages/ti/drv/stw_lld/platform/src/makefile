#
# This file is the makefile for building STW platform library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = stw_platform

SRCDIR = src src/$(SOC)
INCDIR = . src src/$(SOC)
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
SRCDIR += src/tda2xx
INCDIR += src/tda2xx
endif
ifeq ($(SOC), dra78x)
SRCDIR += src/tda3xx
INCDIR += src/tda3xx
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(STW_LLD_CFLAGS)
PACKAGE_SRCS_COMMON = . ../stw_lld_component.mk ../.gitignore ../makefile

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += platform.c stw_platform.c
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x))
SRCS_COMMON += irq_xbar.c dma_xbar.c chip_config.c
endif
SRCS_tda2xx += platform_tda2xx.c platform_tda2xx_pad_config.c stw_platformTda2xx.c
SRCS_tda2px += platform_tda2xx.c platform_tda2xx_pad_config.c stw_platformTda2xx.c
SRCS_tda2ex += platform_tda2xx.c platform_tda2xx_pad_config.c stw_platformTda2xx.c
SRCS_tda3xx += platform_tda3xx.c platform_tda3xx_pad_config.c stw_platformTda3xx.c
SRCS_dra75x += platform_tda2xx.c platform_tda2xx_pad_config.c stw_platformTda2xx.c
SRCS_dra72x += platform_tda2xx.c platform_tda2xx_pad_config.c stw_platformTda2xx.c
SRCS_dra78x += platform_tda3xx.c platform_tda3xx_pad_config.c stw_platformTda3xx.c
SRCS_ti814x += platform_ti814x.c

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
