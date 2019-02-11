# 
#******************************************************************************
#
#  HDVICP2.0 Based H.264 HP Encoder
# 
# "HDVICP2.0 Based H.264 HP Encoder" is software module developed on TI's 
#  HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
#  video into a high/main/baseline profile bit-stream. Based on ISO/IEC      
#  14496-10." 
# Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
# ALL RIGHTS RESERVED 
#******************************************************************************
# 

#  
#******************************************************************************
# @file makefile
#                                       
# @brief This file contains all make rules required for compiling/building
#        Netra Test App
#   
# @author: Kumar Desappan (kumar.desappan@ti.com)
#
# @version 0.0 (May 2010) : Base version created
# @version 0.1 (April 2011) : Fix for the Debug list accountation in building
#
#*****************************************************************************
# 

#-----------------------------------------------------------------------------#
# Install directires of all thecomponants required for building the           #
# Test App software. These can either from environment variables or the       #
# absolute paths                                                              #
#-----------------------------------------------------------------------------#
HDVICP_DIR = %HDVICP2_INSTALL_DIR%
FC_DIR = %FC_INSTALL_DIR%
CG_TOOL = %CG_TOOL_DIR_M3%
XDC_DIR = %XDCROOT%

#-----------------------------------------------------------------------------#
#HDVICP_DIR = \
#E:\Work\IVAHD\H264E\CC\a0393754_SS_07\VIP_Video\IVA_HD\HDVICP2.0\ivahd_api
#CSP_DIR    = E:\Work\IVAHD\H264E\CC\a0393754_SS_07\VIP_Video\IVA_HD\csp
#FC_DIR     = C:\CCStudio_v4\ccsv4\framework_components_3_00_00_57
#CG_TOOL    = C:\CCStudio_v4\ccsv4\tms470\cgtools\4_5_1
#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
# Creating a common root to access all the files in the entire code basse     #
#-----------------------------------------------------------------------------#
ROOT_DIR = ..\..\..\..

#-----------------------------------------------------------------------------#
# List of Pre-requisite libraries required to build this software             #
#-----------------------------------------------------------------------------#
LIB_SRCS += \
$(HDVICP_DIR)\lib\ivahd_ti_api_vm3.lib \
$(ROOT_DIR)\lib\h264enc_ti_host.lib \
$(ROOT_DIR)\app\Test\Src\fileio.lib \
$(ROOT_DIR)\app\Test\Src\tiler.lib

#-----------------------------------------------------------------------------#
# RTS library used by this software                                           #
#-----------------------------------------------------------------------------#
RTS_LIBS += \
-l"rtsv7M3_T_le_eabi.lib"


#-----------------------------------------------------------------------------#
# List of C source files needs to be compiled                                 #
#-----------------------------------------------------------------------------#
C_SRCS += \
$(ROOT_DIR)\app\Test\Src\alg_control.c \
$(ROOT_DIR)\app\Test\Src\alg_create.c \
$(ROOT_DIR)\app\Test\Src\alg_malloc.c \
$(ROOT_DIR)\app\Test\Src\buffermanager.c \
$(ROOT_DIR)\app\Test\Src\h264enc_ti_config.c \
$(ROOT_DIR)\app\Test\Src\h264enc.c \
$(ROOT_DIR)\app\Test\Src\H264EncRmanConfig.c \
$(ROOT_DIR)\app\Test\Src\H264EncTest.c \
$(ROOT_DIR)\app\Test\Src\h264enc_ti_trace.c \
$(ROOT_DIR)\app\Test\Src\InterruptVecTable.c

#-----------------------------------------------------------------------------#
# List of C source files needs to be compiled with special compile options    #
# Depending on the requirement more number of groups also can be created      #
#-----------------------------------------------------------------------------#
DEBUG_C_SRCS += \
$(ROOT_DIR)\app\Test\Src\h264e_host_scalingmatrix.c 

#-----------------------------------------------------------------------------#
# List of ASM source files needs to be compiled                               #
#-----------------------------------------------------------------------------#
#ASM_SRCS += \

#-----------------------------------------------------------------------------#
# Linker command file required to link this software                          #
#-----------------------------------------------------------------------------#
CMD_FILE += \
..\H264VEncApp.cmd

#-----------------------------------------------------------------------------#
# Final target out file                                                       #
#-----------------------------------------------------------------------------#
OUT_FILE += \
..\Out\TestAppEncoder.out

