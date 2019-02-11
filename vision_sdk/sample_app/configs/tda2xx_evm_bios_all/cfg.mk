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
PROC_IPU2_INCLUDE=yes
PROC_A15_0_INCLUDE=yes
PROC_DSP1_INCLUDE=yes
PROC_DSP2_INCLUDE=yes
PROC_EVE1_INCLUDE=yes
PROC_EVE2_INCLUDE=yes
PROC_EVE3_INCLUDE=yes
PROC_EVE4_INCLUDE=yes


VSDK_BOARD_TYPE=TDA2XX_EVM

DUAL_A15_SMP_BIOS=no

# Supported values: DDR_MEM_512M
DDR_MEM=DDR_MEM_512M

# Supported values: ipu1_0 ipu1_1 a15_0 none
NDK_PROC_TO_USE=a15_0

#Used to control TFDTP stack (supported values: yes no)
NSP_TFDTP_INCLUDE=no

# Supported values: ipu1_0 none
FATFS_PROC_TO_USE=ipu1_0

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
PROFILE_ipu2 ?= $(PROFILE)
PROFILE_c66xdsp_1 ?= $(PROFILE)
PROFILE_c66xdsp_2 ?= $(PROFILE)
PROFILE_arp32_1 ?= $(PROFILE)
PROFILE_arp32_2 ?= $(PROFILE)
PROFILE_arp32_3 ?= $(PROFILE)
PROFILE_arp32_4 ?= $(PROFILE)
PROFILE_a15_0 ?= $(PROFILE)

#
# For TDA2xx & TDA2Ex - vision SDK can run on either IPU1 or IPU2 subsystem
# For TDA3xx - We have only IPU1 and hence IPU1 is the only option
# Select IPU primary core from the available IPU1 & IPU2 subsytems
#
# Supported values: ipu1_0 ipu2
IPU_PRIMARY_CORE=ipu1_0
IPU_SECONDARY_CORE=ipu2

#
# Set A15_TARGET_OS
# A15 can run Linux or Bios
#
#                 A15_TARGET_OS support
#   Platform        BIOS        Linux
#
#   TDA2XX_EVM      yes         yes
#   TDA3XX_EVM      yes         no
#   TDA2EX_EVM      yes         yes
#
# Supported values: Bios Linux
A15_TARGET_OS=Bios

IVAHD_INCLUDE=yes
VPE_INCLUDE=yes
DSS_INCLUDE=yes

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

AVB_INCLUDE=no

#
# Enable below macro to enable DCAN integration into Vision SDK.
#
DCAN_INCLUDE=no

CPU_IDLE_ENABLED=yes

#
# Enable below macro to view the bandwidth used by different IPs in the device
# as a graphical plot on the display screen.
#
DATA_VIS_INCLUDE=no

OPENCL_INCLUDE=no
ENABLE_OPENCV=no

HS_DEVICE=no

#
# Enable this macro to enable Ultra sonic based initialization
# This is added as the power measurement and Ultra sonic use the same
# pad on the device. Kindly note the Ultrasonic and power measurement
# use the same GPIO6_14/15 pads with different functionalities. Ultrasonic configures
# UART10 on those pads and power measurement configures I2C3. Hence when this
# macro is yes the power measurement functionality is not supported.
#
ULTRASONIC_INCLUDE=no

include $($(MAKEAPPNAME)_PATH)/configs/$(MAKECONFIG)/uc_cfg.mk
