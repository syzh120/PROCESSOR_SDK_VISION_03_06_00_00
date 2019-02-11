#*******************************************************************************
#* FILE PURPOSE: Top level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: makefile
#*
#* DESCRIPTION: Defines Compiler tools paths, libraries , Build Options 
#*
#*
#* This is an auto-generated file          
#*******************************************************************************
#*
# (Mandatory) Specify where various tools are installed.

# C6X_GEN_INSTALL_DIR   - C6x Code gen tools install directory
export C6X_GEN_INSTALL_DIR ?= C:/VLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/ti-cgt-c6000_8.2.4

# MSVC_GEN_INSTALL_DIR   - MS VC Code gen tools install directory
export MSVC_GEN_INSTALL_DIR ?= C:/PROGRA~2\MICROS~1.0\Common7\Tools\/../../
export MSVC_DIR ?= $(VSINSTALLDIR)\VC
export MSDK_DIR ?= C:/PROGRA~2/Windows Kits/8.0/

# PATH TO  EPI INSTALL DIR
export EPI_INSTALL_DIR     ?= C:/VLIB_Tools/xdc_eclipse_plugin_gen

# PATH TO  DMAUTILS INSTALL DIR
export DMAUTILS_INSTALL_DIR     ?= C:/VLIB_Tools/dsp_apps/dmautils

# VXLIB_INSTALL_DIR   - VXLIB install directory
export VXLIB_INSTALL_DIR ?= C:/ti/vxlib_c66x_1_1_3_0/packages

# PATH TO  ALGFRAMEWORK INSTALL DIR
export ALGFRAMEWORK_INSTALL_DIR     ?= C:/VLIB_Tools/dsp_apps/algframework

# ROOT Directory
export ROOTDIR := ../..

# INCLUDE Directory
export INCDIR := ;$(EPI_INSTALL_DIR)/20091203;$(ALGFRAMEWORK_INSTALL_DIR)/inc;$(DMAUTILS_INSTALL_DIR)/inc/baseaddress/vayu/dsp;$(DMAUTILS_INSTALL_DIR)/inc/edma_csl;$(DMAUTILS_INSTALL_DIR)/inc/edma_utils;$(VXLIB_INSTALL_DIR);$(EPI_INSTALL_DIR)/20091203;$(ALGFRAMEWORK_INSTALL_DIR)/inc;$(DMAUTILS_INSTALL_DIR)/inc/baseaddress/vayu/dsp;$(DMAUTILS_INSTALL_DIR)/inc/edma_csl;$(DMAUTILS_INSTALL_DIR)/inc/edma_utils;$(VXLIB_INSTALL_DIR);$(ROOTDIR)

# Common Macros used in make

ifndef RM
export RM = rm -f
endif

ifndef CP
export CP = cp -p
endif

export MKDIR = mkdir -p

ifndef RMDIR
export RMDIR = rm -rf
endif

ifndef SED
export SED = sed
endif

ifndef MAKE
export MAKE = make
endif

# PHONY Targets
.PHONY: all clean cleanall 

# FORCE Targets
FORCE: 

# all rule
all: .executables
.executables: .projects
.projects: .libraries
.libraries:

# Clean Rule
clean:: clean_package
# Clean Top Level Object Directory 
clean_package :
	$(RMDIR) package/lib
	$(RMDIR) package/cfg

# all,e66 rule
all,e66: .executables,e66
.executables,e66: .projects,e66
.projects,e66: .libraries,e66
.libraries,e66:


# Make rule to create lib/common.ae66 library
.libraries,e66 .libraries: lib/common.ae66
lib/common.ae66: FORCE
	$(MAKE) -f lib/common.ae66.mk $@
# Rule to clean lib/common.ae66 library
clean ::
	$(RM) lib/common.ae66


ifeq ($(OS),Windows_NT) # Windows Build Environment

# all,86 rule
all,86: .executables,86
.executables,86: .projects,86
.projects,86: .libraries,86
.libraries,86:

else # Linux Build Environment

# all,86l rule
all,86l: .executables,86l
.executables,86l: .projects,86l
.projects,86l: .libraries,86l
.libraries,86l:

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/common.a86 library
.libraries,86 .libraries: lib/common.a86
lib/common.a86: FORCE
	$(MAKE) -f lib/common.a86.mk $@
# Rule to clean lib/common.a86 library
clean ::
	$(RM) lib/common.a86

else # Linux Build Environment

# Make rule to create lib/common.a86l library
.libraries,86l .libraries: lib/common.a86l
lib/common.a86l: FORCE
	$(MAKE) -f lib/common.a86l.mk $@
# Rule to clean lib/common.a86l library
clean ::
	$(RM) lib/common.a86l

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# all,86_64W rule
all,86_64W: .executables,86_64W
.executables,86_64W: .projects,86_64W
.projects,86_64W: .libraries,86_64W
.libraries,86_64W:

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/common.a86_64W library
.libraries,86_64W .libraries: lib/common.a86_64W
lib/common.a86_64W: PATH:=$(MSVC_DIR)/bin/x86_amd64;$(PATH)
lib/common.a86_64W: FORCE
	$(MAKE) -f lib/common.a86_64W.mk $@
