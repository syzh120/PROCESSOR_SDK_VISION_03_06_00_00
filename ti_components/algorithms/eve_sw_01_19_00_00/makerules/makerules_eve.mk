#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


##############################################################

# Valid values: gcc VC
HOST_TOOLCHAIN?=VC
HOST_TOOLCHAIN_PATH=C:/MinGW

ifeq ($(wildcard $(EVE_SW_ROOT)),)
$(error You must define EVE_SW_ROOT!)
endif

ifdef SystemRoot
#Windows OS
    ifeq ($(wildcard $(UTILS_PATH)),)
      $(error You must define UTILS_PATH!)
    endif
    RM_CMD = $(UTILS_PATH)/rm -rf
    MKDIR_CMD = $(UTILS_PATH)/mkdir -p $(1)
    CHANGE_PATHSEP=$(subst /,\,$(1))
    CHANGE_PATHSEP_UNIX=$(subst \,/,$(1))
    CAT_CMD = $(UTILS_PATH)/cat
    else
    ifeq ($(shell uname), Linux)
#Linux
      RM_CMD = rm -rf
      MKDIR_CMD = mkdir -p $(1)
      CHANGE_PATHSEP=$(subst \,/,$(1))
      CAT_CMD = cat
    endif
endif

ifeq ($(BUILD_FOLDER),)
BUILD_FOLDER := $(EVE_SW_ROOT)/out
endif

SHOW_COMMANDS ?= 0

ifeq ($(SHOW_COMMANDS),1)
Q:=
else
Q:=@
endif

EVE_SW_ROOT:= $(call  CHANGE_PATHSEP,$(EVE_SW_ROOT))

EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)
COMMA:=$(EMPTY),$(EMPTY)

_MAKEPATH := $(abspath .)
_MAKEPATH:= $(call  CHANGE_PATHSEP,$(_MAKEPATH))

ifdef SystemRoot
_MODPATH  := $(subst $(EVE_SW_ROOT)\,,$(_MAKEPATH))
else
_MODPATH  := $(subst $(EVE_SW_ROOT)/,,$(_MAKEPATH))
endif
_MODPATH:= $(call CHANGE_PATHSEP,$(_MODPATH))

BUILD_MODE ?=OBJ



ARP32_TOOLS ?= "C:\ti\ARP32_tools"
xdais_PATH ?= "C:\ti\xdais_7_23_00_06"
DMAUTILS_PATH ?= "D:\work\vision\dsp_git\dsp_apps\dmautils"
# Default platform
# Supported values: vayu,vme
TARGET_SOC ?= vayu
# Default CORE
# Supported values: dsp, eve
CORE ?= eve
TARGET_PLATFORM ?= EVE

ifeq ($(HOST_TOOLCHAIN),gcc)
PC_LIB_EXTN:=
endif
ifeq ($(HOST_TOOLCHAIN),VC)
PC_LIB_EXTN:=_pc.lib
endif

XDAIS_PACKAGES_DIR = $(xdais_PATH)/packages
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
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_PLATFORM)/$(TARGET_BUILD)
else
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)
endif

CURR_BUILD_FOLDER:= $(call  CHANGE_PATHSEP,$(CURR_BUILD_FOLDER))


STARTERWARE      := $(EVE_SW_ROOT)/starterware
ALGFRAMEWORK_PATH ?= "D:\work\vision\dsp_git\dsp_apps\algframework"
ALG_FRAMEWORK_DIR := $(ALGFRAMEWORK_PATH)

KERNELS_DIR := $(EVE_SW_ROOT)/kernels
COMMON_DIR := $(EVE_SW_ROOT)/common
BASE_ADDRESS_DIR := $(STARTERWARE)/inc/baseaddress/$(TARGET_SOC)/$(CORE)
ifeq ($(TARGET_PLATFORM) , PC)
STARTERWARE_LIB  := $(STARTERWARE)/libs/$(TARGET_PLATFORM)/$(TARGET_BUILD)/libevestarterware_eve.lib$(PC_LIB_EXTN)
else
STARTERWARE_LIB  := $(STARTERWARE)/libs/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)/libevestarterware_$(CORE).lib
endif
VCOP_HOST_DIR    := ../kernels/common
##############################################################

##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
  ifeq ($(HOST_TOOLCHAIN),gcc)
    COMPILE_PATH=$(HOST_TOOLCHAIN_PATH)
    CC=$(COMPILE_PATH)/bin/g++ -c
    AR=$(COMPILE_PATH)/bin/ar
    ARFLAGS = rs
    COMPILER_FLAGS = -O3 -DVCOP_HOST_EMULATION -DHOST_EMULATION -fpermissive -m32
    LD = $(COMPILE_PATH)/bin/ld
  endif
  ifeq ($(HOST_TOOLCHAIN),VC)
    CC = CL
    CP = CL
    AS = $(TARGET_CPU)ASM
    AR = LIB
    LD = LINK
  endif
