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
## ======== src/utils/Makefile.am ========
##

# additional include paths necessary to compile the library
AM_CFLAGS = -I$(top_srcdir)/hlos_common/include -D_GNU_SOURCE -Wall

if KERNEL_INSTALL_DIR
AM_CFLAGS += -I$(KERNEL_INSTALL_DIR)/include/generated/uapi
endif

if AF_RPMSG
AM_CFLAGS += -DAF_RPMSG=$(AF_RPMSG)
endif

AM_CFLAGS += -I$(top_srcdir)/linux/include -I$(top_srcdir)/packages @AM_CFLAGS@

###############################################################################
# THE LIBRARIES TO BUILD
###############################################################################

# the library names to build (note we are building shared libs)
lib_LTLIBRARIES = libtiipcutils.la libtiipcutils_lad.la

# where to install the headers on the system
libtiipcutils_ladir = $(includedir)
libtiipcutils_lad_ladir = $(includedir)

# the list of header files that belong to the library (to be installed later)
libtiipcutils_la_HEADERS =
libtiipcutils_lad_la_HEADERS =

# the sources to add to the library and to add to the source distribution
libtiipcutils_la_SOURCES =    \
                        $(libtiipcutils_la_HEADERS) \
                        $(top_srcdir)/linux/include/ladclient.h \
                        $(top_srcdir)/linux/include/_lad.h \
                        $(top_srcdir)/linux/include/_MultiProc.h \
                        $(top_srcdir)/linux/include/net/rpmsg.h \
                        $(top_srcdir)/linux/include/ti/ipc/Std.h \
                        $(top_srcdir)/packages/ti/ipc/MultiProc.h \
                        LAD_client.c \
                        $(top_srcdir)/hlos_common/src/utils/MultiProc.c \
                        MultiProc_app.c \
                        SocketFxns.c

libtiipcutils_lad_la_SOURCES =    \
                        $(libtiipcutils_la_HEADERS) \
                        $(top_srcdir)/linux/include/ladclient.h \
                        $(top_srcdir)/linux/include/_lad.h \
                        $(top_srcdir)/linux/include/_MultiProc.h \
                        $(top_srcdir)/linux/include/net/rpmsg.h \
                        $(top_srcdir)/linux/include/ti/ipc/Std.h \
                        $(top_srcdir)/packages/ti/ipc/MultiProc.h \
                        LAD_client.c \
                        $(top_srcdir)/hlos_common/src/utils/MultiProc.c \
                        SocketFxns.c


# Add version info to the shared library
libtiipcutils_la_LDFLAGS = -version-info 1:0:0
libtiipcutils_lad_la_LDFLAGS = -version-info 1:0:0

pkgconfig_DATA          = libtiipcutils.pc
pkgconfigdir            = $(libdir)/pkgconfig

###############################################################################
