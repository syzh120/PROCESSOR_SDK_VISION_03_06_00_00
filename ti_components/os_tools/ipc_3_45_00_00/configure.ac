#
#   Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
# ======== configure.ac ========
#

# Process this file with autoconf to produce a configure script.
AC_PREREQ(2.59)

# Initilize autoconf
AC_INIT(TI IPC, 3.0.0, )

# Check common src files to ensure integrity of the package
AC_CONFIG_SRCDIR([packages/ti/ipc/MessageQ.h])

# Set auxiliary build tools directory
AC_CONFIG_AUX_DIR([linux/build-aux])

# Initilize automake
AM_INIT_AUTOMAKE([foreign])

# Disabling maintainer mode to prevent rebuild of configure script
AM_MAINTAINER_MODE([disable])

# Initalize libtool but disable fortran check
LT_INIT
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
AC_PROG_LIBTOOL(gcc)

# Checks for programs.
AC_PROG_CC(gcc)
AC_PROG_INSTALL

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h])

# Export CFLAGS and LDFLAGS to Makefile(s)
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_LDFLAGS])

# Add config variables/options and check them
# Note that 6614 isn't documented and, though it may work, is planned for removal
AC_ARG_VAR(PLATFORM, Platform to build. Options are: 'OMAPL138' 'OMAP54XX' '66AK2E' 'TCI6630' 'TCI6636' 'TCI6638' '66AK2G' and 'DRA7XX'. If not defined all platforms will be built.)
AC_ARG_VAR(CMEM_INSTALL_DIR, Installation path directory to the CMEM libraries)
AC_ARG_VAR(KERNEL_INSTALL_DIR, Installation path to the Linux kernel.)
AC_ARG_VAR(AF_RPMSG, Address Family used by the RPMSG driver)
AC_ARG_VAR(DRM_PREFIX, Installation location to the DRM library.)

# Test platform variable for setting
AS_IF([test "x$PLATFORM" = "xOMAPL138"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "x66AK2E"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "xTCI6614"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "xTCI6630"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "xTCI6636"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "xTCI6638"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "x66AK2G"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "xOMAP54XX"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "xDRA7XX"],
  [AC_MSG_NOTICE([PLATFORM is set to ${PLATFORM}])],
  [AS_IF([test "x$PLATFORM" = "x"],
  [AC_MSG_NOTICE([PLATFORM is not set. All supported platforms will be built ....])],
  [AC_MSG_ERROR([PLATFORM is set to "${PLATFORM}": run ./configure --help for available PLATFORM options])])])])])])])])])])])

# If platform is specified, make sure at least one of
# KERNEL_INSTALL_DIR or AF_MSG are set.
AS_IF([test -n "$PLATFORM" -a -z "$KERNEL_INSTALL_DIR" -a -z "$AF_RPMSG"],
  [AC_MSG_ERROR([Must set at least one of KERNEL_INSTALL_DIR or AF_RPMSG])])

# Ignore KERNEL path when no platform is set
AS_IF([test "x$PLATFORM" = "x"], [KERNEL_INSTALL_DIR=])
AS_IF([test "x$PLATFORM" = "x"], [DRM_PREFIX=])
AS_IF([test "x$PLATFORM" = "x"], [CMEM_INSTALL_DIR=])

# Export optional user variable to Makefile(s)
AC_SUBST([PLATFORM])
AC_SUBST([CMEM_INSTALL_DIR])
AC_SUBST([KERNEL_INSTALL_DIR])
AC_SUBST([AF_RPMSG])
AC_SUBST([DRM_PREFIX])

# Define specific variables to be used in Makefile.am
AM_CONDITIONAL([OMAPL138], [test "x$PLATFORM" = "xOMAPL138"])
AM_CONDITIONAL([C66AK2E],  [test "x$PLATFORM" = "x66AK2E"])
AM_CONDITIONAL([TCI6614], [test "x$PLATFORM" = "xTCI6614"])
AM_CONDITIONAL([TCI6630], [test "x$PLATFORM" = "xTCI6630"])
AM_CONDITIONAL([TCI6636], [test "x$PLATFORM" = "xTCI6636"])
AM_CONDITIONAL([TCI6638], [test "x$PLATFORM" = "xTCI6638"])
AM_CONDITIONAL([C66AK2G], [test "x$PLATFORM" = "x66AK2G"])
AM_CONDITIONAL([OMAP54XX_SMP], [test "x$PLATFORM" = "xOMAP54XX"])
AM_CONDITIONAL([DRA7XX], [test "x$PLATFORM" = "xDRA7XX"])
AM_CONDITIONAL([CMEM], [test "x$CMEM_INSTALL_DIR" != "x"])
AM_CONDITIONAL([KDIR], [test "x$KERNEL_INSTALL_DIR" != "x"])
AM_CONDITIONAL([KERNEL_INSTALL_DIR], [test -n "$KERNEL_INSTALL_DIR"])
AM_CONDITIONAL([DRM], [test "x$DRM_PREFIX" != "x"])
AM_CONDITIONAL([AF_RPMSG], [test -n "$AF_RPMSG"])

# Generate Makefile(s)
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([linux/etc/Makefile])
AC_CONFIG_FILES([linux/src/utils/Makefile])
AC_CONFIG_FILES([linux/src/utils/libtiipcutils.pc])
AC_CONFIG_FILES([linux/src/api/Makefile])
AC_CONFIG_FILES([linux/src/api/libtiipc.pc])
AC_CONFIG_FILES([linux/src/mm/Makefile])
AC_CONFIG_FILES([linux/src/mm/libmmrpc.pc])
AC_CONFIG_FILES([linux/src/daemon/Makefile])
AC_CONFIG_FILES([linux/src/tests/Makefile])
AC_CONFIG_FILES([linux/src/transport/Makefile])
AC_OUTPUT

echo \
"-----------------------------------------------------------

Thank you for installing the Linux ${PACKAGE_NAME} package

Installation directory prefix: '${prefix}'.
Compilation command: '${CC} ${CFLAGS} ${CPPFLAGS}'

You have configured to build for the '${PLATFORM}' platform

Your KERNEL installation directory is set to:
    '${KERNEL_INSTALL_DIR}'

Your DRM installation directory is set to:
    '${DRM_PREFIX}'

Your CMEM installation directory is set to:
    '${CMEM_INSTALL_DIR}'

Now type 'make; sudo make install' to generate the program
and install it to your system.

------------------------------------------------------------"
