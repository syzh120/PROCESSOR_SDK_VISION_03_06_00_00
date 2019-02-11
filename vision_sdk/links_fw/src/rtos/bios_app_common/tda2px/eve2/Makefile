
APP_NAME = vision_sdk

SRCDIR = src ../eve_common

INCDIR = . ../eve_common

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk ipc vision_sdk fc xdais edma \
	links_fw links_fw_rtos

# List all the components required by the application
COMP_LIST_arp32_2  = bios xdc ipc fc vision_sdk

# XDC CFG File
XDC_CFG_FILE_arp32_2  = MAIN_APP_eve2.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_arp32_2 = main_common_eve2.c tlb_config_eve2.c tlb_config_eve_common.c main_eve_common.c

# Include application main_app source code
include $($(MAKEAPPNAME)_PATH)/src/common/main_app/tda2px/eve2/src/SRC_FILES.MK

CFLAGS_LOCAL_arp32_2 = $(vision_sdk_CFLAGS)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
