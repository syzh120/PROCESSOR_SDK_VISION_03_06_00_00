#
#   Copyright (c) 2015, Texas Instruments Incorporated
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

LOCAL_PATH:= $(call my-dir)

############### libtiipc ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages \
                     $(LOCAL_PATH)/hlos_common/include

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID -DGATEMP_SUPPORT -fPIC
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/api/MultiProc.c \
                  linux/src/api/NameServer.c \
                  linux/src/api/Ipc.c \
                  linux/src/api/MessageQ.c \
                  linux/src/api/gates/GateMP.c \
                  linux/src/api/gates/GateMutex.c \
                  linux/src/api/gates/GateHWSpinlock.c \
                  linux/src/heaps/HeapStd.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils

LOCAL_MODULE:= libtiipc
include $(BUILD_SHARED_LIBRARY)


############### libtiipcutils ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages \
                     $(LOCAL_PATH)/hlos_common/include

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/utils/LAD_client.c \
                  linux/src/utils/SocketFxns.c \
                  linux/src/utils/MultiProc_app.c \
                  hlos_common/src/utils/MultiProc.c

LOCAL_SHARED_LIBRARIES := \
    liblog

LOCAL_MODULE:= libtiipcutils
include $(BUILD_SHARED_LIBRARY)


############### libtiipcutils_lad ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages \
                     $(LOCAL_PATH)/hlos_common/include

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/utils/LAD_client.c \
                  linux/src/utils/SocketFxns.c \
                  hlos_common/src/utils/MultiProc.c

LOCAL_SHARED_LIBRARIES := \
    liblog

LOCAL_ALLOW_UNDEFINED_SYMBOLS:= true

LOCAL_MODULE:= libtiipcutils_lad
include $(BUILD_SHARED_LIBRARY)


############### libtitransportrpmsg ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages \
                     $(LOCAL_PATH)/hlos_common/include

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/transport/TransportRpmsg.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils libtiipc

LOCAL_MODULE:= libtitransportrpmsg
include $(BUILD_SHARED_LIBRARY)


############### libmmrpc ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES += $(LOCAL_PATH) \
                    $(LOCAL_PATH)/packages

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= packages/ti/ipc/mm/MmRpc.c

LOCAL_SHARED_LIBRARIES := \
    liblog

LOCAL_MODULE:= libmmrpc
include $(BUILD_SHARED_LIBRARY)


############### lad_dra7xx ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages \
                     $(LOCAL_PATH)/hlos_common/include

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID -DGATEMP_SUPPORT -DDAEMON=0
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/daemon/lad.c \
                  linux/src/daemon/Ipc_daemon.c \
                  linux/src/daemon/MessageQ_daemon.c \
                  linux/src/daemon/MultiProc_daemon.c \
                  linux/src/daemon/NameServer_daemon.c \
                  linux/src/daemon/cfg/MultiProcCfg_dra7xx.c \
                  linux/src/daemon/GateMP_daemon.c \
                  linux/src/daemon/GateHWSpinlock.c \
                  linux/src/daemon/GateHWSpinlock_daemon.c \
                  linux/src/daemon/cfg/GateHWSpinlockCfg_dra7xx.c \
                  linux/src/daemon/cfg/IpcCfg.c \
                  linux/src/daemon/cfg/MessageQCfg.c \
                  linux/src/api/gates/GateMutex.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils_lad

LOCAL_MODULE:= lad_dra7xx
include $(BUILD_EXECUTABLE)


############### MessageQApp ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/tests/MessageQApp.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils libtiipc libtitransportrpmsg

LOCAL_MODULE:= messageQApp
include $(BUILD_EXECUTABLE)


############### MessageQBench ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/tests/MessageQBench.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils libtiipc libtitransportrpmsg

LOCAL_MODULE:= messageQBench
include $(BUILD_EXECUTABLE)


############### MessageQMulti ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/tests/MessageQMulti.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils libtiipc libtitransportrpmsg

LOCAL_MODULE:= messageQMulti
include $(BUILD_EXECUTABLE)


############# NameServerApp ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/hlos_common/include \
                     $(LOCAL_PATH)/packages

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/tests/NameServerApp.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils libtiipc libtitransportrpmsg

LOCAL_MODULE:= nameServerApp
include $(BUILD_EXECUTABLE)


############### ping_rpmsg ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/tests/ping_rpmsg.c

LOCAL_SHARED_LIBRARIES := \
    liblog

LOCAL_MODULE:= ping_rpmsg
include $(BUILD_EXECUTABLE)


############### MessageQFaultApp ###############
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=  $(LOCAL_PATH)/linux/include \
                     $(LOCAL_PATH)/packages

LOCAL_CFLAGS += -DIPC_BUILDOS_ANDROID
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= linux/src/tests/fault.c

LOCAL_SHARED_LIBRARIES := \
    liblog libtiipcutils libtiipc libtitransportrpmsg

LOCAL_MODULE:= messageQFaultApp
include $(BUILD_EXECUTABLE)