#-----------------------------------------------------------------------------#
# Object file directory                                                       #
#-----------------------------------------------------------------------------#
OBJ_DIR += $(ROOT_DIR)\app\Build\TestAppDM816x\Obj

#-----------------------------------------------------------------------------#
# Deriving OBJ and PPA(dependecies list file) files list for ASM source list  #
#-----------------------------------------------------------------------------#
ASM_OBJS      = $(ASM_SRCS:.asm=.obj)
ASM_PPAS      = $(ASM_SRCS:.asm=.ppa)
#-----------------------------------------------------------------------------#
# Extracting the file name alone (removing the directry name from the list)   #
#-----------------------------------------------------------------------------#
ASM_PPAS_FILE = $(notdir $(ASM_PPAS))
ASM_PPAS_ORG  = $(addprefix $(OBJ_DIR)\,$(ASM_PPAS_FILE))
ASM_OBJS_FILE_TEMP = $(notdir $(ASM_OBJS))
ASM_OBJS_FILE = $(addprefix $(OBJ_DIR)\,$(ASM_OBJS_FILE_TEMP))

#-----------------------------------------------------------------------------#
# Deriving OBJ and PPA(dependecies list file) files list for C source list    #
#-----------------------------------------------------------------------------#
C_OBJS      = $(C_SRCS:.c=.obj)
C_PPS       = $(C_SRCS:.c=.PP)
#-----------------------------------------------------------------------------#
# Extracting the file name alone (removing the directry name from the list)   #
#-----------------------------------------------------------------------------#
C_OBJS_FILE_TEMP = $(notdir $(C_OBJS))
C_PPS_FILE  = $(notdir $(C_PPS))
C_OBJS_FILE = $(addprefix $(OBJ_DIR)\,$(C_OBJS_FILE_TEMP))

#-----------------------------------------------------------------------------#
# Deriving OBJ and PPA(dependecies list file) files list for C source list    #
#-----------------------------------------------------------------------------#
DEBUG_C_OBJS      = $(DEBUG_C_SRCS:.c=.obj)
DEBUG_C_PPS       = $(DEBUG_C_SRCS:.c=.PP)
#-----------------------------------------------------------------------------#
# Extracting the file name alone (removing the directry name from the list)   #
#-----------------------------------------------------------------------------#
DEBUG_C_OBJS_FILE_TEMP = $(notdir $(DEBUG_C_OBJS))
DEBUG_C_PPS_FILE  = $(notdir $(DEBUG_C_PPS))
DEBUG_C_OBJS_FILE = $(addprefix $(OBJ_DIR)\,$(DEBUG_C_OBJS_FILE_TEMP))

#-----------------------------------------------------------------------------#
# Definin RM as force delete. This is used while target clean                 #
#-----------------------------------------------------------------------------#
RM = del /f

#-----------------------------------------------------------------------------#
# Compiler executable                                                         #
#-----------------------------------------------------------------------------#
CC     = $(CG_TOOL)\bin\armcl
	
#-----------------------------------------------------------------------------#
# List of folder needs to be searched for a included header file              #
#-----------------------------------------------------------------------------#
INCDIR = --include_path="$(CG_TOOL)\include" \
				 --include_path="$(FC_DIR)\fctools\packages\ti\xdais" \
				 --include_path="$(FC_DIR)\fctools\packages" \
				 --include_path="$(FC_DIR)\packages" \
				 --include_path="$(ROOT_DIR)\app\Test\Inc" \
				 --include_path="$(ROOT_DIR)" \
				 --include_path="$(XDC_DIR)\packages" 

#-----------------------------------------------------------------------------#
# Common compile flags                                                        #
#-----------------------------------------------------------------------------#
CFLAGS = -mv7M3 --define="_DEBUG" --define="NETRA" \
			--define "_SIMULATOR_" \
			--define="xdc_target_types__= ti/targets/std.h" \
			--define="xdc_target_name__= TMS470" --diag_warning=225 \
			--wchar_t=32 --keep_unneeded_types=false \
			 -me --enum_type=packed --elf --gen_func_subsections --abi=eabi \
			--signed_chars --obj_directory="$(OBJ_DIR)"
				 
#-----------------------------------------------------------------------------#
# Final target needs to be build                                              #
#-----------------------------------------------------------------------------#
all: $(OUT_FILE)

