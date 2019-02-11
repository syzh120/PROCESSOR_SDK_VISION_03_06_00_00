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
export CCSCGTVER ?= 7.4.2

# CCS_INSTALL_DIR   - TI Code Composer Studio install directory
export CCSV5_INSTALL_DIR ?= C:/ti/ccsv5

ifneq ($(findstring $(CCSVERSION), CCSV5),)
	export CCS_INSTALL_DIR ?= $(CCSV5_INSTALL_DIR)
	export ECLIPSE_CMD ?= "$(CCS_INSTALL_DIR)/eclipse/eclipsec.exe" -noSplash
	export CDTFILE ?= .cproject
endif

# MATHLIB_INSTALL_DIR   - MATHLIB install directory
export MATHLIB_INSTALL_DIR ?= C:/ti/mathlib_c66x_3_1_0_0/packages

# Common Macros used in make

ifndef RMDIR
export RMDIR = DEL /Q /F /S
endif

ifneq ($(findstring $(SHELL), sh.exe),)
	quote = "
	FIXCCSPJT=
else
	quote = '
	FIXCCSPJT=${XDC_INSTALL_DIR}/xs -f ../mas/swtools/fixccspjt.js $(@D)/$(CDTFILE)
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

# Rule to Build Project acosdp_66_LE_COFF

#############################################################

.executables: src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out

.projects: src/acosdp//c66//acosdp_66_LE_COFF

src/acosdp//c66//acosdp_66_LE_COFF: src/acosdp//c66//acosdp_66_LE_COFF/.project

src/acosdp//c66//acosdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acosdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_COFF_SRCACOSDP/acosdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acosdp//c66//acosdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_COFF_SRCACOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_COFF_SRCACOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acosdp//c66//acosdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSDP_66_LE_COFF_SRCACOSDP=../../ >> src/acosdp//c66//acosdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSDP_66_LE_COFF_SRCACOSDPC66=.././ >> src/acosdp//c66//acosdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSDP_66_LE_COFF_SRCCOMMON=../../../common >> src/acosdp//c66//acosdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_LE_COFF"
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/acosdp/acosdp.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/acosdp/acosdp_d.c
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/acosdp//c66/acosdp.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/acosdp//c66/acosdp_i.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common/drvdp.c
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common/drvdp.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common/driver.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common/driver.c
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common/common.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common/tables.c
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/common//c66/common.h
src/acosdp//c66//acosdp_66_LE_COFF/Release/acosdp_66_LE_COFF.out: src/acosdp//c66//acosdp_66_LE_COFF/.project
	-@ echo Importing Project acosdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acosdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66/acosdp_66_LE_COFF"
	-@ echo Building Project acosdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acosdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project acosdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/acosdp//c66//acosdp_66_LE_COFF"


#############################################################

# Rule to Build Project acosdp_66_BE_COFF

#############################################################

.executables: src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out

.projects: src/acosdp//c66//acosdp_66_BE_COFF

src/acosdp//c66//acosdp_66_BE_COFF: src/acosdp//c66//acosdp_66_BE_COFF/.project

src/acosdp//c66//acosdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acosdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_COFF_SRCACOSDP/acosdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acosdp//c66//acosdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_COFF_SRCACOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_COFF_SRCACOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acosdp//c66//acosdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSDP_66_BE_COFF_SRCACOSDP=../../ >> src/acosdp//c66//acosdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSDP_66_BE_COFF_SRCACOSDPC66=.././ >> src/acosdp//c66//acosdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSDP_66_BE_COFF_SRCCOMMON=../../../common >> src/acosdp//c66//acosdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_BE_COFF"
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/acosdp/acosdp.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/acosdp/acosdp_d.c
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/acosdp//c66/acosdp.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/acosdp//c66/acosdp_i.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common/drvdp.c
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common/drvdp.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common/driver.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common/driver.c
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common/common.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common/tables.c
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/common//c66/common.h
src/acosdp//c66//acosdp_66_BE_COFF/Release/acosdp_66_BE_COFF.out: src/acosdp//c66//acosdp_66_BE_COFF/.project
	-@ echo Importing Project acosdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acosdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66/acosdp_66_BE_COFF"
	-@ echo Building Project acosdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acosdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project acosdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/acosdp//c66//acosdp_66_BE_COFF"


#############################################################

# Rule to Build Project acosdp_66_LE_ELF

#############################################################

.executables: src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out

.projects: src/acosdp//c66//acosdp_66_LE_ELF

src/acosdp//c66//acosdp_66_LE_ELF: src/acosdp//c66//acosdp_66_LE_ELF/.project

src/acosdp//c66//acosdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acosdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_ELF_SRCACOSDP/acosdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acosdp//c66//acosdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_ELF_SRCACOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_ELF_SRCACOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acosdp//c66//acosdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSDP_66_LE_ELF_SRCACOSDP=../../ >> src/acosdp//c66//acosdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSDP_66_LE_ELF_SRCACOSDPC66=.././ >> src/acosdp//c66//acosdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSDP_66_LE_ELF_SRCCOMMON=../../../common >> src/acosdp//c66//acosdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_LE_ELF"
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/acosdp/acosdp.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/acosdp/acosdp_d.c
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/acosdp//c66/acosdp.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/acosdp//c66/acosdp_i.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common/drvdp.c
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common/drvdp.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common/driver.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common/driver.c
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common/common.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common/tables.c
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/common//c66/common.h
src/acosdp//c66//acosdp_66_LE_ELF/Release/acosdp_66_LE_ELF.out: src/acosdp//c66//acosdp_66_LE_ELF/.project
	-@ echo Importing Project acosdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acosdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66/acosdp_66_LE_ELF"
	-@ echo Building Project acosdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acosdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project acosdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/acosdp//c66//acosdp_66_LE_ELF"


#############################################################

# Rule to Build Project acosdp_66_BE_ELF

#############################################################

.executables: src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out

.projects: src/acosdp//c66//acosdp_66_BE_ELF

src/acosdp//c66//acosdp_66_BE_ELF: src/acosdp//c66//acosdp_66_BE_ELF/.project

src/acosdp//c66//acosdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acosdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_ELF_SRCACOSDP/acosdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acosdp//c66//acosdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_ELF_SRCACOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_ELF_SRCACOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acosdp//c66//acosdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSDP_66_BE_ELF_SRCACOSDP=../../ >> src/acosdp//c66//acosdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSDP_66_BE_ELF_SRCACOSDPC66=.././ >> src/acosdp//c66//acosdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSDP_66_BE_ELF_SRCCOMMON=../../../common >> src/acosdp//c66//acosdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_BE_ELF"
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/acosdp/acosdp.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/acosdp/acosdp_d.c
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/acosdp//c66/acosdp.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/acosdp//c66/acosdp_i.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common/drvdp.c
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common/drvdp.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common/driver.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common/driver.c
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common/common.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common/tables.c
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/common//c66/common.h
src/acosdp//c66//acosdp_66_BE_ELF/Release/acosdp_66_BE_ELF.out: src/acosdp//c66//acosdp_66_BE_ELF/.project
	-@ echo Importing Project acosdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acosdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acosdp/c66/acosdp_66_BE_ELF"
	-@ echo Building Project acosdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acosdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acosdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project acosdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acosdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/acosdp//c66//acosdp_66_BE_ELF"


#############################################################

# Rule to Build Project acoshdp_66_LE_COFF

#############################################################

.executables: src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out

.projects: src/acoshdp//c66//acoshdp_66_LE_COFF

src/acoshdp//c66//acoshdp_66_LE_COFF: src/acoshdp//c66//acoshdp_66_LE_COFF/.project

src/acoshdp//c66//acoshdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_COFF_SRCACOSHDP/acoshdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshdp//c66//acoshdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_COFF_SRCACOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_COFF_SRCACOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acoshdp//c66//acoshdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_LE_COFF_SRCACOSHDP=../../ >> src/acoshdp//c66//acoshdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_LE_COFF_SRCACOSHDPC66=.././ >> src/acoshdp//c66//acoshdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_LE_COFF_SRCCOMMON=../../../common >> src/acoshdp//c66//acoshdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_LE_COFF"
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/acoshdp/acoshdp.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/acoshdp/acoshdp_d.c
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/acoshdp//c66/acoshdp.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/acoshdp//c66/acoshdp_i.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common/drvdp.c
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common/drvdp.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common/driver.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common/driver.c
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common/common.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common/tables.c
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/common//c66/common.h
src/acoshdp//c66//acoshdp_66_LE_COFF/Release/acoshdp_66_LE_COFF.out: src/acoshdp//c66//acoshdp_66_LE_COFF/.project
	-@ echo Importing Project acoshdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66/acoshdp_66_LE_COFF"
	-@ echo Building Project acoshdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project acoshdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/acoshdp//c66//acoshdp_66_LE_COFF"


#############################################################

# Rule to Build Project acoshdp_66_BE_COFF

#############################################################

.executables: src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out

.projects: src/acoshdp//c66//acoshdp_66_BE_COFF

src/acoshdp//c66//acoshdp_66_BE_COFF: src/acoshdp//c66//acoshdp_66_BE_COFF/.project

src/acoshdp//c66//acoshdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_COFF_SRCACOSHDP/acoshdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshdp//c66//acoshdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_COFF_SRCACOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_COFF_SRCACOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acoshdp//c66//acoshdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_BE_COFF_SRCACOSHDP=../../ >> src/acoshdp//c66//acoshdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_BE_COFF_SRCACOSHDPC66=.././ >> src/acoshdp//c66//acoshdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_BE_COFF_SRCCOMMON=../../../common >> src/acoshdp//c66//acoshdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_BE_COFF"
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/acoshdp/acoshdp.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/acoshdp/acoshdp_d.c
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/acoshdp//c66/acoshdp.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/acoshdp//c66/acoshdp_i.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common/drvdp.c
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common/drvdp.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common/driver.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common/driver.c
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common/common.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common/tables.c
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/common//c66/common.h
src/acoshdp//c66//acoshdp_66_BE_COFF/Release/acoshdp_66_BE_COFF.out: src/acoshdp//c66//acoshdp_66_BE_COFF/.project
	-@ echo Importing Project acoshdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66/acoshdp_66_BE_COFF"
	-@ echo Building Project acoshdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project acoshdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/acoshdp//c66//acoshdp_66_BE_COFF"


#############################################################

# Rule to Build Project acoshdp_66_LE_ELF

#############################################################

.executables: src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out

.projects: src/acoshdp//c66//acoshdp_66_LE_ELF

src/acoshdp//c66//acoshdp_66_LE_ELF: src/acoshdp//c66//acoshdp_66_LE_ELF/.project

src/acoshdp//c66//acoshdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_ELF_SRCACOSHDP/acoshdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshdp//c66//acoshdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_ELF_SRCACOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_ELF_SRCACOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acoshdp//c66//acoshdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_LE_ELF_SRCACOSHDP=../../ >> src/acoshdp//c66//acoshdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_LE_ELF_SRCACOSHDPC66=.././ >> src/acoshdp//c66//acoshdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_LE_ELF_SRCCOMMON=../../../common >> src/acoshdp//c66//acoshdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_LE_ELF"
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/acoshdp/acoshdp.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/acoshdp/acoshdp_d.c
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/acoshdp//c66/acoshdp.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/acoshdp//c66/acoshdp_i.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common/drvdp.c
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common/drvdp.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common/driver.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common/driver.c
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common/common.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common/tables.c
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/common//c66/common.h
src/acoshdp//c66//acoshdp_66_LE_ELF/Release/acoshdp_66_LE_ELF.out: src/acoshdp//c66//acoshdp_66_LE_ELF/.project
	-@ echo Importing Project acoshdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66/acoshdp_66_LE_ELF"
	-@ echo Building Project acoshdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project acoshdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/acoshdp//c66//acoshdp_66_LE_ELF"


#############################################################

# Rule to Build Project acoshdp_66_BE_ELF

#############################################################

.executables: src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out

.projects: src/acoshdp//c66//acoshdp_66_BE_ELF

src/acoshdp//c66//acoshdp_66_BE_ELF: src/acoshdp//c66//acoshdp_66_BE_ELF/.project

src/acoshdp//c66//acoshdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_ELF_SRCACOSHDP/acoshdp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshdp//c66//acoshdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_ELF_SRCACOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_ELF_SRCACOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acoshdp//c66//acoshdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_BE_ELF_SRCACOSHDP=../../ >> src/acoshdp//c66//acoshdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_BE_ELF_SRCACOSHDPC66=.././ >> src/acoshdp//c66//acoshdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSHDP_66_BE_ELF_SRCCOMMON=../../../common >> src/acoshdp//c66//acoshdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_BE_ELF"
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/acoshdp/acoshdp.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/acoshdp/acoshdp_d.c
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/acoshdp//c66/acoshdp.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/acoshdp//c66/acoshdp_i.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common/drvdp.c
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common/drvdp.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common/driver.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common/driver.c
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common/common.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common/tables.c
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/common//c66/common.h
src/acoshdp//c66//acoshdp_66_BE_ELF/Release/acoshdp_66_BE_ELF.out: src/acoshdp//c66//acoshdp_66_BE_ELF/.project
	-@ echo Importing Project acoshdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshdp/c66/acoshdp_66_BE_ELF"
	-@ echo Building Project acoshdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project acoshdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/acoshdp//c66//acoshdp_66_BE_ELF"


#############################################################

# Rule to Build Project acoshsp_66_LE_COFF

#############################################################

.executables: src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out

.projects: src/acoshsp//c66//acoshsp_66_LE_COFF

src/acoshsp//c66//acoshsp_66_LE_COFF: src/acoshsp//c66//acoshsp_66_LE_COFF/.project

src/acoshsp//c66//acoshsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_COFF_SRCACOSHSP/acoshsp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshsp//c66//acoshsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_COFF_SRCACOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_COFF_SRCACOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acoshsp//c66//acoshsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_LE_COFF_SRCACOSHSP=../../ >> src/acoshsp//c66//acoshsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_LE_COFF_SRCACOSHSPC66=.././ >> src/acoshsp//c66//acoshsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_LE_COFF_SRCCOMMON=../../../common >> src/acoshsp//c66//acoshsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_LE_COFF"
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/acoshsp/acoshsp.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/acoshsp/acoshsp_d.c
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/acoshsp//c66/acoshsp.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/acoshsp//c66/acoshsp_i.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common/drvsp.c
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common/drvsp.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common/driver.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common/driver.c
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common/common.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common/tables.c
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/common//c66/common.h
src/acoshsp//c66//acoshsp_66_LE_COFF/Release/acoshsp_66_LE_COFF.out: src/acoshsp//c66//acoshsp_66_LE_COFF/.project
	-@ echo Importing Project acoshsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66/acoshsp_66_LE_COFF"
	-@ echo Building Project acoshsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project acoshsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/acoshsp//c66//acoshsp_66_LE_COFF"


#############################################################

# Rule to Build Project acoshsp_66_BE_COFF

#############################################################

.executables: src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out

.projects: src/acoshsp//c66//acoshsp_66_BE_COFF

src/acoshsp//c66//acoshsp_66_BE_COFF: src/acoshsp//c66//acoshsp_66_BE_COFF/.project

src/acoshsp//c66//acoshsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_COFF_SRCACOSHSP/acoshsp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshsp//c66//acoshsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_COFF_SRCACOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_COFF_SRCACOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acoshsp//c66//acoshsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_BE_COFF_SRCACOSHSP=../../ >> src/acoshsp//c66//acoshsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_BE_COFF_SRCACOSHSPC66=.././ >> src/acoshsp//c66//acoshsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_BE_COFF_SRCCOMMON=../../../common >> src/acoshsp//c66//acoshsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_BE_COFF"
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/acoshsp/acoshsp.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/acoshsp/acoshsp_d.c
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/acoshsp//c66/acoshsp.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/acoshsp//c66/acoshsp_i.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common/drvsp.c
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common/drvsp.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common/driver.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common/driver.c
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common/common.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common/tables.c
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/common//c66/common.h
src/acoshsp//c66//acoshsp_66_BE_COFF/Release/acoshsp_66_BE_COFF.out: src/acoshsp//c66//acoshsp_66_BE_COFF/.project
	-@ echo Importing Project acoshsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66/acoshsp_66_BE_COFF"
	-@ echo Building Project acoshsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project acoshsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/acoshsp//c66//acoshsp_66_BE_COFF"


#############################################################

# Rule to Build Project acoshsp_66_LE_ELF

#############################################################

.executables: src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out

.projects: src/acoshsp//c66//acoshsp_66_LE_ELF

src/acoshsp//c66//acoshsp_66_LE_ELF: src/acoshsp//c66//acoshsp_66_LE_ELF/.project

src/acoshsp//c66//acoshsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_ELF_SRCACOSHSP/acoshsp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshsp//c66//acoshsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_ELF_SRCACOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_ELF_SRCACOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acoshsp//c66//acoshsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_LE_ELF_SRCACOSHSP=../../ >> src/acoshsp//c66//acoshsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_LE_ELF_SRCACOSHSPC66=.././ >> src/acoshsp//c66//acoshsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_LE_ELF_SRCCOMMON=../../../common >> src/acoshsp//c66//acoshsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_LE_ELF"
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/acoshsp/acoshsp.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/acoshsp/acoshsp_d.c
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/acoshsp//c66/acoshsp.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/acoshsp//c66/acoshsp_i.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common/drvsp.c
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common/drvsp.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common/driver.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common/driver.c
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common/common.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common/tables.c
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/common//c66/common.h
src/acoshsp//c66//acoshsp_66_LE_ELF/Release/acoshsp_66_LE_ELF.out: src/acoshsp//c66//acoshsp_66_LE_ELF/.project
	-@ echo Importing Project acoshsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66/acoshsp_66_LE_ELF"
	-@ echo Building Project acoshsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project acoshsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/acoshsp//c66//acoshsp_66_LE_ELF"


#############################################################

# Rule to Build Project acoshsp_66_BE_ELF

#############################################################

.executables: src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out

.projects: src/acoshsp//c66//acoshsp_66_BE_ELF

src/acoshsp//c66//acoshsp_66_BE_ELF: src/acoshsp//c66//acoshsp_66_BE_ELF/.project

src/acoshsp//c66//acoshsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acoshsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_ELF_SRCACOSHSP/acoshsp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acoshsp//c66//acoshsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_ELF_SRCACOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_ELF_SRCACOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acoshsp//c66//acoshsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_BE_ELF_SRCACOSHSP=../../ >> src/acoshsp//c66//acoshsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_BE_ELF_SRCACOSHSPC66=.././ >> src/acoshsp//c66//acoshsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSHSP_66_BE_ELF_SRCCOMMON=../../../common >> src/acoshsp//c66//acoshsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_BE_ELF"
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/acoshsp/acoshsp.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/acoshsp/acoshsp_d.c
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/acoshsp//c66/acoshsp.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/acoshsp//c66/acoshsp_i.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common/drvsp.c
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common/drvsp.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common/driver.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common/driver.c
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common/common.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common/tables.c
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/common//c66/common.h
src/acoshsp//c66//acoshsp_66_BE_ELF/Release/acoshsp_66_BE_ELF.out: src/acoshsp//c66//acoshsp_66_BE_ELF/.project
	-@ echo Importing Project acoshsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acoshsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acoshsp/c66/acoshsp_66_BE_ELF"
	-@ echo Building Project acoshsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acoshsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acoshsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project acoshsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acoshsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/acoshsp//c66//acoshsp_66_BE_ELF"


#############################################################

# Rule to Build Project acossp_66_LE_COFF

#############################################################

.executables: src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out

.projects: src/acossp//c66//acossp_66_LE_COFF

src/acossp//c66//acossp_66_LE_COFF: src/acossp//c66//acossp_66_LE_COFF/.project

src/acossp//c66//acossp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acossp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_COFF_SRCACOSSP/acossp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acossp//c66//acossp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_COFF_SRCACOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_COFF_SRCACOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acossp//c66//acossp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSSP_66_LE_COFF_SRCACOSSP=../../ >> src/acossp//c66//acossp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSSP_66_LE_COFF_SRCACOSSPC66=.././ >> src/acossp//c66//acossp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ACOSSP_66_LE_COFF_SRCCOMMON=../../../common >> src/acossp//c66//acossp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acossp_66_LE_COFF"
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/acossp/acossp.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/acossp/acossp_d.c
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/acossp//c66/acossp.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/acossp//c66/acossp_i.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common/drvsp.c
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common/drvsp.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common/driver.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common/driver.c
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common/common.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common/tables.c
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/common//c66/common.h
src/acossp//c66//acossp_66_LE_COFF/Release/acossp_66_LE_COFF.out: src/acossp//c66//acossp_66_LE_COFF/.project
	-@ echo Importing Project acossp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acossp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66/acossp_66_LE_COFF"
	-@ echo Building Project acossp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acossp_66_LE_COFF -ccs.configuration Release
	-@ echo Project acossp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acossp_66_LE_COFF"

clean::
	-$(RMDIR) "src/acossp//c66//acossp_66_LE_COFF"


#############################################################

# Rule to Build Project acossp_66_BE_COFF

#############################################################

.executables: src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out

.projects: src/acossp//c66//acossp_66_BE_COFF

src/acossp//c66//acossp_66_BE_COFF: src/acossp//c66//acossp_66_BE_COFF/.project

src/acossp//c66//acossp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acossp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_COFF_SRCACOSSP/acossp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acossp//c66//acossp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_COFF_SRCACOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_COFF_SRCACOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/acossp//c66//acossp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSSP_66_BE_COFF_SRCACOSSP=../../ >> src/acossp//c66//acossp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSSP_66_BE_COFF_SRCACOSSPC66=.././ >> src/acossp//c66//acossp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ACOSSP_66_BE_COFF_SRCCOMMON=../../../common >> src/acossp//c66//acossp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acossp_66_BE_COFF"
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/acossp/acossp.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/acossp/acossp_d.c
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/acossp//c66/acossp.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/acossp//c66/acossp_i.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common/drvsp.c
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common/drvsp.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common/driver.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common/driver.c
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common/common.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common/tables.c
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/common//c66/common.h
src/acossp//c66//acossp_66_BE_COFF/Release/acossp_66_BE_COFF.out: src/acossp//c66//acossp_66_BE_COFF/.project
	-@ echo Importing Project acossp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acossp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66/acossp_66_BE_COFF"
	-@ echo Building Project acossp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acossp_66_BE_COFF -ccs.configuration Release
	-@ echo Project acossp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acossp_66_BE_COFF"

clean::
	-$(RMDIR) "src/acossp//c66//acossp_66_BE_COFF"


#############################################################

# Rule to Build Project acossp_66_LE_ELF

#############################################################

.executables: src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out

.projects: src/acossp//c66//acossp_66_LE_ELF

src/acossp//c66//acossp_66_LE_ELF: src/acossp//c66//acossp_66_LE_ELF/.project

src/acossp//c66//acossp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acossp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_ELF_SRCACOSSP/acossp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acossp//c66//acossp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_ELF_SRCACOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_ELF_SRCACOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acossp//c66//acossp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSSP_66_LE_ELF_SRCACOSSP=../../ >> src/acossp//c66//acossp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSSP_66_LE_ELF_SRCACOSSPC66=.././ >> src/acossp//c66//acossp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ACOSSP_66_LE_ELF_SRCCOMMON=../../../common >> src/acossp//c66//acossp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acossp_66_LE_ELF"
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/acossp/acossp.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/acossp/acossp_d.c
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/acossp//c66/acossp.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/acossp//c66/acossp_i.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common/drvsp.c
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common/drvsp.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common/driver.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common/driver.c
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common/common.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common/tables.c
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/common//c66/common.h
src/acossp//c66//acossp_66_LE_ELF/Release/acossp_66_LE_ELF.out: src/acossp//c66//acossp_66_LE_ELF/.project
	-@ echo Importing Project acossp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acossp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66/acossp_66_LE_ELF"
	-@ echo Building Project acossp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acossp_66_LE_ELF -ccs.configuration Release
	-@ echo Project acossp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acossp_66_LE_ELF"

clean::
	-$(RMDIR) "src/acossp//c66//acossp_66_LE_ELF"


#############################################################

# Rule to Build Project acossp_66_BE_ELF

#############################################################

.executables: src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out

.projects: src/acossp//c66//acossp_66_BE_ELF

src/acossp//c66//acossp_66_BE_ELF: src/acossp//c66//acossp_66_BE_ELF/.project

src/acossp//c66//acossp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name acossp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_ELF_SRCACOSSP/acossp_d.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/acossp//c66//acossp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_ELF_SRCACOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_ELF_SRCACOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66" \
 -ccs.definePathVariable EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/acossp//c66//acossp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSSP_66_BE_ELF_SRCACOSSP=../../ >> src/acossp//c66//acossp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSSP_66_BE_ELF_SRCACOSSPC66=.././ >> src/acossp//c66//acossp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ACOSSP_66_BE_ELF_SRCCOMMON=../../../common >> src/acossp//c66//acossp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/acossp_66_BE_ELF"
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/acossp/acossp.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/acossp/acossp_d.c
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/acossp//c66/acossp.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/acossp//c66/acossp_i.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common/drvsp.c
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common/drvsp.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common/driver.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common/driver.c
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common/common.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common/tables.c
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/common//c66/common.h
src/acossp//c66//acossp_66_BE_ELF/Release/acossp_66_BE_ELF.out: src/acossp//c66//acossp_66_BE_ELF/.project
	-@ echo Importing Project acossp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects acossp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/acossp/c66/acossp_66_BE_ELF"
	-@ echo Building Project acossp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/acossp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects acossp_66_BE_ELF -ccs.configuration Release
	-@ echo Project acossp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/acossp_66_BE_ELF"

clean::
	-$(RMDIR) "src/acossp//c66//acossp_66_BE_ELF"


#############################################################

# Rule to Build Project asindp_66_LE_COFF

#############################################################

.executables: src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out

.projects: src/asindp//c66//asindp_66_LE_COFF

src/asindp//c66//asindp_66_LE_COFF: src/asindp//c66//asindp_66_LE_COFF/.project

src/asindp//c66//asindp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asindp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_COFF_SRCASINDP/asindp_d.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asindp//c66//asindp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_COFF_SRCASINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_COFF_SRCASINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asindp//c66//asindp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINDP_66_LE_COFF_SRCASINDP=../../ >> src/asindp//c66//asindp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINDP_66_LE_COFF_SRCASINDPC66=.././ >> src/asindp//c66//asindp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINDP_66_LE_COFF_SRCCOMMON=../../../common >> src/asindp//c66//asindp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asindp_66_LE_COFF"
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/asindp/asindp.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/asindp/asindp_d.c
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/asindp//c66/asindp.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/asindp//c66/asindp_i.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common/drvdp.c
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common/drvdp.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common/driver.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common/driver.c
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common/common.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common/tables.c
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/common//c66/common.h
src/asindp//c66//asindp_66_LE_COFF/Release/asindp_66_LE_COFF.out: src/asindp//c66//asindp_66_LE_COFF/.project
	-@ echo Importing Project asindp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asindp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66/asindp_66_LE_COFF"
	-@ echo Building Project asindp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asindp_66_LE_COFF -ccs.configuration Release
	-@ echo Project asindp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asindp_66_LE_COFF"

clean::
	-$(RMDIR) "src/asindp//c66//asindp_66_LE_COFF"


#############################################################

# Rule to Build Project asindp_66_BE_COFF

#############################################################

.executables: src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out

.projects: src/asindp//c66//asindp_66_BE_COFF

src/asindp//c66//asindp_66_BE_COFF: src/asindp//c66//asindp_66_BE_COFF/.project

src/asindp//c66//asindp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asindp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_COFF_SRCASINDP/asindp_d.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asindp//c66//asindp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_COFF_SRCASINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_COFF_SRCASINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asindp//c66//asindp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINDP_66_BE_COFF_SRCASINDP=../../ >> src/asindp//c66//asindp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINDP_66_BE_COFF_SRCASINDPC66=.././ >> src/asindp//c66//asindp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINDP_66_BE_COFF_SRCCOMMON=../../../common >> src/asindp//c66//asindp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asindp_66_BE_COFF"
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/asindp/asindp.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/asindp/asindp_d.c
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/asindp//c66/asindp.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/asindp//c66/asindp_i.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common/drvdp.c
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common/drvdp.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common/driver.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common/driver.c
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common/common.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common/tables.c
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/common//c66/common.h
src/asindp//c66//asindp_66_BE_COFF/Release/asindp_66_BE_COFF.out: src/asindp//c66//asindp_66_BE_COFF/.project
	-@ echo Importing Project asindp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asindp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66/asindp_66_BE_COFF"
	-@ echo Building Project asindp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asindp_66_BE_COFF -ccs.configuration Release
	-@ echo Project asindp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asindp_66_BE_COFF"

clean::
	-$(RMDIR) "src/asindp//c66//asindp_66_BE_COFF"


#############################################################

# Rule to Build Project asindp_66_LE_ELF

#############################################################

.executables: src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out

.projects: src/asindp//c66//asindp_66_LE_ELF

src/asindp//c66//asindp_66_LE_ELF: src/asindp//c66//asindp_66_LE_ELF/.project

src/asindp//c66//asindp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asindp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_ELF_SRCASINDP/asindp_d.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asindp//c66//asindp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_ELF_SRCASINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_ELF_SRCASINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asindp//c66//asindp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINDP_66_LE_ELF_SRCASINDP=../../ >> src/asindp//c66//asindp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINDP_66_LE_ELF_SRCASINDPC66=.././ >> src/asindp//c66//asindp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINDP_66_LE_ELF_SRCCOMMON=../../../common >> src/asindp//c66//asindp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asindp_66_LE_ELF"
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/asindp/asindp.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/asindp/asindp_d.c
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/asindp//c66/asindp.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/asindp//c66/asindp_i.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common/drvdp.c
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common/drvdp.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common/driver.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common/driver.c
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common/common.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common/tables.c
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/common//c66/common.h
src/asindp//c66//asindp_66_LE_ELF/Release/asindp_66_LE_ELF.out: src/asindp//c66//asindp_66_LE_ELF/.project
	-@ echo Importing Project asindp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asindp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66/asindp_66_LE_ELF"
	-@ echo Building Project asindp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asindp_66_LE_ELF -ccs.configuration Release
	-@ echo Project asindp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asindp_66_LE_ELF"

clean::
	-$(RMDIR) "src/asindp//c66//asindp_66_LE_ELF"


#############################################################

# Rule to Build Project asindp_66_BE_ELF

#############################################################

.executables: src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out

.projects: src/asindp//c66//asindp_66_BE_ELF

src/asindp//c66//asindp_66_BE_ELF: src/asindp//c66//asindp_66_BE_ELF/.project

src/asindp//c66//asindp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asindp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_ELF_SRCASINDP/asindp_d.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asindp//c66//asindp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_ELF_SRCASINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_ELF_SRCASINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asindp//c66//asindp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINDP_66_BE_ELF_SRCASINDP=../../ >> src/asindp//c66//asindp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINDP_66_BE_ELF_SRCASINDPC66=.././ >> src/asindp//c66//asindp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINDP_66_BE_ELF_SRCCOMMON=../../../common >> src/asindp//c66//asindp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asindp_66_BE_ELF"
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/asindp/asindp.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/asindp/asindp_d.c
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/asindp//c66/asindp.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/asindp//c66/asindp_i.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common/drvdp.c
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common/drvdp.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common/driver.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common/driver.c
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common/common.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common/tables.c
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/common//c66/common.h
src/asindp//c66//asindp_66_BE_ELF/Release/asindp_66_BE_ELF.out: src/asindp//c66//asindp_66_BE_ELF/.project
	-@ echo Importing Project asindp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asindp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asindp/c66/asindp_66_BE_ELF"
	-@ echo Building Project asindp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asindp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asindp_66_BE_ELF -ccs.configuration Release
	-@ echo Project asindp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asindp_66_BE_ELF"

clean::
	-$(RMDIR) "src/asindp//c66//asindp_66_BE_ELF"


#############################################################

# Rule to Build Project asinhdp_66_LE_COFF

#############################################################

.executables: src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out

.projects: src/asinhdp//c66//asinhdp_66_LE_COFF

src/asinhdp//c66//asinhdp_66_LE_COFF: src/asinhdp//c66//asinhdp_66_LE_COFF/.project

src/asinhdp//c66//asinhdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_COFF_SRCASINHDP/asinhdp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhdp//c66//asinhdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_COFF_SRCASINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_COFF_SRCASINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asinhdp//c66//asinhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINHDP_66_LE_COFF_SRCASINHDP=../../ >> src/asinhdp//c66//asinhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINHDP_66_LE_COFF_SRCASINHDPC66=.././ >> src/asinhdp//c66//asinhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINHDP_66_LE_COFF_SRCCOMMON=../../../common >> src/asinhdp//c66//asinhdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_LE_COFF"
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/asinhdp/asinhdp.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/asinhdp/asinhdp_d.c
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/asinhdp//c66/asinhdp.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/asinhdp//c66/asinhdp_i.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common/drvdp.c
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common/drvdp.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common/driver.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common/driver.c
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common/common.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common/tables.c
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/common//c66/common.h
src/asinhdp//c66//asinhdp_66_LE_COFF/Release/asinhdp_66_LE_COFF.out: src/asinhdp//c66//asinhdp_66_LE_COFF/.project
	-@ echo Importing Project asinhdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66/asinhdp_66_LE_COFF"
	-@ echo Building Project asinhdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project asinhdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/asinhdp//c66//asinhdp_66_LE_COFF"


#############################################################

# Rule to Build Project asinhdp_66_BE_COFF

#############################################################

.executables: src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out

.projects: src/asinhdp//c66//asinhdp_66_BE_COFF

src/asinhdp//c66//asinhdp_66_BE_COFF: src/asinhdp//c66//asinhdp_66_BE_COFF/.project

src/asinhdp//c66//asinhdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_COFF_SRCASINHDP/asinhdp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhdp//c66//asinhdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_COFF_SRCASINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_COFF_SRCASINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asinhdp//c66//asinhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINHDP_66_BE_COFF_SRCASINHDP=../../ >> src/asinhdp//c66//asinhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINHDP_66_BE_COFF_SRCASINHDPC66=.././ >> src/asinhdp//c66//asinhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINHDP_66_BE_COFF_SRCCOMMON=../../../common >> src/asinhdp//c66//asinhdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_BE_COFF"
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/asinhdp/asinhdp.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/asinhdp/asinhdp_d.c
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/asinhdp//c66/asinhdp.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/asinhdp//c66/asinhdp_i.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common/drvdp.c
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common/drvdp.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common/driver.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common/driver.c
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common/common.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common/tables.c
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/common//c66/common.h
src/asinhdp//c66//asinhdp_66_BE_COFF/Release/asinhdp_66_BE_COFF.out: src/asinhdp//c66//asinhdp_66_BE_COFF/.project
	-@ echo Importing Project asinhdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66/asinhdp_66_BE_COFF"
	-@ echo Building Project asinhdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project asinhdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/asinhdp//c66//asinhdp_66_BE_COFF"


#############################################################

# Rule to Build Project asinhdp_66_LE_ELF

#############################################################

.executables: src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out

.projects: src/asinhdp//c66//asinhdp_66_LE_ELF

src/asinhdp//c66//asinhdp_66_LE_ELF: src/asinhdp//c66//asinhdp_66_LE_ELF/.project

src/asinhdp//c66//asinhdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_ELF_SRCASINHDP/asinhdp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhdp//c66//asinhdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_ELF_SRCASINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_ELF_SRCASINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asinhdp//c66//asinhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINHDP_66_LE_ELF_SRCASINHDP=../../ >> src/asinhdp//c66//asinhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINHDP_66_LE_ELF_SRCASINHDPC66=.././ >> src/asinhdp//c66//asinhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINHDP_66_LE_ELF_SRCCOMMON=../../../common >> src/asinhdp//c66//asinhdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_LE_ELF"
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/asinhdp/asinhdp.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/asinhdp/asinhdp_d.c
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/asinhdp//c66/asinhdp.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/asinhdp//c66/asinhdp_i.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common/drvdp.c
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common/drvdp.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common/driver.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common/driver.c
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common/common.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common/tables.c
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/common//c66/common.h
src/asinhdp//c66//asinhdp_66_LE_ELF/Release/asinhdp_66_LE_ELF.out: src/asinhdp//c66//asinhdp_66_LE_ELF/.project
	-@ echo Importing Project asinhdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66/asinhdp_66_LE_ELF"
	-@ echo Building Project asinhdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project asinhdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/asinhdp//c66//asinhdp_66_LE_ELF"


#############################################################

# Rule to Build Project asinhdp_66_BE_ELF

#############################################################

.executables: src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out

.projects: src/asinhdp//c66//asinhdp_66_BE_ELF

src/asinhdp//c66//asinhdp_66_BE_ELF: src/asinhdp//c66//asinhdp_66_BE_ELF/.project

src/asinhdp//c66//asinhdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_ELF_SRCASINHDP/asinhdp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhdp//c66//asinhdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_ELF_SRCASINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_ELF_SRCASINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asinhdp//c66//asinhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINHDP_66_BE_ELF_SRCASINHDP=../../ >> src/asinhdp//c66//asinhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINHDP_66_BE_ELF_SRCASINHDPC66=.././ >> src/asinhdp//c66//asinhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINHDP_66_BE_ELF_SRCCOMMON=../../../common >> src/asinhdp//c66//asinhdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_BE_ELF"
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/asinhdp/asinhdp.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/asinhdp/asinhdp_d.c
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/asinhdp//c66/asinhdp.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/asinhdp//c66/asinhdp_i.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common/drvdp.c
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common/drvdp.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common/driver.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common/driver.c
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common/common.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common/tables.c
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/common//c66/common.h
src/asinhdp//c66//asinhdp_66_BE_ELF/Release/asinhdp_66_BE_ELF.out: src/asinhdp//c66//asinhdp_66_BE_ELF/.project
	-@ echo Importing Project asinhdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhdp/c66/asinhdp_66_BE_ELF"
	-@ echo Building Project asinhdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project asinhdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/asinhdp//c66//asinhdp_66_BE_ELF"


