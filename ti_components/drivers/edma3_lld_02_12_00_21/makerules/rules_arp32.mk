#/*******************************************************************************
# *                                                                             *
# * Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/      *
# *                        ALL RIGHTS RESERVED                                  *
# *                                                                             *
# ******************************************************************************/

# Filename: rules_arp32.mk
#
# Make rules for EVE - This file has all the common rules and defines required
#                     for arp32 ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (currently it uses arp32cgt_1.0.2)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for arp32 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(CODEGEN_PATH_ARP32)/include

CC = $(CODEGEN_PATH_ARP32)/bin/cl-arp32
AR = $(CODEGEN_PATH_ARP32)/bin/ar-arp32
LNK = $(CODEGEN_PATH_ARP32)/bin/lnk-arp32

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN = 
else
  RTSLIB_ENDIAN = e
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),COFF)
  CSWITCH_FORMAT = 
  RTSLIB_FORMAT = 
endif
ifeq ($(FORMAT),ELF)
  CSWITCH_FORMAT = eabi
  RTSLIB_FORMAT = elf
endif

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -v210 -c -qq -pdsw225 --abi=$(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) --symdebug:dwarf

# Uncomment for misra C build
#CFLAGS_INTERNAL += --check_misra="all"

# Uncomment for Cpp enabled build
#CFLAGS_INTERNAL += --cpp_default

CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)

# XDC Specific defines
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifeq ($(PROFILE_$(CORE)),debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	CFG_LNKFILENAMEPART_XDC=
  endif
  ifeq ($(PROFILE_$(CORE)),release)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	CFG_LNKFILENAMEPART_XDC=
  endif
  ifeq ($(PROFILE_$(CORE)),whole_program_debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
    CFG_LNKFILENAMEPART_XDC=_x
  endif
  CFG_CFILE_XDC =$(patsubst %.cfg,%_$(CFG_CFILENAMEPART_XDC).c,$(notdir $(XDC_CFG_FILE_$(CORE))))
  CFG_C_XDC = $(addprefix $(CONFIGURO_DIR)/package/cfg/,$(CFG_CFILE_XDC))
  XDCLNKCMD_FILE =$(patsubst %.c, %$(CFG_LNKFILENAMEPART_XDC).xdl, $(CFG_C_XDC))
  CFG_COBJ_XDC = $(patsubst %.c,%.$(OBJEXT),$(CFG_CFILE_XDC))
#  OBJ_PATHS += $(CFG_COBJ_XDC)
  LNKCMD_FILE = $(CONFIGURO_DIR)/linker_mod.cmd
  SPACE := 
  SPACE += 
  XDC_GREP_STRING = $(CONFIGURO_DIRNAME)
#  XDC_GREP_STRING = $(subst $(SPACE),\|,$(COMP_LIST_$(CORE)))
#  XDC_GREP_STRING += \|$(CONFIGURO_DIRNAME)
endif

# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), debug)
 CFLAGS_XDCINTERNAL += -Dxdc_target_name__=ARP32_far -Dxdc_target_types__=ti/targets/arp32/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_6_1 -D_DEBUG_=1 
  ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__='$(CONFIGURO_DIR)/package/cfg/$(XDC_CFG_BASE_FILE_NAME)_pearp32.h' 
 endif
 LNKFLAGS_INTERNAL_PROFILE = 
endif

ifeq ($(PROFILE_$(CORE)), release)
 CFLAGS_XDCINTERNAL += -Dxdc_target_name__=ARP32_far -Dxdc_target_types__=ti/targets/arp32/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_6_1 -D_DEBUG_=0 -o2
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__='$(CONFIGURO_DIR)/package/cfg/$(XDC_CFG_BASE_FILE_NAME)_pearp32.h' 
 endif
 LNKFLAGS_INTERNAL_PROFILE = -o2
endif

# For generic platform define GENERIC in CFLAGS
ifeq ($(PLATFORM),generic)
 CFLAGS_XDCINTERNAL += -DGENERIC
endif

# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST_EVE_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
  
  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the local CORE...
  CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_EVE_LOCAL),-D_LOCAL_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_EVE_LOCAL),-D_BUILD_$(PKG)_)
  ifeq ($(CORE),eve)
    PKG_LIST_EVE_REMOTE = $(foreach COMP,$(COMP_LIST_eve),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_EVE_
  endif
  
  PKG_LIST_EVE_REMOTE = $(foreach COMP,$(COMP_LIST_eve),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the remote CORE...
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_EVE_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_EVE_REMOTE),-D_BUILD_$(PKG)_)
endif

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_XDCINTERNAL) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $< to $@ ...
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fc $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fc $<

# Archive flags - normally doesn't change
ARFLAGS = rq

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS)
	$(ECHO) \#
	$(ECHO) \# Archiving $(OBJ_PATHS) into $@...
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS)

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON = -w -q -u _c_int00 --silicon_version=210 -c --rom_model

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE)) 

# Path of the RTS library - normally doesn't change for a given tool-chain
RTSLIB_PATH = $(CODEGEN_PATH_ARP32)/lib/rtsarp32_v200.lib
LIB_PATHS += $(RTSLIB_PATH)

LNK_LIBS = $(addprefix -l,$(LIB_PATHS))
ifeq ($(DEST_ROOT),)
 TMPOBJDIR = .
