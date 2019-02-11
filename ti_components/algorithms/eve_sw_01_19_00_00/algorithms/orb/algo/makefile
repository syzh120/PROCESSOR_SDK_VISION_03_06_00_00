
##############################################################
EVEAPPS = "../../../apps"
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./lib/$(TARGET_BUILD)/libeveorb.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)/makerules/makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ./inc

CFLAGS+= -I $(EVEAPPS)/fast9_corner_detect/algo/inc
CFLAGS+= -I $(EVEAPPS)/rbrief/algo/inc
CFLAGS+= -I $(EVEAPPS)/imagePyramid_u8/algo/inc
CFLAGS+= -I $(EVEAPPS)/harris_best_feature_to_front/algo/inc
CFLAGS+= -I $(EVEAPPS)/fast9_best_feature_to_front/algo/inc
##############################################################


##############################################################
LIBDIR =  "./lib/$(TARGET_BUILD)"
OUTDIR =  "./elf_out"

$(OUTFILE) : libfile
##############################################################

