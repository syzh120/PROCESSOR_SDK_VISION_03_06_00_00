# Makefile for edma3 lld app

APP_NAME = edma3_drv_SIMc6657_sample

SRCDIR = ../src
INCDIR = ../src

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc edma3_lld

# List all the components required by the application
COMP_LIST_c6xdsp = edma3_lld_drv edma3_lld_rm

# XDC CFG File
XDC_CFG_FILE_c6xdsp = rtsc_config/edma3_drv_bios6_c6657_st_sample.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = common.c dma_misc_test.c dma_test.c qdma_test.c dma_chain_test.c \
              dma_ping_pong_test.c main.c dma_link_test.c dma_poll_test.c      \
              qdma_link_test.c
CFLAGS_LOCAL_COMMON =

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
