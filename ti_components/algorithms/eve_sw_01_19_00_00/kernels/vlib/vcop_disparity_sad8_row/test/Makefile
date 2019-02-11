# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_disparity_sad8_row
TEST_BENCH = $(FILE)_tb
KERNEL = ../src_kernelC/vcop_disparity_sad8_row
CFILES = ../src_C/$(FILE)_cn.c ../src_kernelC/init_disparity_sad8_row_params.c $(FILE)_config.c

HOSTFILES += $(KERNELFILES)

include ../../../common/Makefile.wincommon