#############################################################

# Rule to Build Project asinhsp_66_LE_COFF

#############################################################

.executables: src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out

.projects: src/asinhsp//c66//asinhsp_66_LE_COFF

src/asinhsp//c66//asinhsp_66_LE_COFF: src/asinhsp//c66//asinhsp_66_LE_COFF/.project

src/asinhsp//c66//asinhsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_COFF_SRCASINHSP/asinhsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhsp//c66//asinhsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_COFF_SRCASINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_COFF_SRCASINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asinhsp//c66//asinhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINHSP_66_LE_COFF_SRCASINHSP=../../ >> src/asinhsp//c66//asinhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINHSP_66_LE_COFF_SRCASINHSPC66=.././ >> src/asinhsp//c66//asinhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINHSP_66_LE_COFF_SRCCOMMON=../../../common >> src/asinhsp//c66//asinhsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_LE_COFF"
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/asinhsp/asinhsp.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/asinhsp/asinhsp_d.c
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/asinhsp//c66/asinhsp.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/asinhsp//c66/asinhsp_i.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common/drvsp.c
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common/drvsp.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common/driver.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common/driver.c
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common/common.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common/tables.c
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/common//c66/common.h
src/asinhsp//c66//asinhsp_66_LE_COFF/Release/asinhsp_66_LE_COFF.out: src/asinhsp//c66//asinhsp_66_LE_COFF/.project
	-@ echo Importing Project asinhsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66/asinhsp_66_LE_COFF"
	-@ echo Building Project asinhsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project asinhsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/asinhsp//c66//asinhsp_66_LE_COFF"


#############################################################

# Rule to Build Project asinhsp_66_BE_COFF

#############################################################

.executables: src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out

.projects: src/asinhsp//c66//asinhsp_66_BE_COFF

src/asinhsp//c66//asinhsp_66_BE_COFF: src/asinhsp//c66//asinhsp_66_BE_COFF/.project

src/asinhsp//c66//asinhsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_COFF_SRCASINHSP/asinhsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhsp//c66//asinhsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_COFF_SRCASINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_COFF_SRCASINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asinhsp//c66//asinhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINHSP_66_BE_COFF_SRCASINHSP=../../ >> src/asinhsp//c66//asinhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINHSP_66_BE_COFF_SRCASINHSPC66=.././ >> src/asinhsp//c66//asinhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINHSP_66_BE_COFF_SRCCOMMON=../../../common >> src/asinhsp//c66//asinhsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_BE_COFF"
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/asinhsp/asinhsp.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/asinhsp/asinhsp_d.c
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/asinhsp//c66/asinhsp.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/asinhsp//c66/asinhsp_i.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common/drvsp.c
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common/drvsp.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common/driver.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common/driver.c
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common/common.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common/tables.c
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/common//c66/common.h
src/asinhsp//c66//asinhsp_66_BE_COFF/Release/asinhsp_66_BE_COFF.out: src/asinhsp//c66//asinhsp_66_BE_COFF/.project
	-@ echo Importing Project asinhsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66/asinhsp_66_BE_COFF"
	-@ echo Building Project asinhsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project asinhsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/asinhsp//c66//asinhsp_66_BE_COFF"


#############################################################

# Rule to Build Project asinhsp_66_LE_ELF

#############################################################

.executables: src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out

.projects: src/asinhsp//c66//asinhsp_66_LE_ELF

src/asinhsp//c66//asinhsp_66_LE_ELF: src/asinhsp//c66//asinhsp_66_LE_ELF/.project

src/asinhsp//c66//asinhsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_ELF_SRCASINHSP/asinhsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhsp//c66//asinhsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_ELF_SRCASINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_ELF_SRCASINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asinhsp//c66//asinhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINHSP_66_LE_ELF_SRCASINHSP=../../ >> src/asinhsp//c66//asinhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINHSP_66_LE_ELF_SRCASINHSPC66=.././ >> src/asinhsp//c66//asinhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINHSP_66_LE_ELF_SRCCOMMON=../../../common >> src/asinhsp//c66//asinhsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_LE_ELF"
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/asinhsp/asinhsp.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/asinhsp/asinhsp_d.c
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/asinhsp//c66/asinhsp.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/asinhsp//c66/asinhsp_i.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common/drvsp.c
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common/drvsp.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common/driver.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common/driver.c
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common/common.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common/tables.c
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/common//c66/common.h
src/asinhsp//c66//asinhsp_66_LE_ELF/Release/asinhsp_66_LE_ELF.out: src/asinhsp//c66//asinhsp_66_LE_ELF/.project
	-@ echo Importing Project asinhsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66/asinhsp_66_LE_ELF"
	-@ echo Building Project asinhsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project asinhsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/asinhsp//c66//asinhsp_66_LE_ELF"


#############################################################

# Rule to Build Project asinhsp_66_BE_ELF

#############################################################

.executables: src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out

.projects: src/asinhsp//c66//asinhsp_66_BE_ELF

src/asinhsp//c66//asinhsp_66_BE_ELF: src/asinhsp//c66//asinhsp_66_BE_ELF/.project

src/asinhsp//c66//asinhsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinhsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_ELF_SRCASINHSP/asinhsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinhsp//c66//asinhsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_ELF_SRCASINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_ELF_SRCASINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asinhsp//c66//asinhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINHSP_66_BE_ELF_SRCASINHSP=../../ >> src/asinhsp//c66//asinhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINHSP_66_BE_ELF_SRCASINHSPC66=.././ >> src/asinhsp//c66//asinhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINHSP_66_BE_ELF_SRCCOMMON=../../../common >> src/asinhsp//c66//asinhsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_BE_ELF"
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/asinhsp/asinhsp.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/asinhsp/asinhsp_d.c
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/asinhsp//c66/asinhsp.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/asinhsp//c66/asinhsp_i.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common/drvsp.c
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common/drvsp.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common/driver.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common/driver.c
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common/common.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common/tables.c
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/common//c66/common.h
src/asinhsp//c66//asinhsp_66_BE_ELF/Release/asinhsp_66_BE_ELF.out: src/asinhsp//c66//asinhsp_66_BE_ELF/.project
	-@ echo Importing Project asinhsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinhsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinhsp/c66/asinhsp_66_BE_ELF"
	-@ echo Building Project asinhsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinhsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project asinhsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinhsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/asinhsp//c66//asinhsp_66_BE_ELF"


#############################################################

# Rule to Build Project asinsp_66_LE_COFF

#############################################################

.executables: src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out

.projects: src/asinsp//c66//asinsp_66_LE_COFF

src/asinsp//c66//asinsp_66_LE_COFF: src/asinsp//c66//asinsp_66_LE_COFF/.project

src/asinsp//c66//asinsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_COFF_SRCASINSP/asinsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinsp//c66//asinsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_COFF_SRCASINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_COFF_SRCASINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asinsp//c66//asinsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINSP_66_LE_COFF_SRCASINSP=../../ >> src/asinsp//c66//asinsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINSP_66_LE_COFF_SRCASINSPC66=.././ >> src/asinsp//c66//asinsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ASINSP_66_LE_COFF_SRCCOMMON=../../../common >> src/asinsp//c66//asinsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_LE_COFF"
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/asinsp/asinsp.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/asinsp/asinsp_d.c
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/asinsp//c66/asinsp.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/asinsp//c66/asinsp_i.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common/drvsp.c
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common/drvsp.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common/driver.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common/driver.c
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common/common.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common/tables.c
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/common//c66/common.h
src/asinsp//c66//asinsp_66_LE_COFF/Release/asinsp_66_LE_COFF.out: src/asinsp//c66//asinsp_66_LE_COFF/.project
	-@ echo Importing Project asinsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66/asinsp_66_LE_COFF"
	-@ echo Building Project asinsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project asinsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/asinsp//c66//asinsp_66_LE_COFF"


#############################################################

# Rule to Build Project asinsp_66_BE_COFF

#############################################################

.executables: src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out

.projects: src/asinsp//c66//asinsp_66_BE_COFF

src/asinsp//c66//asinsp_66_BE_COFF: src/asinsp//c66//asinsp_66_BE_COFF/.project

src/asinsp//c66//asinsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_COFF_SRCASINSP/asinsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinsp//c66//asinsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_COFF_SRCASINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_COFF_SRCASINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/asinsp//c66//asinsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINSP_66_BE_COFF_SRCASINSP=../../ >> src/asinsp//c66//asinsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINSP_66_BE_COFF_SRCASINSPC66=.././ >> src/asinsp//c66//asinsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ASINSP_66_BE_COFF_SRCCOMMON=../../../common >> src/asinsp//c66//asinsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_BE_COFF"
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/asinsp/asinsp.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/asinsp/asinsp_d.c
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/asinsp//c66/asinsp.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/asinsp//c66/asinsp_i.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common/drvsp.c
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common/drvsp.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common/driver.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common/driver.c
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common/common.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common/tables.c
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/common//c66/common.h
src/asinsp//c66//asinsp_66_BE_COFF/Release/asinsp_66_BE_COFF.out: src/asinsp//c66//asinsp_66_BE_COFF/.project
	-@ echo Importing Project asinsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66/asinsp_66_BE_COFF"
	-@ echo Building Project asinsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project asinsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/asinsp//c66//asinsp_66_BE_COFF"


#############################################################

# Rule to Build Project asinsp_66_LE_ELF

#############################################################

.executables: src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out

.projects: src/asinsp//c66//asinsp_66_LE_ELF

src/asinsp//c66//asinsp_66_LE_ELF: src/asinsp//c66//asinsp_66_LE_ELF/.project

src/asinsp//c66//asinsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_ELF_SRCASINSP/asinsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinsp//c66//asinsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_ELF_SRCASINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_ELF_SRCASINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asinsp//c66//asinsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINSP_66_LE_ELF_SRCASINSP=../../ >> src/asinsp//c66//asinsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINSP_66_LE_ELF_SRCASINSPC66=.././ >> src/asinsp//c66//asinsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ASINSP_66_LE_ELF_SRCCOMMON=../../../common >> src/asinsp//c66//asinsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_LE_ELF"
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/asinsp/asinsp.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/asinsp/asinsp_d.c
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/asinsp//c66/asinsp.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/asinsp//c66/asinsp_i.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common/drvsp.c
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common/drvsp.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common/driver.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common/driver.c
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common/common.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common/tables.c
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/common//c66/common.h
src/asinsp//c66//asinsp_66_LE_ELF/Release/asinsp_66_LE_ELF.out: src/asinsp//c66//asinsp_66_LE_ELF/.project
	-@ echo Importing Project asinsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66/asinsp_66_LE_ELF"
	-@ echo Building Project asinsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project asinsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/asinsp//c66//asinsp_66_LE_ELF"


#############################################################

# Rule to Build Project asinsp_66_BE_ELF

#############################################################

.executables: src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out

.projects: src/asinsp//c66//asinsp_66_BE_ELF

src/asinsp//c66//asinsp_66_BE_ELF: src/asinsp//c66//asinsp_66_BE_ELF/.project

src/asinsp//c66//asinsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name asinsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_ELF_SRCASINSP/asinsp_d.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/asinsp//c66//asinsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_ELF_SRCASINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_ELF_SRCASINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/asinsp//c66//asinsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINSP_66_BE_ELF_SRCASINSP=../../ >> src/asinsp//c66//asinsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINSP_66_BE_ELF_SRCASINSPC66=.././ >> src/asinsp//c66//asinsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ASINSP_66_BE_ELF_SRCCOMMON=../../../common >> src/asinsp//c66//asinsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_BE_ELF"
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/asinsp/asinsp.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/asinsp/asinsp_d.c
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/asinsp//c66/asinsp.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/asinsp//c66/asinsp_i.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common/drvsp.c
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common/drvsp.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common/driver.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common/driver.c
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common/common.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common/tables.c
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/common//c66/common.h
src/asinsp//c66//asinsp_66_BE_ELF/Release/asinsp_66_BE_ELF.out: src/asinsp//c66//asinsp_66_BE_ELF/.project
	-@ echo Importing Project asinsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects asinsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/asinsp/c66/asinsp_66_BE_ELF"
	-@ echo Building Project asinsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/asinsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects asinsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project asinsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/asinsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/asinsp//c66//asinsp_66_BE_ELF"


#############################################################

# Rule to Build Project atan2dp_66_LE_COFF

#############################################################

.executables: src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out

.projects: src/atan2dp//c66//atan2dp_66_LE_COFF

src/atan2dp//c66//atan2dp_66_LE_COFF: src/atan2dp//c66//atan2dp_66_LE_COFF/.project

src/atan2dp//c66//atan2dp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2dp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_COFF_SRCATAN2DP/atan2dp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2dp//c66//atan2dp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_COFF_SRCATAN2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_COFF_SRCATAN2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atan2dp//c66//atan2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_LE_COFF_SRCATAN2DP=../../ >> src/atan2dp//c66//atan2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_LE_COFF_SRCATAN2DPC66=.././ >> src/atan2dp//c66//atan2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_LE_COFF_SRCCOMMON=../../../common >> src/atan2dp//c66//atan2dp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_LE_COFF"
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/atan2dp/atan2dp.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/atan2dp/atan2dp_d.c
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/atan2dp//c66/atan2dp.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/atan2dp//c66/atan2dp_i.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common/drvdp.c
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common/drvdp.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common/driver.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common/driver.c
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common/common.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common/tables.c
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/common//c66/common.h
src/atan2dp//c66//atan2dp_66_LE_COFF/Release/atan2dp_66_LE_COFF.out: src/atan2dp//c66//atan2dp_66_LE_COFF/.project
	-@ echo Importing Project atan2dp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2dp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66/atan2dp_66_LE_COFF"
	-@ echo Building Project atan2dp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2dp_66_LE_COFF -ccs.configuration Release
	-@ echo Project atan2dp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_LE_COFF"

clean::
	-$(RMDIR) "src/atan2dp//c66//atan2dp_66_LE_COFF"


#############################################################

# Rule to Build Project atan2dp_66_BE_COFF

#############################################################

.executables: src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out

.projects: src/atan2dp//c66//atan2dp_66_BE_COFF

src/atan2dp//c66//atan2dp_66_BE_COFF: src/atan2dp//c66//atan2dp_66_BE_COFF/.project

src/atan2dp//c66//atan2dp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2dp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_COFF_SRCATAN2DP/atan2dp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2dp//c66//atan2dp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_COFF_SRCATAN2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_COFF_SRCATAN2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atan2dp//c66//atan2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_BE_COFF_SRCATAN2DP=../../ >> src/atan2dp//c66//atan2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_BE_COFF_SRCATAN2DPC66=.././ >> src/atan2dp//c66//atan2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_BE_COFF_SRCCOMMON=../../../common >> src/atan2dp//c66//atan2dp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_BE_COFF"
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/atan2dp/atan2dp.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/atan2dp/atan2dp_d.c
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/atan2dp//c66/atan2dp.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/atan2dp//c66/atan2dp_i.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common/drvdp.c
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common/drvdp.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common/driver.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common/driver.c
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common/common.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common/tables.c
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/common//c66/common.h
src/atan2dp//c66//atan2dp_66_BE_COFF/Release/atan2dp_66_BE_COFF.out: src/atan2dp//c66//atan2dp_66_BE_COFF/.project
	-@ echo Importing Project atan2dp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2dp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66/atan2dp_66_BE_COFF"
	-@ echo Building Project atan2dp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2dp_66_BE_COFF -ccs.configuration Release
	-@ echo Project atan2dp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_BE_COFF"

clean::
	-$(RMDIR) "src/atan2dp//c66//atan2dp_66_BE_COFF"


#############################################################

# Rule to Build Project atan2dp_66_LE_ELF

#############################################################

.executables: src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out

.projects: src/atan2dp//c66//atan2dp_66_LE_ELF

src/atan2dp//c66//atan2dp_66_LE_ELF: src/atan2dp//c66//atan2dp_66_LE_ELF/.project

src/atan2dp//c66//atan2dp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2dp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_ELF_SRCATAN2DP/atan2dp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2dp//c66//atan2dp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_ELF_SRCATAN2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_ELF_SRCATAN2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atan2dp//c66//atan2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_LE_ELF_SRCATAN2DP=../../ >> src/atan2dp//c66//atan2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_LE_ELF_SRCATAN2DPC66=.././ >> src/atan2dp//c66//atan2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_LE_ELF_SRCCOMMON=../../../common >> src/atan2dp//c66//atan2dp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_LE_ELF"
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/atan2dp/atan2dp.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/atan2dp/atan2dp_d.c
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/atan2dp//c66/atan2dp.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/atan2dp//c66/atan2dp_i.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common/drvdp.c
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common/drvdp.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common/driver.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common/driver.c
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common/common.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common/tables.c
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/common//c66/common.h
src/atan2dp//c66//atan2dp_66_LE_ELF/Release/atan2dp_66_LE_ELF.out: src/atan2dp//c66//atan2dp_66_LE_ELF/.project
	-@ echo Importing Project atan2dp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2dp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66/atan2dp_66_LE_ELF"
	-@ echo Building Project atan2dp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2dp_66_LE_ELF -ccs.configuration Release
	-@ echo Project atan2dp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_LE_ELF"

clean::
	-$(RMDIR) "src/atan2dp//c66//atan2dp_66_LE_ELF"


#############################################################

# Rule to Build Project atan2dp_66_BE_ELF

#############################################################

.executables: src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out

.projects: src/atan2dp//c66//atan2dp_66_BE_ELF

src/atan2dp//c66//atan2dp_66_BE_ELF: src/atan2dp//c66//atan2dp_66_BE_ELF/.project

src/atan2dp//c66//atan2dp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2dp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_ELF_SRCATAN2DP/atan2dp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2dp//c66//atan2dp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_ELF_SRCATAN2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_ELF_SRCATAN2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atan2dp//c66//atan2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_BE_ELF_SRCATAN2DP=../../ >> src/atan2dp//c66//atan2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_BE_ELF_SRCATAN2DPC66=.././ >> src/atan2dp//c66//atan2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATAN2DP_66_BE_ELF_SRCCOMMON=../../../common >> src/atan2dp//c66//atan2dp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_BE_ELF"
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/atan2dp/atan2dp.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/atan2dp/atan2dp_d.c
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/atan2dp//c66/atan2dp.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/atan2dp//c66/atan2dp_i.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common/drvdp.c
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common/drvdp.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common/driver.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common/driver.c
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common/common.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common/tables.c
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/common//c66/common.h
src/atan2dp//c66//atan2dp_66_BE_ELF/Release/atan2dp_66_BE_ELF.out: src/atan2dp//c66//atan2dp_66_BE_ELF/.project
	-@ echo Importing Project atan2dp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2dp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2dp/c66/atan2dp_66_BE_ELF"
	-@ echo Building Project atan2dp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2dp_66_BE_ELF -ccs.configuration Release
	-@ echo Project atan2dp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2dp_66_BE_ELF"

clean::
	-$(RMDIR) "src/atan2dp//c66//atan2dp_66_BE_ELF"


#############################################################

# Rule to Build Project atan2sp_66_LE_COFF

#############################################################

.executables: src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out

.projects: src/atan2sp//c66//atan2sp_66_LE_COFF

src/atan2sp//c66//atan2sp_66_LE_COFF: src/atan2sp//c66//atan2sp_66_LE_COFF/.project

src/atan2sp//c66//atan2sp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2sp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_COFF_SRCATAN2SP/atan2sp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2sp//c66//atan2sp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_COFF_SRCATAN2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_COFF_SRCATAN2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atan2sp//c66//atan2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_LE_COFF_SRCATAN2SP=../../ >> src/atan2sp//c66//atan2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_LE_COFF_SRCATAN2SPC66=.././ >> src/atan2sp//c66//atan2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_LE_COFF_SRCCOMMON=../../../common >> src/atan2sp//c66//atan2sp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_LE_COFF"
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/atan2sp/atan2sp.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/atan2sp/atan2sp_d.c
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/atan2sp//c66/atan2sp.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/atan2sp//c66/atan2sp_i.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common/drvsp.c
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common/drvsp.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common/driver.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common/driver.c
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common/common.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common/tables.c
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/common//c66/common.h
src/atan2sp//c66//atan2sp_66_LE_COFF/Release/atan2sp_66_LE_COFF.out: src/atan2sp//c66//atan2sp_66_LE_COFF/.project
	-@ echo Importing Project atan2sp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2sp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66/atan2sp_66_LE_COFF"
	-@ echo Building Project atan2sp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2sp_66_LE_COFF -ccs.configuration Release
	-@ echo Project atan2sp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_LE_COFF"

clean::
	-$(RMDIR) "src/atan2sp//c66//atan2sp_66_LE_COFF"


#############################################################

# Rule to Build Project atan2sp_66_BE_COFF

#############################################################

.executables: src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out

.projects: src/atan2sp//c66//atan2sp_66_BE_COFF

src/atan2sp//c66//atan2sp_66_BE_COFF: src/atan2sp//c66//atan2sp_66_BE_COFF/.project

src/atan2sp//c66//atan2sp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2sp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_COFF_SRCATAN2SP/atan2sp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2sp//c66//atan2sp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_COFF_SRCATAN2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_COFF_SRCATAN2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atan2sp//c66//atan2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_BE_COFF_SRCATAN2SP=../../ >> src/atan2sp//c66//atan2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_BE_COFF_SRCATAN2SPC66=.././ >> src/atan2sp//c66//atan2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_BE_COFF_SRCCOMMON=../../../common >> src/atan2sp//c66//atan2sp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_BE_COFF"
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/atan2sp/atan2sp.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/atan2sp/atan2sp_d.c
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/atan2sp//c66/atan2sp.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/atan2sp//c66/atan2sp_i.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common/drvsp.c
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common/drvsp.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common/driver.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common/driver.c
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common/common.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common/tables.c
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/common//c66/common.h
src/atan2sp//c66//atan2sp_66_BE_COFF/Release/atan2sp_66_BE_COFF.out: src/atan2sp//c66//atan2sp_66_BE_COFF/.project
	-@ echo Importing Project atan2sp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2sp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66/atan2sp_66_BE_COFF"
	-@ echo Building Project atan2sp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2sp_66_BE_COFF -ccs.configuration Release
	-@ echo Project atan2sp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_BE_COFF"

clean::
	-$(RMDIR) "src/atan2sp//c66//atan2sp_66_BE_COFF"


#############################################################

# Rule to Build Project atan2sp_66_LE_ELF

#############################################################

.executables: src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out

.projects: src/atan2sp//c66//atan2sp_66_LE_ELF

src/atan2sp//c66//atan2sp_66_LE_ELF: src/atan2sp//c66//atan2sp_66_LE_ELF/.project

src/atan2sp//c66//atan2sp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2sp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_ELF_SRCATAN2SP/atan2sp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2sp//c66//atan2sp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_ELF_SRCATAN2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_ELF_SRCATAN2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atan2sp//c66//atan2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_LE_ELF_SRCATAN2SP=../../ >> src/atan2sp//c66//atan2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_LE_ELF_SRCATAN2SPC66=.././ >> src/atan2sp//c66//atan2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_LE_ELF_SRCCOMMON=../../../common >> src/atan2sp//c66//atan2sp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_LE_ELF"
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/atan2sp/atan2sp.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/atan2sp/atan2sp_d.c
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/atan2sp//c66/atan2sp.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/atan2sp//c66/atan2sp_i.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common/drvsp.c
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common/drvsp.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common/driver.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common/driver.c
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common/common.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common/tables.c
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/common//c66/common.h
src/atan2sp//c66//atan2sp_66_LE_ELF/Release/atan2sp_66_LE_ELF.out: src/atan2sp//c66//atan2sp_66_LE_ELF/.project
	-@ echo Importing Project atan2sp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2sp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66/atan2sp_66_LE_ELF"
	-@ echo Building Project atan2sp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2sp_66_LE_ELF -ccs.configuration Release
	-@ echo Project atan2sp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_LE_ELF"

clean::
	-$(RMDIR) "src/atan2sp//c66//atan2sp_66_LE_ELF"


#############################################################

# Rule to Build Project atan2sp_66_BE_ELF

#############################################################

.executables: src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out

.projects: src/atan2sp//c66//atan2sp_66_BE_ELF

src/atan2sp//c66//atan2sp_66_BE_ELF: src/atan2sp//c66//atan2sp_66_BE_ELF/.project

src/atan2sp//c66//atan2sp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atan2sp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_ELF_SRCATAN2SP/atan2sp_d.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atan2sp//c66//atan2sp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_ELF_SRCATAN2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_ELF_SRCATAN2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atan2sp//c66//atan2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_BE_ELF_SRCATAN2SP=../../ >> src/atan2sp//c66//atan2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_BE_ELF_SRCATAN2SPC66=.././ >> src/atan2sp//c66//atan2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATAN2SP_66_BE_ELF_SRCCOMMON=../../../common >> src/atan2sp//c66//atan2sp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_BE_ELF"
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/atan2sp/atan2sp.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/atan2sp/atan2sp_d.c
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/atan2sp//c66/atan2sp.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/atan2sp//c66/atan2sp_i.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common/drvsp.c
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common/drvsp.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common/driver.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common/driver.c
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common/common.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common/tables.c
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/common//c66/common.h
src/atan2sp//c66//atan2sp_66_BE_ELF/Release/atan2sp_66_BE_ELF.out: src/atan2sp//c66//atan2sp_66_BE_ELF/.project
	-@ echo Importing Project atan2sp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atan2sp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atan2sp/c66/atan2sp_66_BE_ELF"
	-@ echo Building Project atan2sp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atan2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atan2sp_66_BE_ELF -ccs.configuration Release
	-@ echo Project atan2sp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atan2sp_66_BE_ELF"

clean::
	-$(RMDIR) "src/atan2sp//c66//atan2sp_66_BE_ELF"


#############################################################

# Rule to Build Project atandp_66_LE_COFF

#############################################################

.executables: src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out

.projects: src/atandp//c66//atandp_66_LE_COFF

src/atandp//c66//atandp_66_LE_COFF: src/atandp//c66//atandp_66_LE_COFF/.project

src/atandp//c66//atandp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atandp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_COFF_SRCATANDP/atandp_d.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atandp//c66//atandp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_COFF_SRCATANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_COFF_SRCATANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atandp//c66//atandp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANDP_66_LE_COFF_SRCATANDP=../../ >> src/atandp//c66//atandp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANDP_66_LE_COFF_SRCATANDPC66=.././ >> src/atandp//c66//atandp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANDP_66_LE_COFF_SRCCOMMON=../../../common >> src/atandp//c66//atandp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atandp_66_LE_COFF"
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/atandp/atandp.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/atandp/atandp_d.c
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/atandp//c66/atandp.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/atandp//c66/atandp_i.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common/drvdp.c
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common/drvdp.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common/driver.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common/driver.c
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common/common.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common/tables.c
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/common//c66/common.h
src/atandp//c66//atandp_66_LE_COFF/Release/atandp_66_LE_COFF.out: src/atandp//c66//atandp_66_LE_COFF/.project
	-@ echo Importing Project atandp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atandp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66/atandp_66_LE_COFF"
	-@ echo Building Project atandp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atandp_66_LE_COFF -ccs.configuration Release
	-@ echo Project atandp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atandp_66_LE_COFF"

clean::
	-$(RMDIR) "src/atandp//c66//atandp_66_LE_COFF"


#############################################################

# Rule to Build Project atandp_66_BE_COFF

#############################################################

.executables: src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out

.projects: src/atandp//c66//atandp_66_BE_COFF

src/atandp//c66//atandp_66_BE_COFF: src/atandp//c66//atandp_66_BE_COFF/.project

src/atandp//c66//atandp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atandp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_COFF_SRCATANDP/atandp_d.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atandp//c66//atandp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_COFF_SRCATANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_COFF_SRCATANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atandp//c66//atandp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANDP_66_BE_COFF_SRCATANDP=../../ >> src/atandp//c66//atandp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANDP_66_BE_COFF_SRCATANDPC66=.././ >> src/atandp//c66//atandp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANDP_66_BE_COFF_SRCCOMMON=../../../common >> src/atandp//c66//atandp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atandp_66_BE_COFF"
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/atandp/atandp.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/atandp/atandp_d.c
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/atandp//c66/atandp.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/atandp//c66/atandp_i.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common/drvdp.c
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common/drvdp.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common/driver.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common/driver.c
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common/common.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common/tables.c
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/common//c66/common.h
src/atandp//c66//atandp_66_BE_COFF/Release/atandp_66_BE_COFF.out: src/atandp//c66//atandp_66_BE_COFF/.project
	-@ echo Importing Project atandp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atandp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66/atandp_66_BE_COFF"
	-@ echo Building Project atandp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atandp_66_BE_COFF -ccs.configuration Release
	-@ echo Project atandp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atandp_66_BE_COFF"

clean::
	-$(RMDIR) "src/atandp//c66//atandp_66_BE_COFF"


#############################################################

# Rule to Build Project atandp_66_LE_ELF

#############################################################

.executables: src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out

.projects: src/atandp//c66//atandp_66_LE_ELF

src/atandp//c66//atandp_66_LE_ELF: src/atandp//c66//atandp_66_LE_ELF/.project

src/atandp//c66//atandp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atandp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_ELF_SRCATANDP/atandp_d.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atandp//c66//atandp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_ELF_SRCATANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_ELF_SRCATANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atandp//c66//atandp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANDP_66_LE_ELF_SRCATANDP=../../ >> src/atandp//c66//atandp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANDP_66_LE_ELF_SRCATANDPC66=.././ >> src/atandp//c66//atandp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANDP_66_LE_ELF_SRCCOMMON=../../../common >> src/atandp//c66//atandp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atandp_66_LE_ELF"
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/atandp/atandp.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/atandp/atandp_d.c
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/atandp//c66/atandp.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/atandp//c66/atandp_i.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common/drvdp.c
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common/drvdp.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common/driver.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common/driver.c
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common/common.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common/tables.c
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/common//c66/common.h
src/atandp//c66//atandp_66_LE_ELF/Release/atandp_66_LE_ELF.out: src/atandp//c66//atandp_66_LE_ELF/.project
	-@ echo Importing Project atandp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atandp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66/atandp_66_LE_ELF"
	-@ echo Building Project atandp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atandp_66_LE_ELF -ccs.configuration Release
	-@ echo Project atandp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atandp_66_LE_ELF"

clean::
	-$(RMDIR) "src/atandp//c66//atandp_66_LE_ELF"


#############################################################

# Rule to Build Project atandp_66_BE_ELF

#############################################################

.executables: src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out

.projects: src/atandp//c66//atandp_66_BE_ELF

src/atandp//c66//atandp_66_BE_ELF: src/atandp//c66//atandp_66_BE_ELF/.project

src/atandp//c66//atandp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atandp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_ELF_SRCATANDP/atandp_d.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atandp//c66//atandp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_ELF_SRCATANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_ELF_SRCATANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atandp//c66//atandp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANDP_66_BE_ELF_SRCATANDP=../../ >> src/atandp//c66//atandp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANDP_66_BE_ELF_SRCATANDPC66=.././ >> src/atandp//c66//atandp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANDP_66_BE_ELF_SRCCOMMON=../../../common >> src/atandp//c66//atandp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atandp_66_BE_ELF"
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/atandp/atandp.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/atandp/atandp_d.c
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/atandp//c66/atandp.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/atandp//c66/atandp_i.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common/drvdp.c
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common/drvdp.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common/driver.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common/driver.c
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common/common.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common/tables.c
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/common//c66/common.h
src/atandp//c66//atandp_66_BE_ELF/Release/atandp_66_BE_ELF.out: src/atandp//c66//atandp_66_BE_ELF/.project
	-@ echo Importing Project atandp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atandp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atandp/c66/atandp_66_BE_ELF"
	-@ echo Building Project atandp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atandp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atandp_66_BE_ELF -ccs.configuration Release
	-@ echo Project atandp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atandp_66_BE_ELF"

clean::
	-$(RMDIR) "src/atandp//c66//atandp_66_BE_ELF"


#############################################################

# Rule to Build Project atanhdp_66_LE_COFF

#############################################################

.executables: src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out

.projects: src/atanhdp//c66//atanhdp_66_LE_COFF

src/atanhdp//c66//atanhdp_66_LE_COFF: src/atanhdp//c66//atanhdp_66_LE_COFF/.project

src/atanhdp//c66//atanhdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_COFF_SRCATANHDP/atanhdp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhdp//c66//atanhdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_COFF_SRCATANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_COFF_SRCATANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atanhdp//c66//atanhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANHDP_66_LE_COFF_SRCATANHDP=../../ >> src/atanhdp//c66//atanhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANHDP_66_LE_COFF_SRCATANHDPC66=.././ >> src/atanhdp//c66//atanhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANHDP_66_LE_COFF_SRCCOMMON=../../../common >> src/atanhdp//c66//atanhdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_LE_COFF"
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/atanhdp/atanhdp.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/atanhdp/atanhdp_d.c
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/atanhdp//c66/atanhdp.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/atanhdp//c66/atanhdp_i.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common/drvdp.c
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common/drvdp.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common/driver.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common/driver.c
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common/common.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common/tables.c
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/common//c66/common.h
src/atanhdp//c66//atanhdp_66_LE_COFF/Release/atanhdp_66_LE_COFF.out: src/atanhdp//c66//atanhdp_66_LE_COFF/.project
	-@ echo Importing Project atanhdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66/atanhdp_66_LE_COFF"
	-@ echo Building Project atanhdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project atanhdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/atanhdp//c66//atanhdp_66_LE_COFF"


#############################################################

# Rule to Build Project atanhdp_66_BE_COFF

#############################################################

.executables: src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out

.projects: src/atanhdp//c66//atanhdp_66_BE_COFF

src/atanhdp//c66//atanhdp_66_BE_COFF: src/atanhdp//c66//atanhdp_66_BE_COFF/.project

src/atanhdp//c66//atanhdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_COFF_SRCATANHDP/atanhdp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhdp//c66//atanhdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_COFF_SRCATANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_COFF_SRCATANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atanhdp//c66//atanhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANHDP_66_BE_COFF_SRCATANHDP=../../ >> src/atanhdp//c66//atanhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANHDP_66_BE_COFF_SRCATANHDPC66=.././ >> src/atanhdp//c66//atanhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANHDP_66_BE_COFF_SRCCOMMON=../../../common >> src/atanhdp//c66//atanhdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_BE_COFF"
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/atanhdp/atanhdp.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/atanhdp/atanhdp_d.c
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/atanhdp//c66/atanhdp.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/atanhdp//c66/atanhdp_i.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common/drvdp.c
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common/drvdp.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common/driver.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common/driver.c
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common/common.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common/tables.c
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/common//c66/common.h
src/atanhdp//c66//atanhdp_66_BE_COFF/Release/atanhdp_66_BE_COFF.out: src/atanhdp//c66//atanhdp_66_BE_COFF/.project
	-@ echo Importing Project atanhdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66/atanhdp_66_BE_COFF"
	-@ echo Building Project atanhdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project atanhdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/atanhdp//c66//atanhdp_66_BE_COFF"


#############################################################

# Rule to Build Project atanhdp_66_LE_ELF

#############################################################

.executables: src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out

.projects: src/atanhdp//c66//atanhdp_66_LE_ELF

src/atanhdp//c66//atanhdp_66_LE_ELF: src/atanhdp//c66//atanhdp_66_LE_ELF/.project

src/atanhdp//c66//atanhdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_ELF_SRCATANHDP/atanhdp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhdp//c66//atanhdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_ELF_SRCATANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_ELF_SRCATANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atanhdp//c66//atanhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANHDP_66_LE_ELF_SRCATANHDP=../../ >> src/atanhdp//c66//atanhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANHDP_66_LE_ELF_SRCATANHDPC66=.././ >> src/atanhdp//c66//atanhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANHDP_66_LE_ELF_SRCCOMMON=../../../common >> src/atanhdp//c66//atanhdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_LE_ELF"
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/atanhdp/atanhdp.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/atanhdp/atanhdp_d.c
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/atanhdp//c66/atanhdp.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/atanhdp//c66/atanhdp_i.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common/drvdp.c
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common/drvdp.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common/driver.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common/driver.c
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common/common.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common/tables.c
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/common//c66/common.h
src/atanhdp//c66//atanhdp_66_LE_ELF/Release/atanhdp_66_LE_ELF.out: src/atanhdp//c66//atanhdp_66_LE_ELF/.project
	-@ echo Importing Project atanhdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66/atanhdp_66_LE_ELF"
	-@ echo Building Project atanhdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project atanhdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/atanhdp//c66//atanhdp_66_LE_ELF"


#############################################################

# Rule to Build Project atanhdp_66_BE_ELF

#############################################################

.executables: src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out

.projects: src/atanhdp//c66//atanhdp_66_BE_ELF

src/atanhdp//c66//atanhdp_66_BE_ELF: src/atanhdp//c66//atanhdp_66_BE_ELF/.project

