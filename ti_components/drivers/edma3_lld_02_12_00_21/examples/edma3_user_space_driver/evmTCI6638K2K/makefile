# Makefile for edma3 lld app

APP_NAME = edma3_drv_6638k2k_a15_sample

SRCDIR = ../src ./
INCDIR = ../src

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = edma3_lld

# List all the components required by the application
COMP_LIST_a15 = edma3_lld_drv edma3_lld_rm

XDC_CFG_FILE_a15 =

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c evmTCI6638K2KSample.c
CFLAGS_LOCAL_COMMON =

# Libraries and Include paths
EXT_LIB_a15host = $(edma3_lld_drv_PATH)/lib/a15/$(PROFILE_$(CORE))/edma3_lld_drv.aa15fg $(edma3_lld_rm_PATH)/lib/tci6638k2k-evm/a15/$(PROFILE_$(CORE))/edma3_lld_rm.aa15fg -lrt -lpthread
EXT_INCLUDES = -I$(edma3_lld_drv_PATH) -I$(edma3_lld_rm_PATH) -I$(edma3_lld_PATH)/packages

# Include common make files
include $(ROOTDIR)/makerules/common.mk

# Nothing beyond this point


