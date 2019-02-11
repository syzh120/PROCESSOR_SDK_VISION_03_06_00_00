# Makefile for EDMA3 LLD RM

MODULE_NAME = edma3_lld_rm

SRCDIR = src src/configs
INCDIR = . ../../../.. src

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES =

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = edma3resmgr.c edma3_rm_gbl_data.c
ifeq ($(CORE),c6xdsp)
CFLAGS_LOCAL_COMMON = -mi10
endif

# Defines for picking proper configuration based on the cores
ifeq ($(CORE),c6xdsp)
CFLAGS_LOCAL_c6a811x-evm = -DBUILD_C6A811X_DSP
endif
ifeq ($(CORE),a8host)
CFLAGS_LOCAL_c6a811x-evm = -DBUILD_C6A811X_A8
endif
ifeq ($(CORE),m3video)
CFLAGS_LOCAL_c6a811x-evm = -DBUILD_C6A811X_M3VIDEO
endif
ifeq ($(CORE),m3vpss)
CFLAGS_LOCAL_c6a811x-evm = -DBUILD_C6A811X_M3VPSS
endif
ifeq ($(CORE),a15host)
CFLAGS_LOCAL_tda2xx = -DBUILD_TDA2XX_MPU
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =
SRCS_c6472-evm = edma3_c6472_cfg.c
SRCS_tci6486-evm = edma3_tci6486_cfg.c
SRCS_tci6608-sim = edma3_tci6608_cfg.c
SRCS_tci6616-sim = edma3_tci6616_cfg.c
SRCS_tci6614-sim = edma3_tci6614_cfg.c
SRCS_c6657-sim = edma3_c6657_cfg.c
SRCS_tci6638k2k-sim = edma3_tci6638k2k_cfg.c
SRCS_c6670-evm = edma3_c6670_cfg.c
SRCS_c6678-evm = edma3_c6678_cfg.c
SRCS_tci6614-evm = edma3_tci6614_cfg.c
SRCS_c6657-evm = edma3_c6657_cfg.c
SRCS_tci6638k2k-evm = edma3_tci6638k2k_cfg.c
SRCS_tci6636k2h-evm = edma3_tci6636k2h_cfg.c
SRCS_tci6630k2l-evm = edma3_tci6630k2l_cfg.c
SRCS_c66ak2e-evm = edma3_c66ak2e_cfg.c
SRCS_tci66ak2g02-evm = edma3_tci66ak2g02_cfg.c
SRCS_omapl137-evm = edma3_omapl137_cfg.c
SRCS_omapl138-evm = edma3_omapl138_cfg.c
SRCS_c6748-evm = edma3_c6748_cfg.c
SRCS_da830-evm = edma3_da830_cfg.c
SRCS_omap4-evm = edma3_omap4_cfg.c
SRCS_ti814x = edma3_ti814x_cfg.c
SRCS_tda2xx = edma3_tda2xx_cfg.c
SRCS_tda3xx = edma3_tda3xx_cfg.c
SRCS_dra72x = edma3_dra72x_cfg.c
SRCS_ti816x = edma3_ti816x_cfg.c
SRCS_am335x = edma3_am335x_cfg.c
SRCS_am437x = edma3_am437x_cfg.c
SRCS_c6a811x-evm = edma3_c6a811x_cfg.c
SRCS_am572x = edma3_am572x_cfg.c
SRCS_am571x = edma3_am571x_cfg.c
CFLAGS_LOCAL_generic = -DGENERIC

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
