
##############################################################

##############################################################


##############################################################
SUBDIRS = ./inc
SUBDIRS+= ./src

CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
HFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\lib\$(TARGET_BUILD)\libeveBeamForming.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc

CFLAGS+= -I $(KERNELS_DIR)/radarlib/vcop_beam_forming/inc
CFLAGS+= -I $(KERNELS_DIR)/radarlib/vcop_beam_forming/bam_helper


##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

