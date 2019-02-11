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

# Common Macros used in make

ifndef RMDIR
export RMDIR = DEL /Q /F /S
endif

ifneq ($(findstring $(SHELL), sh.exe),)
	quote = "
	FIXCCSPJT=
else
	quote = '
	FIXCCSPJT=${XDC_INSTALL_DIR}/xs -f ../../../../../../DSPLIB_Install/swtools/ti/mas/swtools/fixccspjt.js $(@D)/$(CDTFILE)
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

# Rule to Build Project FFT_Example_66_LE_COFF

#############################################################

.projects: fft_ex/FFT_Example_66_LE_COFF

fft_ex/FFT_Example_66_LE_COFF: fft_ex/FFT_Example_66_LE_COFF/.project

fft_ex/FFT_Example_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_Example_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_Example_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX/fft_example.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX/lnk.cmd\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX/gen_twiddle_fft16x16.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX/gen_twiddle_fft16x32.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX/gen_twiddle_fft32x32.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_ex/FFT_Example_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_ex/FFT_Example_66_LE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_ex/FFT_Example_66_LE_COFF/macros.ini
	echo EXT_ROOT__FFT_EXAMPLE_66_LE_COFF_FFT_EX=.././ >> fft_ex/FFT_Example_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_LE_COFF"
	-@ echo Project FFT_Example_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_LE_COFF"

clean::
	-$(RMDIR) "fft_ex/FFT_Example_66_LE_COFF"


#############################################################

# Rule to Build Project FFT_Example_66_BE_COFF

#############################################################

.projects: fft_ex/FFT_Example_66_BE_COFF

fft_ex/FFT_Example_66_BE_COFF: fft_ex/FFT_Example_66_BE_COFF/.project

fft_ex/FFT_Example_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_Example_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_Example_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX/fft_example.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX/lnk.cmd\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX/gen_twiddle_fft16x16.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX/gen_twiddle_fft16x32.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX/gen_twiddle_fft32x32.c\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_ex/FFT_Example_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_ex/FFT_Example_66_BE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_ex/FFT_Example_66_BE_COFF/macros.ini
	echo EXT_ROOT__FFT_EXAMPLE_66_BE_COFF_FFT_EX=.././ >> fft_ex/FFT_Example_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_BE_COFF"
	-@ echo Project FFT_Example_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_BE_COFF"

clean::
	-$(RMDIR) "fft_ex/FFT_Example_66_BE_COFF"


#############################################################

# Rule to Build Project FFT_Example_66_LE_ELF

#############################################################

.projects: fft_ex/FFT_Example_66_LE_ELF

fft_ex/FFT_Example_66_LE_ELF: fft_ex/FFT_Example_66_LE_ELF/.project

fft_ex/FFT_Example_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_Example_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_Example_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX/fft_example.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX/lnk.cmd\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX/gen_twiddle_fft16x16.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX/gen_twiddle_fft16x32.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX/gen_twiddle_fft32x32.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_ex/FFT_Example_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_ex/FFT_Example_66_LE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_ex/FFT_Example_66_LE_ELF/macros.ini
	echo EXT_ROOT__FFT_EXAMPLE_66_LE_ELF_FFT_EX=.././ >> fft_ex/FFT_Example_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_LE_ELF"
	-@ echo Project FFT_Example_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_LE_ELF"

clean::
	-$(RMDIR) "fft_ex/FFT_Example_66_LE_ELF"


#############################################################

# Rule to Build Project FFT_Example_66_BE_ELF

#############################################################

.projects: fft_ex/FFT_Example_66_BE_ELF

fft_ex/FFT_Example_66_BE_ELF: fft_ex/FFT_Example_66_BE_ELF/.project

fft_ex/FFT_Example_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_Example_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_Example_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX/fft_example.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX/lnk.cmd\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX/gen_twiddle_fft16x16.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX/gen_twiddle_fft16x32.c\
 -ccs.linkFile EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX/gen_twiddle_fft32x32.c\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_ex/FFT_Example_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_ex/FFT_Example_66_BE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_ex/FFT_Example_66_BE_ELF/macros.ini
	echo EXT_ROOT__FFT_EXAMPLE_66_BE_ELF_FFT_EX=.././ >> fft_ex/FFT_Example_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_BE_ELF"
	-@ echo Project FFT_Example_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_Example_66_BE_ELF"

