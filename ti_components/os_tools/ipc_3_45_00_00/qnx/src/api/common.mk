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

NAME = ipc

define PINFO
PINFO DESCRIPTION=IPC QNX User library
endef

INSTALLDIR = /usr/lib

CCOPTS += -DIPC_BUILDOS_QNX

ifeq ("$(IPC_PLATFORM)", "vayu")
CCOPTS += -DGATEMP_SUPPORT
endif

# source path
EXTRA_SRCVPATH += \
       $(IPC_REPO)/qnx/src/api \
       $(IPC_REPO)/qnx/src/api/gates

EXCLUDE_OBJS =

# include path
EXTRA_INCVPATH += \
        $(IPC_REPO)/packages \
	$(IPC_REPO)/qnx/include \
        $(IPC_REPO)/hlos_common/include \
	$(IPC_REPO)/qnx/src/ipc3x_dev

include $(MKFILES_ROOT)/qtargets.mk
OPTIMIZE__gcc=$(OPTIMIZE_NONE_gcc)

# install the headers
POST_INSTALL += \
        $(CP_HOST) -Rv $(IPC_REPO)/qnx/include/ti/ipc/interfaces $(INSTALL_ROOT_nto)/usr/include/ti/ipc; \
        $(CP_HOST) -Rv $(IPC_REPO)/packages/ti/ipc/MessageQ.h $(INSTALL_ROOT_nto)/usr/include/ti/ipc/MessageQ.h; \
        $(CP_HOST) -Rv $(IPC_REPO)/packages/ti/ipc/NameServer.h $(INSTALL_ROOT_nto)/usr/include/ti/ipc/NameServer.h; \
        $(CP_HOST) -Rv $(IPC_REPO)/packages/ti/ipc/GateMP.h $(INSTALL_ROOT_nto)/usr/include/ti/ipc/GateMP.h; \
        $(CP_HOST) -Rv $(IPC_REPO)/packages/ti/ipc/Ipc.h $(INSTALL_ROOT_nto)/usr/include/ti/ipc/Ipc.h; \
        $(CP_HOST) -Rv $(IPC_REPO)/qnx/include/ti/ipc/Std.h $(INSTALL_ROOT_nto)/usr/include/ti/ipc/Std.h

# Quiet the build output
include $(IPC_REPO)/qnx/quiet.mk
