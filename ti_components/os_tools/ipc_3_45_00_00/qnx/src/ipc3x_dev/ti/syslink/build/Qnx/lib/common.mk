#
# Copyright (c) 2015, Texas Instruments Incorporated
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

INSTALLDIR=/usr/lib

define PINFO
PINFO DESCRIPTION=IPC QNX Usr Libs
endef
NAME=ipc_client

# ---------------------------------------------------------------------------- #
# Defines                                                                      #
# ---------------------------------------------------------------------------- #
# Override definitions in base Makefile if required

#To Over ride the usage of ipc memory manager
IPC_USE_SYSMGR := 0
#To Over ride the build optimization flag
IPC_BUILD_OPTIMIZE := 0
#To override the debug build flag
IPC_BUILD_DEBUG := 0
#To override the TRACE flag
IPC_TRACE_ENABLE := 0

ifeq ("$(IPC_PLATFORM)", "omap5430")
CCOPTS += -DIPC_PLATFORM_OMAP5430
endif # ifeq ("$(IPC_PLATFORM)", "omap5430")

#default IPC Product root path and can be overridden from commandline
IPC_ROOT = $(PROJECT_ROOT)/../../../../..
IPC_BUILDOS = Qnx

#For SOURCE and include paths
#-include $(IPC_ROOT)/ti/syslink/buildutils/hlos/usr/Makefile.inc

#Add Resource Manager include path
#EXTRA_INCVPATH+=$(IPC_ROOT)/ti/syslink/utils/hlos/knl/Qnx/resMgr

#Add extra include path
EXTRA_INCVPATH+=$(IPC_ROOT)	\
				$(IPC_ROOT)/ti/syslink/inc	\
				$(IPC_ROOT)/ti/syslink/inc/usr/$(IPC_BUILDOS)	\
				$(IPC_ROOT)/ti/syslink/inc/usr	\
				$(IPC_ROOT)/ti/syslink/inc/$(IPC_BUILDOS) \
				$(IPC_REPO)/packages \
				$(IPC_REPO)/qnx/include \
                                $(IPC_REPO)/hlos_common/include
#SRCS:=$(CSRCS)

#SRCDIRS=$(sort $(foreach i,$(CSRCS),$(shell dirname $i)))
#EXTRA_SRCVPATH+=$(SRCDIRS)
EXTRA_SRCVPATH+=$(IPC_ROOT)/ti/syslink/ipc/hlos/usr \
				$(IPC_ROOT)/ti/syslink/ipc/hlos/usr/$(IPC_BUILDOS)	\
				$(IPC_ROOT)/ti/syslink/utils/hlos	\
				$(IPC_ROOT)/ti/syslink/utils/hlos/usr	\
				$(IPC_ROOT)/ti/syslink/utils/hlos/usr/$(IPC_BUILDOS)	\
				$(IPC_ROOT)/ti/syslink/utils/hlos/usr/osal/$(IPC_BUILDOS)

#Using the default build rules TODO: to selective pick and choose the compiler/linker/archiver & build rules
include $(MKFILES_ROOT)/qtargets.mk
CCOPTS += -DIPC_BUILDOS_QNX -DIPC_BUILD_DEBUG $(QNX_CFLAGS)
ifeq ("$(IPC_DEBUG)", "1")
#enable debug build
CCOPTS += -g -O0
endif # ifeq ("$(IPC_DEBUG)", "")
CCFLAGS += $(COMPILE_FLAGS)
CCFLAGS += -fPIC

# Quiet the build output
include $(IPC_REPO)/qnx/quiet.mk
