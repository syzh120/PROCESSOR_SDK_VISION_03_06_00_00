#
#  Copyright (c) 2012, Texas Instruments Incorporated
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
#  ======== makefile ========
#

include ../products.mak

# List of supported devices (choose one): OMAP3530, OMAP4430, TI814X, TI816X, TI811X, C6A8149, VAYU
#
DEVICE = _your_device_

# Set SDK type when building for a TI SDK kit (choose one): EZSDK or NONE
#
SDK = NONE

# Define root dir to install examples into
#
EXEC_DIR = $(CURDIR)/install


############### Don't modify below this line ###############

EXAMPLES = $(wildcard ex??_*)
UNZIP = $(XDC_INSTALL_DIR)/bin/unzip

# determine which shell make is using
ifeq ("$(SHELL)","sh.exe")
    # use Windows commands
    MKSH = CMD
else
    # use Linux commands
    MKSH = SH
endif

EXHOSTOS := bios

ifeq ("$(SDK)","NONE")
    EXSDK =
else
ifeq ("$(MKSH)","SH")
    EXSDK := _$(shell echo $(SDK) | tr A-Z a-z)
else
    EXSDK = _$(SDK)
endif
endif

ARCHIVES = $(wildcard archive/$(DEVICE)_$(EXHOSTOS)_elf$(EXSDK)/ex??_*)


all:
	@echo "#"
	@echo "# Making all examples..."
ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do $(MAKE) -C $$d all; done
else
	@if "$(EXAMPLES)"=="" ( \
            echo "There are no examples to build." \
        ) else ( \
            @for %%d in ($(EXAMPLES)) do $(MAKE) -C %%d all \
        )
endif

help:
	@echo "make all        # build all examples"
	@echo "make clean      # clean all examples (does not delete them)"
	@echo "make clobber    # delete all example"
	@echo "make extract    # unzip examples from archive folder"
	@echo "make install    # install examples onto target file system"
	@echo ""
	@echo "Use the EXEC_DIR variable to override install folder"
	@echo "make EXEC_DIR=/tmp install"
	@echo ""
	@echo "Use -n option to make for dry run"
	@echo "make -n all"
	@echo ""
	@echo "The extract goal will unzip the appropriate examples based"
	@echo "on your settings in the products.mak file. Note: unzip will"
	@echo "prompt before overwritting existing files."
	@echo ""

clean::
	@echo "#"
	@echo "# Cleaning all examples..."
ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do $(MAKE) -C $$d clean; done
else
	@if not "$(EXAMPLES)"=="" \
	@for %%d in ($(EXAMPLES)) do $(MAKE) -C %%d clean
endif

clobber::
	@echo "#"
	@echo "# Deleting all examples..."
ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do rm -rf $$d; done
else
	@if not "$(EXAMPLES)"=="" \
	@for %%d in ($(EXAMPLES)) do rmdir /s /q %%d
endif

# Note: the unzip command will prompt user when target file exists.
extract:
	@echo "#"
	@echo "# Unzipping all examples (from archive/$(DEVICE)_$(EXHOSTOS)_elf$(EXSDK))..."
ifeq ("$(MKSH)","SH")
	@for f in $(ARCHIVES); do $(UNZIP) $$f; done
else
	@if "$(ARCHIVES)"=="" ( \
            echo "No appropriate examples found in archive folder." \
        ) else ( \
            @for %%f in ($(ARCHIVES)) do $(UNZIP) %%f \
        )
endif

install:
	@echo "#"
	@echo "# Installing examples into $(EXEC_DIR)"
ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do \
             $(MAKE) -C $$d install EXEC_DIR=$(EXEC_DIR); \
         done
else
	@for %%d in ($(EXAMPLES)) do \
             $(MAKE) -C %%d install EXEC_DIR=$(EXEC_DIR)
endif
	@$(INSTALL_M) scripts/runall.sh $(EXEC_DIR)


# portable install commands
ifneq ($(wildcard $(XDC_INSTALL_DIR)/bin/echo.exe),)
    INSTALL_M = $(XDC_INSTALL_DIR)/bin/cp.exe
else
    INSTALL_M = install -m 0755
endif
