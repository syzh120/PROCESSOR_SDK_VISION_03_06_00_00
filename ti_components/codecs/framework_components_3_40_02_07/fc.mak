#
#   Copyright (c) 2012-2014, Texas Instruments Incorporated
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

#
# Where to install/stage the packages
# Typically this would point to the devkit location
#
DESTDIR ?= <UNDEFINED>

packagesdir ?= /packages
libdir ?= /lib
includedir ?= /include

ifeq ($(docdir),)
    docdir := /share/ti/framework_components/doc
    packagedocdir := /docs/framework_components
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
# Set XDCOPTIONS.  Use -v for a verbose build.
#
#XDCOPTIONS=v
export XDCOPTIONS

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
    ti.targets.C674=\"$(ti.targets.C674)\" \
    ti.targets.arm.elf.M3=\"$(ti.targets.arm.elf.M3)\" \
    ti.targets.arm.elf.M4=\"$(ti.targets.arm.elf.M4)\" \
    ti.targets.elf.C64P=\"$(ti.targets.elf.C64P)\" \
    ti.targets.elf.C64T=\"$(ti.targets.elf.C64T)\" \
    ti.targets.elf.C66=\"$(ti.targets.elf.C66)\" \
    ti.targets.elf.C66_big_endian=\"$(ti.targets.elf.C66_big_endian)\" \
    ti.targets.elf.C674=\"$(ti.targets.elf.C674)\"

#
# Get list of packages to rebuild.  Using LIST allows SDKs to only build
# a subset of packages if they want to.  Default behavior builds all
# packages.
#
LIST = $(shell $(XDC_INSTALL_DIR)/bin/xdcpkg ./packages)

# Set XDCPATH to contain necessary repositories.
XDCPATH = $(XDAIS_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(EDMA3_LLD_INSTALL_DIR)/packages
export XDCPATH

#
# Set XDC executable command
# Note that XDCBUILDCFG points to the fc.bld file which uses
# the arguments specified by XDCARGS
#
XDC = $(XDC_INSTALL_DIR)/xdc XDCARGS="$(XDCARGS)" XDCBUILDCFG=./fc.bld

######################################################
## Shouldnt have to modify anything below this line ##
######################################################

all:
	@ echo building packages ...
	@ $(XDC) -P $(LIST)

libs:
	@echo "#"
	@echo "# Making $@ ..."
	$(XDC) .libraries -P $(LIST)
#	$(XDC) .dlls -P $(LIST)
	misraListErrors packages/misra > misraReport.txt

release:
	@ echo releasing packages ...
	@ $(XDC) release -P $(LIST)

# This cleans all packages rooted in ./packages
clean:
	@ echo cleaning fc packages ...
	@ $(XDC) clean -Pr ./packages

install-packages:
	@ echo installing packages to $(DESTDIR) ...
	@ mkdir -p $(DESTDIR)/$(packageprefix)/$(packagedocdir)
	@ cp -rf $(wildcard ipc_*_release_notes.html) docs/* $(DESTDIR)/$(packageprefix)/$(packagedocdir)
	@ mkdir -p $(DESTDIR)/$(packageprefix)/$(packagesdir)
	@ cp -rf packages/* $(DESTDIR)/$(packageprefix)/$(packagesdir)

# Nothing for this Linux goal
install:
