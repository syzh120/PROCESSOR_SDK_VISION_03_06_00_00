
APP_NAME = vision_sdk

SRCDIR = src

INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk ipc vision_sdk fc xdais edma \
	links_fw links_fw_rtos

# List all the components required by the application
COMP_LIST_arp32_1  = bios xdc ipc fc vision_sdk

# XDC CFG File
XDC_CFG_FILE_arp32_1  = MAIN_APP_eve1.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_arp32_1  = main_common_eve1.c tlb_config_eve1.c

# This is an example usage of file specific optimization levels.
# The format of CFLAGS_<filename_without_extension> = <Your desired file specific options>
# can be used for any specific file as part of EVE and DSP build.
CFLAGS_tlb_config_eve1 = --opt_level=0

# Include application main_app source code
include $($(MAKEAPPNAME)_PATH)/src/common/main_app/tda3xx/eve1/src/SRC_FILES.MK

CFLAGS_LOCAL_arp32_1 = $(vision_sdk_CFLAGS)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
