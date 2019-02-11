# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_canny_non_maximum_suppression
TEST_BENCH = $(FILE)_tb
CFILES = ..\src_C\$(FILE)_cn.c $(FILE)_config.c
EVE_LCF = ./linker.cmd
include ../../../common/Makefile.wincommon
TARGETLD_FLAGS = --define VCOP_CAMA
