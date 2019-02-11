#
#  Copyright (c) 2013-2014, Texas Instruments Incorporated
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
IPC_INSTALL_DIR = ..
include $(IPC_INSTALL_DIR)/products.mak

# HOSTOS is best-effort assigned from values which should already have been
# set in ../products.mak.  If for some reason it is incorrectly determined,
# you can always assign it explicitly here (to Bios, Linux, or Qnx)
#
# If we see KERNEL_INSTALL_DIR set, we assume Linux, else if we see
# QNX_INSTALL_DIR set, we assume Qnx, else we assume Bios.
ifneq ("$(KERNEL_INSTALL_DIR)","")
    HOSTOS = linux
else
    ifneq ("$(QNX_INSTALL_DIR)","")
        HOSTOS = qnx
    else
        HOSTOS = bios
    endif
endif

# Defining an unzip command to extract the provided examples. It uses an
#     XDCTools provided utility but can be defined to a similar utility if
#     XDCTools are not available.
#
UNZIP = $(XDC_INSTALL_DIR)/bin/unzip


###############################################################################
# Generally there is no need to edit the content below.
#
# The below build goals extract and build the examples based on PLATFORM and
#     HOSTOS
###############################################################################


EXEC_DIR = $(CURDIR)/install

# determine which shell make is using
ifeq ("$(SHELL)","sh.exe")
    # use Windows commands
    MKSH = CMD
else
    # use Linux commands
    MKSH = SH
endif


EXHOSTOS = $(HOSTOS)

# Only elf supported now
EXLDR = elf

ARCHIVES = $(filter %.zip, $(wildcard $(PLATFORM)_$(EXHOSTOS)_$(EXLDR)/ex??_*))
EXAMPLES = $(filter %/, $(wildcard $(PLATFORM)_$(EXHOSTOS)_$(EXLDR)/ex??_*/))

all:
	@echo "#"
	@echo "# Making all examples..."
ifeq ("$(EXAMPLES)","")
	@echo "There are no examples to build."
else
    ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do $(MAKE) -C $$d .show;\
            $(MAKE) -C $$d all; done
    else
	@for %%d in ($(EXAMPLES)) do $(MAKE) -C %%d all
    endif
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
ifeq ("$(EXAMPLES)","")
	@echo "No examples found to clean."
else
    ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do $(MAKE) -C $$d clean; done
    else
	@for %%d in ($(EXAMPLES)) do $(MAKE) -C %%d clean
    endif
endif

clobber::
	@echo "#"
	@echo "# Deleting all examples..."
ifeq ("$(EXAMPLES)","")
	@echo "No examples found to delete."
else
    ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do rm -rf $$d; done
    else
	@for %%d in ($(EXAMPLES)) do rmdir /s /q %%d
    endif
endif

# Note: the unzip command will prompt user when target file exists.
extract:
	@echo "#"
	@echo "# Unzipping all examples..."
ifeq ("$(ARCHIVES)","")
	@echo "No appropriate examples found in archive folder."
else
    ifeq ("$(MKSH)","SH")
	@for f in $(ARCHIVES); do $(UNZIP) -o $$f -d $$(dirname $$f); rm $$f; done
    else
	@for %%f in ($(ARCHIVES)) do $(UNZIP) -o -%%f -d %%(dir %%f); rm %%f
    endif
endif

install::
	@echo "#"
	@echo "# Installing examples into $(EXEC_DIR)"
ifeq ("$(EXAMPLES)","")
	@echo "No examples found to install."
else
    ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do \
             $(MAKE) -C $$d install EXEC_DIR=$(EXEC_DIR); \
         done
    else
	@for %%d in ($(EXAMPLES)) do \
             $(MAKE) -C %%d install EXEC_DIR=$(EXEC_DIR)
    endif
endif

install_rov::
	@echo "#"
	@echo "# Installing ROV of examples into $(EXEC_DIR)"
ifeq ("$(EXAMPLES)","")
	@echo "No examples found to install."
else
    ifeq ("$(MKSH)","SH")
	@for d in $(EXAMPLES); do \
             $(MAKE) -C $$d install_rov EXEC_DIR=$(EXEC_DIR); \
         done
    else
	@for %%d in ($(EXAMPLES)) do \
             $(MAKE) -C %%d install_rov EXEC_DIR=$(EXEC_DIR)
    endif
endif


# portable install commands
ifneq ($(wildcard $(XDC_INSTALL_DIR)/bin/echo.exe),)
    INSTALL_M = $(XDC_INSTALL_DIR)/bin/cp.exe
else
    INSTALL_M = install -m 0755
endif
