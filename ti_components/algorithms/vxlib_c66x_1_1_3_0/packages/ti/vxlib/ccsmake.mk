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

# VXLIB_INSTALL_DIR   - VXLIB install directory
export VXLIB_INSTALL_DIR ?= C:/ti/vxlib_c66x_1_1_3_0/packages

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

# Rule to Build Project VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF

src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF: src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I16S_I16S_O16S/VXLIB_absDiff_i16s_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I16S_I16S_O16S/VXLIB_absDiff_i16s_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I16S_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_absDiff_i16s_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I16S_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_absDiff_i16s_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I16S_I16S_O16S=../../ >> src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I16S_I16S_O16SC66=.././ >> src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66//VXLIB_absDiff_i16s_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I8U_I8U_O8U/VXLIB_absDiff_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I8U_I8U_O8U/VXLIB_absDiff_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_absDiff_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_absDiff_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I8U_I8U_O8U=../../ >> src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ABSDIFF_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ABSDIFF_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66//VXLIB_absDiff_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_accumulateImage_i8u_io16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF

src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF: src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/.project

src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_accumulateImage_i8u_io16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_accumulateImage_i8u_io16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATEIMAGE_I8U_IO16S/VXLIB_accumulateImage_i8u_io16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATEIMAGE_I8U_IO16S/VXLIB_accumulateImage_i8u_io16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATEIMAGE_I8U_IO16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_accumulateImage_i8u_io16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATEIMAGE_I8U_IO16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_accumulateImage_i8u_io16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATEIMAGE_I8U_IO16S=../../ >> src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATEIMAGE_I8U_IO16SC66=.././ >> src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_accumulateImage_i8u_io16s_66_LE_ELF"
	-@ echo Project VXLIB_accumulateImage_i8u_io16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_accumulateImage_i8u_io16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_accumulateImage_i8u_io16s//c66//VXLIB_accumulateImage_i8u_io16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF

src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF: src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/.project

src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S/VXLIB_accumulateSquareImage_i8u_io16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S/VXLIB_accumulateSquareImage_i8u_io16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_accumulateSquareImage_i8u_io16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_accumulateSquareImage_i8u_io16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S=../../ >> src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCVXVXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16SC66=.././ >> src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF"
	-@ echo Project VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66//VXLIB_accumulateSquareImage_i8u_io16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF

src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF: src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/.project

src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCVXVXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U/VXLIB_accumulateWeightedImage_i8u_io8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCVXVXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U/VXLIB_accumulateWeightedImage_i8u_io8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCVXVXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_accumulateWeightedImage_i8u_io8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCVXVXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_accumulateWeightedImage_i8u_io8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCVXVXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U=../../ >> src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCVXVXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8UC66=.././ >> src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ACCUMULATEWEIGHTEDIMAGE_I8U_IO8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF"
	-@ echo Project VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66//VXLIB_accumulateWeightedImage_i8u_io8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF

src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF: src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADDSQUARE_I8U_I16S_O16S/VXLIB_addSquare_i8u_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADDSQUARE_I8U_I16S_O16S/VXLIB_addSquare_i8u_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADDSQUARE_I8U_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_addSquare_i8u_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADDSQUARE_I8U_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_addSquare_i8u_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADDSQUARE_I8U_I16S_O16S=../../ >> src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADDSQUARE_I8U_I16S_O16SC66=.././ >> src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDSQUARE_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66//VXLIB_addSquare_i8u_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADDWEIGHT_I8U_I8U_O8U/VXLIB_addWeight_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADDWEIGHT_I8U_I8U_O8U/VXLIB_addWeight_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADDWEIGHT_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_addWeight_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADDWEIGHT_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_addWeight_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADDWEIGHT_I8U_I8U_O8U=../../ >> src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADDWEIGHT_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADDWEIGHT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66//VXLIB_addWeight_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_add_i16s_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF

src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF: src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_add_i16s_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_add_i16s_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I16S_I16S_O16S/VXLIB_add_i16s_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I16S_I16S_O16S/VXLIB_add_i16s_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I16S_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i16s_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I16S_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i16s_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I16S_I16S_O16S=../../ >> src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I16S_I16S_O16SC66=.././ >> src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i16s_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_add_i16s_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i16s_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_add_i16s_i16s_o16s//c66//VXLIB_add_i16s_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_add_i8u_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF

src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF: src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_add_i8u_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_add_i8u_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I16S_O16S/VXLIB_add_i8u_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I16S_O16S/VXLIB_add_i8u_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i8u_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i8u_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I16S_O16S=../../ >> src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I16S_O16SC66=.././ >> src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i8u_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_add_i8u_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i8u_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_add_i8u_i16s_o16s//c66//VXLIB_add_i8u_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_add_i8u_i8u_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF

src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF: src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/.project

src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_add_i8u_i8u_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_add_i8u_i8u_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O16S/VXLIB_add_i8u_i8u_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O16S/VXLIB_add_i8u_i8u_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i8u_i8u_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i8u_i8u_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O16S=../../ >> src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O16SC66=.././ >> src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i8u_i8u_o16s_66_LE_ELF"
	-@ echo Project VXLIB_add_i8u_i8u_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i8u_i8u_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_add_i8u_i8u_o16s//c66//VXLIB_add_i8u_i8u_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_add_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_add_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_add_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O8U/VXLIB_add_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O8U/VXLIB_add_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_add_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O8U=../../ >> src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ADD_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ADD_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_add_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_add_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_add_i8u_i8u_o8u//c66//VXLIB_add_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_and_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_and_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_and_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_AND_I8U_I8U_O8U/VXLIB_and_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_AND_I8U_I8U_O8U/VXLIB_and_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_AND_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_and_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_AND_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_and_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_AND_I8U_I8U_O8U=../../ >> src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_AND_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_AND_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_and_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_and_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_and_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_and_i8u_i8u_o8u//c66//VXLIB_and_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_box_3x3_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF

src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF: src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_box_3x3_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_box_3x3_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_BOX_3X3_I8U_O8U/VXLIB_box_3x3_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_BOX_3X3_I8U_O8U/VXLIB_box_3x3_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_BOX_3X3_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_box_3x3_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_BOX_3X3_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_box_3x3_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_BOX_3X3_I8U_O8U=../../ >> src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_BOX_3X3_I8U_O8UC66=.././ >> src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_BOX_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_box_3x3_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_box_3x3_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_box_3x3_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_box_3x3_i8u_o8u//c66//VXLIB_box_3x3_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF

