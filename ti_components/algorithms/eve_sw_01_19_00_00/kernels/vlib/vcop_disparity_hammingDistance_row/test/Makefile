# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_disparity_hammingDistance_row
TEST_BENCH = $(FILE)_tb

CFILES = ../src_C/vcop_disparity_hammingDistance32_row_cn.c \
         ../src_C/vcop_disparity_hammingDistance64_row_cn.c \
	 ../src_kernelC/init_disparity_hammingDistance_row_params.c \
	 $(FILE)_config.c

KERNELFILES = ../src_kernelC/vcop_disparity_hammingDistance32_RL_row_kernel.k \
              ../src_kernelC/vcop_disparity_hammingDistance32_row_kernel.k \
	      ../src_kernelC/vcop_disparity_hammingDistance64_row_kernel.k\
	      ../src_kernelC/vcop_disparity_postprocess_kernel.k

HOSTFILES += $(KERNELFILES)

include ../../../common/Makefile.wincommon
