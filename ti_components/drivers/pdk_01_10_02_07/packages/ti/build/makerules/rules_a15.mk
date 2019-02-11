#
# Copyright (c) 2013-2016, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Filename: rules_a15.mk
#
# Make rules for A15 - This file has all the common rules and defines required
#                     for Cortex-A15 ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (This file uses Code Sourcery)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for A15 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(TOOLCHAIN_PATH_A15)/arm-none-eabi/include
ifneq ($(GCC_FLOAT_PATH),FPU)
CODEGEN_INCLUDE += $(TOOLCHAIN_PATH_A15)/arm-none-eabi/include/newlib-nano
endif
CC = $(TOOLCHAIN_PATH_A15)/bin/arm-none-eabi-gcc
AR = $(TOOLCHAIN_PATH_A15)/bin/arm-none-eabi-ar
LNK = $(TOOLCHAIN_PATH_A15)/bin/arm-none-eabi-gcc
SIZE = $(TOOLCHAIN_PATH_A15)/bin/arm-none-eabi-size

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN = le
else
  RTSLIB_ENDIAN = be
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),COFF)
  CSWITCH_FORMAT = ti_arm9_abi
  RTSLIB_FORMAT = tiarm9
endif
ifeq ($(FORMAT),ELF)
  CSWITCH_FORMAT = eabi
  RTSLIB_FORMAT = eabi
endif

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -Wimplicit -Wall -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections -c -mcpu=cortex-a15 -g -mfpu=neon -mfloat-abi=hard -mabi=aapcs -mapcs-frame -D__ARMv7
ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)
  CFLAGS_INTERNAL += -Werror
  LNKFLAGS_INTERNAL_COMMON += -Werror
endif
CFLAGS_DIROPTS =

# CFLAGS based on profile selected
ifeq ($(BUILD_PROFILE_$(CORE)), debug)
  CFLAGS_INTERNAL += -D_DEBUG_=1
  LNKFLAGS_INTERNAL_BUILD_PROFILE =
endif
ifeq ($(BUILD_PROFILE_$(CORE)), release)
  CFLAGS_INTERNAL += -O2 -s -DNDEBUG
  LNKFLAGS_INTERNAL_BUILD_PROFILE = -O2
endif

# XDC specific CFLAGS
CFLAGS_XDCINTERNAL = -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_target_name__=A15F -Dxdc_bld__profile_$(BUILD_PROFILE_$(CORE))
ifndef MODULE_NAME
  XDC_HFILE_NAME = $(basename $(XDC_CFG_FILE_$(CORE)))
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__='$(CONFIGURO_DIR)/package/cfg/$(XDC_HFILE_NAME)_pa15fg.h'
endif
LNKFLAGS_INTERNAL_BUILD_PROFILE =

# This CFLAG is added to include header files for re-entrancy support when migrating to BIOS version 6.37.01.24. XDC tools version 3.25.05.94
CFLAGS_FOR_REENTRANCY_SUPPORT = -I$(BIOSROOT)/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_INTERNAL) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_COMP_COMMON)
_XDCFLAGS = $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_INTERNAL) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_COMP_COMMON)

ifeq ($($(MODULE_NAME)_BOARD_DEPENDENCY),yes)
  _CFLAGS += $(CFLAGS_LOCAL_$(BOARD)) $(CFLAGS_GLOBAL_$(BOARD))
  _XDCFLAGS += $(CFLAGS_LOCAL_$(BOARD)) $(CFLAGS_GLOBAL_$(BOARD))
else
  ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
    _CFLAGS += $(CFLAGS_LOCAL_$(BOARD)) $(CFLAGS_GLOBAL_$(BOARD))
    _XDCFLAGS += $(CFLAGS_LOCAL_$(BOARD)) $(CFLAGS_GLOBAL_$(BOARD))
  else
    _CFLAGS += $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_GLOBAL_$(SOC))
    _XDCFLAGS += $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_GLOBAL_$(SOC))
  endif
endif

ifneq ($(XDC_CFG_FILE_$(CORE)),)
  _CFLAGS += $(CFLAGS_XDCINTERNAL) $(CFLAGS_FOR_REENTRANCY_SUPPORT)
  _XDCFLAGS += $(CFLAGS_XDCINTERNAL) $(CFLAGS_FOR_REENTRANCY_SUPPORT)