src/atanhdp//c66//atanhdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_ELF_SRCATANHDP/atanhdp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhdp//c66//atanhdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_ELF_SRCATANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_ELF_SRCATANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atanhdp//c66//atanhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANHDP_66_BE_ELF_SRCATANHDP=../../ >> src/atanhdp//c66//atanhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANHDP_66_BE_ELF_SRCATANHDPC66=.././ >> src/atanhdp//c66//atanhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANHDP_66_BE_ELF_SRCCOMMON=../../../common >> src/atanhdp//c66//atanhdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_BE_ELF"
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/atanhdp/atanhdp.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/atanhdp/atanhdp_d.c
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/atanhdp//c66/atanhdp.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/atanhdp//c66/atanhdp_i.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common/drvdp.c
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common/drvdp.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common/driver.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common/driver.c
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common/common.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common/tables.c
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/common//c66/common.h
src/atanhdp//c66//atanhdp_66_BE_ELF/Release/atanhdp_66_BE_ELF.out: src/atanhdp//c66//atanhdp_66_BE_ELF/.project
	-@ echo Importing Project atanhdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhdp/c66/atanhdp_66_BE_ELF"
	-@ echo Building Project atanhdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project atanhdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/atanhdp//c66//atanhdp_66_BE_ELF"


#############################################################

# Rule to Build Project atanhsp_66_LE_COFF

#############################################################

.executables: src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out

.projects: src/atanhsp//c66//atanhsp_66_LE_COFF

src/atanhsp//c66//atanhsp_66_LE_COFF: src/atanhsp//c66//atanhsp_66_LE_COFF/.project

src/atanhsp//c66//atanhsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_COFF_SRCATANHSP/atanhsp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhsp//c66//atanhsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_COFF_SRCATANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_COFF_SRCATANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atanhsp//c66//atanhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANHSP_66_LE_COFF_SRCATANHSP=../../ >> src/atanhsp//c66//atanhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANHSP_66_LE_COFF_SRCATANHSPC66=.././ >> src/atanhsp//c66//atanhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANHSP_66_LE_COFF_SRCCOMMON=../../../common >> src/atanhsp//c66//atanhsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_LE_COFF"
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/atanhsp/atanhsp.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/atanhsp/atanhsp_d.c
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/atanhsp//c66/atanhsp.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/atanhsp//c66/atanhsp_i.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common/drvsp.c
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common/drvsp.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common/driver.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common/driver.c
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common/common.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common/tables.c
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/common//c66/common.h
src/atanhsp//c66//atanhsp_66_LE_COFF/Release/atanhsp_66_LE_COFF.out: src/atanhsp//c66//atanhsp_66_LE_COFF/.project
	-@ echo Importing Project atanhsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66/atanhsp_66_LE_COFF"
	-@ echo Building Project atanhsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project atanhsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/atanhsp//c66//atanhsp_66_LE_COFF"


#############################################################

# Rule to Build Project atanhsp_66_BE_COFF

#############################################################

.executables: src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out

.projects: src/atanhsp//c66//atanhsp_66_BE_COFF

src/atanhsp//c66//atanhsp_66_BE_COFF: src/atanhsp//c66//atanhsp_66_BE_COFF/.project

src/atanhsp//c66//atanhsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_COFF_SRCATANHSP/atanhsp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhsp//c66//atanhsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_COFF_SRCATANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_COFF_SRCATANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atanhsp//c66//atanhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANHSP_66_BE_COFF_SRCATANHSP=../../ >> src/atanhsp//c66//atanhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANHSP_66_BE_COFF_SRCATANHSPC66=.././ >> src/atanhsp//c66//atanhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANHSP_66_BE_COFF_SRCCOMMON=../../../common >> src/atanhsp//c66//atanhsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_BE_COFF"
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/atanhsp/atanhsp.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/atanhsp/atanhsp_d.c
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/atanhsp//c66/atanhsp.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/atanhsp//c66/atanhsp_i.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common/drvsp.c
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common/drvsp.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common/driver.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common/driver.c
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common/common.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common/tables.c
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/common//c66/common.h
src/atanhsp//c66//atanhsp_66_BE_COFF/Release/atanhsp_66_BE_COFF.out: src/atanhsp//c66//atanhsp_66_BE_COFF/.project
	-@ echo Importing Project atanhsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66/atanhsp_66_BE_COFF"
	-@ echo Building Project atanhsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project atanhsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/atanhsp//c66//atanhsp_66_BE_COFF"


#############################################################

# Rule to Build Project atanhsp_66_LE_ELF

#############################################################

.executables: src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out

.projects: src/atanhsp//c66//atanhsp_66_LE_ELF

src/atanhsp//c66//atanhsp_66_LE_ELF: src/atanhsp//c66//atanhsp_66_LE_ELF/.project

src/atanhsp//c66//atanhsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_ELF_SRCATANHSP/atanhsp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhsp//c66//atanhsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_ELF_SRCATANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_ELF_SRCATANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atanhsp//c66//atanhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANHSP_66_LE_ELF_SRCATANHSP=../../ >> src/atanhsp//c66//atanhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANHSP_66_LE_ELF_SRCATANHSPC66=.././ >> src/atanhsp//c66//atanhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANHSP_66_LE_ELF_SRCCOMMON=../../../common >> src/atanhsp//c66//atanhsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_LE_ELF"
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/atanhsp/atanhsp.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/atanhsp/atanhsp_d.c
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/atanhsp//c66/atanhsp.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/atanhsp//c66/atanhsp_i.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common/drvsp.c
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common/drvsp.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common/driver.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common/driver.c
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common/common.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common/tables.c
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/common//c66/common.h
src/atanhsp//c66//atanhsp_66_LE_ELF/Release/atanhsp_66_LE_ELF.out: src/atanhsp//c66//atanhsp_66_LE_ELF/.project
	-@ echo Importing Project atanhsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66/atanhsp_66_LE_ELF"
	-@ echo Building Project atanhsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project atanhsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/atanhsp//c66//atanhsp_66_LE_ELF"


#############################################################

# Rule to Build Project atanhsp_66_BE_ELF

#############################################################

.executables: src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out

.projects: src/atanhsp//c66//atanhsp_66_BE_ELF

src/atanhsp//c66//atanhsp_66_BE_ELF: src/atanhsp//c66//atanhsp_66_BE_ELF/.project

src/atanhsp//c66//atanhsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atanhsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_ELF_SRCATANHSP/atanhsp_d.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atanhsp//c66//atanhsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_ELF_SRCATANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_ELF_SRCATANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atanhsp//c66//atanhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANHSP_66_BE_ELF_SRCATANHSP=../../ >> src/atanhsp//c66//atanhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANHSP_66_BE_ELF_SRCATANHSPC66=.././ >> src/atanhsp//c66//atanhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANHSP_66_BE_ELF_SRCCOMMON=../../../common >> src/atanhsp//c66//atanhsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_BE_ELF"
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/atanhsp/atanhsp.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/atanhsp/atanhsp_d.c
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/atanhsp//c66/atanhsp.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/atanhsp//c66/atanhsp_i.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common/drvsp.c
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common/drvsp.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common/driver.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common/driver.c
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common/common.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common/tables.c
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/common//c66/common.h
src/atanhsp//c66//atanhsp_66_BE_ELF/Release/atanhsp_66_BE_ELF.out: src/atanhsp//c66//atanhsp_66_BE_ELF/.project
	-@ echo Importing Project atanhsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atanhsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atanhsp/c66/atanhsp_66_BE_ELF"
	-@ echo Building Project atanhsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atanhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atanhsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project atanhsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atanhsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/atanhsp//c66//atanhsp_66_BE_ELF"


#############################################################

# Rule to Build Project atansp_66_LE_COFF

#############################################################

.executables: src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out

.projects: src/atansp//c66//atansp_66_LE_COFF

src/atansp//c66//atansp_66_LE_COFF: src/atansp//c66//atansp_66_LE_COFF/.project

src/atansp//c66//atansp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atansp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_COFF_SRCATANSP/atansp_d.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atansp//c66//atansp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_COFF_SRCATANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_COFF_SRCATANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atansp//c66//atansp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANSP_66_LE_COFF_SRCATANSP=../../ >> src/atansp//c66//atansp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANSP_66_LE_COFF_SRCATANSPC66=.././ >> src/atansp//c66//atansp_66_LE_COFF/macros.ini
	echo EXT_ROOT__ATANSP_66_LE_COFF_SRCCOMMON=../../../common >> src/atansp//c66//atansp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atansp_66_LE_COFF"
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/atansp/atansp.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/atansp/atansp_d.c
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/atansp//c66/atansp.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/atansp//c66/atansp_i.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common/drvsp.c
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common/drvsp.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common/driver.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common/driver.c
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common/common.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common/tables.c
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/common//c66/common.h
src/atansp//c66//atansp_66_LE_COFF/Release/atansp_66_LE_COFF.out: src/atansp//c66//atansp_66_LE_COFF/.project
	-@ echo Importing Project atansp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atansp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66/atansp_66_LE_COFF"
	-@ echo Building Project atansp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atansp_66_LE_COFF -ccs.configuration Release
	-@ echo Project atansp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atansp_66_LE_COFF"

clean::
	-$(RMDIR) "src/atansp//c66//atansp_66_LE_COFF"


#############################################################

# Rule to Build Project atansp_66_BE_COFF

#############################################################

.executables: src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out

.projects: src/atansp//c66//atansp_66_BE_COFF

src/atansp//c66//atansp_66_BE_COFF: src/atansp//c66//atansp_66_BE_COFF/.project

src/atansp//c66//atansp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atansp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_COFF_SRCATANSP/atansp_d.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atansp//c66//atansp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_COFF_SRCATANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_COFF_SRCATANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/atansp//c66//atansp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANSP_66_BE_COFF_SRCATANSP=../../ >> src/atansp//c66//atansp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANSP_66_BE_COFF_SRCATANSPC66=.././ >> src/atansp//c66//atansp_66_BE_COFF/macros.ini
	echo EXT_ROOT__ATANSP_66_BE_COFF_SRCCOMMON=../../../common >> src/atansp//c66//atansp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atansp_66_BE_COFF"
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/atansp/atansp.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/atansp/atansp_d.c
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/atansp//c66/atansp.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/atansp//c66/atansp_i.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common/drvsp.c
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common/drvsp.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common/driver.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common/driver.c
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common/common.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common/tables.c
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/common//c66/common.h
src/atansp//c66//atansp_66_BE_COFF/Release/atansp_66_BE_COFF.out: src/atansp//c66//atansp_66_BE_COFF/.project
	-@ echo Importing Project atansp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atansp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66/atansp_66_BE_COFF"
	-@ echo Building Project atansp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atansp_66_BE_COFF -ccs.configuration Release
	-@ echo Project atansp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atansp_66_BE_COFF"

clean::
	-$(RMDIR) "src/atansp//c66//atansp_66_BE_COFF"


#############################################################

# Rule to Build Project atansp_66_LE_ELF

#############################################################

.executables: src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out

.projects: src/atansp//c66//atansp_66_LE_ELF

src/atansp//c66//atansp_66_LE_ELF: src/atansp//c66//atansp_66_LE_ELF/.project

src/atansp//c66//atansp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atansp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_ELF_SRCATANSP/atansp_d.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atansp//c66//atansp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_ELF_SRCATANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_ELF_SRCATANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atansp//c66//atansp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANSP_66_LE_ELF_SRCATANSP=../../ >> src/atansp//c66//atansp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANSP_66_LE_ELF_SRCATANSPC66=.././ >> src/atansp//c66//atansp_66_LE_ELF/macros.ini
	echo EXT_ROOT__ATANSP_66_LE_ELF_SRCCOMMON=../../../common >> src/atansp//c66//atansp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atansp_66_LE_ELF"
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/atansp/atansp.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/atansp/atansp_d.c
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/atansp//c66/atansp.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/atansp//c66/atansp_i.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common/drvsp.c
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common/drvsp.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common/driver.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common/driver.c
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common/common.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common/tables.c
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/common//c66/common.h
src/atansp//c66//atansp_66_LE_ELF/Release/atansp_66_LE_ELF.out: src/atansp//c66//atansp_66_LE_ELF/.project
	-@ echo Importing Project atansp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atansp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66/atansp_66_LE_ELF"
	-@ echo Building Project atansp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atansp_66_LE_ELF -ccs.configuration Release
	-@ echo Project atansp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atansp_66_LE_ELF"

clean::
	-$(RMDIR) "src/atansp//c66//atansp_66_LE_ELF"


#############################################################

# Rule to Build Project atansp_66_BE_ELF

#############################################################

.executables: src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out

.projects: src/atansp//c66//atansp_66_BE_ELF

src/atansp//c66//atansp_66_BE_ELF: src/atansp//c66//atansp_66_BE_ELF/.project

src/atansp//c66//atansp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name atansp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_ELF_SRCATANSP/atansp_d.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/atansp//c66//atansp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_ELF_SRCATANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_ELF_SRCATANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66" \
 -ccs.definePathVariable EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/atansp//c66//atansp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANSP_66_BE_ELF_SRCATANSP=../../ >> src/atansp//c66//atansp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANSP_66_BE_ELF_SRCATANSPC66=.././ >> src/atansp//c66//atansp_66_BE_ELF/macros.ini
	echo EXT_ROOT__ATANSP_66_BE_ELF_SRCCOMMON=../../../common >> src/atansp//c66//atansp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/atansp_66_BE_ELF"
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/atansp/atansp.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/atansp/atansp_d.c
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/atansp//c66/atansp.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/atansp//c66/atansp_i.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common/drvsp.c
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common/drvsp.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common/driver.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common/driver.c
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common/common.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common/tables.c
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/common//c66/common.h
src/atansp//c66//atansp_66_BE_ELF/Release/atansp_66_BE_ELF.out: src/atansp//c66//atansp_66_BE_ELF/.project
	-@ echo Importing Project atansp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects atansp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/atansp/c66/atansp_66_BE_ELF"
	-@ echo Building Project atansp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/atansp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects atansp_66_BE_ELF -ccs.configuration Release
	-@ echo Project atansp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/atansp_66_BE_ELF"

clean::
	-$(RMDIR) "src/atansp//c66//atansp_66_BE_ELF"


#############################################################

# Rule to Build Project cosdp_66_LE_COFF

#############################################################

.executables: src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out

.projects: src/cosdp//c66//cosdp_66_LE_COFF

src/cosdp//c66//cosdp_66_LE_COFF: src/cosdp//c66//cosdp_66_LE_COFF/.project

src/cosdp//c66//cosdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cosdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_COFF_SRCCOSDP/cosdp_d.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cosdp//c66//cosdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_COFF_SRCCOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_COFF_SRCCOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/cosdp//c66//cosdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSDP_66_LE_COFF_SRCCOSDP=../../ >> src/cosdp//c66//cosdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSDP_66_LE_COFF_SRCCOSDPC66=.././ >> src/cosdp//c66//cosdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSDP_66_LE_COFF_SRCCOMMON=../../../common >> src/cosdp//c66//cosdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_LE_COFF"
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/cosdp/cosdp.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/cosdp/cosdp_d.c
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/cosdp//c66/cosdp.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/cosdp//c66/cosdp_i.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common/drvdp.c
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common/drvdp.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common/driver.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common/driver.c
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common/common.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common/tables.c
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/common//c66/common.h
src/cosdp//c66//cosdp_66_LE_COFF/Release/cosdp_66_LE_COFF.out: src/cosdp//c66//cosdp_66_LE_COFF/.project
	-@ echo Importing Project cosdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cosdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66/cosdp_66_LE_COFF"
	-@ echo Building Project cosdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cosdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project cosdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/cosdp//c66//cosdp_66_LE_COFF"


#############################################################

# Rule to Build Project cosdp_66_BE_COFF

#############################################################

.executables: src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out

.projects: src/cosdp//c66//cosdp_66_BE_COFF

src/cosdp//c66//cosdp_66_BE_COFF: src/cosdp//c66//cosdp_66_BE_COFF/.project

src/cosdp//c66//cosdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cosdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_COFF_SRCCOSDP/cosdp_d.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cosdp//c66//cosdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_COFF_SRCCOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_COFF_SRCCOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/cosdp//c66//cosdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSDP_66_BE_COFF_SRCCOSDP=../../ >> src/cosdp//c66//cosdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSDP_66_BE_COFF_SRCCOSDPC66=.././ >> src/cosdp//c66//cosdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSDP_66_BE_COFF_SRCCOMMON=../../../common >> src/cosdp//c66//cosdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_BE_COFF"
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/cosdp/cosdp.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/cosdp/cosdp_d.c
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/cosdp//c66/cosdp.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/cosdp//c66/cosdp_i.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common/drvdp.c
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common/drvdp.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common/driver.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common/driver.c
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common/common.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common/tables.c
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/common//c66/common.h
src/cosdp//c66//cosdp_66_BE_COFF/Release/cosdp_66_BE_COFF.out: src/cosdp//c66//cosdp_66_BE_COFF/.project
	-@ echo Importing Project cosdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cosdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66/cosdp_66_BE_COFF"
	-@ echo Building Project cosdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cosdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project cosdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/cosdp//c66//cosdp_66_BE_COFF"


#############################################################

# Rule to Build Project cosdp_66_LE_ELF

#############################################################

.executables: src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out

.projects: src/cosdp//c66//cosdp_66_LE_ELF

src/cosdp//c66//cosdp_66_LE_ELF: src/cosdp//c66//cosdp_66_LE_ELF/.project

src/cosdp//c66//cosdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cosdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_ELF_SRCCOSDP/cosdp_d.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cosdp//c66//cosdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_ELF_SRCCOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_ELF_SRCCOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/cosdp//c66//cosdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSDP_66_LE_ELF_SRCCOSDP=../../ >> src/cosdp//c66//cosdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSDP_66_LE_ELF_SRCCOSDPC66=.././ >> src/cosdp//c66//cosdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSDP_66_LE_ELF_SRCCOMMON=../../../common >> src/cosdp//c66//cosdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_LE_ELF"
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/cosdp/cosdp.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/cosdp/cosdp_d.c
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/cosdp//c66/cosdp.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/cosdp//c66/cosdp_i.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common/drvdp.c
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common/drvdp.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common/driver.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common/driver.c
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common/common.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common/tables.c
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/common//c66/common.h
src/cosdp//c66//cosdp_66_LE_ELF/Release/cosdp_66_LE_ELF.out: src/cosdp//c66//cosdp_66_LE_ELF/.project
	-@ echo Importing Project cosdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cosdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66/cosdp_66_LE_ELF"
	-@ echo Building Project cosdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cosdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project cosdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/cosdp//c66//cosdp_66_LE_ELF"


#############################################################

# Rule to Build Project cosdp_66_BE_ELF

#############################################################

.executables: src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out

.projects: src/cosdp//c66//cosdp_66_BE_ELF

src/cosdp//c66//cosdp_66_BE_ELF: src/cosdp//c66//cosdp_66_BE_ELF/.project

src/cosdp//c66//cosdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cosdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_ELF_SRCCOSDP/cosdp_d.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cosdp//c66//cosdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_ELF_SRCCOSDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_ELF_SRCCOSDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/cosdp//c66//cosdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSDP_66_BE_ELF_SRCCOSDP=../../ >> src/cosdp//c66//cosdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSDP_66_BE_ELF_SRCCOSDPC66=.././ >> src/cosdp//c66//cosdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSDP_66_BE_ELF_SRCCOMMON=../../../common >> src/cosdp//c66//cosdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_BE_ELF"
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/cosdp/cosdp.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/cosdp/cosdp_d.c
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/cosdp//c66/cosdp.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/cosdp//c66/cosdp_i.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common/drvdp.c
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common/drvdp.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common/driver.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common/driver.c
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common/common.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common/tables.c
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/common//c66/common.h
src/cosdp//c66//cosdp_66_BE_ELF/Release/cosdp_66_BE_ELF.out: src/cosdp//c66//cosdp_66_BE_ELF/.project
	-@ echo Importing Project cosdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cosdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cosdp/c66/cosdp_66_BE_ELF"
	-@ echo Building Project cosdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cosdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cosdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project cosdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cosdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/cosdp//c66//cosdp_66_BE_ELF"


#############################################################

# Rule to Build Project coshdp_66_LE_COFF

#############################################################

.executables: src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out

.projects: src/coshdp//c66//coshdp_66_LE_COFF

src/coshdp//c66//coshdp_66_LE_COFF: src/coshdp//c66//coshdp_66_LE_COFF/.project

src/coshdp//c66//coshdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_COFF_SRCCOSHDP/coshdp_d.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshdp//c66//coshdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_COFF_SRCCOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_COFF_SRCCOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/coshdp//c66//coshdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSHDP_66_LE_COFF_SRCCOSHDP=../../ >> src/coshdp//c66//coshdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSHDP_66_LE_COFF_SRCCOSHDPC66=.././ >> src/coshdp//c66//coshdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSHDP_66_LE_COFF_SRCCOMMON=../../../common >> src/coshdp//c66//coshdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_LE_COFF"
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/coshdp/coshdp.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/coshdp/coshdp_d.c
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/coshdp//c66/coshdp.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/coshdp//c66/coshdp_i.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common/drvdp.c
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common/drvdp.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common/driver.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common/driver.c
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common/common.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common/tables.c
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/common//c66/common.h
src/coshdp//c66//coshdp_66_LE_COFF/Release/coshdp_66_LE_COFF.out: src/coshdp//c66//coshdp_66_LE_COFF/.project
	-@ echo Importing Project coshdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66/coshdp_66_LE_COFF"
	-@ echo Building Project coshdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project coshdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/coshdp//c66//coshdp_66_LE_COFF"


#############################################################

# Rule to Build Project coshdp_66_BE_COFF

#############################################################

.executables: src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out

.projects: src/coshdp//c66//coshdp_66_BE_COFF

src/coshdp//c66//coshdp_66_BE_COFF: src/coshdp//c66//coshdp_66_BE_COFF/.project

src/coshdp//c66//coshdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_COFF_SRCCOSHDP/coshdp_d.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshdp//c66//coshdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_COFF_SRCCOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_COFF_SRCCOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/coshdp//c66//coshdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSHDP_66_BE_COFF_SRCCOSHDP=../../ >> src/coshdp//c66//coshdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSHDP_66_BE_COFF_SRCCOSHDPC66=.././ >> src/coshdp//c66//coshdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSHDP_66_BE_COFF_SRCCOMMON=../../../common >> src/coshdp//c66//coshdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_BE_COFF"
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/coshdp/coshdp.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/coshdp/coshdp_d.c
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/coshdp//c66/coshdp.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/coshdp//c66/coshdp_i.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common/drvdp.c
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common/drvdp.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common/driver.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common/driver.c
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common/common.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common/tables.c
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/common//c66/common.h
src/coshdp//c66//coshdp_66_BE_COFF/Release/coshdp_66_BE_COFF.out: src/coshdp//c66//coshdp_66_BE_COFF/.project
	-@ echo Importing Project coshdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66/coshdp_66_BE_COFF"
	-@ echo Building Project coshdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project coshdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/coshdp//c66//coshdp_66_BE_COFF"


#############################################################

# Rule to Build Project coshdp_66_LE_ELF

#############################################################

.executables: src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out

.projects: src/coshdp//c66//coshdp_66_LE_ELF

src/coshdp//c66//coshdp_66_LE_ELF: src/coshdp//c66//coshdp_66_LE_ELF/.project

src/coshdp//c66//coshdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_ELF_SRCCOSHDP/coshdp_d.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshdp//c66//coshdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_ELF_SRCCOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_ELF_SRCCOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/coshdp//c66//coshdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSHDP_66_LE_ELF_SRCCOSHDP=../../ >> src/coshdp//c66//coshdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSHDP_66_LE_ELF_SRCCOSHDPC66=.././ >> src/coshdp//c66//coshdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSHDP_66_LE_ELF_SRCCOMMON=../../../common >> src/coshdp//c66//coshdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_LE_ELF"
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/coshdp/coshdp.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/coshdp/coshdp_d.c
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/coshdp//c66/coshdp.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/coshdp//c66/coshdp_i.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common/drvdp.c
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common/drvdp.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common/driver.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common/driver.c
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common/common.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common/tables.c
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/common//c66/common.h
src/coshdp//c66//coshdp_66_LE_ELF/Release/coshdp_66_LE_ELF.out: src/coshdp//c66//coshdp_66_LE_ELF/.project
	-@ echo Importing Project coshdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66/coshdp_66_LE_ELF"
	-@ echo Building Project coshdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project coshdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/coshdp//c66//coshdp_66_LE_ELF"


#############################################################

# Rule to Build Project coshdp_66_BE_ELF

#############################################################

.executables: src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out

.projects: src/coshdp//c66//coshdp_66_BE_ELF

src/coshdp//c66//coshdp_66_BE_ELF: src/coshdp//c66//coshdp_66_BE_ELF/.project

src/coshdp//c66//coshdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_ELF_SRCCOSHDP/coshdp_d.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshdp//c66//coshdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_ELF_SRCCOSHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_ELF_SRCCOSHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/coshdp//c66//coshdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSHDP_66_BE_ELF_SRCCOSHDP=../../ >> src/coshdp//c66//coshdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSHDP_66_BE_ELF_SRCCOSHDPC66=.././ >> src/coshdp//c66//coshdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSHDP_66_BE_ELF_SRCCOMMON=../../../common >> src/coshdp//c66//coshdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_BE_ELF"
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/coshdp/coshdp.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/coshdp/coshdp_d.c
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/coshdp//c66/coshdp.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/coshdp//c66/coshdp_i.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common/drvdp.c
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common/drvdp.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common/driver.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common/driver.c
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common/common.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common/tables.c
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/common//c66/common.h
src/coshdp//c66//coshdp_66_BE_ELF/Release/coshdp_66_BE_ELF.out: src/coshdp//c66//coshdp_66_BE_ELF/.project
	-@ echo Importing Project coshdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshdp/c66/coshdp_66_BE_ELF"
	-@ echo Building Project coshdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project coshdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/coshdp//c66//coshdp_66_BE_ELF"


#############################################################

# Rule to Build Project coshsp_66_LE_COFF

#############################################################

.executables: src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out

.projects: src/coshsp//c66//coshsp_66_LE_COFF

src/coshsp//c66//coshsp_66_LE_COFF: src/coshsp//c66//coshsp_66_LE_COFF/.project

src/coshsp//c66//coshsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_COFF_SRCCOSHSP/coshsp_d.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshsp//c66//coshsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_COFF_SRCCOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_COFF_SRCCOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/coshsp//c66//coshsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSHSP_66_LE_COFF_SRCCOSHSP=../../ >> src/coshsp//c66//coshsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSHSP_66_LE_COFF_SRCCOSHSPC66=.././ >> src/coshsp//c66//coshsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSHSP_66_LE_COFF_SRCCOMMON=../../../common >> src/coshsp//c66//coshsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_LE_COFF"
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/coshsp/coshsp.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/coshsp/coshsp_d.c
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/coshsp//c66/coshsp.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/coshsp//c66/coshsp_i.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common/drvsp.c
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common/drvsp.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common/driver.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common/driver.c
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common/common.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common/tables.c
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/common//c66/common.h
src/coshsp//c66//coshsp_66_LE_COFF/Release/coshsp_66_LE_COFF.out: src/coshsp//c66//coshsp_66_LE_COFF/.project
	-@ echo Importing Project coshsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66/coshsp_66_LE_COFF"
	-@ echo Building Project coshsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project coshsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/coshsp//c66//coshsp_66_LE_COFF"


#############################################################

# Rule to Build Project coshsp_66_BE_COFF

#############################################################

.executables: src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out

.projects: src/coshsp//c66//coshsp_66_BE_COFF

src/coshsp//c66//coshsp_66_BE_COFF: src/coshsp//c66//coshsp_66_BE_COFF/.project

src/coshsp//c66//coshsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_COFF_SRCCOSHSP/coshsp_d.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshsp//c66//coshsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_COFF_SRCCOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_COFF_SRCCOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/coshsp//c66//coshsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSHSP_66_BE_COFF_SRCCOSHSP=../../ >> src/coshsp//c66//coshsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSHSP_66_BE_COFF_SRCCOSHSPC66=.././ >> src/coshsp//c66//coshsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSHSP_66_BE_COFF_SRCCOMMON=../../../common >> src/coshsp//c66//coshsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_BE_COFF"
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/coshsp/coshsp.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/coshsp/coshsp_d.c
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/coshsp//c66/coshsp.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/coshsp//c66/coshsp_i.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common/drvsp.c
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common/drvsp.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common/driver.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common/driver.c
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common/common.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common/tables.c
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/common//c66/common.h
src/coshsp//c66//coshsp_66_BE_COFF/Release/coshsp_66_BE_COFF.out: src/coshsp//c66//coshsp_66_BE_COFF/.project
	-@ echo Importing Project coshsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66/coshsp_66_BE_COFF"
	-@ echo Building Project coshsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project coshsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/coshsp//c66//coshsp_66_BE_COFF"


#############################################################

# Rule to Build Project coshsp_66_LE_ELF

#############################################################

.executables: src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out

.projects: src/coshsp//c66//coshsp_66_LE_ELF

src/coshsp//c66//coshsp_66_LE_ELF: src/coshsp//c66//coshsp_66_LE_ELF/.project

src/coshsp//c66//coshsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_ELF_SRCCOSHSP/coshsp_d.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshsp//c66//coshsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_ELF_SRCCOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_ELF_SRCCOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/coshsp//c66//coshsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSHSP_66_LE_ELF_SRCCOSHSP=../../ >> src/coshsp//c66//coshsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSHSP_66_LE_ELF_SRCCOSHSPC66=.././ >> src/coshsp//c66//coshsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSHSP_66_LE_ELF_SRCCOMMON=../../../common >> src/coshsp//c66//coshsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_LE_ELF"
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/coshsp/coshsp.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/coshsp/coshsp_d.c
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/coshsp//c66/coshsp.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/coshsp//c66/coshsp_i.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common/drvsp.c
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common/drvsp.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common/driver.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common/driver.c
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common/common.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common/tables.c
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/common//c66/common.h
src/coshsp//c66//coshsp_66_LE_ELF/Release/coshsp_66_LE_ELF.out: src/coshsp//c66//coshsp_66_LE_ELF/.project
	-@ echo Importing Project coshsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66/coshsp_66_LE_ELF"
	-@ echo Building Project coshsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project coshsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/coshsp//c66//coshsp_66_LE_ELF"


#############################################################

# Rule to Build Project coshsp_66_BE_ELF

#############################################################

.executables: src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out

.projects: src/coshsp//c66//coshsp_66_BE_ELF

src/coshsp//c66//coshsp_66_BE_ELF: src/coshsp//c66//coshsp_66_BE_ELF/.project

src/coshsp//c66//coshsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name coshsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_ELF_SRCCOSHSP/coshsp_d.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/coshsp//c66//coshsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_ELF_SRCCOSHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_ELF_SRCCOSHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/coshsp//c66//coshsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSHSP_66_BE_ELF_SRCCOSHSP=../../ >> src/coshsp//c66//coshsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSHSP_66_BE_ELF_SRCCOSHSPC66=.././ >> src/coshsp//c66//coshsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSHSP_66_BE_ELF_SRCCOMMON=../../../common >> src/coshsp//c66//coshsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_BE_ELF"
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/coshsp/coshsp.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/coshsp/coshsp_d.c
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/coshsp//c66/coshsp.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/coshsp//c66/coshsp_i.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common/drvsp.c
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common/drvsp.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common/driver.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common/driver.c
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common/common.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common/tables.c
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/common//c66/common.h
src/coshsp//c66//coshsp_66_BE_ELF/Release/coshsp_66_BE_ELF.out: src/coshsp//c66//coshsp_66_BE_ELF/.project
	-@ echo Importing Project coshsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects coshsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/coshsp/c66/coshsp_66_BE_ELF"
	-@ echo Building Project coshsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/coshsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects coshsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project coshsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/coshsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/coshsp//c66//coshsp_66_BE_ELF"


#############################################################

# Rule to Build Project cossp_66_LE_COFF

#############################################################

.executables: src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out

.projects: src/cossp//c66//cossp_66_LE_COFF

src/cossp//c66//cossp_66_LE_COFF: src/cossp//c66//cossp_66_LE_COFF/.project

src/cossp//c66//cossp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cossp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_COFF_SRCCOSSP/cossp_d.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cossp//c66//cossp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_COFF_SRCCOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_COFF_SRCCOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/cossp//c66//cossp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSSP_66_LE_COFF_SRCCOSSP=../../ >> src/cossp//c66//cossp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSSP_66_LE_COFF_SRCCOSSPC66=.././ >> src/cossp//c66//cossp_66_LE_COFF/macros.ini
	echo EXT_ROOT__COSSP_66_LE_COFF_SRCCOMMON=../../../common >> src/cossp//c66//cossp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cossp_66_LE_COFF"
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/cossp/cossp.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/cossp/cossp_d.c
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/cossp//c66/cossp.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/cossp//c66/cossp_i.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common/drvsp.c
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common/drvsp.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common/driver.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common/driver.c
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common/common.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common/tables.c
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/common//c66/common.h
src/cossp//c66//cossp_66_LE_COFF/Release/cossp_66_LE_COFF.out: src/cossp//c66//cossp_66_LE_COFF/.project
	-@ echo Importing Project cossp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cossp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66/cossp_66_LE_COFF"
	-@ echo Building Project cossp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cossp_66_LE_COFF -ccs.configuration Release
	-@ echo Project cossp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cossp_66_LE_COFF"

clean::
	-$(RMDIR) "src/cossp//c66//cossp_66_LE_COFF"


#############################################################

# Rule to Build Project cossp_66_BE_COFF

#############################################################

.executables: src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out

.projects: src/cossp//c66//cossp_66_BE_COFF

src/cossp//c66//cossp_66_BE_COFF: src/cossp//c66//cossp_66_BE_COFF/.project

src/cossp//c66//cossp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cossp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_COFF_SRCCOSSP/cossp_d.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cossp//c66//cossp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_COFF_SRCCOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_COFF_SRCCOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/cossp//c66//cossp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSSP_66_BE_COFF_SRCCOSSP=../../ >> src/cossp//c66//cossp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSSP_66_BE_COFF_SRCCOSSPC66=.././ >> src/cossp//c66//cossp_66_BE_COFF/macros.ini
	echo EXT_ROOT__COSSP_66_BE_COFF_SRCCOMMON=../../../common >> src/cossp//c66//cossp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cossp_66_BE_COFF"
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/cossp/cossp.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/cossp/cossp_d.c
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/cossp//c66/cossp.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/cossp//c66/cossp_i.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common/drvsp.c
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common/drvsp.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common/driver.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common/driver.c
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common/common.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common/tables.c
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/common//c66/common.h
src/cossp//c66//cossp_66_BE_COFF/Release/cossp_66_BE_COFF.out: src/cossp//c66//cossp_66_BE_COFF/.project
	-@ echo Importing Project cossp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cossp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66/cossp_66_BE_COFF"
	-@ echo Building Project cossp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cossp_66_BE_COFF -ccs.configuration Release
	-@ echo Project cossp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cossp_66_BE_COFF"

clean::
	-$(RMDIR) "src/cossp//c66//cossp_66_BE_COFF"


#############################################################

# Rule to Build Project cossp_66_LE_ELF

#############################################################

.executables: src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out

.projects: src/cossp//c66//cossp_66_LE_ELF

src/cossp//c66//cossp_66_LE_ELF: src/cossp//c66//cossp_66_LE_ELF/.project

src/cossp//c66//cossp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cossp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_ELF_SRCCOSSP/cossp_d.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cossp//c66//cossp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_ELF_SRCCOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_ELF_SRCCOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/cossp//c66//cossp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSSP_66_LE_ELF_SRCCOSSP=../../ >> src/cossp//c66//cossp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSSP_66_LE_ELF_SRCCOSSPC66=.././ >> src/cossp//c66//cossp_66_LE_ELF/macros.ini
	echo EXT_ROOT__COSSP_66_LE_ELF_SRCCOMMON=../../../common >> src/cossp//c66//cossp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cossp_66_LE_ELF"
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/cossp/cossp.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/cossp/cossp_d.c
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/cossp//c66/cossp.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/cossp//c66/cossp_i.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common/drvsp.c
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common/drvsp.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common/driver.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common/driver.c
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common/common.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common/tables.c
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/common//c66/common.h
src/cossp//c66//cossp_66_LE_ELF/Release/cossp_66_LE_ELF.out: src/cossp//c66//cossp_66_LE_ELF/.project
	-@ echo Importing Project cossp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cossp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66/cossp_66_LE_ELF"
	-@ echo Building Project cossp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cossp_66_LE_ELF -ccs.configuration Release
	-@ echo Project cossp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cossp_66_LE_ELF"

clean::
	-$(RMDIR) "src/cossp//c66//cossp_66_LE_ELF"


#############################################################

# Rule to Build Project cossp_66_BE_ELF

#############################################################

.executables: src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out

.projects: src/cossp//c66//cossp_66_BE_ELF

src/cossp//c66//cossp_66_BE_ELF: src/cossp//c66//cossp_66_BE_ELF/.project

src/cossp//c66//cossp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name cossp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_ELF_SRCCOSSP/cossp_d.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/cossp//c66//cossp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_ELF_SRCCOSSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_ELF_SRCCOSSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66" \
 -ccs.definePathVariable EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/cossp//c66//cossp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSSP_66_BE_ELF_SRCCOSSP=../../ >> src/cossp//c66//cossp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSSP_66_BE_ELF_SRCCOSSPC66=.././ >> src/cossp//c66//cossp_66_BE_ELF/macros.ini
	echo EXT_ROOT__COSSP_66_BE_ELF_SRCCOMMON=../../../common >> src/cossp//c66//cossp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/cossp_66_BE_ELF"
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/cossp/cossp.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/cossp/cossp_d.c
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/cossp//c66/cossp.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/cossp//c66/cossp_i.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common/drvsp.c
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common/drvsp.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common/driver.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common/driver.c
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common/common.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common/tables.c
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/common//c66/common.h
src/cossp//c66//cossp_66_BE_ELF/Release/cossp_66_BE_ELF.out: src/cossp//c66//cossp_66_BE_ELF/.project
	-@ echo Importing Project cossp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects cossp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/cossp/c66/cossp_66_BE_ELF"
	-@ echo Building Project cossp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/cossp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects cossp_66_BE_ELF -ccs.configuration Release
	-@ echo Project cossp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/cossp_66_BE_ELF"

