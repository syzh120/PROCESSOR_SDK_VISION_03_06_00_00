#
#   Copyright (c) 2012-2015, Texas Instruments Incorporated
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
#  ======== ipc-qnx.mak ========
#

include ./products.mak

# Setup QNX paths
ifneq ($(wildcard $(QNX_INSTALL_DIR)),)
    QNX_PATH := $(QNX_INSTALL_DIR)/host/linux/x86/usr/bin
    QNX_PATH := $(QNX_PATH):$(QNX_INSTALL_DIR)/.qnx/bin
    QNX_PATH := $(QNX_PATH):$(QNX_INSTALL_DIR)/jre/bin

    export QNX_CONFIGURATION?=$(QNX_INSTALL_DIR)/.qnx
    export QNX_HOST?=$(QNX_INSTALL_DIR)/host/linux/x86
    export QNX_TARGET?=$(QNX_INSTALL_DIR)/target/qnx6
    export MAKEFLAGS=-I$(QNX_INSTALL_DIR)/target/qnx6/usr/include
    export LD_LIBRARY_PATH=$(QNX_INSTALL_DIR)/host/linux/x86/usr/lib
endif

all: .qnx

.qnx: .qnx,$(PLATFORM)

.qnx,%: PATH:=$(QNX_PATH):$(PATH)
.qnx,%:
	@echo "building Qnx user libraries for \"$(PLATFORM)\" platform..."
ifneq ("$(QNX_CFLAGS)","")
	@make -C qnx \
                IPC_REPO=`pwd` \
                PLATFORM=$(PLATFORM) \
                QNX_CFLAGS=$(QNX_CFLAGS)
else
	@make -C qnx \
                IPC_REPO=`pwd` \
                PLATFORM=$(PLATFORM)
endif

clean:
	@echo "cleaning Qnx user libraries ..."
	@make -C qnx PLATFORM=$(PLATFORM) IPC_REPO=`pwd` clean

install: .install,$(PLATFORM)

.install,%: PATH:=$(QNX_PATH):$(PATH)
.install,%:
	@echo installing binaries to $(DESTDIR) ...
	@mkdir -p $(DESTDIR)
	@make -C qnx \
                IPC_REPO=`pwd` \
                PLATFORM=$(PLATFORM) \
		DESTDIR=$(DESTDIR) \
		install