src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF: src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/.project

src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCVXVXLIB_CANNYNMS_I16S_I16S_I16U_O8U/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCVXVXLIB_CANNYNMS_I16S_I16S_I16U_O8U/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCVXVXLIB_CANNYNMS_I16S_I16S_I16U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCVXVXLIB_CANNYNMS_I16S_I16S_I16U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCVXVXLIB_CANNYNMS_I16S_I16S_I16U_O8U=../../ >> src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCVXVXLIB_CANNYNMS_I16S_I16S_I16U_O8UC66=.././ >> src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66//VXLIB_cannyNMS_i16s_i16s_i16u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_2TO1_I8U_O8U/VXLIB_channelCombine_2to1_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_2TO1_I8U_O8U/VXLIB_channelCombine_2to1_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_2TO1_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_2to1_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_2TO1_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_2to1_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_2TO1_I8U_O8U=../../ >> src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_2TO1_I8U_O8UC66=.././ >> src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_2TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66//VXLIB_channelCombine_2to1_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_3TO1_I8U_O8U/VXLIB_channelCombine_3to1_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_3TO1_I8U_O8U/VXLIB_channelCombine_3to1_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_3TO1_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_3to1_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_3TO1_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_3to1_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_3TO1_I8U_O8U=../../ >> src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_3TO1_I8U_O8UC66=.././ >> src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_3TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66//VXLIB_channelCombine_3to1_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_4TO1_I8U_O8U/VXLIB_channelCombine_4to1_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_4TO1_I8U_O8U/VXLIB_channelCombine_4to1_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_4TO1_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_4to1_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_4TO1_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_4to1_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_4TO1_I8U_O8U=../../ >> src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_4TO1_I8U_O8UC66=.././ >> src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66//VXLIB_channelCombine_4to1_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_YUYV_I8U_O8U/VXLIB_channelCombine_yuyv_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_YUYV_I8U_O8U/VXLIB_channelCombine_yuyv_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_YUYV_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_yuyv_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_YUYV_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCombine_yuyv_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_YUYV_I8U_O8U=../../ >> src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOMBINE_YUYV_I8U_O8UC66=.././ >> src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66//VXLIB_channelCombine_yuyv_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOPY_1TO1_I8U_O8U/VXLIB_channelCopy_1to1_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOPY_1TO1_I8U_O8U/VXLIB_channelCopy_1to1_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOPY_1TO1_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCopy_1to1_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOPY_1TO1_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelCopy_1to1_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOPY_1TO1_I8U_O8U=../../ >> src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELCOPY_1TO1_I8U_O8UC66=.././ >> src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELCOPY_1TO1_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66//VXLIB_channelCopy_1to1_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF2_I8U_O8U/VXLIB_channelExtract_1of2_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF2_I8U_O8U/VXLIB_channelExtract_1of2_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF2_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelExtract_1of2_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF2_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelExtract_1of2_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF2_I8U_O8U=../../ >> src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF2_I8U_O8UC66=.././ >> src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF2_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66//VXLIB_channelExtract_1of2_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF3_I8U_O8U/VXLIB_channelExtract_1of3_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF3_I8U_O8U/VXLIB_channelExtract_1of3_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF3_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelExtract_1of3_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF3_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelExtract_1of3_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF3_I8U_O8U=../../ >> src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF3_I8U_O8UC66=.././ >> src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF3_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66//VXLIB_channelExtract_1of3_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF

src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF: src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF4_I8U_O8U/VXLIB_channelExtract_1of4_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF4_I8U_O8U/VXLIB_channelExtract_1of4_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF4_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelExtract_1of4_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF4_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_channelExtract_1of4_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF4_I8U_O8U=../../ >> src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_CHANNELEXTRACT_1OF4_I8U_O8UC66=.././ >> src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CHANNELEXTRACT_1OF4_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66//VXLIB_channelExtract_1of4_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTONV12_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTONV12_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGB_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTORGB_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGB_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTORGB_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_NVXXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTONV12_I8U_O8U/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTONV12_I8U_O8U/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTONV12_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTONV12_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTONV12_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTONV12_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBtoNV12_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTORGBX_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTORGBX_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTONV12_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTONV12_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTORGB_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTORGB_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_RGBXTOYUV4_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66//VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTOIYUV_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTONV12_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTONV12_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGBX_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF

src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF: src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGB_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U=../../ >> src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCVXVXLIB_COLORCONVERT_YUVXTORGB_I8U_O8UC66=.././ >> src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_COLORCONVERT_YUVXTORGB_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66//VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convertDepth_i16s_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF

src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF: src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/.project

src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convertDepth_i16s_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convertDepth_i16s_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I16S_O8U/VXLIB_convertDepth_i16s_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I16S_O8U/VXLIB_convertDepth_i16s_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I16S_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convertDepth_i16s_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I16S_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convertDepth_i16s_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I16S_O8U=../../ >> src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I16S_O8UC66=.././ >> src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I16S_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convertDepth_i16s_o8u_66_LE_ELF"
	-@ echo Project VXLIB_convertDepth_i16s_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convertDepth_i16s_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convertDepth_i16s_o8u//c66//VXLIB_convertDepth_i16s_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convertDepth_i8u_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF

src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF: src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/.project

src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convertDepth_i8u_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convertDepth_i8u_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I8U_O16S/VXLIB_convertDepth_i8u_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I8U_O16S/VXLIB_convertDepth_i8u_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I8U_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convertDepth_i8u_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I8U_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convertDepth_i8u_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I8U_O16S=../../ >> src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCVXVXLIB_CONVERTDEPTH_I8U_O16SC66=.././ >> src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVERTDEPTH_I8U_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convertDepth_i8u_o16s_66_LE_ELF"
	-@ echo Project VXLIB_convertDepth_i8u_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convertDepth_i8u_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convertDepth_i8u_o16s//c66//VXLIB_convertDepth_i8u_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF

src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF: src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O16S/VXLIB_convolve_3x3_i8u_c16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O16S/VXLIB_convolve_3x3_i8u_c16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O16S=../../ >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O16SC66=.././ >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66//VXLIB_convolve_3x3_i8u_c16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF

