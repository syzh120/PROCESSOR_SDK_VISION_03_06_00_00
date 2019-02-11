
##############################################################

##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libeveHarrisBestFeatureToFront.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc

CFLAGS += -I../../../kernels/vlib/vcop_multipoint_harrisScore_u16/bam_helper
CFLAGS += -I../../../kernels/vlib/blockSortU32/bam_helper
CFLAGS += -I../../../kernels/vlib/vcop_prune_big_list/bam_helper
CFLAGS += -I../../../kernels/vlib/vcop_extract_bit_field_u32/bam_helper
CFLAGS += -I../../../kernels/vlib/blockSortU32/inc

##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

