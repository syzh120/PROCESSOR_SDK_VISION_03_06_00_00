# file name: Rules.make
# set up the build environment

ifeq ($(vision_sdk_PATH), )

#
# Application to build for
#
# Supported Applications are:
#	sample_app
#	apps

MAKEAPPNAME?=apps

#
# Config to use
#
# Selecting a config selects the system config and modules to include
# in the build
#
# Edit the detailed config in file
# $(vision_sdk_PATH)/$(MAKEAPPNAME)/configs/$(MAKECONFIG)/cfg.mk
#
# Supported "out of box" configs are listed below
# - TDA2x Configs,
#    tda2xx_evm_bios_all
#    tda2xx_rvp_bios_all
#    tda2xx_evm_bios_opencx
#    tda2xx_evm_bios_radar
#    tda2xx_evm_linux_all
#    tda2xx_rvp_linux_all
#    tda2xx_evm_linux_infoadas
#    tda2xx_evm_linux_opencl
#    tda2xx_evm_linux_opencx
#    tda2xx_evm_robust_rvc
#
# - TDA3x Configs,
#    tda3xx_alps_bios_radar
#    tda3xx_evm_bios_all
#    tda3xx_evm_bios_radar
#    tda3xx_rvp_bios_all
#    tda3xx_evm_bios_iss
#    tda3xx_rvp_bios_iss
#
# - TDA2Ex Configs,
#    tda2ex_17x17_evm_linux_all
#    tda2ex_evm_bios_all
#    tda2ex_evm_linux_all
#    tda2ex_evm_linux_infoadas
#    tda2ex_evm_robust_rvc
#
# - TDA2Px Configs,
#    tda2px_evm_bios_all
#    tda2px_evm_bios_radar
#    tda2px_evm_linux_all
#    tda2px_evm_linux_infoadas
#    tda2px_evm_bios_iss
#
#
MAKECONFIG?=tda2xx_evm_bios_all

# Default build environment
# Options: Windows_NT or Linux
BUILD_OS ?= Linux
ifeq ($(OS),Windows_NT)
    BUILD_OS=Windows_NT
endif

#
# Set BUILD_MACHINE to 32BIT as required, this is needed only
# if A15_TARGET_OS is going to be Linux
#
# Options: 32BIT or 64BIT
BUILD_MACHINE ?= 64BIT

vision_sdk_RELPATH = vision_sdk
vision_sdk_PATH  := $(abspath ..)

# Application paths
$(MAKEAPPNAME)_PATH := $(vision_sdk_PATH)/$(MAKEAPPNAME)

include $($(MAKEAPPNAME)_PATH)/configs/defaults.mk
include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk
include $($(MAKEAPPNAME)_PATH)/configs/autorules_header_cfg.mk
include $(vision_sdk_PATH)/build/tools_path.mk
include $($(MAKEAPPNAME)_PATH)/configs/autorules_footer_cfg.mk

endif

include $(MAKERULEDIR)/build_config.mk
include $(MAKERULEDIR)/platform.mk
include $(MAKERULEDIR)/env.mk
include $(MAKERULEDIR)/component.mk

export MAKEAPPNAME
export $(MAKEAPPNAME)_PATH
export MAKECONFIG
