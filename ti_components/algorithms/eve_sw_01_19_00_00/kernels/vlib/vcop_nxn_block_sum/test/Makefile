# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_nxn_block_sum
TEST_BENCH = $(FILE)_tb
CFILES = ../src_C/$(FILE)_cn.c
#Below File name is Optional to specify . Default name is a.exe
HOST_EXE_FILE_NAME = vcop_nxn_block_sum_kernel_tb.exe 
include ../../../common/Makefile.wincommon
TARGETLD_FLAGS = --define VCOP_CAMA
TARGETCC_FLAGS += --keep_asm