ifeq ($(TARGET_BUILD), release)
  ifeq ($(HOST_TOOLCHAIN),VC)
    COMPILER_FLAGS += /EHsc /TP /W0 /DCORE_EVE /DVCOP_HOST_EMULATION /DHOST_EMULATION /c /nologo /Ox /MD
  endif
  LDDEBUG :=
else
  ifeq ($(HOST_TOOLCHAIN),VC)
    COMPILER_FLAGS += /EHsc /TP /W0 /DCORE_EVE /DVCOP_HOST_EMULATION /DHOST_EMULATION /c /nologo /Od /MDd /Gm /Zi /RTC1
  LDDEBUG := /DEBUG
  endif
endif
  CFLAGS += -I $(VCOP_HOST_DIR)
  ifeq ($(HOST_TOOLCHAIN),VC)
    ARFLAGS := /nologo /MACHINE:X86
  endif
#  LDFLAGS :=
else
  ifeq ($(CORE),eve)
    CC = $(ARP32_TOOLS)/bin/cl-arp32
    LD = $(ARP32_TOOLS)/bin/lnk-arp32
    AR = $(ARP32_TOOLS)/bin/ar-arp32
    ifeq ($(TARGET_BUILD), release)
      COMPILER_FLAGS += -kh -kv -lu -o3 --silicon_version=v210 -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311
    else
      COMPILER_FLAGS += -kh -kv -lu -g --silicon_version=v210  -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x --display_error_number --diag_suppress=num=10063  --diag_suppress=num=10068
    CFLAGS += -I $(ARP32_TOOLS)/include
    CFLAGS += -I $(ARP32_TOOLS)/include/vcop
    CFLAGS += -DCORE_EVE
  endif
  ifeq ($(CORE),dsp)
    CC = $(DSP_TOOLS)/bin/cl6x
    LD = $(DSP_TOOLS)/bin/lnk6x
    AR = $(DSP_TOOLS)/bin/ar6x
    ifeq ($(TARGET_BUILD), release)
      COMPILER_FLAGS += -O3 -mv6740+ -ml3 -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS)
    else
      COMPILER_FLAGS +=-mv6740+ -ml3 -g -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS)
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x
    CFLAGS += -I $(DSP_TOOLS)/include
  endif
  ifneq ($(VCOP_H_DIR),)
    CFLAGS += --temp_directory=$(VCOP_H_DIR)
  endif
endif

CFLAGS += -I $(ARP32_TOOLS)/include/vcop
CFLAGS += -I $(BASE_ADDRESS_DIR)
CFLAGS += -I $(DMAUTILS_PATH)/inc
CFLAGS += -I $(DMAUTILS_PATH)/inc/edma_csl
CFLAGS += -I $(DMAUTILS_PATH)/inc/edma_utils
CFLAGS += -I $(STARTERWARE)/inc
CFLAGS += -I $(ALG_FRAMEWORK_DIR)/inc
CFLAGS += -I $(KERNELS_DIR)/inc

CFLAGS += -I $(KERNELS_DIR)
CFLAGS += -I $(COMMON_DIR)
CFLAGS += -I $(XDAIS_PACKAGES_DIR)
LDFLAGS+= -l $(KERNELS_DIR)/lib/$(TARGET_BUILD)/libevekernels.$(CORE).lib
LDFLAGS+= -l $(KERNELS_DIR)/lib/$(TARGET_BUILD)/libevenatckernels.$(CORE).lib
LDFLAGS+= -l $(ARP32_TOOLS)/lib/rtsarp32_v200.lib

ifeq ($(TARGET_PLATFORM) , PC)
else
endif

ifeq ($(TARGET_PLATFORM) , PC)
COMMON_LIBS =  $(DMAUTILS_PATH)/libs/$(TARGET_PLATFORM)/$(CORE)/$(TARGET_BUILD)/dmautils.lib
COMMON_LIBS  +=  "$(ALG_FRAMEWORK_DIR)/lib/$(TARGET_PLATFORM)/$(CORE)/$(TARGET_BUILD)/algframework.lib"
#COMMON_LIBS  +=  "$(ALG_FRAMEWORK_DIR)/lib/$(TARGET_PLATFORM)/$(CORE)/$(TARGET_BUILD)/extmem.lib"
else
COMMON_LIBS  = -l $(DMAUTILS_PATH)/libs/$(CORE)/$(TARGET_BUILD)/dmautils.lib
COMMON_LIBS  += -l "$(ALG_FRAMEWORK_DIR)/lib/$(CORE)/$(TARGET_BUILD)/algframework.lib"
#COMMON_LIBS  += -l "$(ALG_FRAMEWORK_DIR)/lib/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)/extmem.lib"
endif


##############################################################


##############################################################
ifeq ($(LIBDIR),)
LIBDIR =  .\lib\$(TARGET_BUILD)
endif
ifeq ($(OUTDIR),)
OUTDIR =  .\elf_out
endif

CFLAGS += -I $(ARP32_TOOLS)/include/vcop

#CFLAGS += -DEN_ZEBU_TEST

ifeq ($(ENABLE_FASTFILEIO),1)
CFLAGS += -DUSE_HOST_FILE_IO
endif

