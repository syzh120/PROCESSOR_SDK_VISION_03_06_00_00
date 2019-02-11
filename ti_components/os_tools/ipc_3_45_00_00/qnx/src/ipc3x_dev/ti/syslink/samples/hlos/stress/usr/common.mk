#
#   Copyright (c) 2013-2015, Texas Instruments Incorporated
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

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION=rpmsg-omx Stress Test
endef

NAME = rpmsg-omx-stress
INSTALLDIR = /dev/null

#default IPC Product root path and can be overridden from commandline
IPC_ROOT = $(PROJECT_ROOT)/../../../../../..
IPC_BUILDOS = Qnx

#Add extra include path
EXTRA_INCVPATH+=$(IPC_ROOT)	\
				$(IPC_ROOT)/ti/syslink/inc	\
				$(IPC_ROOT)/ti/syslink/inc/usr/$(IPC_BUILDOS)	\
				$(IPC_ROOT)/ti/syslink/inc/usr	\
				$(IPC_ROOT)/ti/syslink/inc/$(IPC_BUILDOS)

EXTRA_SRCVPATH+=$(PROJECT_ROOT)/$(IPC_BUILDOS)	\
				$(PROJECT_ROOT)/..

CCOPTS+=-g -O0 -DIPC_BUILDOS_QNX

include $(MKFILES_ROOT)/qtargets.mk

# Quiet the build output
include $(IPC_REPO)/qnx/quiet.mk
