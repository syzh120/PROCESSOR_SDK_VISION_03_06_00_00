#
# This file is the makefile for building PM HAL OPTIMIZED library.
#
#   Copyright (c) Texas Instruments Incorporated 2017
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = pm_hal_optimized

INCLUDE_INTERNAL_INTERFACES = pm_hal_optimized
PM_CFLAGS += -DPM_OPTIMIZE

include makefile

#Nothing beyond this point
