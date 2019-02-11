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

include $(ROOTDIR)/build/rtos/makerules/build_config.mk
include $(ROOTDIR)/build/rtos/makerules/platform.mk
include $(ROOTDIR)/build/rtos/makerules/env.mk

OUTFILE=$(vision_sdk_PATH)/links_fw/include/config/$(MAKEAPPNAME)/$(MAKECONFIG)/linksInclude_$(CORE).h
OUTLINE=$(ECHO) $(1) >> $(OUTFILE)

.PHONY : all clean gendirs m3video m3vpss c6xdsp c66x c66xdsp m4video m4vpss host c66xdsp_1 c66xdsp_2 ipu1_0 ipu1_1 ipu2 arp32_1 arp32_2 arp32_3 arp32_4 a15_0

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
  PACKAGEDIR = package/$(DEPENDENCY_SUB_PATH)/$(PACKAGE_SELECT)
else
  ifdef MODULE_NAME
    OBJDIR = $(DEST_ROOT)/obj/$(MODULE_NAME)/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
    LIBDIR = $(DEST_ROOT)/lib/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
  else
    OBJDIR = $(DEST_ROOT)/obj/$(APP_NAME)/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))
    BINDIR = $(DEST_ROOT)/$(APP_NAME)/bin/$(PLATFORM)
  endif
  PACKAGEDIR = $(DEST_ROOT/package/$(PACKAGE_SELECT)
endif

CONFIGURO_DIRNAME = $(APP_NAME)_configuro
ifeq ($(XDC_CFG_DIR),)
 CONFIGURO_DIR = $(OBJDIR)/$(CONFIGURO_DIRNAME)
 XDC_CFG_FILE_NAME = $(XDC_CFG_FILE_$(CORE))
else
 CONFIGURO_DIR = $(XDC_CFG_DIR)/configuro/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))/$(CONFIGURO_DIRNAME)
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

$(PACKAGEDIR) :
	$(MKDIR) -p $(PACKAGEDIR)

#
# Common variables
#

# Assemble list of source file names
SRCS = $(SRCS_COMMON) $(SRCS_$(CORE)) $(SRCS_$(SOCFAMILY))
SRCS_ASM = $(SRCS_ASM_COMMON) $(SRCS_ASM_$(CORE)) $(SRCS_ASM_$(SOCFAMILY))
SRCS_CPP = $(SRCS_CPP_COMMON) $(SRCS_CPP_$(CORE)) $(SRCS_CPP_$(SOCFAMILY))

ifneq ($(SOCFAMILY),$(PLATFORM))
SRCS += $(SRCS_$(PLATFORM))
SRCS_ASM += $(SRCS_ASM_$(PLATFORM))
SRCS_CPP += $(SRCS_CPP_$(PLATFORM))
endif #ifneq ($(SOCFAMILY,$(PLATFORM))

ifneq ($(SOC),$(SOCFAMILY))
SRCS += $(SRCS_$(SOC))
SRCS_ASM += $(SRCS_ASM_$(SOC))
SRCS_CPP += $(SRCS_CPP_$(SOC))
endif #ifneq ($(SOC),$(SOCFAMILY))

# Only applicable for EVE Kernel C files
SRCS_K = $(SRCS_K_COMMON) $(SRCS_K_$(CORE)) $(SRCS_K_$(SOC)) $(SRCS_K_$(PLATFORM))

PACKAGE_SRCS = $(PACKAGE_SRCS_COMMON)

# Define search paths
VPATH = $(SRCDIR)

# Following 'if...' block is for an application.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app

  PKG_LIST = $(foreach COMP,$(COMP_LIST_COMMON),$($(COMP)_PKG_LIST))
  PKG_LIST += $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  NON_BSP_PKG_LIST = $(filter-out bsp_%,$(PKG_LIST))
  BSP_PKG_LIST = $(filter bsp_%,$(PKG_LIST))

  # For each of the packages (or modules), get a list of source files that are
  # marked to be compiled in app stage of the build (or in the context in the app)
  SRCS_APPSTG_FILES = $(foreach PKG, $(PKG_LIST), $($(PKG)_APP_STAGE_FILES))
  # The app has to compile package cfg source files in its context. The name
  # of the file assumed is <MOD>_cfg.c under the top-level directory - i.e.
  # specified by <MOD>_PATH variable
  SRCS += $(SRCS_APPSTG_FILES)
  PKG_PATHS = $(foreach PKG,$(PKG_LIST),$($(PKG)_PATH))
  VPATH += $(PKG_PATHS)

  export PKG_LIST
endif

# Change the extension from C to $(OBJEXT) and also add path
OBJ_PATHS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(SRCS))

# Change the extension from ASM to $(OBJEXT) and also add path
OBJ_PATHS_ASM = $(patsubst %.asm, $(OBJDIR)/%.$(OBJEXT), $(SRCS_ASM))

