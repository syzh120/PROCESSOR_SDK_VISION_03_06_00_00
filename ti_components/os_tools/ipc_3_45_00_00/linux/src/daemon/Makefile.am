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
## ======== src/daemon/Makefile.am ========
##

# additional include paths necessary to compile the program
AM_CFLAGS = -I$(top_srcdir)/hlos_common/include -D_GNU_SOURCE -Wall -pthread \
        -DKERNEL_INSTALL_DIR="$(KERNEL_INSTALL_DIR)"

if DRA7XX
AM_CFLAGS += -DGATEMP_SUPPORT
endif

if KERNEL_INSTALL_DIR
AM_CFLAGS += -I$(KERNEL_INSTALL_DIR)/include/generated/uapi
endif

if AF_RPMSG
AM_CFLAGS += -DAF_RPMSG=$(AF_RPMSG)
endif

AM_CFLAGS += -I$(top_srcdir)/linux/include -I$(top_srcdir)/packages @AM_CFLAGS@

###############################################################################
# THE PROGRAMS TO BUILD
###############################################################################

# the program to build (the names of the final binaries)
bin_PROGRAMS =

if OMAP54XX_SMP
  bin_PROGRAMS += lad_omap54xx_smp
else
if DRA7XX
  bin_PROGRAMS += lad_dra7xx
else
if OMAPL138
  bin_PROGRAMS += lad_omapl138
else
if C66AK2E
  bin_PROGRAMS += lad_66ak2e
else
if TCI6614
  bin_PROGRAMS += lad_tci6614
else
if TCI6630
  bin_PROGRAMS += lad_tci6630
else
if TCI6636
  bin_PROGRAMS += lad_tci6636
else
if TCI6638
  bin_PROGRAMS += lad_tci6638
else
if C66AK2G
  bin_PROGRAMS += lad_66ak2g
else
  bin_PROGRAMS += lad_omap54xx_smp lad_dra7xx lad_omapl138 lad_66ak2e lad_tci6614 lad_tci6630 lad_tci6636 lad_tci6638 lad_66ak2g
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
                lad.c \
                Ipc_daemon.c \
                cfg/IpcCfg.c \
                MessageQ_daemon.c \
                cfg/MessageQCfg.c \
                MultiProc_daemon.c \
                NameServer_daemon.c \
                $(top_srcdir)/linux/include/ti/ipc/Std.h \
                $(top_srcdir)/hlos_common/include/_NameServerRemoteRpmsg.h \
                $(top_srcdir)/hlos_common/include/_MessageQ.h \
                $(top_srcdir)/hlos_common/include/_NameServer.h \
                $(top_srcdir)/linux/include/_Ipc.h \
                $(top_srcdir)/linux/include/_MultiProc.h \
                $(top_srcdir)/linux/include/_lad.h \
                $(top_srcdir)/linux/include/SocketFxns.h \
                $(top_srcdir)/linux/include/ladclient.h \
                $(top_srcdir)/linux/include/net/rpmsg.h \
                $(top_srcdir)/packages/ti/ipc/MessageQ.h \
                $(top_srcdir)/packages/ti/ipc/NameServer.h \
                $(top_srcdir)/packages/ti/ipc/MultiProc.h

if DRA7XX
common_sources += \
                GateMP_daemon.c \
		GateHWSpinlock.c \
		GateHWSpinlock_daemon.c \
		cfg/GateHWSpinlockCfg_dra7xx.c \
		$(top_srcdir)/linux/src/api/gates/GateMutex.c \
		$(top_srcdir)/linux/include/_GateMP.h \
                $(top_srcdir)/linux/include/_GateMP_daemon.h \
                $(top_srcdir)/linux/include/IGateProvider.h \
                $(top_srcdir)/linux/include/GateHWSpinlock.h \
                $(top_srcdir)/linux/include/GateMutex.h \
                $(top_srcdir)/linux/include/GateMP_config.h \
                $(top_srcdir)/packages/ti/ipc/GateMP.h
endif

# list of sources for the 'lad' binary and to add to the source distribution
#
# NOTE:  6636_SOURCES using 6638.c is not a typo!  6636 has the same
# MultiProc config as 6638, so we reuse that source file.
lad_omap54xx_smp_SOURCES = $(common_sources) cfg/MultiProcCfg_omap54xx_smp.c
lad_dra7xx_SOURCES = $(common_sources) cfg/MultiProcCfg_dra7xx.c
lad_omapl138_SOURCES = $(common_sources) cfg/MultiProcCfg_omapl138.c
lad_66ak2e_SOURCES = $(common_sources) cfg/MultiProcCfg_66ak2e.c
lad_tci6614_SOURCES = $(common_sources) cfg/MultiProcCfg_tci6614.c
lad_tci6630_SOURCES = $(common_sources) cfg/MultiProcCfg_tci6630.c
lad_tci6636_SOURCES = $(common_sources) cfg/MultiProcCfg_tci6638.c
lad_tci6638_SOURCES = $(common_sources) cfg/MultiProcCfg_tci6638.c
lad_66ak2g_SOURCES = $(common_sources) cfg/MultiProcCfg_66ak2g.c

common_libraries = -lpthread \
                $(top_builddir)/linux/src/utils/libtiipcutils_lad.la

# the additional libraries needed to link program
lad_omap54xx_smp_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_dra7xx_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_omapl138_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_66ak2e_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_tci6614_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_tci6630_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_tci6636_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_tci6638_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)
lad_66ak2g_LDADD = $(common_libraries) \
                $(AM_LDFLAGS)

###############################################################################