else
  ifneq ($(findstring xdc, $(INCLUDE_EXTERNAL_INTERFACES)),)
      _CFLAGS += $(CFLAGS_XDCINTERNAL)
      _XDCFLAGS += $(CFLAGS_XDCINTERNAL)
  endif
endif

#Add some additional include paths
INCLUDES += -I$(evealg_PATH)/apps/apps_nonbam/inc
INCLUDES += -I$(evealg_PATH)/
INCLUDES += -I$(evealg_PATH)/common

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) -MD -MF $(DEPDIR)/$(basename $(notdir $<)).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

$(OBJ_PATHS_CPP): $(OBJDIR)/%.$(OBJEXT): %.cpp | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) -MD -MF $(DEPDIR)/$(basename $(notdir $<)).P $(_CFLAGS) -Wno-write-strings $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

ASMFLAGS = $(ASMFLAGS_INTERNAL) $(ASMFLAGS_GLOBAL_$(CORE)) $(ASMFLAGS_LOCAL_COMMON) $(ASMFLAGS_LOCAL_$(CORE)) $(ASMFLAGS_LOCAL_$(BOARD)) $(ASMFLAGS_LOCAL_$(SOC)) $(ASMFLAGS_APP_DEFINES) $(ASMFLAGS_COMP_COMMON) $(ASMFLAGS_GLOBAL_$(BOARD))
# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) -c -x assembler-with-cpp $(_CFLAGS) $(ASMFLAGS) $(INCLUDES) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying to $(PACKAGE_RELPATH)/$($(APP_NAME)$(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(PACKAGE_ROOT)/$($(APP_NAME)$(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(PACKAGE_ROOT)/$($(APP_NAME)$(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = cr

# Archive/library file creation
$(LIBDIR)/$(LIBNAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) | $(LIBDIR)
	$(ECHO) \#
	$(ECHO) \# Archiving $(PRINT_MESSAGE) into $@ ...
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP)

$(LIBDIR)/$(LIBNAME).$(LIBEXT)_size: $(LIBDIR)/$(LIBNAME).$(LIBEXT)
	$(ECHO) \#
	$(ECHO) \# Computing sectti size $(PRINT_MESSAGE) info into $@.txt ...
	$(ECHO) \#
	$(SIZE) -t $(subst _size,,$@) > $@.txt

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON += -Wl,-static -Wl,--gc-sections -nostartfiles -mfloat-abi=hard --specs=rdimon.specs
ifneq ($(GCC_FLOAT_PATH),FPU)
LNKFLAGS_INTERNAL_COMMON += --specs=nano.specs
endif

ifeq ($($(APP_NAME)_FP_DEPENDENCY),yes)
  LNKFLAGS_INTERNAL_COMMON += -u _printf_float
endif

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_BUILD_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

# Path of the RTS library - normally doesn't change for a given tool-chain
RTSLIB_PATH =

LIB_PATHS += $(APP_LIBS_$(CORE))
LIB_PATHS += $(EXT_LIB_a15_0)
LIB_PATHS += $(RTSLIB_PATH)

#if float type is not FPU use hard lib
ifneq ($(GCC_FLOAT_PATH),FPU)
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  LIB_PATHS_DIR = $(bios_PATH)/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/hard
else
  LIB_PATHS_DIR  = $(HARDLIB_PATH)
  LIB_PATHS_DIR += $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/hard
  LIB_PATHS     += $(HARDLIB_PATH)/libgcc.a $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/hard/libc_nano.a $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/hard/libm.a  $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/hard/librdimon_nano.a $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/hard/libg_nano.a
endif
else
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  LIB_PATHS_DIR = $(bios_PATH)/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/fpu
else
  LIB_PATHS_DIR  = $(FPULIB_PATH)
  LIB_PATHS_DIR += $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/fpu
  LIB_PATHS     += $(FPULIB_PATH)/libgcc.a $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/fpu/libc.a $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/fpu/libm.a  $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/fpu/librdimon.a $(TOOLCHAIN_PATH_A15)/arm-none-eabi/lib/fpu/libg.a
endif
endif
LNK_LIBS = $(addprefix -L,$(LIB_PATHS_DIR))
LNK_LIBS += $(addprefix -L,$(LIB_PATHS))
LNK_LIBS += $(addprefix -L,$(EXT_LIB_PATHS))