src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF: src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/.project

src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O8U/VXLIB_convolve_3x3_i8u_c16s_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O8U/VXLIB_convolve_3x3_i8u_c16s_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O8U=../../ >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_3X3_I8U_C16S_O8UC66=.././ >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_3X3_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF"
	-@ echo Project VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66//VXLIB_convolve_3x3_i8u_c16s_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF

src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF: src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O16S/VXLIB_convolve_5x5_i8u_c16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O16S/VXLIB_convolve_5x5_i8u_c16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O16S=../../ >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O16SC66=.././ >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66//VXLIB_convolve_5x5_i8u_c16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF

src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF: src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/.project

src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O8U/VXLIB_convolve_5x5_i8u_c16s_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O8U/VXLIB_convolve_5x5_i8u_c16s_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O8U=../../ >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_5X5_I8U_C16S_O8UC66=.././ >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF"
	-@ echo Project VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66//VXLIB_convolve_5x5_i8u_c16s_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF

src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF: src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O16S/VXLIB_convolve_7x7_i8u_c16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O16S/VXLIB_convolve_7x7_i8u_c16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O16S=../../ >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O16SC66=.././ >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66//VXLIB_convolve_7x7_i8u_c16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF

src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF: src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/.project

src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O8U/VXLIB_convolve_7x7_i8u_c16s_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O8U/VXLIB_convolve_7x7_i8u_c16s_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O8U=../../ >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_7X7_I8U_C16S_O8UC66=.././ >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF"
	-@ echo Project VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66//VXLIB_convolve_7x7_i8u_c16s_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF

src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF: src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O16S/VXLIB_convolve_i8u_c16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O16S/VXLIB_convolve_i8u_c16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_i8u_c16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_i8u_c16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O16S=../../ >> src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O16SC66=.././ >> src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_i8u_c16s_o16s//c66//VXLIB_convolve_i8u_c16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF

src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF: src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/.project

src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O8U/VXLIB_convolve_i8u_c16s_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O8U/VXLIB_convolve_i8u_c16s_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_i8u_c16s_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_convolve_i8u_c16s_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O8U=../../ >> src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCVXVXLIB_CONVOLVE_I8U_C16S_O8UC66=.././ >> src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_CONVOLVE_I8U_C16S_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF"
	-@ echo Project VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_convolve_i8u_c16s_o8u//c66//VXLIB_convolve_i8u_c16s_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF

src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF: src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_3X3_I8U_O8U/VXLIB_dilate_3x3_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_3X3_I8U_O8U/VXLIB_dilate_3x3_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_3X3_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_dilate_3x3_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_3X3_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_dilate_3x3_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_3X3_I8U_O8U=../../ >> src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_3X3_I8U_O8UC66=.././ >> src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_dilate_3x3_i8u_o8u//c66//VXLIB_dilate_3x3_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_MXN_I8U_I8U_O8U/VXLIB_dilate_MxN_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_MXN_I8U_I8U_O8U/VXLIB_dilate_MxN_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_MXN_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_MXN_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_MXN_I8U_I8U_O8U=../../ >> src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_DILATE_MXN_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DILATE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66//VXLIB_dilate_MxN_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF

src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF: src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/.project

src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCVXVXLIB_DOUBLETHRESHOLD_I16U_I8U/VXLIB_doubleThreshold_i16u_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCVXVXLIB_DOUBLETHRESHOLD_I16U_I8U/VXLIB_doubleThreshold_i16u_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCVXVXLIB_DOUBLETHRESHOLD_I16U_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_doubleThreshold_i16u_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCVXVXLIB_DOUBLETHRESHOLD_I16U_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_doubleThreshold_i16u_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCVXVXLIB_DOUBLETHRESHOLD_I16U_I8U=../../ >> src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCVXVXLIB_DOUBLETHRESHOLD_I16U_I8UC66=.././ >> src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_DOUBLETHRESHOLD_I16U_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF"
	-@ echo Project VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_doubleThreshold_i16u_i8u//c66//VXLIB_doubleThreshold_i16u_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_edgeTracing_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF

src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF: src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/.project

src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_edgeTracing_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_edgeTracing_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCVXVXLIB_EDGETRACING_I8U/VXLIB_edgeTracing_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCVXVXLIB_EDGETRACING_I8U/VXLIB_edgeTracing_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCVXVXLIB_EDGETRACING_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_edgeTracing_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCVXVXLIB_EDGETRACING_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_edgeTracing_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCVXVXLIB_EDGETRACING_I8U=../../ >> src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCVXVXLIB_EDGETRACING_I8UC66=.././ >> src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EDGETRACING_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_edgeTracing_i8u_66_LE_ELF"
	-@ echo Project VXLIB_edgeTracing_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_edgeTracing_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_edgeTracing_i8u//c66//VXLIB_edgeTracing_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_equalizeHist_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF

src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF: src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_equalizeHist_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_equalizeHist_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_EQUALIZEHIST_I8U_O8U/VXLIB_equalizeHist_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_EQUALIZEHIST_I8U_O8U/VXLIB_equalizeHist_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_EQUALIZEHIST_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_equalizeHist_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_EQUALIZEHIST_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_equalizeHist_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_EQUALIZEHIST_I8U_O8U=../../ >> src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_EQUALIZEHIST_I8U_O8UC66=.././ >> src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_EQUALIZEHIST_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_equalizeHist_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_equalizeHist_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_equalizeHist_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_equalizeHist_i8u_o8u//c66//VXLIB_equalizeHist_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_erode_3x3_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF

src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF: src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_erode_3x3_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_erode_3x3_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_3X3_I8U_O8U/VXLIB_erode_3x3_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_3X3_I8U_O8U/VXLIB_erode_3x3_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_3X3_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_erode_3x3_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_3X3_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_erode_3x3_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_3X3_I8U_O8U=../../ >> src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_3X3_I8U_O8UC66=.././ >> src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_erode_3x3_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_erode_3x3_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_erode_3x3_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_erode_3x3_i8u_o8u//c66//VXLIB_erode_3x3_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_MXN_I8U_I8U_O8U/VXLIB_erode_MxN_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_MXN_I8U_I8U_O8U/VXLIB_erode_MxN_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_MXN_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_erode_MxN_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_MXN_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_erode_MxN_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_MXN_I8U_I8U_O8U=../../ >> src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_ERODE_MXN_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_ERODE_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66//VXLIB_erode_MxN_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_fastCornersDetect_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF

