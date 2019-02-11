##############################################################

##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libeveFAST9BestFeatureToFront.eve.lib
##############################################################

##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc


CFLAGS+= -I../../../kernels/vlib/vcop_fast9_score/bam_helper
CFLAGS+= -I../../../kernels/vlib/blockSortU32/bam_helper
CFLAGS+= -I../../../kernels/vlib/vcop_horizontal_non_max_suppression/bam_helper
CFLAGS+= -I../../../kernels/vlib/vcop_vertical_non_max_suppression/bam_helper
CFLAGS+= -I../../../kernels/vlib/vcop_prune_big_list/bam_helper
##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################