# Change the extension from .cpp to $(OBJEXT) and also add path
OBJ_PATHS_CPP = $(patsubst %.cpp, $(OBJDIR)/%.$(OBJEXT), $(SRCS_CPP))

# Change the extension from .k to $(OBJEXT) and also add path
OBJ_PATHS_K = $(patsubst %.k, $(OBJDIR)/%.$(OBJEXT), $(SRCS_K))

PACKAGE_PATHS = $(patsubst %, $(PACKAGEDIR)/%, $(PACKAGE_SRCS))

# Add prefix "-I" to each of the include paths in INCLUDE_ALL
INCLUDES = $(addprefix -I,$(INCLUDE_ALL))

# Create rule to "make" all packages
.PHONY : $(NON_BSP_PKG_LIST)
$(NON_BSP_PKG_LIST) :
	$(ECHO) \# Making $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$@...

.PHONY : $(BSP_PKG_LIST)
$(BSP_PKG_LIST) :
	$(ECHO)  \# Making $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$@...
	$(MAKE) -C $(pdk_PATH) CORE=ipu1_0 pdk BUILD_PROFILE=$(PROFILE_$(IPU_PRIMARY_CORE))

# Get libraries for all the packages
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

endif

# XDC Specific defines
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifeq ($(PROFILE_$(CORE)),debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  endif
  ifeq ($(PROFILE_$(CORE)),release)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  endif
  ifeq ($(PROFILE_$(CORE)),prod_release)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  endif
  CFG_CFILE_XDC =$(patsubst %.cfg,%_$(CFG_CFILENAMEPART_XDC).c,$(XDC_CFG_FILE_$(CORE)))
  CFG_C_XDC = $(addprefix $(CONFIGURO_DIR)/package/cfg/,$(CFG_CFILE_XDC))
  XDCLNKCMD_FILE =$(patsubst %.c, %$(CFG_LNKFILENAMEPART_XDC).xdl, $(CFG_C_XDC))
  CFG_COBJ_XDC = $(patsubst %.c,%.$(OBJEXT),$(CFG_CFILE_XDC))
  LNKCMD_FILE = $(CONFIGURO_DIR)/linker_mod.cmd
  SPACE :=
  SPACE +=
   XDC_GREP_STRING = $(CFG_COBJ_XDC)
endif

# Include make rules for ISA that is built in this iteration
#   eg: rules_m3.mk
include $(ROOTDIR)/build/rtos/makerules/rules_$(ISA).mk

package : $(PACKAGE_PATHS)

ifdef MODULE_NAME
# Rules for module; this iteration is for a module

# Clean Object and Library (archive) directories
clean :
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/* $(LIBDIR)/*

# Create dependencies list to ultimately create module archive library file
$(CORE) : $(OBJDIR) $(DEPDIR) $(LIBDIR)
	$(MAKE) $(LIBDIR)/$(MODULE_NAME).$(LIBEXT)

APP_LIB=$(LIBDIR)/$(MODULE_NAME).$(LIBEXT)
ifneq ("$(wildcard $(DEST_ROOT)/linksfwLibList_$(CORE)_$(PROFILE_$(CORE)).txt)","")
	APP_LIB_LIST=$(shell $(CAT) $(DEST_ROOT)/linksfwLibList_$(CORE)_$(PROFILE_$(CORE)).txt)
endif
APP_LIB_FILTER=$(filter $(APP_LIB),$(APP_LIB_LIST))

ifneq ("$(wildcard $(OUTFILE))","")
	LIB_INC_LIST = $(shell $(CAT) $(OUTFILE))
endif
LIB_INC_FILTER=$(filter $(MODULE_NAME),$(LIB_INC_LIST))

depend: $(LIBDIR)
ifneq "$(or $(SRCS_COMMON),$(SRCS_ASM_COMMON),$(SRCS_CPP_COMMON),\
		$(SRCS_$(CORE)),$(SRCS_ASM_$(CORE)),$(SRCS_CPP_$(CORE)),\
		$(SRCS_$(SOCFAMILY)),$(SRCS_ASM_$(SOCFAMILY)),$(SRCS_CPP_$(SOCFAMILY)))"""
	$(ECHO) \# Depend $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME)
ifeq ($(APP_LIB_FILTER),)
	$(ECHO) -e $(APP_LIB) >> $(DEST_ROOT)/linksfwLibList_$(CORE)_$(PROFILE_$(CORE)).txt
endif
ifeq ($(LIB_INC_FILTER),)
	$(call OUTLINE,'#define $(MODULE_NAME)')
endif
endif

else
# Rules for application; this iteration is for an app

# Clean Object, Binary and Configuro generated directories
clean :
	$(RM) -rf $(CONFIGURO_DIR)
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/*

# Create dependencies list to ultimately create application executable binary
$(CORE) : $(OBJDIR) $(BINDIR) $(DEPDIR) $(CONFIGURO_DIR)
	$(MAKE) $(PKG_LIST)
	$(MAKE) $(EXE_NAME)

endif

# Nothing beyond this point

