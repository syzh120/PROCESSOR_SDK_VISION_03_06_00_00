
APP_NAME = vision_sdk

SRCDIR = src

INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk ipc vision_sdk fc xdais edma links_fw links_fw_rtos

# List all the components required by the application
COMP_LIST_a15_0 = bios xdc ipc vision_sdk

# XDC CFG File
XDC_CFG_FILE_a15_0 = MAIN_APP_a15_0.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_a15_0 = main_common_a15_0.c

# Include application main_app source code
include $($(MAKEAPPNAME)_PATH)/src/common/main_app/tda2xx/a15_0/src/SRC_FILES.MK

CFLAGS_LOCAL_a15_0 = $(vision_sdk_CFLAGS)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
