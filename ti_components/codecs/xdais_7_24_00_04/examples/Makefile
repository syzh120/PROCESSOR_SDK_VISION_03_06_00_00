#
#  Copyright (c) 2013, Texas Instruments Incorporated
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
#  ======== Makefile ========
#

# Set location of various tools
XDC_INSTALL_DIR = _your_XDCTOOLS_installation_directory/xdctools_3_23_00_32
XDAIS_INSTALL_DIR = _your_XDAIS_installation_directory/xdais_7_24_00_04

# Set location of xdc executable
XDC = $(XDC_INSTALL_DIR)/xdc

# Set XDCPATH to contain necessary repositories.
# Note, the '^' character puts 'this' repository first in the XDCPATH.  This is
# necessary because that's where config.bld will be found.
XDCPATH = ^;$(XDAIS_INSTALL_DIR)/packages

# How many concurrent build threads (i.e. jobs) do you want to allow to run
JOBS=4

# Conditionally, you can create verbose build output
XDCOPTIONS=v

########################################################
## Shouldn't have to modify anything be low this line ##
########################################################

export XDCOPTIONS
export XDCPATH

all: .all-packages

# This recursively locates all packages in the "ti" directory, builds
# and releases them
.all-packages:
	$(XDC) release --jobs=$(JOBS) -PR ti

# This recursively cleans all packages in the "ti" directory
clean: clean-packages

clean-packages:
	$(XDC) clean --jobs=$(JOBS) -PR ti
