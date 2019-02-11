#
# BAM algorithm framework
#
# Framework for supporting block-based algorithms
#
# Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED 
#
#


##############################################################
#               Adding sub directories                       #
##############################################################
ALGBASE_PATH ?= $(abspath ../)

ifeq ($(TARGET_CPU),C71)
include $(ALGBASE_PATH)/makerules/config_c7x.mk
endif

SUBDIRS:=.\src\bam
SUBDIRS+=.\src\bam_dma_nodes
SUBDIRS+=.\src
ifndef SystemRoot
	SUBDIRS:= $(subst \,/,$(SUBDIRS))
endif

##############################################################
#               Indexing source files                        #
##############################################################

CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
HFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))


##############################################################
#               Including dsp makerules.mk                   #
##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
ifeq ($(CORE),eve)
LIBDIR  = .\lib\PC\$(CORE)\$(TARGET_BUILD)
else
LIBDIR  = .\lib\PC\$(CORE)\$(TARGET_BUILD)
endif
else
ifeq ($(CORE),eve)
LIBDIR  = .\lib\$(CORE)\$(TARGET_BUILD)
else
LIBDIR  = .\lib\$(CORE)\$(TARGET_BUILD)
endif
endif
OUTFILE=$(LIBDIR)\algframework.lib

ifeq ($(TARGET_CPU),C71)
include $(ALGBASE_PATH)/makerules/rules_c7x.mk
else
include $(ALGBASE_PATH)/makerules/rules.mk
endif

##############################################################
#               Additional CFLAGS                            #
##############################################################

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I $(DMAUTILS_PATH)
CFLAGS+= -I $(DMAUTILS_PATH)/inc
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_utils
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_csl
CFLAGS+= -I ./inc
CFLAGS+= -I ../common

ifeq ($(CORE) , dsp)
CFLAGS += -DCORE_DSP -DCORE_C6XX
endif

ifeq ($(CORE) , eve)
CFLAGS += -DCORE_EVE
endif

##############################################################
$(OUTFILE) : libfile

##############################################################


