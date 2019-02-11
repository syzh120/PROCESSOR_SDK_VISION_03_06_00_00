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
## ======== src/test/Makefile.am ========
##

# additional include paths necessary to compile the program
AM_CFLAGS = -I$(top_srcdir)/hlos_common/include -D_GNU_SOURCE -Wall -pthread

if DRM
AM_CFLAGS += \
        -I$(DRM_PREFIX)/usr/include \
        -I$(DRM_PREFIX)/usr/include/libdrm \
        -I$(DRM_PREFIX)/usr/include/omap
endif

if CMEM
AM_CFLAGS += -I$(CMEM_INSTALL_DIR)/include
endif

if KERNEL_INSTALL_DIR
AM_CFLAGS += -I$(KERNEL_INSTALL_DIR)/include/generated/uapi
endif

if AF_RPMSG
AM_CFLAGS += -DAF_RPMSG=$(AF_RPMSG)
endif

AM_CFLAGS += -I$(top_srcdir)/linux/include -I$(top_srcdir)/packages @AM_CFLAGS@

VPATH = ../../../packages/ti/ipc/tests

###############################################################################
# THE PROGRAMS TO BUILD
###############################################################################

# the program to build (the names of the final binaries)
bin_PROGRAMS = ping_rpmsg MessageQApp  MessageQBench MessageQMulti \
                MessageQMultiMulti NameServerApp Msgq100 fault


if OMAP54XX_SMP
# Add platform specific bin application's here
  bin_PROGRAMS +=
if KDIR
if DRM
  bin_PROGRAMS += mmrpc_test
endif
endif
else
if DRA7XX
# Add platform specific bin application's here
  bin_PROGRAMS +=
if CMEM
  bin_PROGRAMS += GateMPApp
endif
if KDIR
if DRM
  bin_PROGRAMS += mmrpc_test
endif
endif
else
if OMAPL138
# Add platform specific bin application's here
  bin_PROGRAMS +=
if CMEM
  bin_PROGRAMS += nano_test
endif
else
if C66AK2E
# Add platform specific bin application's here
  bin_PROGRAMS +=
else
if TCI6614
# Add platform specific bin application's here
  bin_PROGRAMS +=
else
if TCI6630
# Add platform specific bin applications here
  bin_PROGRAMS +=
else
if TCI6636
# Add platform specific bin application's here
  bin_PROGRAMS +=
else
if TCI6638
# Add platform specific bin application's here
  bin_PROGRAMS +=
else
if C66AK2G
# Add platform specific bin application's here
  bin_PROGRAMS +=
else
# Add platform independent apps here or above in bin_PROGRAMS
if CMEM
  bin_PROGRAMS += nano_test
endif
if KDIR
if DRM
  bin_PROGRAMS += mmrpc_test
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif

common_sources = \
                $(top_srcdir)/linux/include/ti/ipc/Std.h \
                $(top_srcdir)/packages/ti/ipc/Ipc.h \
                $(top_srcdir)/packages/ti/ipc/MessageQ.h

nameServer_common_sources = \
                $(top_srcdir)/linux/include/ti/ipc/Std.h \
                $(top_srcdir)/linux/include/ladclient.h \
                $(top_srcdir)/hlos_common/include/_NameServer.h \
                $(top_srcdir)/packages/ti/ipc/NameServer.h \
                NameServerApp.c


# list of sources for the 'ping_rpmsg' binary
ping_rpmsg_SOURCES = ping_rpmsg.c

# list of sources for the 'mmrpc_test' binary
mmrpc_test_SOURCES = $(top_srcdir)/packages/ti/ipc/tests/Mx.c \
                $(top_srcdir)/packages/ti/ipc/tests/Mx.h \
                $(top_srcdir)/packages/ti/ipc/tests/mmrpc_test.c

# list of sources for the 'fault' binary
fault_SOURCES = $(common_sources) fault.c

# list of sources for the 'MessageQApp' binary
MessageQApp_SOURCES = $(common_sources) MessageQApp.c

# list of sources for the 'MessageQBench' binary
MessageQBench_SOURCES = $(common_sources) MessageQBench.c

# list of sources for the 'MessageQMulti' binary
MessageQMulti_SOURCES = $(common_sources) MessageQMulti.c

# list of sources for the 'MessageQMultiMulti' binary
MessageQMultiMulti_SOURCES = $(common_sources) MessageQMultiMulti.c

# list of sources for the 'NameServerApp' binary
NameServerApp_SOURCES = $(nameServer_common_sources)

# list of sources for the 'nano_test' binary
nano_test_SOURCES = $(common_sources) nano_test.c

# list of sources for the 'Msgq100' binary
Msgq100_SOURCES = $(common_sources) Msgq100.c

# list of sources for the 'GateMPApp' binary
GateMPApp_SOURCES = $(common_sources) \
                $(top_srcdir)/linux/src/tests/main_host.c \
                $(top_srcdir)/linux/src/tests/GateMPApp.c \
                $(top_srcdir)/linux/src/tests/GateMPApp.h \
                $(top_srcdir)/packages/ti/ipc/GateMP.h \
                $(top_srcdir)/packages/ti/ipc/tests/GateMPAppCommon.h

common_libraries = -lpthread $(top_builddir)/linux/src/api/libtiipc.la \
                $(top_builddir)/linux/src/utils/libtiipcutils.la \
                $(top_builddir)/linux/src/transport/libtitransportrpmsg.la


# the additional libraries to link ping_rpmsg
ping_rpmsg_LDADD = -lrt

# the additional libraries to link mmrpc_test
mmrpc_test_LDADD = $(common_libraries) \
                $(top_builddir)/linux/src/mm/libmmrpc.la \
                $(DRM_PREFIX)/usr/lib/libdrm.la \
                $(DRM_PREFIX)/usr/lib/libdrm_omap.la

# the additional libraries needed to link fault
fault_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

# the additional libraries needed to link MessageQApp
MessageQApp_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

# the additional libraries needed to link MessageQBench
MessageQBench_LDADD = $(common_libraries) -lrt \
                $(AM_LDFLAGS)

# the additional libraries needed to link MessageQMulti
MessageQMulti_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

# the additional libraries needed to link MessageQMultiMulti
MessageQMultiMulti_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

# the additional libraries needed to link NameServerApp
NameServerApp_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

# the additional libraries needed to link nano_test
nano_test_LDADD = $(common_libraries) \
                $(CMEM_INSTALL_DIR)/src/cmem/api/.libs/libticmem.a \
                $(AM_LDFLAGS)

# the additional libraries needed to link Msgq100
Msgq100_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

# the additional libraries needed to link GateMPApp
GateMPApp_LDADD = $(common_libraries) \
                $(CMEM_INSTALL_DIR)/src/cmem/api/.libs/libticmem.a \
                $(AM_LDFLAGS)

###############################################################################
