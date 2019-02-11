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

# Filename: rules_pru.mk
#
# Make rules for TI CL compiler - This file has all the common rules and defines
# required for PRU CORE 0 and CORE 1 ISA
#


# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(CL_PRU_INSTALL_PATH)/include
CODEGEN_BIN_INCLUDE = $(CL_PRU_INSTALL_PATH)/lib
CCS_PRU_INCLUDE = $(SDK_INSTALL_PATH)/ccsv6/ccs_base/pru/include
CC = $(CL_PRU_INSTALL_PATH)/bin/clpru
AR = $(CL_PRU_INSTALL_PATH)/bin/arpru
LNK = $(CL_PRU_INSTALL_PATH)/bin/clpru
SIZE = $(CL_PRU_INSTALL_PATH)/bin/ofdpru
HEX = $(CL_PRU_INSTALL_PATH)/bin/hexpru

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -v3 -g --endian=$(ENDIAN)

ifeq ($(PRUVERSION),REV2)
    CFLAGS_INTERNAL += -DICSS_REV2
endif
ifeq ($(PRUVERSION),REV1)
    CFLAGS_INTERNAL += -DICSS_REV1
endif

CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)

LNKFLAGS_INTERNAL_BUILD_PROFILE = -v3 -g --endian=$(ENDIAN) --define=$(SOC) --diag_wrap=off --diag_warning=225 --display_error_number --hardware_mac=on -z --stack_size=0 --heap_size=0 --reread_libs --warn_sections

CFLAGS_INTERNAL += --diag_wrap=off --diag_warning=225 --display_error_number --hardware_mac=on --preproc_with_compile -eo.$(OBJEXT) 

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

ifeq ($(CORE),pru_0)
    ifeq ($(HOSTCORE), $(filter $(HOSTCORE), c66x))
        HEX_LNKCMD_FILE = $(PDK_INSTALL_PATH)/ti/build/pruss/PRU0_$(PRUVERSION)_to_C66.cmd
    endif
    ifeq ($(HOSTCORE), $(filter $(HOSTCORE), a8host a9host a15_0 ipu1_0))
        HEX_LNKCMD_FILE = $(PDK_INSTALL_PATH)/ti/build/pruss/PRU0_$(PRUVERSION)_to_ARM.cmd
    endif
endif
ifeq ($(CORE),pru_1)
    ifeq ($(HOSTCORE), $(filter $(HOSTCORE), c66x))
        HEX_LNKCMD_FILE = $(PDK_INSTALL_PATH)/ti/build/pruss/PRU1_$(PRUVERSION)_to_C66.cmd
    endif
    ifeq ($(HOSTCORE), $(filter $(HOSTCORE), a8host a9host a15_0 ipu1_0))
        HEX_LNKCMD_FILE = $(PDK_INSTALL_PATH)/ti/build/pruss/PRU1_$(PRUVERSION)_to_ARM.cmd
    endif
endif

# Object file creation
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) $(_CFLAGS) -I$(CCS_PRU_INCLUDE) $(INCLUDES) $(CFLAGS_DIROPTS) --preproc_dependency="$(basename $(notdir $<)).d" $<

$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm | $(OBJDIR) $(DEPDIR)
	$(ECHO) \# Compiling $(PRINT_MESSAGE): $<
	$(CC) $(_CFLAGS) -I$(CCS_PRU_INCLUDE) $(INCLUDES) $(CFLAGS_DIROPTS) --preproc_dependency="$(basename $(notdir $<)).d" $<

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON += -I$(CODEGEN_INCLUDE) -I$(CODEGEN_BIN_INCLUDE)

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_BUILD_PROFILE) $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE)) 

LINK_PATHS += $(CL_PRU_INSTALL_PATH)/lib/libc.a

LNK_INCLUDES = $(addprefix -l,$(LINK_PATHS))

LNK_OUTPUT_FILE = $(OBJDIR)/$(HEADERNAME)

# Archive/library file creation
$(LNK_OUTPUT_FILE) : $(OBJ_PATHS_ASM) $(OBJ_PATHS)
	$(ECHO) \#
	$(ECHO) \# Linking into $(PRINT_MESSAGE) into $(LNK_OUTPUT_FILE)/$(HEADERNAME).$(OUTEXT)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LNKCMD_FILE) -o $@.$(OUTEXT) -m $@.map --xml_link_info="$@_linkInfo.xml" $(LNK_INCLUDES)


$(HEADERDIR)/$(HEADERNAME).$(HEADEREXT) : $(LNK_OUTPUT_FILE) | $(HEADERDIR)
	$(ECHO) \#
	$(ECHO) \# Generating output header into $(PRINT_MESSAGE) into $(HEADERDIR)/$(HEADERNAME).bin...
	$(ECHO) \#
	$(HEX) $(HEX_LNKCMD_FILE) $(OBJDIR)/$(HEADERNAME).$(OUTEXT) -o $(HEADERDIR)/$(HEADERNAME).bin


# Nothing beyond this point
