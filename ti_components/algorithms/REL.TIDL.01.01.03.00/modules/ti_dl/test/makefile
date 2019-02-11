#
# Copyright (c) {2015 - 2017} Texas Instruments Incorporated
#
# All rights reserved not granted herein.
#
# Limited License.
#
# Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
# license under copyrights and patents it now or hereafter owns or controls to make,
# have made, use, import, offer to sell and sell ("Utilize") this software subject to the
# terms herein.  With respect to the foregoing patent license, such license is granted
# solely to the extent that any such patent is necessary to Utilize the software alone.
# The patent license shall not apply to any combinations which include this software,
# other than combinations with devices manufactured by or for TI ("TI Devices").
# No hardware patent is licensed hereunder.
#
# Redistributions must preserve existing copyright notices and reproduce this license
# (including the above copyright notice and the disclaimer and (if applicable) source
# code license limitations below) in the documentation and/or other materials provided
# with the distribution
#
# Redistribution and use in binary form, without modification, are permitted provided
# that the following conditions are met:
#
# *       No reverse engineering, decompilation, or disassembly of this software is
# permitted with respect to any software provided in binary form.
#
# *       any redistribution and use are licensed by TI for use only with TI Devices.
#
# *       Nothing shall obligate TI to provide you with source code for the software
# licensed and provided to you in object code.
#
# If software source code is provided to you, modification and redistribution of the
# source code are permitted provided that the following conditions are met:
#
# *       any redistribution and use of the source code, including any resulting derivative
# works, are licensed by TI for use only with TI Devices.
#
# *       any redistribution and use of any object code compiled from the source code
# and any resulting derivative works, are licensed by TI for use only with TI Devices.
#
# Neither the name of Texas Instruments Incorporated nor the names of its suppliers
#
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# DISCLAIMER.
#
# THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

##############################################################
ALGBASE_PATH ?= $(abspath ../../../)
include $(ALGBASE_PATH)/makerules/config.mk


DSP_COMMON_DIR= ../../../common
DSP_MODULES = "../../ti_dl"
OPENCV_INSTALL_DIR = D:\opencv_3.1.0\opencv
##############################################################


##############################################################
SUBDIRS= ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += $(DSP_COMMON_DIR)/configparser.c
CFILES += $(DSP_COMMON_DIR)/ti_draw_utils.c
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(DSP_COMMON_DIR)/ti_file_io.c))

CFILES += $(DSP_COMMON_DIR)/ti_mem_manager.c

ifeq ($(CORE) , eve)
CFILES += $(DSP_COMMON_DIR)/eve/eve_profile.c
CFILES += $(DSP_COMMON_DIR)/eve/curve_fitting.c
CFILES += $(DSP_COMMON_DIR)/eve/eve_sctm.c
CFILES += $(DSP_COMMON_DIR)/eve/ti_stats_collector.c 
CFILES += $(DSP_COMMON_DIR)/eve/cred.c
CFILES += $(DSP_COMMON_DIR)/eve/boot_arp32.asm 
CFLAGS+= -I $(DSP_COMMON_DIR)/eve
else ifeq ($(CORE) , dsp)
CFILES += $(DSP_COMMON_DIR)/cache.c
CFILES += $(DSP_COMMON_DIR)/profile.c
CFILES += $(DSP_COMMON_DIR)/dsp_tsc_h.asm
endif

ifeq ($(TARGET_PLATFORM), PC)
CFILES:= $(filter-out %ti_file_io.c, $(CFILES))
CFILES:= $(filter-out %eve_sctm.c, $(CFILES))
endif

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=./out/$(CORE)_test_dl_algo.out
##############################################################


##############################################################

include $(ALGBASE_PATH)/makerules/rules.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ../inc
CFLAGS+= -I $(XDAIS_PACKAGE_DIR)
CFLAGS+= -I $(DSP_COMMON_DIR)
CFLAGS+= -I $(DMAUTILS_PATH)/inc
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_utils
CFLAGS+= -I $(DMAUTILS_PATH)/inc/edma_csl
CFLAGS+= -I $(DSP_COMMON_DIR)/baseaddress/$(TARGET_SOC)/$(CORE)
CFLAGS+= -I $(DMAUTILS_PATH)/drivers/inc
CFLAGS+= -I $(EDMA3_LLD_ROOT)/packages/ti/sdo/edma3/rm
CFLAGS+= -I $(EDMA3_LLD_ROOT)/packages
CFLAGS+= -I $(DSP_MODULES)/ti_dl/algo/inc
CFLAGS+= -I $(MATHLIB_INSTALL_DIR)/packages
CFLAGS+= -I $(MATHLIB_INSTALL_DIR)/packages/ti/mathlib
CFLAGS+= -I $(OPENCV_INSTALL_DIR)\sources\modules\core\include
CFLAGS+= -I $(OPENCV_INSTALL_DIR)\sources\modules\highgui\include
CFLAGS+= -I $(OPENCV_INSTALL_DIR)\sources\modules\imgcodecs\include
CFLAGS+= -I $(OPENCV_INSTALL_DIR)\sources\modules\videoio\include
CFLAGS+= -I $(OPENCV_INSTALL_DIR)\sources\modules\imgproc\include
ifeq ($(CORE) , eve)
CFLAGS+= -I $(DSP_COMMON_DIR)/eve
endif
##############################################################


