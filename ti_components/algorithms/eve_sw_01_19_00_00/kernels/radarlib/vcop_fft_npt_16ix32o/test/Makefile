# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
FILE = vcop_fft_npt_16ix32o

TEST_BENCH = $(FILE)_tb

CFILES = ../src_C/vcop_fft_npt_16ix32o_cn.c \
         ../src_kernelC/vcop_fft_npt_16ix32o_wrapper.c \
         ../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_npt_16ix16o_gen_twiddleFactor.c \
        $(FILE)_config.c

CUSTOM_KERNELFILES = ../src_kernelC/vcop_fft_512_16ix32o_kernel
KERNELFILES += ../src_kernelC/vcop_fft_256_16ix32o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_128_16ix32o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_64_16ix32o_kernel.k
KERNELFILES += ../src_kernelC/vcop_fft_doppler_correction_32ix32o_kernel.k
KERNELFILES += ../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_512_16ix16o_32inter_kernel.k
KERNELFILES += ../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_256_16ix16o_32inter_kernel.k
KERNELFILES += ../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_128_16ix16o_32inter_kernel.k
KERNELFILES += ../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_64_16ix16o_32inter_kernel.k

# KERNELFILES
TARGETLD_FLAGS = --define VCOP_CAMA
EVE_LCF = linker.cmd
#HOSTFILES += $(KERNELFILES)
MSVC_CC_FLAGS += /D_DUMP=1 /D_FOR_FFT_O32_TEST_BENCH=1
include ../../../common/Makefile.wincommon