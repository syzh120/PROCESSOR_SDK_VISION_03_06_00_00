# Filename: rules_m4.mk
#
# Make rules for M4 - This file has all the common rules and defines required
#                     for Cortex-M4 ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (currently it uses TMS470)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for M4 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(CODEGEN_PATH_M4)/include
CODEGEN_INCLUDE += $(CODEGEN_PATH_M4)/include/AUTOSAR31
CC = $(CODEGEN_PATH_M4)/bin/armcl
AR = $(CODEGEN_PATH_M4)/bin/armar
LNK = $(CODEGEN_PATH_M4)/bin/armlnk

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
CFLAGS_INTERNAL =  -c -qq -pdsw225 --endian=$(ENDIAN) -mv7M4 --float_support=vfplib --abi=$(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) --symdebug:dwarf --embed_inline_assembly -DBIOS_BUILD -DSYSBIOS --common=off
CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)


ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)
ifneq ($(OPENCL_INCLUDE),yes)
CFLAGS_INTERNAL += --emit_warnings_as_errors
endif
endif

ifeq ($(EARLY_USECASE_ENABLE),yes)
CFLAGS_INTERNAL += -DEARLY_USECASE_ENABLE
endif

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
CFLAGS_INTERNAL += -DA15_TARGET_OS_LINUX -DDDR_MEM_1024M
ifeq ($(A15_TARGET_OS),Qnx)
CFLAGS_INTERNAL += -DA15_TARGET_OS_QNX
endif
ifeq ($(ROBUST_RVC_INCLUDE),yes)
CFLAGS_INTERNAL += -DBSP_DISABLE_I2C2 -DBSP_DISABLE_I2C5
else
ifeq ($(PLATFORM), tda2xx-rvp)
CFLAGS_INTERNAL += -DBSP_DISABLE_I2C0 -DVPS_DISABLE_I2C2
else
CFLAGS_INTERNAL += -DBSP_DISABLE_I2C0 -DBSP_DISABLE_I2C2 -DBSP_DISABLE_I2C5
endif
endif
ifeq ($(IPU1_EVELOADER_INCLUDE), yes)
CFLAGS_INTERNAL += -DIPU1_LOAD_EVES
endif
ifeq ($(IPUMM_INCLUDE), yes)
CFLAGS_INTERNAL += -DIPUMM_INCLUDE
endif
endif

ifeq ($(DDR_MEM), DDR_MEM_1024M)
CFLAGS_INTERNAL += -DDDR_MEM_1024M
endif

ifeq ($(CPU_IDLE_ENABLED), yes)
CFLAGS_INTERNAL += -DCPU_IDLE_ENABLED
endif

ifeq ($(A15_TARGET_OS), Bios)
CFLAGS_INTERNAL += -DA15_TARGET_OS_BIOS
endif

XDC_HFILE_NAME = $(basename $(XDC_CFG_FILE_$(CORE)))
# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), debug)
 CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_6_1 -D_DEBUG_=1 -ms
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__=$(CONFIGURO_DIR)/package/cfg/$(XDC_HFILE_NAME)_pem4.h
 endif
 LNKFLAGS_INTERNAL_PROFILE =
endif
ifeq ($(PROFILE_$(CORE)), release)
 CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_6_1 -ms -oe -O3 -op0 -os --optimize_with_debug --inline_recursion_limit=20
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__=$(CONFIGURO_DIR)/package/cfg/$(XDC_HFILE_NAME)_pem4.h
 endif
 LNKFLAGS_INTERNAL_PROFILE = --strict_compatibility=on
endif
ifeq ($(PROFILE_$(CORE)), prod_release)
 CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_6_1 -ms -oe -O3 -op0 -os --optimize_with_debug --inline_recursion_limit=20
 ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__=$(CONFIGURO_DIR)/package/cfg/$(XDC_HFILE_NAME)_pem4.h
 endif
 LNKFLAGS_INTERNAL_PROFILE = --opt='--endian=$(ENDIAN) -mv7M4 --float_support=vfplib --abi=$(CSWITCH_FORMAT) -qq -pdsw225 $(CFLAGS_GLOBAL_$(CORE)) -oe --symdebug:dwarf -ms -op2 -O3 -os --optimize_with_debug --inline_recursion_limit=20 --diag_suppress=23000' --strict_compatibility=on
endif

# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST_M4_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the local CORE...
  CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_M4_LOCAL),-D_LOCAL_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_M4_LOCAL),-D_BUILD_$(PKG)_)

  ifeq ($(CORE),m4vpss)
    PKG_LIST_M4_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
  endif
  ifeq ($(CORE),m4video)
    PKG_LIST_M4_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
  endif

  ifeq ($(CORE),ipu1_0)
    PKG_LIST_M4_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
  endif
  ifeq ($(CORE),ipu1_1)
    PKG_LIST_M4_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
  endif
  ifeq ($(CORE),ipu2)
    PKG_LIST_M4_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
  endif
  PKG_LIST_A8_REMOTE = $(foreach COMP,$(COMP_LIST_a8host),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the remote CORE...
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_M4_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_M4_REMOTE),-D_BUILD_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A8_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A8_REMOTE),-D_BUILD_$(PKG)_)
endif

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_XDCINTERNAL) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOCFAMILY)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))

# Decide the compile mode
COMPILEMODE = -fc
ifeq ($(CPLUSPLUS_BUILD), yes)
  COMPILEMODE = -fg
endif

INCLUDE_TEMP = $(ndk_INCLUDE) $(nsp_INCLUDE)
INCLUDE_UIA =  $(uia_INCLUDE)
INCLUDE_EXTERNAL = $(foreach INCL,$(INCLUDE_EXTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_INTERNAL = $(foreach INCL,$(INCLUDE_INTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_ALL = $(CODEGEN_INCLUDE) $(INCDIR) $(INCLUDE_EXTERNAL) $(INCLUDE_INTERNAL) $(INCLUDE_TEMP) $(INCLUDE_UIA)

# Add prefix "-I" to each of the include paths in INCLUDE_ALL
INCLUDES = $(addprefix -I,$(INCLUDE_ALL))
INCLUDES += -I$(vision_sdk_PATH)/links_fw/include/config/$(MAKEAPPNAME)/$(MAKECONFIG)
INCLUDES += -I$(evealg_PATH)/common
INCLUDES += -I$(tidl_INCLUDE)
INCLUDES += -I$(tiop_INCLUDE)

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<

$(OBJ_PATHS_CPP): $(OBJDIR)/%.$(OBJEXT): %.cpp
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $<

$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fa $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fa $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying $(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = rq

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP)
ifneq "$(or $(OBJ_PATHS),$(OBJ_PATHS_ASM),$(OBJ_PATHS_CPP))"""
	$(ECHO) \#
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME)
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP)
endif

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON = -w -q -u _c_int00 --silicon_version=7M4 -c --diag_suppress=16032

#  The warning can be suppressed with the --diag_suppress=<id> option.
#  To suppress warnings in general, use the --display_error_number option
#  which will give the error id number (16032 in the case of wchat16/32), then use --diag_suppress=<id>.
# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

EXT_NAME =
ifeq ($(CORE), ipu1_0)
  EXT_NAME = $(APP_EXT_NAME)
endif

# Path of the RTS library - normally doesn't change for a given tool-chain
RTSLIB_PATH = $(CODEGEN_PATH_M4)/lib/libc.a

PDKLIB_PATH =
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/bsp_lld/i2c/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/bsp_i2c.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/bsp_lld/uart/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/bsp_uart.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/bsp_lld/mcspi/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/bsp_mcspi.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(PDK_BOARD)/$(ISA)/$(PROFILE_$(CORE))/vps_boards.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vps_common.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vps_devices.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/fvid2.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vps_osal_tirtos.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vps_platforms.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vpslib.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(PDK_BOARD)/$(ISA)/$(PROFILE_$(CORE))/vps_examples_utility.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/stw_lld/i2clld/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/i2c_lld.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/boot/sbl_auto/qspiflash/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/qspiflash_lib.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/csl/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/ti.csl.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/vps/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/vpsdrv.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/stw_lld/platform/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/stw_platform.aem4
#PDKLIB_PATH +=$(pdk_PATH)/packages/ti/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/sys_config.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/pm/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/pm_hal.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/pm/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/pm_lib.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/boot/sbl_auto/lib/$(PDK_BOARD)/$(ISA)/$(PROFILE_$(CORE))/sbl_lib.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/stw_lld/fatlib/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/stw_fatlib.aem4
PDKLIB_PATH +=$(pdk_PATH)/packages/ti/drv/fw_l3l4/lib/$(SOC)/$(ISA)/$(PROFILE_$(CORE))/firewall_l3l4.aem4
ifneq ($(RADAR_ONLY),yes)
	CODEC_PATHS += $(jpegvdec_PATH)/packages/ti/sdo/codecs/jpegvdec/lib/jpegvdec_ti_host.lib
	CODEC_PATHS += $(jpegvenc_PATH)/packages/ti/sdo/codecs/jpegvenc/lib/jpegenc_ti_host.lib
	CODEC_PATHS += $(h264venc_PATH)/packages/ti/sdo/codecs/h264enc/lib/h264enc_ti_host.lib
	CODEC_PATHS += $(h264vdec_PATH)/packages/ti/sdo/codecs/h264vdec/lib/h264vdec_ti.lib
	CODEC_PATHS += $(hdvicplib_PATH)/packages/ti/sdo/codecs/hdvicp20api/lib/ivahd_ti_api_vM3.lib
endif

# Application libs
LIB_PATHS += $(APP_LIBS_$(CORE))

LIB_PATHS += $(PDKLIB_PATH)

ifeq ($(SOCFAMILY),tda2xx)
	LIB_PATHS += $(CODEC_PATHS)
endif

LIB_PATHS += $(DEST_ROOT)/lib/$(PLATFORM)/$(ISA)/$(PROFILE_$(CORE))/edma3lld_rm.$(LIBEXT)
LIB_PATHS += $(DEST_ROOT)/lib/$(PLATFORM)/$(ISA)/$(PROFILE_$(CORE))/edma3lld_drv.$(LIBEXT)
LIB_PATHS += $(RTSLIB_PATH)

#This must be last since it overrides core
ifeq ($(IPC_LIB_INCLUDE), yes)
ifneq ($(CORE), ipu2)
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/ipc_lite/lib/$(SOC)/$(CORE)/$(PROFILE_$(CORE))/ipc_lib.$(LIBEXT)
else
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/ipc_lite/lib/$(SOC)/ipu2_0/$(PROFILE_$(CORE))/ipc_lib.$(LIBEXT)
endif
endif

ifeq ($(AUTOSAR_APP), yes)
LIB_PATHS += $(mcal_PATH)/lib/$(PROFILE)/cddIpc.$(LIBEXT)
LIB_PATHS += $(mcal_PATH)/lib/$(PROFILE)/mcu.$(LIBEXT)
LIB_PATHS += $(mcal_PATH)/lib/$(PROFILE)/app_utils.$(LIBEXT)
ifeq ($(IPC_LIB_INCLUDE), no)
ifneq ($(CORE), ipu2)
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/ipc_lite/lib/$(SOC)/$(CORE)/$(PROFILE_$(CORE))/ipc_lib.$(LIBEXT)
else
LIB_PATHS += $(pdk_PATH)/packages/ti/drv/ipc_lite/lib/$(SOC)/ipu2_0/$(PROFILE_$(CORE))/ipc_lib.$(LIBEXT)
endif
endif
endif

ifdef APP_NAME
	# The application libs created are read from the file
	LIB_PATHS += $(shell $(CAT) $(DEST_ROOT)/linksfwLibList_$(CORE)_$(PROFILE_$(CORE)).txt)
endif

LNK_LIBS = $(addprefix -l,$(LIB_PATHS))

# Linker - to create executable file

ifeq ($(LOCAL_APP_NAME),)
 EXE_NAME = $(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE))$(EXT_NAME).$(EXEEXT)
else
 ifeq ($(PROFILE_$(CORE)),prod_release)
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME)$(EXT_NAME).$(EXEEXT)
 else
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME)_$(PROFILE_$(CORE)$(EXT_NAME).$(EXEEXT)
 endif
endif

$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(LIB_PATHS) $(LNKCMD_FILE) $(OBJDIR)/$(CFG_COBJ_XDC)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(CP) $(OBJDIR)/$(CFG_COBJ_XDC) $(CONFIGURO_DIR)/package/cfg
ifeq ($(PROFILE_$(CORE)),whole_program_debug)
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(OBJDIR)/$(CFG_COBJ_XDC) $(LNKCMD_FILE) -o $@ -m $@.map $(LNK_LIBS)
else
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(LNKCMD_FILE) -o $@ -m $@.map $(LNK_LIBS)
endif
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

# XDC specific - assemble XDC-Configuro command
ifeq ($(PROFILE_$(CORE)),prod_release)
  CONFIGURO_PROFILE = release
else
  CONFIGURO_PROFILE = $(PROFILE_$(CORE))
endif
CONFIGURO_CMD = $(xdc_PATH)/xs xdc.tools.configuro --generationOnly -o $(CONFIGURO_DIR) -t $(TARGET_XDC) -p $(PLATFORM_XDC) \
               -r $(CONFIGURO_PROFILE) -b $(CONFIG_BLD_XDC_$(ISA)) --cfgArgs $(CFGARGS_XDC) $(XDC_CFG_FILE_NAME)
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
$(OBJDIR)/$(CFG_COBJ_XDC) : $(CFG_C_XDC)
	$(ECHO) \# Compiling generated $(CFG_COBJ_XDC)
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fc $(CFG_C_XDC)
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fc $(CFG_C_XDC)
endif

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)
-include $(SRCS_CPP:%.cpp=$(DEPDIR)/%.P)


# Nothing beyond this point
