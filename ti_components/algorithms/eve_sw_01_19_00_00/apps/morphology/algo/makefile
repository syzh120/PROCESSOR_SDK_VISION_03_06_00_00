
##############################################################

##############################################################


##############################################################
SUBDIRS = ./inc
SUBDIRS+= ./src

CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
HFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

ifneq ($(TARGET_PLATFORM) , PC)
CFILES := $(filter-out %grayscale_morphology_host.c,$(CFILES))
HFILES := $(filter-out %grayscale_morphology_host.h,$(HFILES))
endif

OUTFILE=./lib/$(TARGET_BUILD)/libeveMorphology.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc

CFLAGS+= -I ../../../kernels/vlib/vcop_grayscale_morphology_flat/inc

##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

