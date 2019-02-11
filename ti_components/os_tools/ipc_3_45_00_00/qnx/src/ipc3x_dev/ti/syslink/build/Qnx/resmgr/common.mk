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

INSTALLDIR=bin

define PINFO
PINFO DESCRIPTION=IPC Resource Manager
endef
NAME=ipc

CCOPTS += -DIPC_BUILDOS_QNX -DIPC_BUILD_DEBUG -DIPC_BUILD_HLOS $(QNX_CFLAGS)

ifeq ("$(IPC_DEBUG)", "1")
#enable debug build
CCOPTS += -g -O0
endif # ifeq ("$(IPC_DEBUG)", "1")

ifeq ("$(IPC_PLATFORM)", "omap5430")
ifeq ("$(SMP)", "1")
CCOPTS += -DIPC_SYSBIOS_SMP
endif # ifeq ("$(SMP)", "1")
CCOPTS += -DIPC_PLATFORM_OMAP5430 -DARM_TARGET -DC60_TARGET -DIPC_USE_IPU_PM
endif # ifeq ("$(IPC_PLATFORM)", "omap5430")

ifeq ("$(IPC_PLATFORM)", "vayu")
CCOPTS += -DIPC_PLATFORM_VAYU -DARM_TARGET -DC60_TARGET
endif # ifeq ("$(IPC_PLATFORM)", "vayu")

#IPC Product root path
IPC_ROOT = $(PROJECT_ROOT)/../../../../..
IPC_BUILDOS = Qnx

#PUBLIC_INCVPATH = $(PROJECT_ROOT)/public

EXTRA_INCVPATH = $(IPC_ROOT)	\
		  $(IPC_ROOT)/ti/syslink/inc	\
		  $(IPC_ROOT)/ti/syslink/inc/ti/ipc	\
		  $(IPC_ROOT)/ti/syslink/inc/knl	\
		  $(IPC_ROOT)/ti/syslink/inc/$(IPC_BUILDOS)	\
		  $(IPC_ROOT)/ti/syslink/inc/knl/$(IPC_BUILDOS) 	\
		  $(IPC_ROOT)/ti/syslink/ipc/hlos/knl/family/$(IPC_PLATFORM) 	\
		  $(IPC_PKGPATH)	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/rprc 	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/DLOAD_API	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/DLOAD	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/C60_DLOAD_DYN	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/C60_DLOAD_REL	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/TMS470_DLOAD_DYN	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/TMS470_DLOAD_REL	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/DLOAD_SYM	\
		  $(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/dlw_client	\
		  $(IPC_ROOT)/ti/syslink/rpmsg-resmgr/hlos/knl/$(IPC_BUILDOS)/family	\
		  $(IPC_ROOT)/ti/syslink/resources	\
                  $(IPC_ROOT)/ti/syslink/family/common \
		  $(IPC_REPO)/qnx/include \
                  $(IPC_REPO)/hlos_common/include \
		  $(IPC_REPO)/packages \

#devctl for ipc, procmgr, utils
EXTRA_SRCVPATH+=$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/rprc	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/DLOAD	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/TMS470_DLOAD_DYN	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/TMS470_DLOAD_REL	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/C60_DLOAD_REL	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/C60_DLOAD_DYN	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/DLOAD/DLOAD_SYM	\
		$(IPC_ROOT)/ti/syslink/procMgr/hlos/knl/loaders/Elf/$(IPC_BUILDOS)/dlw_client	\
		$(IPC_ROOT)/ti/syslink/resources	\
		$(IPC_ROOT)/ti/syslink/ipc/hlos/knl/transports/virtio	\
		$(IPC_ROOT)/ti/syslink/ipc/hlos/knl	\
		$(IPC_ROOT)/ti/syslink/ipc/hlos/knl/arch	\
		$(IPC_ROOT)/ti/syslink/ipc/hlos/knl/arch/$(IPC_PLATFORM)	\
		$(IPC_ROOT)/ti/syslink/ipc/hlos/knl/$(IPC_BUILDOS)	\
		$(IPC_ROOT)/ti/syslink/utils/common	\
		$(IPC_ROOT)/ti/syslink/utils/hlos	\
		$(IPC_ROOT)/ti/syslink/utils/hlos/knl	\
		$(IPC_ROOT)/ti/syslink/utils/hlos/knl/$(IPC_BUILDOS)	\
		$(IPC_ROOT)/ti/syslink/utils/hlos/knl/osal/$(IPC_BUILDOS)	\
		$(IPC_ROOT)/ti/syslink/rpmsg-omx/hlos/knl/$(IPC_BUILDOS)	\
		$(IPC_ROOT)/ti/syslink/rpmsg-dce/hlos/knl/$(IPC_BUILDOS)	\
		$(IPC_ROOT)/ti/syslink/ti-ipc	\
		$(IPC_ROOT)/ti/syslink/rpmsg-rpc	\
		$(IPC_ROOT)/ti/syslink/rpmsg-resmgr/hlos/knl/$(IPC_BUILDOS)/family/$(IPC_PLATFORM)	\
		$(IPC_ROOT)/ti/syslink/rpmsg-resmgr/hlos/knl/$(IPC_BUILDOS) \
                $(IPC_REPO)/qnx/src/cfg

ifeq ("$(IPC_PLATFORM)", "omap5430")
EXTRA_SRCVPATH+=$(IPC_ROOT)/ti/syslink/family/$(IPC_PLATFORM)	\
		$(IPC_ROOT)/ti/syslink/family/$(IPC_PLATFORM)/ipu \
                $(IPC_REPO)/qnx/src/cfg/$(IPC_PLATFORM)

EXCLUDE_OBJS = GateMP_daemon.o gatemp_devctl.o
endif

ifeq ("$(IPC_PLATFORM)", "vayu")
EXTRA_SRCVPATH+=$(IPC_ROOT)/ti/syslink/family/common	\
		$(IPC_ROOT)/ti/syslink/family/common/$(IPC_PLATFORM)/$(IPC_PLATFORM)dsp	\
		$(IPC_ROOT)/ti/syslink/family/common/$(IPC_PLATFORM)/$(IPC_PLATFORM)ipu	\
		$(IPC_ROOT)/ti/syslink/family/common/$(IPC_PLATFORM)/$(IPC_PLATFORM)ipu/$(IPC_PLATFORM)core0	\
		$(IPC_ROOT)/ti/syslink/family/$(IPC_PLATFORM)	\
		$(IPC_ROOT)/ti/syslink/family/$(IPC_PLATFORM)/$(IPC_PLATFORM)dsp	\
		$(IPC_ROOT)/ti/syslink/family/$(IPC_PLATFORM)/$(IPC_PLATFORM)ipu	\
                $(IPC_REPO)/qnx/src/api/gates \
                $(IPC_REPO)/qnx/src/cfg/dra7xx

EXCLUDE_OBJS = GateMP.o GateHWSpinlock_client.o
endif

include $(MKFILES_ROOT)/qtargets.mk

LDFLAGS += -M

EXTRA_LIBVPATH += $(INSTALL_ROOT_nto)/usr/lib

ifeq ("$(IPC_DEBUG)", "1")
EXTRA_LIBVPATH += $(IPC_REPO)/qnx/src/utils/arm/a.g.le.v7
LIBS += utils_g
else
EXTRA_LIBVPATH += $(IPC_REPO)/qnx/src/utils/arm/a.le.v7
LIBS += utils
endif # ifeq ("$(IPC_DEBUG)", "1")

# Quiet the build output
include $(IPC_REPO)/qnx/quiet.mk
