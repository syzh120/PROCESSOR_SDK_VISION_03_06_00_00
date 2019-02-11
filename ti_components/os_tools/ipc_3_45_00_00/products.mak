#
#   Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
#  ======== products.mak ========
#

# Note that these variables can be explicitly set here or on the command line.
# If you want to use variables in the environment, see the GNU make manual's
# -e option:  http://www.gnu.org/software/make/manual/make.html#Environment

# Optional: recommended to install all dependent components in one folder.
#
DEPOT = _your_depot_folder_

# Platform to build for
#   Supported platforms (choose one):
#       OMAPL138, OMAP54XX, DRA7XX, 66AK2G, 66AK2E, TCI6630, TCI6636, TCI6638,
#       TDA3XX
#
# Note, this is used for Linux, QNX and BIOS builds
#
PLATFORM =

# Destination when installing the built binaries
#
# Note, this is used for Linux (if you use ipc-linux.mak to run the
# configure command), QNX and BIOS.
#
DESTDIR =


#################### IPC Linux ####################

# Set up required cross compiler path for IPC Linux configuration and build
#
TOOLCHAIN_LONGNAME = arm-none-linux-gnueabi
TOOLCHAIN_INSTALL_DIR = $(DEPOT)/_your_arm_code_gen_install_
TOOLCHAIN_PREFIX = $(TOOLCHAIN_INSTALL_DIR)/bin/$(TOOLCHAIN_LONGNAME)-

# Path to Linux Kernel - needed to build the IPC user libraries
#
KERNEL_INSTALL_DIR =

# Optional: Specify the Address Family for RPMSG. This value is specified
# either from the Linux kernel specified by KERNEL_INSTALL_DIR above, or
# the make variable AF_RPMSG below. Do not use both.
#
AF_RPMSG =

# Optional: Path to DRM Library
#
DRM_PREFIX =

# Optional: Path to TI Linux Utils product
#
CMEM_INSTALL_DIR =


#################### IPC QNX ####################

# Path to QNX tools installation
#
QNX_INSTALL_DIR =

# Optional: Any additional compile options
#
QNX_CFLAGS =

#################### IPC Bios ####################

# Path to required dependencies for IPC BIOS builds
#
XDC_INSTALL_DIR = $(DEPOT)/_your_xdctools_install_
BIOS_INSTALL_DIR = $(DEPOT)/_your_bios_install_

# Do you want to build SMP-enabled libraries (if supported for your target)?
# Set to either 0 (disabled) or 1 (enabled)
#
BIOS_SMPENABLED=1

# Path to various cgtools
#
ti.targets.elf.C64P =
ti.targets.elf.C64P_big_endian =
ti.targets.elf.C64T =
ti.targets.elf.C66 =
ti.targets.elf.C66_big_endian =
ti.targets.elf.C674 =

ti.targets.arm.elf.Arm9 =
ti.targets.arm.elf.A8F =
ti.targets.arm.elf.A8Fnv =
ti.targets.arm.elf.M3 =
ti.targets.arm.elf.M4 =
ti.targets.arm.elf.M4F =

ti.targets.arp32.elf.ARP32 =
ti.targets.arp32.elf.ARP32_far =

gnu.targets.arm.A8F =
gnu.targets.arm.A15F =