clean::
	-$(RMDIR) "src/cossp//c66//cossp_66_BE_ELF"


#############################################################

# Rule to Build Project divdp_66_LE_COFF

#############################################################

.executables: src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out

.projects: src/divdp//c66//divdp_66_LE_COFF

src/divdp//c66//divdp_66_LE_COFF: src/divdp//c66//divdp_66_LE_COFF/.project

src/divdp//c66//divdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_COFF_SRCDIVDP/divdp_d.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divdp//c66//divdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_COFF_SRCDIVDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_COFF_SRCDIVDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/divdp//c66//divdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__DIVDP_66_LE_COFF_SRCDIVDP=../../ >> src/divdp//c66//divdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__DIVDP_66_LE_COFF_SRCDIVDPC66=.././ >> src/divdp//c66//divdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__DIVDP_66_LE_COFF_SRCCOMMON=../../../common >> src/divdp//c66//divdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divdp_66_LE_COFF"
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/divdp/divdp.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/divdp/divdp_d.c
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/divdp//c66/divdp.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/divdp//c66/divdp_i.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common/drvdp.c
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common/drvdp.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common/driver.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common/driver.c
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common/common.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common/tables.c
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/common//c66/common.h
src/divdp//c66//divdp_66_LE_COFF/Release/divdp_66_LE_COFF.out: src/divdp//c66//divdp_66_LE_COFF/.project
	-@ echo Importing Project divdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66/divdp_66_LE_COFF"
	-@ echo Building Project divdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project divdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/divdp//c66//divdp_66_LE_COFF"


#############################################################

# Rule to Build Project divdp_66_BE_COFF

#############################################################

.executables: src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out

.projects: src/divdp//c66//divdp_66_BE_COFF

src/divdp//c66//divdp_66_BE_COFF: src/divdp//c66//divdp_66_BE_COFF/.project

src/divdp//c66//divdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_COFF_SRCDIVDP/divdp_d.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divdp//c66//divdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_COFF_SRCDIVDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_COFF_SRCDIVDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/divdp//c66//divdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__DIVDP_66_BE_COFF_SRCDIVDP=../../ >> src/divdp//c66//divdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__DIVDP_66_BE_COFF_SRCDIVDPC66=.././ >> src/divdp//c66//divdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__DIVDP_66_BE_COFF_SRCCOMMON=../../../common >> src/divdp//c66//divdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divdp_66_BE_COFF"
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/divdp/divdp.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/divdp/divdp_d.c
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/divdp//c66/divdp.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/divdp//c66/divdp_i.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common/drvdp.c
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common/drvdp.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common/driver.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common/driver.c
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common/common.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common/tables.c
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/common//c66/common.h
src/divdp//c66//divdp_66_BE_COFF/Release/divdp_66_BE_COFF.out: src/divdp//c66//divdp_66_BE_COFF/.project
	-@ echo Importing Project divdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66/divdp_66_BE_COFF"
	-@ echo Building Project divdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project divdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/divdp//c66//divdp_66_BE_COFF"


#############################################################

# Rule to Build Project divdp_66_LE_ELF

#############################################################

.executables: src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out

.projects: src/divdp//c66//divdp_66_LE_ELF

src/divdp//c66//divdp_66_LE_ELF: src/divdp//c66//divdp_66_LE_ELF/.project

src/divdp//c66//divdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_ELF_SRCDIVDP/divdp_d.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divdp//c66//divdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_ELF_SRCDIVDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_ELF_SRCDIVDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/divdp//c66//divdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__DIVDP_66_LE_ELF_SRCDIVDP=../../ >> src/divdp//c66//divdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__DIVDP_66_LE_ELF_SRCDIVDPC66=.././ >> src/divdp//c66//divdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__DIVDP_66_LE_ELF_SRCCOMMON=../../../common >> src/divdp//c66//divdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divdp_66_LE_ELF"
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/divdp/divdp.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/divdp/divdp_d.c
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/divdp//c66/divdp.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/divdp//c66/divdp_i.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common/drvdp.c
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common/drvdp.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common/driver.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common/driver.c
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common/common.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common/tables.c
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/common//c66/common.h
src/divdp//c66//divdp_66_LE_ELF/Release/divdp_66_LE_ELF.out: src/divdp//c66//divdp_66_LE_ELF/.project
	-@ echo Importing Project divdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66/divdp_66_LE_ELF"
	-@ echo Building Project divdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project divdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/divdp//c66//divdp_66_LE_ELF"


#############################################################

# Rule to Build Project divdp_66_BE_ELF

#############################################################

.executables: src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out

.projects: src/divdp//c66//divdp_66_BE_ELF

src/divdp//c66//divdp_66_BE_ELF: src/divdp//c66//divdp_66_BE_ELF/.project

src/divdp//c66//divdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_ELF_SRCDIVDP/divdp_d.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divdp//c66//divdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_ELF_SRCDIVDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_ELF_SRCDIVDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/divdp//c66//divdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__DIVDP_66_BE_ELF_SRCDIVDP=../../ >> src/divdp//c66//divdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__DIVDP_66_BE_ELF_SRCDIVDPC66=.././ >> src/divdp//c66//divdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__DIVDP_66_BE_ELF_SRCCOMMON=../../../common >> src/divdp//c66//divdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divdp_66_BE_ELF"
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/divdp/divdp.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/divdp/divdp_d.c
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/divdp//c66/divdp.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/divdp//c66/divdp_i.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common/drvdp.c
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common/drvdp.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common/driver.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common/driver.c
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common/common.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common/tables.c
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/common//c66/common.h
src/divdp//c66//divdp_66_BE_ELF/Release/divdp_66_BE_ELF.out: src/divdp//c66//divdp_66_BE_ELF/.project
	-@ echo Importing Project divdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divdp/c66/divdp_66_BE_ELF"
	-@ echo Building Project divdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project divdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/divdp//c66//divdp_66_BE_ELF"


#############################################################

# Rule to Build Project divsp_66_LE_COFF

#############################################################

.executables: src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out

.projects: src/divsp//c66//divsp_66_LE_COFF

src/divsp//c66//divsp_66_LE_COFF: src/divsp//c66//divsp_66_LE_COFF/.project

src/divsp//c66//divsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_COFF_SRCDIVSP/divsp_d.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divsp//c66//divsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_COFF_SRCDIVSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_COFF_SRCDIVSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/divsp//c66//divsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__DIVSP_66_LE_COFF_SRCDIVSP=../../ >> src/divsp//c66//divsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__DIVSP_66_LE_COFF_SRCDIVSPC66=.././ >> src/divsp//c66//divsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__DIVSP_66_LE_COFF_SRCCOMMON=../../../common >> src/divsp//c66//divsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divsp_66_LE_COFF"
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/divsp/divsp.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/divsp/divsp_d.c
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/divsp//c66/divsp.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/divsp//c66/divsp_i.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common/drvsp.c
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common/drvsp.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common/driver.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common/driver.c
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common/common.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common/tables.c
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/common//c66/common.h
src/divsp//c66//divsp_66_LE_COFF/Release/divsp_66_LE_COFF.out: src/divsp//c66//divsp_66_LE_COFF/.project
	-@ echo Importing Project divsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66/divsp_66_LE_COFF"
	-@ echo Building Project divsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project divsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/divsp//c66//divsp_66_LE_COFF"


#############################################################

# Rule to Build Project divsp_66_BE_COFF

#############################################################

.executables: src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out

.projects: src/divsp//c66//divsp_66_BE_COFF

src/divsp//c66//divsp_66_BE_COFF: src/divsp//c66//divsp_66_BE_COFF/.project

src/divsp//c66//divsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_COFF_SRCDIVSP/divsp_d.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divsp//c66//divsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_COFF_SRCDIVSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_COFF_SRCDIVSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/divsp//c66//divsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__DIVSP_66_BE_COFF_SRCDIVSP=../../ >> src/divsp//c66//divsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__DIVSP_66_BE_COFF_SRCDIVSPC66=.././ >> src/divsp//c66//divsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__DIVSP_66_BE_COFF_SRCCOMMON=../../../common >> src/divsp//c66//divsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divsp_66_BE_COFF"
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/divsp/divsp.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/divsp/divsp_d.c
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/divsp//c66/divsp.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/divsp//c66/divsp_i.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common/drvsp.c
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common/drvsp.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common/driver.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common/driver.c
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common/common.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common/tables.c
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/common//c66/common.h
src/divsp//c66//divsp_66_BE_COFF/Release/divsp_66_BE_COFF.out: src/divsp//c66//divsp_66_BE_COFF/.project
	-@ echo Importing Project divsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66/divsp_66_BE_COFF"
	-@ echo Building Project divsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project divsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/divsp//c66//divsp_66_BE_COFF"


#############################################################

# Rule to Build Project divsp_66_LE_ELF

#############################################################

.executables: src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out

.projects: src/divsp//c66//divsp_66_LE_ELF

src/divsp//c66//divsp_66_LE_ELF: src/divsp//c66//divsp_66_LE_ELF/.project

src/divsp//c66//divsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_ELF_SRCDIVSP/divsp_d.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divsp//c66//divsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_ELF_SRCDIVSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_ELF_SRCDIVSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/divsp//c66//divsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__DIVSP_66_LE_ELF_SRCDIVSP=../../ >> src/divsp//c66//divsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__DIVSP_66_LE_ELF_SRCDIVSPC66=.././ >> src/divsp//c66//divsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__DIVSP_66_LE_ELF_SRCCOMMON=../../../common >> src/divsp//c66//divsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divsp_66_LE_ELF"
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/divsp/divsp.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/divsp/divsp_d.c
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/divsp//c66/divsp.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/divsp//c66/divsp_i.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common/drvsp.c
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common/drvsp.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common/driver.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common/driver.c
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common/common.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common/tables.c
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/common//c66/common.h
src/divsp//c66//divsp_66_LE_ELF/Release/divsp_66_LE_ELF.out: src/divsp//c66//divsp_66_LE_ELF/.project
	-@ echo Importing Project divsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66/divsp_66_LE_ELF"
	-@ echo Building Project divsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project divsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/divsp//c66//divsp_66_LE_ELF"


#############################################################

# Rule to Build Project divsp_66_BE_ELF

#############################################################

.executables: src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out

.projects: src/divsp//c66//divsp_66_BE_ELF

src/divsp//c66//divsp_66_BE_ELF: src/divsp//c66//divsp_66_BE_ELF/.project

src/divsp//c66//divsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name divsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_ELF_SRCDIVSP/divsp_d.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/divsp//c66//divsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_ELF_SRCDIVSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_ELF_SRCDIVSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66" \
 -ccs.definePathVariable EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/divsp//c66//divsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__DIVSP_66_BE_ELF_SRCDIVSP=../../ >> src/divsp//c66//divsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__DIVSP_66_BE_ELF_SRCDIVSPC66=.././ >> src/divsp//c66//divsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__DIVSP_66_BE_ELF_SRCCOMMON=../../../common >> src/divsp//c66//divsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/divsp_66_BE_ELF"
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/divsp/divsp.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/divsp/divsp_d.c
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/divsp//c66/divsp.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/divsp//c66/divsp_i.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common/drvsp.c
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common/drvsp.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common/driver.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common/driver.c
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common/common.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common/tables.c
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/common//c66/common.h
src/divsp//c66//divsp_66_BE_ELF/Release/divsp_66_BE_ELF.out: src/divsp//c66//divsp_66_BE_ELF/.project
	-@ echo Importing Project divsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects divsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/divsp/c66/divsp_66_BE_ELF"
	-@ echo Building Project divsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/divsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects divsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project divsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/divsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/divsp//c66//divsp_66_BE_ELF"


#############################################################

# Rule to Build Project exp10dp_66_LE_COFF

#############################################################

.executables: src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out

.projects: src/exp10dp//c66//exp10dp_66_LE_COFF

src/exp10dp//c66//exp10dp_66_LE_COFF: src/exp10dp//c66//exp10dp_66_LE_COFF/.project

src/exp10dp//c66//exp10dp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10dp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_COFF_SRCEXP10DP/exp10dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10dp//c66//exp10dp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_COFF_SRCEXP10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_COFF_SRCEXP10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp10dp//c66//exp10dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP10DP_66_LE_COFF_SRCEXP10DP=../../ >> src/exp10dp//c66//exp10dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP10DP_66_LE_COFF_SRCEXP10DPC66=.././ >> src/exp10dp//c66//exp10dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP10DP_66_LE_COFF_SRCCOMMON=../../../common >> src/exp10dp//c66//exp10dp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_LE_COFF"
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/exp10dp/exp10dp.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/exp10dp/exp10dp_d.c
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/exp10dp//c66/exp10dp.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/exp10dp//c66/exp10dp_i.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common/drvdp.c
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common/drvdp.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common/driver.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common/driver.c
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common/common.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common/tables.c
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/common//c66/common.h
src/exp10dp//c66//exp10dp_66_LE_COFF/Release/exp10dp_66_LE_COFF.out: src/exp10dp//c66//exp10dp_66_LE_COFF/.project
	-@ echo Importing Project exp10dp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10dp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66/exp10dp_66_LE_COFF"
	-@ echo Building Project exp10dp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10dp_66_LE_COFF -ccs.configuration Release
	-@ echo Project exp10dp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_LE_COFF"

clean::
	-$(RMDIR) "src/exp10dp//c66//exp10dp_66_LE_COFF"


#############################################################

# Rule to Build Project exp10dp_66_BE_COFF

#############################################################

.executables: src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out

.projects: src/exp10dp//c66//exp10dp_66_BE_COFF

src/exp10dp//c66//exp10dp_66_BE_COFF: src/exp10dp//c66//exp10dp_66_BE_COFF/.project

src/exp10dp//c66//exp10dp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10dp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_COFF_SRCEXP10DP/exp10dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10dp//c66//exp10dp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_COFF_SRCEXP10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_COFF_SRCEXP10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp10dp//c66//exp10dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP10DP_66_BE_COFF_SRCEXP10DP=../../ >> src/exp10dp//c66//exp10dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP10DP_66_BE_COFF_SRCEXP10DPC66=.././ >> src/exp10dp//c66//exp10dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP10DP_66_BE_COFF_SRCCOMMON=../../../common >> src/exp10dp//c66//exp10dp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_BE_COFF"
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/exp10dp/exp10dp.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/exp10dp/exp10dp_d.c
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/exp10dp//c66/exp10dp.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/exp10dp//c66/exp10dp_i.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common/drvdp.c
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common/drvdp.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common/driver.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common/driver.c
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common/common.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common/tables.c
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/common//c66/common.h
src/exp10dp//c66//exp10dp_66_BE_COFF/Release/exp10dp_66_BE_COFF.out: src/exp10dp//c66//exp10dp_66_BE_COFF/.project
	-@ echo Importing Project exp10dp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10dp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66/exp10dp_66_BE_COFF"
	-@ echo Building Project exp10dp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10dp_66_BE_COFF -ccs.configuration Release
	-@ echo Project exp10dp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_BE_COFF"

clean::
	-$(RMDIR) "src/exp10dp//c66//exp10dp_66_BE_COFF"


#############################################################

# Rule to Build Project exp10dp_66_LE_ELF

#############################################################

.executables: src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out

.projects: src/exp10dp//c66//exp10dp_66_LE_ELF

src/exp10dp//c66//exp10dp_66_LE_ELF: src/exp10dp//c66//exp10dp_66_LE_ELF/.project

src/exp10dp//c66//exp10dp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10dp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_ELF_SRCEXP10DP/exp10dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10dp//c66//exp10dp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_ELF_SRCEXP10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_ELF_SRCEXP10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp10dp//c66//exp10dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP10DP_66_LE_ELF_SRCEXP10DP=../../ >> src/exp10dp//c66//exp10dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP10DP_66_LE_ELF_SRCEXP10DPC66=.././ >> src/exp10dp//c66//exp10dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP10DP_66_LE_ELF_SRCCOMMON=../../../common >> src/exp10dp//c66//exp10dp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_LE_ELF"
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/exp10dp/exp10dp.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/exp10dp/exp10dp_d.c
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/exp10dp//c66/exp10dp.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/exp10dp//c66/exp10dp_i.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common/drvdp.c
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common/drvdp.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common/driver.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common/driver.c
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common/common.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common/tables.c
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/common//c66/common.h
src/exp10dp//c66//exp10dp_66_LE_ELF/Release/exp10dp_66_LE_ELF.out: src/exp10dp//c66//exp10dp_66_LE_ELF/.project
	-@ echo Importing Project exp10dp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10dp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66/exp10dp_66_LE_ELF"
	-@ echo Building Project exp10dp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10dp_66_LE_ELF -ccs.configuration Release
	-@ echo Project exp10dp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_LE_ELF"

clean::
	-$(RMDIR) "src/exp10dp//c66//exp10dp_66_LE_ELF"


#############################################################

# Rule to Build Project exp10dp_66_BE_ELF

#############################################################

.executables: src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out

.projects: src/exp10dp//c66//exp10dp_66_BE_ELF

src/exp10dp//c66//exp10dp_66_BE_ELF: src/exp10dp//c66//exp10dp_66_BE_ELF/.project

src/exp10dp//c66//exp10dp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10dp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_ELF_SRCEXP10DP/exp10dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10dp//c66//exp10dp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_ELF_SRCEXP10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_ELF_SRCEXP10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp10dp//c66//exp10dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP10DP_66_BE_ELF_SRCEXP10DP=../../ >> src/exp10dp//c66//exp10dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP10DP_66_BE_ELF_SRCEXP10DPC66=.././ >> src/exp10dp//c66//exp10dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP10DP_66_BE_ELF_SRCCOMMON=../../../common >> src/exp10dp//c66//exp10dp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_BE_ELF"
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/exp10dp/exp10dp.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/exp10dp/exp10dp_d.c
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/exp10dp//c66/exp10dp.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/exp10dp//c66/exp10dp_i.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common/drvdp.c
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common/drvdp.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common/driver.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common/driver.c
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common/common.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common/tables.c
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/common//c66/common.h
src/exp10dp//c66//exp10dp_66_BE_ELF/Release/exp10dp_66_BE_ELF.out: src/exp10dp//c66//exp10dp_66_BE_ELF/.project
	-@ echo Importing Project exp10dp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10dp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10dp/c66/exp10dp_66_BE_ELF"
	-@ echo Building Project exp10dp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10dp_66_BE_ELF -ccs.configuration Release
	-@ echo Project exp10dp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10dp_66_BE_ELF"

clean::
	-$(RMDIR) "src/exp10dp//c66//exp10dp_66_BE_ELF"


#############################################################

# Rule to Build Project exp10sp_66_LE_COFF

#############################################################

.executables: src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out

.projects: src/exp10sp//c66//exp10sp_66_LE_COFF

src/exp10sp//c66//exp10sp_66_LE_COFF: src/exp10sp//c66//exp10sp_66_LE_COFF/.project

src/exp10sp//c66//exp10sp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10sp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_COFF_SRCEXP10SP/exp10sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10sp//c66//exp10sp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_COFF_SRCEXP10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_COFF_SRCEXP10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp10sp//c66//exp10sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP10SP_66_LE_COFF_SRCEXP10SP=../../ >> src/exp10sp//c66//exp10sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP10SP_66_LE_COFF_SRCEXP10SPC66=.././ >> src/exp10sp//c66//exp10sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP10SP_66_LE_COFF_SRCCOMMON=../../../common >> src/exp10sp//c66//exp10sp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_LE_COFF"
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/exp10sp/exp10sp.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/exp10sp/exp10sp_d.c
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/exp10sp//c66/exp10sp.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/exp10sp//c66/exp10sp_i.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common/drvsp.c
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common/drvsp.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common/driver.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common/driver.c
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common/common.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common/tables.c
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/common//c66/common.h
src/exp10sp//c66//exp10sp_66_LE_COFF/Release/exp10sp_66_LE_COFF.out: src/exp10sp//c66//exp10sp_66_LE_COFF/.project
	-@ echo Importing Project exp10sp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10sp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66/exp10sp_66_LE_COFF"
	-@ echo Building Project exp10sp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10sp_66_LE_COFF -ccs.configuration Release
	-@ echo Project exp10sp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_LE_COFF"

clean::
	-$(RMDIR) "src/exp10sp//c66//exp10sp_66_LE_COFF"


#############################################################

# Rule to Build Project exp10sp_66_BE_COFF

#############################################################

.executables: src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out

.projects: src/exp10sp//c66//exp10sp_66_BE_COFF

src/exp10sp//c66//exp10sp_66_BE_COFF: src/exp10sp//c66//exp10sp_66_BE_COFF/.project

src/exp10sp//c66//exp10sp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10sp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_COFF_SRCEXP10SP/exp10sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10sp//c66//exp10sp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_COFF_SRCEXP10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_COFF_SRCEXP10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp10sp//c66//exp10sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP10SP_66_BE_COFF_SRCEXP10SP=../../ >> src/exp10sp//c66//exp10sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP10SP_66_BE_COFF_SRCEXP10SPC66=.././ >> src/exp10sp//c66//exp10sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP10SP_66_BE_COFF_SRCCOMMON=../../../common >> src/exp10sp//c66//exp10sp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_BE_COFF"
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/exp10sp/exp10sp.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/exp10sp/exp10sp_d.c
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/exp10sp//c66/exp10sp.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/exp10sp//c66/exp10sp_i.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common/drvsp.c
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common/drvsp.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common/driver.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common/driver.c
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common/common.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common/tables.c
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/common//c66/common.h
src/exp10sp//c66//exp10sp_66_BE_COFF/Release/exp10sp_66_BE_COFF.out: src/exp10sp//c66//exp10sp_66_BE_COFF/.project
	-@ echo Importing Project exp10sp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10sp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66/exp10sp_66_BE_COFF"
	-@ echo Building Project exp10sp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10sp_66_BE_COFF -ccs.configuration Release
	-@ echo Project exp10sp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_BE_COFF"

clean::
	-$(RMDIR) "src/exp10sp//c66//exp10sp_66_BE_COFF"


#############################################################

# Rule to Build Project exp10sp_66_LE_ELF

#############################################################

.executables: src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out

.projects: src/exp10sp//c66//exp10sp_66_LE_ELF

src/exp10sp//c66//exp10sp_66_LE_ELF: src/exp10sp//c66//exp10sp_66_LE_ELF/.project

src/exp10sp//c66//exp10sp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10sp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_ELF_SRCEXP10SP/exp10sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10sp//c66//exp10sp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_ELF_SRCEXP10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_ELF_SRCEXP10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp10sp//c66//exp10sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP10SP_66_LE_ELF_SRCEXP10SP=../../ >> src/exp10sp//c66//exp10sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP10SP_66_LE_ELF_SRCEXP10SPC66=.././ >> src/exp10sp//c66//exp10sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP10SP_66_LE_ELF_SRCCOMMON=../../../common >> src/exp10sp//c66//exp10sp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_LE_ELF"
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/exp10sp/exp10sp.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/exp10sp/exp10sp_d.c
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/exp10sp//c66/exp10sp.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/exp10sp//c66/exp10sp_i.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common/drvsp.c
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common/drvsp.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common/driver.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common/driver.c
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common/common.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common/tables.c
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/common//c66/common.h
src/exp10sp//c66//exp10sp_66_LE_ELF/Release/exp10sp_66_LE_ELF.out: src/exp10sp//c66//exp10sp_66_LE_ELF/.project
	-@ echo Importing Project exp10sp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10sp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66/exp10sp_66_LE_ELF"
	-@ echo Building Project exp10sp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10sp_66_LE_ELF -ccs.configuration Release
	-@ echo Project exp10sp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_LE_ELF"

clean::
	-$(RMDIR) "src/exp10sp//c66//exp10sp_66_LE_ELF"


#############################################################

# Rule to Build Project exp10sp_66_BE_ELF

#############################################################

.executables: src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out

.projects: src/exp10sp//c66//exp10sp_66_BE_ELF

src/exp10sp//c66//exp10sp_66_BE_ELF: src/exp10sp//c66//exp10sp_66_BE_ELF/.project

src/exp10sp//c66//exp10sp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp10sp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_ELF_SRCEXP10SP/exp10sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp10sp//c66//exp10sp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_ELF_SRCEXP10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_ELF_SRCEXP10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp10sp//c66//exp10sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP10SP_66_BE_ELF_SRCEXP10SP=../../ >> src/exp10sp//c66//exp10sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP10SP_66_BE_ELF_SRCEXP10SPC66=.././ >> src/exp10sp//c66//exp10sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP10SP_66_BE_ELF_SRCCOMMON=../../../common >> src/exp10sp//c66//exp10sp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_BE_ELF"
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/exp10sp/exp10sp.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/exp10sp/exp10sp_d.c
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/exp10sp//c66/exp10sp.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/exp10sp//c66/exp10sp_i.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common/drvsp.c
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common/drvsp.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common/driver.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common/driver.c
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common/common.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common/tables.c
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/common//c66/common.h
src/exp10sp//c66//exp10sp_66_BE_ELF/Release/exp10sp_66_BE_ELF.out: src/exp10sp//c66//exp10sp_66_BE_ELF/.project
	-@ echo Importing Project exp10sp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp10sp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp10sp/c66/exp10sp_66_BE_ELF"
	-@ echo Building Project exp10sp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp10sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp10sp_66_BE_ELF -ccs.configuration Release
	-@ echo Project exp10sp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp10sp_66_BE_ELF"

clean::
	-$(RMDIR) "src/exp10sp//c66//exp10sp_66_BE_ELF"


#############################################################

# Rule to Build Project exp2dp_66_LE_COFF

#############################################################

.executables: src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out

.projects: src/exp2dp//c66//exp2dp_66_LE_COFF

src/exp2dp//c66//exp2dp_66_LE_COFF: src/exp2dp//c66//exp2dp_66_LE_COFF/.project

src/exp2dp//c66//exp2dp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2dp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_COFF_SRCEXP2DP/exp2dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2dp//c66//exp2dp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_COFF_SRCEXP2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_COFF_SRCEXP2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp2dp//c66//exp2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP2DP_66_LE_COFF_SRCEXP2DP=../../ >> src/exp2dp//c66//exp2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP2DP_66_LE_COFF_SRCEXP2DPC66=.././ >> src/exp2dp//c66//exp2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP2DP_66_LE_COFF_SRCCOMMON=../../../common >> src/exp2dp//c66//exp2dp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_LE_COFF"
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/exp2dp/exp2dp.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/exp2dp/exp2dp_d.c
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/exp2dp//c66/exp2dp.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/exp2dp//c66/exp2dp_i.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common/drvdp.c
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common/drvdp.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common/driver.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common/driver.c
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common/common.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common/tables.c
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/common//c66/common.h
src/exp2dp//c66//exp2dp_66_LE_COFF/Release/exp2dp_66_LE_COFF.out: src/exp2dp//c66//exp2dp_66_LE_COFF/.project
	-@ echo Importing Project exp2dp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2dp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66/exp2dp_66_LE_COFF"
	-@ echo Building Project exp2dp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2dp_66_LE_COFF -ccs.configuration Release
	-@ echo Project exp2dp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_LE_COFF"

clean::
	-$(RMDIR) "src/exp2dp//c66//exp2dp_66_LE_COFF"


#############################################################

# Rule to Build Project exp2dp_66_BE_COFF

#############################################################

.executables: src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out

.projects: src/exp2dp//c66//exp2dp_66_BE_COFF

src/exp2dp//c66//exp2dp_66_BE_COFF: src/exp2dp//c66//exp2dp_66_BE_COFF/.project

src/exp2dp//c66//exp2dp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2dp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_COFF_SRCEXP2DP/exp2dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2dp//c66//exp2dp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_COFF_SRCEXP2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_COFF_SRCEXP2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp2dp//c66//exp2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP2DP_66_BE_COFF_SRCEXP2DP=../../ >> src/exp2dp//c66//exp2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP2DP_66_BE_COFF_SRCEXP2DPC66=.././ >> src/exp2dp//c66//exp2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP2DP_66_BE_COFF_SRCCOMMON=../../../common >> src/exp2dp//c66//exp2dp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_BE_COFF"
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/exp2dp/exp2dp.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/exp2dp/exp2dp_d.c
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/exp2dp//c66/exp2dp.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/exp2dp//c66/exp2dp_i.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common/drvdp.c
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common/drvdp.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common/driver.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common/driver.c
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common/common.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common/tables.c
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/common//c66/common.h
src/exp2dp//c66//exp2dp_66_BE_COFF/Release/exp2dp_66_BE_COFF.out: src/exp2dp//c66//exp2dp_66_BE_COFF/.project
	-@ echo Importing Project exp2dp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2dp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66/exp2dp_66_BE_COFF"
	-@ echo Building Project exp2dp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2dp_66_BE_COFF -ccs.configuration Release
	-@ echo Project exp2dp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_BE_COFF"

clean::
	-$(RMDIR) "src/exp2dp//c66//exp2dp_66_BE_COFF"


#############################################################

# Rule to Build Project exp2dp_66_LE_ELF

#############################################################

.executables: src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out

.projects: src/exp2dp//c66//exp2dp_66_LE_ELF

src/exp2dp//c66//exp2dp_66_LE_ELF: src/exp2dp//c66//exp2dp_66_LE_ELF/.project

src/exp2dp//c66//exp2dp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2dp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_ELF_SRCEXP2DP/exp2dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2dp//c66//exp2dp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_ELF_SRCEXP2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_ELF_SRCEXP2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp2dp//c66//exp2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP2DP_66_LE_ELF_SRCEXP2DP=../../ >> src/exp2dp//c66//exp2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP2DP_66_LE_ELF_SRCEXP2DPC66=.././ >> src/exp2dp//c66//exp2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP2DP_66_LE_ELF_SRCCOMMON=../../../common >> src/exp2dp//c66//exp2dp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_LE_ELF"
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/exp2dp/exp2dp.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/exp2dp/exp2dp_d.c
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/exp2dp//c66/exp2dp.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/exp2dp//c66/exp2dp_i.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common/drvdp.c
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common/drvdp.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common/driver.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common/driver.c
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common/common.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common/tables.c
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/common//c66/common.h
src/exp2dp//c66//exp2dp_66_LE_ELF/Release/exp2dp_66_LE_ELF.out: src/exp2dp//c66//exp2dp_66_LE_ELF/.project
	-@ echo Importing Project exp2dp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2dp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66/exp2dp_66_LE_ELF"
	-@ echo Building Project exp2dp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2dp_66_LE_ELF -ccs.configuration Release
	-@ echo Project exp2dp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_LE_ELF"

clean::
	-$(RMDIR) "src/exp2dp//c66//exp2dp_66_LE_ELF"


#############################################################

# Rule to Build Project exp2dp_66_BE_ELF

#############################################################

.executables: src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out

.projects: src/exp2dp//c66//exp2dp_66_BE_ELF

src/exp2dp//c66//exp2dp_66_BE_ELF: src/exp2dp//c66//exp2dp_66_BE_ELF/.project

src/exp2dp//c66//exp2dp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2dp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_ELF_SRCEXP2DP/exp2dp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2dp//c66//exp2dp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_ELF_SRCEXP2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_ELF_SRCEXP2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp2dp//c66//exp2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP2DP_66_BE_ELF_SRCEXP2DP=../../ >> src/exp2dp//c66//exp2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP2DP_66_BE_ELF_SRCEXP2DPC66=.././ >> src/exp2dp//c66//exp2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP2DP_66_BE_ELF_SRCCOMMON=../../../common >> src/exp2dp//c66//exp2dp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_BE_ELF"
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/exp2dp/exp2dp.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/exp2dp/exp2dp_d.c
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/exp2dp//c66/exp2dp.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/exp2dp//c66/exp2dp_i.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common/drvdp.c
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common/drvdp.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common/driver.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common/driver.c
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common/common.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common/tables.c
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/common//c66/common.h
src/exp2dp//c66//exp2dp_66_BE_ELF/Release/exp2dp_66_BE_ELF.out: src/exp2dp//c66//exp2dp_66_BE_ELF/.project
	-@ echo Importing Project exp2dp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2dp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2dp/c66/exp2dp_66_BE_ELF"
	-@ echo Building Project exp2dp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2dp_66_BE_ELF -ccs.configuration Release
	-@ echo Project exp2dp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2dp_66_BE_ELF"

clean::
	-$(RMDIR) "src/exp2dp//c66//exp2dp_66_BE_ELF"


#############################################################

# Rule to Build Project exp2sp_66_LE_COFF

#############################################################

.executables: src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out

.projects: src/exp2sp//c66//exp2sp_66_LE_COFF

src/exp2sp//c66//exp2sp_66_LE_COFF: src/exp2sp//c66//exp2sp_66_LE_COFF/.project

src/exp2sp//c66//exp2sp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2sp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_COFF_SRCEXP2SP/exp2sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2sp//c66//exp2sp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_COFF_SRCEXP2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_COFF_SRCEXP2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp2sp//c66//exp2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP2SP_66_LE_COFF_SRCEXP2SP=../../ >> src/exp2sp//c66//exp2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP2SP_66_LE_COFF_SRCEXP2SPC66=.././ >> src/exp2sp//c66//exp2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXP2SP_66_LE_COFF_SRCCOMMON=../../../common >> src/exp2sp//c66//exp2sp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_LE_COFF"
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/exp2sp/exp2sp.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/exp2sp/exp2sp_d.c
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/exp2sp//c66/exp2sp.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/exp2sp//c66/exp2sp_i.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common/drvsp.c
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common/drvsp.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common/driver.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common/driver.c
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common/common.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common/tables.c
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/common//c66/common.h
src/exp2sp//c66//exp2sp_66_LE_COFF/Release/exp2sp_66_LE_COFF.out: src/exp2sp//c66//exp2sp_66_LE_COFF/.project
	-@ echo Importing Project exp2sp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2sp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66/exp2sp_66_LE_COFF"
	-@ echo Building Project exp2sp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2sp_66_LE_COFF -ccs.configuration Release
	-@ echo Project exp2sp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_LE_COFF"

clean::
	-$(RMDIR) "src/exp2sp//c66//exp2sp_66_LE_COFF"


#############################################################

# Rule to Build Project exp2sp_66_BE_COFF

#############################################################

.executables: src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out

.projects: src/exp2sp//c66//exp2sp_66_BE_COFF

src/exp2sp//c66//exp2sp_66_BE_COFF: src/exp2sp//c66//exp2sp_66_BE_COFF/.project

src/exp2sp//c66//exp2sp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2sp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_COFF_SRCEXP2SP/exp2sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2sp//c66//exp2sp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_COFF_SRCEXP2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_COFF_SRCEXP2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/exp2sp//c66//exp2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP2SP_66_BE_COFF_SRCEXP2SP=../../ >> src/exp2sp//c66//exp2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP2SP_66_BE_COFF_SRCEXP2SPC66=.././ >> src/exp2sp//c66//exp2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXP2SP_66_BE_COFF_SRCCOMMON=../../../common >> src/exp2sp//c66//exp2sp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_BE_COFF"
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/exp2sp/exp2sp.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/exp2sp/exp2sp_d.c
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/exp2sp//c66/exp2sp.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/exp2sp//c66/exp2sp_i.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common/drvsp.c
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common/drvsp.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common/driver.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common/driver.c
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common/common.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common/tables.c
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/common//c66/common.h
src/exp2sp//c66//exp2sp_66_BE_COFF/Release/exp2sp_66_BE_COFF.out: src/exp2sp//c66//exp2sp_66_BE_COFF/.project
	-@ echo Importing Project exp2sp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2sp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66/exp2sp_66_BE_COFF"
	-@ echo Building Project exp2sp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2sp_66_BE_COFF -ccs.configuration Release
	-@ echo Project exp2sp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_BE_COFF"

clean::
	-$(RMDIR) "src/exp2sp//c66//exp2sp_66_BE_COFF"


#############################################################

# Rule to Build Project exp2sp_66_LE_ELF

#############################################################

.executables: src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out

.projects: src/exp2sp//c66//exp2sp_66_LE_ELF

src/exp2sp//c66//exp2sp_66_LE_ELF: src/exp2sp//c66//exp2sp_66_LE_ELF/.project

src/exp2sp//c66//exp2sp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2sp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_ELF_SRCEXP2SP/exp2sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2sp//c66//exp2sp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_ELF_SRCEXP2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_ELF_SRCEXP2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp2sp//c66//exp2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP2SP_66_LE_ELF_SRCEXP2SP=../../ >> src/exp2sp//c66//exp2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP2SP_66_LE_ELF_SRCEXP2SPC66=.././ >> src/exp2sp//c66//exp2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXP2SP_66_LE_ELF_SRCCOMMON=../../../common >> src/exp2sp//c66//exp2sp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_LE_ELF"
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/exp2sp/exp2sp.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/exp2sp/exp2sp_d.c
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/exp2sp//c66/exp2sp.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/exp2sp//c66/exp2sp_i.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common/drvsp.c
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common/drvsp.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common/driver.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common/driver.c
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common/common.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common/tables.c
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/common//c66/common.h
src/exp2sp//c66//exp2sp_66_LE_ELF/Release/exp2sp_66_LE_ELF.out: src/exp2sp//c66//exp2sp_66_LE_ELF/.project
	-@ echo Importing Project exp2sp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2sp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66/exp2sp_66_LE_ELF"
	-@ echo Building Project exp2sp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2sp_66_LE_ELF -ccs.configuration Release
	-@ echo Project exp2sp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_LE_ELF"

