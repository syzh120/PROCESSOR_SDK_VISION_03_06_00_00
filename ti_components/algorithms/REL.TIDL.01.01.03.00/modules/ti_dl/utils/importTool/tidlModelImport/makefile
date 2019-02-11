#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
ifdef SystemRoot
ALGBASE_PATH ?= $(abspath ../../../../../)
COMMON_DIR= ../../../../../common
SUBDIRS= ../../tfImportCc/proto_cc/tensorflow/core/framework
CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cc))
CFILES += ../../caffeImportCc/caffe.pb.cc
CFILES += $(COMMON_DIR)/configparser.c
else
ALGBASE_PATH ?= $(abspath ../../../../)
COMMON_DIR= ../../../../common
SUBDIRS= ../tfImport/proto_cc/tensorflow/core/framework
CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cc))
CFILES += ../caffeImport/caffe.pb.cc
CFILES += $(COMMON_DIR)/configparser.c
endif

CFILES += tidl_import_main.cpp
CFILES += tidl_import_config.cpp
CFILES += tidl_import_common.cpp

#CFILES += ../tfImport/tidl_tfImport.cpp
#CFILES += ../caffeImport/tidl_caffeImport.cpp
CFILES += tidl_tfImport.cpp
CFILES += tidl_caffeImport.cpp

ifdef SystemRoot
HFILES = ../../caffeImportCc/caffe.pb.h
else
HFILES = ../caffeImport/caffe.pb.h
endif
HFILES += ti_dl.h

TARGET_PLATFORM = PC
ifdef SystemRoot
# Generating exe file one level above to avoid 
# updation of paths in import config files 
OUTFILE= ../tidl_model_import.out
else
OUTFILE=./out/tidl_model_import.out
endif
ifeq ($(PROTOBUF_LIB_DIR),)
$(call error,ERROR - PROTOBUF_LIB_DIR IS NOT DEFINED)
endif
ifeq ($(PROTOBUF_INC_DIR),)
$(call error,ERROR - PROTOBUF_INC_DIR IS NOT DEFINED)
endif
##############################################################

include $(ALGBASE_PATH)/makerules/rules.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I $(PROTOBUF_INC_DIR)
ifdef SystemRoot
CFLAGS+= -I ../../../inc
CFLAGS+= -I ../../caffeImportCc
CFLAGS+= -I ../../tfImportCc
CFLAGS+= -I ../../tfImportCc/proto_cc
else
CFLAGS+= -I ../../inc
CFLAGS+= -I ../caffeImport
CFLAGS+= -I ../tfImport
CFLAGS+= -I ../tfImport/proto_cc
endif
CFLAGS+= -I $(COMMON_DIR)

ifdef SystemRoot
CFLAGS+= /D_MSC_VER=1700 /Gd
CFLAGS+= /DTIDL_IMPORT_TOOL

ifeq ($(TARGET_BUILD), debug)
CFLAGS+= /D_DEBUG /MTd
else
CFLAGS+= /D_NDEBUG /MT
endif

##############################################################

##############################################################
ifeq ($(TARGET_BUILD), release)
LDFLAGS+=-l $(PROTOBUF_LIB_DIR)/libprotoc.lib
LDFLAGS+=-l $(PROTOBUF_LIB_DIR)/libprotobuf.lib
else
LDFLAGS+=-l $(PROTOBUF_LIB_DIR)/libprotocd.lib
LDFLAGS+=-l $(PROTOBUF_LIB_DIR)/libprotobufd.lib
endif

else
CFLAGS+=-DTIDL_IMPORT_TOOL
LDFLAGS= -L $(PROTOBUF_LIB_DIR)
LDFLAGS+= -lprotoc -lprotobuf
LDFLAGS+= -lpthread

ifeq ($(PLATFORM_BUILD), x86)
ifeq ($(LINUX_IMPORT_TOOL), 64BIT)
CFLAGS+= -DPLATFORM_64BIT 
endif
LDFLAGS+= -lstdc++ -static
else
LDFLAGS+= -lstdc++ -lz -static
endif
endif

##############################################################


##############################################################
OUTDIR =  "out"

$(OUTFILE) : outfile
##############################################################