##############################################################

# In case there are no sources, it is better to not generate any lib
ifeq (,$(wildcard $(CFILES)))
OUTFILE=
endif
##############################################################
#CFILES:= $(subst /,\,$(CFILES))
CFILES := $(call  CHANGE_PATHSEP,$(CFILES))
HFILES := $(call  CHANGE_PATHSEP,$(HFILES))

CFILESK:= $(filter %.k,$(CFILES))
CFILESC:= $(filter %.c,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESK) $(CFILESC) $(CFILESASM)

#OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))

OFILES:= $(CFILESC:%.c=%.obj)
ifneq ($(TARGET_PLATFORM) , PC)
OFILES+= $(CFILESASM:%.asm=%.obj)
endif
DEPILES:= $(CFILESC:%.c=%.dep)
KOFILES:= $(CFILESK:%.k=%.obj)

BUILDDIR := $(CURR_BUILD_FOLDER)/$(_MODPATH)/
BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))

OFILES:= $(addprefix  $(BUILDDIR), $(OFILES))
KOFILES:= $(addprefix $(BUILDDIR), $(KOFILES))
DEPILES:= $(addprefix $(BUILDDIR), $(DEPILES))

OFILES := $(call  CHANGE_PATHSEP,$(OFILES))

BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))

OBJDIRS := $(foreach file, $(OFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(KOFILES), $(dir $(file)))
OBJDIRS += $(BUILDDIR)
OBJDIRS := $(sort $(OBJDIRS))
OBJDIRS := $(addsuffix \.gitignore, $(OBJDIRS))

##############################################################
CC := $(call  CHANGE_PATHSEP,$(CC))
CFLAGS := $(call  CHANGE_PATHSEP,$(CFLAGS))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
LIBDIR := $(call  CHANGE_PATHSEP,$(LIBDIR))
OUTDIR := $(call  CHANGE_PATHSEP,$(OUTDIR))

OFILES_UNIX_STYLE := $(call  CHANGE_PATHSEP_UNIX,$(OFILES))
KOFILES_UNIX_STYLE := $(call  CHANGE_PATHSEP_UNIX,$(KOFILES))
ARFILES_UNIX_STYLE := $(call  CHANGE_PATHSEP_UNIX,$(ARFILES))
OUTFILE_UNIX_STYLE := $(call  CHANGE_PATHSEP_UNIX,$(OUTFILE))
OBJDIRS := $(call  CHANGE_PATHSEP,$(OBJDIRS))

CFLAGS := $(COMPILER_FLAGS) $(CFLAGS)
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
ifeq ($(HOST_TOOLCHAIN),gcc)
	$(Q)$(CC) $(CFLAGS) -xc++ $< -o$@ 
endif
ifeq ($(HOST_TOOLCHAIN),VC)
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
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
ifeq ($(HOST_TOOLCHAIN),gcc)
	$(Q)$(CC) $(CFLAGS) $< -o$@ 
endif
ifeq ($(HOST_TOOLCHAIN),VC)
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
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
	$(Q)echo Linking $(OUTFILE)
ifeq ($(HOST_TOOLCHAIN),gcc)
#	$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
	$(Q)echo $(ARFLAGS) $(OUTFILE_UNIX_STYLE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES_UNIX_STYLE) $(KOFILES_UNIX_STYLE) $(ARFILES_UNIX_STYLE)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
endif
ifeq ($(HOST_TOOLCHAIN),VC)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE)$(PC_LIB_EXTN) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
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

PC_LDFLAGS1 = $(filter-out %rtsarp32_v200.lib,$(LDFLAGS))
PC_LDFLAGS = $(filter-out %rtsarp32_v200.lib",$(PC_LDFLAGS1))
ALL_LIBS1 = $(filter %.lib,$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib"",$(PC_LDFLAGS))

ALL_LIBS  = $(subst .lib,.lib$(PC_LIB_EXTN),$(ALL_LIBS1))

##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(KOFILES) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)if exist $(OUTFILE).exe del $(OUTFILE).exe
ifeq ($(HOST_TOOLCHAIN),VC)
	$(Q)$(LD) $(STARTERWARE_LIB) $(COMMON_LIBS) $(ALL_LIBS) $(LDDEBUG) /nologo /MACHINE:X86 /OUT:$(OUTFILE).exe $(KOFILES) $(OFILES) $(LDFILES)
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) -l $(STARTERWARE_LIB) $(COMMON_LIBS) $(LDFLAGS) --output_file=$(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif
$(OUTDIR):
	$(Q)$(MKDIR_CMD) $(OUTDIR) || cd $(OUTDIR)

##############################################################


##############################################################
.PHONY: mergefile
mergefile: 
ifeq ($(TARGET_PLATFORM) , PC)
ifeq ($(HOST_TOOLCHAIN),VC)
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevekernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libevekernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libeveprivkernels.eve.lib$(PC_LIB_EXTN)
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevenatckernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libevenatckernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libeveprivnatckernels.eve.lib$(PC_LIB_EXTN)
endif
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