clean::
	-$(RMDIR) "src/exp2sp//c66//exp2sp_66_LE_ELF"


#############################################################

# Rule to Build Project exp2sp_66_BE_ELF

#############################################################

.executables: src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out

.projects: src/exp2sp//c66//exp2sp_66_BE_ELF

src/exp2sp//c66//exp2sp_66_BE_ELF: src/exp2sp//c66//exp2sp_66_BE_ELF/.project

src/exp2sp//c66//exp2sp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name exp2sp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_ELF_SRCEXP2SP/exp2sp_d.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/exp2sp//c66//exp2sp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_ELF_SRCEXP2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_ELF_SRCEXP2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/exp2sp//c66//exp2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP2SP_66_BE_ELF_SRCEXP2SP=../../ >> src/exp2sp//c66//exp2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP2SP_66_BE_ELF_SRCEXP2SPC66=.././ >> src/exp2sp//c66//exp2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXP2SP_66_BE_ELF_SRCCOMMON=../../../common >> src/exp2sp//c66//exp2sp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_BE_ELF"
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/exp2sp/exp2sp.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/exp2sp/exp2sp_d.c
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/exp2sp//c66/exp2sp.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/exp2sp//c66/exp2sp_i.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common/drvsp.c
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common/drvsp.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common/driver.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common/driver.c
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common/common.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common/tables.c
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/common//c66/common.h
src/exp2sp//c66//exp2sp_66_BE_ELF/Release/exp2sp_66_BE_ELF.out: src/exp2sp//c66//exp2sp_66_BE_ELF/.project
	-@ echo Importing Project exp2sp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects exp2sp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/exp2sp/c66/exp2sp_66_BE_ELF"
	-@ echo Building Project exp2sp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/exp2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects exp2sp_66_BE_ELF -ccs.configuration Release
	-@ echo Project exp2sp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/exp2sp_66_BE_ELF"

clean::
	-$(RMDIR) "src/exp2sp//c66//exp2sp_66_BE_ELF"


#############################################################

# Rule to Build Project expdp_66_LE_COFF

#############################################################

.executables: src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out

.projects: src/expdp//c66//expdp_66_LE_COFF

src/expdp//c66//expdp_66_LE_COFF: src/expdp//c66//expdp_66_LE_COFF/.project

src/expdp//c66//expdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_COFF_SRCEXPDP/expdp_d.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expdp//c66//expdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_COFF_SRCEXPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_COFF_SRCEXPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/expdp//c66//expdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXPDP_66_LE_COFF_SRCEXPDP=../../ >> src/expdp//c66//expdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXPDP_66_LE_COFF_SRCEXPDPC66=.././ >> src/expdp//c66//expdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXPDP_66_LE_COFF_SRCCOMMON=../../../common >> src/expdp//c66//expdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expdp_66_LE_COFF"
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/expdp/expdp.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/expdp/expdp_d.c
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/expdp//c66/expdp.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/expdp//c66/expdp_i.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common/drvdp.c
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common/drvdp.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common/driver.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common/driver.c
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common/common.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common/tables.c
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/common//c66/common.h
src/expdp//c66//expdp_66_LE_COFF/Release/expdp_66_LE_COFF.out: src/expdp//c66//expdp_66_LE_COFF/.project
	-@ echo Importing Project expdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66/expdp_66_LE_COFF"
	-@ echo Building Project expdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project expdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/expdp//c66//expdp_66_LE_COFF"


#############################################################

# Rule to Build Project expdp_66_BE_COFF

#############################################################

.executables: src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out

.projects: src/expdp//c66//expdp_66_BE_COFF

src/expdp//c66//expdp_66_BE_COFF: src/expdp//c66//expdp_66_BE_COFF/.project

src/expdp//c66//expdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_COFF_SRCEXPDP/expdp_d.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expdp//c66//expdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_COFF_SRCEXPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_COFF_SRCEXPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/expdp//c66//expdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXPDP_66_BE_COFF_SRCEXPDP=../../ >> src/expdp//c66//expdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXPDP_66_BE_COFF_SRCEXPDPC66=.././ >> src/expdp//c66//expdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXPDP_66_BE_COFF_SRCCOMMON=../../../common >> src/expdp//c66//expdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expdp_66_BE_COFF"
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/expdp/expdp.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/expdp/expdp_d.c
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/expdp//c66/expdp.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/expdp//c66/expdp_i.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common/drvdp.c
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common/drvdp.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common/driver.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common/driver.c
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common/common.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common/tables.c
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/common//c66/common.h
src/expdp//c66//expdp_66_BE_COFF/Release/expdp_66_BE_COFF.out: src/expdp//c66//expdp_66_BE_COFF/.project
	-@ echo Importing Project expdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66/expdp_66_BE_COFF"
	-@ echo Building Project expdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project expdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/expdp//c66//expdp_66_BE_COFF"


#############################################################

# Rule to Build Project expdp_66_LE_ELF

#############################################################

.executables: src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out

.projects: src/expdp//c66//expdp_66_LE_ELF

src/expdp//c66//expdp_66_LE_ELF: src/expdp//c66//expdp_66_LE_ELF/.project

src/expdp//c66//expdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_ELF_SRCEXPDP/expdp_d.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expdp//c66//expdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_ELF_SRCEXPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_ELF_SRCEXPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/expdp//c66//expdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXPDP_66_LE_ELF_SRCEXPDP=../../ >> src/expdp//c66//expdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXPDP_66_LE_ELF_SRCEXPDPC66=.././ >> src/expdp//c66//expdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXPDP_66_LE_ELF_SRCCOMMON=../../../common >> src/expdp//c66//expdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expdp_66_LE_ELF"
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/expdp/expdp.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/expdp/expdp_d.c
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/expdp//c66/expdp.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/expdp//c66/expdp_i.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common/drvdp.c
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common/drvdp.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common/driver.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common/driver.c
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common/common.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common/tables.c
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/common//c66/common.h
src/expdp//c66//expdp_66_LE_ELF/Release/expdp_66_LE_ELF.out: src/expdp//c66//expdp_66_LE_ELF/.project
	-@ echo Importing Project expdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66/expdp_66_LE_ELF"
	-@ echo Building Project expdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project expdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/expdp//c66//expdp_66_LE_ELF"


#############################################################

# Rule to Build Project expdp_66_BE_ELF

#############################################################

.executables: src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out

.projects: src/expdp//c66//expdp_66_BE_ELF

src/expdp//c66//expdp_66_BE_ELF: src/expdp//c66//expdp_66_BE_ELF/.project

src/expdp//c66//expdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_ELF_SRCEXPDP/expdp_d.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expdp//c66//expdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_ELF_SRCEXPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_ELF_SRCEXPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/expdp//c66//expdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXPDP_66_BE_ELF_SRCEXPDP=../../ >> src/expdp//c66//expdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXPDP_66_BE_ELF_SRCEXPDPC66=.././ >> src/expdp//c66//expdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXPDP_66_BE_ELF_SRCCOMMON=../../../common >> src/expdp//c66//expdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expdp_66_BE_ELF"
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/expdp/expdp.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/expdp/expdp_d.c
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/expdp//c66/expdp.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/expdp//c66/expdp_i.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common/drvdp.c
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common/drvdp.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common/driver.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common/driver.c
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common/common.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common/tables.c
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/common//c66/common.h
src/expdp//c66//expdp_66_BE_ELF/Release/expdp_66_BE_ELF.out: src/expdp//c66//expdp_66_BE_ELF/.project
	-@ echo Importing Project expdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expdp/c66/expdp_66_BE_ELF"
	-@ echo Building Project expdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project expdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/expdp//c66//expdp_66_BE_ELF"


#############################################################

# Rule to Build Project expsp_66_LE_COFF

#############################################################

.executables: src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out

.projects: src/expsp//c66//expsp_66_LE_COFF

src/expsp//c66//expsp_66_LE_COFF: src/expsp//c66//expsp_66_LE_COFF/.project

src/expsp//c66//expsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_COFF_SRCEXPSP/expsp_d.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expsp//c66//expsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_COFF_SRCEXPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_COFF_SRCEXPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/expsp//c66//expsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXPSP_66_LE_COFF_SRCEXPSP=../../ >> src/expsp//c66//expsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXPSP_66_LE_COFF_SRCEXPSPC66=.././ >> src/expsp//c66//expsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__EXPSP_66_LE_COFF_SRCCOMMON=../../../common >> src/expsp//c66//expsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expsp_66_LE_COFF"
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/expsp/expsp.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/expsp/expsp_d.c
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/expsp//c66/expsp.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/expsp//c66/expsp_i.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common/drvsp.c
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common/drvsp.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common/driver.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common/driver.c
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common/common.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common/tables.c
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/common//c66/common.h
src/expsp//c66//expsp_66_LE_COFF/Release/expsp_66_LE_COFF.out: src/expsp//c66//expsp_66_LE_COFF/.project
	-@ echo Importing Project expsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66/expsp_66_LE_COFF"
	-@ echo Building Project expsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project expsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/expsp//c66//expsp_66_LE_COFF"


#############################################################

# Rule to Build Project expsp_66_BE_COFF

#############################################################

.executables: src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out

.projects: src/expsp//c66//expsp_66_BE_COFF

src/expsp//c66//expsp_66_BE_COFF: src/expsp//c66//expsp_66_BE_COFF/.project

src/expsp//c66//expsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_COFF_SRCEXPSP/expsp_d.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expsp//c66//expsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_COFF_SRCEXPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_COFF_SRCEXPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/expsp//c66//expsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXPSP_66_BE_COFF_SRCEXPSP=../../ >> src/expsp//c66//expsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXPSP_66_BE_COFF_SRCEXPSPC66=.././ >> src/expsp//c66//expsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__EXPSP_66_BE_COFF_SRCCOMMON=../../../common >> src/expsp//c66//expsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expsp_66_BE_COFF"
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/expsp/expsp.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/expsp/expsp_d.c
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/expsp//c66/expsp.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/expsp//c66/expsp_i.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common/drvsp.c
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common/drvsp.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common/driver.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common/driver.c
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common/common.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common/tables.c
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/common//c66/common.h
src/expsp//c66//expsp_66_BE_COFF/Release/expsp_66_BE_COFF.out: src/expsp//c66//expsp_66_BE_COFF/.project
	-@ echo Importing Project expsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66/expsp_66_BE_COFF"
	-@ echo Building Project expsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project expsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/expsp//c66//expsp_66_BE_COFF"


#############################################################

# Rule to Build Project expsp_66_LE_ELF

#############################################################

.executables: src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out

.projects: src/expsp//c66//expsp_66_LE_ELF

src/expsp//c66//expsp_66_LE_ELF: src/expsp//c66//expsp_66_LE_ELF/.project

src/expsp//c66//expsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_ELF_SRCEXPSP/expsp_d.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expsp//c66//expsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_ELF_SRCEXPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_ELF_SRCEXPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/expsp//c66//expsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXPSP_66_LE_ELF_SRCEXPSP=../../ >> src/expsp//c66//expsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXPSP_66_LE_ELF_SRCEXPSPC66=.././ >> src/expsp//c66//expsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__EXPSP_66_LE_ELF_SRCCOMMON=../../../common >> src/expsp//c66//expsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expsp_66_LE_ELF"
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/expsp/expsp.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/expsp/expsp_d.c
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/expsp//c66/expsp.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/expsp//c66/expsp_i.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common/drvsp.c
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common/drvsp.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common/driver.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common/driver.c
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common/common.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common/tables.c
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/common//c66/common.h
src/expsp//c66//expsp_66_LE_ELF/Release/expsp_66_LE_ELF.out: src/expsp//c66//expsp_66_LE_ELF/.project
	-@ echo Importing Project expsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66/expsp_66_LE_ELF"
	-@ echo Building Project expsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project expsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/expsp//c66//expsp_66_LE_ELF"


#############################################################

# Rule to Build Project expsp_66_BE_ELF

#############################################################

.executables: src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out

.projects: src/expsp//c66//expsp_66_BE_ELF

src/expsp//c66//expsp_66_BE_ELF: src/expsp//c66//expsp_66_BE_ELF/.project

src/expsp//c66//expsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name expsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_ELF_SRCEXPSP/expsp_d.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/expsp//c66//expsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_ELF_SRCEXPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_ELF_SRCEXPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66" \
 -ccs.definePathVariable EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/expsp//c66//expsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXPSP_66_BE_ELF_SRCEXPSP=../../ >> src/expsp//c66//expsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXPSP_66_BE_ELF_SRCEXPSPC66=.././ >> src/expsp//c66//expsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__EXPSP_66_BE_ELF_SRCCOMMON=../../../common >> src/expsp//c66//expsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/expsp_66_BE_ELF"
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/expsp/expsp.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/expsp/expsp_d.c
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/expsp//c66/expsp.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/expsp//c66/expsp_i.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common/drvsp.c
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common/drvsp.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common/driver.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common/driver.c
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common/common.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common/tables.c
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/common//c66/common.h
src/expsp//c66//expsp_66_BE_ELF/Release/expsp_66_BE_ELF.out: src/expsp//c66//expsp_66_BE_ELF/.project
	-@ echo Importing Project expsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects expsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/expsp/c66/expsp_66_BE_ELF"
	-@ echo Building Project expsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/expsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects expsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project expsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/expsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/expsp//c66//expsp_66_BE_ELF"


#############################################################

# Rule to Build Project log10dp_66_LE_COFF

#############################################################

.executables: src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out

.projects: src/log10dp//c66//log10dp_66_LE_COFF

src/log10dp//c66//log10dp_66_LE_COFF: src/log10dp//c66//log10dp_66_LE_COFF/.project

src/log10dp//c66//log10dp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10dp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_COFF_SRCLOG10DP/log10dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10dp//c66//log10dp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_COFF_SRCLOG10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_COFF_SRCLOG10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log10dp//c66//log10dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG10DP_66_LE_COFF_SRCLOG10DP=../../ >> src/log10dp//c66//log10dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG10DP_66_LE_COFF_SRCLOG10DPC66=.././ >> src/log10dp//c66//log10dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG10DP_66_LE_COFF_SRCCOMMON=../../../common >> src/log10dp//c66//log10dp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_LE_COFF"
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/log10dp/log10dp.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/log10dp/log10dp_d.c
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/log10dp//c66/log10dp.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/log10dp//c66/log10dp_i.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common/drvdp.c
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common/drvdp.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common/driver.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common/driver.c
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common/common.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common/tables.c
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/common//c66/common.h
src/log10dp//c66//log10dp_66_LE_COFF/Release/log10dp_66_LE_COFF.out: src/log10dp//c66//log10dp_66_LE_COFF/.project
	-@ echo Importing Project log10dp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10dp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66/log10dp_66_LE_COFF"
	-@ echo Building Project log10dp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10dp_66_LE_COFF -ccs.configuration Release
	-@ echo Project log10dp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_LE_COFF"

clean::
	-$(RMDIR) "src/log10dp//c66//log10dp_66_LE_COFF"


#############################################################

# Rule to Build Project log10dp_66_BE_COFF

#############################################################

.executables: src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out

.projects: src/log10dp//c66//log10dp_66_BE_COFF

src/log10dp//c66//log10dp_66_BE_COFF: src/log10dp//c66//log10dp_66_BE_COFF/.project

src/log10dp//c66//log10dp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10dp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_COFF_SRCLOG10DP/log10dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10dp//c66//log10dp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_COFF_SRCLOG10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_COFF_SRCLOG10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log10dp//c66//log10dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG10DP_66_BE_COFF_SRCLOG10DP=../../ >> src/log10dp//c66//log10dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG10DP_66_BE_COFF_SRCLOG10DPC66=.././ >> src/log10dp//c66//log10dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG10DP_66_BE_COFF_SRCCOMMON=../../../common >> src/log10dp//c66//log10dp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_BE_COFF"
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/log10dp/log10dp.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/log10dp/log10dp_d.c
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/log10dp//c66/log10dp.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/log10dp//c66/log10dp_i.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common/drvdp.c
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common/drvdp.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common/driver.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common/driver.c
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common/common.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common/tables.c
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/common//c66/common.h
src/log10dp//c66//log10dp_66_BE_COFF/Release/log10dp_66_BE_COFF.out: src/log10dp//c66//log10dp_66_BE_COFF/.project
	-@ echo Importing Project log10dp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10dp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66/log10dp_66_BE_COFF"
	-@ echo Building Project log10dp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10dp_66_BE_COFF -ccs.configuration Release
	-@ echo Project log10dp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_BE_COFF"

clean::
	-$(RMDIR) "src/log10dp//c66//log10dp_66_BE_COFF"


#############################################################

# Rule to Build Project log10dp_66_LE_ELF

#############################################################

.executables: src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out

.projects: src/log10dp//c66//log10dp_66_LE_ELF

src/log10dp//c66//log10dp_66_LE_ELF: src/log10dp//c66//log10dp_66_LE_ELF/.project

src/log10dp//c66//log10dp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10dp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_ELF_SRCLOG10DP/log10dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10dp//c66//log10dp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_ELF_SRCLOG10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_ELF_SRCLOG10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log10dp//c66//log10dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG10DP_66_LE_ELF_SRCLOG10DP=../../ >> src/log10dp//c66//log10dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG10DP_66_LE_ELF_SRCLOG10DPC66=.././ >> src/log10dp//c66//log10dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG10DP_66_LE_ELF_SRCCOMMON=../../../common >> src/log10dp//c66//log10dp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_LE_ELF"
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/log10dp/log10dp.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/log10dp/log10dp_d.c
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/log10dp//c66/log10dp.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/log10dp//c66/log10dp_i.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common/drvdp.c
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common/drvdp.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common/driver.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common/driver.c
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common/common.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common/tables.c
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/common//c66/common.h
src/log10dp//c66//log10dp_66_LE_ELF/Release/log10dp_66_LE_ELF.out: src/log10dp//c66//log10dp_66_LE_ELF/.project
	-@ echo Importing Project log10dp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10dp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66/log10dp_66_LE_ELF"
	-@ echo Building Project log10dp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10dp_66_LE_ELF -ccs.configuration Release
	-@ echo Project log10dp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_LE_ELF"

clean::
	-$(RMDIR) "src/log10dp//c66//log10dp_66_LE_ELF"


#############################################################

# Rule to Build Project log10dp_66_BE_ELF

#############################################################

.executables: src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out

.projects: src/log10dp//c66//log10dp_66_BE_ELF

src/log10dp//c66//log10dp_66_BE_ELF: src/log10dp//c66//log10dp_66_BE_ELF/.project

src/log10dp//c66//log10dp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10dp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_ELF_SRCLOG10DP/log10dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10dp//c66//log10dp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_ELF_SRCLOG10DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_ELF_SRCLOG10DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log10dp//c66//log10dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG10DP_66_BE_ELF_SRCLOG10DP=../../ >> src/log10dp//c66//log10dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG10DP_66_BE_ELF_SRCLOG10DPC66=.././ >> src/log10dp//c66//log10dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG10DP_66_BE_ELF_SRCCOMMON=../../../common >> src/log10dp//c66//log10dp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_BE_ELF"
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/log10dp/log10dp.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/log10dp/log10dp_d.c
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/log10dp//c66/log10dp.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/log10dp//c66/log10dp_i.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common/drvdp.c
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common/drvdp.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common/driver.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common/driver.c
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common/common.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common/tables.c
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/common//c66/common.h
src/log10dp//c66//log10dp_66_BE_ELF/Release/log10dp_66_BE_ELF.out: src/log10dp//c66//log10dp_66_BE_ELF/.project
	-@ echo Importing Project log10dp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10dp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10dp/c66/log10dp_66_BE_ELF"
	-@ echo Building Project log10dp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10dp_66_BE_ELF -ccs.configuration Release
	-@ echo Project log10dp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10dp_66_BE_ELF"

clean::
	-$(RMDIR) "src/log10dp//c66//log10dp_66_BE_ELF"


#############################################################

# Rule to Build Project log10sp_66_LE_COFF

#############################################################

.executables: src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out

.projects: src/log10sp//c66//log10sp_66_LE_COFF

src/log10sp//c66//log10sp_66_LE_COFF: src/log10sp//c66//log10sp_66_LE_COFF/.project

src/log10sp//c66//log10sp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10sp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_COFF_SRCLOG10SP/log10sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10sp//c66//log10sp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_COFF_SRCLOG10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_COFF_SRCLOG10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log10sp//c66//log10sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG10SP_66_LE_COFF_SRCLOG10SP=../../ >> src/log10sp//c66//log10sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG10SP_66_LE_COFF_SRCLOG10SPC66=.././ >> src/log10sp//c66//log10sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG10SP_66_LE_COFF_SRCCOMMON=../../../common >> src/log10sp//c66//log10sp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_LE_COFF"
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/log10sp/log10sp.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/log10sp/log10sp_d.c
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/log10sp//c66/log10sp.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/log10sp//c66/log10sp_i.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common/drvsp.c
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common/drvsp.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common/driver.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common/driver.c
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common/common.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common/tables.c
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/common//c66/common.h
src/log10sp//c66//log10sp_66_LE_COFF/Release/log10sp_66_LE_COFF.out: src/log10sp//c66//log10sp_66_LE_COFF/.project
	-@ echo Importing Project log10sp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10sp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66/log10sp_66_LE_COFF"
	-@ echo Building Project log10sp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10sp_66_LE_COFF -ccs.configuration Release
	-@ echo Project log10sp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_LE_COFF"

clean::
	-$(RMDIR) "src/log10sp//c66//log10sp_66_LE_COFF"


#############################################################

# Rule to Build Project log10sp_66_BE_COFF

#############################################################

.executables: src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out

.projects: src/log10sp//c66//log10sp_66_BE_COFF

src/log10sp//c66//log10sp_66_BE_COFF: src/log10sp//c66//log10sp_66_BE_COFF/.project

src/log10sp//c66//log10sp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10sp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_COFF_SRCLOG10SP/log10sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10sp//c66//log10sp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_COFF_SRCLOG10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_COFF_SRCLOG10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log10sp//c66//log10sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG10SP_66_BE_COFF_SRCLOG10SP=../../ >> src/log10sp//c66//log10sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG10SP_66_BE_COFF_SRCLOG10SPC66=.././ >> src/log10sp//c66//log10sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG10SP_66_BE_COFF_SRCCOMMON=../../../common >> src/log10sp//c66//log10sp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_BE_COFF"
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/log10sp/log10sp.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/log10sp/log10sp_d.c
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/log10sp//c66/log10sp.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/log10sp//c66/log10sp_i.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common/drvsp.c
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common/drvsp.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common/driver.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common/driver.c
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common/common.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common/tables.c
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/common//c66/common.h
src/log10sp//c66//log10sp_66_BE_COFF/Release/log10sp_66_BE_COFF.out: src/log10sp//c66//log10sp_66_BE_COFF/.project
	-@ echo Importing Project log10sp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10sp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66/log10sp_66_BE_COFF"
	-@ echo Building Project log10sp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10sp_66_BE_COFF -ccs.configuration Release
	-@ echo Project log10sp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_BE_COFF"

clean::
	-$(RMDIR) "src/log10sp//c66//log10sp_66_BE_COFF"


#############################################################

# Rule to Build Project log10sp_66_LE_ELF

#############################################################

.executables: src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out

.projects: src/log10sp//c66//log10sp_66_LE_ELF

src/log10sp//c66//log10sp_66_LE_ELF: src/log10sp//c66//log10sp_66_LE_ELF/.project

src/log10sp//c66//log10sp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10sp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_ELF_SRCLOG10SP/log10sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10sp//c66//log10sp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_ELF_SRCLOG10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_ELF_SRCLOG10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log10sp//c66//log10sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG10SP_66_LE_ELF_SRCLOG10SP=../../ >> src/log10sp//c66//log10sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG10SP_66_LE_ELF_SRCLOG10SPC66=.././ >> src/log10sp//c66//log10sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG10SP_66_LE_ELF_SRCCOMMON=../../../common >> src/log10sp//c66//log10sp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_LE_ELF"
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/log10sp/log10sp.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/log10sp/log10sp_d.c
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/log10sp//c66/log10sp.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/log10sp//c66/log10sp_i.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common/drvsp.c
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common/drvsp.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common/driver.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common/driver.c
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common/common.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common/tables.c
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/common//c66/common.h
src/log10sp//c66//log10sp_66_LE_ELF/Release/log10sp_66_LE_ELF.out: src/log10sp//c66//log10sp_66_LE_ELF/.project
	-@ echo Importing Project log10sp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10sp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66/log10sp_66_LE_ELF"
	-@ echo Building Project log10sp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10sp_66_LE_ELF -ccs.configuration Release
	-@ echo Project log10sp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_LE_ELF"

clean::
	-$(RMDIR) "src/log10sp//c66//log10sp_66_LE_ELF"


#############################################################

# Rule to Build Project log10sp_66_BE_ELF

#############################################################

.executables: src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out

.projects: src/log10sp//c66//log10sp_66_BE_ELF

src/log10sp//c66//log10sp_66_BE_ELF: src/log10sp//c66//log10sp_66_BE_ELF/.project

src/log10sp//c66//log10sp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log10sp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_ELF_SRCLOG10SP/log10sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log10sp//c66//log10sp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_ELF_SRCLOG10SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_ELF_SRCLOG10SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log10sp//c66//log10sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG10SP_66_BE_ELF_SRCLOG10SP=../../ >> src/log10sp//c66//log10sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG10SP_66_BE_ELF_SRCLOG10SPC66=.././ >> src/log10sp//c66//log10sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG10SP_66_BE_ELF_SRCCOMMON=../../../common >> src/log10sp//c66//log10sp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_BE_ELF"
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/log10sp/log10sp.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/log10sp/log10sp_d.c
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/log10sp//c66/log10sp.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/log10sp//c66/log10sp_i.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common/drvsp.c
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common/drvsp.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common/driver.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common/driver.c
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common/common.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common/tables.c
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/common//c66/common.h
src/log10sp//c66//log10sp_66_BE_ELF/Release/log10sp_66_BE_ELF.out: src/log10sp//c66//log10sp_66_BE_ELF/.project
	-@ echo Importing Project log10sp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log10sp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log10sp/c66/log10sp_66_BE_ELF"
	-@ echo Building Project log10sp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log10sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log10sp_66_BE_ELF -ccs.configuration Release
	-@ echo Project log10sp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log10sp_66_BE_ELF"

clean::
	-$(RMDIR) "src/log10sp//c66//log10sp_66_BE_ELF"


#############################################################

# Rule to Build Project log2dp_66_LE_COFF

#############################################################

.executables: src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out

.projects: src/log2dp//c66//log2dp_66_LE_COFF

src/log2dp//c66//log2dp_66_LE_COFF: src/log2dp//c66//log2dp_66_LE_COFF/.project

src/log2dp//c66//log2dp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2dp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_COFF_SRCLOG2DP/log2dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2dp//c66//log2dp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_COFF_SRCLOG2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_COFF_SRCLOG2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log2dp//c66//log2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG2DP_66_LE_COFF_SRCLOG2DP=../../ >> src/log2dp//c66//log2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG2DP_66_LE_COFF_SRCLOG2DPC66=.././ >> src/log2dp//c66//log2dp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG2DP_66_LE_COFF_SRCCOMMON=../../../common >> src/log2dp//c66//log2dp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_LE_COFF"
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/log2dp/log2dp.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/log2dp/log2dp_d.c
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/log2dp//c66/log2dp.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/log2dp//c66/log2dp_i.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common/drvdp.c
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common/drvdp.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common/driver.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common/driver.c
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common/common.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common/tables.c
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/common//c66/common.h
src/log2dp//c66//log2dp_66_LE_COFF/Release/log2dp_66_LE_COFF.out: src/log2dp//c66//log2dp_66_LE_COFF/.project
	-@ echo Importing Project log2dp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2dp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66/log2dp_66_LE_COFF"
	-@ echo Building Project log2dp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2dp_66_LE_COFF -ccs.configuration Release
	-@ echo Project log2dp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_LE_COFF"

clean::
	-$(RMDIR) "src/log2dp//c66//log2dp_66_LE_COFF"


#############################################################

# Rule to Build Project log2dp_66_BE_COFF

#############################################################

.executables: src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out

.projects: src/log2dp//c66//log2dp_66_BE_COFF

src/log2dp//c66//log2dp_66_BE_COFF: src/log2dp//c66//log2dp_66_BE_COFF/.project

src/log2dp//c66//log2dp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2dp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_COFF_SRCLOG2DP/log2dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2dp//c66//log2dp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_COFF_SRCLOG2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_COFF_SRCLOG2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log2dp//c66//log2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG2DP_66_BE_COFF_SRCLOG2DP=../../ >> src/log2dp//c66//log2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG2DP_66_BE_COFF_SRCLOG2DPC66=.././ >> src/log2dp//c66//log2dp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG2DP_66_BE_COFF_SRCCOMMON=../../../common >> src/log2dp//c66//log2dp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_BE_COFF"
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/log2dp/log2dp.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/log2dp/log2dp_d.c
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/log2dp//c66/log2dp.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/log2dp//c66/log2dp_i.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common/drvdp.c
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common/drvdp.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common/driver.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common/driver.c
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common/common.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common/tables.c
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/common//c66/common.h
src/log2dp//c66//log2dp_66_BE_COFF/Release/log2dp_66_BE_COFF.out: src/log2dp//c66//log2dp_66_BE_COFF/.project
	-@ echo Importing Project log2dp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2dp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66/log2dp_66_BE_COFF"
	-@ echo Building Project log2dp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2dp_66_BE_COFF -ccs.configuration Release
	-@ echo Project log2dp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_BE_COFF"

clean::
	-$(RMDIR) "src/log2dp//c66//log2dp_66_BE_COFF"


#############################################################

# Rule to Build Project log2dp_66_LE_ELF

#############################################################

.executables: src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out

.projects: src/log2dp//c66//log2dp_66_LE_ELF

src/log2dp//c66//log2dp_66_LE_ELF: src/log2dp//c66//log2dp_66_LE_ELF/.project

src/log2dp//c66//log2dp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2dp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_ELF_SRCLOG2DP/log2dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2dp//c66//log2dp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_ELF_SRCLOG2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_ELF_SRCLOG2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log2dp//c66//log2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG2DP_66_LE_ELF_SRCLOG2DP=../../ >> src/log2dp//c66//log2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG2DP_66_LE_ELF_SRCLOG2DPC66=.././ >> src/log2dp//c66//log2dp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG2DP_66_LE_ELF_SRCCOMMON=../../../common >> src/log2dp//c66//log2dp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_LE_ELF"
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/log2dp/log2dp.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/log2dp/log2dp_d.c
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/log2dp//c66/log2dp.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/log2dp//c66/log2dp_i.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common/drvdp.c
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common/drvdp.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common/driver.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common/driver.c
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common/common.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common/tables.c
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/common//c66/common.h
src/log2dp//c66//log2dp_66_LE_ELF/Release/log2dp_66_LE_ELF.out: src/log2dp//c66//log2dp_66_LE_ELF/.project
	-@ echo Importing Project log2dp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2dp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66/log2dp_66_LE_ELF"
	-@ echo Building Project log2dp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2dp_66_LE_ELF -ccs.configuration Release
	-@ echo Project log2dp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_LE_ELF"

clean::
	-$(RMDIR) "src/log2dp//c66//log2dp_66_LE_ELF"


#############################################################

# Rule to Build Project log2dp_66_BE_ELF

#############################################################

.executables: src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out

.projects: src/log2dp//c66//log2dp_66_BE_ELF

src/log2dp//c66//log2dp_66_BE_ELF: src/log2dp//c66//log2dp_66_BE_ELF/.project

src/log2dp//c66//log2dp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2dp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_ELF_SRCLOG2DP/log2dp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2dp//c66//log2dp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_ELF_SRCLOG2DP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_ELF_SRCLOG2DPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log2dp//c66//log2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG2DP_66_BE_ELF_SRCLOG2DP=../../ >> src/log2dp//c66//log2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG2DP_66_BE_ELF_SRCLOG2DPC66=.././ >> src/log2dp//c66//log2dp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG2DP_66_BE_ELF_SRCCOMMON=../../../common >> src/log2dp//c66//log2dp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_BE_ELF"
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/log2dp/log2dp.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/log2dp/log2dp_d.c
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/log2dp//c66/log2dp.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/log2dp//c66/log2dp_i.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common/drvdp.c
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common/drvdp.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common/driver.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common/driver.c
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common/common.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common/tables.c
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/common//c66/common.h
src/log2dp//c66//log2dp_66_BE_ELF/Release/log2dp_66_BE_ELF.out: src/log2dp//c66//log2dp_66_BE_ELF/.project
	-@ echo Importing Project log2dp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2dp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2dp/c66/log2dp_66_BE_ELF"
	-@ echo Building Project log2dp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2dp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2dp_66_BE_ELF -ccs.configuration Release
	-@ echo Project log2dp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2dp_66_BE_ELF"

clean::
	-$(RMDIR) "src/log2dp//c66//log2dp_66_BE_ELF"


#############################################################

# Rule to Build Project log2sp_66_LE_COFF

#############################################################

.executables: src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out

.projects: src/log2sp//c66//log2sp_66_LE_COFF

src/log2sp//c66//log2sp_66_LE_COFF: src/log2sp//c66//log2sp_66_LE_COFF/.project

src/log2sp//c66//log2sp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2sp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_COFF_SRCLOG2SP/log2sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2sp//c66//log2sp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_COFF_SRCLOG2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_COFF_SRCLOG2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log2sp//c66//log2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG2SP_66_LE_COFF_SRCLOG2SP=../../ >> src/log2sp//c66//log2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG2SP_66_LE_COFF_SRCLOG2SPC66=.././ >> src/log2sp//c66//log2sp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOG2SP_66_LE_COFF_SRCCOMMON=../../../common >> src/log2sp//c66//log2sp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_LE_COFF"
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/log2sp/log2sp.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/log2sp/log2sp_d.c
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/log2sp//c66/log2sp.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/log2sp//c66/log2sp_i.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common/drvsp.c
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common/drvsp.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common/driver.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common/driver.c
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common/common.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common/tables.c
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/common//c66/common.h
src/log2sp//c66//log2sp_66_LE_COFF/Release/log2sp_66_LE_COFF.out: src/log2sp//c66//log2sp_66_LE_COFF/.project
	-@ echo Importing Project log2sp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2sp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66/log2sp_66_LE_COFF"
	-@ echo Building Project log2sp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2sp_66_LE_COFF -ccs.configuration Release
	-@ echo Project log2sp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_LE_COFF"

clean::
	-$(RMDIR) "src/log2sp//c66//log2sp_66_LE_COFF"


#############################################################

# Rule to Build Project log2sp_66_BE_COFF

#############################################################

.executables: src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out

.projects: src/log2sp//c66//log2sp_66_BE_COFF

src/log2sp//c66//log2sp_66_BE_COFF: src/log2sp//c66//log2sp_66_BE_COFF/.project

src/log2sp//c66//log2sp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2sp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_COFF_SRCLOG2SP/log2sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2sp//c66//log2sp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_COFF_SRCLOG2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_COFF_SRCLOG2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/log2sp//c66//log2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG2SP_66_BE_COFF_SRCLOG2SP=../../ >> src/log2sp//c66//log2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG2SP_66_BE_COFF_SRCLOG2SPC66=.././ >> src/log2sp//c66//log2sp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOG2SP_66_BE_COFF_SRCCOMMON=../../../common >> src/log2sp//c66//log2sp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_BE_COFF"
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/log2sp/log2sp.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/log2sp/log2sp_d.c
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/log2sp//c66/log2sp.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/log2sp//c66/log2sp_i.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common/drvsp.c
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common/drvsp.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common/driver.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common/driver.c
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common/common.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common/tables.c
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/common//c66/common.h
src/log2sp//c66//log2sp_66_BE_COFF/Release/log2sp_66_BE_COFF.out: src/log2sp//c66//log2sp_66_BE_COFF/.project
	-@ echo Importing Project log2sp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2sp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66/log2sp_66_BE_COFF"
	-@ echo Building Project log2sp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2sp_66_BE_COFF -ccs.configuration Release
	-@ echo Project log2sp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_BE_COFF"

clean::
	-$(RMDIR) "src/log2sp//c66//log2sp_66_BE_COFF"


#############################################################

# Rule to Build Project log2sp_66_LE_ELF

#############################################################

.executables: src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out

.projects: src/log2sp//c66//log2sp_66_LE_ELF

src/log2sp//c66//log2sp_66_LE_ELF: src/log2sp//c66//log2sp_66_LE_ELF/.project

src/log2sp//c66//log2sp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2sp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_ELF_SRCLOG2SP/log2sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2sp//c66//log2sp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_ELF_SRCLOG2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_ELF_SRCLOG2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log2sp//c66//log2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG2SP_66_LE_ELF_SRCLOG2SP=../../ >> src/log2sp//c66//log2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG2SP_66_LE_ELF_SRCLOG2SPC66=.././ >> src/log2sp//c66//log2sp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOG2SP_66_LE_ELF_SRCCOMMON=../../../common >> src/log2sp//c66//log2sp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_LE_ELF"
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/log2sp/log2sp.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/log2sp/log2sp_d.c
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/log2sp//c66/log2sp.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/log2sp//c66/log2sp_i.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common/drvsp.c
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common/drvsp.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common/driver.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common/driver.c
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common/common.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common/tables.c
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/common//c66/common.h
src/log2sp//c66//log2sp_66_LE_ELF/Release/log2sp_66_LE_ELF.out: src/log2sp//c66//log2sp_66_LE_ELF/.project
	-@ echo Importing Project log2sp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2sp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66/log2sp_66_LE_ELF"
	-@ echo Building Project log2sp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2sp_66_LE_ELF -ccs.configuration Release
	-@ echo Project log2sp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_LE_ELF"