clean::
	-$(RMDIR) "fft_ex/FFT_Example_66_BE_ELF"


#############################################################

# Rule to Build Project FFT_SP_Example_66_LE_COFF

#############################################################

.projects: fft_sp_ex/FFT_SP_Example_66_LE_COFF

fft_sp_ex/FFT_SP_Example_66_LE_COFF: fft_sp_ex/FFT_SP_Example_66_LE_COFF/.project

fft_sp_ex/FFT_SP_Example_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_SP_Example_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_SP_Example_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_LE_COFF_FFT_SP_EX/fft_example_sp.c\
 -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_LE_COFF_FFT_SP_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_sp_ex/FFT_SP_Example_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__FFT_SP_EXAMPLE_66_LE_COFF_FFT_SP_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_sp_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_sp_ex/FFT_SP_Example_66_LE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_sp_ex/FFT_SP_Example_66_LE_COFF/macros.ini
	echo EXT_ROOT__FFT_SP_EXAMPLE_66_LE_COFF_FFT_SP_EX=.././ >> fft_sp_ex/FFT_SP_Example_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_LE_COFF"
	-@ echo Project FFT_SP_Example_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_LE_COFF"

clean::
	-$(RMDIR) "fft_sp_ex/FFT_SP_Example_66_LE_COFF"


#############################################################

# Rule to Build Project FFT_SP_Example_66_BE_COFF

#############################################################

.projects: fft_sp_ex/FFT_SP_Example_66_BE_COFF

fft_sp_ex/FFT_SP_Example_66_BE_COFF: fft_sp_ex/FFT_SP_Example_66_BE_COFF/.project

fft_sp_ex/FFT_SP_Example_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_SP_Example_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_SP_Example_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_BE_COFF_FFT_SP_EX/fft_example_sp.c\
 -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_BE_COFF_FFT_SP_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_sp_ex/FFT_SP_Example_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__FFT_SP_EXAMPLE_66_BE_COFF_FFT_SP_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_sp_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_sp_ex/FFT_SP_Example_66_BE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_sp_ex/FFT_SP_Example_66_BE_COFF/macros.ini
	echo EXT_ROOT__FFT_SP_EXAMPLE_66_BE_COFF_FFT_SP_EX=.././ >> fft_sp_ex/FFT_SP_Example_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_BE_COFF"
	-@ echo Project FFT_SP_Example_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_BE_COFF"

clean::
	-$(RMDIR) "fft_sp_ex/FFT_SP_Example_66_BE_COFF"


#############################################################

# Rule to Build Project FFT_SP_Example_66_LE_ELF

#############################################################

.projects: fft_sp_ex/FFT_SP_Example_66_LE_ELF

fft_sp_ex/FFT_SP_Example_66_LE_ELF: fft_sp_ex/FFT_SP_Example_66_LE_ELF/.project

fft_sp_ex/FFT_SP_Example_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_SP_Example_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_SP_Example_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_LE_ELF_FFT_SP_EX/fft_example_sp.c\
 -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_LE_ELF_FFT_SP_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_sp_ex/FFT_SP_Example_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__FFT_SP_EXAMPLE_66_LE_ELF_FFT_SP_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_sp_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_sp_ex/FFT_SP_Example_66_LE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_sp_ex/FFT_SP_Example_66_LE_ELF/macros.ini
	echo EXT_ROOT__FFT_SP_EXAMPLE_66_LE_ELF_FFT_SP_EX=.././ >> fft_sp_ex/FFT_SP_Example_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_LE_ELF"
	-@ echo Project FFT_SP_Example_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_LE_ELF"

clean::
	-$(RMDIR) "fft_sp_ex/FFT_SP_Example_66_LE_ELF"


#############################################################

# Rule to Build Project FFT_SP_Example_66_BE_ELF

#############################################################

.projects: fft_sp_ex/FFT_SP_Example_66_BE_ELF

fft_sp_ex/FFT_SP_Example_66_BE_ELF: fft_sp_ex/FFT_SP_Example_66_BE_ELF/.project

