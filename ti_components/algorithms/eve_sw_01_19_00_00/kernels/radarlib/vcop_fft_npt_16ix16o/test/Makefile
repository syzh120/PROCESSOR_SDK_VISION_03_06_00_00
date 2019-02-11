# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_fft_npt_16ix16o

TEST_BENCH = $(FILE)_tb

CFILES = ../src_C/vcop_fft_npt_16ix16o_cn.c \
         ../src_C/vcop_fft_npt_16ix16o_32inter_cn.c \
         ../src_kernelC/vcop_fft_npt_16ix16o_wrapper.c \
         ../src_kernelC/vcop_fft_npt_16ix16o_gen_twiddleFactor.c \
         ../src_kernelC/vcop_fft_npt_16ix16o_32inter_wrapper.c \
         $(FILE)_config.c

CUSTOM_KERNELFILES = ../src_kernelC/vcop_fft_1024_16ix16o_kernel
KERNELFILES += ../src_kernelC/vcop_fft_1024_16ix16o_kernel_overflow.k
KERNELFILES += ../src_kernelC/vcop_fft_512_16ix16o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_512_16ix16o_kernel_overflow.k
KERNELFILES += ../src_kernelC/vcop_fft_256_16ix16o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_256_16ix16o_kernel_overflow.k
KERNELFILES += ../src_kernelC/vcop_fft_128_16ix16o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_128_16ix16o_kernel_overflow.k
KERNELFILES += ../src_kernelC/vcop_fft_64_16ix16o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_64_16ix16o_kernel_overflow.k
KERNELFILES += ../src_kernelC/vcop_fft_512_16ix16o_32inter_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_256_16ix16o_32inter_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_128_16ix16o_32inter_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_64_16ix16o_32inter_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_doppler_correction_kernel.k

# KERNELFILES
TARGETLD_FLAGS = --define VCOP_CAMA
EVE_LCF = linker.cmd
#HOSTFILES += $(KERNELFILES)
MSVC_CC_FLAGS += /D_DUMP=1
include ../../../common/Makefile.wincommon