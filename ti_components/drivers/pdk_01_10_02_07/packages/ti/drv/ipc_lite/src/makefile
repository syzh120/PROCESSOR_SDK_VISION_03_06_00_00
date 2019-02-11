#
# This file is the makefile for building Firewall library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = ipc_lib

SRCDIR = src src/$(SOC)
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(IPCLIB_CFLAGS)
PACKAGE_SRCS_COMMON = ipclib_interrupt.h ipclite_component.mk .gitignore
PACKAGE_SRCS_COMMON += ipclib_interruptTda2xx.h ipclib_interruptTda2px.h ipclib_interruptTda2ex.h ipclib_interruptTda3xx.h
PACKAGE_SRCS_COMMON += docs src

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),tda2xx)
SRCS_COMMON += ipclib_interruptTda2xx.c ipclib_interruptTda2xxMailboxCfg.c ipclib_interruptTda2xxProcCfg.c ipclib_interruptTda2xxXbarCfg.c
endif
ifeq ($(SOC),tda2px)
SRCS_COMMON += ipclib_interruptTda2px.c ipclib_interruptTda2pxMailboxCfg.c ipclib_interruptTda2pxProcCfg.c ipclib_interruptTda2pxXbarCfg.c
endif
ifeq ($(SOC),tda3xx)
SRCS_COMMON += ipclib_interruptTda3xx.c ipclib_interruptTda3xxMailboxCfg.c ipclib_interruptTda3xxProcCfg.c ipclib_interruptTda3xxXbarCfg.c
endif
ifeq ($(SOC),tda2ex)
SRCS_COMMON += ipclib_interruptTda2ex.c ipclib_interruptTda2exMailboxCfg.c ipclib_interruptTda2exProcCfg.c ipclib_interruptTda2exXbarCfg.c
endif
SRCS_COMMON += ipclib_interrupt.c

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
