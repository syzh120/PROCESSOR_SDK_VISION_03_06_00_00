#
#*******************************************************************************
# HDVICP2.0 Based JPEG Encoder
#
# "HDVICP2.0 Based JPEG Encoder" is software module developed for
# TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
# by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
# Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED
#*******************************************************************************
#

#  
#******************************************************************************
# @file makefile
#                                       
# @brief This file contains all make rules required for compiling/building
#        test application
#   
# @author: Vasudev Anand
#
# @version 0.0 (Sep 2010) : Base version created
#
#*****************************************************************************
# 

#-----------------------------------------------------------------------------#
# Install directires of all thecomponants required for building the           #
# Test App software. These can either from environment variables or the       #
# absolute paths                                                              #
#-----------------------------------------------------------------------------#
HDVICP_DIR  = %HDVICP2_INSTALL_DIR%
FC_INST_DIR = %FC_INSTALL_DIR%
CG_TOOL     = %CG_TOOL_DIR_M3%
XDC_TOOLS   = %XDCROOT%

#-----------------------------------------------------------------------------#
# Creating a common root to access all the files in the entire code base      #
#-----------------------------------------------------------------------------#
ROOT_DIR = ..\..\..\..

#-----------------------------------------------------------------------------#
# List of Pre-requisite libraries required to build this software             #
#-----------------------------------------------------------------------------#
LIB_SRCS1 += \
$(HDVICP_DIR)\lib\ivahd_ti_api_vM3.lib

LIB_SRCS += \
$(ROOT_DIR)\lib\jpegenc_ti_host.lib

LIB_SRCS2 += \
$(ROOT_DIR)\app\test\src\tiler.lib

#-----------------------------------------------------------------------------#
# List of C source files needs to be compiled                                 #
#-----------------------------------------------------------------------------#
C_SRCS += \
$(ROOT_DIR)\app\test\src\jpegenc_ti_alg_control.c \
$(ROOT_DIR)\app\test\src\jpegenc_ti_alg_create.c \
$(ROOT_DIR)\app\test\src\jpegenc_ti_alg_malloc.c \
$(ROOT_DIR)\app\test\src\jpegenc_ti_api.c \
$(ROOT_DIR)\app\test\src\jpegenc_ti_InterruptVecTable.c \
$(ROOT_DIR)\app\test\src\jpegenc_ti_Test.c \
$(ROOT_DIR)\app\test\src\jpegenc_ti_rman_config.c \
$(ROOT_DIR)\app\test\src\ivahd_standby_power_on_uboot.c \

#-----------------------------------------------------------------------------#
# Linker command file required to link this software                          #
#-----------------------------------------------------------------------------#
CMD_FILE += \
../JpegVEncTestApp.cmd

#-----------------------------------------------------------------------------#
# Final target out file                                                       #
#-----------------------------------------------------------------------------#
OUT_FILE += \
$(ROOT_DIR)\app\build\TestAppDM816x\out\jpegenc_ti_testapp.out

#-----------------------------------------------------------------------------#
# Object file directory                                                       #
#-----------------------------------------------------------------------------#
OBJ_DIR += $(ROOT_DIR)\app\build\TestAppDM816x\obj

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
# Defining RM as force delete. This is used while target clean                #
#-----------------------------------------------------------------------------#
RM := del /f

#-----------------------------------------------------------------------------#
# Compiler executable                                                         #
#-----------------------------------------------------------------------------#
CC     = "$(CG_TOOL)/bin/armcl"

#-----------------------------------------------------------------------------#
# List of folder needs to be searched for a included header file              #
#-----------------------------------------------------------------------------#
INCDIR = --include_path="$(CG_TOOL)\include" \
	 --include_path="$(HDVICP_DIR)\inc" \
   --include_path="$(XDC_TOOLS)\packages" \
	 --include_path="$(FC_INST_DIR)\fctools\packages\ti\xdais" \
	 --include_path="$(FC_INST_DIR)\fctools\packages" \
	 --include_path="$(FC_INST_DIR)\packages\ti\xdais" \
	 --include_path="$(FC_INST_DIR)\packages" \
	 --include_path="$(ROOT_DIR)\app\test\inc" \
	 --include_path="$(ROOT_DIR)" \
	 
