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

include $(ALGBASE_PATH)/makerules/config.mk

XDAIS_PACKAGE_DIR := $(XDAIS_PATH)/packages
BUILD_FOLDER      := $(ALGBASE_PATH)\out

ifdef SystemRoot
#Windows OS
    ifndef UTILS_PATH
      $(error You must define UTILS_PATH!)
    endif
    RM_CMD = $(UTILS_PATH)\rm -rf
    MKDIR_CMD = $(UTILS_PATH)\mkdir -p $(1)
    CHANGE_PATHSEP=$(subst /,\,$(1))
    CAT_CMD = $(UTILS_PATH)\cat
    MAKE = gmake
else
    ifeq ($(shell uname), Linux)
#Linux
      RM_CMD = rm -rf
      MKDIR_CMD = mkdir -p $(1)
      CHANGE_PATHSEP=$(subst \,/,$(1))
      CAT_CMD = cat
      MAKE = make
    endif
endif

ifeq ($(SHOW_COMMANDS),1)
Q:=
else
Q:=@
endif

ALGBASE_PATH:= $(call  CHANGE_PATHSEP,$(ALGBASE_PATH))
XDAIS_PACKAGE_DIR:= $(call  CHANGE_PATHSEP,$(XDAIS_PACKAGE_DIR))
EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)
COMMA:=$(EMPTY),$(EMPTY)

_MAKEPATH := $(abspath .)
_MAKEPATH:= $(call  CHANGE_PATHSEP,$(_MAKEPATH))


ifdef SystemRoot
_MODPATH  := $(subst $(ALGBASE_PATH)\,,$(_MAKEPATH))
else
_MODPATH  := $(subst $(ALGBASE_PATH)/,,$(_MAKEPATH))
endif
_MODPATH:= $(call CHANGE_PATHSEP,$(_MODPATH))



BUILD_MODE ?=OBJ

#if platform is vayu
ifeq ($(TARGET_SOC),vayu)
    DEFINE_FLAGS := VAYU_PLATFORM
endif

#if platform is vme
ifeq ($(TARGET_SOC),vme)
    DEFINE_FLAGS := VME_PLATFORM
endif

ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

ifeq ($(TARGET_PLATFORM) , PC)
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_PLATFORM)/$(CORE)/$(TARGET_BUILD)
else
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)
endif

CURR_BUILD_FOLDER:= $(call  CHANGE_PATHSEP,$(CURR_BUILD_FOLDER))

##############################################################

##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
  CC = CL
  CP = CL
  AS = $(TARGET_CPU)ASM
  AR = LIB
  LD = LINK
  ifeq ($(TARGET_BUILD), release)
    COMPILER_FLAGS += /EHsc /TP /W0  /DHOST_EMULATION /c /nologo /Ox /MD /Gm /Zi /D_HOST_BUILD  /D_HAS_ITERATOR_DEBUGGING=0 /D_ITERATOR_DEBUG_LEVEL=0
    LDDEBUG := /DEBUG 
  else
    COMPILER_FLAGS += /EHsc /TP /W0 /DHOST_EMULATION /c /nologo /Od /MDd /Gm /Zi /RTC1 /D_HOST_BUILD 
    LDDEBUG := /DEBUG 
  endif
  ARFLAGS := /nologo /MACHINE:X86
else 
  #Linux Host Emulation
  CC=gcc -c
  AR=ar
  ARFLAGS := rvs
  ifeq ($(TARGET_BUILD), debug)
    COMPILER_FLAGS += -std=c99 -ggdb -ggdb3 -gdwarf-2 -DHOST_EMULATION -m32
  else
    COMPILER_FLAGS += -std=c99 -O3 -DHOST_EMULATION -m32
  endif
  LD=g++
  LDFLAGS +=
endif
  ifeq ($(CORE),eve)
  COMPILER_FLAGS += -DCORE_EVE -DVCOP_HOST_EMULATION
  endif
  ifeq ($(CORE),dsp)
  COMPILER_FLAGS += -DCORE_C6XX -D_TMS320C6600

   ifeq ($(TARGET_CPU),C64T)
     COMPILER_FLAGS += -DTMS320C64X
     else ifeq ($(TARGET_CPU),C64P)
     COMPILER_FLAGS += -DTMS320C64PX
     else ifeq ($(TARGET_CPU),C64)
     COMPILER_FLAGS += -DTMS320C64X
     else ifeq ($(TARGET_CPU),C66)
     COMPILER_FLAGS += -DTMS320C66X
     else ifeq ($(TARGET_CPU),C674)
     COMPILER_FLAGS += -DTMS320C67X
     else ifeq ($(TARGET_CPU),C67)
     COMPILER_FLAGS += -DTMS320C67X
     else ifeq ($(TARGET_CPU),C67P)
     COMPILER_FLAGS += -DTMS320C67X
   endif
   COMPILER_FLAGS += -DLITTLE_ENDIAN_HOST
  endif 