fft_sp_ex/FFT_SP_Example_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/FFT_SP_Example_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name FFT_SP_Example_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_BE_ELF_FFT_SP_EX/fft_example_sp.c\
 -ccs.linkFile EXT_ROOT__FFT_SP_EXAMPLE_66_BE_ELF_FFT_SP_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location fft_sp_ex/FFT_SP_Example_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__FFT_SP_EXAMPLE_66_BE_ELF_FFT_SP_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/fft_sp_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> fft_sp_ex/FFT_SP_Example_66_BE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> fft_sp_ex/FFT_SP_Example_66_BE_ELF/macros.ini
	echo EXT_ROOT__FFT_SP_EXAMPLE_66_BE_ELF_FFT_SP_EX=.././ >> fft_sp_ex/FFT_SP_Example_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_BE_ELF"
	-@ echo Project FFT_SP_Example_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/FFT_SP_Example_66_BE_ELF"

clean::
	-$(RMDIR) "fft_sp_ex/FFT_SP_Example_66_BE_ELF"


#############################################################

# Rule to Build Project QRD_dp_least_squares_Example_66_LE_COFF

#############################################################

.projects: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF/.project

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/QRD_dp_least_squares_Example_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name QRD_dp_least_squares_Example_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_COFF_QRD_DP_LEAST_SQUARES_EX/DSPF_dp_qrd_example.c\
 -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_COFF_QRD_DP_LEAST_SQUARES_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_COFF_QRD_DP_LEAST_SQUARES_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/QRD_dp_least_squares_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF/macros.ini
	echo EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_COFF_QRD_DP_LEAST_SQUARES_EX=.././ >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_LE_COFF"
	-@ echo Project QRD_dp_least_squares_Example_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_LE_COFF"

clean::
	-$(RMDIR) "QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_COFF"


#############################################################

# Rule to Build Project QRD_dp_least_squares_Example_66_BE_COFF

#############################################################

.projects: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF/.project

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/QRD_dp_least_squares_Example_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name QRD_dp_least_squares_Example_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_COFF_QRD_DP_LEAST_SQUARES_EX/DSPF_dp_qrd_example.c\
 -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_COFF_QRD_DP_LEAST_SQUARES_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_COFF_QRD_DP_LEAST_SQUARES_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/QRD_dp_least_squares_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF/macros.ini
	echo EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_COFF_QRD_DP_LEAST_SQUARES_EX=.././ >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_BE_COFF"
	-@ echo Project QRD_dp_least_squares_Example_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_BE_COFF"

clean::
	-$(RMDIR) "QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_COFF"


#############################################################

# Rule to Build Project QRD_dp_least_squares_Example_66_LE_ELF

#############################################################

.projects: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF/.project

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/QRD_dp_least_squares_Example_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name QRD_dp_least_squares_Example_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_ELF_QRD_DP_LEAST_SQUARES_EX/DSPF_dp_qrd_example.c\
 -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_ELF_QRD_DP_LEAST_SQUARES_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_ELF_QRD_DP_LEAST_SQUARES_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/QRD_dp_least_squares_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF/macros.ini
	echo EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_LE_ELF_QRD_DP_LEAST_SQUARES_EX=.././ >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_LE_ELF"
	-@ echo Project QRD_dp_least_squares_Example_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_LE_ELF"

clean::
	-$(RMDIR) "QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_LE_ELF"


#############################################################

# Rule to Build Project QRD_dp_least_squares_Example_66_BE_ELF

#############################################################

.projects: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF: QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF/.project

QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/QRD_dp_least_squares_Example_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name QRD_dp_least_squares_Example_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_ELF_QRD_DP_LEAST_SQUARES_EX/DSPF_dp_qrd_example.c\
 -ccs.linkFile EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_ELF_QRD_DP_LEAST_SQUARES_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_ELF_QRD_DP_LEAST_SQUARES_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/QRD_dp_least_squares_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF/macros.ini
	echo EXT_ROOT__QRD_DP_LEAST_SQUARES_EXAMPLE_66_BE_ELF_QRD_DP_LEAST_SQUARES_EX=.././ >> QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_BE_ELF"
	-@ echo Project QRD_dp_least_squares_Example_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/QRD_dp_least_squares_Example_66_BE_ELF"