src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF: src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/.project

src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_fastCornersDetect_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_fastCornersDetect_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSDETECT_I8U/VXLIB_fastCornersDetect_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSDETECT_I8U/VXLIB_fastCornersDetect_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSDETECT_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCornersDetect_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSDETECT_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCornersDetect_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSDETECT_I8U=../../ >> src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSDETECT_I8UC66=.././ >> src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSDETECT_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCornersDetect_i8u_66_LE_ELF"
	-@ echo Project VXLIB_fastCornersDetect_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCornersDetect_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_fastCornersDetect_i8u//c66//VXLIB_fastCornersDetect_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_fastCornersNMS_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF

src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF: src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/.project

src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_fastCornersNMS_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_fastCornersNMS_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSNMS_I8U/VXLIB_fastCornersNMS_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSNMS_I8U/VXLIB_fastCornersNMS_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSNMS_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCornersNMS_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSNMS_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCornersNMS_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSNMS_I8U=../../ >> src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSNMS_I8UC66=.././ >> src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSNMS_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCornersNMS_i8u_66_LE_ELF"
	-@ echo Project VXLIB_fastCornersNMS_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCornersNMS_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_fastCornersNMS_i8u//c66//VXLIB_fastCornersNMS_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_fastCornersScore_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF

src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF: src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/.project

src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_fastCornersScore_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_fastCornersScore_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSSCORE_I8U/VXLIB_fastCornersScore_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSSCORE_I8U/VXLIB_fastCornersScore_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSSCORE_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCornersScore_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSSCORE_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCornersScore_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSSCORE_I8U=../../ >> src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERSSCORE_I8UC66=.././ >> src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERSSCORE_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCornersScore_i8u_66_LE_ELF"
	-@ echo Project VXLIB_fastCornersScore_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCornersScore_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_fastCornersScore_i8u//c66//VXLIB_fastCornersScore_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_fastCorners_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF

src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF: src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/.project

src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_fastCorners_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_fastCorners_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERS_I8U/VXLIB_fastCorners_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERS_I8U/VXLIB_fastCorners_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERS_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCorners_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERS_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_fastCorners_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERS_I8U=../../ >> src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCVXVXLIB_FASTCORNERS_I8UC66=.././ >> src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_FASTCORNERS_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCorners_i8u_66_LE_ELF"
	-@ echo Project VXLIB_fastCorners_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_fastCorners_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_fastCorners_i8u//c66//VXLIB_fastCorners_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF

src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF: src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_3X3_I8U_O8U/VXLIB_gaussian_3x3_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_3X3_I8U_O8U/VXLIB_gaussian_3x3_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_3X3_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_gaussian_3x3_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_3X3_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_gaussian_3x3_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_3X3_I8U_O8U=../../ >> src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_3X3_I8U_O8UC66=.././ >> src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66//VXLIB_gaussian_3x3_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF

src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF: src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_BR_I8U_O8U/VXLIB_gaussian_5x5_br_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_BR_I8U_O8U/VXLIB_gaussian_5x5_br_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_BR_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_gaussian_5x5_br_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_BR_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_gaussian_5x5_br_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_BR_I8U_O8U=../../ >> src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_BR_I8U_O8UC66=.././ >> src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66//VXLIB_gaussian_5x5_br_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF

src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF: src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_I8U_O8U/VXLIB_gaussian_5x5_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_I8U_O8U/VXLIB_gaussian_5x5_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_gaussian_5x5_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_gaussian_5x5_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_I8U_O8U=../../ >> src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_GAUSSIAN_5X5_I8U_O8UC66=.././ >> src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_GAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66//VXLIB_gaussian_5x5_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF

src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF: src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U=../../ >> src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8UC66=.././ >> src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_BR_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF

src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF: src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U/VXLIB_halfScaleGaussian_5x5_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U/VXLIB_halfScaleGaussian_5x5_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U=../../ >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8UC66=.././ >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF

src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF: src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U=../../ >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCVXVXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8UC66=.././ >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66//VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_harrisCornersDetect_i32f_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF

src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF: src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/.project

src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_harrisCornersDetect_i32f_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_harrisCornersDetect_i32f_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSDETECT_I32F/VXLIB_harrisCornersDetect_i32f_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSDETECT_I32F/VXLIB_harrisCornersDetect_i32f_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSDETECT_I32F "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersDetect_i32f" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSDETECT_I32FC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersDetect_i32f/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSDETECT_I32F=../../ >> src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSDETECT_I32FC66=.././ >> src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSDETECT_I32F_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersDetect_i32f_66_LE_ELF"
	-@ echo Project VXLIB_harrisCornersDetect_i32f_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersDetect_i32f_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_harrisCornersDetect_i32f//c66//VXLIB_harrisCornersDetect_i32f_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_harrisCornersNMS_i32f_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF

src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF: src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/.project

src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_harrisCornersNMS_i32f_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_harrisCornersNMS_i32f_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSNMS_I32F/VXLIB_harrisCornersNMS_i32f_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSNMS_I32F/VXLIB_harrisCornersNMS_i32f_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSNMS_I32F "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersNMS_i32f" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSNMS_I32FC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersNMS_i32f/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSNMS_I32F=../../ >> src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSNMS_I32FC66=.././ >> src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSNMS_I32F_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersNMS_i32f_66_LE_ELF"
	-@ echo Project VXLIB_harrisCornersNMS_i32f_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersNMS_i32f_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_harrisCornersNMS_i32f//c66//VXLIB_harrisCornersNMS_i32f_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF

src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF: src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/.project

src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F/VXLIB_harrisCornersScore_i16s_i16s_o32f_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F/VXLIB_harrisCornersScore_i16s_i16s_o32f_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I16S_I16S_O32FC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F=../../ >> src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I16S_I16S_O32FC66=.././ >> src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF"
	-@ echo Project VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66//VXLIB_harrisCornersScore_i16s_i16s_o32f_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF

src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF: src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/.project

