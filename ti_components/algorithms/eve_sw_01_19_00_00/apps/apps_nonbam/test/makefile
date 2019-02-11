#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=../../../algframework
EVESTARTERWARE=../../../starterware

EVEKERNELSLIB=../../../kernels
EVECOMMON=../../../common
EVELIBAPPS=../../apps_nonbam
##############################################################


##############################################################
SUBDIRS=./common

CFILES_TEMP= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES_TEMP+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES_TEMP+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))
#remove any kernel test bench files
CFILES= $(filter-out %_tb.c, $(CFILES_TEMP))
CFILES+=$(EVECOMMON)/eve_profile.c
CFILES+=$(EVECOMMON)/ti_stats_collector.c

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ../inc
CFLAGS+= -I ./common
CFLAGS+= -I ../src
CFLAGS+= -I ../src/common
CFLAGS+= -I $(EVECOMMON)
CFLAGS+= -I $(EVESTARTERWARE)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_utils
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_csl

CFLAGS+= -I $(EVEKERNELSLIB)
CFLAGS+= -I $(EVEKERNELSLIB)/inc
CFLAGS+= -I $(EVEALGFRAMEWORK)/inc
##############################################################


##############################################################
LDFLAGS+= -l $(STARTERWARE_LIB)
LDFLAGS+= -l $(ARP32_TOOLS)/lib/rtsarp32_v200.lib
LDFLAGS+= -l $(EVEKERNELSLIB)/lib/$(TARGET_BUILD)/libevekernels.eve.lib
LDFLAGS+= -l $(EVEKERNELSLIB)/lib/$(TARGET_BUILD)/libevenatckernels.eve.lib
LDFLAGS+= -l $(EVELIBAPPS)/lib/$(TARGET_BUILD)/libeveapps.eve.lib
LDFLAGS+=  $(COMMON_LIBS)
LDFLAGS+= -l "./common/linker.cmd"
##############################################################

##############################################################
all : $(OUTDIR) $(OUTDIR)/evelib_fir_filter_2d_test.eve.out \
    $(OUTDIR)/evelib_edma_frame_padding_test.eve.out \
    $(OUTDIR)/evelib_fir_filter_2d_scattergather_test.eve.out \
    $(OUTDIR)/evelib_dma_image_copy_test.eve.out \
    $(OUTDIR)/evelib_harris_corner_detection_test.eve.out 
##############################################################


# If src exists, then link the individual object file,
# else, link the kernel library (as in for Object Release)
ifeq (,$(wildcard $(FILT_REF_SRC)))
FILT_REF=$(EVEKERNELSLIB)/lib/$(TARGET_BUILD)/libevenatckernels.eve.lib
else
endif

$(FILT_REF): $(FILT_REF_SRC)
	$(CC) $(CFLAGS) -c $^ --output_file=$@

##############################################################
$(BUILDDIR)/evelib_fir_filter_2d_test.obj : evelib_fir_filter_2d_test.c
	$(CC) $(CFLAGS) -c $^ --output_file=$@

$(OUTDIR)/evelib_fir_filter_2d_test.eve.out : $(BUILDDIR)/evelib_fir_filter_2d_test.obj $(FILT_REF) $(OFILES)
	$(LD) $(LDFLAGS) -l$(FILT_REF) --output_file=$@ $^ $(LDFILES) -m $@.map
##############################################################

##############################################################
$(BUILDDIR)/evelib_fir_filter_2d_scattergather_test.obj : evelib_fir_filter_2d_scattergather_test.c
	$(CC) $(CFLAGS) -c $^ --output_file=$@

$(OUTDIR)/evelib_fir_filter_2d_scattergather_test.eve.out : $(BUILDDIR)/evelib_fir_filter_2d_scattergather_test.obj $(FILT_REF) $(OFILES)
	$(LD) $(LDFLAGS) -l$(FILT_REF) --output_file=$@ $^ $(LDFILES) -m $@.map
##############################################################

##############################################################
$(BUILDDIR)/evelib_edma_frame_padding_test.obj : evelib_edma_frame_padding_test.c
	$(CC) $(CFLAGS) -c $^ --output_file=$@

$(OUTDIR)/evelib_edma_frame_padding_test.eve.out : $(BUILDDIR)/evelib_edma_frame_padding_test.obj $(OFILES)
	$(LD) $(LDFLAGS) --output_file=$@ $^ $(LDFILES) -m $@.map

$(BUILDDIR)/evelib_dma_image_copy_test.obj : evelib_dma_image_copy_test.c
	$(CC) $(CFLAGS) -c $^ --output_file=$@

$(OUTDIR)/evelib_dma_image_copy_test.eve.out : $(BUILDDIR)/evelib_dma_image_copy_test.obj $(OFILES)
	$(LD) $(LDFLAGS) --output_file=$@ $^ $(LDFILES) -m $@.map

##############################################################

##############################################################
HARRISCORNER_REF_SRC=$(wildcard $(EVEKERNELSLIB)/vlib/vcop_harrisScore_7x7/src_C/vcop_harrisScore_7x7_cn.c)
# If src exists, then link the individual object file,
# else, link the kernel library (as in for Object Release)
ifeq (,$(wildcard $(HARRISCORNER_REF_SRC)))
HARRISCORNER_REF=$(EVEKERNELSLIB)/lib/$(TARGET_BUILD)/libeveprivnatckernels.eve.lib 
else
HARRISCORNER_REF=$(EVEKERNELSLIB)/lib/$(TARGET_BUILD)/libeveprivnatckernels.eve.lib 
endif

$(BUILDDIR)/evelib_harris_corner_detection_test.obj : evelib_harris_corner_detection_test.c
	$(CC) $(CFLAGS) -c $^ --output_file=$@

$(OUTDIR)/evelib_harris_corner_detection_test.eve.out : $(BUILDDIR)/evelib_harris_corner_detection_test.obj $(HARRISCORNER_REF) $(OFILES)
	$(LD) $(LDFLAGS) -l$(HARRISCORNER_REF) --output_file=$@ $^ $(LDFILES) -m $@.map
##############################################################

##############################################################

##############################################################
$(BUILDDIR)/evelib_bayer2yuv422_test.obj : evelib_bayer2yuv422_test.c
	$(CC) $(CFLAGS) -c $^ --output_file=$@

$(OUTDIR)/evelib_bayer2yuv422_test.eve.out : $(BUILDDIR)/evelib_bayer2yuv422_test.obj $(OFILES)
	$(LD) $(LDFLAGS) --output_file=$@ $^ $(LDFILES) -m $@.map
##############################################################