# Added -lgcc twice to support both "before" and "after" order with -lm
# This is required to satisfy some linking order to support
# some Math/Algo kernals on A15
LNK_LIBS += -lstdc++ -lgcc -lm -lgcc -lc -lrdimon

ifneq ($(EXTERNAL_LNKCMD_FILE_LOCAL),)
LNKCMD_PREFIX = -Wl,-T,
EXTERNAL_LNKCMD_FILE = $(addprefix $(LNKCMD_PREFIX), $(EXTERNAL_LNKCMD_FILE_LOCAL))
endif

# Linker - to create executable file
ifeq ($(LOCAL_APP_NAME),)
 EXE_NAME = $(BINDIR)/$(APP_NAME)_$(CORE)_$(BUILD_PROFILE_$(CORE)).$(EXEEXT)
else
 ifeq ($(BUILD_PROFILE_$(CORE)),prod_release)
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME).$(EXEEXT)
 else
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME)_$(BUILD_PROFILE_$(CORE)).$(EXEEXT)
 endif
endif

ifneq ($(XDC_CFG_FILE_$(CORE)),)
$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(LIB_PATHS) $(LNKCMD_FILE) $(OBJDIR)/$(CFG_COBJ_XDC)
	$(CP) $(CONFIGURO_DIR)/package/cfg/*.rov.xs $(BINDIR)
else
$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(LIB_PATHS) $(LNKCMD_FILE)
endif
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) -Wl,-T,$(LNKCMD_FILE) $(EXTERNAL_LNKCMD_FILE) -Wl,-Map=$@.map -o $@ $(EXT_LIB_a15_0) -Wl,--start-group $(LIB_PATHS) $(EXT_LIB_PATHS) $(LNK_LIBS) -Wl,--end-group
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

# XDC specific - assemble XDC-Configuro command
ifeq ($(BUILD_PROFILE_$(CORE)),prod_release)
  CONFIGURO_BUILD_PROFILE = release
else
  CONFIGURO_BUILD_PROFILE = $(BUILD_PROFILE_$(CORE))
endif

_XDC_GREP_STRING = \"$(XDC_GREP_STRING)\"
EGREP_CMD = $(EGREP) -ivw $(XDC_GREP_STRING) $(XDCLNKCMD_FILE)

ifeq ($(OS),Windows_NT)
EVERYONE = $(word 1,$(shell whoami -groups | findstr "S-1-1-0"))
endif

# Invoke configuro for the rest of the components
#  NOTE: 1. String handling is having issues with various make versions when the
#           cammand is directly tried to be given below. Hence, as a work-around,
#           the command is re-directed to a file (shell or batch file) and then
#           executed
#        2. The linker.cmd file generated, includes the libraries generated by
#           XDC. An egrep to search for these and omit in the .cmd file is added
#           after configuro is done
xdc_configuro : $(CFG_C_XDC)
	$(MAKE) $(LNKCMD_FILE)

ifeq ($(DEST_ROOT),)
  XDC_BUILD_ROOT = .
else
  XDC_BUILD_ROOT = $(DEST_ROOT)
endif

$(CFG_C_XDC) $(LNKCMD_FILE) : $(XDC_CFG_FILE)
	$(ECHO) \# Invoking configuro...
	$(MKDIR) -p $(XDC_BUILD_ROOT)
	$(xdc_PATH)/xs xdc.tools.configuro --generationOnly -o $(CONFIGURO_DIR) -t $(TARGET_XDC) -p $(PLATFORM_XDC) \
               -r $(CONFIGURO_BUILD_PROFILE) -b $(CONFIG_BLD_XDC_$(ISA)) --ol $(LNKCMD_FILE) $(XDC_CFG_FILE_NAME)
	$(ECHO) \# Configuro done!

ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifndef MODULE_NAME
$(OBJDIR)/$(CFG_COBJ_XDC) : $(CFG_C_XDC)
	$(ECHO) \# Compiling generated $< to $(CONFIGURO_DIR)/package/cfg/$(CFG_COBJ_XDC) ...
	$(CC) $(_XDCFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS)-o $(CONFIGURO_DIR)/package/cfg/$(CFG_COBJ_XDC) $(CFG_C_XDC)
  endif
endif

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)
-include $(SRCS_CPP:%.cpp=$(DEPDIR)/%.P)

# Nothing beyond this point