src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F/VXLIB_harrisCornersScore_i32s_i32s_o32f_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F/VXLIB_harrisCornersScore_i32s_i32s_o32f_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I32S_I32S_O32FC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F=../../ >> src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCVXVXLIB_HARRISCORNERSSCORE_I32S_I32S_O32FC66=.././ >> src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HARRISCORNERSSCORE_I32S_I32S_O32F_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF"
	-@ echo Project VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66//VXLIB_harrisCornersScore_i32s_i32s_o32f_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF

src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF: src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/.project

src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMCDFLUT_I32U_O8U/VXLIB_histogramCdfLut_i32u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMCDFLUT_I32U_O8U/VXLIB_histogramCdfLut_i32u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMCDFLUT_I32U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_histogramCdfLut_i32u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMCDFLUT_I32U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_histogramCdfLut_i32u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMCDFLUT_I32U_O8U=../../ >> src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMCDFLUT_I32U_O8UC66=.././ >> src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMCDFLUT_I32U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66//VXLIB_histogramCdfLut_i32u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_histogramSimple_i8u_o32u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF

src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF: src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/.project

src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_histogramSimple_i8u_o32u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_histogramSimple_i8u_o32u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMSIMPLE_I8U_O32U/VXLIB_histogramSimple_i8u_o32u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMSIMPLE_I8U_O32U/VXLIB_histogramSimple_i8u_o32u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMSIMPLE_I8U_O32U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_histogramSimple_i8u_o32u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMSIMPLE_I8U_O32UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_histogramSimple_i8u_o32u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMSIMPLE_I8U_O32U=../../ >> src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAMSIMPLE_I8U_O32UC66=.././ >> src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAMSIMPLE_I8U_O32U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_histogramSimple_i8u_o32u_66_LE_ELF"
	-@ echo Project VXLIB_histogramSimple_i8u_o32u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_histogramSimple_i8u_o32u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_histogramSimple_i8u_o32u//c66//VXLIB_histogramSimple_i8u_o32u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_histogram_i8u_o32u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF

src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF: src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/.project

src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_histogram_i8u_o32u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_histogram_i8u_o32u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAM_I8U_O32U/VXLIB_histogram_i8u_o32u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAM_I8U_O32U/VXLIB_histogram_i8u_o32u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAM_I8U_O32U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_histogram_i8u_o32u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAM_I8U_O32UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_histogram_i8u_o32u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAM_I8U_O32U=../../ >> src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCVXVXLIB_HISTOGRAM_I8U_O32UC66=.././ >> src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_HISTOGRAM_I8U_O32U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_histogram_i8u_o32u_66_LE_ELF"
	-@ echo Project VXLIB_histogram_i8u_o32u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_histogram_i8u_o32u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_histogram_i8u_o32u//c66//VXLIB_histogram_i8u_o32u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_integralImage_i8u_o32u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF

src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF: src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/.project

src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_integralImage_i8u_o32u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_integralImage_i8u_o32u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_INTEGRALIMAGE_I8U_O32U/VXLIB_integralImage_i8u_o32u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_INTEGRALIMAGE_I8U_O32U/VXLIB_integralImage_i8u_o32u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_INTEGRALIMAGE_I8U_O32U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_integralImage_i8u_o32u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_INTEGRALIMAGE_I8U_O32UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_integralImage_i8u_o32u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_INTEGRALIMAGE_I8U_O32U=../../ >> src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCVXVXLIB_INTEGRALIMAGE_I8U_O32UC66=.././ >> src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_INTEGRALIMAGE_I8U_O32U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_integralImage_i8u_o32u_66_LE_ELF"
	-@ echo Project VXLIB_integralImage_i8u_o32u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_integralImage_i8u_o32u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_integralImage_i8u_o32u//c66//VXLIB_integralImage_i8u_o32u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF

src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF: src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MAGNITUDE_I16S_I16S_O16S/VXLIB_magnitude_i16s_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MAGNITUDE_I16S_I16S_O16S/VXLIB_magnitude_i16s_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MAGNITUDE_I16S_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_magnitude_i16s_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MAGNITUDE_I16S_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_magnitude_i16s_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MAGNITUDE_I16S_I16S_O16S=../../ >> src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MAGNITUDE_I16S_I16S_O16SC66=.././ >> src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MAGNITUDE_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66//VXLIB_magnitude_i16s_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_meanStdDev_i8u_o32f_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF

src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF: src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/.project

src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_meanStdDev_i8u_o32f_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_meanStdDev_i8u_o32f_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCVXVXLIB_MEANSTDDEV_I8U_O32F/VXLIB_meanStdDev_i8u_o32f_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCVXVXLIB_MEANSTDDEV_I8U_O32F/VXLIB_meanStdDev_i8u_o32f_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCVXVXLIB_MEANSTDDEV_I8U_O32F "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_meanStdDev_i8u_o32f" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCVXVXLIB_MEANSTDDEV_I8U_O32FC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_meanStdDev_i8u_o32f/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCVXVXLIB_MEANSTDDEV_I8U_O32F=../../ >> src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCVXVXLIB_MEANSTDDEV_I8U_O32FC66=.././ >> src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEANSTDDEV_I8U_O32F_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_meanStdDev_i8u_o32f_66_LE_ELF"
	-@ echo Project VXLIB_meanStdDev_i8u_o32f_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_meanStdDev_i8u_o32f_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_meanStdDev_i8u_o32f//c66//VXLIB_meanStdDev_i8u_o32f_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_median_3x3_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF

src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF: src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_median_3x3_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_median_3x3_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_3X3_I8U_O8U/VXLIB_median_3x3_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_3X3_I8U_O8U/VXLIB_median_3x3_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_3X3_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_median_3x3_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_3X3_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_median_3x3_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_3X3_I8U_O8U=../../ >> src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_3X3_I8U_O8UC66=.././ >> src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_3X3_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_median_3x3_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_median_3x3_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_median_3x3_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_median_3x3_i8u_o8u//c66//VXLIB_median_3x3_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_MXN_I8U_I8U_O8U/VXLIB_median_MxN_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_MXN_I8U_I8U_O8U/VXLIB_median_MxN_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_MXN_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_median_MxN_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_MXN_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_median_MxN_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_MXN_I8U_I8U_O8U=../../ >> src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MEDIAN_MXN_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MEDIAN_MXN_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66//VXLIB_median_MxN_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_minMaxLoc_i16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF

src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF: src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/.project

