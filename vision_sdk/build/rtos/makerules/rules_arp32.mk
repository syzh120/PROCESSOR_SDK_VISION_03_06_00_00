# Filename: rules_arp32f.mk
#
# Make rules for EVE - This file has all the common rules and defines required
#                     for EVE ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (currently it uses arp32cgt_1.0.0)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for EVE ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(CODEGEN_PATH_EVE)/include
CC = $(CODEGEN_PATH_EVE)/bin/cl-arp32
AR = $(CODEGEN_PATH_EVE)/bin/ar-arp32
LNK = $(CODEGEN_PATH_EVE)/bin/lnk-arp32

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN =
else
  RTSLIB_ENDIAN = e
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),COFF)
  #CSWITCH_FORMAT = ti_arm9_abi
  #RTSLIB_FORMAT = _tiarm9

  CSWITCH_FORMAT =
  #RTSLIB_FORMAT =
  XDCINTERNAL_DEFINES = -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__vers_1_0_7_0_0
endif
ifeq ($(FORMAT),ELF)
  #CSWITCH_FORMAT = eabi
  #RTSLIB_FORMAT = _elf

  CSWITCH_FORMAT =
  RTSLIB_FORMAT = _elf
  XDCINTERNAL_DEFINES = -Dxdc_target_types__=ti/targets/arp32/elf/std.h -Dxdc_bld__vers_1_0_7_2_0_10271
endif

#########

# XDC Specific defines
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifeq ($(PROFILE_$(CORE)),debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	CFG_LNKFILENAMEPART_XDC=
  endif
  ifeq ($(PROFILE_$(CORE)),release)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  endif
  ifeq ($(PROFILE_$(CORE)),whole_program_debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
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

MISC_LNKCMD_INCLUDE=$(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/$(SOC)/cfg/link_eve.cmd

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL =  -c -qq -pdsw225 $(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) -DBIOS_BUILD -DSYSBIOS
CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)
CFLAGS_NEW_DIROPTS = -fr=$(CFG_C_NEW_XDC) -fs=$(CFG_C_NEW_XDC)


ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)

CFLAGS_INTERNAL += --emit_warnings_as_errors

endif

CFLAGS_INTERNAL += --silicon_version=v210

KFLAGS= -kh -kv --gen_func_subsections

ifeq ($(CPU_IDLE_ENABLED), yes)
CFLAGS_INTERNAL += -DCPU_IDLE_ENABLED
endif

#########XDC Config File for EVE##########

# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), release)
 CFLAGS_INTERNAL += --symdebug:dwarf -O3
 CFLAGS_XDCINTERNAL = -Dxdc_target_name__=ARP32_far  -Dxdc_bld__profile_debug -D_DEBUG_=1
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__=$(CONFIGURO_DIR)/package/cfg/$(XDC_CFG_BASE_FILE_NAME)_pearp32F.h
 endif
 LNKFLAGS_INTERNAL_PROFILE = -o2
endif


# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), debug)
 CFLAGS_INTERNAL += --symdebug:dwarf
 CFLAGS_XDCINTERNAL = -Dxdc_target_name__=ARP32_far  -Dxdc_bld__profile_debug -D_DEBUG_=1
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__=$(CONFIGURO_DIR)/package/cfg/$(XDC_CFG_BASE_FILE_NAME)_pearp32F.h
 endif
 LNKFLAGS_INTERNAL_PROFILE =
endif


# For generic platform define GENERIC in CFLAGS
ifeq ($(PLATFORM),generic)
 CFLAGS_XDCINTERNAL += -DGENERIC
endif
CFLAGS_XDCINTERNAL += $(XDCINTERNAL_DEFINES)
CFLAGS_XDCINTERNAL += --silicon_version=v210
########################################

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
CFLAGS_INTERNAL += -DA15_TARGET_OS_LINUX -DDDR_MEM_1024M
ifeq ($(A15_TARGET_OS),Qnx)
CFLAGS_INTERNAL += -DA15_TARGET_OS_QNX
endif
endif

ifeq ($(DDR_MEM), DDR_MEM_1024M)
CFLAGS_INTERNAL += -DDDR_MEM_1024M
endif

ifeq ($(A15_TARGET_OS),Bios)
CFLAGS_INTERNAL += -DA15_TARGET_OS_BIOS
endif

ifeq ($(IPU1_EVELOADER_INCLUDE), yes)
CFLAGS_INTERNAL += -DIPU1_LOAD_EVES
endif



# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST_ARP32_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the local CORE...
  CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_ARP32_LOCAL),-D_LOCAL_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_ARP32_LOCAL),-D_BUILD_$(PKG)_)

  ifeq ($(CORE),arp32_1)
    PKG_LIST_ARP32_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
    ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px))
      MISC_LNKCMD_INCLUDE += $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/$(SOC)/eve1/linker_cmd_eve1_$(PROFILE).cmd
    endif
  endif
  ifeq ($(CORE),arp32_2)
    PKG_LIST_ARP32_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
    ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px))
      MISC_LNKCMD_INCLUDE += $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/$(SOC)/eve2/linker_cmd_eve2_$(PROFILE).cmd
    endif
  endif
  ifeq ($(CORE),arp32_3)
    PKG_LIST_ARP32_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
    ifeq ($(SOC),tda2xx)
      MISC_LNKCMD_INCLUDE += $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/$(SOC)/eve3/linker_cmd_eve3_$(PROFILE).cmd
    endif
  endif
  ifeq ($(CORE),arp32_4)
    PKG_LIST_ARP32_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
    ifeq ($(SOC),tda2xx)
      MISC_LNKCMD_INCLUDE += $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/$(SOC)/eve4/linker_cmd_eve4_$(PROFILE).cmd
    endif
  endif
  PKG_LIST_A8_REMOTE = $(foreach COMP,$(COMP_LIST_a8host),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the remote CORE...
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_ARP32_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_ARP32_REMOTE),-D_BUILD_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A8_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A8_REMOTE),-D_BUILD_$(PKG)_)
endif

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_XDCINTERNAL) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOCFAMILY)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))