else
#TI_DEVICE
  ifeq ($(CORE),eve)
    CC = $(ARP32_TOOLS)\bin\cl-arp32
    LD = $(ARP32_TOOLS)\bin\lnk-arp32
    AR = $(ARP32_TOOLS)\bin\ar-arp32
    ifeq ($(TARGET_BUILD), release)
      COMPILER_FLAGS += -kh -kv -lu -o3 --silicon_version=v210 -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311
    else
      COMPILER_FLAGS += -kh -kv -lu -g --silicon_version=v210  -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x --display_error_number --diag_suppress=num=10063  --diag_suppress=num=10068
    CFLAGS += -I $(ARP32_TOOLS)/include
    CFLAGS += -DCORE_EVE
    ifneq ($(VCOP_H_DIR),)
      CFLAGS += --temp_directory=$(VCOP_H_DIR)
    endif
  endif
  ifeq ($(CORE),dsp)
    CC = $(DSP_TOOLS)\bin\cl6x
    LD = $(DSP_TOOLS)\bin\lnk6x
    AR = $(DSP_TOOLS)\bin\ar6x
    ifeq ($(TARGET_BUILD), release)
      CFLAGS = -O3 -ml3 -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS) --abi=eabi --rtti -mo
    else
      CFLAGS = -ml3 -g -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS) --abi=eabi --rtti -mo
    endif
    CFLAGS += -DCORE_C6XX
    
    ifeq ($(TARGET_CPU),C64T)
      CFLAGS += --silicon_version=tesla -D=xdc_target_name=C64T
      else ifeq ($(TARGET_CPU),C64P)
      CFLAGS += --silicon_version=6400+ -D=xdc_target_name=C64P
      else ifeq ($(TARGET_CPU),C64)
      CFLAGS += --silicon_version=6400 -D=xdc_target_name=C64
      else ifeq ($(TARGET_CPU),C66)
      CFLAGS += --silicon_version=6600 -D=xdc_target_name=C66
      else ifeq ($(TARGET_CPU),C674)
      CFLAGS += --silicon_version=6740 -D=xdc_target_name=C674
      else ifeq ($(TARGET_CPU),C67)
      CFLAGS += --silicon_version=6700 -D=xdc_target_name=C67
      else ifeq ($(TARGET_CPU),C67P)
      CFLAGS += --silicon_version=6700+ -D=xdc_target_name=C67P
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x
    CFLAGS += -I $(DSP_TOOLS)/include
  endif
  ifeq ($(CORE),arm)
	CFLAGS_GLOBAL_m4vpss = -g -ms -D___DSPBIOS___ -D___DUCATI_FW___ --obj_extension=obj
	ENDIAN = little
	FORMAT = ELF
    
	CC = $(TIARM_TOOLS)\bin\armcl
	LD = $(TIARM_TOOLS)\bin\armlnk
	AR = $(TIARM_TOOLS)\bin\armar
	CFLAGS_INTERNAL = -c -qq -pdsw225 --endian=$(ENDIAN) -mv7M4 --float_support=vfplib --abi=$(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) --symdebug:dwarf --embed_inline_assembly
    
    ifeq ($(FORMAT),COFF)
		CSWITCH_FORMAT = ti_arm9_abi
		RTSLIB_FORMAT = tiarm9
    endif
    ifeq ($(FORMAT),ELF)
		CSWITCH_FORMAT = eabi
		RTSLIB_FORMAT = eabi
    endif

    ifeq ($(TARGET_BUILD), release)
		LNKFLAGS_INTERNAL_PROFILE = --opt='--endian=$(ENDIAN) -mv7M4 --float_support=vfplib --abi=$(CSWITCH_FORMAT) -qq -pdsw225 $(CFLAGS_GLOBAL_m4vpss) -oe --symdebug:dwarf -ms -op2 -O3 -os --optimize_with_debug --inline_recursion_limit=20 --diag_suppress=23000' --strict_compatibility=on
		CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_6_1 -ms -oe -O3 -op0 -os --optimize_with_debug --inline_recursion_limit=20
    else
		LNKFLAGS_INTERNAL_PROFILE =
		CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_6_1 -D_DEBUG_=1
 
    endif
	
	ARFLAGS = rq
	CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_m4vpss) $(CFLAGS_XDCINTERNAL)
	CFLAGS += -I $(TIARM_TOOLS)\include
  endif

  
  CFLAGS += --diag_suppress=496 --diag_suppress=1311
