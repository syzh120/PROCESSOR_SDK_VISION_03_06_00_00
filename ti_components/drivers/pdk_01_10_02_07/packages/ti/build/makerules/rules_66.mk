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

# Filename: rules_66.mk
#
# Make rules for c66x - This file has all the common rules and defines required
#                     for c66x ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (currently it uses CG600_7.2.0.B2)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for C66 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(C6X_GEN_INSTALL_PATH)/include
CC = $(C6X_GEN_INSTALL_PATH)/bin/cl6x
AR = $(C6X_GEN_INSTALL_PATH)/bin/ar6x
LNK = $(C6X_GEN_INSTALL_PATH)/bin/lnk6x
SIZE = $(C6X_GEN_INSTALL_PATH)/bin/ofd6x

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN =
else
  RTSLIB_ENDIAN = e
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),COFF)
  CSWITCH_FORMAT = ti_arm9_abi
  RTSLIB_FORMAT = _tiarm9
  CSWITCH_FORMAT =
  XDCINTERNAL_DEFINES = -Dxdc_target_types__=ti/targets/std.h
endif
ifeq ($(FORMAT),ELF)
  CSWITCH_FORMAT = --abi=eabi
  RTSLIB_FORMAT = _elf
  XDCINTERNAL_DEFINES = -Dxdc_target_types__=ti/targets/elf/std.h
endif

#########

# XDC Specific defines
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifeq ($(BUILD_PROFILE_$(CORE)),debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA_EXT)
	CFG_LNKFILENAMEPART_XDC=
  endif
  ifeq ($(BUILD_PROFILE_$(CORE)),release)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA_EXT)
  endif
  ifeq ($(BUILD_PROFILE_$(CORE)),whole_program_debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
    CFG_LNKFILENAMEPART_XDC=_x
  endif
  CFG_CFILE_XDC =$(patsubst %.cfg,%_$(CFG_CFILENAMEPART_XDC).c,$(notdir $(XDC_CFG_FILE_$(CORE))))
  CFG_C_XDC = $(addprefix $(CONFIGURO_DIR)/package/cfg/,$(CFG_CFILE_XDC))
  CFG_C_NEW_XDC = $(CONFIGURO_DIR)/package/cfg
  XDCLNKCMD_FILE =$(patsubst %.c, %$(CFG_LNKFILENAMEPART_XDC).xdl, $(CFG_C_XDC))
  CFG_COBJ_XDC = $(patsubst %.c,%.$(OBJEXT),$(CFG_CFILE_XDC))
  LNKCMD_FILE = $(CONFIGURO_DIR)/linker_mod.cmd
  SPACE :=
  SPACE +=
  XDC_GREP_STRING = $(CONFIGURO_DIRNAME)
endif


#########

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -mv6600 $(CSWITCH_FORMAT) -q -mi10 -mo -pden -pds=238 -pds=880 -pds1110 --program_level_compile -g --endian=$(ENDIAN) -eo.$(OBJEXT) -ea.$(ASMEXT)
ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)
  CFLAGS_INTERNAL += --emit_warnings_as_errors
  LNKFLAGS_INTERNAL_COMMON += --emit_warnings_as_errors
endif
CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)
CFLAGS_NEW_DIROPTS = -fr=$(CFG_C_NEW_XDC) -fs=$(CFG_C_NEW_XDC)

#########XDC Config File for DSP##########


XDC_HFILE_NAME = $(basename $(XDC_CFG_FILE_$(CORE)))
# CFLAGS based on profile selected
ifeq ($(BUILD_PROFILE_$(CORE)), debug)
 CFLAGS_INTERNAL +=
 CFLAGS_XDCINTERNAL = -Dxdc_target_name__=C66 -D_DEBUG_=1
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__='$(CONFIGURO_DIR)/package/cfg/$(XDC_HFILE_NAME)_pe66.h'
 endif
 LNKFLAGS_INTERNAL_BUILD_PROFILE =
endif

ifeq ($(BUILD_PROFILE_$(CORE)), release)
 LNKFLAGS_INTERNAL_BUILD_PROFILE =
 CFLAGS_INTERNAL += -o3 --optimize_with_debug
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__='$(CONFIGURO_DIR)/package/cfg/$(XDC_HFILE_NAME)_pe66.h'
 endif
endif

# For generic board define GENERIC in CFLAGS
ifeq ($(BOARD),generic)
 CFLAGS_XDCINTERNAL += -DGENERIC
endif
CFLAGS_XDCINTERNAL += $(XDCINTERNAL_DEFINES)

########################################

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_INTERNAL) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_COMP_COMMON)
ifeq ($($(MODULE_NAME)_BOARD_DEPENDENCY),yes)
  _CFLAGS += $(CFLAGS_LOCAL_$(BOARD)) $(CFLAGS_GLOBAL_$(BOARD))
else
  ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
    _CFLAGS += $(CFLAGS_LOCAL_$(BOARD)) $(CFLAGS_GLOBAL_$(BOARD))
  else
    _CFLAGS += $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_GLOBAL_$(SOC))
  endif
endif
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  _CFLAGS += $(CFLAGS_XDCINTERNAL) $(CFLAGS_FOR_REENTRANCY_SUPPORT)
endif

# Decide the compile mode
COMPILEMODE = -fc
ifeq ($(CPLUSPLUS_BUILD), yes)
  COMPILEMODE = -fg
endif

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<


# Aid in transitioning hand-coded assembly from COFF to EABI
ifeq ($(FORMAT),ELF)
  ASMFLAGS = --strip_coff_underscore
endif

# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fa $<
	$(CC) $(_CFLAGS) $(ASMFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fa $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying to $(PACKAGE_RELPATH)/$($(APP_NAME)$(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(PACKAGE_ROOT)/$($(APP_NAME)$(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(PACKAGE_ROOT)/$($(APP_NAME)$(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = rq

# Archive/library file creation
$(LIBDIR)/$(LIBNAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) | $(LIBDIR)
	$(ECHO) \#
	$(ECHO) \# Archiving $(PRINT_MESSAGE) into $@ ...
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS)

$(LIBDIR)/$(LIBNAME).$(LIBEXT)_size: $(LIBDIR)/$(LIBNAME).$(LIBEXT)
	$(ECHO) \#
	$(ECHO) \# Computing sectti size $(PRINT_MESSAGE) info into $@.txt ...
	$(ECHO) \#
	$(SIZE) -x $(subst _size,,$@) > $@temp
	$(SECTTI) $@temp > $@.txt
	$(RM)   $@temp

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON += --warn_sections -q -e=_c_int00 --silicon_version=6600 -c

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_BUILD_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

# Path of the RTS library - normally doesn't change for a given tool-chain
#Let the linker choose the required library
RTSLIB_PATH = $(C6X_GEN_INSTALL_PATH)/lib/libc.a
LIB_PATHS += $(RTSLIB_PATH)

LNK_LIBS = $(addprefix -l,$(LIB_PATHS))
LNK_LIBS += $(addprefix -l,$(EXT_LIB_PATHS))

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
$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE) $(CFG_C_NEW_XDC)/$(CFG_COBJ_XDC)
else
$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE)
endif
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) -l$(LNKCMD_FILE) -o $@ -m $@.map $(LNK_LIBS)
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
$(CFG_C_NEW_XDC)/$(CFG_COBJ_XDC) : $(CFG_C_XDC)
	$(ECHO) \# Compiling generated $(CFG_COBJ_XDC)
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_NEW_DIROPTS) -fc $(CFG_C_XDC)
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_NEW_DIROPTS) -fc $(CFG_C_XDC)
  endif
endif

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)

# Nothing beyond this point