src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_minMaxLoc_i16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_minMaxLoc_i16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I16S/VXLIB_minMaxLoc_i16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I16S/VXLIB_minMaxLoc_i16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_minMaxLoc_i16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_minMaxLoc_i16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I16S=../../ >> src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I16SC66=.././ >> src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_minMaxLoc_i16s_66_LE_ELF"
	-@ echo Project VXLIB_minMaxLoc_i16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_minMaxLoc_i16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_minMaxLoc_i16s//c66//VXLIB_minMaxLoc_i16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_minMaxLoc_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF

src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF: src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/.project

src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_minMaxLoc_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_minMaxLoc_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I8U/VXLIB_minMaxLoc_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I8U/VXLIB_minMaxLoc_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_minMaxLoc_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_minMaxLoc_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I8U=../../ >> src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCVXVXLIB_MINMAXLOC_I8UC66=.././ >> src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MINMAXLOC_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_minMaxLoc_i8u_66_LE_ELF"
	-@ echo Project VXLIB_minMaxLoc_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_minMaxLoc_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_minMaxLoc_i8u//c66//VXLIB_minMaxLoc_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF

src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF: src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I16S_I16S_O16S/VXLIB_multiply_i16s_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I16S_I16S_O16S/VXLIB_multiply_i16s_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I16S_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i16s_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I16S_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i16s_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I16S_I16S_O16S=../../ >> src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I16S_I16S_O16SC66=.././ >> src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_multiply_i16s_i16s_o16s//c66//VXLIB_multiply_i16s_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF

src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF: src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I16S_O16S/VXLIB_multiply_i8u_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I16S_O16S/VXLIB_multiply_i8u_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i8u_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i8u_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I16S_O16S=../../ >> src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I16S_O16SC66=.././ >> src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_multiply_i8u_i16s_o16s//c66//VXLIB_multiply_i8u_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF

src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF: src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/.project

src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O16S/VXLIB_multiply_i8u_i8u_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O16S/VXLIB_multiply_i8u_i8u_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i8u_i8u_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i8u_i8u_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O16S=../../ >> src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O16SC66=.././ >> src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF"
	-@ echo Project VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_multiply_i8u_i8u_o16s//c66//VXLIB_multiply_i8u_i8u_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O8U/VXLIB_multiply_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O8U/VXLIB_multiply_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_multiply_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O8U=../../ >> src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_MULTIPLY_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_MULTIPLY_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_multiply_i8u_i8u_o8u//c66//VXLIB_multiply_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF

src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF: src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/.project

src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML1_I16S_I16S_O16U/VXLIB_normL1_i16s_i16s_o16u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML1_I16S_I16S_O16U/VXLIB_normL1_i16s_i16s_o16u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML1_I16S_I16S_O16U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_normL1_i16s_i16s_o16u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML1_I16S_I16S_O16UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_normL1_i16s_i16s_o16u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML1_I16S_I16S_O16U=../../ >> src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML1_I16S_I16S_O16UC66=.././ >> src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML1_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF"
	-@ echo Project VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_normL1_i16s_i16s_o16u//c66//VXLIB_normL1_i16s_i16s_o16u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF

src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF: src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/.project

src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML2_I16S_I16S_O16U/VXLIB_normL2_i16s_i16s_o16u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML2_I16S_I16S_O16U/VXLIB_normL2_i16s_i16s_o16u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML2_I16S_I16S_O16U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_normL2_i16s_i16s_o16u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML2_I16S_I16S_O16UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_normL2_i16s_i16s_o16u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML2_I16S_I16S_O16U=../../ >> src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCVXVXLIB_NORML2_I16S_I16S_O16UC66=.././ >> src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NORML2_I16S_I16S_O16U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF"
	-@ echo Project VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_normL2_i16s_i16s_o16u//c66//VXLIB_normL2_i16s_i16s_o16u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_not_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF

src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF: src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_not_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_not_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCVXVXLIB_NOT_I8U_O8U/VXLIB_not_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCVXVXLIB_NOT_I8U_O8U/VXLIB_not_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCVXVXLIB_NOT_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_not_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCVXVXLIB_NOT_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_not_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCVXVXLIB_NOT_I8U_O8U=../../ >> src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCVXVXLIB_NOT_I8U_O8UC66=.././ >> src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_NOT_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_not_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_not_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_not_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_not_i8u_o8u//c66//VXLIB_not_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_or_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_or_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_or_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_OR_I8U_I8U_O8U/VXLIB_or_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_OR_I8U_I8U_O8U/VXLIB_or_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_OR_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_or_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_OR_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_or_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_OR_I8U_I8U_O8U=../../ >> src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_OR_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_OR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_or_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_or_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_or_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_or_i8u_i8u_o8u//c66//VXLIB_or_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_phase_i16s_i16s_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF

src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF: src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/.project

src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_phase_i16s_i16s_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_phase_i16s_i16s_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCVXVXLIB_PHASE_I16S_I16S_O8U/VXLIB_phase_i16s_i16s_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCVXVXLIB_PHASE_I16S_I16S_O8U/VXLIB_phase_i16s_i16s_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCVXVXLIB_PHASE_I16S_I16S_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_phase_i16s_i16s_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCVXVXLIB_PHASE_I16S_I16S_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_phase_i16s_i16s_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCVXVXLIB_PHASE_I16S_I16S_O8U=../../ >> src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCVXVXLIB_PHASE_I16S_I16S_O8UC66=.././ >> src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_PHASE_I16S_I16S_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_phase_i16s_i16s_o8u_66_LE_ELF"
	-@ echo Project VXLIB_phase_i16s_i16s_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_phase_i16s_i16s_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_phase_i16s_i16s_o8u//c66//VXLIB_phase_i16s_i16s_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF

src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF: src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U/VXLIB_remapBilinear_bc_i8u_i32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U/VXLIB_remapBilinear_bc_i8u_i32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPBILINEAR_BC_I8U_I32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U=../../ >> src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPBILINEAR_BC_I8U_I32F_O8UC66=.././ >> src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPBILINEAR_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66//VXLIB_remapBilinear_bc_i8u_i32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF

