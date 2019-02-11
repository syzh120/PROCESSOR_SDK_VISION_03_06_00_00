#
#   Copyright (c) 2012-2015, Texas Instruments Incorporated
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#
#   *  Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#
#   *  Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#
#   *  Neither the name of Texas Instruments Incorporated nor the names of
#      its contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  ======== ipc-bios.mak ========
#

#
# Where to install/stage the packages
# Typically this would point to the devkit location
#
DESTDIR ?= <UNDEFINED>

packagesdir ?= /packages
libdir ?= /lib
includedir ?= /include

ifeq ($(docdir),)
docdir := /share/ti/ipc/doc
packagedocdir := /docs/ipc
else
packagedocdir := $(docdir)
endif

ifeq ($(prefix),)
prefix := /usr
packageprefix := /
else
packageprefix := $(prefix)
endif

include ./products.mak

#
# Set XDCARGS to some of the variables above.  XDCARGS are passed
# to the XDC build engine... which will load ipc-bios.bld... which will
# extract these variables and use them to determine what to build and which
# toolchains to use.
#
# Note that not all of these variables need to be set to something valid.
# Unfortunately, since these vars are unconditionally assigned, your build line
# will be longer and more noisy than necessary (e.g., it will include C66
# assignment even if you're just building for C64P).
#
# Some background is here:
#     http://rtsc.eclipse.org/docs-tip/Command_-_xdc#Environment_Variables
#
XDCARGS= \
    PLATFORM=\"$(PLATFORM)\" \
    BIOS_SMPENABLED=\"$(BIOS_SMPENABLED)\" \
    ti.targets.C64P=\"$(ti.targets.C64P)\" \
    ti.targets.C64P_big_endian=\"$(ti.targets.C64P_big_endian)\" \
    ti.targets.C674=\"$(ti.targets.C674)\" \
    ti.targets.arm.elf.Arm9=\"$(ti.targets.arm.elf.Arm9)\" \
    ti.targets.arm.elf.A8F=\"$(ti.targets.arm.elf.A8F)\" \
    ti.targets.arm.elf.A8Fnv=\"$(ti.targets.arm.elf.A8Fnv)\" \
    ti.targets.arm.elf.M3=\"$(ti.targets.arm.elf.M3)\" \
    ti.targets.arm.elf.M4=\"$(ti.targets.arm.elf.M4)\" \
    ti.targets.arm.elf.M4F=\"$(ti.targets.arm.elf.M4F)\" \
    ti.targets.elf.C64P=\"$(ti.targets.elf.C64P)\" \
    ti.targets.elf.C64P_big_endian=\"$(ti.targets.elf.C64P_big_endian)\" \
    ti.targets.elf.C64T=\"$(ti.targets.elf.C64T)\" \
    ti.targets.elf.C66=\"$(ti.targets.elf.C66)\" \
    ti.targets.elf.C66_big_endian=\"$(ti.targets.elf.C66_big_endian)\" \
    ti.targets.elf.C674=\"$(ti.targets.elf.C674)\" \
    ti.targets.arp32.elf.ARP32=\"$(ti.targets.arp32.elf.ARP32)\" \
    ti.targets.arp32.elf.ARP32_far=\"$(ti.targets.arp32.elf.ARP32_far)\" \
    gnu.targets.arm.A8F=\"$(gnu.targets.arm.A8F)\" \
    gnu.targets.arm.A15F=\"$(gnu.targets.arm.A15F)\"

ifeq ($(MAKECMDGOALS),release)
    XDCARGS += GOAL=release
endif

#
# Get list of packages to rebuild. Remove examples from the list.
#
XDCPKG := $(XDC_INSTALL_DIR)/bin/xdcpkg

# Check for Windows specific env vars to determine if we are on Windows
ifneq (,$(findstring :,$(WINDIR)$(windir)$(COMSPEC)$(comspec)))
   # Replace '/' with '\' because cmd.exe requires '\'s in command names
   XDCPKG := $(subst /,\,$(XDCPKG))
endif

LIST = $(shell $(XDCPKG) ./packages)

#
# Set XDCPATH to contain necessary repositories.
#
XDCPATH = $(BIOS_INSTALL_DIR)/packages
export XDCPATH

#
# Set XDCOPTIONS.  Use -v for a verbose build.
#
#XDCOPTIONS=v
export XDCOPTIONS

#
# Set XDC executable command
# Note that XDCBUILDCFG points to the ipc-bios.bld file which uses
# the arguments specified by XDCARGS
#
XDC = $(XDC_INSTALL_DIR)/xdc $(JOBS) XDCARGS="$(XDCARGS)" XDCBUILDCFG=./ipc-bios.bld

######################################################
## Shouldnt have to modify anything below this line ##
######################################################

all:
	@echo building ipc packages ...
# build everything in the Bios IPC package
	@$(XDC) -P $(LIST)

interfaces:
	@echo building interfaces for  ipc packages ...
	@$(patsubst ${JOBS},,$(XDC)) .interfaces -P $(LIST)

libs:
	@echo "#"
	@echo "# Making $@ ..."
	@$(XDC) .dlls -P $(patsubst %/tests,,$(LIST))

release: interfaces
	@echo building ipc packages ...
# create a XDC release for the Bios IPC package
	@$(XDC) release -P $(LIST)

clean:
	@ echo cleaning ipc packages ...
	@ $(XDC) clean -Pr ./packages

install-packages:
	@ echo installing ipc packages to $(DESTDIR) ...
	@ mkdir -p $(DESTDIR)/$(packageprefix)/$(packagedocdir)
	@ cp -rf $(wildcard ipc_*_release_notes.html) docs/* $(DESTDIR)/$(packageprefix)/$(packagedocdir)
	@ mkdir -p $(DESTDIR)/$(packageprefix)/$(packagesdir)
	@ cp -rf packages/* $(DESTDIR)/$(packageprefix)/$(packagesdir)

install:
	@ echo installing ti/ipc to $(DESTDIR) ...
	@ mkdir -p $(DESTDIR)/$(prefix)/$(docdir)
	@ cp -rf $(wildcard ipc_*_release_notes.html) docs/* $(DESTDIR)/$(prefix)/$(docdir)
	@ mkdir -p $(DESTDIR)/$(prefix)/$(includedir)/ti/ipc
	@ cp -rf packages/ti/ipc/*.h $(DESTDIR)/$(prefix)/$(includedir)/ti/ipc