INCLUDE_EXTERNAL = $(foreach INCL,$(INCLUDE_EXTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_UIA =  $(uia_INCLUDE)
INCLUDE_INTERNAL = $(foreach INCL,$(INCLUDE_INTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_ALL = $(CODEGEN_INCLUDE) $(INCDIR) $(INCLUDE_EXTERNAL) $(INCLUDE_INTERNAL) $(INCLUDE_UIA)

# Add prefix "-I" to each of the include paths in INCLUDE_ALL
INCLUDES = $(addprefix -I,$(INCLUDE_ALL))
INCLUDES += -I$(vision_sdk_PATH)/links_fw/include/config/$(MAKEAPPNAME)/$(MAKECONFIG)

#Add some additional include paths
INCLUDES +=

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(CFLAGS_$(basename $(notdir $<))) -fc $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(CFLAGS_$(basename $(notdir $<))) -fc $<

$(OBJ_PATHS_CPP): $(OBJDIR)/%.$(OBJEXT): %.cpp
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(CFLAGS_$(basename $(notdir $<))) $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(CFLAGS_$(basename $(notdir $<))) $<

$(OBJ_PATHS_K): $(OBJDIR)/%.$(OBJEXT): %.k
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(KFLAGS) $(CFLAGS_DIROPTS) $(CFLAGS_$(basename $(notdir $<))) -ft=$(dir $< ) $<


# Archive flags - normally doesn't change
ARFLAGS = rq

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_K) $(OBJ_PATHS) $(OBJ_PATHS_CPP)
ifneq "$(or $(OBJ_PATHS),$(OBJ_PATHS_ASM),$(OBJ_PATHS_CPP))"""
	$(ECHO) \#
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME)
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(OBJ_PATHS_K)
endif

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON = --warn_sections -q -e=_c_int00 --silicon_version=arp32 -c -x --zero_init=off --rom_model

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

# Path of the RTS library - normally doesn't change for a given tool-chain
RTSLIB_PATH = $(CODEGEN_PATH_EVE)/lib/rtsarp32_v203.lib

LIB_PATHS += $(DEST_ROOT)/lib/$(PLATFORM)/$(ISA)/$(PROFILE_$(CORE))/edma3lld_rm.$(LIBEXT)
LIB_PATHS += $(DEST_ROOT)/lib/$(PLATFORM)/$(ISA)/$(PROFILE_$(CORE))/edma3lld_drv.$(LIBEXT)
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/fw_l3l4/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/firewall_l3l4.aearp32F
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vps_osal_tirtos.$(LIBEXT)
LIB_PATHS += $(RTSLIB_PATH)

# Application libs
LIB_PATHS += $(APP_LIBS_$(CORE))

PM_FUNC_INCLUDE_PATH +=$(pdk_PATH)/packages/ti/drv/pm/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/pm_hal.aearp32F
PM_FUNC_INCLUDE_PATH +=$(pdk_PATH)/packages/ti/drv/pm/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/pm_lib.aearp32F
PM_FUNC_INCLUDE_PATH +=$(pdk_PATH)/packages/ti/csl/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/ti.csl.aearp32F

ifeq ($(IPC_LIB_INCLUDE), yes)
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/ipc_lite/lib/$(SOC)/$(CORE)/$(PROFILE_$(CORE))/ipc_lib.$(LIBEXT)
endif

ifdef APP_NAME
	# The application libs created are read from the file
	LIB_PATHS += $(shell $(CAT) $(DEST_ROOT)/linksfwLibList_$(CORE)_$(PROFILE_$(CORE)).txt)
endif

LNK_LIBS = $(addprefix -l,$(LIB_PATHS))

ifdef APP_NAME
	ifeq ($(LNK_Starterware_LIB), yes)
		LNK_LIBS += $(StarterwareHalLIB_PATH)
	endif

	ifeq ($(LNK_Starterware_Common_LIB), yes)
		LNK_LIBS += $(Starterware_Common_PATH)
	endif

	ifeq ($(LNK_SYSCONFIG_LIB), yes)
		LNK_LIBS += $(SysConfig_PATH)
	endif

	LNK_LIBS += $(PM_FUNC_INCLUDE_PATH)

endif

# Linker - to create executable file

EXE_NAME = $(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE)).$(EXEEXT)

$(EXE_NAME) : $(OBJ_PATHS_K) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(LIB_PATHS) $(LNKCMD_FILE) $(CFG_C_NEW_XDC)/$(CFG_COBJ_XDC) $(MISC_LNKCMD_INCLUDE)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(OBJ_PATHS_K) -l$(LNKCMD_FILE) -o $@ -m $@.map $(LNK_LIBS) $(MISC_LNKCMD_INCLUDE)
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#
ifeq ($(IPU1_EVELOADER_INCLUDE),yes)
	mono $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/eveloader/tools/out2rprc.exe $(EXE_NAME) $(EXE_NAME).rprc
endif

# XDC specific - assemble XDC-Configuro command
ifeq ($(PROFILE_$(CORE)),prod_release)
  CONFIGURO_PROFILE = release
else
  CONFIGURO_PROFILE = $(PROFILE_$(CORE))
endif
CONFIGURO_CMD = $(xdc_PATH)/xs xdc.tools.configuro --generationOnly -o $(CONFIGURO_DIR) -t $(TARGET_XDC) -p $(PLATFORM_XDC) \
               -r $(CONFIGURO_PROFILE) -c $(CODEGEN_PATH_EVE) -b $(CONFIG_BLD_XDC_$(ISA)) --cfgArgs $(CFGARGS_XDC) $(XDC_CFG_FILE_NAME)
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
xdc_configuro : $(XDC_CFG_FILE)
	$(ECHO) \# Invoking configuro...
	$(MKDIR) -p $(DEST_ROOT)
	$(ECHO) -e $(CONFIGURO_CMD) > $(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat
ifeq ($(OS),Windows_NT)
	CACLS $(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat /E /P $(EVERYONE):F
else
	$(CHMOD) a+x $(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat
endif
	$(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat
	$(CP) $(XDCLNKCMD_FILE) $(LNKCMD_FILE)
	$(ECHO) \# Configuro done!



ifndef MODULE_NAME
$(CFG_C_NEW_XDC)/$(CFG_COBJ_XDC) : $(CFG_C_XDC)
	$(ECHO) \# Compiling generated $(CFG_COBJ_XDC)
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_NEW_DIROPTS) -fc $(CFG_C_XDC)
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_NEW_DIROPTS) -fc $(CFG_C_XDC)
endif


# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)
-include $(SRCS_CPP:%.cpp=$(DEPDIR)/%.P)
-include $(SRCS_K:%.k=$(DEPDIR)/%.P)

# Nothing beyond this point
