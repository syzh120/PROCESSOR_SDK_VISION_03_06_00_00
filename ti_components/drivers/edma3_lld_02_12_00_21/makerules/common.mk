# Filename: common.mk
#
# Common make file - This file has common rules and definitions that are common
#                    across platforms/cores/ISAs/SoCs
#
# This file needs to change when:
#     1. common rule/define has to be added or modified
#

#
# Include make paths and options for all supported targets/platforms
#

include $(ROOTDIR)/makerules/build_config.mk
include $(ROOTDIR)/makerules/env.mk
include $(ROOTDIR)/makerules/platform.mk

#.DEFAULT_GOAL := all

.PHONY : all clean gendirs m3video m3vpss c6xdsp a8host arm9

all : $(CORE)

# Define directories that are going to be created as a part of build process
ifdef MODULE_NAME
  ifeq ($($(MODULE_NAME)_PLATFORM_DEPENDENCY),yes)
    ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
      DEPENDENCY_SUB_PATH = $(PLATFORM)/$(CORE)
    else
      DEPENDENCY_SUB_PATH = $(PLATFORM)/$(ISA)
    endif
  else
    ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
      DEPENDENCY_SUB_PATH = $(CORE)
    else
      DEPENDENCY_SUB_PATH = $(ISA)
    endif
  endif
endif

ifeq ($(DEST_ROOT),)
 ifdef MODULE_NAME
  OBJDIR = obj/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
  LIBDIR = lib/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
 else
  OBJDIR = obj/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))
  BINDIR = bin/$(PLATFORM)
 endif
else
  ifdef MODULE_NAME
    OBJDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/obj/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
    LIBDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/lib/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
  else
    OBJDIR = $(DEST_ROOT)/$(APP_NAME)/obj/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))
    BINDIR = $(DEST_ROOT)/$(APP_NAME)/bin/$(PLATFORM)
  endif
endif

CONFIGURO_DIRNAME = $(APP_NAME)_configuro
ifeq ($(XDC_CFG_DIR),)
 CONFIGURO_DIR = $(OBJDIR)/$(CONFIGURO_DIRNAME)
 XDC_CFG_FILE_NAME = $(XDC_CFG_FILE_$(CORE))
else
 CONFIGURO_DIR = $(XDC_CFG_DIR)/configuro/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))/$(CONFIGURO_DIRNAME)
# XDC_CFG_FILE_NAME = $(XDC_CFG_DIR)/$(XDC_CFG_FILE_$(CORE))
 XDC_CFG_FILE_NAME = $(XDC_CFG_FILE_$(CORE))
endif

DEPDIR = $(OBJDIR)/.deps
DEPFILE = $(DEPDIR)/$(*F)

# Create directories
$(OBJDIR) :
	$(MKDIR) -p $(OBJDIR)

$(DEPDIR) :
	$(MKDIR) -p $(DEPDIR)

$(LIBDIR) :
	$(MKDIR) -p $(LIBDIR)

$(BINDIR) :
	$(MKDIR) -p $(BINDIR)

$(CONFIGURO_DIR) :
	$(MKDIR) -p $(OBJDIR)
	$(MKDIR) -p $(DEPDIR)
	$(MKDIR) -p $(CONFIGURO_DIR)

#
# Common variables
#

# Assemble list of source file names
SRCS = $(SRCS_COMMON) $(SRCS_$(CORE)) $(SRCS_$(SOC)) $(SRCS_$(PLATFORM))

# Define search paths
VPATH = $(SRCDIR)

# Following 'if...' block is for an application.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  # For each of the packages (or modules), get a list of source files that are
  # marked to be compiled in app stage of the build (or in the context in the app)
  SRCS_APPSTG_FILES = $(foreach PKG, $(PKG_LIST), $($(PKG)_APP_STAGE_FILES))
  # The app has to compile package cfg source files in its context. The name
  # of the file assumed is <MOD>_cfg.c under the top-level directory - i.e.
  # specified by <MOD>_PATH variable
  #SRCS_CFG = $(addsuffix _cfg.c,$(PKG_LIST))
  SRCS += $(SRCS_APPSTG_FILES)
  PKG_PATHS = $(foreach PKG,$(PKG_LIST),$($(PKG)_PATH))
  VPATH += $(PKG_PATHS)
endif

# Change the extension from C to $(OBJEXT) and also add path
OBJ_PATHS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(SRCS))
OBJ_PATHS_SO = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT_SO), $(SRCS))