#-----------------------------------------------------------------------------#
# Common compile flags                                                        #
#-----------------------------------------------------------------------------#
CFLAGS = -mv7M3 \
   --define="xdc_target_types__= ti/targets/std.h" \
   --define="xdc_target_name__= TMS470" --define=HOSTCORTEXM3_NETRA \
   --define=HOSTCORTEXM3_NETRASIMULATOR --define=_ENABLE_BOOTING_\
   --define="xdc_target_types__= ti/targets/std.h" \
   --diag_warning=225 --display_error_number -me --enum_type=packed --elf \
   --gen_func_subsections --abi=eabi --signed_chars \
	 --diag_warning=225 --diag_warning=167 --diag_warning=14 --diag_warning=48 \
	 --diag_warning=69 --diag_warning=77 --diag_warning=97 --diag_warning=112 \
	 --diag_warning=129 --diag_warning=169 --diag_warning=172 --diag_warning=173 \
	 --diag_warning=174 --diag_warning=188 --diag_warning=190 --diag_warning=232 \
	 --diag_warning=239 --diag_warning=303 --diag_warning=383 --diag_warning=452 \
	 --diag_warning=515 --diag_warning=551 --diag_warning=552 --diag_warning=682 \
	 --diag_warning=1107 --diag_warning=1116 --diag_warning=1311 \
	 --wchar_t=32 --keep_unneeded_types=false \
     --obj_directory="$(OBJ_DIR)"

#-----------------------------------------------------------------------------#
# Default configuration This can be overridden by command line argument       #
#-----------------------------------------------------------------------------#
CONFIGURATION = DEBUG

#-----------------------------------------------------------------------------#
# Setting the flags based on the CONFIGURATION                                #
#-----------------------------------------------------------------------------#

ifeq ($(CONFIGURATION),FASTFILEIO)
CFLAGS += --define="A9_HOST_FILE_IO" --define="OMAP4_SDC"
endif
ifeq ($(CONFIGURATION),RELEASE)
CFLAGS += --symdebug:none -O3
endif
ifeq ($(CONFIGURATION),DEBUG)
CFLAGS += --define="_DEBUG" -g -O0
endif

#-----------------------------------------------------------------------------#
# Final target needs to be build                                              #
#-----------------------------------------------------------------------------#
all: $(OUT_FILE)

#-----------------------------------------------------------------------------#
# Rules to build the target. Here $(C_OBJS_FILE) $(LIB_SRCS)                  #
# $(ASM_OBJS_FILE) $(CMD_FILE) are pre requisite files. Target wil be         #
# remade only if there is any change (time stamp) in these file               #
#-----------------------------------------------------------------------------#
$(OUT_FILE) : $(C_OBJS_FILE) $(CMD_FILE) $(LIB_SRCS)
	echo Linking ...
	$(CC) $(C_OBJS_FILE) --run_linker -I "$(CG_TOOL)\lib" \
	--library=$(CMD_FILE) $(LIB_SRCS1) $(LIB_SRCS2) $(LIB_SRCS) \
	--warn_sections -z --reread_libs --rom_model --diag_suppress=16032 \
	-m"../map/ivahd_ti_jpegencoder_testapp.map" -o $(OUT_FILE)
	echo Linking Completed...
	
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

#-----------------------------------------------------------------------------#
# Compiling the C source files to get the corresponding object files          #
#-----------------------------------------------------------------------------#
$(C_OBJS_FILE) : 
	echo Compiling  $(<)
	$(CC) $(<) $(CFLAGS) $(INCDIR)
	echo Finished

endif

#-----------------------------------------------------------------------------#
# Creating all the required dependency file for OBJ file. Also creating the   #
# dependency for target file on library sources                               #
#-----------------------------------------------------------------------------#
deps:
	echo Scanning dependencies . . .
	echo $(INCDIR)
	$(CC) $(C_SRCS) -ppd $(CFLAGS) $(INCDIR)
	echo echo OFF > temp_pps.bat
	FOR %%i IN ($(C_PPS)) DO echo move %%i >> temp_pps.bat
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
	-$(RM) $(C_PPS_FILE) $(C_OBJS_FILE) $(OUT_FILE)

#-----------------------------------------------------------------------------#
# End of the file                                                             #
#-----------------------------------------------------------------------------#
