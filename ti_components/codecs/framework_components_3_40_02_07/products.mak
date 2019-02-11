#
#   Copyright (c) 2012-2013, Texas Instruments Incorporated
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
#  ======== products.mak ========
#

# Optional: recommended to install all dependent components in one folder.
#
DEPOT = _your_depot_folder_


# Path to required dependencies
#
XDAIS_INSTALL_DIR      = $(DEPOT)/_your_xdais_install_
EDMA3_LLD_INSTALL_DIR  = $(DEPOT)/_your_edma3lld_install_
XDC_INSTALL_DIR        = $(DEPOT)/_your_xdctools_install_
BIOS_INSTALL_DIR       = $(DEPOT)/_your_bios_install_

# Path to various cgtools
#
ti.targets.C64P ?=
ti.targets.C674 ?=

ti.targets.elf.C64P ?=
ti.targets.elf.C64T ?=
ti.targets.elf.C66 ?=
ti.targets.elf.C66_big_endian ?=
ti.targets.elf.C674 ?=

ti.targets.arm.elf.M3 ?=
ti.targets.arm.elf.M4 ?=
