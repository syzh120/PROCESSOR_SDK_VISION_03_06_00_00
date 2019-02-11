#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/pyramid_lk_tracker/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/pyramid_lk_tracker/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_evepyramidLKTracker.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc

CFLAGS+= -I $(ALGINCPATH)

CFLAGS+= -I ../../../kernels/vlib/vcop_weight_computation/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_copy_new_lk_xy/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_calc_determinant_tensor_matrix/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_calc_inverse_structure_tensor_2x2/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_multiblock_bilinear_interp_7x7_u8/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_multiblock_bilinear_interp_intlv_7x7_s16/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_multiblock_gradient_xy/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_tensor_matrix_7x7_s16_grad/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_weight_address_bilinear_interpolation/inc      
CFLAGS+= -I ../../../kernels/vlib/vcop_foreach_multiblock_bilinear_interp_7x7_u8/inc  
CFLAGS+= -I ../../../kernels/vlib/vcop_sum_grad_cross_inter_frame_diff_7x7/inc        
CFLAGS+= -I ../../../kernels/vlib/vcop_calc_new_lk_xy/inc
CFLAGS+= -I ../../../kernels/vlib/vcop_sad_error_measure_lk/inc

##############################################################


##############################################################
LDFLAGS+= -l "$(ALGLIBPATH)/libevePyramidLKTracker.eve.lib"
LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