clean::
	-$(RMDIR) "src/log2sp//c66//log2sp_66_LE_ELF"


#############################################################

# Rule to Build Project log2sp_66_BE_ELF

#############################################################

.executables: src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out

.projects: src/log2sp//c66//log2sp_66_BE_ELF

src/log2sp//c66//log2sp_66_BE_ELF: src/log2sp//c66//log2sp_66_BE_ELF/.project

src/log2sp//c66//log2sp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name log2sp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_ELF_SRCLOG2SP/log2sp_d.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/log2sp//c66//log2sp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_ELF_SRCLOG2SP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_ELF_SRCLOG2SPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/log2sp//c66//log2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG2SP_66_BE_ELF_SRCLOG2SP=../../ >> src/log2sp//c66//log2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG2SP_66_BE_ELF_SRCLOG2SPC66=.././ >> src/log2sp//c66//log2sp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOG2SP_66_BE_ELF_SRCCOMMON=../../../common >> src/log2sp//c66//log2sp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_BE_ELF"
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/log2sp/log2sp.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/log2sp/log2sp_d.c
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/log2sp//c66/log2sp.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/log2sp//c66/log2sp_i.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common/drvsp.c
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common/drvsp.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common/driver.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common/driver.c
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common/common.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common/tables.c
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/common//c66/common.h
src/log2sp//c66//log2sp_66_BE_ELF/Release/log2sp_66_BE_ELF.out: src/log2sp//c66//log2sp_66_BE_ELF/.project
	-@ echo Importing Project log2sp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects log2sp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/log2sp/c66/log2sp_66_BE_ELF"
	-@ echo Building Project log2sp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/log2sp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects log2sp_66_BE_ELF -ccs.configuration Release
	-@ echo Project log2sp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/log2sp_66_BE_ELF"

clean::
	-$(RMDIR) "src/log2sp//c66//log2sp_66_BE_ELF"


#############################################################

# Rule to Build Project logdp_66_LE_COFF

#############################################################

.executables: src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out

.projects: src/logdp//c66//logdp_66_LE_COFF

src/logdp//c66//logdp_66_LE_COFF: src/logdp//c66//logdp_66_LE_COFF/.project

src/logdp//c66//logdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_COFF_SRCLOGDP/logdp_d.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logdp//c66//logdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_COFF_SRCLOGDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_COFF_SRCLOGDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/logdp//c66//logdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOGDP_66_LE_COFF_SRCLOGDP=../../ >> src/logdp//c66//logdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOGDP_66_LE_COFF_SRCLOGDPC66=.././ >> src/logdp//c66//logdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOGDP_66_LE_COFF_SRCCOMMON=../../../common >> src/logdp//c66//logdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logdp_66_LE_COFF"
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/logdp/logdp.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/logdp/logdp_d.c
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/logdp//c66/logdp.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/logdp//c66/logdp_i.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common/drvdp.c
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common/drvdp.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common/driver.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common/driver.c
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common/common.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common/tables.c
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/common//c66/common.h
src/logdp//c66//logdp_66_LE_COFF/Release/logdp_66_LE_COFF.out: src/logdp//c66//logdp_66_LE_COFF/.project
	-@ echo Importing Project logdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66/logdp_66_LE_COFF"
	-@ echo Building Project logdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project logdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/logdp//c66//logdp_66_LE_COFF"


#############################################################

# Rule to Build Project logdp_66_BE_COFF

#############################################################

.executables: src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out

.projects: src/logdp//c66//logdp_66_BE_COFF

src/logdp//c66//logdp_66_BE_COFF: src/logdp//c66//logdp_66_BE_COFF/.project

src/logdp//c66//logdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_COFF_SRCLOGDP/logdp_d.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logdp//c66//logdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_COFF_SRCLOGDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_COFF_SRCLOGDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/logdp//c66//logdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOGDP_66_BE_COFF_SRCLOGDP=../../ >> src/logdp//c66//logdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOGDP_66_BE_COFF_SRCLOGDPC66=.././ >> src/logdp//c66//logdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOGDP_66_BE_COFF_SRCCOMMON=../../../common >> src/logdp//c66//logdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logdp_66_BE_COFF"
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/logdp/logdp.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/logdp/logdp_d.c
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/logdp//c66/logdp.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/logdp//c66/logdp_i.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common/drvdp.c
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common/drvdp.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common/driver.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common/driver.c
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common/common.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common/tables.c
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/common//c66/common.h
src/logdp//c66//logdp_66_BE_COFF/Release/logdp_66_BE_COFF.out: src/logdp//c66//logdp_66_BE_COFF/.project
	-@ echo Importing Project logdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66/logdp_66_BE_COFF"
	-@ echo Building Project logdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project logdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/logdp//c66//logdp_66_BE_COFF"


#############################################################

# Rule to Build Project logdp_66_LE_ELF

#############################################################

.executables: src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out

.projects: src/logdp//c66//logdp_66_LE_ELF

src/logdp//c66//logdp_66_LE_ELF: src/logdp//c66//logdp_66_LE_ELF/.project

src/logdp//c66//logdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_ELF_SRCLOGDP/logdp_d.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logdp//c66//logdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_ELF_SRCLOGDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_ELF_SRCLOGDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/logdp//c66//logdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOGDP_66_LE_ELF_SRCLOGDP=../../ >> src/logdp//c66//logdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOGDP_66_LE_ELF_SRCLOGDPC66=.././ >> src/logdp//c66//logdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOGDP_66_LE_ELF_SRCCOMMON=../../../common >> src/logdp//c66//logdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logdp_66_LE_ELF"
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/logdp/logdp.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/logdp/logdp_d.c
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/logdp//c66/logdp.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/logdp//c66/logdp_i.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common/drvdp.c
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common/drvdp.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common/driver.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common/driver.c
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common/common.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common/tables.c
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/common//c66/common.h
src/logdp//c66//logdp_66_LE_ELF/Release/logdp_66_LE_ELF.out: src/logdp//c66//logdp_66_LE_ELF/.project
	-@ echo Importing Project logdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66/logdp_66_LE_ELF"
	-@ echo Building Project logdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project logdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/logdp//c66//logdp_66_LE_ELF"


#############################################################

# Rule to Build Project logdp_66_BE_ELF

#############################################################

.executables: src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out

.projects: src/logdp//c66//logdp_66_BE_ELF

src/logdp//c66//logdp_66_BE_ELF: src/logdp//c66//logdp_66_BE_ELF/.project

src/logdp//c66//logdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_ELF_SRCLOGDP/logdp_d.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logdp//c66//logdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_ELF_SRCLOGDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_ELF_SRCLOGDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/logdp//c66//logdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOGDP_66_BE_ELF_SRCLOGDP=../../ >> src/logdp//c66//logdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOGDP_66_BE_ELF_SRCLOGDPC66=.././ >> src/logdp//c66//logdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOGDP_66_BE_ELF_SRCCOMMON=../../../common >> src/logdp//c66//logdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logdp_66_BE_ELF"
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/logdp/logdp.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/logdp/logdp_d.c
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/logdp//c66/logdp.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/logdp//c66/logdp_i.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common/drvdp.c
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common/drvdp.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common/driver.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common/driver.c
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common/common.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common/tables.c
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/common//c66/common.h
src/logdp//c66//logdp_66_BE_ELF/Release/logdp_66_BE_ELF.out: src/logdp//c66//logdp_66_BE_ELF/.project
	-@ echo Importing Project logdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logdp/c66/logdp_66_BE_ELF"
	-@ echo Building Project logdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project logdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/logdp//c66//logdp_66_BE_ELF"


#############################################################

# Rule to Build Project logsp_66_LE_COFF

#############################################################

.executables: src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out

.projects: src/logsp//c66//logsp_66_LE_COFF

src/logsp//c66//logsp_66_LE_COFF: src/logsp//c66//logsp_66_LE_COFF/.project

src/logsp//c66//logsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_COFF_SRCLOGSP/logsp_d.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logsp//c66//logsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_COFF_SRCLOGSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_COFF_SRCLOGSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/logsp//c66//logsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOGSP_66_LE_COFF_SRCLOGSP=../../ >> src/logsp//c66//logsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOGSP_66_LE_COFF_SRCLOGSPC66=.././ >> src/logsp//c66//logsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__LOGSP_66_LE_COFF_SRCCOMMON=../../../common >> src/logsp//c66//logsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logsp_66_LE_COFF"
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/logsp/logsp.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/logsp/logsp_d.c
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/logsp//c66/logsp.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/logsp//c66/logsp_i.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common/drvsp.c
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common/drvsp.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common/driver.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common/driver.c
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common/common.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common/tables.c
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/common//c66/common.h
src/logsp//c66//logsp_66_LE_COFF/Release/logsp_66_LE_COFF.out: src/logsp//c66//logsp_66_LE_COFF/.project
	-@ echo Importing Project logsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66/logsp_66_LE_COFF"
	-@ echo Building Project logsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project logsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/logsp//c66//logsp_66_LE_COFF"


#############################################################

# Rule to Build Project logsp_66_BE_COFF

#############################################################

.executables: src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out

.projects: src/logsp//c66//logsp_66_BE_COFF

src/logsp//c66//logsp_66_BE_COFF: src/logsp//c66//logsp_66_BE_COFF/.project

src/logsp//c66//logsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_COFF_SRCLOGSP/logsp_d.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logsp//c66//logsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_COFF_SRCLOGSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_COFF_SRCLOGSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/logsp//c66//logsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOGSP_66_BE_COFF_SRCLOGSP=../../ >> src/logsp//c66//logsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOGSP_66_BE_COFF_SRCLOGSPC66=.././ >> src/logsp//c66//logsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__LOGSP_66_BE_COFF_SRCCOMMON=../../../common >> src/logsp//c66//logsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logsp_66_BE_COFF"
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/logsp/logsp.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/logsp/logsp_d.c
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/logsp//c66/logsp.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/logsp//c66/logsp_i.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common/drvsp.c
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common/drvsp.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common/driver.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common/driver.c
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common/common.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common/tables.c
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/common//c66/common.h
src/logsp//c66//logsp_66_BE_COFF/Release/logsp_66_BE_COFF.out: src/logsp//c66//logsp_66_BE_COFF/.project
	-@ echo Importing Project logsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66/logsp_66_BE_COFF"
	-@ echo Building Project logsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project logsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/logsp//c66//logsp_66_BE_COFF"


#############################################################

# Rule to Build Project logsp_66_LE_ELF

#############################################################

.executables: src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out

.projects: src/logsp//c66//logsp_66_LE_ELF

src/logsp//c66//logsp_66_LE_ELF: src/logsp//c66//logsp_66_LE_ELF/.project

src/logsp//c66//logsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_ELF_SRCLOGSP/logsp_d.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logsp//c66//logsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_ELF_SRCLOGSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_ELF_SRCLOGSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/logsp//c66//logsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOGSP_66_LE_ELF_SRCLOGSP=../../ >> src/logsp//c66//logsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOGSP_66_LE_ELF_SRCLOGSPC66=.././ >> src/logsp//c66//logsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__LOGSP_66_LE_ELF_SRCCOMMON=../../../common >> src/logsp//c66//logsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logsp_66_LE_ELF"
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/logsp/logsp.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/logsp/logsp_d.c
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/logsp//c66/logsp.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/logsp//c66/logsp_i.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common/drvsp.c
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common/drvsp.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common/driver.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common/driver.c
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common/common.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common/tables.c
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/common//c66/common.h
src/logsp//c66//logsp_66_LE_ELF/Release/logsp_66_LE_ELF.out: src/logsp//c66//logsp_66_LE_ELF/.project
	-@ echo Importing Project logsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66/logsp_66_LE_ELF"
	-@ echo Building Project logsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project logsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/logsp//c66//logsp_66_LE_ELF"


#############################################################

# Rule to Build Project logsp_66_BE_ELF

#############################################################

.executables: src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out

.projects: src/logsp//c66//logsp_66_BE_ELF

src/logsp//c66//logsp_66_BE_ELF: src/logsp//c66//logsp_66_BE_ELF/.project

src/logsp//c66//logsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name logsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_ELF_SRCLOGSP/logsp_d.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/logsp//c66//logsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_ELF_SRCLOGSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_ELF_SRCLOGSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66" \
 -ccs.definePathVariable EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/logsp//c66//logsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOGSP_66_BE_ELF_SRCLOGSP=../../ >> src/logsp//c66//logsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOGSP_66_BE_ELF_SRCLOGSPC66=.././ >> src/logsp//c66//logsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__LOGSP_66_BE_ELF_SRCCOMMON=../../../common >> src/logsp//c66//logsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/logsp_66_BE_ELF"
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/logsp/logsp.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/logsp/logsp_d.c
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/logsp//c66/logsp.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/logsp//c66/logsp_i.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common/drvsp.c
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common/drvsp.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common/driver.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common/driver.c
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common/common.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common/tables.c
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/common//c66/common.h
src/logsp//c66//logsp_66_BE_ELF/Release/logsp_66_BE_ELF.out: src/logsp//c66//logsp_66_BE_ELF/.project
	-@ echo Importing Project logsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects logsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/logsp/c66/logsp_66_BE_ELF"
	-@ echo Building Project logsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/logsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects logsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project logsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/logsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/logsp//c66//logsp_66_BE_ELF"


#############################################################

# Rule to Build Project powdp_66_LE_COFF

#############################################################

.executables: src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out

.projects: src/powdp//c66//powdp_66_LE_COFF

src/powdp//c66//powdp_66_LE_COFF: src/powdp//c66//powdp_66_LE_COFF/.project

src/powdp//c66//powdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_COFF_SRCPOWDP/powdp_d.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powdp//c66//powdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_COFF_SRCPOWDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_COFF_SRCPOWDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/powdp//c66//powdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__POWDP_66_LE_COFF_SRCPOWDP=../../ >> src/powdp//c66//powdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__POWDP_66_LE_COFF_SRCPOWDPC66=.././ >> src/powdp//c66//powdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__POWDP_66_LE_COFF_SRCCOMMON=../../../common >> src/powdp//c66//powdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powdp_66_LE_COFF"
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/powdp/powdp.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/powdp/powdp_d.c
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/powdp//c66/powdp.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/powdp//c66/powdp_i.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common/drvdp.c
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common/drvdp.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common/driver.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common/driver.c
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common/common.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common/tables.c
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/common//c66/common.h
src/powdp//c66//powdp_66_LE_COFF/Release/powdp_66_LE_COFF.out: src/powdp//c66//powdp_66_LE_COFF/.project
	-@ echo Importing Project powdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66/powdp_66_LE_COFF"
	-@ echo Building Project powdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project powdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/powdp//c66//powdp_66_LE_COFF"


#############################################################

# Rule to Build Project powdp_66_BE_COFF

#############################################################

.executables: src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out

.projects: src/powdp//c66//powdp_66_BE_COFF

src/powdp//c66//powdp_66_BE_COFF: src/powdp//c66//powdp_66_BE_COFF/.project

src/powdp//c66//powdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_COFF_SRCPOWDP/powdp_d.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powdp//c66//powdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_COFF_SRCPOWDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_COFF_SRCPOWDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/powdp//c66//powdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__POWDP_66_BE_COFF_SRCPOWDP=../../ >> src/powdp//c66//powdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__POWDP_66_BE_COFF_SRCPOWDPC66=.././ >> src/powdp//c66//powdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__POWDP_66_BE_COFF_SRCCOMMON=../../../common >> src/powdp//c66//powdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powdp_66_BE_COFF"
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/powdp/powdp.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/powdp/powdp_d.c
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/powdp//c66/powdp.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/powdp//c66/powdp_i.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common/drvdp.c
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common/drvdp.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common/driver.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common/driver.c
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common/common.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common/tables.c
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/common//c66/common.h
src/powdp//c66//powdp_66_BE_COFF/Release/powdp_66_BE_COFF.out: src/powdp//c66//powdp_66_BE_COFF/.project
	-@ echo Importing Project powdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66/powdp_66_BE_COFF"
	-@ echo Building Project powdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project powdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/powdp//c66//powdp_66_BE_COFF"


#############################################################

# Rule to Build Project powdp_66_LE_ELF

#############################################################

.executables: src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out

.projects: src/powdp//c66//powdp_66_LE_ELF

src/powdp//c66//powdp_66_LE_ELF: src/powdp//c66//powdp_66_LE_ELF/.project

src/powdp//c66//powdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_ELF_SRCPOWDP/powdp_d.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powdp//c66//powdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_ELF_SRCPOWDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_ELF_SRCPOWDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/powdp//c66//powdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__POWDP_66_LE_ELF_SRCPOWDP=../../ >> src/powdp//c66//powdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__POWDP_66_LE_ELF_SRCPOWDPC66=.././ >> src/powdp//c66//powdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__POWDP_66_LE_ELF_SRCCOMMON=../../../common >> src/powdp//c66//powdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powdp_66_LE_ELF"
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/powdp/powdp.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/powdp/powdp_d.c
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/powdp//c66/powdp.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/powdp//c66/powdp_i.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common/drvdp.c
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common/drvdp.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common/driver.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common/driver.c
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common/common.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common/tables.c
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/common//c66/common.h
src/powdp//c66//powdp_66_LE_ELF/Release/powdp_66_LE_ELF.out: src/powdp//c66//powdp_66_LE_ELF/.project
	-@ echo Importing Project powdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66/powdp_66_LE_ELF"
	-@ echo Building Project powdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project powdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/powdp//c66//powdp_66_LE_ELF"


#############################################################

# Rule to Build Project powdp_66_BE_ELF

#############################################################

.executables: src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out

.projects: src/powdp//c66//powdp_66_BE_ELF

src/powdp//c66//powdp_66_BE_ELF: src/powdp//c66//powdp_66_BE_ELF/.project

src/powdp//c66//powdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_ELF_SRCPOWDP/powdp_d.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powdp//c66//powdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_ELF_SRCPOWDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_ELF_SRCPOWDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/powdp//c66//powdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__POWDP_66_BE_ELF_SRCPOWDP=../../ >> src/powdp//c66//powdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__POWDP_66_BE_ELF_SRCPOWDPC66=.././ >> src/powdp//c66//powdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__POWDP_66_BE_ELF_SRCCOMMON=../../../common >> src/powdp//c66//powdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powdp_66_BE_ELF"
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/powdp/powdp.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/powdp/powdp_d.c
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/powdp//c66/powdp.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/powdp//c66/powdp_i.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common/drvdp.c
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common/drvdp.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common/driver.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common/driver.c
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common/common.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common/tables.c
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/common//c66/common.h
src/powdp//c66//powdp_66_BE_ELF/Release/powdp_66_BE_ELF.out: src/powdp//c66//powdp_66_BE_ELF/.project
	-@ echo Importing Project powdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powdp/c66/powdp_66_BE_ELF"
	-@ echo Building Project powdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project powdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/powdp//c66//powdp_66_BE_ELF"


#############################################################

# Rule to Build Project powsp_66_LE_COFF

#############################################################

.executables: src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out

.projects: src/powsp//c66//powsp_66_LE_COFF

src/powsp//c66//powsp_66_LE_COFF: src/powsp//c66//powsp_66_LE_COFF/.project

src/powsp//c66//powsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_COFF_SRCPOWSP/powsp_d.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powsp//c66//powsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_COFF_SRCPOWSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_COFF_SRCPOWSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/powsp//c66//powsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__POWSP_66_LE_COFF_SRCPOWSP=../../ >> src/powsp//c66//powsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__POWSP_66_LE_COFF_SRCPOWSPC66=.././ >> src/powsp//c66//powsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__POWSP_66_LE_COFF_SRCCOMMON=../../../common >> src/powsp//c66//powsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powsp_66_LE_COFF"
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/powsp/powsp.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/powsp/powsp_d.c
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/powsp//c66/powsp.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/powsp//c66/powsp_i.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common/drvsp.c
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common/drvsp.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common/driver.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common/driver.c
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common/common.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common/tables.c
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/common//c66/common.h
src/powsp//c66//powsp_66_LE_COFF/Release/powsp_66_LE_COFF.out: src/powsp//c66//powsp_66_LE_COFF/.project
	-@ echo Importing Project powsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66/powsp_66_LE_COFF"
	-@ echo Building Project powsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project powsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/powsp//c66//powsp_66_LE_COFF"


#############################################################

# Rule to Build Project powsp_66_BE_COFF

#############################################################

.executables: src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out

.projects: src/powsp//c66//powsp_66_BE_COFF

src/powsp//c66//powsp_66_BE_COFF: src/powsp//c66//powsp_66_BE_COFF/.project

src/powsp//c66//powsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_COFF_SRCPOWSP/powsp_d.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powsp//c66//powsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_COFF_SRCPOWSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_COFF_SRCPOWSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/powsp//c66//powsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__POWSP_66_BE_COFF_SRCPOWSP=../../ >> src/powsp//c66//powsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__POWSP_66_BE_COFF_SRCPOWSPC66=.././ >> src/powsp//c66//powsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__POWSP_66_BE_COFF_SRCCOMMON=../../../common >> src/powsp//c66//powsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powsp_66_BE_COFF"
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/powsp/powsp.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/powsp/powsp_d.c
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/powsp//c66/powsp.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/powsp//c66/powsp_i.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common/drvsp.c
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common/drvsp.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common/driver.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common/driver.c
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common/common.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common/tables.c
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/common//c66/common.h
src/powsp//c66//powsp_66_BE_COFF/Release/powsp_66_BE_COFF.out: src/powsp//c66//powsp_66_BE_COFF/.project
	-@ echo Importing Project powsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66/powsp_66_BE_COFF"
	-@ echo Building Project powsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project powsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/powsp//c66//powsp_66_BE_COFF"


#############################################################

# Rule to Build Project powsp_66_LE_ELF

#############################################################

.executables: src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out

.projects: src/powsp//c66//powsp_66_LE_ELF

src/powsp//c66//powsp_66_LE_ELF: src/powsp//c66//powsp_66_LE_ELF/.project

src/powsp//c66//powsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_ELF_SRCPOWSP/powsp_d.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powsp//c66//powsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_ELF_SRCPOWSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_ELF_SRCPOWSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/powsp//c66//powsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__POWSP_66_LE_ELF_SRCPOWSP=../../ >> src/powsp//c66//powsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__POWSP_66_LE_ELF_SRCPOWSPC66=.././ >> src/powsp//c66//powsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__POWSP_66_LE_ELF_SRCCOMMON=../../../common >> src/powsp//c66//powsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powsp_66_LE_ELF"
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/powsp/powsp.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/powsp/powsp_d.c
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/powsp//c66/powsp.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/powsp//c66/powsp_i.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common/drvsp.c
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common/drvsp.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common/driver.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common/driver.c
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common/common.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common/tables.c
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/common//c66/common.h
src/powsp//c66//powsp_66_LE_ELF/Release/powsp_66_LE_ELF.out: src/powsp//c66//powsp_66_LE_ELF/.project
	-@ echo Importing Project powsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66/powsp_66_LE_ELF"
	-@ echo Building Project powsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project powsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/powsp//c66//powsp_66_LE_ELF"


#############################################################

# Rule to Build Project powsp_66_BE_ELF

#############################################################

.executables: src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out

.projects: src/powsp//c66//powsp_66_BE_ELF

src/powsp//c66//powsp_66_BE_ELF: src/powsp//c66//powsp_66_BE_ELF/.project

src/powsp//c66//powsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name powsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_ELF_SRCPOWSP/powsp_d.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/powsp//c66//powsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_ELF_SRCPOWSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_ELF_SRCPOWSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66" \
 -ccs.definePathVariable EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/powsp//c66//powsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__POWSP_66_BE_ELF_SRCPOWSP=../../ >> src/powsp//c66//powsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__POWSP_66_BE_ELF_SRCPOWSPC66=.././ >> src/powsp//c66//powsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__POWSP_66_BE_ELF_SRCCOMMON=../../../common >> src/powsp//c66//powsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/powsp_66_BE_ELF"
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/powsp/powsp.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/powsp/powsp_d.c
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/powsp//c66/powsp.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/powsp//c66/powsp_i.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common/drvsp.c
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common/drvsp.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common/driver.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common/driver.c
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common/common.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common/tables.c
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/common//c66/common.h
src/powsp//c66//powsp_66_BE_ELF/Release/powsp_66_BE_ELF.out: src/powsp//c66//powsp_66_BE_ELF/.project
	-@ echo Importing Project powsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects powsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/powsp/c66/powsp_66_BE_ELF"
	-@ echo Building Project powsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/powsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects powsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project powsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/powsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/powsp//c66//powsp_66_BE_ELF"


#############################################################

# Rule to Build Project recipdp_66_LE_COFF

#############################################################

.executables: src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out

.projects: src/recipdp//c66//recipdp_66_LE_COFF

src/recipdp//c66//recipdp_66_LE_COFF: src/recipdp//c66//recipdp_66_LE_COFF/.project

src/recipdp//c66//recipdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_COFF_SRCRECIPDP/recipdp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipdp//c66//recipdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_COFF_SRCRECIPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_COFF_SRCRECIPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/recipdp//c66//recipdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RECIPDP_66_LE_COFF_SRCRECIPDP=../../ >> src/recipdp//c66//recipdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RECIPDP_66_LE_COFF_SRCRECIPDPC66=.././ >> src/recipdp//c66//recipdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RECIPDP_66_LE_COFF_SRCCOMMON=../../../common >> src/recipdp//c66//recipdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_LE_COFF"
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/recipdp/recipdp.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/recipdp/recipdp_d.c
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/recipdp//c66/recipdp.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/recipdp//c66/recipdp_i.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common/drvdp.c
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common/drvdp.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common/driver.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common/driver.c
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common/common.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common/tables.c
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/common//c66/common.h
src/recipdp//c66//recipdp_66_LE_COFF/Release/recipdp_66_LE_COFF.out: src/recipdp//c66//recipdp_66_LE_COFF/.project
	-@ echo Importing Project recipdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66/recipdp_66_LE_COFF"
	-@ echo Building Project recipdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project recipdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/recipdp//c66//recipdp_66_LE_COFF"


#############################################################

# Rule to Build Project recipdp_66_BE_COFF

#############################################################

.executables: src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out

.projects: src/recipdp//c66//recipdp_66_BE_COFF

src/recipdp//c66//recipdp_66_BE_COFF: src/recipdp//c66//recipdp_66_BE_COFF/.project

src/recipdp//c66//recipdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_COFF_SRCRECIPDP/recipdp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipdp//c66//recipdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_COFF_SRCRECIPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_COFF_SRCRECIPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/recipdp//c66//recipdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RECIPDP_66_BE_COFF_SRCRECIPDP=../../ >> src/recipdp//c66//recipdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RECIPDP_66_BE_COFF_SRCRECIPDPC66=.././ >> src/recipdp//c66//recipdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RECIPDP_66_BE_COFF_SRCCOMMON=../../../common >> src/recipdp//c66//recipdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_BE_COFF"
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/recipdp/recipdp.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/recipdp/recipdp_d.c
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/recipdp//c66/recipdp.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/recipdp//c66/recipdp_i.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common/drvdp.c
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common/drvdp.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common/driver.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common/driver.c
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common/common.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common/tables.c
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/common//c66/common.h
src/recipdp//c66//recipdp_66_BE_COFF/Release/recipdp_66_BE_COFF.out: src/recipdp//c66//recipdp_66_BE_COFF/.project
	-@ echo Importing Project recipdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66/recipdp_66_BE_COFF"
	-@ echo Building Project recipdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project recipdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/recipdp//c66//recipdp_66_BE_COFF"


#############################################################

# Rule to Build Project recipdp_66_LE_ELF

#############################################################

.executables: src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out

.projects: src/recipdp//c66//recipdp_66_LE_ELF

src/recipdp//c66//recipdp_66_LE_ELF: src/recipdp//c66//recipdp_66_LE_ELF/.project

src/recipdp//c66//recipdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_ELF_SRCRECIPDP/recipdp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipdp//c66//recipdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_ELF_SRCRECIPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_ELF_SRCRECIPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/recipdp//c66//recipdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RECIPDP_66_LE_ELF_SRCRECIPDP=../../ >> src/recipdp//c66//recipdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RECIPDP_66_LE_ELF_SRCRECIPDPC66=.././ >> src/recipdp//c66//recipdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RECIPDP_66_LE_ELF_SRCCOMMON=../../../common >> src/recipdp//c66//recipdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_LE_ELF"
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/recipdp/recipdp.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/recipdp/recipdp_d.c
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/recipdp//c66/recipdp.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/recipdp//c66/recipdp_i.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common/drvdp.c
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common/drvdp.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common/driver.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common/driver.c
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common/common.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common/tables.c
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/common//c66/common.h
src/recipdp//c66//recipdp_66_LE_ELF/Release/recipdp_66_LE_ELF.out: src/recipdp//c66//recipdp_66_LE_ELF/.project
	-@ echo Importing Project recipdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66/recipdp_66_LE_ELF"
	-@ echo Building Project recipdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project recipdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/recipdp//c66//recipdp_66_LE_ELF"


#############################################################

# Rule to Build Project recipdp_66_BE_ELF

#############################################################

.executables: src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out

.projects: src/recipdp//c66//recipdp_66_BE_ELF

src/recipdp//c66//recipdp_66_BE_ELF: src/recipdp//c66//recipdp_66_BE_ELF/.project

src/recipdp//c66//recipdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_ELF_SRCRECIPDP/recipdp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipdp//c66//recipdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_ELF_SRCRECIPDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_ELF_SRCRECIPDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/recipdp//c66//recipdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RECIPDP_66_BE_ELF_SRCRECIPDP=../../ >> src/recipdp//c66//recipdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RECIPDP_66_BE_ELF_SRCRECIPDPC66=.././ >> src/recipdp//c66//recipdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RECIPDP_66_BE_ELF_SRCCOMMON=../../../common >> src/recipdp//c66//recipdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_BE_ELF"
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/recipdp/recipdp.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/recipdp/recipdp_d.c
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/recipdp//c66/recipdp.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/recipdp//c66/recipdp_i.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common/drvdp.c
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common/drvdp.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common/driver.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common/driver.c
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common/common.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common/tables.c
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/common//c66/common.h
src/recipdp//c66//recipdp_66_BE_ELF/Release/recipdp_66_BE_ELF.out: src/recipdp//c66//recipdp_66_BE_ELF/.project
	-@ echo Importing Project recipdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipdp/c66/recipdp_66_BE_ELF"
	-@ echo Building Project recipdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project recipdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/recipdp//c66//recipdp_66_BE_ELF"


#############################################################

# Rule to Build Project recipsp_66_LE_COFF

#############################################################

.executables: src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out

.projects: src/recipsp//c66//recipsp_66_LE_COFF

src/recipsp//c66//recipsp_66_LE_COFF: src/recipsp//c66//recipsp_66_LE_COFF/.project

src/recipsp//c66//recipsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_COFF_SRCRECIPSP/recipsp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipsp//c66//recipsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_COFF_SRCRECIPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_COFF_SRCRECIPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/recipsp//c66//recipsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RECIPSP_66_LE_COFF_SRCRECIPSP=../../ >> src/recipsp//c66//recipsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RECIPSP_66_LE_COFF_SRCRECIPSPC66=.././ >> src/recipsp//c66//recipsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RECIPSP_66_LE_COFF_SRCCOMMON=../../../common >> src/recipsp//c66//recipsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_LE_COFF"
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/recipsp/recipsp.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/recipsp/recipsp_d.c
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/recipsp//c66/recipsp.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/recipsp//c66/recipsp_i.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common/drvsp.c
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common/drvsp.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common/driver.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common/driver.c
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common/common.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common/tables.c
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/common//c66/common.h
src/recipsp//c66//recipsp_66_LE_COFF/Release/recipsp_66_LE_COFF.out: src/recipsp//c66//recipsp_66_LE_COFF/.project
	-@ echo Importing Project recipsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66/recipsp_66_LE_COFF"
	-@ echo Building Project recipsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project recipsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/recipsp//c66//recipsp_66_LE_COFF"


#############################################################

# Rule to Build Project recipsp_66_BE_COFF

#############################################################

.executables: src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out

.projects: src/recipsp//c66//recipsp_66_BE_COFF

src/recipsp//c66//recipsp_66_BE_COFF: src/recipsp//c66//recipsp_66_BE_COFF/.project

src/recipsp//c66//recipsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_COFF_SRCRECIPSP/recipsp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipsp//c66//recipsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_COFF_SRCRECIPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_COFF_SRCRECIPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/recipsp//c66//recipsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RECIPSP_66_BE_COFF_SRCRECIPSP=../../ >> src/recipsp//c66//recipsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RECIPSP_66_BE_COFF_SRCRECIPSPC66=.././ >> src/recipsp//c66//recipsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RECIPSP_66_BE_COFF_SRCCOMMON=../../../common >> src/recipsp//c66//recipsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_BE_COFF"
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/recipsp/recipsp.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/recipsp/recipsp_d.c
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/recipsp//c66/recipsp.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/recipsp//c66/recipsp_i.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common/drvsp.c
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common/drvsp.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common/driver.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common/driver.c
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common/common.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common/tables.c
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/common//c66/common.h
src/recipsp//c66//recipsp_66_BE_COFF/Release/recipsp_66_BE_COFF.out: src/recipsp//c66//recipsp_66_BE_COFF/.project
	-@ echo Importing Project recipsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66/recipsp_66_BE_COFF"
	-@ echo Building Project recipsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project recipsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/recipsp//c66//recipsp_66_BE_COFF"


#############################################################

# Rule to Build Project recipsp_66_LE_ELF

#############################################################

.executables: src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out

.projects: src/recipsp//c66//recipsp_66_LE_ELF

src/recipsp//c66//recipsp_66_LE_ELF: src/recipsp//c66//recipsp_66_LE_ELF/.project

src/recipsp//c66//recipsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_ELF_SRCRECIPSP/recipsp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipsp//c66//recipsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_ELF_SRCRECIPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_ELF_SRCRECIPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/recipsp//c66//recipsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RECIPSP_66_LE_ELF_SRCRECIPSP=../../ >> src/recipsp//c66//recipsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RECIPSP_66_LE_ELF_SRCRECIPSPC66=.././ >> src/recipsp//c66//recipsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RECIPSP_66_LE_ELF_SRCCOMMON=../../../common >> src/recipsp//c66//recipsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_LE_ELF"
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/recipsp/recipsp.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/recipsp/recipsp_d.c
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/recipsp//c66/recipsp.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/recipsp//c66/recipsp_i.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common/drvsp.c
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common/drvsp.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common/driver.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common/driver.c
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common/common.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common/tables.c
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/common//c66/common.h
src/recipsp//c66//recipsp_66_LE_ELF/Release/recipsp_66_LE_ELF.out: src/recipsp//c66//recipsp_66_LE_ELF/.project
	-@ echo Importing Project recipsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66/recipsp_66_LE_ELF"
	-@ echo Building Project recipsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project recipsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/recipsp//c66//recipsp_66_LE_ELF"


#############################################################

# Rule to Build Project recipsp_66_BE_ELF

#############################################################

.executables: src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out

.projects: src/recipsp//c66//recipsp_66_BE_ELF

src/recipsp//c66//recipsp_66_BE_ELF: src/recipsp//c66//recipsp_66_BE_ELF/.project

src/recipsp//c66//recipsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name recipsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_ELF_SRCRECIPSP/recipsp_d.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/recipsp//c66//recipsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_ELF_SRCRECIPSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_ELF_SRCRECIPSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/recipsp//c66//recipsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RECIPSP_66_BE_ELF_SRCRECIPSP=../../ >> src/recipsp//c66//recipsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RECIPSP_66_BE_ELF_SRCRECIPSPC66=.././ >> src/recipsp//c66//recipsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RECIPSP_66_BE_ELF_SRCCOMMON=../../../common >> src/recipsp//c66//recipsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_BE_ELF"
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/recipsp/recipsp.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/recipsp/recipsp_d.c
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/recipsp//c66/recipsp.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/recipsp//c66/recipsp_i.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common/drvsp.c
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common/drvsp.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common/driver.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common/driver.c
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common/common.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common/tables.c
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/common//c66/common.h
src/recipsp//c66//recipsp_66_BE_ELF/Release/recipsp_66_BE_ELF.out: src/recipsp//c66//recipsp_66_BE_ELF/.project
	-@ echo Importing Project recipsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects recipsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/recipsp/c66/recipsp_66_BE_ELF"
	-@ echo Building Project recipsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/recipsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects recipsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project recipsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/recipsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/recipsp//c66//recipsp_66_BE_ELF"


#############################################################

# Rule to Build Project rsqrtdp_66_LE_COFF

#############################################################

.executables: src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out

.projects: src/rsqrtdp//c66//rsqrtdp_66_LE_COFF

src/rsqrtdp//c66//rsqrtdp_66_LE_COFF: src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/.project

src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_COFF_SRCRSQRTDP/rsqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtdp//c66//rsqrtdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_COFF_SRCRSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_COFF_SRCRSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_LE_COFF_SRCRSQRTDP=../../ >> src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_LE_COFF_SRCRSQRTDPC66=.././ >> src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_LE_COFF_SRCCOMMON=../../../common >> src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_LE_COFF"
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/rsqrtdp/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/rsqrtdp/rsqrtdp_d.c
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/rsqrtdp//c66/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/rsqrtdp//c66/rsqrtdp_i.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common/drvdp.c
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common/drvdp.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common/driver.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common/driver.c
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common/common.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common/tables.c
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/common//c66/common.h
src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/Release/rsqrtdp_66_LE_COFF.out: src/rsqrtdp//c66//rsqrtdp_66_LE_COFF/.project
	-@ echo Importing Project rsqrtdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66/rsqrtdp_66_LE_COFF"
	-@ echo Building Project rsqrtdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project rsqrtdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/rsqrtdp//c66//rsqrtdp_66_LE_COFF"