endif

ifeq ($(CORE),eve)
CFLAGS += -I $(ARP32_TOOLS)/include/vcop
endif
##############################################################


##############################################################
ifeq ($(LIBDIR),)
LIBDIR =  .\lib\$(TARGET_BUILD)
endif
ifeq ($(OUTDIR),)
OUTDIR =  .\elf_out
endif



ifeq ($(ENABLE_FASTFILEIO),1)
CFLAGS += -DUSE_HOST_FILE_IO
endif

##############################################################

# In case there are no sources, it is better to not generate any lib
ifeq (,$(wildcard $(CFILES)))
OUTFILE=
endif
##############################################################
CFILES := $(call  CHANGE_PATHSEP,$(CFILES))
HFILES := $(call  CHANGE_PATHSEP,$(HFILES))

CFILESK:= $(filter %.k,$(CFILES))
CFILESC:= $(filter %.c,$(CFILES))
CFILESCPP:= $(filter %.cpp,$(CFILES))
CFILESCC:= $(filter %.cc,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESK) $(CFILESC) $(CFILESASM) $(CFILESCPP) $(CFILESCC)

#OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))

OFILES:= $(CFILESC:%.c=%.obj)
OFILES+= $(CFILESCPP:%.cpp=%.obj)
OFILES+= $(CFILESCC:%.cc=%.obj)
ifneq ($(TARGET_PLATFORM) , PC)
OFILES+= $(CFILESASM:%.asm=%.obj)
endif
DEPILES:= $(CFILESC:%.c=%.dep)
DEPILES+= $(CFILESCPP:%.cpp=%.dep)
DEPILES+= $(CFILESCC:%.cc=%.dep)
KOFILES:= $(CFILESK:%.k=%.obj)

BUILDDIR := $(CURR_BUILD_FOLDER)/$(_MODPATH)/
BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))

OFILES:= $(addprefix  $(BUILDDIR), $(OFILES))
KOFILES:= $(addprefix $(BUILDDIR), $(KOFILES))
DEPILES:= $(addprefix $(BUILDDIR), $(DEPILES))

OFILES := $(call  CHANGE_PATHSEP,$(OFILES))
FIRST_OFILES := $(word 1,$(OFILES))
RESTOF_OFILES := $(filter-out $(FIRST_OFILES), $(OFILES))

BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
OBJDIRS := $(foreach file, $(OFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(KOFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(OUTFILE), $(dir $(file)))
OBJDIRS += $(BUILDDIR)
OBJDIRS := $(sort $(OBJDIRS))
OBJDIRS := $(addsuffix \.gitignore, $(OBJDIRS))

##############################################################
CC := $(call  CHANGE_PATHSEP,$(CC))
LD := $(call  CHANGE_PATHSEP,$(LD))
AR := $(call  CHANGE_PATHSEP,$(AR))

CFLAGS := $(call  CHANGE_PATHSEP,$(CFLAGS))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
LIBDIR := $(call  CHANGE_PATHSEP,$(LIBDIR))
OUTDIR := $(call  CHANGE_PATHSEP,$(OUTDIR))

OBJDIRS := $(call  CHANGE_PATHSEP,$(OBJDIRS))

CFLAGS := $(COMPILER_FLAGS) $(CFLAGS)

#$(info OBJDIRS $(OBJDIRS))

##############################################################
# 'all' rules
all : dir $(OUTFILE)

# Define a ".gitignore" file which will help in making sure the module's output
# folder always exists.
%.gitignore:
#	@echo creating $@
	$(Q) $(MKDIR_CMD) $(dir $@)
	$(Q)echo .> $@
dir: $(OBJDIRS)

$(OUTFILE): $(KOFILES) $(OFILES)

ifdef SystemRoot
$(BUILDDIR)\%.obj: .\%.k
else
$(BUILDDIR)%.obj: %.k
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --compile_only -fr=$(dir $@) "$<"
endif

ifdef SystemRoot
$(BUILDDIR)\%.obj: .\%.c
else
$(BUILDDIR)%.obj: %.c
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif


ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cpp
else
$(BUILDDIR)%.obj: .%.cpp
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif

ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cc
else
$(BUILDDIR)%.obj: .%.cc
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif


ifneq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
$(BUILDDIR)\%.obj : ./%.asm
else
$(BUILDDIR)%.obj : %.asm
endif
	$(Q)$(CC) $(CFLAGS) -c $^ --output_file=$@
endif
##############################################################

print :
	echo $(LDFLAGS)
	echo $(OFILES)
	echo $(OUTFILE)
	echo $(CFILES)
	echo $(HFILES)
	echo @$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
##############################################################
# clean rules
.IGNORE: clean
clean:
ifdef SystemRoot
	@echo echo OFF > temp_pps.bat
	@FOR %%i IN ($(OFILES) $(KOFILES)) DO echo del %%i >> temp_pps.bat
ifneq ($(TARGET_PLATFORM) , PC)
	@FOR %%i IN ( $(DEPILES)) DO echo del %%i >> temp_pps.bat
endif
	@echo echo ON >> temp_pps.bat
	@temp_pps.bat
	@-del temp_pps.bat
else
	$(Q)$(RM_CMD) $(OFILES) $(KOFILES)
endif	
ifneq ($(BUILD_MODE),OBJ)
	$(Q)$(RM_CMD) $(LIBDIR)
endif
	$(Q)$(RM_CMD) $(OUTDIR)
##############################################################


##############################################################
.PHONY: libfile
libfile: $(LIBDIR) $(KOFILES) $(OFILES) $(ARFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)echo Linking $(OUTFILE)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)$(AR) $(ARFLAGS) -o $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
ifdef SystemRoot
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)$(RM_CMD) ar_cmd.txt
else	
	@$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
