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

# Filename: common.mk
#
# Common make file - This file has common rules and definitions that are common
#                    across boards/cores/ISAs/SoCs
#
# This file needs to change when:
#     1. common rule/define has to be added or modified
#

#
# Include make paths and options for all supported targets/boards
#

.PHONY : all clean gendirs c66x c66xdsp_1 c66xdsp_2 ipu1_0 ipu1_1 ipu2_0 ipu2_1 host a15_0 a8host a9host arp32_1 arp32_2 arp32_3 arp32_4 arm9_0 c674x

all : $(CORE)

# Define directories that are going to be created as a part of build process
ifdef MODULE_NAME
  ifeq ($($(MODULE_NAME)_SOC_DEPENDENCY),no)
    ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
      DEPENDENCY_SUB_PATH = $(CORE)
    else
      DEPENDENCY_SUB_PATH = $(ISA)
    endif
  else
    ifeq ($($(MODULE_NAME)_BOARD_DEPENDENCY),yes)
      ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
        DEPENDENCY_SUB_PATH = $(BOARD)/$(CORE)
      else
        DEPENDENCY_SUB_PATH = $(BOARD)/$(ISA)
      endif
    else
      ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
        ifeq ($(CORE),$(filter $(CORE), pru_0 pru_1))
          DEPENDENCY_SUB_PATH = $(SOC)/$(HOSTCORE)/$(PRUVERSION)
        else
          DEPENDENCY_SUB_PATH = $(SOC)/$(CORE)
        endif
      else
        DEPENDENCY_SUB_PATH = $(SOC)/$(ISA)
      endif
    endif
  endif
endif

ifeq ($(DEST_ROOT),)
  ifdef MODULE_NAME
    OBJDIR = obj/$(DEPENDENCY_SUB_PATH)/$(BUILD_PROFILE_$(CORE))
    LIBDIR = lib/$(DEPENDENCY_SUB_PATH)/$(BUILD_PROFILE_$(CORE))
    ifeq ($($(MODULE_NAME)_LIBNAME),)
      # use module name as libname if not defined
      LIBNAME = $(MODULE_NAME)
    else
      LIBNAME = $($(MODULE_NAME)_LIBNAME)
    endif
  else
    OBJDIR = obj/$(BOARD)/$(CORE)/$(BUILD_PROFILE_$(CORE))
    BINDIR = bin/$(BOARD)
  endif
