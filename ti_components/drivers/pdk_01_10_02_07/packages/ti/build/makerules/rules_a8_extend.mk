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

# Filename: rules_a8_extend.mk
#
# Make rules for A8 - This file has any extension of make rules for Cortex-A8 ISA
#
# This file needs to change when:
#     1. an extended rule common for A8 ISA has to be added or modified

CROSS_COMPILE = $(CODEGEN_PATH_A8)/bin/arm-none-linux-gnueabi-
OSAL_INSTALL_DIR = $(osal_PATH)

link_dep_extension: linuxdistbld syslink_usrspace

# The following is for Linuxdist package (OSAL)
linuxdistbld:
	$(ECHO) \# Building linuxdist - $@...
	$(MKDIR) -p $(OSAL_INSTALL_DIR)/packages/linuxdist/build/lib
	$(MAKE) -C $(OSAL_INSTALL_DIR)/packages/linuxdist/build \
            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            PRECONFIG=$(OSAL_INSTALL_DIR)/packages/linuxdist/preconfig/production \
            CFLAGS=-O2
	$(MKDIR) -p $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs/lib
	$(MAKE) -C $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs \
            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            CFLAGS=-O2

# The following is to build syslink HLOS user space library
syslink_usrspace:
	$(ECHO) \# Building Syslink HLOS user space library
	cd $(syslink_PATH)/ti/syslink/utils/hlos/usr/Linux && $(MAKE) \
            ARCH=arm \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            TOOLCHAIN_PREFIX=$(CROSS_COMPILE) \
            SYSLINK_PLATFORM=TI81XX \
            SYSLINK_VARIANT=TI816X \
            SYSLINK_LOADER=ELF \
            SYSLINK_ROOT=$(syslink_PATH) \

# Nothing beyond this point
