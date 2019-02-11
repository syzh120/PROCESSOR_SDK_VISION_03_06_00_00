#
# Copyright (c) 2013-2015, Texas Instruments Incorporated
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
ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

NAME = mmrpc

define PINFO
PINFO DESCRIPTION=MmRpc User Library
endef

INSTALLDIR = /usr/lib

CCOPTS += -DIPC_BUILDOS_QNX

# source path
EXTRA_SRCVPATH = $(IPC_REPO)/packages/ti/ipc/mm
SRCS = MmRpc.c

EXCLUDE_OBJS =

# include path
EXTRA_INCVPATH += \
        $(IPC_REPO)/packages \
        $(IPC_REPO)/qnx/src/ipc3x_dev/ti/syslink/inc

include $(MKFILES_ROOT)/qtargets.mk
OPTIMIZE__gcc=$(OPTIMIZE_NONE_gcc)

# install the header
POST_INSTALL += \
	$(CP_HOST) -Rv $(IPC_REPO)/packages/ti/ipc/mm/MmRpc.h $(INSTALL_ROOT_nto)/usr/include/ti/ipc/mm/MmRpc.h

# Quiet the build output
include $(IPC_REPO)/qnx/quiet.mk