else
  ifdef MODULE_NAME
    ifeq ($(CORE),$(filter $(CORE), pru_0 pru_1))
      ifeq ($($(MODULE_NAME)_OBJPATH), )
        OBJDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/obj/$(DEPENDENCY_SUB_PATH)/$(CORE)
      else
        OBJDIR = $(DEST_ROOT)/$($(MODULE_NAME)_OBJPATH)/obj/$(DEPENDENCY_SUB_PATH)/$(CORE)
      endif
    else
      ifeq ($($(MODULE_NAME)_OBJPATH), )
        OBJDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/obj/$(DEPENDENCY_SUB_PATH)/$(BUILD_PROFILE_$(CORE))
      else
        OBJDIR = $(DEST_ROOT)/$($(MODULE_NAME)_OBJPATH)/obj/$(DEPENDENCY_SUB_PATH)/$(BUILD_PROFILE_$(CORE))
      endif
    endif
    ifeq ($($(MODULE_NAME)_LIBPATH), )
      LIBDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/lib/$(DEPENDENCY_SUB_PATH)/$(BUILD_PROFILE_$(CORE))
    else
      LIBDIR = $($(MODULE_NAME)_LIBPATH)/$(DEPENDENCY_SUB_PATH)/$(BUILD_PROFILE_$(CORE))
    endif
    ifeq ($($(MODULE_NAME)_LIBNAME),)
      # use module name as libname is not defined
      LIBNAME = $(MODULE_NAME)
    else
      LIBNAME = $($(MODULE_NAME)_LIBNAME)
    endif
    ifeq ($($(MODULE_NAME)_HEADERPATH), )
      HEADERDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/lib/$(DEPENDENCY_SUB_PATH)
    else
      HEADERDIR = $($(MODULE_NAME)_HEADERPATH)/$(DEPENDENCY_SUB_PATH)
    endif
    ifeq ($($(MODULE_NAME)_HEADERNAME),)
      # use module name as HEADERNAME is not defined
      HEADERNAME = $(MODULE_NAME)
    else
      HEADERNAME = $($(MODULE_NAME)_HEADERNAME)_$(ARCH)
    endif
  else
    ifeq ($($(APP_NAME)_OBJPATH), )
      ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
        OBJDIR = $(DEST_ROOT)/$(APP_NAME)/obj/$(BOARD)/$(CORE)/$(BUILD_PROFILE_$(CORE))
      else
        OBJDIR = $(DEST_ROOT)/$(APP_NAME)/obj/$(SOC)/$(CORE)/$(BUILD_PROFILE_$(CORE))
      endif
    else
      ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
        OBJDIR = $($(APP_NAME)_OBJPATH)/$(BOARD)/$(CORE)/$(BUILD_PROFILE_$(CORE))
      else
        OBJDIR = $($(APP_NAME)_OBJPATH)/$(SOC)/$(CORE)/$(BUILD_PROFILE_$(CORE))
      endif
    endif
    ifeq ($($(APP_NAME)_BINPATH), )
      ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
        BINDIR = $(DEST_ROOT)/$(APP_NAME)/bin/$(BOARD)
      else
        BINDIR = $(DEST_ROOT)/$(APP_NAME)/bin/$(SOC)
      endif
    else
      ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
        BINDIR = $($(APP_NAME)_BINPATH)/$(BOARD)
      else
        BINDIR = $($(APP_NAME)_BINPATH)/$(SOC)
      endif
    endif
  endif
endif
PACKAGEDIR = package/$(PACKAGE_SELECT)

CONFIGURO_DIRNAME = configuro
ifeq ($(XDC_CFG_DIR),)
 CONFIGURO_DIR = $(OBJDIR)/$(CONFIGURO_DIRNAME)
 XDC_CFG_FILE_NAME = $(XDC_CFG_FILE_$(CORE))
else
 CONFIGURO_DIR = $(XDC_CFG_DIR)/configuro/$(BOARD)/$(CORE)/$(BUILD_PROFILE_$(CORE))/$(CONFIGURO_DIRNAME)
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

$(HEADERDIR) :
	$(MKDIR) -p $(HEADERDIR)

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
SRCS = $(SRCS_COMMON) $(SRCS_$(CORE)) $(SRCS_$(SOC))
SRCS_ASM = $(SRCS_ASM_COMMON) $(SRCS_ASM_$(CORE)) $(SRCS_ASM_$(SOC))

ifneq ($(SOC),$(BOARD))
SRCS += $(SRCS_$(BOARD))
SRCS_ASM += $(SRCS_ASM_$(BOARD))
endif #ifneq ($(SOC,$(BOARD))

PACKAGE_SRCS = $(PACKAGE_SRCS_COMMON)

# Define search paths
VPATH = $(SRCDIR)

# Following 'if...' block is for an application.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST = $(foreach COMP,$(COMP_LIST_COMMON),$($(COMP)_PKG_LIST))
  PKG_LIST += $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
  PKG_LIST += $(foreach COMP,$(COMP_LIST_$(SOC)),$($(COMP)_PKG_LIST))
  # Derive list of all external libraries
  EXT_LIB_LIST = $(EXT_LIB_LIST_COMMON)
  EXT_LIB_LIST += $(EXT_LIB_LIST_$(CORE))
  EXT_LIB_LIST += $(EXT_LIB_LIST_$(SOC))

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

PACKAGE_PATHS = $(patsubst %, $(PACKAGEDIR)/%, $(PACKAGE_SRCS))