clean::
	-$(RMDIR) "QRD_dp_least_squares_ex/QRD_dp_least_squares_Example_66_BE_ELF"


#############################################################

# Rule to Build Project SVD_dp_rank_Example_66_LE_COFF

#############################################################

.projects: SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF

SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF: SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF/.project

SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/SVD_dp_rank_Example_66_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name SVD_dp_rank_Example_66_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_COFF_SVD_DP_RANK_EX/DSPF_dp_svd_example.c\
 -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_COFF_SVD_DP_RANK_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_COFF_SVD_DP_RANK_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/SVD_dp_rank_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF/macros.ini
	echo EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_COFF_SVD_DP_RANK_EX=.././ >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_LE_COFF"
	-@ echo Project SVD_dp_rank_Example_66_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_LE_COFF"

clean::
	-$(RMDIR) "SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_COFF"


#############################################################

# Rule to Build Project SVD_dp_rank_Example_66_BE_COFF

#############################################################

.projects: SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF

SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF: SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF/.project

SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/SVD_dp_rank_Example_66_BE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name SVD_dp_rank_Example_66_BE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_COFF_SVD_DP_RANK_EX/DSPF_dp_svd_example.c\
 -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_COFF_SVD_DP_RANK_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k -mw -Dti_targets_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_COFF_SVD_DP_RANK_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/SVD_dp_rank_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF/macros.ini
	echo EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_COFF_SVD_DP_RANK_EX=.././ >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_BE_COFF"
	-@ echo Project SVD_dp_rank_Example_66_BE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_BE_COFF"

clean::
	-$(RMDIR) "SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_COFF"


#############################################################

# Rule to Build Project SVD_dp_rank_Example_66_LE_ELF

#############################################################

.projects: SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF

SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF: SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF/.project

SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/SVD_dp_rank_Example_66_LE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name SVD_dp_rank_Example_66_LE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_ELF_SVD_DP_RANK_EX/DSPF_dp_svd_example.c\
 -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_ELF_SVD_DP_RANK_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_ELF_SVD_DP_RANK_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/SVD_dp_rank_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF/macros.ini
	echo EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_LE_ELF_SVD_DP_RANK_EX=.././ >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_LE_ELF"
	-@ echo Project SVD_dp_rank_Example_66_LE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_LE_ELF"

clean::
	-$(RMDIR) "SVD_dp_rank_ex/SVD_dp_rank_Example_66_LE_ELF"


#############################################################

# Rule to Build Project SVD_dp_rank_Example_66_BE_ELF

#############################################################

.projects: SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF

SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF: SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF/.project

SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/SVD_dp_rank_Example_66_BE_ELF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name SVD_dp_rank_Example_66_BE_ELF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness big\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_ELF_SVD_DP_RANK_EX/DSPF_dp_svd_example.c\
 -ccs.linkFile EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_ELF_SVD_DP_RANK_EX/lnk.cmd\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -g  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Debug\
 -ccs.setCompilerOptions "-mv6600 -k  -mw --strip_coff_underscore -Dti_targets_elf_C66_big_endian --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../" @configurations Release\
 -ccs.setLinkerOptions " -i../../../../ -i$$$${MATHLIB_INSTALL_DIR}/packages  -i$$$${DSPLIB_INSTALL_DIR} -i../../"\
 -ccs.location SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat elf\
 -ccs.definePathVariable EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_ELF_SVD_DP_RANK_EX "C:/nightlybuilds/dsplib/ti/dsplib/dsplib/examples/SVD_dp_rank_ex" \

	${FIXCCSPJT}
	echo MATHLIB_INSTALL_DIR=c:/ti/mathlib_c66x_3_1_0_0 >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF/macros.ini
	echo DSPLIB_INSTALL_DIR=c:/nightlybuilds/dsplib >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF/macros.ini
	echo EXT_ROOT__SVD_DP_RANK_EXAMPLE_66_BE_ELF_SVD_DP_RANK_EX=.././ >> SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_BE_ELF"
	-@ echo Project SVD_dp_rank_Example_66_BE_ELF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/SVD_dp_rank_Example_66_BE_ELF"

clean::
	-$(RMDIR) "SVD_dp_rank_ex/SVD_dp_rank_Example_66_BE_ELF"

