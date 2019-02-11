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

# PATH TO  VXLIB INSTALL DIR
export VXLIB_INSTALL_DIR     ?= C:/nightlybuilds/vxlib/ti/vxlib/vxlib/packages

# PATH TO  ALGFRAMEWORK INSTALL DIR
export ALGFRAMEWORK_INSTALL_DIR     ?= C:/VLIB_Tools/dsp_apps/algframework

# ROOT Directory
export ROOTDIR := ..

# INCLUDE Directory
export INCDIR := ;$(EPI_INSTALL_DIR)/20091203;$(ALGFRAMEWORK_INSTALL_DIR)/inc;$(DMAUTILS_INSTALL_DIR)/inc/baseaddress/vayu/dsp;$(DMAUTILS_INSTALL_DIR)/inc/edma_csl;$(DMAUTILS_INSTALL_DIR)/inc/edma_utils;c:/nightlybuilds/vxlib;$(EPI_INSTALL_DIR)/20091203;$(ALGFRAMEWORK_INSTALL_DIR)/inc;$(DMAUTILS_INSTALL_DIR)/inc/baseaddress/vayu/dsp;$(DMAUTILS_INSTALL_DIR)/inc/edma_csl;$(DMAUTILS_INSTALL_DIR)/inc/edma_utils;c:/nightlybuilds/vxlib;$(VXLIB_INSTALL_DIR);$(ROOTDIR)

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



.executables,86 .executables: make_dependent_86

make_dependent_86: 
	-@$(MAKE) -C $(VXLIB_INSTALL_DIR)/ti/vxlib all,86

.executables: make_dependent

make_dependent: 
	-@$(MAKE) -C $(VXLIB_INSTALL_DIR)/ti/vxlib all

cleanall: clean_dependent 

clean_dependent: 
	-@$(MAKE) -C $(VXLIB_INSTALL_DIR)/ti/vxlib clean


ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create Regression/WINPC//RegressionTest.exe executable
.executables,86 .executables: Regression/WINPC//RegressionTest.exe
Regression/WINPC//RegressionTest.exe: FORCE
	@$(MAKE) -f Regression/WINPC//RegressionTest.exe.mk $@
clean ::
	$(RM) Regression/WINPC//RegressionTest.exe

else # Linux Build Environment

# Make rule to create Regression/WINPC//RegressionTest.exel executable
.executables,86l .executables: Regression/WINPC//RegressionTest.exel
Regression/WINPC//RegressionTest.exe: FORCE
	@$(MAKE) -f Regression/WINPC//RegressionTest.exel.mk $@
clean ::
	$(RM) Regression/WINPC//RegressionTest.exel

endif




ifeq ($(OS),Windows_NT) # Windows Build Environment

# all,86_64W rule
all,86_64W: .executables,86_64W
.executables,86_64W: .projects,86_64W
.projects,86_64W: .libraries,86_64W
.libraries,86_64W:

endif



.executables,86_64W .executables: make_dependent_86_64W

make_dependent_86_64W: 
	-@$(MAKE) -C $(VXLIB_INSTALL_DIR)/ti/vxlib all,86_64W


ifeq ($(OS),Windows_NT) # Windows Build Environment

# Make rule to create Regression/WINPC_64//RegressionTest.exe executable
.executables,86_64W .executables: Regression/WINPC_64//RegressionTest.exe
Regression/WINPC_64//RegressionTest.exe: PATH:=$(MSVC_DIR)/bin/x86_amd64;$(MSDK_DIR)/lib/win8/um/x64;$(PATH)
Regression/WINPC_64//RegressionTest.exe: LIB:=$(MSVC_DIR)/lib/amd64;$(MSDK_DIR)/lib/win8/um/x64;$(LIB)
Regression/WINPC_64//RegressionTest.exe: FORCE
	@$(MAKE) -f Regression/WINPC_64//RegressionTest.exe.mk $@
clean ::
	$(RM) Regression/WINPC_64//RegressionTest.exe

endif


