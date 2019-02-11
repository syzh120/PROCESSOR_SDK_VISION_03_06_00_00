# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_clahe_generate_lut
TEST_BENCH = $(FILE)_tb
CFILES = ../src_C/$(FILE)_cn.c
#Below File name is Optional to specify . Default name is a.exe
HOST_EXE_FILE_NAME = vcop_clahe_generate_lut_kernel_tb.exe 
include ../../../common/Makefile.wincommon
TARGETLD_FLAGS = --define VCOP_CAMA
TARGETCC_FLAGS += --keep_asm
