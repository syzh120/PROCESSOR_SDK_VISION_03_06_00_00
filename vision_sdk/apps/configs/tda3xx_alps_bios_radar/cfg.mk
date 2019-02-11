#
# This file defines the modules included in $(MAKECONFIG) config
#
# Modules are split into,
# - Use-cases specified in uc_cfg.mk
# - Other system config/feature, specified in this file
#
# Any specific overrides are also specified in this file
# Example, for TDA3x SoC EVE2/3/4 are not present and hence force marked as <blank>, i.e disabled
#

#
# Additional config options
#

#
# CPUs to included in build
#
PROC_IPU1_0_INCLUDE=yes
PROC_IPU1_1_INCLUDE=yes
PROC_DSP1_INCLUDE=yes
PROC_DSP2_INCLUDE=no
PROC_EVE1_INCLUDE=yes


VSDK_BOARD_TYPE=TDA3XX_EVM

# Supported values: DDR_MEM_512M DDR_MEM_128M
DDR_MEM=DDR_MEM_128M

# Supported values: ipu1_0 ipu1_1 a15_0 none
NDK_PROC_TO_USE=ipu1_1

#Used to control TFDTP stack (supported values: yes no)
NSP_TFDTP_INCLUDE=yes

#Enable IPv6 Support
NDK_ENABLE_IPV6=no

# Supported values: ipu1_0 none
FATFS_PROC_TO_USE=none

WORKQ_INCLUDE=yes

#
# UART is not present on the board hence using network for logging
ENABLE_UART_LOG=no
ENABLE_NETWORK_LOG=yes

#
# Used to control building of algorithm source.
# By default algorithm source not included in Vision SDK
#
BUILD_ALGORITHMS=no



#
# Applies profile to all cores
#
# Supported profiles: release debug
#PROFILE=debug
PROFILE ?= release

PROFILE_ipu1_0 ?= $(PROFILE)
PROFILE_ipu1_1 ?= $(PROFILE)
PROFILE_c66xdsp_1 ?= $(PROFILE)
PROFILE_c66xdsp_2 ?= $(PROFILE)
PROFILE_arp32_1 ?= $(PROFILE)

DSS_INCLUDE=yes
CAL_INCLUDE=yes
ISS_INCLUDE=yes
ISS_ENABLE_DEBUG_TAPS=no
WDR_LDC_INCLUDE=yes

RTI_INCLUDE=no

#
# Use the Starterware IPC Library.
#
IPC_LIB_INCLUDE=yes

#
# EMIF ECC and Freedom from Interference (FFI) are clubbed together as they
# involve consolidated memory map changes
# ECC_FFI_INCLUDE=yes is not supported for DDR_MEM_128M
# If ECC_FFI_INCLUDE is set to no - memory map will match older versions.
# Firewall configuration and DSP XMC configuration is enabled/disabled using this
# flag
# Vision SDK does not enable EMIF ECC but expects SBL to enable it.
# Vision SDK sets up ECC error handlers irrespective of value of ECC_FFI_INCLUDE.
#
ECC_FFI_INCLUDE=no

#
# DCC is integrated in a way that requires ESM.
# Both modules are, therefore, clubbed together
# These are present only in TDA3XX
# Setting this to "no" only disables usage of these modules
# Source files are always enabled in build for TDA3XX
#
DCC_ESM_INCLUDE=no


#
# Enable below macro to enable DCAN integration into Vision SDK.
#
DCAN_INCLUDE=no

#
# Enable below macro when building in Radar SDK
#
RADAR_ONLY=yes
#
# Radar board type to be used
#
RADAR_BOARD=TDA3XX_AR12_ALPS

CPU_IDLE_ENABLED=yes

#
# Enable below macro to view the bandwidth used by different IPs in the device
# as a graphical plot on the display screen.
#
DATA_VIS_INCLUDE=no

HS_DEVICE=no

include $($(MAKEAPPNAME)_PATH)/configs/$(MAKECONFIG)/uc_cfg.mk
