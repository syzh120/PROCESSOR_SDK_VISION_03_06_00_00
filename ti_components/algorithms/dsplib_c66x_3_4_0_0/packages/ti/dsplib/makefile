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
export C6X_GEN_INSTALL_DIR ?= c:/DSPLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2

# PATH TO  MATHLIB INSTALL DIR
export MATHLIB_INSTALL_DIR     ?= c:/ti/mathlib_c66x_3_1_0_0

# PATH TO  DSPLIB INSTALL DIR
export DSPLIB_INSTALL_DIR     ?= c:/nightlybuilds/dsplib

# ROOT Directory
export ROOTDIR := ../..

# INCLUDE Directory
export INCDIR := $(DSPLIB_INSTALL_DIR);$(MATHLIB_INSTALL_DIR)/packages;$(ROOTDIR)

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


# Make rule to create lib/dsplib.a66 library
.libraries: lib/dsplib.a66
lib/dsplib.a66: FORCE
	$(MAKE) -f lib/dsplib.a66.mk $@ 
# Rule to clean lib/dsplib.a66 library
clean ::
	$(RM) lib/dsplib.a66


# Make rule to create lib/dsplib.a66e library
.libraries: lib/dsplib.a66e
lib/dsplib.a66e: FORCE
	$(MAKE) -f lib/dsplib.a66e.mk $@ 
# Rule to clean lib/dsplib.a66e library
clean ::
	$(RM) lib/dsplib.a66e


# Make rule to create lib/dsplib.ae66 library
.libraries: lib/dsplib.ae66
lib/dsplib.ae66: FORCE
	$(MAKE) -f lib/dsplib.ae66.mk $@ 
# Rule to clean lib/dsplib.ae66 library
clean ::
	$(RM) lib/dsplib.ae66


# Make rule to create lib/dsplib.ae66e library
.libraries: lib/dsplib.ae66e
lib/dsplib.ae66e: FORCE
	$(MAKE) -f lib/dsplib.ae66e.mk $@ 
# Rule to clean lib/dsplib.ae66e library
clean ::
	$(RM) lib/dsplib.ae66e


# Make rule to create lib/dsplib_cn.a66 library
.libraries: lib/dsplib_cn.a66
lib/dsplib_cn.a66: FORCE
	$(MAKE) -f lib/dsplib_cn.a66.mk $@ 
# Rule to clean lib/dsplib_cn.a66 library
clean ::
	$(RM) lib/dsplib_cn.a66


# Make rule to create lib/dsplib_cn.a66e library
.libraries: lib/dsplib_cn.a66e
lib/dsplib_cn.a66e: FORCE
	$(MAKE) -f lib/dsplib_cn.a66e.mk $@ 
# Rule to clean lib/dsplib_cn.a66e library
clean ::
	$(RM) lib/dsplib_cn.a66e


# Make rule to create lib/dsplib_cn.ae66 library
.libraries: lib/dsplib_cn.ae66
lib/dsplib_cn.ae66: FORCE
	$(MAKE) -f lib/dsplib_cn.ae66.mk $@ 
# Rule to clean lib/dsplib_cn.ae66 library
clean ::
	$(RM) lib/dsplib_cn.ae66


# Make rule to create lib/dsplib_cn.ae66e library
.libraries: lib/dsplib_cn.ae66e
lib/dsplib_cn.ae66e: FORCE
	$(MAKE) -f lib/dsplib_cn.ae66e.mk $@ 
# Rule to clean lib/dsplib_cn.ae66e library
clean ::
	$(RM) lib/dsplib_cn.ae66e
