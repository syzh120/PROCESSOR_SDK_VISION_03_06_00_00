#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
##############################################################
EVEAPPS = "../../../apps"
EVEALGORITHMS = "../../../algorithms"

##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src
SUBDIRS+= ../../../common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./elf_out/test_orb.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I $(EVEALGORITHMS)/orb/algo/inc
##############################################################


##############################################################
LDFLAGS+= -l "$(EVEAPPS)/fast9_corner_detect/algo/lib/$(TARGET_BUILD)/libeveFast9CornerDetect.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)/rbrief/algo/lib/$(TARGET_BUILD)/libeveRbrief.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)/imagePyramid_u8/algo/lib/$(TARGET_BUILD)/libeveImagePyramid_u8.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)/harris_best_feature_to_front/algo/lib/$(TARGET_BUILD)/libeveHarrisBestFeatureToFront.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)/fast9_best_feature_to_front/algo/lib/$(TARGET_BUILD)/libeveFAST9BestFeatureToFront.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)/orb/algo/lib/$(TARGET_BUILD)/libeveorb.eve.lib"

LDFLAGS+= -l "./linker.cmd"
##############################################################


##############################################################
OUTDIR =  "./elf_out"

$(OUTFILE) : outfile
##############################################################

