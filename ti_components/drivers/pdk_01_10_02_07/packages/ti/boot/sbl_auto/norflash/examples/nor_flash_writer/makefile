#
# This file is the makefile for building NOR FLash Writer.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = nor_flash_writer

SRCDIR = .
INCDIR = .

#Create the executable under SBL as this is used for flashing the SBL image, so
#logical to put this together with sbl image
$(APP_NAME)_BINPATH = $(DEST_ROOT)/sbl/$(APP_NAME)
export $(APP_NAME)_BINPATH

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON = csl stw_uartconsole stw_platform norflash_lib

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = util.c device.c norwriter.c
PACKAGE_SRCS_COMMON = .

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)

ifeq ($(CORE),ipu1_0)
 LNKCMD_FILE = lnk_m4.cmd
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