endif	
endif 
$(LIBDIR):
	$(Q) $(MKDIR_CMD) $(LIBDIR) || cd $(LIBDIR)

##############################################################
.PHONY: pllibfile
pllibfile: $(LIBDIR) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo Linking $(OUTFILE)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)$(AR) $(ARFLAGS) -o $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
endif
else
ifdef SystemRoot
	$(Q)echo $(ARFLAGS) temp_pl.lib > ar_cmd.txt
	$(Q)FOR %%i IN ($(RESTOF_OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)$(LD) -r $(LDFLAGS) --output_file="plink.out"  $(FIRST_OFILES) $(LDFILES) -m "plink.map" -l temp_pl.lib
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)echo plink.out >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del temp_pl.lib
	$(Q)-del ar_cmd.txt
	$(Q)-del plink.map
	$(Q)-del plink.out
else	
	$(Q)$(LD) -r --output_file="plink.out"  $(FIRST_OFILES) $(RESTOF_OFILES) $(KOFILES) -m "plink.map"
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) plink.out
endif	
endif

##############################################################
PC_LDFLAGS1 = $(filter-out %rtsarp32_v200.lib,$(LDFLAGS))
PC_LDFLAGS = $(filter-out %rtsarp32_v200.lib",$(PC_LDFLAGS1))
ALL_LIBS1 = $(filter %.lib,$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib"",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.a86",$(PC_LDFLAGS))

ALL_LIBS  = $(subst .lib,.lib,$(ALL_LIBS1))

##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(KOFILES) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)if exist $(OUTFILE).exe del $(OUTFILE).exe
	$(Q)$(LD) $(ALL_LIBS) $(LDDEBUG) /nologo /MACHINE:X86 /OUT:$(OUTFILE).exe $(KOFILES) $(OFILES) $(LDFILES)
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) -o $(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) $(LDFLAGS) 
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) $(LDFLAGS) --output_file=$(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif
$(OUTDIR):
	$(Q)$(MKDIR_CMD) $(OUTDIR) || cd $(OUTDIR)

##############################################################


##############################################################
.PHONY: mergefile
mergefile: 
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevekernels.eve.lib lib\$(TARGET_BUILD)\libevekernels.eve.lib lib\$(TARGET_BUILD)\libeveprivkernels.eve.lib
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevenatckernels.eve.lib lib\$(TARGET_BUILD)\libevenatckernels.eve.lib lib\$(TARGET_BUILD)\libeveprivnatckernels.eve.lib
else
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libevekernels.eve.lib
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libeveprivkernels.eve.lib
	$(Q)$(AR) a lib/$(TARGET_BUILD)/libevekernels.eve.lib *.obj
	$(Q)$(RM_CMD) *.obj
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libevenatckernels.eve.lib
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libeveprivnatckernels.eve.lib
	$(Q)$(AR) a lib/$(TARGET_BUILD)/libevenatckernels.eve.lib *.obj
	$(Q)$(RM_CMD) *.obj
endif
##############################################################


define INCLUDE_DEPEND
-include $(1).dep
endef

$(foreach obj,$(OFILES),$(eval $(call INCLUDE_DEPEND,$(basename $(obj)))))




