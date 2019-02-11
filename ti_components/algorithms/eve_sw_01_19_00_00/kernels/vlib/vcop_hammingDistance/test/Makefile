# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_hamming_distance
TEST_BENCH = $(FILE)_tb
EVE_LCF =linker_boot.cmd

CFILES = ../src_C/$(FILE)_cn.c $(FILE)_config.c
KERNELFILES = ../src_kernelC/vcop_feature_matching_kernel.k

include ../../../common/Makefile.wincommon
TARGETLD_FLAGS = --define VCOP_CAMA

.PRECIOUS: translate.data
