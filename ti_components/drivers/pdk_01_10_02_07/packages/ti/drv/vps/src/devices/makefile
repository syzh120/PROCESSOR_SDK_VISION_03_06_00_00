#
# This file is the makefile for building VPS devices library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = vps_devices

SRCDIR = src tvp5158/src tvp7002/src sii9127/src mt9v022/src ov1063x/src \
         lcdCtrl/src tlc59108/src aic31/src ar0132/src sii9022a/src ioexp/src \
         ar0132rccc/src pga450/src pga460/src adv7611/src ov10640/src ar0140/src \
         imx224/src imx290/src ds90uh925/src ds90uh926/src ov2659/src ov2775/src \
         ov490/src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl vps_common vps_osal_tirtos fvid2

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(VPSLIB_CFLAGS) $(VPSDRV_CFLAGS)
PACKAGE_SRCS_COMMON = . ../../include/devices

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = bsp_device.c
ifeq ($(VPS_USE_TI_RTOS_I2C),yes)
  SRCS_COMMON += bsp_deviceI2cTiRtos.c
else
  INCLUDE_EXTERNAL_INTERFACES += xdc bios
  SRCS_COMMON += bsp_deviceI2c.c
endif

include tvp5158/src_files_tvp5158.mk
include sii9127/src_files_sii9127.mk
include ov1063x/src_files_ov1063x.mk
include lcdCtrl/src_files_lcdctrl.mk
include tlc59108/src_files_tlc59108.mk
include ar0132/src_files_ar0132.mk
include ar0140/src_files_ar0140.mk
include ar0132rccc/src_files_ar0132rccc.mk
include sii9022a/src_files_sii9022a.mk
include ds90uh925/src_files_ds90uh925.mk
include ds90uh926/src_files_ds90uh926.mk
include ioexp/src_files_ioexp.mk
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  include pga450/src_files_pga450.mk
  include pga460/src_files_pga460.mk
endif
include adv7611/src_files_adv7611.mk
include ov10640/src_files_ov10640.mk
include imx224/src_files_imx224.mk
include imx290/src_files_imx290.mk
include ov2775/src_files_ov2775.mk
include ov2659/src_files_ov2659.mk
ifeq ($(VPS_RADAR_INCLUDE),yes)
  include radar_ar12xx/src_files_ar12xx.mk
endif
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  include ov490/src_files_ov490.mk
endif

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
