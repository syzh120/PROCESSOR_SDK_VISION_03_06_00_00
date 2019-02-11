#
# This file is the makefile for building IPC Mailbox test app.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = ipc_lite_mbx_test_app

SRCDIR = .
INCDIR =

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON += csl csl_uart_console firewall ipc_lib vps_osal_baremetal
COMP_LIST_a15_0 = csl_init

# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .
SRCS_COMMON = main.c

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)


ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda3xx tda2ex))
ifeq ($(CORE),a15_0)
 LNKCMD_FILE = ./lnk_a15.cmd
endif

ifeq ($(CORE),c66xdsp_1)
 LNKCMD_FILE = ./lnk_dsp1.cmd
endif

ifeq ($(CORE),c66xdsp_2)
 LNKCMD_FILE = ./lnk_dsp2.cmd
endif

ifeq ($(CORE),ipu1_0)
 LNKCMD_FILE = ./lnk_ipu1_0.cmd
endif

ifeq ($(CORE),ipu1_1)
 LNKCMD_FILE = ./lnk_ipu1_1.cmd
endif

ifeq ($(CORE),ipu2_0)
 LNKCMD_FILE = ./lnk_ipu2_0.cmd
endif

ifeq ($(CORE),arp32_1)
 LNKCMD_FILE = ./lnk_arp32_1.cmd
endif

ifeq ($(CORE),arp32_2)
 LNKCMD_FILE = ./lnk_arp32_2.cmd
endif

ifeq ($(CORE),arp32_3)
 LNKCMD_FILE = ./lnk_arp32_3.cmd
endif

ifeq ($(CORE),arp32_4)
 LNKCMD_FILE = ./lnk_arp32_4.cmd
endif
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
LNKFLAGS_LOCAL_a15_0 += --entry Entry
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
