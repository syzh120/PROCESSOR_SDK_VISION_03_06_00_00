#*******************************************************************************
#* FILE PURPOSE: Top level makefile for Creating Kernel CCS Projects
#*******************************************************************************
#* FILE NAME: ccsmake.mk
#*
#* DESCRIPTION: Defines Compiler tools paths, CCS path and rule to create and build CCS projects 
#*
#*
#* This is an auto-generated file             
#*******************************************************************************
#*
# (Mandatory) Specify where various tools are installed.

# CCSCGTVER   - C6x Code Generation version to be used for building CCS project
export CCSCGTVER ?= 8.2.4

# CCS_INSTALL_DIR   - TI Code Composer Studio install directory
export CCSV5_INSTALL_DIR ?= C:/ti/ccsv5

ifneq ($(findstring $(CCSVERSION), CCSV5),)
	export CCS_INSTALL_DIR ?= $(CCSV5_INSTALL_DIR)
	export ECLIPSE_CMD ?= "$(CCS_INSTALL_DIR)/eclipse/eclipsec.exe" -noSplash
	export CDTFILE ?= .cproject
endif

# Common Macros used in make

ifndef RMDIR
export RMDIR = DEL /Q /F /S
endif

# PHONY Targets
.PHONY: all clean cleanall .projects 

# FORCE Targets
FORCE: 

# all rule
all: .executables
.executables: .projects
.projects:
.xdcenv.mak:
Package.mak:
package.bld:

#############################################################

# Rule to Build Project RegressionTest_66_LE_ELF

#############################################################

.projects: Regression/RegressionTest_66_LE_ELF

Regression/RegressionTest_66_LE_ELF: Regression/RegressionTest_66_LE_ELF/.project

Regression/RegressionTest_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/RegressionTest_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name RegressionTest_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__REGRESSIONTEST_66_LE_ELF_REGRESSION/main.c\
 -ccs.linkFile EXT_ROOT__REGRESSIONTEST_66_LE_ELF_REGRESSION/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -D__ONESHOTTEST -g  -i../../../../ -i../../" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -D__ONESHOTTEST -o3 --symdebug:none  -i../../../../ -i../../" @configurations Release -ccs.location Regression/RegressionTest_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__REGRESSIONTEST_66_LE_ELF_REGRESSION "C:/nightlybuilds/vxlib/ti/vxlib/vxlib/examples/Regression" \

	echo EXT_ROOT__REGRESSIONTEST_66_LE_ELF_REGRESSION=.././ >> Regression/RegressionTest_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/RegressionTest_66_LE_ELF"
	-@ echo Project RegressionTest_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/RegressionTest_66_LE_ELF"

clean::
	-$(RMDIR) "Regression/RegressionTest_66_LE_ELF"