src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF: src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPNEAREST_BC_I8U_I32F_O8U/VXLIB_remapNearest_bc_i8u_i32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPNEAREST_BC_I8U_I32F_O8U/VXLIB_remapNearest_bc_i8u_i32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPNEAREST_BC_I8U_I32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPNEAREST_BC_I8U_I32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPNEAREST_BC_I8U_I32F_O8U=../../ >> src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCVXVXLIB_REMAPNEAREST_BC_I8U_I32F_O8UC66=.././ >> src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66//VXLIB_remapNearest_bc_i8u_i32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF

src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF: src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U/VXLIB_scaleImageBilinear_bc_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U/VXLIB_scaleImageBilinear_bc_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U=../../ >> src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8UC66=.././ >> src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BC_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66//VXLIB_scaleImageBilinear_bc_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF

src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF: src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U/VXLIB_scaleImageBilinear_br_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U/VXLIB_scaleImageBilinear_br_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U=../../ >> src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8UC66=.././ >> src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_BR_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66//VXLIB_scaleImageBilinear_br_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF

src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF: src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_I8U_O8U/VXLIB_scaleImageBilinear_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_I8U_O8U/VXLIB_scaleImageBilinear_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageBilinear_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageBilinear_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_I8U_O8U=../../ >> src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGEBILINEAR_I8U_O8UC66=.././ >> src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGEBILINEAR_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66//VXLIB_scaleImageBilinear_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF

src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF: src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGENEAREST_I8U_O8U/VXLIB_scaleImageNearest_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGENEAREST_I8U_O8U/VXLIB_scaleImageNearest_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGENEAREST_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageNearest_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGENEAREST_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scaleImageNearest_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGENEAREST_I8U_O8U=../../ >> src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SCALEIMAGENEAREST_I8U_O8UC66=.././ >> src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCALEIMAGENEAREST_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66//VXLIB_scaleImageNearest_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF

src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF: src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SCHARR_3X3_I8U_O16S_O16S/VXLIB_scharr_3x3_i8u_o16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SCHARR_3X3_I8U_O16S_O16S/VXLIB_scharr_3x3_i8u_o16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SCHARR_3X3_I8U_O16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SCHARR_3X3_I8U_O16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SCHARR_3X3_I8U_O16S_O16S=../../ >> src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SCHARR_3X3_I8U_O16S_O16SC66=.././ >> src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SCHARR_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66//VXLIB_scharr_3x3_i8u_o16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF

src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF: src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/.project

src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELX_3X3_I8U_O16S/VXLIB_sobelX_3x3_i8u_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELX_3X3_I8U_O16S/VXLIB_sobelX_3x3_i8u_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELX_3X3_I8U_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobelX_3x3_i8u_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELX_3X3_I8U_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobelX_3x3_i8u_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELX_3X3_I8U_O16S=../../ >> src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELX_3X3_I8U_O16SC66=.././ >> src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELX_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF"
	-@ echo Project VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66//VXLIB_sobelX_3x3_i8u_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF

src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF: src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/.project

src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELY_3X3_I8U_O16S/VXLIB_sobelY_3x3_i8u_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELY_3X3_I8U_O16S/VXLIB_sobelY_3x3_i8u_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELY_3X3_I8U_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobelY_3x3_i8u_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELY_3X3_I8U_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobelY_3x3_i8u_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELY_3X3_I8U_O16S=../../ >> src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SOBELY_3X3_I8U_O16SC66=.././ >> src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBELY_3X3_I8U_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF"
	-@ echo Project VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66//VXLIB_sobelY_3x3_i8u_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF

src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF: src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_3X3_I8U_O16S_O16S/VXLIB_sobel_3x3_i8u_o16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_3X3_I8U_O16S_O16S/VXLIB_sobel_3x3_i8u_o16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_3X3_I8U_O16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_3X3_I8U_O16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_3X3_I8U_O16S_O16S=../../ >> src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_3X3_I8U_O16S_O16SC66=.././ >> src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_3X3_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66//VXLIB_sobel_3x3_i8u_o16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF

src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF: src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_5X5_I8U_O16S_O16S/VXLIB_sobel_5x5_i8u_o16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_5X5_I8U_O16S_O16S/VXLIB_sobel_5x5_i8u_o16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_5X5_I8U_O16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_5X5_I8U_O16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_5X5_I8U_O16S_O16S=../../ >> src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_5X5_I8U_O16S_O16SC66=.././ >> src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_5X5_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66//VXLIB_sobel_5x5_i8u_o16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF

src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF: src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O16S_O16S/VXLIB_sobel_7x7_i8u_o16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O16S_O16S/VXLIB_sobel_7x7_i8u_o16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O16S_O16S=../../ >> src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O16S_O16SC66=.././ >> src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66//VXLIB_sobel_7x7_i8u_o16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF

src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF: src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/.project

src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O32S_O32S/VXLIB_sobel_7x7_i8u_o32s_o32s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O32S_O32S/VXLIB_sobel_7x7_i8u_o32s_o32s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O32S_O32S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O32S_O32SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O32S_O32S=../../ >> src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCVXVXLIB_SOBEL_7X7_I8U_O32S_O32SC66=.././ >> src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SOBEL_7X7_I8U_O32S_O32S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF"
	-@ echo Project VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66//VXLIB_sobel_7x7_i8u_o32s_o32s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF

src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF: src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I16S_I16S_O16S/VXLIB_subtract_i16s_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I16S_I16S_O16S/VXLIB_subtract_i16s_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I16S_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i16s_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I16S_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i16s_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I16S_I16S_O16S=../../ >> src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I16S_I16S_O16SC66=.././ >> src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I16S_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_subtract_i16s_i16s_o16s//c66//VXLIB_subtract_i16s_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF

src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF: src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I16S_O16S/VXLIB_subtract_i8u_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I16S_O16S/VXLIB_subtract_i8u_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i8u_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i8u_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I16S_O16S=../../ >> src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I16S_O16SC66=.././ >> src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_subtract_i8u_i16s_o16s//c66//VXLIB_subtract_i8u_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF

src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF: src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/.project

src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O16S/VXLIB_subtract_i8u_i8u_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O16S/VXLIB_subtract_i8u_i8u_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i8u_i8u_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i8u_i8u_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O16S=../../ >> src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O16SC66=.././ >> src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF"
	-@ echo Project VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_subtract_i8u_i8u_o16s//c66//VXLIB_subtract_i8u_i8u_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O8U/VXLIB_subtract_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O8U/VXLIB_subtract_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_subtract_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O8U=../../ >> src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_SUBTRACT_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_SUBTRACT_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_subtract_i8u_i8u_o8u//c66//VXLIB_subtract_i8u_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_tableLookup_i16s_o16s_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF

src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF: src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/.project

src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_tableLookup_i16s_o16s_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_tableLookup_i16s_o16s_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I16S_O16S/VXLIB_tableLookup_i16s_o16s_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I16S_O16S/VXLIB_tableLookup_i16s_o16s_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I16S_O16S "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_tableLookup_i16s_o16s" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I16S_O16SC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_tableLookup_i16s_o16s/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I16S_O16S=../../ >> src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I16S_O16SC66=.././ >> src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I16S_O16S_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_tableLookup_i16s_o16s_66_LE_ELF"
	-@ echo Project VXLIB_tableLookup_i16s_o16s_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_tableLookup_i16s_o16s_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_tableLookup_i16s_o16s//c66//VXLIB_tableLookup_i16s_o16s_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_tableLookup_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF

src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF: src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_tableLookup_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_tableLookup_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I8U_O8U/VXLIB_tableLookup_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I8U_O8U/VXLIB_tableLookup_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_tableLookup_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_tableLookup_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I8U_O8U=../../ >> src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCVXVXLIB_TABLELOOKUP_I8U_O8UC66=.././ >> src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TABLELOOKUP_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_tableLookup_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_tableLookup_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_tableLookup_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_tableLookup_i8u_o8u//c66//VXLIB_tableLookup_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF

src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF: src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDBINARY_I8U_O8U/VXLIB_thresholdBinary_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDBINARY_I8U_O8U/VXLIB_thresholdBinary_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDBINARY_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_thresholdBinary_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDBINARY_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_thresholdBinary_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDBINARY_I8U_O8U=../../ >> src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDBINARY_I8U_O8UC66=.././ >> src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDBINARY_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_thresholdBinary_i8u_o8u//c66//VXLIB_thresholdBinary_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_thresholdRange_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF

src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF: src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_thresholdRange_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_thresholdRange_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDRANGE_I8U_O8U/VXLIB_thresholdRange_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDRANGE_I8U_O8U/VXLIB_thresholdRange_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDRANGE_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_thresholdRange_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDRANGE_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_thresholdRange_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDRANGE_I8U_O8U=../../ >> src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCVXVXLIB_THRESHOLDRANGE_I8U_O8UC66=.././ >> src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_THRESHOLDRANGE_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_thresholdRange_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_thresholdRange_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_thresholdRange_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_thresholdRange_i8u_o8u//c66//VXLIB_thresholdRange_i8u_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_trackFeaturesLK_i8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF

src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF: src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/.project

src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_trackFeaturesLK_i8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_trackFeaturesLK_i8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCVXVXLIB_TRACKFEATURESLK_I8U/VXLIB_trackFeaturesLK_i8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCVXVXLIB_TRACKFEATURESLK_I8U/VXLIB_trackFeaturesLK_i8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCVXVXLIB_TRACKFEATURESLK_I8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_trackFeaturesLK_i8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCVXVXLIB_TRACKFEATURESLK_I8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_trackFeaturesLK_i8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCVXVXLIB_TRACKFEATURESLK_I8U=../../ >> src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCVXVXLIB_TRACKFEATURESLK_I8UC66=.././ >> src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_TRACKFEATURESLK_I8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_trackFeaturesLK_i8u_66_LE_ELF"
	-@ echo Project VXLIB_trackFeaturesLK_i8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_trackFeaturesLK_i8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_trackFeaturesLK_i8u//c66//VXLIB_trackFeaturesLK_i8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U/VXLIB_warpAffineBilinear_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U/VXLIB_warpAffineBilinear_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66//VXLIB_warpAffineBilinear_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_I8U_C32F_O8U/VXLIB_warpAffineNearest_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_I8U_C32F_O8U/VXLIB_warpAffineNearest_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPAFFINENEAREST_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPAFFINENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66//VXLIB_warpAffineNearest_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVEBILINEAR_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_BC_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF

src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF: src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/.project

src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U=../../ >> src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCVXVXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8UC66=.././ >> src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_WARPPERSPECTIVENEAREST_I8U_C32F_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF"
	-@ echo Project VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66//VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_66_LE_ELF"


#############################################################

# Rule to Build Project VXLIB_xor_i8u_i8u_o8u_66_LE_ELF

#############################################################

.projects: src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF

src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF: src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/.project

src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/VXLIB_xor_i8u_i8u_o8u_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name VXLIB_xor_i8u_i8u_o8u_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_XOR_I8U_I8U_O8U/VXLIB_xor_i8u_i8u_o8u_d.c\
 -ccs.linkFile EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_XOR_I8U_I8U_O8U/VXLIB_xor_i8u_i8u_o8u_idat.c\
 -ccs.linkFile EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -g  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Debug -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far --legacy -o3 --symdebug:none  -i../../../../../../../../ -i../../../ -i../../ -i../../../../../common -i../../../../../common/c6x -i../../../../../common/c66" @configurations Release -ccs.location src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_XOR_I8U_I8U_O8U "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_xor_i8u_i8u_o8u" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_XOR_I8U_I8U_O8UC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/vx/VXLIB_xor_i8u_i8u_o8u/c66" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON "C:/nightlybuilds/vxlib/ti/vxlib/src/common" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c6x" \
 -ccs.definePathVariable EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66 "C:/nightlybuilds/vxlib/ti/vxlib/src/common/c66" \

	echo EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_XOR_I8U_I8U_O8U=../../ >> src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCVXVXLIB_XOR_I8U_I8U_O8UC66=.././ >> src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMON=../../../../common >> src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC6X=../../../../common/c6x >> src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/macros.ini
	echo EXT_ROOT__VXLIB_XOR_I8U_I8U_O8U_66_LE_ELF_SRCCOMMONC66=../../../../common/c66 >> src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/VXLIB_xor_i8u_i8u_o8u_66_LE_ELF"
	-@ echo Project VXLIB_xor_i8u_i8u_o8u_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/VXLIB_xor_i8u_i8u_o8u_66_LE_ELF"

clean::
	-$(RMDIR) "src/vx/VXLIB_xor_i8u_i8u_o8u//c66//VXLIB_xor_i8u_i8u_o8u_66_LE_ELF"

