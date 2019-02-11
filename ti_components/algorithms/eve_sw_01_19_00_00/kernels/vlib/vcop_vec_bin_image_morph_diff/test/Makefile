# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_vec_bin_image_morph_diff
TEST_BENCH = $(FILE)_tb
CFILES = ..\src_C\$(FILE)_c.c $(FILE)_config.c

include ../../../common/Makefile.wincommon

TARGETLD_FLAGS = --define VCOP_CAMA
EVE_LCF = linker.cmd