#############################################################

# Rule to Build Project rsqrtdp_66_BE_COFF

#############################################################

.executables: src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out

.projects: src/rsqrtdp//c66//rsqrtdp_66_BE_COFF

src/rsqrtdp//c66//rsqrtdp_66_BE_COFF: src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/.project

src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_COFF_SRCRSQRTDP/rsqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtdp//c66//rsqrtdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_COFF_SRCRSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_COFF_SRCRSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_BE_COFF_SRCRSQRTDP=../../ >> src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_BE_COFF_SRCRSQRTDPC66=.././ >> src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_BE_COFF_SRCCOMMON=../../../common >> src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_BE_COFF"
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/rsqrtdp/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/rsqrtdp/rsqrtdp_d.c
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/rsqrtdp//c66/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/rsqrtdp//c66/rsqrtdp_i.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common/drvdp.c
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common/drvdp.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common/driver.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common/driver.c
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common/common.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common/tables.c
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/common//c66/common.h
src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/Release/rsqrtdp_66_BE_COFF.out: src/rsqrtdp//c66//rsqrtdp_66_BE_COFF/.project
	-@ echo Importing Project rsqrtdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66/rsqrtdp_66_BE_COFF"
	-@ echo Building Project rsqrtdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project rsqrtdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/rsqrtdp//c66//rsqrtdp_66_BE_COFF"


#############################################################

# Rule to Build Project rsqrtdp_66_LE_ELF

#############################################################

.executables: src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out

.projects: src/rsqrtdp//c66//rsqrtdp_66_LE_ELF

src/rsqrtdp//c66//rsqrtdp_66_LE_ELF: src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/.project

src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_ELF_SRCRSQRTDP/rsqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtdp//c66//rsqrtdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_ELF_SRCRSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_ELF_SRCRSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_LE_ELF_SRCRSQRTDP=../../ >> src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_LE_ELF_SRCRSQRTDPC66=.././ >> src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_LE_ELF_SRCCOMMON=../../../common >> src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_LE_ELF"
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/rsqrtdp/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/rsqrtdp/rsqrtdp_d.c
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/rsqrtdp//c66/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/rsqrtdp//c66/rsqrtdp_i.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common/drvdp.c
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common/drvdp.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common/driver.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common/driver.c
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common/common.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common/tables.c
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/common//c66/common.h
src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/Release/rsqrtdp_66_LE_ELF.out: src/rsqrtdp//c66//rsqrtdp_66_LE_ELF/.project
	-@ echo Importing Project rsqrtdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66/rsqrtdp_66_LE_ELF"
	-@ echo Building Project rsqrtdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project rsqrtdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/rsqrtdp//c66//rsqrtdp_66_LE_ELF"


#############################################################

# Rule to Build Project rsqrtdp_66_BE_ELF

#############################################################

.executables: src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out

.projects: src/rsqrtdp//c66//rsqrtdp_66_BE_ELF

src/rsqrtdp//c66//rsqrtdp_66_BE_ELF: src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/.project

src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_ELF_SRCRSQRTDP/rsqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtdp//c66//rsqrtdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_ELF_SRCRSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_ELF_SRCRSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_BE_ELF_SRCRSQRTDP=../../ >> src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_BE_ELF_SRCRSQRTDPC66=.././ >> src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RSQRTDP_66_BE_ELF_SRCCOMMON=../../../common >> src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_BE_ELF"
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/rsqrtdp/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/rsqrtdp/rsqrtdp_d.c
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/rsqrtdp//c66/rsqrtdp.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/rsqrtdp//c66/rsqrtdp_i.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common/drvdp.c
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common/drvdp.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common/driver.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common/driver.c
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common/common.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common/tables.c
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/common//c66/common.h
src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/Release/rsqrtdp_66_BE_ELF.out: src/rsqrtdp//c66//rsqrtdp_66_BE_ELF/.project
	-@ echo Importing Project rsqrtdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtdp/c66/rsqrtdp_66_BE_ELF"
	-@ echo Building Project rsqrtdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project rsqrtdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/rsqrtdp//c66//rsqrtdp_66_BE_ELF"


#############################################################

# Rule to Build Project rsqrtsp_66_LE_COFF

#############################################################

.executables: src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out

.projects: src/rsqrtsp//c66//rsqrtsp_66_LE_COFF

src/rsqrtsp//c66//rsqrtsp_66_LE_COFF: src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/.project

src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_COFF_SRCRSQRTSP/rsqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtsp//c66//rsqrtsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_COFF_SRCRSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_COFF_SRCRSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_LE_COFF_SRCRSQRTSP=../../ >> src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_LE_COFF_SRCRSQRTSPC66=.././ >> src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_LE_COFF_SRCCOMMON=../../../common >> src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_LE_COFF"
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/rsqrtsp/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/rsqrtsp/rsqrtsp_d.c
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/rsqrtsp//c66/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/rsqrtsp//c66/rsqrtsp_i.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common/drvsp.c
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common/drvsp.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common/driver.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common/driver.c
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common/common.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common/tables.c
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/common//c66/common.h
src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/Release/rsqrtsp_66_LE_COFF.out: src/rsqrtsp//c66//rsqrtsp_66_LE_COFF/.project
	-@ echo Importing Project rsqrtsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66/rsqrtsp_66_LE_COFF"
	-@ echo Building Project rsqrtsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project rsqrtsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/rsqrtsp//c66//rsqrtsp_66_LE_COFF"


#############################################################

# Rule to Build Project rsqrtsp_66_BE_COFF

#############################################################

.executables: src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out

.projects: src/rsqrtsp//c66//rsqrtsp_66_BE_COFF

src/rsqrtsp//c66//rsqrtsp_66_BE_COFF: src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/.project

src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_COFF_SRCRSQRTSP/rsqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtsp//c66//rsqrtsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_COFF_SRCRSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_COFF_SRCRSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_BE_COFF_SRCRSQRTSP=../../ >> src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_BE_COFF_SRCRSQRTSPC66=.././ >> src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_BE_COFF_SRCCOMMON=../../../common >> src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_BE_COFF"
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/rsqrtsp/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/rsqrtsp/rsqrtsp_d.c
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/rsqrtsp//c66/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/rsqrtsp//c66/rsqrtsp_i.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common/drvsp.c
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common/drvsp.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common/driver.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common/driver.c
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common/common.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common/tables.c
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/common//c66/common.h
src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/Release/rsqrtsp_66_BE_COFF.out: src/rsqrtsp//c66//rsqrtsp_66_BE_COFF/.project
	-@ echo Importing Project rsqrtsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66/rsqrtsp_66_BE_COFF"
	-@ echo Building Project rsqrtsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project rsqrtsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/rsqrtsp//c66//rsqrtsp_66_BE_COFF"


#############################################################

# Rule to Build Project rsqrtsp_66_LE_ELF

#############################################################

.executables: src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out

.projects: src/rsqrtsp//c66//rsqrtsp_66_LE_ELF

src/rsqrtsp//c66//rsqrtsp_66_LE_ELF: src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/.project

src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_ELF_SRCRSQRTSP/rsqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtsp//c66//rsqrtsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_ELF_SRCRSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_ELF_SRCRSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_LE_ELF_SRCRSQRTSP=../../ >> src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_LE_ELF_SRCRSQRTSPC66=.././ >> src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_LE_ELF_SRCCOMMON=../../../common >> src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_LE_ELF"
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/rsqrtsp/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/rsqrtsp/rsqrtsp_d.c
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/rsqrtsp//c66/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/rsqrtsp//c66/rsqrtsp_i.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common/drvsp.c
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common/drvsp.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common/driver.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common/driver.c
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common/common.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common/tables.c
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/common//c66/common.h
src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/Release/rsqrtsp_66_LE_ELF.out: src/rsqrtsp//c66//rsqrtsp_66_LE_ELF/.project
	-@ echo Importing Project rsqrtsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66/rsqrtsp_66_LE_ELF"
	-@ echo Building Project rsqrtsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project rsqrtsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/rsqrtsp//c66//rsqrtsp_66_LE_ELF"


#############################################################

# Rule to Build Project rsqrtsp_66_BE_ELF

#############################################################

.executables: src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out

.projects: src/rsqrtsp//c66//rsqrtsp_66_BE_ELF

src/rsqrtsp//c66//rsqrtsp_66_BE_ELF: src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/.project

src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name rsqrtsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_ELF_SRCRSQRTSP/rsqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/rsqrtsp//c66//rsqrtsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_ELF_SRCRSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_ELF_SRCRSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_BE_ELF_SRCRSQRTSP=../../ >> src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_BE_ELF_SRCRSQRTSPC66=.././ >> src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__RSQRTSP_66_BE_ELF_SRCCOMMON=../../../common >> src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_BE_ELF"
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/rsqrtsp/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/rsqrtsp/rsqrtsp_d.c
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/rsqrtsp//c66/rsqrtsp.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/rsqrtsp//c66/rsqrtsp_i.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common/drvsp.c
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common/drvsp.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common/driver.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common/driver.c
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common/common.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common/tables.c
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/common//c66/common.h
src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/Release/rsqrtsp_66_BE_ELF.out: src/rsqrtsp//c66//rsqrtsp_66_BE_ELF/.project
	-@ echo Importing Project rsqrtsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects rsqrtsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/rsqrtsp/c66/rsqrtsp_66_BE_ELF"
	-@ echo Building Project rsqrtsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/rsqrtsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects rsqrtsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project rsqrtsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/rsqrtsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/rsqrtsp//c66//rsqrtsp_66_BE_ELF"


#############################################################

# Rule to Build Project sindp_66_LE_COFF

#############################################################

.executables: src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out

.projects: src/sindp//c66//sindp_66_LE_COFF

src/sindp//c66//sindp_66_LE_COFF: src/sindp//c66//sindp_66_LE_COFF/.project

src/sindp//c66//sindp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sindp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_COFF_SRCSINDP/sindp_d.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sindp//c66//sindp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_COFF_SRCSINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_COFF_SRCSINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sindp//c66//sindp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINDP_66_LE_COFF_SRCSINDP=../../ >> src/sindp//c66//sindp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINDP_66_LE_COFF_SRCSINDPC66=.././ >> src/sindp//c66//sindp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINDP_66_LE_COFF_SRCCOMMON=../../../common >> src/sindp//c66//sindp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sindp_66_LE_COFF"
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/sindp/sindp.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/sindp/sindp_d.c
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/sindp//c66/sindp.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/sindp//c66/sindp_i.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common/drvdp.c
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common/drvdp.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common/driver.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common/driver.c
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common/common.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common/tables.c
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/common//c66/common.h
src/sindp//c66//sindp_66_LE_COFF/Release/sindp_66_LE_COFF.out: src/sindp//c66//sindp_66_LE_COFF/.project
	-@ echo Importing Project sindp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sindp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66/sindp_66_LE_COFF"
	-@ echo Building Project sindp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sindp_66_LE_COFF -ccs.configuration Release
	-@ echo Project sindp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sindp_66_LE_COFF"

clean::
	-$(RMDIR) "src/sindp//c66//sindp_66_LE_COFF"


#############################################################

# Rule to Build Project sindp_66_BE_COFF

#############################################################

.executables: src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out

.projects: src/sindp//c66//sindp_66_BE_COFF

src/sindp//c66//sindp_66_BE_COFF: src/sindp//c66//sindp_66_BE_COFF/.project

src/sindp//c66//sindp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sindp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_COFF_SRCSINDP/sindp_d.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sindp//c66//sindp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_COFF_SRCSINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_COFF_SRCSINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sindp//c66//sindp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINDP_66_BE_COFF_SRCSINDP=../../ >> src/sindp//c66//sindp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINDP_66_BE_COFF_SRCSINDPC66=.././ >> src/sindp//c66//sindp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINDP_66_BE_COFF_SRCCOMMON=../../../common >> src/sindp//c66//sindp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sindp_66_BE_COFF"
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/sindp/sindp.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/sindp/sindp_d.c
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/sindp//c66/sindp.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/sindp//c66/sindp_i.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common/drvdp.c
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common/drvdp.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common/driver.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common/driver.c
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common/common.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common/tables.c
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/common//c66/common.h
src/sindp//c66//sindp_66_BE_COFF/Release/sindp_66_BE_COFF.out: src/sindp//c66//sindp_66_BE_COFF/.project
	-@ echo Importing Project sindp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sindp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66/sindp_66_BE_COFF"
	-@ echo Building Project sindp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sindp_66_BE_COFF -ccs.configuration Release
	-@ echo Project sindp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sindp_66_BE_COFF"

clean::
	-$(RMDIR) "src/sindp//c66//sindp_66_BE_COFF"


#############################################################

# Rule to Build Project sindp_66_LE_ELF

#############################################################

.executables: src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out

.projects: src/sindp//c66//sindp_66_LE_ELF

src/sindp//c66//sindp_66_LE_ELF: src/sindp//c66//sindp_66_LE_ELF/.project

src/sindp//c66//sindp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sindp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_ELF_SRCSINDP/sindp_d.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sindp//c66//sindp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_ELF_SRCSINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_ELF_SRCSINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sindp//c66//sindp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINDP_66_LE_ELF_SRCSINDP=../../ >> src/sindp//c66//sindp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINDP_66_LE_ELF_SRCSINDPC66=.././ >> src/sindp//c66//sindp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINDP_66_LE_ELF_SRCCOMMON=../../../common >> src/sindp//c66//sindp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sindp_66_LE_ELF"
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/sindp/sindp.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/sindp/sindp_d.c
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/sindp//c66/sindp.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/sindp//c66/sindp_i.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common/drvdp.c
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common/drvdp.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common/driver.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common/driver.c
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common/common.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common/tables.c
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/common//c66/common.h
src/sindp//c66//sindp_66_LE_ELF/Release/sindp_66_LE_ELF.out: src/sindp//c66//sindp_66_LE_ELF/.project
	-@ echo Importing Project sindp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sindp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66/sindp_66_LE_ELF"
	-@ echo Building Project sindp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sindp_66_LE_ELF -ccs.configuration Release
	-@ echo Project sindp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sindp_66_LE_ELF"

clean::
	-$(RMDIR) "src/sindp//c66//sindp_66_LE_ELF"


#############################################################

# Rule to Build Project sindp_66_BE_ELF

#############################################################

.executables: src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out

.projects: src/sindp//c66//sindp_66_BE_ELF

src/sindp//c66//sindp_66_BE_ELF: src/sindp//c66//sindp_66_BE_ELF/.project

src/sindp//c66//sindp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sindp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_ELF_SRCSINDP/sindp_d.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sindp//c66//sindp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_ELF_SRCSINDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_ELF_SRCSINDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sindp//c66//sindp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINDP_66_BE_ELF_SRCSINDP=../../ >> src/sindp//c66//sindp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINDP_66_BE_ELF_SRCSINDPC66=.././ >> src/sindp//c66//sindp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINDP_66_BE_ELF_SRCCOMMON=../../../common >> src/sindp//c66//sindp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sindp_66_BE_ELF"
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/sindp/sindp.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/sindp/sindp_d.c
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/sindp//c66/sindp.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/sindp//c66/sindp_i.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common/drvdp.c
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common/drvdp.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common/driver.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common/driver.c
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common/common.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common/tables.c
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/common//c66/common.h
src/sindp//c66//sindp_66_BE_ELF/Release/sindp_66_BE_ELF.out: src/sindp//c66//sindp_66_BE_ELF/.project
	-@ echo Importing Project sindp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sindp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sindp/c66/sindp_66_BE_ELF"
	-@ echo Building Project sindp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sindp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sindp_66_BE_ELF -ccs.configuration Release
	-@ echo Project sindp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sindp_66_BE_ELF"

clean::
	-$(RMDIR) "src/sindp//c66//sindp_66_BE_ELF"


#############################################################

# Rule to Build Project sinhdp_66_LE_COFF

#############################################################

.executables: src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out

.projects: src/sinhdp//c66//sinhdp_66_LE_COFF

src/sinhdp//c66//sinhdp_66_LE_COFF: src/sinhdp//c66//sinhdp_66_LE_COFF/.project

src/sinhdp//c66//sinhdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_COFF_SRCSINHDP/sinhdp_d.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhdp//c66//sinhdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_COFF_SRCSINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_COFF_SRCSINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sinhdp//c66//sinhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINHDP_66_LE_COFF_SRCSINHDP=../../ >> src/sinhdp//c66//sinhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINHDP_66_LE_COFF_SRCSINHDPC66=.././ >> src/sinhdp//c66//sinhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINHDP_66_LE_COFF_SRCCOMMON=../../../common >> src/sinhdp//c66//sinhdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_LE_COFF"
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/sinhdp/sinhdp.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/sinhdp/sinhdp_d.c
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/sinhdp//c66/sinhdp.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/sinhdp//c66/sinhdp_i.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common/drvdp.c
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common/drvdp.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common/driver.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common/driver.c
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common/common.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common/tables.c
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/common//c66/common.h
src/sinhdp//c66//sinhdp_66_LE_COFF/Release/sinhdp_66_LE_COFF.out: src/sinhdp//c66//sinhdp_66_LE_COFF/.project
	-@ echo Importing Project sinhdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66/sinhdp_66_LE_COFF"
	-@ echo Building Project sinhdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project sinhdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/sinhdp//c66//sinhdp_66_LE_COFF"


#############################################################

# Rule to Build Project sinhdp_66_BE_COFF

#############################################################

.executables: src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out

.projects: src/sinhdp//c66//sinhdp_66_BE_COFF

src/sinhdp//c66//sinhdp_66_BE_COFF: src/sinhdp//c66//sinhdp_66_BE_COFF/.project

src/sinhdp//c66//sinhdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_COFF_SRCSINHDP/sinhdp_d.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhdp//c66//sinhdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_COFF_SRCSINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_COFF_SRCSINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sinhdp//c66//sinhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINHDP_66_BE_COFF_SRCSINHDP=../../ >> src/sinhdp//c66//sinhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINHDP_66_BE_COFF_SRCSINHDPC66=.././ >> src/sinhdp//c66//sinhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINHDP_66_BE_COFF_SRCCOMMON=../../../common >> src/sinhdp//c66//sinhdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_BE_COFF"
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/sinhdp/sinhdp.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/sinhdp/sinhdp_d.c
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/sinhdp//c66/sinhdp.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/sinhdp//c66/sinhdp_i.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common/drvdp.c
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common/drvdp.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common/driver.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common/driver.c
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common/common.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common/tables.c
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/common//c66/common.h
src/sinhdp//c66//sinhdp_66_BE_COFF/Release/sinhdp_66_BE_COFF.out: src/sinhdp//c66//sinhdp_66_BE_COFF/.project
	-@ echo Importing Project sinhdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66/sinhdp_66_BE_COFF"
	-@ echo Building Project sinhdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project sinhdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/sinhdp//c66//sinhdp_66_BE_COFF"


#############################################################

# Rule to Build Project sinhdp_66_LE_ELF

#############################################################

.executables: src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out

.projects: src/sinhdp//c66//sinhdp_66_LE_ELF

src/sinhdp//c66//sinhdp_66_LE_ELF: src/sinhdp//c66//sinhdp_66_LE_ELF/.project

src/sinhdp//c66//sinhdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_ELF_SRCSINHDP/sinhdp_d.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhdp//c66//sinhdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_ELF_SRCSINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_ELF_SRCSINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sinhdp//c66//sinhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINHDP_66_LE_ELF_SRCSINHDP=../../ >> src/sinhdp//c66//sinhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINHDP_66_LE_ELF_SRCSINHDPC66=.././ >> src/sinhdp//c66//sinhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINHDP_66_LE_ELF_SRCCOMMON=../../../common >> src/sinhdp//c66//sinhdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_LE_ELF"
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/sinhdp/sinhdp.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/sinhdp/sinhdp_d.c
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/sinhdp//c66/sinhdp.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/sinhdp//c66/sinhdp_i.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common/drvdp.c
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common/drvdp.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common/driver.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common/driver.c
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common/common.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common/tables.c
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/common//c66/common.h
src/sinhdp//c66//sinhdp_66_LE_ELF/Release/sinhdp_66_LE_ELF.out: src/sinhdp//c66//sinhdp_66_LE_ELF/.project
	-@ echo Importing Project sinhdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66/sinhdp_66_LE_ELF"
	-@ echo Building Project sinhdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project sinhdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/sinhdp//c66//sinhdp_66_LE_ELF"


#############################################################

# Rule to Build Project sinhdp_66_BE_ELF

#############################################################

.executables: src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out

.projects: src/sinhdp//c66//sinhdp_66_BE_ELF

src/sinhdp//c66//sinhdp_66_BE_ELF: src/sinhdp//c66//sinhdp_66_BE_ELF/.project

src/sinhdp//c66//sinhdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_ELF_SRCSINHDP/sinhdp_d.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhdp//c66//sinhdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_ELF_SRCSINHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_ELF_SRCSINHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sinhdp//c66//sinhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINHDP_66_BE_ELF_SRCSINHDP=../../ >> src/sinhdp//c66//sinhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINHDP_66_BE_ELF_SRCSINHDPC66=.././ >> src/sinhdp//c66//sinhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINHDP_66_BE_ELF_SRCCOMMON=../../../common >> src/sinhdp//c66//sinhdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_BE_ELF"
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/sinhdp/sinhdp.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/sinhdp/sinhdp_d.c
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/sinhdp//c66/sinhdp.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/sinhdp//c66/sinhdp_i.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common/drvdp.c
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common/drvdp.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common/driver.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common/driver.c
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common/common.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common/tables.c
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/common//c66/common.h
src/sinhdp//c66//sinhdp_66_BE_ELF/Release/sinhdp_66_BE_ELF.out: src/sinhdp//c66//sinhdp_66_BE_ELF/.project
	-@ echo Importing Project sinhdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhdp/c66/sinhdp_66_BE_ELF"
	-@ echo Building Project sinhdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project sinhdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/sinhdp//c66//sinhdp_66_BE_ELF"


#############################################################

# Rule to Build Project sinhsp_66_LE_COFF

#############################################################

.executables: src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out

.projects: src/sinhsp//c66//sinhsp_66_LE_COFF

src/sinhsp//c66//sinhsp_66_LE_COFF: src/sinhsp//c66//sinhsp_66_LE_COFF/.project

src/sinhsp//c66//sinhsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_COFF_SRCSINHSP/sinhsp_d.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhsp//c66//sinhsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_COFF_SRCSINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_COFF_SRCSINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sinhsp//c66//sinhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINHSP_66_LE_COFF_SRCSINHSP=../../ >> src/sinhsp//c66//sinhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINHSP_66_LE_COFF_SRCSINHSPC66=.././ >> src/sinhsp//c66//sinhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINHSP_66_LE_COFF_SRCCOMMON=../../../common >> src/sinhsp//c66//sinhsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_LE_COFF"
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/sinhsp/sinhsp.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/sinhsp/sinhsp_d.c
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/sinhsp//c66/sinhsp.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/sinhsp//c66/sinhsp_i.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common/drvsp.c
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common/drvsp.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common/driver.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common/driver.c
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common/common.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common/tables.c
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/common//c66/common.h
src/sinhsp//c66//sinhsp_66_LE_COFF/Release/sinhsp_66_LE_COFF.out: src/sinhsp//c66//sinhsp_66_LE_COFF/.project
	-@ echo Importing Project sinhsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66/sinhsp_66_LE_COFF"
	-@ echo Building Project sinhsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project sinhsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/sinhsp//c66//sinhsp_66_LE_COFF"


#############################################################

# Rule to Build Project sinhsp_66_BE_COFF

#############################################################

.executables: src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out

.projects: src/sinhsp//c66//sinhsp_66_BE_COFF

src/sinhsp//c66//sinhsp_66_BE_COFF: src/sinhsp//c66//sinhsp_66_BE_COFF/.project

src/sinhsp//c66//sinhsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_COFF_SRCSINHSP/sinhsp_d.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhsp//c66//sinhsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_COFF_SRCSINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_COFF_SRCSINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sinhsp//c66//sinhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINHSP_66_BE_COFF_SRCSINHSP=../../ >> src/sinhsp//c66//sinhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINHSP_66_BE_COFF_SRCSINHSPC66=.././ >> src/sinhsp//c66//sinhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINHSP_66_BE_COFF_SRCCOMMON=../../../common >> src/sinhsp//c66//sinhsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_BE_COFF"
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/sinhsp/sinhsp.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/sinhsp/sinhsp_d.c
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/sinhsp//c66/sinhsp.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/sinhsp//c66/sinhsp_i.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common/drvsp.c
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common/drvsp.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common/driver.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common/driver.c
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common/common.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common/tables.c
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/common//c66/common.h
src/sinhsp//c66//sinhsp_66_BE_COFF/Release/sinhsp_66_BE_COFF.out: src/sinhsp//c66//sinhsp_66_BE_COFF/.project
	-@ echo Importing Project sinhsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66/sinhsp_66_BE_COFF"
	-@ echo Building Project sinhsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project sinhsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/sinhsp//c66//sinhsp_66_BE_COFF"


#############################################################

# Rule to Build Project sinhsp_66_LE_ELF

#############################################################

.executables: src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out

.projects: src/sinhsp//c66//sinhsp_66_LE_ELF

src/sinhsp//c66//sinhsp_66_LE_ELF: src/sinhsp//c66//sinhsp_66_LE_ELF/.project

src/sinhsp//c66//sinhsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_ELF_SRCSINHSP/sinhsp_d.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhsp//c66//sinhsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_ELF_SRCSINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_ELF_SRCSINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sinhsp//c66//sinhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINHSP_66_LE_ELF_SRCSINHSP=../../ >> src/sinhsp//c66//sinhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINHSP_66_LE_ELF_SRCSINHSPC66=.././ >> src/sinhsp//c66//sinhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINHSP_66_LE_ELF_SRCCOMMON=../../../common >> src/sinhsp//c66//sinhsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_LE_ELF"
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/sinhsp/sinhsp.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/sinhsp/sinhsp_d.c
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/sinhsp//c66/sinhsp.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/sinhsp//c66/sinhsp_i.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common/drvsp.c
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common/drvsp.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common/driver.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common/driver.c
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common/common.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common/tables.c
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/common//c66/common.h
src/sinhsp//c66//sinhsp_66_LE_ELF/Release/sinhsp_66_LE_ELF.out: src/sinhsp//c66//sinhsp_66_LE_ELF/.project
	-@ echo Importing Project sinhsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66/sinhsp_66_LE_ELF"
	-@ echo Building Project sinhsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project sinhsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/sinhsp//c66//sinhsp_66_LE_ELF"


#############################################################

# Rule to Build Project sinhsp_66_BE_ELF

#############################################################

.executables: src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out

.projects: src/sinhsp//c66//sinhsp_66_BE_ELF

src/sinhsp//c66//sinhsp_66_BE_ELF: src/sinhsp//c66//sinhsp_66_BE_ELF/.project

src/sinhsp//c66//sinhsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinhsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_ELF_SRCSINHSP/sinhsp_d.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinhsp//c66//sinhsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_ELF_SRCSINHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_ELF_SRCSINHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sinhsp//c66//sinhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINHSP_66_BE_ELF_SRCSINHSP=../../ >> src/sinhsp//c66//sinhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINHSP_66_BE_ELF_SRCSINHSPC66=.././ >> src/sinhsp//c66//sinhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINHSP_66_BE_ELF_SRCCOMMON=../../../common >> src/sinhsp//c66//sinhsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_BE_ELF"
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/sinhsp/sinhsp.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/sinhsp/sinhsp_d.c
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/sinhsp//c66/sinhsp.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/sinhsp//c66/sinhsp_i.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common/drvsp.c
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common/drvsp.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common/driver.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common/driver.c
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common/common.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common/tables.c
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/common//c66/common.h
src/sinhsp//c66//sinhsp_66_BE_ELF/Release/sinhsp_66_BE_ELF.out: src/sinhsp//c66//sinhsp_66_BE_ELF/.project
	-@ echo Importing Project sinhsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinhsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinhsp/c66/sinhsp_66_BE_ELF"
	-@ echo Building Project sinhsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinhsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project sinhsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinhsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/sinhsp//c66//sinhsp_66_BE_ELF"


#############################################################

# Rule to Build Project sinsp_66_LE_COFF

#############################################################

.executables: src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out

.projects: src/sinsp//c66//sinsp_66_LE_COFF

src/sinsp//c66//sinsp_66_LE_COFF: src/sinsp//c66//sinsp_66_LE_COFF/.project

src/sinsp//c66//sinsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_COFF_SRCSINSP/sinsp_d.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinsp//c66//sinsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_COFF_SRCSINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_COFF_SRCSINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sinsp//c66//sinsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINSP_66_LE_COFF_SRCSINSP=../../ >> src/sinsp//c66//sinsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINSP_66_LE_COFF_SRCSINSPC66=.././ >> src/sinsp//c66//sinsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SINSP_66_LE_COFF_SRCCOMMON=../../../common >> src/sinsp//c66//sinsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_LE_COFF"
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/sinsp/sinsp.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/sinsp/sinsp_d.c
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/sinsp//c66/sinsp.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/sinsp//c66/sinsp_i.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common/drvsp.c
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common/drvsp.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common/driver.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common/driver.c
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common/common.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common/tables.c
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/common//c66/common.h
src/sinsp//c66//sinsp_66_LE_COFF/Release/sinsp_66_LE_COFF.out: src/sinsp//c66//sinsp_66_LE_COFF/.project
	-@ echo Importing Project sinsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66/sinsp_66_LE_COFF"
	-@ echo Building Project sinsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project sinsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/sinsp//c66//sinsp_66_LE_COFF"


#############################################################

# Rule to Build Project sinsp_66_BE_COFF

#############################################################

.executables: src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out

.projects: src/sinsp//c66//sinsp_66_BE_COFF

src/sinsp//c66//sinsp_66_BE_COFF: src/sinsp//c66//sinsp_66_BE_COFF/.project

src/sinsp//c66//sinsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_COFF_SRCSINSP/sinsp_d.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinsp//c66//sinsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_COFF_SRCSINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_COFF_SRCSINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sinsp//c66//sinsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINSP_66_BE_COFF_SRCSINSP=../../ >> src/sinsp//c66//sinsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINSP_66_BE_COFF_SRCSINSPC66=.././ >> src/sinsp//c66//sinsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SINSP_66_BE_COFF_SRCCOMMON=../../../common >> src/sinsp//c66//sinsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_BE_COFF"
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/sinsp/sinsp.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/sinsp/sinsp_d.c
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/sinsp//c66/sinsp.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/sinsp//c66/sinsp_i.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common/drvsp.c
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common/drvsp.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common/driver.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common/driver.c
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common/common.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common/tables.c
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/common//c66/common.h
src/sinsp//c66//sinsp_66_BE_COFF/Release/sinsp_66_BE_COFF.out: src/sinsp//c66//sinsp_66_BE_COFF/.project
	-@ echo Importing Project sinsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66/sinsp_66_BE_COFF"
	-@ echo Building Project sinsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project sinsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/sinsp//c66//sinsp_66_BE_COFF"


#############################################################

# Rule to Build Project sinsp_66_LE_ELF

#############################################################

.executables: src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out

.projects: src/sinsp//c66//sinsp_66_LE_ELF

src/sinsp//c66//sinsp_66_LE_ELF: src/sinsp//c66//sinsp_66_LE_ELF/.project

src/sinsp//c66//sinsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_ELF_SRCSINSP/sinsp_d.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinsp//c66//sinsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_ELF_SRCSINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_ELF_SRCSINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sinsp//c66//sinsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINSP_66_LE_ELF_SRCSINSP=../../ >> src/sinsp//c66//sinsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINSP_66_LE_ELF_SRCSINSPC66=.././ >> src/sinsp//c66//sinsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SINSP_66_LE_ELF_SRCCOMMON=../../../common >> src/sinsp//c66//sinsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_LE_ELF"
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/sinsp/sinsp.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/sinsp/sinsp_d.c
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/sinsp//c66/sinsp.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/sinsp//c66/sinsp_i.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common/drvsp.c
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common/drvsp.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common/driver.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common/driver.c
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common/common.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common/tables.c
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/common//c66/common.h
src/sinsp//c66//sinsp_66_LE_ELF/Release/sinsp_66_LE_ELF.out: src/sinsp//c66//sinsp_66_LE_ELF/.project
	-@ echo Importing Project sinsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66/sinsp_66_LE_ELF"
	-@ echo Building Project sinsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project sinsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/sinsp//c66//sinsp_66_LE_ELF"


#############################################################

# Rule to Build Project sinsp_66_BE_ELF

#############################################################

.executables: src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out

.projects: src/sinsp//c66//sinsp_66_BE_ELF

src/sinsp//c66//sinsp_66_BE_ELF: src/sinsp//c66//sinsp_66_BE_ELF/.project

src/sinsp//c66//sinsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sinsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_ELF_SRCSINSP/sinsp_d.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sinsp//c66//sinsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_ELF_SRCSINSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_ELF_SRCSINSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sinsp//c66//sinsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINSP_66_BE_ELF_SRCSINSP=../../ >> src/sinsp//c66//sinsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINSP_66_BE_ELF_SRCSINSPC66=.././ >> src/sinsp//c66//sinsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SINSP_66_BE_ELF_SRCCOMMON=../../../common >> src/sinsp//c66//sinsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_BE_ELF"
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/sinsp/sinsp.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/sinsp/sinsp_d.c
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/sinsp//c66/sinsp.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/sinsp//c66/sinsp_i.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common/drvsp.c
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common/drvsp.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common/driver.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common/driver.c
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common/common.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common/tables.c
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/common//c66/common.h
src/sinsp//c66//sinsp_66_BE_ELF/Release/sinsp_66_BE_ELF.out: src/sinsp//c66//sinsp_66_BE_ELF/.project
	-@ echo Importing Project sinsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sinsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sinsp/c66/sinsp_66_BE_ELF"
	-@ echo Building Project sinsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sinsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sinsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project sinsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sinsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/sinsp//c66//sinsp_66_BE_ELF"


#############################################################

# Rule to Build Project sqrtdp_66_LE_COFF

#############################################################

.executables: src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out

.projects: src/sqrtdp//c66//sqrtdp_66_LE_COFF

src/sqrtdp//c66//sqrtdp_66_LE_COFF: src/sqrtdp//c66//sqrtdp_66_LE_COFF/.project

src/sqrtdp//c66//sqrtdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_COFF_SRCSQRTDP/sqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtdp//c66//sqrtdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_COFF_SRCSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_COFF_SRCSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sqrtdp//c66//sqrtdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SQRTDP_66_LE_COFF_SRCSQRTDP=../../ >> src/sqrtdp//c66//sqrtdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SQRTDP_66_LE_COFF_SRCSQRTDPC66=.././ >> src/sqrtdp//c66//sqrtdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SQRTDP_66_LE_COFF_SRCCOMMON=../../../common >> src/sqrtdp//c66//sqrtdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_LE_COFF"
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/sqrtdp/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/sqrtdp/sqrtdp_d.c
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/sqrtdp//c66/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/sqrtdp//c66/sqrtdp_i.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common/drvdp.c
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common/drvdp.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common/driver.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common/driver.c
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common/common.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common/tables.c
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/common//c66/common.h
src/sqrtdp//c66//sqrtdp_66_LE_COFF/Release/sqrtdp_66_LE_COFF.out: src/sqrtdp//c66//sqrtdp_66_LE_COFF/.project
	-@ echo Importing Project sqrtdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66/sqrtdp_66_LE_COFF"
	-@ echo Building Project sqrtdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project sqrtdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/sqrtdp//c66//sqrtdp_66_LE_COFF"


#############################################################

# Rule to Build Project sqrtdp_66_BE_COFF

#############################################################

.executables: src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out

.projects: src/sqrtdp//c66//sqrtdp_66_BE_COFF

src/sqrtdp//c66//sqrtdp_66_BE_COFF: src/sqrtdp//c66//sqrtdp_66_BE_COFF/.project

src/sqrtdp//c66//sqrtdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_COFF_SRCSQRTDP/sqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtdp//c66//sqrtdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_COFF_SRCSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_COFF_SRCSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sqrtdp//c66//sqrtdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SQRTDP_66_BE_COFF_SRCSQRTDP=../../ >> src/sqrtdp//c66//sqrtdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SQRTDP_66_BE_COFF_SRCSQRTDPC66=.././ >> src/sqrtdp//c66//sqrtdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SQRTDP_66_BE_COFF_SRCCOMMON=../../../common >> src/sqrtdp//c66//sqrtdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_BE_COFF"
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/sqrtdp/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/sqrtdp/sqrtdp_d.c
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/sqrtdp//c66/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/sqrtdp//c66/sqrtdp_i.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common/drvdp.c
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common/drvdp.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common/driver.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common/driver.c
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common/common.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common/tables.c
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/common//c66/common.h
src/sqrtdp//c66//sqrtdp_66_BE_COFF/Release/sqrtdp_66_BE_COFF.out: src/sqrtdp//c66//sqrtdp_66_BE_COFF/.project
	-@ echo Importing Project sqrtdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66/sqrtdp_66_BE_COFF"
	-@ echo Building Project sqrtdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project sqrtdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/sqrtdp//c66//sqrtdp_66_BE_COFF"


#############################################################

# Rule to Build Project sqrtdp_66_LE_ELF

#############################################################

.executables: src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out

.projects: src/sqrtdp//c66//sqrtdp_66_LE_ELF

