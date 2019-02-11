#
# This file is the makefile for building PM LIB library.
#
#   Copyright (c) Texas Instruments Incorporated 2017
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = pm_lib

INCLUDE_INTERNAL_INTERFACES = pm_hal pm_lib

include makefile

#Nothing beyond this point
