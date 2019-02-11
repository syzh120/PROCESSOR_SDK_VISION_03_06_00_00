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

# MSVC_GEN_INSTALL_DIR   - MS VC98 Code gen tools install directory
export MSVC_GEN_INSTALL_DIR ?= C:/PROGRA~2\MICROS~1.0\Common7\Tools\/../../
export MSVC_DIR ?= $(VSINSTALLDIR)\VC
export MSDK_DIR ?= C:/PROGRA~2/Windows Kits/8.0/

# PATH TO  EPI INSTALL DIR
export EPI_INSTALL_DIR     ?= C:/VLIB_Tools/xdc_eclipse_plugin_gen

# PATH TO  VLIB INSTALL DIR
export VLIB_INSTALL_DIR     ?= C:/nightlybuilds/vlib/ti/vlib/vlib/packages

# ROOT Directory
export ROOTDIR := ..

# INCLUDE Directory
export INCDIR := $(EPI_INSTALL_DIR)/20091203;c:/nightlybuilds/vlib;$(VLIB_INSTALL_DIR);$(ROOTDIR)

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




# Make rule to create Regression/regress_d_c.ae66 library
.libraries,e66 .libraries: Regression/regress_d_c.ae66
Regression/regress_d_c.ae66: FORCE
	$(MAKE) -f Regression/regress_d_c.ae66.mk $@
# Rule to clean Regression/regress_d_c.ae66 library
clean ::
	$(RM) Regression/regress_d_c.ae66