# Assemble include paths here
INCLUDE_EXTERNAL = $(foreach INCL,$(INCLUDE_EXTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_ALL = $(CODEGEN_INCLUDE) $(INCDIR) $(INCLUDE_EXTERNAL)

# Add prefix "-I" to each of the include paths in INCLUDE_ALL
INCLUDES = $(addprefix -I,$(INCLUDE_ALL))

# Create rule to "make" all packages
.PHONY : $(PKG_LIST)
$(PKG_LIST) :
	$(ECHO) \# Making $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$@...
	$(MAKE) -C $($@_PATH)

# Get libraries for all the packages
# LIBS = $(foreach LIB,$(PKG_LIST),$(LIB).$(LIBEXT))
define GET_COMP_DEPENDENCY_SUB_PATH
  ifeq ($$($(1)_PLATFORM_DEPENDENCY),yes)
    ifeq ($$($(1)_CORE_DEPENDENCY),yes)
      $(1)_DEPSUBPATH = $(PLATFORM)/$(CORE)
    else
      $(1)_DEPSUBPATH = $(PLATFORM)/$(ISA)
    endif
   else
    ifeq ($$($(1)_CORE_DEPENDENCY),yes)
      $(1)_DEPSUBPATH = $(CORE)
    else
      $(1)_DEPSUBPATH = $(ISA)
    endif
  endif
endef

$(foreach LIB,$(PKG_LIST),$(eval $(call GET_COMP_DEPENDENCY_SUB_PATH,$(LIB))))

ifeq ($(DEST_ROOT),)
LIB_PATHS = $(foreach LIB,$(PKG_LIST),$($(LIB)_PATH)/lib/$($(LIB)_DEPSUBPATH)/$(PROFILE_$(CORE))/$(LIB).$(LIBEXT))
else
LIB_PATHS = $(foreach LIB,$(PKG_LIST),$(DEST_ROOT)/$($(LIB)_RELPATH)/lib/$($(LIB)_DEPSUBPATH)/$(PROFILE_$(CORE))/$(LIB).$(LIBEXT))
endif

# XDC Specific defines
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifeq ($(PROFILE_$(CORE)),debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  endif
  ifeq ($(PROFILE_$(CORE)),whole_program_debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
    CFG_LNKFILENAMEPART_XDC=_x
  endif
  CFG_CFILE_XDC =$(patsubst %.cfg,%_$(CFG_CFILENAMEPART_XDC).c,$(XDC_CFG_FILE_$(CORE)))
  CFG_C_XDC = $(addprefix $(CONFIGURO_DIR)/package/cfg/,$(CFG_CFILE_XDC))
  XDCLNKCMD_FILE =$(patsubst %.c, %$(CFG_LNKFILENAMEPART_XDC).xdl, $(CFG_C_XDC))
  CFG_COBJ_XDC = $(patsubst %.c,%.$(OBJEXT),$(CFG_CFILE_XDC))
  XDC_CFG_BASE_FILE_NAME = $(basename $(notdir $(XDC_CFG_FILE_$(CORE))))
#  OBJ_PATHS += $(CFG_COBJ_XDC)
  LNKCMD_FILE = $(CONFIGURO_DIR)/linker_mod.cmd
ifeq ($(ISA),a15)
  LNKCMD_FILE = $(CONFIGURO_DIR)/linker.cmd
endif
  SPACE :=
  SPACE +=
  XDC_GREP_STRING = $(CONFIGURO_DIRNAME)
#  XDC_GREP_STRING = $(subst $(SPACE),\|,$(COMP_LIST_$(CORE)))
#  XDC_GREP_STRING += \|$(CONFIGURO_DIRNAME)
endif

# Include make rules for ISA that is built in this iteration
#   eg: rules_m3.mk
ifneq ($(TOOLCHAIN_$(ISA)),)
  TOOLCHAIN_SELECTION = $(TOOLCHAIN_$(ISA))_
endif
include $(ROOTDIR)/makerules/rules_$(TOOLCHAIN_SELECTION)$(ISA).mk

ifdef MODULE_NAME
# Rules for module; this iteration is for a module

# Clean Object and Library (archive) directories
clean :
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/* $(LIBDIR)/*

# Create dependencies list to ultimately create module archive library file
ifeq ($(PLATFORM), $(filter $(PLATFORM),tci6636k2h-evm tci6638k2k-evm tci6630k2l-evm c66ak2e-evm))
ifeq ($(TOOLCHAIN_$(ISA)),GCC)
$(CORE) : $(OBJDIR) $(DEPDIR) $(LIBDIR) $(LIBDIR)/$(MODULE_NAME).$(LIBEXT) $(LIBDIR)/$(MODULE_NAME).$(LIBEXT_SO)
else
$(CORE) : $(OBJDIR) $(DEPDIR) $(LIBDIR) $(LIBDIR)/$(MODULE_NAME).$(LIBEXT)
endif
else
$(CORE) : $(OBJDIR) $(DEPDIR) $(LIBDIR) $(LIBDIR)/$(MODULE_NAME).$(LIBEXT)
endif

else
# Rules for application; this iteration is for an app

# Clean Object, Binary and Configuro generated directories
clean :
	$(RM) -rf $(CONFIGURO_DIR)
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/*

# Create dependencies list to ultimately create application executable binary
$(CORE) : $(OBJDIR) $(BINDIR) $(DEPDIR) $(CONFIGURO_DIR) $(PKG_LIST) $(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE)).$(EXEEXT)

endif

# Nothing beyond this point

