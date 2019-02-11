
##############################################################

##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
#SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libeveHarrisCornerDetection32.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc
CFLAGS+= -I $(ALG_FRAMEWORK_DIR)/src/bam_dma_nodes
CFLAGS+= -I $(KERNELS_DIR)/vlib/vcop_vec_gradients_xy_and_magnitude/bam_helper
CFLAGS+= -I $(KERNELS_DIR)/vlib/vcop_harrisScore_32_7x7/bam_helper
CFLAGS+= -I $(KERNELS_DIR)/vlib/vcop_nonMaxSuppress_mxn_S32/bam_helper
CFLAGS+= -I $(KERNELS_DIR)/vlib/vcop_generateList/bam_helper

##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

