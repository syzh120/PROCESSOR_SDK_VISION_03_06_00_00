##############################################################


EVEKERNELDB=     "../../../kernels"
EVE_COMMON_DIR= "../../../common"
##############################################################

##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libevePyramidLKTracker.eve.lib
##############################################################

##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc
CFLAGS+= -I ./src


CFLAGS+= -I $(KERNELS_DIR)/common
CFLAGS+= -I ../../../kernels/vlib/vcop_weight_computation/bam_helper
CFLAGS+= -I ../../../kernels/vlib/vcop_calc_determinant_tensor_matrix/bam_helper
CFLAGS+= -I ../../../kernels/vlib/vcop_calc_inverse_structure_tensor_2x2/bam_helper
CFLAGS+= -I ../../../kernels/vlib/vcop_multiblock_bilinear_interp_7x7_u8/bam_helper
CFLAGS+= -I ../../../kernels/vlib/vcop_multiblock_bilinear_interp_intlv_7x7_s16/bam_helper
CFLAGS+= -I ../../../kernels/vlib/vcop_multiblock_gradient_xy/bam_helper
CFLAGS+= -I ../../../kernels/vlib/vcop_tensor_matrix_7x7_s16_grad/bam_helper

##############################################################

##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################
