
##############################################################

##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libeveEdgeDetector.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc


CFLAGS += -I ../../../kernels/imgsiglib/vcop_sobel_xy/bam_helper
CFLAGS += -I ../../../kernels/imgsiglib/vcop_yuv420_fir2d_separable/bam_helper
CFLAGS += -I ../../../kernels/vlib/vcop_vec_gradients_xy_and_magnitude/bam_helper
CFLAGS += -I ../../../kernels/vlib/vcop_canny_non_maximum_suppression/bam_helper
CFLAGS += -I src/bam_helper

##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

