##
##  Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
##
##  Redistribution and use in source and binary forms, with or without
##  modification, are permitted provided that the following conditions
##  are met:
##
##  *  Redistributions of source code must retain the above copyright
##     notice, this list of conditions and the following disclaimer.
##
##  *  Redistributions in binary form must reproduce the above copyright
##     notice, this list of conditions and the following disclaimer in the
##     documentation and/or other materials provided with the distribution.
##
##  *  Neither the name of Texas Instruments Incorporated nor the names of
##     its contributors may be used to endorse or promote products derived
##     from this software without specific prior written permission.
##
##  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
##  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
##  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
##  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
##  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
##  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
##  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
##  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
##  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
##  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
##  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
## ======== src/api/Makefile.am ========
##

# additional include paths necessary to compile the library
AM_CFLAGS = -I$(top_srcdir)/hlos_common/include -D_GNU_SOURCE -Wall

if DRA7XX
AM_CFLAGS += -DGATEMP_SUPPORT
endif

if KERNEL_INSTALL_DIR
AM_CFLAGS += -I$(KERNEL_INSTALL_DIR)/include/generated/uapi
endif

AM_CFLAGS += -I$(top_srcdir)/linux/include -I$(top_srcdir)/packages @AM_CFLAGS@

###############################################################################
# THE LIBRARIES TO BUILD
###############################################################################

# the library names to build (note we are building shared libs)
lib_LTLIBRARIES = libtiipc.la

# where to install the headers on the system
libtiipc_ladir = $(includedir)/ti/ipc

# the list of header files that belong to the library (to be installed later)
libtiipc_la_HEADERS = $(top_srcdir)/linux/include/ti/ipc/Std.h

# the sources to add to the library and to add to the source distribution
libtiipc_la_SOURCES =    \
                        $(libtiipc_la_HEADERS) \
                        $(top_srcdir)/linux/include/_MultiProc.h \
                        $(top_srcdir)/hlos_common/include/_MessageQ.h \
                        $(top_srcdir)/hlos_common/include/_NameServer.h \
                        $(top_srcdir)/linux/include/ladclient.h \
                        $(top_srcdir)/linux/include/_lad.h \
                        $(top_srcdir)/linux/include/SocketFxns.h \
                        $(top_srcdir)/linux/include/net/rpmsg.h \
                        $(top_srcdir)/packages/ti/ipc/Ipc.h \
                        $(top_srcdir)/packages/ti/ipc/NameServer.h \
                        $(top_srcdir)/packages/ti/ipc/MultiProc.h \
                        $(top_srcdir)/packages/ti/ipc/MessageQ.h \
                        $(top_srcdir)/linux/include/ti/ipc/Std.h \
                        MessageQ.c \
                        MultiProc.c \
                        NameServer.c \
                        Ipc.c \
                        $(top_srcdir)/linux/include/ti/ipc/heaps/HeapStd.h \
                        $(top_srcdir)/linux/src/heaps/HeapStd.c

if DRA7XX
libtiipc_la_SOURCES +=  $(top_srcdir)/linux/include/IGateProvider.h \
                        $(top_srcdir)/linux/include/GateHWSpinlock.h \
                        $(top_srcdir)/linux/include/GateMutex.h \
                        $(top_srcdir)/linux/include/GateMP_config.h \
                        $(top_srcdir)/linux/include/_GateMP.h \
                        $(top_srcdir)/packages/ti/ipc/GateMP.h \
                        $(top_srcdir)/linux/src/api/gates/GateMP.c \
                        $(top_srcdir)/linux/src/api/gates/GateMutex.c \
                        $(top_srcdir)/linux/src/api/gates/GateHWSpinlock.c
endif

# Add version info to the shared library
libtiipc_la_LDFLAGS = -version-info 1:0:0

pkgconfig_DATA          = libtiipc.pc
pkgconfigdir            = $(libdir)/pkgconfig

###############################################################################