#-----------------------------------------------------------------------------#
# Rules to build the target. Here $(C_OBJS_FILE) $(DEBUG_C_OBJS_FILE)         #
# $(ASM_OBJS_FILE) $(CMD_FILE) are pre requisite files. Target wil be         #
# remade only if there is any change (time stamp) in these file               #
#-----------------------------------------------------------------------------#
$(OUT_FILE) : $(C_OBJS_FILE) $(DEBUG_C_OBJS_FILE) $(ASM_OBJS_FILE) $(CMD_FILE)
	echo Linking ...
	$(CC) $(C_OBJS_FILE) $(DEBUG_C_OBJS_FILE) $(ASM_OBJS_FILE) --run_linker -I \
	"$(CG_TOOL)\lib" --library=$(CMD_FILE) $(RTS_LIBS) $(LIB_SRCS) \
	--warn_sections -z --reread_libs --diag_suppress=16032 \
	--rom_model -m"..\Map\TestAppEncoder.map" -o $(OUT_FILE)
	echo Linking Completed------------------------------------------------------
	
#-----------------------------------------------------------------------------#
# Each source file can have list of header files includes. If there is any    #
# change in any of the header files then the corresponding C files needs to   #
# be remade. To get this dependecy, the compile can invoked with "-ppd" otion #
# for this corresponding depency file. This dependency file needs to added to #
# the reules while making the "all" targets                                   #
#-----------------------------------------------------------------------------#
ifeq ($(MAKECMDGOALS),all)
ifneq ($(strip $(C_PPS_FILE)),)
-include $(C_PPS_FILE)
endif
ifneq ($(strip $(DEBUG_C_PPS_FILE)),)
-include $(DEBUG_C_PPS_FILE)
endif
ifneq ($(strip $(ASM_PPAS_FILE)),)
-include $(ASM_PPAS_FILE)
endif

ifneq ($(strip $(LIB_SRCS)),)
-include libs.dep
endif

#-----------------------------------------------------------------------------#
# Compiling the C source files to get the corresponding object files          #
#-----------------------------------------------------------------------------#
$(C_OBJS_FILE) : 
	echo Compiling  $(<)
	$(CC) $(<) -g $(CFLAGS) $(INCDIR)
	echo Finished
	

#-----------------------------------------------------------------------------#
# Compiling the C source files to get the corresponding object files          #
# with special compile otption                                                #
#-----------------------------------------------------------------------------#
$(DEBUG_C_OBJS_FILE) :
	echo Compiling  $(<)
	$(CC) $(<) $(CFLAGS) $(INCDIR) -g
	echo Finished

#-----------------------------------------------------------------------------#
# Compiling the ASm source files to get the corresponding object files        #
#-----------------------------------------------------------------------------#
$(ASM_OBJS_FILE) : 
	echo Compiling  $(<)
	$(CC) $(<) $(CFLAGS) $(INCDIR)
	echo Finished
endif

#-----------------------------------------------------------------------------#
# Creating all the required dependency file for OBJ file. Also creating the   #
# dependency for target file on library sources                               #
#-----------------------------------------------------------------------------#
deps:
	echo Scaning dependencies...
	-$(RM) libs.dep
	FOR %%i IN ($(LIB_SRCS)) DO echo $(OUT_FILE) : %%i >> libs.dep
	$(CC) $(C_SRCS) $(DEBUG_C_SRCS) -ppd $(CFLAGS) $(INCDIR)
	echo echo OFF > temp_pps.bat
	FOR %%i IN ($(C_PPS)) DO echo move %%i >> temp_pps.bat
	FOR %%i IN ($(DEBUG_C_PPS)) DO echo move %%i >> temp_pps.bat
	echo echo ON >> temp_pps.bat
	temp_pps.bat
	-$(RM) temp_pps.bat



#-----------------------------------------------------------------------------#
# List of .PHONY (just rules not the actual files) available in this makefile #
#-----------------------------------------------------------------------------#
.PHONY: clean all deps
	
#-----------------------------------------------------------------------------#
# List rule for removing all the intermidaitre file created during            #
# build of the target                                                         #
#-----------------------------------------------------------------------------#
clean :
	-$(RM) $(C_PPS_FILE) $(DEBUG_C_PPS_FILE) $(ASM_PPAS_FILE) $(C_OBJS_FILE) \
	$(DEBUG_C_OBJS_FILE) $(ASM_OBJS_FILE) $(OUT_FILE) libs.dep
	
#-----------------------------------------------------------------------------#
# End of the file                                                             #
#-----------------------------------------------------------------------------#