# Rule to clean lib/common.a86_64W library
clean ::
	$(RM) lib/common.a86_64W

endif



# Make rule to create lib/vxlib.ae66 library
.libraries,e66 .libraries: lib/vxlib.ae66
lib/vxlib.ae66: FORCE
	$(MAKE) -f lib/vxlib.ae66.mk $@
# Rule to clean lib/vxlib.ae66 library
clean ::
	$(RM) lib/vxlib.ae66


ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/vxlib.a86 library
.libraries,86 .libraries: lib/vxlib.a86
lib/vxlib.a86: FORCE
	$(MAKE) -f lib/vxlib.a86.mk $@
# Rule to clean lib/vxlib.a86 library
clean ::
	$(RM) lib/vxlib.a86

else # Linux Build Environment

# Make rule to create lib/vxlib.a86l library
.libraries,86l .libraries: lib/vxlib.a86l
lib/vxlib.a86l: FORCE
	$(MAKE) -f lib/vxlib.a86l.mk $@
# Rule to clean lib/vxlib.a86l library
clean ::
	$(RM) lib/vxlib.a86l

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/vxlib.a86_64W library
.libraries,86_64W .libraries: lib/vxlib.a86_64W
lib/vxlib.a86_64W: PATH:=$(MSVC_DIR)/bin/x86_amd64;$(PATH)
lib/vxlib.a86_64W: FORCE
	$(MAKE) -f lib/vxlib.a86_64W.mk $@
# Rule to clean lib/vxlib.a86_64W library
clean ::
	$(RM) lib/vxlib.a86_64W

endif



# Make rule to create lib/vxlib_cn.ae66 library
.libraries,e66 .libraries: lib/vxlib_cn.ae66
lib/vxlib_cn.ae66: FORCE
	$(MAKE) -f lib/vxlib_cn.ae66.mk $@
# Rule to clean lib/vxlib_cn.ae66 library
clean ::
	$(RM) lib/vxlib_cn.ae66


ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/vxlib_cn.a86 library
.libraries,86 .libraries: lib/vxlib_cn.a86
lib/vxlib_cn.a86: FORCE
	$(MAKE) -f lib/vxlib_cn.a86.mk $@
# Rule to clean lib/vxlib_cn.a86 library
clean ::
	$(RM) lib/vxlib_cn.a86

else # Linux Build Environment

# Make rule to create lib/vxlib_cn.a86l library
.libraries,86l .libraries: lib/vxlib_cn.a86l
lib/vxlib_cn.a86l: FORCE
	$(MAKE) -f lib/vxlib_cn.a86l.mk $@
# Rule to clean lib/vxlib_cn.a86l library
clean ::
	$(RM) lib/vxlib_cn.a86l

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/vxlib_cn.a86_64W library
.libraries,86_64W .libraries: lib/vxlib_cn.a86_64W
lib/vxlib_cn.a86_64W: PATH:=$(MSVC_DIR)/bin/x86_amd64;$(PATH)
lib/vxlib_cn.a86_64W: FORCE
	$(MAKE) -f lib/vxlib_cn.a86_64W.mk $@
# Rule to clean lib/vxlib_cn.a86_64W library
clean ::
	$(RM) lib/vxlib_cn.a86_64W

endif



# Make rule to create lib/vxlib_bamplugin.ae66 library
.libraries,e66 .libraries: lib/vxlib_bamplugin.ae66
lib/vxlib_bamplugin.ae66: FORCE
	$(MAKE) -f lib/vxlib_bamplugin.ae66.mk $@
# Rule to clean lib/vxlib_bamplugin.ae66 library
clean ::
	$(RM) lib/vxlib_bamplugin.ae66


ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/vxlib_bamplugin.a86 library
.libraries,86 .libraries: lib/vxlib_bamplugin.a86
lib/vxlib_bamplugin.a86: FORCE
	$(MAKE) -f lib/vxlib_bamplugin.a86.mk $@
# Rule to clean lib/vxlib_bamplugin.a86 library
clean ::
	$(RM) lib/vxlib_bamplugin.a86

else # Linux Build Environment

# Make rule to create lib/vxlib_bamplugin.a86l library
.libraries,86l .libraries: lib/vxlib_bamplugin.a86l
lib/vxlib_bamplugin.a86l: FORCE
	$(MAKE) -f lib/vxlib_bamplugin.a86l.mk $@
# Rule to clean lib/vxlib_bamplugin.a86l library
clean ::
	$(RM) lib/vxlib_bamplugin.a86l

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create lib/vxlib_bamplugin.a86_64W library
.libraries,86_64W .libraries: lib/vxlib_bamplugin.a86_64W
lib/vxlib_bamplugin.a86_64W: PATH:=$(MSVC_DIR)/bin/x86_amd64;$(PATH)
lib/vxlib_bamplugin.a86_64W: FORCE
	$(MAKE) -f lib/vxlib_bamplugin.a86_64W.mk $@
# Rule to clean lib/vxlib_bamplugin.a86_64W library
clean ::
	$(RM) lib/vxlib_bamplugin.a86_64W

endif


