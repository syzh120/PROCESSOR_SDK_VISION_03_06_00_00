# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_grayscale_morphology
TEST_BENCH = $(FILE)_tb

CFILES = ../src_C/$(FILE)_c.c ../src_kernelC/$(FILE).c $(FILE)_config.c

include ../../../common/Makefile.wincommon

TARGETLD_FLAGS = --define VCOP_CAMA
EVE_LCF = linker.cmd