##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
DMAUTILS_LIB  := $(DMAUTILS_PATH)/libs/PC/$(CORE)/$(TARGET_BUILD)/dmautils.lib
else
DMAUTILS_LIB  := $(DMAUTILS_PATH)/libs/$(CORE)/$(TARGET_BUILD)/dmautils.lib
endif


ifneq ($(TARGET_PLATFORM) , PC)

ifeq ($(CORE) , eve)
LDFLAGS+= -l $(ARP32_TOOLS)/lib/rtsarp32_v200.lib
LDFLAGS+= -l "./linker_$(CORE)_$(TARGET_BUILD).cmd"
else ifeq ($(CORE) , dsp)  
LDFLAGS+= -cr -x
LDFLAGS+= -l $(DSP_TOOLS)/lib/rts6600_elf.lib
LDFLAGS+= -l $(MATHLIB_INSTALL_DIR)/packages/ti/mathlib/lib/mathlib.ae66
LDFLAGS+= -l "./linker_$(CORE).cmd"
endif

else

ifdef SystemRoot
ifeq ($(TARGET_BUILD), debug)
CFLAGS+= /MTd
LDFLAGS+= /NODEFAULTLIB:msvcrtd.lib
else
CFLAGS+= /MT 
LDFLAGS+= /NODEFAULTLIB:msvcrt.lib
endif

else
LDFLAGS+= -lstdc++ -static
endif

endif

ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
CFLAGS+= /DCORE_C6XX
else
CFLAGS+= -DCORE_C6XX
endif
else
CFLAGS+= -DCORE_C6XX
endif


ifeq ($(TARGET_PLATFORM) , PC)

ifdef SystemRoot
CFLAGS+= /DCORE_C6XX
ifeq ($(RUN_REF_FOR_STATS) ,1)
CFLAGS+= /DRUN_REF_FOR_STATS
endif

else

CFLAGS+= -DCORE_C6XX
ifeq ($(RUN_REF_FOR_STATS) ,1)
CFLAGS+= -DRUN_REF_FOR_STATS
endif
endif
endif



ifeq ($(TARGET_PLATFORM) , PC)
LDFLAGS+= "$(DSP_MODULES)/lib/PC/$(CORE)/$(TARGET_BUILD)/tidl_algo.lib"
ifeq ($(BUILD_WITH_OPENCV), 1)
CFLAGS+= /DBUILD_WITH_OPENCV
ifeq ($(TARGET_BUILD), debug)

LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Debug\opencv_core310d.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Debug\opencv_highgui310d.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Debug\opencv_imgcodecs310d.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Debug\opencv_imgproc310d.lib"

LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\zlibd.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\libjasperd.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\libjpegd.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\libpngd.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\libtiffd.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\libwebpd.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Debug\IlmImfd.lib"

else
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Release\opencv_core310.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Release\opencv_highgui310.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Release\opencv_imgcodecs310.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\lib\Release\opencv_imgproc310.lib"

LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\zlib.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\libjasper.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\libjpeg.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\libpng.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\libtiff.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\libwebp.lib"
LDFLAGS+= -l "$(OPENCV_INSTALL_DIR)\build\3rdparty\lib\Release\IlmImf.lib"
LDFLAGS+= /NODEFAULTLIB:msvcrt.lib
endif
LDFLAGS+= -l "User32.lib"


endif
else
LDFLAGS+= -l "$(DSP_MODULES)/lib/$(CORE)/$(TARGET_BUILD)/tidl_algo.lib"
endif
LDFLAGS += $(DMAUTILS_LIB)

##############################################################


##############################################################
OUTDIR =  "./out"

$(OUTFILE) : outfile
##############################################################