else
 TMPOBJDIR = $(OBJDIR)
endif
# Linker - to create executable file 
$(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE)).$(EXEEXT) : $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE) $(OBJDIR)/$(CFG_COBJ_XDC)
	$(ECHO) \# Linking into $@
	$(ECHO) \#
	cd $(TMPOBJDIR) && $(LNK) $(_LNKFLAGS) $(OBJ_PATHS) -l$(LNKCMD_FILE) sample_app/linker.cmd -o $@ -m $@.map $(LNK_LIBS)
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

ifeq ($(CONFIG_BLD_XDC_CUSTOM),)
  CONFIG_BLD_FILE = $(CONFIG_BLD_XDC_$(ISA))
else
  CONFIG_BLD_FILE = $(CONFIG_BLD_XDC_CUSTOM)
endif
ifeq ($(PLATFORM_XDC_CUSTOM),)
  PLATFORM_XDC_NAME = $(PLATFORM_XDC)
else
  PLATFORM_XDC_NAME = $(PLATFORM_XDC_CUSTOM)
endif

# XDC specific - assemble XDC-Configuro command
#CONFIGURO_CMD = $(xdc_PATH)/xs xdc.tools.configuro --generationOnly -o $(CONFIGURO_DIR) -t $(TARGET_XDC) -p $(PLATFORM_XDC) \
#               $(CFGARGS_XDC) -r $(PROFILE_$(CORE)) -b $(CONFIG_BLD_XDC_$(ISA)) $(XDC_CFG_FILE_NAME)
CONFIGURO_CMD = $(xdc_PATH)/xs xdc.tools.configuro --generationOnly -o $(CONFIGURO_DIR) -t $(TARGET_XDC) -p $(PLATFORM_XDC_NAME) \
               -r $(PROFILE_$(CORE)) -c $(CODEGEN_PATH_ARP32) -b $(CONFIG_BLD_FILE) $(XDC_CFG_FILE_NAME)			   
_XDC_GREP_STRING = \"$(XDC_GREP_STRING)\"
EGREP_CMD = $(EGREP) -ivw $(XDC_GREP_STRING) $(XDCLNKCMD_FILE)

ifneq ($(DEST_ROOT),)
 DEST_ROOT += /
endif
# Invoke configuro for the rest of the components
#  NOTE: 1. String handling is having issues with various make versions when the 
#           cammand is directly tried to be given below. Hence, as a work-around, 
#           the command is re-directed to a file (shell or batch file) and then 
#           executed
#        2. The linker.cmd file generated, includes the libraries generated by
#           XDC. An egrep to search for these and omit in the .cmd file is added
#           after configuro is done
#$(CFG_CFILE_XDC) : $(XDC_CFG_FILE)
xdc_configuro : $(XDC_CFG_FILE) $(CONFIGURO_DIR)
	$(ECHO) \# Invoking configuro...
	$(ECHO) -e $(CONFIGURO_CMD) > $(DEST_ROOT)maketemp_configuro_cmd_$(CORE).bat
ifeq ($(OS),Windows_NT)
	ICACLS $(DEST_ROOT)maketemp_configuro_cmd_$(CORE).bat /q /c /t /grant Everyone:F /T
	$(DEST_ROOT)maketemp_configuro_cmd_$(CORE).bat
else
	$(CHMOD) a+x $(DEST_ROOT)maketemp_configuro_cmd_$(CORE).bat
	./$(DEST_ROOT)maketemp_configuro_cmd_$(CORE).bat
endif
	$(CP) $(XDCLNKCMD_FILE) $(LNKCMD_FILE)
#	$(ECHO) @ $(EGREP_CMD) > maketemp_egrep_cmd.bat
#	./maketemp_egrep_cmd.bat | $(CYGWINPATH)/bin/tail -n+3 > $(LNKCMD_FILE)
#	$(EGREP_CMD) > $(LNKCMD_FILE)
#	$(EGREP) -iv "$(XDC_GREP_STRING)" $(XDCLNKCMD_FILE) > $(LNKCMD_FILE)
	$(ECHO) \# Configuro done!

$(LNKCMD_FILE) :
#	$(CP) $(XDCLNKCMD_FILE) $(LNKCMD_FILE)
#	$(ECHO) @ $(EGREP_CMD) > maketemp_egrep_cmd.bat
#	./maketemp_egrep_cmd.bat | $(CYGWINPATH)/bin/tail -n+3 > $(LNKCMD_FILE)
#	$(EGREP_CMD) > $(LNKCMD_FILE)
 
ifndef MODULE_NAME
$(OBJDIR)/$(CFG_COBJ_XDC) : $(CFG_C_XDC)
	$(ECHO) \# Compiling generated $< to $@ ...
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fc $(CFG_C_XDC)
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fc $(CFG_C_XDC)
ifeq ($(OS),Windows_NT)
	ICACLS  $@ /q /c /grant Everyone:F /T
	ICACLS $(CONFIGURO_DIR)/package/cfg/$(CFG_COBJ_XDC) /q /c /grant Everyone:F /T
endif
	$(CP) $(OBJDIR)/$(CFG_COBJ_XDC) $(CONFIGURO_DIR)/package/cfg/$(CFG_COBJ_XDC)
endif

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)

# Nothing beyond this point
