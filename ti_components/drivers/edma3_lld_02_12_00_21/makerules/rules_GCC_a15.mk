# Filename: rules_GCC_a15.mk
#
# Make rules for A15 - This file has all the common rules and defines required
#                     for Cortex-A15 ISA using a gcc cross-compiler
#
# This file needs to change when:
#     1. Code generation tool chain changes (This file uses Linaro)
#     2. Internal switches (which are normally not touched) has to change
#     3. a rule common for A15 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CROSSCC ?= $(CODEGEN_PATH_A15_GCC)/bin/arm-linux-gnueabihf-gcc
CROSSAR ?= $(CODEGEN_PATH_A15_GCC)/bin/arm-linux-gnueabihf-ar
CROSSLNK ?= $(CODEGEN_PATH_A15_GCC)/bin/arm-linux-gnueabihf-gcc

CC = $(CROSSCC)
AR = $(CROSSAR)
LNK = $(CROSSLNK)
SONAME ?= $(MODULE_NAME).$(LIBEXT_SO)
SONAME_FULL = $(subst .,$(findstring rm,$(MODULE_NAME)).,$(subst rm,,$(SONAME)))

CFLAGS_INTERNAL = -Wall -Wunknown-pragmas -c -mcpu=cortex-a15 -g -mfpu=neon -mfloat-abi=hard -mabi=aapcs -mapcs-frame  -Wswitch -fno-short-enums

ifeq ($(PROFILE_$(CORE)), debug)
CFLAGS_INTERNAL += -D_DEBUG_=1
endif
ifeq ($(PROFILE_$(CORE)), release)
 LNKFLAGS_INTERNAL_PROFILE =
endif

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_XDCINTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))

# Object file creation
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -c -MD -MF $@.dep $(_CFLAGS) $(INCLUDES) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

# The second $(CC) compiles the source to generate object
$(OBJ_PATHS_SO): $(OBJDIR)/%.$(OBJEXT_SO): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -fPIC -c -MD -MF $@.dep $(_CFLAGS) $(INCLUDES) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT_SO) $<

ASMFLAGS =
# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -c -x assembler-with-cpp $(_CFLAGS) $(ASMFLAGS) $(INCLUDES) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

# Object file creation
$(OBJ_PATHS_ASM_SO): $(OBJDIR)/%.$(OBJEXT_SO): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -fPIC -c -x assembler-with-cpp $(_CFLAGS) $(ASMFLAGS) $(INCLUDES) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT_SO) $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying $(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = cr

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS)
	$(ECHO) \#
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME)
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS)

ARFLAGS_SO = -shared
# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT_SO) : $(OBJ_PATHS_ASM_SO) $(OBJ_PATHS_SO)
	$(ECHO) \#
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME) Shared Library $(SONAME_FULL)
	$(ECHO) \#
	$(CC) $(ARFLAGS_SO) -Wl,-soname,$(SONAME_FULL).1 -o $(LIBDIR)/$(SONAME_FULL).1.0.0 $(OBJ_PATHS_ASM_SO) $(OBJ_PATHS_SO)
	@ln -s $(SONAME_FULL).1.0.0 $(SONAME_FULL).1
	@mv $(SONAME_FULL).1 $(LIBDIR)
	@ln -s $(SONAME_FULL).1     $(SONAME_FULL)
	@mv $(SONAME_FULL) $(LIBDIR)

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON =

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL) $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

# Path of the RTS library - normally doesn't change for a given tool-chain
RTSLIB_PATH =

# Add specific paths and libraries as needed in the executable makefile
LIB_PATHS += $(EXT_LIB_a15host)  
INCLUDE_FLAGS = $(EXT_INCLUDES)

LNK_LIBS = $(addprefix -l,$(LIB_PATHS))
# Linker - to create executable file

ifeq ($(LOCAL_APP_NAME),)
 EXE_NAME = $(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE)).$(EXEEXT)
else
 ifeq ($(PROFILE_$(CORE)),prod_release)
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME).$(EXEEXT)
 else
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME)_$(PROFILE_$(CORE)).$(EXEEXT)
 endif
endif

$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	#$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) -Wl,-T,$(LNKCMD_FILE) -Wl,-Map,$@.map $(LIB_PATHS) -o $@
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LIB_PATHS) $(INCLUDE_FLAGS) -o $@
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#


xdc_configuro : $(XDC_CFG_FILE)
	$(ECHO) \# XDC not needed for A15 GCC build

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)
# Nothing beyond this point