# Assemble include paths here
INCLUDE_EXTERNAL = $(foreach INCL,$(INCLUDE_EXTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_INTERNAL = $(foreach INCL,$(INCLUDE_INTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_ALL = $(CODEGEN_INCLUDE) $(INCDIR) $(INCLUDE_EXTERNAL) $(INCLUDE_INTERNAL)

# Add prefix "-I" to each of the include paths in INCLUDE_ALL
INCLUDES = $(addprefix -I,$(INCLUDE_ALL))

# print Info
ifeq ($($(MODULE_NAME)_BOARD_DEPENDENCY),yes)
  PRINT_MESSAGE = $(BOARD):$(SOC):$(CORE):$(BUILD_PROFILE_$(CORE)):$(MODULE_NAME)
else
  ifeq ($($(APP_NAME)_BOARD_DEPENDENCY),yes)
    PRINT_MESSAGE = $(BOARD):$(SOC):$(CORE):$(BUILD_PROFILE_$(CORE)):$(APP_NAME)
  else
    ifeq ($(CORE),$(filter $(CORE), pru_0 pru_1))
      PRINT_MESSAGE = $(SOC):$(CORE):$(APP_NAME)$(MODULE_NAME)
    else
      PRINT_MESSAGE = $(SOC):$(CORE):$(BUILD_PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME)
    endif
  endif
endif

# Create rule to "make" all packages
.PHONY : $(PKG_LIST)
ifeq ($(DISABLE_RECURSE_DEPS),no)
$(PKG_LIST) :
#	$(ECHO) \# Making $(PRINT_MESSAGE):$@...
	$(MAKE) -C $($@_PATH) $($@_MAKEFILE)
endif

# Get libraries for all the packages
define GET_COMP_DEPENDENCY_SUB_PATH
  ifeq ($$($(1)_SOC_DEPENDENCY),no)
    ifeq ($$($(1)_CORE_DEPENDENCY),yes)
      $(1)_DEPSUBPATH = $(CORE)
    else
      $(1)_DEPSUBPATH = $(ISA)
    endif
  else
    ifeq ($$($(1)_BOARD_DEPENDENCY),yes)
      ifeq ($$($(1)_CORE_DEPENDENCY),yes)
        $(1)_DEPSUBPATH = $(BOARD)/$(CORE)
      else
        $(1)_DEPSUBPATH = $(BOARD)/$(ISA)
      endif
     else
      ifeq ($$($(1)_CORE_DEPENDENCY),yes)
        $(1)_DEPSUBPATH = $(SOC)/$(CORE)
      else
        $(1)_DEPSUBPATH = $(SOC)/$(ISA)
      endif
    endif
  endif
endef

# Get libraries name for all the packages
define GET_COMP_LIBNAME
  ifeq ($$($(1)_LIBNAME), )
    # use module name as libname if not defined
    $(1)_LIBNAME = $(1)
  endif
endef

# Get libraries paths for all the packages
define GET_COMP_LIBPATH
  ifeq ($$($(1)_LIBPATH), )
    # use DEST_ROOT as lib path if not defined
    $(1)_LIBPATH = $(DEST_ROOT)/$($(1)_RELPATH)/lib
  endif
endef

$(foreach LIB,$(PKG_LIST),$(eval $(call GET_COMP_DEPENDENCY_SUB_PATH,$(LIB))))
$(foreach LIB,$(PKG_LIST),$(eval $(call GET_COMP_LIBNAME,$(LIB))))
$(foreach LIB,$(PKG_LIST),$(eval $(call GET_COMP_LIBPATH,$(LIB))))

LIB_PATHS = $(foreach LIB,$(PKG_LIST),$($(LIB)_LIBPATH)/$($(LIB)_DEPSUBPATH)/$(BUILD_PROFILE_$(CORE))/$($(LIB)_LIBNAME).$(LIBEXT))
EXT_LIB_PATHS = $(EXT_LIB_LIST)

# XDC Specific defines
ifneq ($(XDC_CFG_FILE_$(CORE)),)
  ifeq ($(BUILD_PROFILE_$(CORE)),debug)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  endif
  ifeq ($(BUILD_PROFILE_$(CORE)),release)
    CFG_CFILENAMEPART_XDC =p$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  endif
  CFG_CFILE_XDC =$(patsubst %.cfg,%_$(CFG_CFILENAMEPART_XDC).c, $(notdir $(XDC_CFG_FILE_$(CORE))))
  CFG_C_XDC = $(addprefix $(CONFIGURO_DIR)/package/cfg/,$(CFG_CFILE_XDC))
  XDCLNKCMD_FILE =$(patsubst %.c, %$(CFG_LNKFILENAMEPART_XDC).xdl, $(CFG_C_XDC))
  CFG_COBJ_XDC = $(patsubst %.c,%.$(OBJEXT),$(CFG_CFILE_XDC))
  LNKCMD_FILE = $(CONFIGURO_DIR)/linker_mod.cmd
  SPACE :=
  SPACE +=
   XDC_GREP_STRING = $(CFG_COBJ_XDC)
endif

# Include make rules for ISA that is built in this iteration
#   eg: rules_m4.mk

# Added makerules for a8 on gcc.
# In case multiple Tool Chains are needed for other cores as well,
# respective EXT for makerules file can be defined here
# Derive GCC EXT makerules file
ifeq ($(TOOLCHAIN_$(ISA_EXT)),gcc)
  TOOLCHAINEXT = $(TOOLCHAIN_$(ISA_EXT))_
endif

include $(MAKERULEDIR)/rules_$(TOOLCHAINEXT)$(ISA_EXT).mk
package : $(PACKAGE_PATHS)

ifdef MODULE_NAME
    # Rules for module; this iteration is for a module
    ifeq ($(CORE),$(filter $(CORE), pru_0 pru_1))
      # Clean Object and Library (archive) directories
      clean :
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/*

      # Create dependencies list to ultimately create module archive library file
      $(CORE) : $(HEADERDIR)/$(HEADERNAME).$(HEADEREXT)
    else
      # Clean Object and Library (archive) directories
      clean :
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/* $(LIBDIR)/$(LIBNAME).$(LIBEXT) $(LIBDIR)/$(LIBNAME).$(LIBEXT)_size.txt

      # Create dependencies list to ultimately create module archive library file
      ifeq ($(SECTTI_SIZE_INFO),yes)
        $(CORE) : $(LIBDIR)/$(LIBNAME).$(LIBEXT)_size
      else
        $(CORE) : $(LIBDIR)/$(LIBNAME).$(LIBEXT)
      endif
    endif
else
# Rules for application; this iteration is for an app

# Clean Object, Binary and Configuro generated directories
clean :
	$(RM) -rf $(CONFIGURO_DIR)
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/* $(BINDIR)/*

# Create dependencies list to ultimately create application executable binary
$(CORE) : $(OBJDIR) $(BINDIR) $(DEPDIR) $(CONFIGURO_DIR)
	$(MAKE) $($(APP_NAME)_MAKEFILE) $(PKG_LIST)
	$(MAKE) $($(APP_NAME)_MAKEFILE) $(EXE_NAME)

#
# SBL Image/App image Generation
#

#SBL Tool paths
SBL_OBJ_COPY=$(TOOLCHAIN_PATH_GCC)/bin/arm-none-eabi-objcopy
SBL_TOOLS_PATH=$(PDK_SBL_AUTO_COMP_PATH)/tools
SBL_TDA3X_SIGNING_TOOL_DIR=$(PDK_TDA3X_SECURITY_COMP_PATH)/tools/tda3xx
SBL_CHIMAGE_BIN_FILE=$(SBL_TOOLS_PATH)/chimage/tda3x_chqspi_clock64mhz.bin
ifeq ($(OS),Windows_NT)
  EXE_EXT=.exe
  SBL_OUTRPRC=$(SBL_TOOLS_PATH)/out2rprc/out2rprc.exe
else
  SBL_OUTRPRC=mono $(SBL_TOOLS_PATH)/out2rprc/out2rprc.exe
endif
SBL_TIIMAGE=$(SBL_TOOLS_PATH)/tiimage/tiimage$(EXE_EXT)
SBL_CHIMAGE=$(SBL_TOOLS_PATH)/chimage/chimage$(EXE_EXT)
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
  SBL_IMAGE_GEN=$(SBL_TOOLS_PATH)/multicore_image_generator/v2/MulticoreImageGen$(EXE_EXT)
else
  SBL_IMAGE_GEN=$(SBL_TOOLS_PATH)/multicore_image_generator/v1/MulticoreImageGen$(EXE_EXT)
endif
ENDIAN_SWP=$(SBL_TOOLS_PATH)/endian_swap/endian_swap$(EXE_EXT)
SBL_CRC_IMAGE_GEN=$(SBL_TOOLS_PATH)/crc_multicore_image/crc_multicore_image$(EXE_EXT)

#Output file names/paths
ifeq ($(LOCAL_APP_NAME),)
  SBL_IMAGE_NAME=$(APP_NAME)_$(CORE)_$(BUILD_PROFILE_$(CORE))
else
  SBL_IMAGE_NAME=$(LOCAL_APP_NAME)_$(BUILD_PROFILE_$(CORE))
endif
ifeq ($(BUILD_HS),yes)
  HS_SUFFIX=_unsigned
  SBL_HS_CHECK_MSHIELD_USES := $(shell grep SOC_VARIANT $(MSHIELD_DK_DIR)/src/config.mk | grep TDA2XX && echo "yes" || echo "no")
else
  SBL_HS_CHECK_MSHIELD_USES := no
endif
SBL_BIN_PATH=$(BINDIR)/$(SBL_IMAGE_NAME)$(HS_SUFFIX).bin
SBL_BIN_PATH_SIGNED=$(BINDIR)/$(SBL_IMAGE_NAME).xloader
SBL_TIIMAGE_PATH=$(BINDIR)/$(SBL_IMAGE_NAME)$(HS_SUFFIX).tiimage
SBL_CHIMAGE_PATH=$(BINDIR)/$(SBL_IMAGE_NAME).chimage
SBL_TIIMAGE_PATH_SIGNED=$(BINDIR)/$(SBL_IMAGE_NAME).xloader
SBL_TIIMAGE_PATH_SIGNED_BE=$(BINDIR)/$(SBL_IMAGE_NAME)_BE.xloader
SBL_RPRC_PATH=$(BINDIR)/$(SBL_IMAGE_NAME).rprc
SBL_APPIMAGE_PATH=$(BINDIR)/$(SBL_IMAGE_NAME).appimage
SBL_APPIMAGE_PATH_BE=$(BINDIR)/$(SBL_IMAGE_NAME)_BE.appimage
ifeq ($(BUILD_PROFILE_$(CORE)),release)
  SBL_MLO_PATH=$(BINDIR)/MLO$(HS_SUFFIX)
  SBL_MLO_PATH_SIGNED=$(BINDIR)/MLO
else
  SBL_MLO_PATH=$(BINDIR)/$(BUILD_PROFILE_$(CORE))/MLO$(HS_SUFFIX)
  SBL_MLO_PATH_SIGNED=$(BINDIR)/$(BUILD_PROFILE_$(CORE))/MLO
endif

SBL_IMAGE_PATH=$(SBL_BIN_PATH)
SBL_IMAGE_PATH_SIGNED=$(SBL_BIN_PATH_SIGNED)
SECURE_IMAGE_TYPE=X-LOADER
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), sd))
  SBL_IMAGE_PATH=$(SBL_MLO_PATH)
  SBL_IMAGE_PATH_SIGNED=$(SBL_MLO_PATH_SIGNED)
  SECURE_IMAGE_TYPE=MLO
endif
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi qspi_sd))
  SBL_IMAGE_PATH=$(SBL_TIIMAGE_PATH)
  SBL_IMAGE_PATH_SIGNED=$(SBL_TIIMAGE_PATH_SIGNED)
endif
SBL_STDOUT_FILE=$(BINDIR)/temp_stdout.txt
SBL_STDOUT_FILE2=$(BINDIR)/temp_stderr.txt

ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi qspi_sd))
  SBL_ENDIAN=BE
endif
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), sd))
  SBL_ENDIAN=LE
endif

#SBL image generation
ifeq ($(BUILD_HS),yes)
sbl_imagegen: $(SBL_IMAGE_PATH_SIGNED)
else
sbl_imagegen: $(SBL_IMAGE_PATH)
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2ex tda2px))
  SBL_HS_ADDRESS=0xffffffff
endif
ifeq ($(SOC), tda3xx)
  SBL_HS_ADDRESS=0x00300000
endif
ifeq ($(SBL_TYPE), mflash)
  SBL_HS_ADDRESS=0xffffffff
endif

$(SBL_IMAGE_PATH): $(EXE_NAME)
	$(RM) -f $@
	$(MKDIR) -p $(BINDIR)
	$(SBL_OBJ_COPY) --gap-fill=0xff -O binary $(EXE_NAME) $(SBL_BIN_PATH)
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), sd qspi qspi_sd))
	$(CHMOD) a+x $(SBL_TIIMAGE)
#For HS build don't append GP Header at the top of SBL
  ifeq ($(BUILD_HS),yes)
	$(SBL_TIIMAGE) $(SBL_HS_ADDRESS) LE $(SBL_BIN_PATH) $(SBL_TIIMAGE_PATH)
  else
	$(SBL_TIIMAGE) $(SBL_RUN_ADDRESS) $(SBL_ENDIAN) $(SBL_BIN_PATH) $(SBL_TIIMAGE_PATH)
  endif
	$(RM) -f $(SBL_BIN_PATH)
  ifeq ($(BUILD_HS),no)
    ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
      ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi))
	  $(CHMOD) a+x $(SBL_CHIMAGE)
	  $(SBL_CHIMAGE) $(SBL_CHIMAGE_BIN_FILE) $(SBL_TIIMAGE_PATH) $(SBL_CHIMAGE_PATH)
	  $(ECHO) \# SBL CH image $(SBL_CHIMAGE_PATH) created.
      endif
    endif
  endif
  ifeq ($(BOOTMODE),$(filter $(BOOTMODE), sd))
    ifneq ($(BUILD_PROFILE_$(CORE)),release)
	$(MKDIR) -p $(BINDIR)/$(BUILD_PROFILE_$(CORE))
    endif
	$(MV) $(SBL_TIIMAGE_PATH) $(SBL_MLO_PATH)
  endif
endif
	$(ECHO) \# SBL image $@ created.
	$(ECHO) \#

ifeq ($(BUILD_HS),yes)
$(SBL_IMAGE_PATH_SIGNED): $(SBL_IMAGE_PATH)
	$(MAKE) secure_sign_sbl
endif

secure_sign_sbl:
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2ex tda2px))
  ifeq ($(SBL_HS_CHECK_MSHIELD_USES),no)
	$(ECHO) "# !!!! MSHIELD-DK/SECDEV is not setup for TDA2XX"
	$(ECHO) "# !!!! Set this using"
	$(ECHO) "# !!!!      cd $(MSHIELD_DK_DIR)/src && ./config.pl && cd -"
	$(ECHO) "# !!!! Make sure arm-linux-gnueabihf-gcc is present in PATH"
	$(ECHO) "# !!!! Check user-guide for more details."
	exit 1
  endif
	$(MSHIELD_DK_DIR)/scripts/create-boot-image.sh $(SECURE_IMAGE_TYPE) $(SBL_IMAGE_PATH) $(SBL_IMAGE_PATH_SIGNED) >> $(SBL_STDOUT_FILE)
  ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi))
	$(CHMOD) a+x $(ENDIAN_SWP)
	$(ENDIAN_SWP) $(SBL_IMAGE_PATH_SIGNED) $(SBL_TIIMAGE_PATH_SIGNED_BE)
	$(RM) -f $(SBL_IMAGE_PATH_SIGNED)
	$(MV) $(SBL_TIIMAGE_PATH_SIGNED_BE) $(SBL_IMAGE_PATH_SIGNED)
  endif
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
	$(CHMOD) u+x $(SBL_TDA3X_SIGNING_TOOL_DIR)/isw_cert_gen.py
ifeq ($(SBL_TYPE), mflash)
	$(SBL_TDA3X_SIGNING_TOOL_DIR)/isw_cert_gen.py --isw-file=$(SBL_IMAGE_PATH) --out $(SBL_IMAGE_PATH_SIGNED) --key=$(SBL_TDA3X_SIGNING_TOOL_DIR)/rootkey.pem >$(SBL_STDOUT_FILE) 2>$(SBL_STDOUT_FILE2)
else
	$(SBL_TDA3X_SIGNING_TOOL_DIR)/isw_cert_gen.py --isw-file $(SBL_IMAGE_PATH) --out $(SBL_IMAGE_PATH_SIGNED) --key $(SBL_TDA3X_SIGNING_TOOL_DIR)/rootkey.pem --gpimage >$(SBL_STDOUT_FILE) 2>$(SBL_STDOUT_FILE2)
endif
  ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi qspi-sd))
	$(CHMOD) a+x $(ENDIAN_SWP)
	$(ENDIAN_SWP) $(SBL_IMAGE_PATH_SIGNED) $(SBL_TIIMAGE_PATH_SIGNED_BE)
	$(RM) -f $(SBL_IMAGE_PATH_SIGNED)
	$(MV) $(SBL_TIIMAGE_PATH_SIGNED_BE) $(SBL_IMAGE_PATH_SIGNED)
  endif
endif
	$(RM) -f $(SBL_STDOUT_FILE) $(SBL_STDOUT_FILE2)
	$(ECHO) \# Signed SBL image $(SBL_IMAGE_PATH_SIGNED) created.
	$(ECHO) \#

#SBL App image generation
sbl_appimagegen: $(SBL_APPIMAGE_PATH)

$(SBL_APPIMAGE_PATH): $(EXE_NAME)
	$(RM) -f $@ $(SBL_APPIMAGE_PATH_BE) $(SBL_RPRC_PATH)
	$(SBL_OUTRPRC) $(EXE_NAME) $(SBL_RPRC_PATH) >> $(SBL_STDOUT_FILE)
	$(CHMOD) a+x $(SBL_IMAGE_GEN)
	$(SBL_IMAGE_GEN) LE $(SBL_DEV_ID) $@ $(SBL_CORE_ID_$(CORE)) $(SBL_RPRC_PATH) >> $(SBL_STDOUT_FILE)
	$(SBL_IMAGE_GEN) BE $(SBL_DEV_ID) $(SBL_APPIMAGE_PATH_BE) $(SBL_CORE_ID_$(CORE)) $(SBL_RPRC_PATH) >> $(SBL_STDOUT_FILE)
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  ifneq ($(BUILD_HS),yes)
	$(RM) -f $(SBL_APPIMAGE_PATH_BE)
	$(SBL_CRC_IMAGE_GEN) $@ $(SBL_APPIMAGE_PATH_BE) >> $(SBL_STDOUT_FILE)
  endif
endif
	$(RM) -f $(SBL_STDOUT_FILE)
	$(ECHO) \# SBL App image $@ and $(SBL_APPIMAGE_PATH_BE) created.
	$(ECHO) \#

endif

# Nothing beyond this point

