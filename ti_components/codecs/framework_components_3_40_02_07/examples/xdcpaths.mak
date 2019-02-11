#
#  Copyright (c) 2016, Texas Instruments Incorporated
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
#  ======== xdcpaths.mak ========
#  definition of XDC paths and commands
#
#  This makefile constructs the "search path" for the XDCtools where it finds
#  numerous components and packages needed to build examples and
#  programs.  See examples/build_instructions.html for general details about
#  this file.
#
#  USER NOTE:
#  1) you can remove some of the devices from the "DEVICE" list to reduce
#     the build time (and possibly avoid checking for presence of a component
#     you don't need)

#
# Note, this is a space-delimited list.
#
#DEVICE := OMAP3530 OMAPL138 OMAP4430 C6472 C6474 TI816X TI814X C6678 C6670 TI813X
DEVICE := TI813X

# Set this to your FC installation dir
FC_INSTALL_DIR = _your_FC_folder_/framework_components_3_40_02_07

# Pre-pend these vars to what products.mak's .show-products prints
.show-products::
	@echo "DEVICE                      = $(DEVICE)"
	@echo "FC_INSTALL_DIR              = $(FC_INSTALL_DIR)"

include $(FC_INSTALL_DIR)/products.mak

# The appropriate dependencies will be used to generate the XDC_PATH.
# Any other components your example requires can be added to thsi variable
# MY_XDC_PATH := <your component>/packages;
MY_XDC_PATH :=

# check above settings for correctness
include $(EXAMPLES_ROOTDIR)/buildutils/xdcpathcheck.mak
