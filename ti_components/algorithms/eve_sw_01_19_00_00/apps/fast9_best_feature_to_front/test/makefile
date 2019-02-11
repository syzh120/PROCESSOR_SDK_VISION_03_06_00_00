#******************************************************************************
#*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################


EVEALGORITHMS = "../../../apps"


ALGINCPATH= $(EVEALGORITHMS)/fast9_best_feature_to_front/algo/inc
ALGLIBPATH= $(EVEALGORITHMS)/fast9_best_feature_to_front/algo/lib/$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_eveFast9BestFeatureToFront.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc


CFLAGS+= -I $(ALGINCPATH)
CFLAGS+= -I../../../kernels/vlib/vcop_fast9_score/inc
CFLAGS+= -I../../../kernels/vlib/blockSortU32/inc
CFLAGS+= -I../../../kernels/vlib/vcop_horizontal_non_max_suppression/inc
CFLAGS+= -I../../../kernels/vlib/vcop_vertical_non_max_suppression/inc
CFLAGS+= -I../../../kernels/vlib/vcop_prune_big_list/inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LDFLAGS+= -l "$(ALGLIBPATH)/libeveFAST9BestFeatureToFront.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################
