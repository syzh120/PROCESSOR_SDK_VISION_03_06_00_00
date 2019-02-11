#
#  Copyright (c) 2011, Texas Instruments Incorporated
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
#  ======== xdcpathcheck.mak ========
#  This file checks various paths set in xdcpaths.mak for their correctness
#  Also complains if required toolchains are not set by the user.
# -----------------------------------------------------------------------------

# Most users have no need to modify anything in this file

# -----------------------------------------------------------------------------

# If we're a subcomponent, allow larger product settings to override our
# defaults.  The variable $(RULES_MAKE) can be overridden on the 'make'
# command-line if the location below is not correct (for example, if you
# want to use a Rules.make from some other location.
RULES_MAKE := $(FC_INSTALL_DIR)/../Rules.make
ifneq ($(wildcard $(RULES_MAKE)),)
include $(RULES_MAKE)
endif

# Note, some good defensive programming here could be to ensure $(DEVICES) and
# $(PROGRAMS) - and others! - don't contain any space characters

#
# Set XDCARGS to some of the variables above.  xdcrules.mak will pass this
# variable to the XDC build engine... which will load config.bld... which will
# extract these variables and use them to determine what to build and which
# toolchains to use.
#
# Note that not all of these variables need to be set to something valid.
# Unfortunately, since these vars are unconditionally assigned, your build line
# will be longer and more noisy than necessary (e.g., it will include CC_V5T
# assignment even if you're just building for WinCE.  While benign, it is
# annoying.  In future releases, we'll clean up this XDCARGS assignment and
# only include the vars that are required.
#
# Some background is here:
#     http://rtsc.eclipse.org/docs-tip/Command_-_xdc#Environment_Variables
#
XDCARGS= \
    DEVICE=\"$(DEVICE)\" \
    PROGRAMS=\"$(PROGRAMS)\" \
    GPPOS=\"$(GPPOS)\" \
    ti.targets.C64P=\"$(ti.targets.C64P)\" \
    ti.targets.C674=\"$(ti.targets.C674)\" \
    ti.targets.arm.elf.M3=\"$(ti.targets.arm.elf.M3)\" \
    ti.targets.elf.C64P=\"$(ti.targets.elf.C64P)\" \
    ti.targets.elf.C64T=\"$(ti.targets.elf.C64T)\" \
    ti.targets.elf.C66=\"$(ti.targets.elf.C66)\" \
    ti.targets.elf.C674=\"$(ti.targets.elf.C674)\" \
    gnu.targets.arm.GCArmv5T=\"$(gnu.targets.arm.GCArmv5T)\"

# -----------------------------------------------------------------------------

# Set XDCPATH to contain necessary repositories.
XDC_PATH = $(XDAIS_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(CMEM_INSTALL_DIR)/packages;$(LINK_INSTALL_DIR)/packages;$(OSAL_INSTALL_DIR)/packages;$(EDMA3_LLD_INSTALL_DIR)/packages;$(IPC_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages

# XDC_PATH is complete. Any other components you could add as
ifneq ($(MY_XDC_PATH),)
    XDC_PATH := $(MY_XDC_PATH);$(XDC_PATH)
endif