src/sqrtdp//c66//sqrtdp_66_LE_ELF: src/sqrtdp//c66//sqrtdp_66_LE_ELF/.project

src/sqrtdp//c66//sqrtdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_ELF_SRCSQRTDP/sqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtdp//c66//sqrtdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_ELF_SRCSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_ELF_SRCSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sqrtdp//c66//sqrtdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SQRTDP_66_LE_ELF_SRCSQRTDP=../../ >> src/sqrtdp//c66//sqrtdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SQRTDP_66_LE_ELF_SRCSQRTDPC66=.././ >> src/sqrtdp//c66//sqrtdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SQRTDP_66_LE_ELF_SRCCOMMON=../../../common >> src/sqrtdp//c66//sqrtdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_LE_ELF"
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/sqrtdp/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/sqrtdp/sqrtdp_d.c
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/sqrtdp//c66/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/sqrtdp//c66/sqrtdp_i.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common/drvdp.c
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common/drvdp.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common/driver.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common/driver.c
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common/common.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common/tables.c
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/common//c66/common.h
src/sqrtdp//c66//sqrtdp_66_LE_ELF/Release/sqrtdp_66_LE_ELF.out: src/sqrtdp//c66//sqrtdp_66_LE_ELF/.project
	-@ echo Importing Project sqrtdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66/sqrtdp_66_LE_ELF"
	-@ echo Building Project sqrtdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project sqrtdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/sqrtdp//c66//sqrtdp_66_LE_ELF"


#############################################################

# Rule to Build Project sqrtdp_66_BE_ELF

#############################################################

.executables: src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out

.projects: src/sqrtdp//c66//sqrtdp_66_BE_ELF

src/sqrtdp//c66//sqrtdp_66_BE_ELF: src/sqrtdp//c66//sqrtdp_66_BE_ELF/.project

src/sqrtdp//c66//sqrtdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_ELF_SRCSQRTDP/sqrtdp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtdp//c66//sqrtdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_ELF_SRCSQRTDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_ELF_SRCSQRTDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sqrtdp//c66//sqrtdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SQRTDP_66_BE_ELF_SRCSQRTDP=../../ >> src/sqrtdp//c66//sqrtdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SQRTDP_66_BE_ELF_SRCSQRTDPC66=.././ >> src/sqrtdp//c66//sqrtdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SQRTDP_66_BE_ELF_SRCCOMMON=../../../common >> src/sqrtdp//c66//sqrtdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_BE_ELF"
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/sqrtdp/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/sqrtdp/sqrtdp_d.c
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/sqrtdp//c66/sqrtdp.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/sqrtdp//c66/sqrtdp_i.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common/drvdp.c
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common/drvdp.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common/driver.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common/driver.c
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common/common.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common/tables.c
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/common//c66/common.h
src/sqrtdp//c66//sqrtdp_66_BE_ELF/Release/sqrtdp_66_BE_ELF.out: src/sqrtdp//c66//sqrtdp_66_BE_ELF/.project
	-@ echo Importing Project sqrtdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtdp/c66/sqrtdp_66_BE_ELF"
	-@ echo Building Project sqrtdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project sqrtdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/sqrtdp//c66//sqrtdp_66_BE_ELF"


#############################################################

# Rule to Build Project sqrtsp_66_LE_COFF

#############################################################

.executables: src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out

.projects: src/sqrtsp//c66//sqrtsp_66_LE_COFF

src/sqrtsp//c66//sqrtsp_66_LE_COFF: src/sqrtsp//c66//sqrtsp_66_LE_COFF/.project

src/sqrtsp//c66//sqrtsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_COFF_SRCSQRTSP/sqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtsp//c66//sqrtsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_COFF_SRCSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_COFF_SRCSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sqrtsp//c66//sqrtsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SQRTSP_66_LE_COFF_SRCSQRTSP=../../ >> src/sqrtsp//c66//sqrtsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SQRTSP_66_LE_COFF_SRCSQRTSPC66=.././ >> src/sqrtsp//c66//sqrtsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__SQRTSP_66_LE_COFF_SRCCOMMON=../../../common >> src/sqrtsp//c66//sqrtsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_LE_COFF"
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/sqrtsp/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/sqrtsp/sqrtsp_d.c
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/sqrtsp//c66/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/sqrtsp//c66/sqrtsp_i.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common/drvsp.c
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common/drvsp.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common/driver.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common/driver.c
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common/common.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common/tables.c
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/common//c66/common.h
src/sqrtsp//c66//sqrtsp_66_LE_COFF/Release/sqrtsp_66_LE_COFF.out: src/sqrtsp//c66//sqrtsp_66_LE_COFF/.project
	-@ echo Importing Project sqrtsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66/sqrtsp_66_LE_COFF"
	-@ echo Building Project sqrtsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project sqrtsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/sqrtsp//c66//sqrtsp_66_LE_COFF"


#############################################################

# Rule to Build Project sqrtsp_66_BE_COFF

#############################################################

.executables: src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out

.projects: src/sqrtsp//c66//sqrtsp_66_BE_COFF

src/sqrtsp//c66//sqrtsp_66_BE_COFF: src/sqrtsp//c66//sqrtsp_66_BE_COFF/.project

src/sqrtsp//c66//sqrtsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_COFF_SRCSQRTSP/sqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtsp//c66//sqrtsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_COFF_SRCSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_COFF_SRCSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/sqrtsp//c66//sqrtsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SQRTSP_66_BE_COFF_SRCSQRTSP=../../ >> src/sqrtsp//c66//sqrtsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SQRTSP_66_BE_COFF_SRCSQRTSPC66=.././ >> src/sqrtsp//c66//sqrtsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__SQRTSP_66_BE_COFF_SRCCOMMON=../../../common >> src/sqrtsp//c66//sqrtsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_BE_COFF"
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/sqrtsp/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/sqrtsp/sqrtsp_d.c
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/sqrtsp//c66/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/sqrtsp//c66/sqrtsp_i.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common/drvsp.c
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common/drvsp.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common/driver.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common/driver.c
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common/common.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common/tables.c
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/common//c66/common.h
src/sqrtsp//c66//sqrtsp_66_BE_COFF/Release/sqrtsp_66_BE_COFF.out: src/sqrtsp//c66//sqrtsp_66_BE_COFF/.project
	-@ echo Importing Project sqrtsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66/sqrtsp_66_BE_COFF"
	-@ echo Building Project sqrtsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project sqrtsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/sqrtsp//c66//sqrtsp_66_BE_COFF"


#############################################################

# Rule to Build Project sqrtsp_66_LE_ELF

#############################################################

.executables: src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out

.projects: src/sqrtsp//c66//sqrtsp_66_LE_ELF

src/sqrtsp//c66//sqrtsp_66_LE_ELF: src/sqrtsp//c66//sqrtsp_66_LE_ELF/.project

src/sqrtsp//c66//sqrtsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_ELF_SRCSQRTSP/sqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtsp//c66//sqrtsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_ELF_SRCSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_ELF_SRCSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sqrtsp//c66//sqrtsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SQRTSP_66_LE_ELF_SRCSQRTSP=../../ >> src/sqrtsp//c66//sqrtsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SQRTSP_66_LE_ELF_SRCSQRTSPC66=.././ >> src/sqrtsp//c66//sqrtsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__SQRTSP_66_LE_ELF_SRCCOMMON=../../../common >> src/sqrtsp//c66//sqrtsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_LE_ELF"
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/sqrtsp/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/sqrtsp/sqrtsp_d.c
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/sqrtsp//c66/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/sqrtsp//c66/sqrtsp_i.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common/drvsp.c
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common/drvsp.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common/driver.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common/driver.c
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common/common.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common/tables.c
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/common//c66/common.h
src/sqrtsp//c66//sqrtsp_66_LE_ELF/Release/sqrtsp_66_LE_ELF.out: src/sqrtsp//c66//sqrtsp_66_LE_ELF/.project
	-@ echo Importing Project sqrtsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66/sqrtsp_66_LE_ELF"
	-@ echo Building Project sqrtsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project sqrtsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/sqrtsp//c66//sqrtsp_66_LE_ELF"


#############################################################

# Rule to Build Project sqrtsp_66_BE_ELF

#############################################################

.executables: src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out

.projects: src/sqrtsp//c66//sqrtsp_66_BE_ELF

src/sqrtsp//c66//sqrtsp_66_BE_ELF: src/sqrtsp//c66//sqrtsp_66_BE_ELF/.project

src/sqrtsp//c66//sqrtsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name sqrtsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_ELF_SRCSQRTSP/sqrtsp_d.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/sqrtsp//c66//sqrtsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_ELF_SRCSQRTSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_ELF_SRCSQRTSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66" \
 -ccs.definePathVariable EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/sqrtsp//c66//sqrtsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SQRTSP_66_BE_ELF_SRCSQRTSP=../../ >> src/sqrtsp//c66//sqrtsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SQRTSP_66_BE_ELF_SRCSQRTSPC66=.././ >> src/sqrtsp//c66//sqrtsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__SQRTSP_66_BE_ELF_SRCCOMMON=../../../common >> src/sqrtsp//c66//sqrtsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_BE_ELF"
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/sqrtsp/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/sqrtsp/sqrtsp_d.c
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/sqrtsp//c66/sqrtsp.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/sqrtsp//c66/sqrtsp_i.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common/drvsp.c
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common/drvsp.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common/driver.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common/driver.c
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common/common.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common/tables.c
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/common//c66/common.h
src/sqrtsp//c66//sqrtsp_66_BE_ELF/Release/sqrtsp_66_BE_ELF.out: src/sqrtsp//c66//sqrtsp_66_BE_ELF/.project
	-@ echo Importing Project sqrtsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects sqrtsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/sqrtsp/c66/sqrtsp_66_BE_ELF"
	-@ echo Building Project sqrtsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/sqrtsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects sqrtsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project sqrtsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/sqrtsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/sqrtsp//c66//sqrtsp_66_BE_ELF"


#############################################################

# Rule to Build Project tandp_66_LE_COFF

#############################################################

.executables: src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out

.projects: src/tandp//c66//tandp_66_LE_COFF

src/tandp//c66//tandp_66_LE_COFF: src/tandp//c66//tandp_66_LE_COFF/.project

src/tandp//c66//tandp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tandp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_COFF_SRCTANDP/tandp_d.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tandp//c66//tandp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_COFF_SRCTANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_COFF_SRCTANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tandp//c66//tandp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANDP_66_LE_COFF_SRCTANDP=../../ >> src/tandp//c66//tandp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANDP_66_LE_COFF_SRCTANDPC66=.././ >> src/tandp//c66//tandp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANDP_66_LE_COFF_SRCCOMMON=../../../common >> src/tandp//c66//tandp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tandp_66_LE_COFF"
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/tandp/tandp.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/tandp/tandp_d.c
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/tandp//c66/tandp.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/tandp//c66/tandp_i.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common/drvdp.c
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common/drvdp.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common/driver.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common/driver.c
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common/common.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common/tables.c
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/common//c66/common.h
src/tandp//c66//tandp_66_LE_COFF/Release/tandp_66_LE_COFF.out: src/tandp//c66//tandp_66_LE_COFF/.project
	-@ echo Importing Project tandp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tandp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66/tandp_66_LE_COFF"
	-@ echo Building Project tandp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tandp_66_LE_COFF -ccs.configuration Release
	-@ echo Project tandp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tandp_66_LE_COFF"

clean::
	-$(RMDIR) "src/tandp//c66//tandp_66_LE_COFF"


#############################################################

# Rule to Build Project tandp_66_BE_COFF

#############################################################

.executables: src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out

.projects: src/tandp//c66//tandp_66_BE_COFF

src/tandp//c66//tandp_66_BE_COFF: src/tandp//c66//tandp_66_BE_COFF/.project

src/tandp//c66//tandp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tandp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_COFF_SRCTANDP/tandp_d.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tandp//c66//tandp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_COFF_SRCTANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_COFF_SRCTANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tandp//c66//tandp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANDP_66_BE_COFF_SRCTANDP=../../ >> src/tandp//c66//tandp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANDP_66_BE_COFF_SRCTANDPC66=.././ >> src/tandp//c66//tandp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANDP_66_BE_COFF_SRCCOMMON=../../../common >> src/tandp//c66//tandp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tandp_66_BE_COFF"
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/tandp/tandp.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/tandp/tandp_d.c
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/tandp//c66/tandp.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/tandp//c66/tandp_i.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common/drvdp.c
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common/drvdp.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common/driver.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common/driver.c
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common/common.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common/tables.c
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/common//c66/common.h
src/tandp//c66//tandp_66_BE_COFF/Release/tandp_66_BE_COFF.out: src/tandp//c66//tandp_66_BE_COFF/.project
	-@ echo Importing Project tandp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tandp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66/tandp_66_BE_COFF"
	-@ echo Building Project tandp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tandp_66_BE_COFF -ccs.configuration Release
	-@ echo Project tandp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tandp_66_BE_COFF"

clean::
	-$(RMDIR) "src/tandp//c66//tandp_66_BE_COFF"


#############################################################

# Rule to Build Project tandp_66_LE_ELF

#############################################################

.executables: src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out

.projects: src/tandp//c66//tandp_66_LE_ELF

src/tandp//c66//tandp_66_LE_ELF: src/tandp//c66//tandp_66_LE_ELF/.project

src/tandp//c66//tandp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tandp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_ELF_SRCTANDP/tandp_d.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tandp//c66//tandp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_ELF_SRCTANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_ELF_SRCTANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tandp//c66//tandp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANDP_66_LE_ELF_SRCTANDP=../../ >> src/tandp//c66//tandp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANDP_66_LE_ELF_SRCTANDPC66=.././ >> src/tandp//c66//tandp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANDP_66_LE_ELF_SRCCOMMON=../../../common >> src/tandp//c66//tandp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tandp_66_LE_ELF"
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/tandp/tandp.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/tandp/tandp_d.c
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/tandp//c66/tandp.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/tandp//c66/tandp_i.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common/drvdp.c
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common/drvdp.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common/driver.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common/driver.c
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common/common.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common/tables.c
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/common//c66/common.h
src/tandp//c66//tandp_66_LE_ELF/Release/tandp_66_LE_ELF.out: src/tandp//c66//tandp_66_LE_ELF/.project
	-@ echo Importing Project tandp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tandp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66/tandp_66_LE_ELF"
	-@ echo Building Project tandp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tandp_66_LE_ELF -ccs.configuration Release
	-@ echo Project tandp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tandp_66_LE_ELF"

clean::
	-$(RMDIR) "src/tandp//c66//tandp_66_LE_ELF"


#############################################################

# Rule to Build Project tandp_66_BE_ELF

#############################################################

.executables: src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out

.projects: src/tandp//c66//tandp_66_BE_ELF

src/tandp//c66//tandp_66_BE_ELF: src/tandp//c66//tandp_66_BE_ELF/.project

src/tandp//c66//tandp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tandp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_ELF_SRCTANDP/tandp_d.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tandp//c66//tandp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_ELF_SRCTANDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_ELF_SRCTANDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tandp//c66//tandp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANDP_66_BE_ELF_SRCTANDP=../../ >> src/tandp//c66//tandp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANDP_66_BE_ELF_SRCTANDPC66=.././ >> src/tandp//c66//tandp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANDP_66_BE_ELF_SRCCOMMON=../../../common >> src/tandp//c66//tandp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tandp_66_BE_ELF"
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/tandp/tandp.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/tandp/tandp_d.c
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/tandp//c66/tandp.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/tandp//c66/tandp_i.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common/drvdp.c
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common/drvdp.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common/driver.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common/driver.c
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common/common.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common/tables.c
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/common//c66/common.h
src/tandp//c66//tandp_66_BE_ELF/Release/tandp_66_BE_ELF.out: src/tandp//c66//tandp_66_BE_ELF/.project
	-@ echo Importing Project tandp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tandp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tandp/c66/tandp_66_BE_ELF"
	-@ echo Building Project tandp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tandp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tandp_66_BE_ELF -ccs.configuration Release
	-@ echo Project tandp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tandp_66_BE_ELF"

clean::
	-$(RMDIR) "src/tandp//c66//tandp_66_BE_ELF"


#############################################################

# Rule to Build Project tanhdp_66_LE_COFF

#############################################################

.executables: src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out

.projects: src/tanhdp//c66//tanhdp_66_LE_COFF

src/tanhdp//c66//tanhdp_66_LE_COFF: src/tanhdp//c66//tanhdp_66_LE_COFF/.project

src/tanhdp//c66//tanhdp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhdp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_COFF_SRCTANHDP/tanhdp_d.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhdp//c66//tanhdp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_COFF_SRCTANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_COFF_SRCTANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tanhdp//c66//tanhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANHDP_66_LE_COFF_SRCTANHDP=../../ >> src/tanhdp//c66//tanhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANHDP_66_LE_COFF_SRCTANHDPC66=.././ >> src/tanhdp//c66//tanhdp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANHDP_66_LE_COFF_SRCCOMMON=../../../common >> src/tanhdp//c66//tanhdp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_LE_COFF"
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/tanhdp/tanhdp.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/tanhdp/tanhdp_d.c
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/tanhdp//c66/tanhdp.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/tanhdp//c66/tanhdp_i.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common/drvdp.c
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common/drvdp.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common/driver.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common/driver.c
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common/common.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common/tables.c
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/common//c66/common.h
src/tanhdp//c66//tanhdp_66_LE_COFF/Release/tanhdp_66_LE_COFF.out: src/tanhdp//c66//tanhdp_66_LE_COFF/.project
	-@ echo Importing Project tanhdp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhdp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66/tanhdp_66_LE_COFF"
	-@ echo Building Project tanhdp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhdp_66_LE_COFF -ccs.configuration Release
	-@ echo Project tanhdp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_LE_COFF"

clean::
	-$(RMDIR) "src/tanhdp//c66//tanhdp_66_LE_COFF"


#############################################################

# Rule to Build Project tanhdp_66_BE_COFF

#############################################################

.executables: src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out

.projects: src/tanhdp//c66//tanhdp_66_BE_COFF

src/tanhdp//c66//tanhdp_66_BE_COFF: src/tanhdp//c66//tanhdp_66_BE_COFF/.project

src/tanhdp//c66//tanhdp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhdp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_COFF_SRCTANHDP/tanhdp_d.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhdp//c66//tanhdp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_COFF_SRCTANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_COFF_SRCTANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tanhdp//c66//tanhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANHDP_66_BE_COFF_SRCTANHDP=../../ >> src/tanhdp//c66//tanhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANHDP_66_BE_COFF_SRCTANHDPC66=.././ >> src/tanhdp//c66//tanhdp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANHDP_66_BE_COFF_SRCCOMMON=../../../common >> src/tanhdp//c66//tanhdp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_BE_COFF"
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/tanhdp/tanhdp.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/tanhdp/tanhdp_d.c
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/tanhdp//c66/tanhdp.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/tanhdp//c66/tanhdp_i.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common/drvdp.c
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common/drvdp.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common/driver.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common/driver.c
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common/common.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common/tables.c
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/common//c66/common.h
src/tanhdp//c66//tanhdp_66_BE_COFF/Release/tanhdp_66_BE_COFF.out: src/tanhdp//c66//tanhdp_66_BE_COFF/.project
	-@ echo Importing Project tanhdp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhdp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66/tanhdp_66_BE_COFF"
	-@ echo Building Project tanhdp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhdp_66_BE_COFF -ccs.configuration Release
	-@ echo Project tanhdp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_BE_COFF"

clean::
	-$(RMDIR) "src/tanhdp//c66//tanhdp_66_BE_COFF"


#############################################################

# Rule to Build Project tanhdp_66_LE_ELF

#############################################################

.executables: src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out

.projects: src/tanhdp//c66//tanhdp_66_LE_ELF

src/tanhdp//c66//tanhdp_66_LE_ELF: src/tanhdp//c66//tanhdp_66_LE_ELF/.project

src/tanhdp//c66//tanhdp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhdp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_ELF_SRCTANHDP/tanhdp_d.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhdp//c66//tanhdp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_ELF_SRCTANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_ELF_SRCTANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tanhdp//c66//tanhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANHDP_66_LE_ELF_SRCTANHDP=../../ >> src/tanhdp//c66//tanhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANHDP_66_LE_ELF_SRCTANHDPC66=.././ >> src/tanhdp//c66//tanhdp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANHDP_66_LE_ELF_SRCCOMMON=../../../common >> src/tanhdp//c66//tanhdp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_LE_ELF"
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/tanhdp/tanhdp.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/tanhdp/tanhdp_d.c
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/tanhdp//c66/tanhdp.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/tanhdp//c66/tanhdp_i.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common/drvdp.c
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common/drvdp.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common/driver.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common/driver.c
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common/common.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common/tables.c
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/common//c66/common.h
src/tanhdp//c66//tanhdp_66_LE_ELF/Release/tanhdp_66_LE_ELF.out: src/tanhdp//c66//tanhdp_66_LE_ELF/.project
	-@ echo Importing Project tanhdp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhdp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66/tanhdp_66_LE_ELF"
	-@ echo Building Project tanhdp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhdp_66_LE_ELF -ccs.configuration Release
	-@ echo Project tanhdp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_LE_ELF"

clean::
	-$(RMDIR) "src/tanhdp//c66//tanhdp_66_LE_ELF"


#############################################################

# Rule to Build Project tanhdp_66_BE_ELF

#############################################################

.executables: src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out

.projects: src/tanhdp//c66//tanhdp_66_BE_ELF

src/tanhdp//c66//tanhdp_66_BE_ELF: src/tanhdp//c66//tanhdp_66_BE_ELF/.project

src/tanhdp//c66//tanhdp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhdp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_ELF_SRCTANHDP/tanhdp_d.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMON/drvdp.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhdp//c66//tanhdp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_ELF_SRCTANHDP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_ELF_SRCTANHDPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tanhdp//c66//tanhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANHDP_66_BE_ELF_SRCTANHDP=../../ >> src/tanhdp//c66//tanhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANHDP_66_BE_ELF_SRCTANHDPC66=.././ >> src/tanhdp//c66//tanhdp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANHDP_66_BE_ELF_SRCCOMMON=../../../common >> src/tanhdp//c66//tanhdp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_BE_ELF"
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/tanhdp/tanhdp.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/tanhdp/tanhdp_d.c
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/tanhdp//c66/tanhdp.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/tanhdp//c66/tanhdp_i.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common/drvdp.c
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common/drvdp.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common/driver.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common/driver.c
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common/common.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common/tables.c
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/common//c66/common.h
src/tanhdp//c66//tanhdp_66_BE_ELF/Release/tanhdp_66_BE_ELF.out: src/tanhdp//c66//tanhdp_66_BE_ELF/.project
	-@ echo Importing Project tanhdp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhdp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhdp/c66/tanhdp_66_BE_ELF"
	-@ echo Building Project tanhdp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhdp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhdp_66_BE_ELF -ccs.configuration Release
	-@ echo Project tanhdp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhdp_66_BE_ELF"

clean::
	-$(RMDIR) "src/tanhdp//c66//tanhdp_66_BE_ELF"


#############################################################

# Rule to Build Project tanhsp_66_LE_COFF

#############################################################

.executables: src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out

.projects: src/tanhsp//c66//tanhsp_66_LE_COFF

src/tanhsp//c66//tanhsp_66_LE_COFF: src/tanhsp//c66//tanhsp_66_LE_COFF/.project

src/tanhsp//c66//tanhsp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhsp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_COFF_SRCTANHSP/tanhsp_d.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhsp//c66//tanhsp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_COFF_SRCTANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_COFF_SRCTANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tanhsp//c66//tanhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANHSP_66_LE_COFF_SRCTANHSP=../../ >> src/tanhsp//c66//tanhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANHSP_66_LE_COFF_SRCTANHSPC66=.././ >> src/tanhsp//c66//tanhsp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANHSP_66_LE_COFF_SRCCOMMON=../../../common >> src/tanhsp//c66//tanhsp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_LE_COFF"
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/tanhsp/tanhsp.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/tanhsp/tanhsp_d.c
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/tanhsp//c66/tanhsp.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/tanhsp//c66/tanhsp_i.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common/drvsp.c
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common/drvsp.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common/driver.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common/driver.c
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common/common.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common/tables.c
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/common//c66/common.h
src/tanhsp//c66//tanhsp_66_LE_COFF/Release/tanhsp_66_LE_COFF.out: src/tanhsp//c66//tanhsp_66_LE_COFF/.project
	-@ echo Importing Project tanhsp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhsp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66/tanhsp_66_LE_COFF"
	-@ echo Building Project tanhsp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhsp_66_LE_COFF -ccs.configuration Release
	-@ echo Project tanhsp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_LE_COFF"

clean::
	-$(RMDIR) "src/tanhsp//c66//tanhsp_66_LE_COFF"


#############################################################

# Rule to Build Project tanhsp_66_BE_COFF

#############################################################

.executables: src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out

.projects: src/tanhsp//c66//tanhsp_66_BE_COFF

src/tanhsp//c66//tanhsp_66_BE_COFF: src/tanhsp//c66//tanhsp_66_BE_COFF/.project

src/tanhsp//c66//tanhsp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhsp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_COFF_SRCTANHSP/tanhsp_d.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhsp//c66//tanhsp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_COFF_SRCTANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_COFF_SRCTANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tanhsp//c66//tanhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANHSP_66_BE_COFF_SRCTANHSP=../../ >> src/tanhsp//c66//tanhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANHSP_66_BE_COFF_SRCTANHSPC66=.././ >> src/tanhsp//c66//tanhsp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANHSP_66_BE_COFF_SRCCOMMON=../../../common >> src/tanhsp//c66//tanhsp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_BE_COFF"
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/tanhsp/tanhsp.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/tanhsp/tanhsp_d.c
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/tanhsp//c66/tanhsp.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/tanhsp//c66/tanhsp_i.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common/drvsp.c
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common/drvsp.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common/driver.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common/driver.c
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common/common.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common/tables.c
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/common//c66/common.h
src/tanhsp//c66//tanhsp_66_BE_COFF/Release/tanhsp_66_BE_COFF.out: src/tanhsp//c66//tanhsp_66_BE_COFF/.project
	-@ echo Importing Project tanhsp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhsp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66/tanhsp_66_BE_COFF"
	-@ echo Building Project tanhsp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhsp_66_BE_COFF -ccs.configuration Release
	-@ echo Project tanhsp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_BE_COFF"

clean::
	-$(RMDIR) "src/tanhsp//c66//tanhsp_66_BE_COFF"


#############################################################

# Rule to Build Project tanhsp_66_LE_ELF

#############################################################

.executables: src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out

.projects: src/tanhsp//c66//tanhsp_66_LE_ELF

src/tanhsp//c66//tanhsp_66_LE_ELF: src/tanhsp//c66//tanhsp_66_LE_ELF/.project

src/tanhsp//c66//tanhsp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhsp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_ELF_SRCTANHSP/tanhsp_d.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhsp//c66//tanhsp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_ELF_SRCTANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_ELF_SRCTANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tanhsp//c66//tanhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANHSP_66_LE_ELF_SRCTANHSP=../../ >> src/tanhsp//c66//tanhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANHSP_66_LE_ELF_SRCTANHSPC66=.././ >> src/tanhsp//c66//tanhsp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANHSP_66_LE_ELF_SRCCOMMON=../../../common >> src/tanhsp//c66//tanhsp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_LE_ELF"
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/tanhsp/tanhsp.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/tanhsp/tanhsp_d.c
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/tanhsp//c66/tanhsp.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/tanhsp//c66/tanhsp_i.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common/drvsp.c
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common/drvsp.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common/driver.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common/driver.c
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common/common.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common/tables.c
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/common//c66/common.h
src/tanhsp//c66//tanhsp_66_LE_ELF/Release/tanhsp_66_LE_ELF.out: src/tanhsp//c66//tanhsp_66_LE_ELF/.project
	-@ echo Importing Project tanhsp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhsp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66/tanhsp_66_LE_ELF"
	-@ echo Building Project tanhsp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhsp_66_LE_ELF -ccs.configuration Release
	-@ echo Project tanhsp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_LE_ELF"

clean::
	-$(RMDIR) "src/tanhsp//c66//tanhsp_66_LE_ELF"


#############################################################

# Rule to Build Project tanhsp_66_BE_ELF

#############################################################

.executables: src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out

.projects: src/tanhsp//c66//tanhsp_66_BE_ELF

src/tanhsp//c66//tanhsp_66_BE_ELF: src/tanhsp//c66//tanhsp_66_BE_ELF/.project

src/tanhsp//c66//tanhsp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tanhsp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_ELF_SRCTANHSP/tanhsp_d.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tanhsp//c66//tanhsp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_ELF_SRCTANHSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_ELF_SRCTANHSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tanhsp//c66//tanhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANHSP_66_BE_ELF_SRCTANHSP=../../ >> src/tanhsp//c66//tanhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANHSP_66_BE_ELF_SRCTANHSPC66=.././ >> src/tanhsp//c66//tanhsp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANHSP_66_BE_ELF_SRCCOMMON=../../../common >> src/tanhsp//c66//tanhsp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_BE_ELF"
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/tanhsp/tanhsp.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/tanhsp/tanhsp_d.c
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/tanhsp//c66/tanhsp.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/tanhsp//c66/tanhsp_i.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common/drvsp.c
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common/drvsp.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common/driver.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common/driver.c
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common/common.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common/tables.c
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/common//c66/common.h
src/tanhsp//c66//tanhsp_66_BE_ELF/Release/tanhsp_66_BE_ELF.out: src/tanhsp//c66//tanhsp_66_BE_ELF/.project
	-@ echo Importing Project tanhsp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tanhsp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tanhsp/c66/tanhsp_66_BE_ELF"
	-@ echo Building Project tanhsp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tanhsp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tanhsp_66_BE_ELF -ccs.configuration Release
	-@ echo Project tanhsp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tanhsp_66_BE_ELF"

clean::
	-$(RMDIR) "src/tanhsp//c66//tanhsp_66_BE_ELF"


#############################################################

# Rule to Build Project tansp_66_LE_COFF

#############################################################

.executables: src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out

.projects: src/tansp//c66//tansp_66_LE_COFF

src/tansp//c66//tansp_66_LE_COFF: src/tansp//c66//tansp_66_LE_COFF/.project

src/tansp//c66//tansp_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tansp_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_COFF_SRCTANSP/tansp_d.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tansp//c66//tansp_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_COFF_SRCTANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_COFF_SRCTANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tansp//c66//tansp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANSP_66_LE_COFF_SRCTANSP=../../ >> src/tansp//c66//tansp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANSP_66_LE_COFF_SRCTANSPC66=.././ >> src/tansp//c66//tansp_66_LE_COFF/macros.ini
	echo EXT_ROOT__TANSP_66_LE_COFF_SRCCOMMON=../../../common >> src/tansp//c66//tansp_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tansp_66_LE_COFF"
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common//c66/lnk.cmd
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/tansp/tansp.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/tansp/tansp_d.c
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/tansp//c66/tansp.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/tansp//c66/tansp_i.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common/drvsp.c
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common/drvsp.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common/driver.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common/driver.c
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common/common.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common/tables.c
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/common//c66/common.h
src/tansp//c66//tansp_66_LE_COFF/Release/tansp_66_LE_COFF.out: src/tansp//c66//tansp_66_LE_COFF/.project
	-@ echo Importing Project tansp_66_LE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_LE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tansp_66_LE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66/tansp_66_LE_COFF"
	-@ echo Building Project tansp_66_LE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_LE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tansp_66_LE_COFF -ccs.configuration Release
	-@ echo Project tansp_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tansp_66_LE_COFF"

clean::
	-$(RMDIR) "src/tansp//c66//tansp_66_LE_COFF"


#############################################################

# Rule to Build Project tansp_66_BE_COFF

#############################################################

.executables: src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out

.projects: src/tansp//c66//tansp_66_BE_COFF

src/tansp//c66//tansp_66_BE_COFF: src/tansp//c66//tansp_66_BE_COFF/.project

src/tansp//c66//tansp_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tansp_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_COFF_SRCTANSP/tansp_d.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tansp//c66//tansp_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_COFF_SRCTANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_COFF_SRCTANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMONC66=../../../common/c66 >> src/tansp//c66//tansp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANSP_66_BE_COFF_SRCTANSP=../../ >> src/tansp//c66//tansp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANSP_66_BE_COFF_SRCTANSPC66=.././ >> src/tansp//c66//tansp_66_BE_COFF/macros.ini
	echo EXT_ROOT__TANSP_66_BE_COFF_SRCCOMMON=../../../common >> src/tansp//c66//tansp_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tansp_66_BE_COFF"
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common//c66/lnk.cmd
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/tansp/tansp.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/tansp/tansp_d.c
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/tansp//c66/tansp.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/tansp//c66/tansp_i.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common/drvsp.c
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common/drvsp.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common/driver.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common/driver.c
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common/common.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common/tables.c
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/common//c66/common.h
src/tansp//c66//tansp_66_BE_COFF/Release/tansp_66_BE_COFF.out: src/tansp//c66//tansp_66_BE_COFF/.project
	-@ echo Importing Project tansp_66_BE_COFF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_BE_COFF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tansp_66_BE_COFF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66/tansp_66_BE_COFF"
	-@ echo Building Project tansp_66_BE_COFF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_BE_COFF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tansp_66_BE_COFF -ccs.configuration Release
	-@ echo Project tansp_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tansp_66_BE_COFF"

clean::
	-$(RMDIR) "src/tansp//c66//tansp_66_BE_COFF"


#############################################################

# Rule to Build Project tansp_66_LE_ELF

#############################################################

.executables: src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out

.projects: src/tansp//c66//tansp_66_LE_ELF

src/tansp//c66//tansp_66_LE_ELF: src/tansp//c66//tansp_66_LE_ELF/.project

src/tansp//c66//tansp_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tansp_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_ELF_SRCTANSP/tansp_d.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tansp//c66//tansp_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_ELF_SRCTANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_ELF_SRCTANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tansp//c66//tansp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANSP_66_LE_ELF_SRCTANSP=../../ >> src/tansp//c66//tansp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANSP_66_LE_ELF_SRCTANSPC66=.././ >> src/tansp//c66//tansp_66_LE_ELF/macros.ini
	echo EXT_ROOT__TANSP_66_LE_ELF_SRCCOMMON=../../../common >> src/tansp//c66//tansp_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tansp_66_LE_ELF"
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common//c66/lnk.cmd
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/tansp/tansp.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/tansp/tansp_d.c
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/tansp//c66/tansp.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/tansp//c66/tansp_i.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common/drvsp.c
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common/drvsp.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common/driver.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common/driver.c
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common/common.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common/tables.c
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/common//c66/common.h
src/tansp//c66//tansp_66_LE_ELF/Release/tansp_66_LE_ELF.out: src/tansp//c66//tansp_66_LE_ELF/.project
	-@ echo Importing Project tansp_66_LE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_LE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tansp_66_LE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66/tansp_66_LE_ELF"
	-@ echo Building Project tansp_66_LE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_LE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tansp_66_LE_ELF -ccs.configuration Release
	-@ echo Project tansp_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tansp_66_LE_ELF"

clean::
	-$(RMDIR) "src/tansp//c66//tansp_66_LE_ELF"


#############################################################

# Rule to Build Project tansp_66_BE_ELF

#############################################################

.executables: src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out

.projects: src/tansp//c66//tansp_66_BE_ELF

src/tansp//c66//tansp_66_BE_ELF: src/tansp//c66//tansp_66_BE_ELF/.project

src/tansp//c66//tansp_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name tansp_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_ELF_SRCTANSP/tansp_d.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMON/drvsp.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMON/driver.c\
 -ccs.linkFile EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMON/tables.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -g  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -o3 --symdebug:none  -i../../../../../../../ -i../../../../common/c66 -i../../../ -i../../ -i../../../../common" @configurations Release -ccs.location src/tansp//c66//tansp_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMONC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_ELF_SRCTANSP "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_ELF_SRCTANSPC66 "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66" \
 -ccs.definePathVariable EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMON "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/common" \

	echo EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMONC66=../../../common/c66 >> src/tansp//c66//tansp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANSP_66_BE_ELF_SRCTANSP=../../ >> src/tansp//c66//tansp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANSP_66_BE_ELF_SRCTANSPC66=.././ >> src/tansp//c66//tansp_66_BE_ELF/macros.ini
	echo EXT_ROOT__TANSP_66_BE_ELF_SRCCOMMON=../../../common >> src/tansp//c66//tansp_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/tansp_66_BE_ELF"
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common//c66/lnk.cmd
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/tansp/tansp.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/tansp/tansp_d.c
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/tansp//c66/tansp.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/tansp//c66/tansp_i.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common/drvsp.c
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common/drvsp.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common/driver.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common/driver.c
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common/common.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common/tables.c
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/common//c66/common.h
src/tansp//c66//tansp_66_BE_ELF/Release/tansp_66_BE_ELF.out: src/tansp//c66//tansp_66_BE_ELF/.project
	-@ echo Importing Project tansp_66_BE_ELF into workspace ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_BE_ELF" -application com.ti.ccstudio.apps.projectImport -ccs.projects tansp_66_BE_ELF -ccs.location "$(MATHLIB_INSTALL_DIR)/ti/mathlib/src/tansp/c66/tansp_66_BE_ELF"
	-@ echo Building Project tansp_66_BE_ELF ...
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/tansp_66_BE_ELF" -application com.ti.ccstudio.apps.projectBuild -ccs.projects tansp_66_BE_ELF -ccs.configuration Release
	-@ echo Project tansp_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/tansp_66_BE_ELF"

clean::
	-$(RMDIR) "src/tansp//c66//tansp_66_BE_ELF"

