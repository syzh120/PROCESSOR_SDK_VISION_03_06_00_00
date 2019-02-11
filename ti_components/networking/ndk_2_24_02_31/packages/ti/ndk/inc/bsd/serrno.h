/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 * ======== serrno.h ========
 * NDK error return constants for socket operations.
 */

#ifndef _SERRNO_H_
#define _SERRNO_H_

/*
 * These values are straight from UNIX. Those that are commented
 * out are not used in this stack implementation.
 *
 * Regarding BSD Support:
 *
 * If user's app is including compiler's errno.h (i.e. getting error
 * definitions from compiler's errno.h), then use error macros defined there.
 * Otherwise, define them here and use fdError to get error codes.
 */

/*#define EPERM           1       // Operation not permitted */
/*#define ENOENT          2       // No such file or directory */
/*#define ESRCH           3       // No such process */

#ifndef EINTR
#define EINTR           4       // Interrupted system call
#endif

/*#define EIO             5       // Input/output error */

#ifndef ENXIO
#define ENXIO           6       /* Device not configured */
#endif

/*#define E2BIG           7       // Argument list too long */
/*#define ENOEXEC         8       // Exec format error */

#ifndef EBADF
#define EBADF           9       /* Bad file descriptor */
#endif

/*#define ECHILD          10      // No child processes */
/*#define EDEADLK         11      // Resource deadlock avoided */

#ifndef ENOMEM
#define ENOMEM          12      /* Cannot allocate memory */
#endif

#ifndef EACCES
#define EACCES          13      /* Permission denied */
#endif

/*#define EFAULT          14      // Bad address */
/*#define ENOTBLK         15      // Block device required */
/*#define EBUSY           16      // Device busy */
/*#define EEXIST          17      // File exists */
/*#define EXDEV           18      // Cross-device link */
/*#define ENODEV          19      // Operation not supported by device */
/*#define ENOTDIR         20      // Not a directory */
/*#define EISDIR          21      // Is a directory */

#ifndef EINVAL
#define EINVAL          22      /* Invalid argument */
#endif

/*#define ENFILE          23      // Too many open files in system */

#ifndef EMFILE
#define EMFILE          24      /* Too many open files */
#endif

/*#define ENOTTY          25      // Inappropriate ioctl for device */
/*#define ETXTBSY         26      // Text file busy */
/*#define EFBIG           27      // File too large */
/*#define ENOSPC          28      // No space left on device */
/*#define ESPIPE          29      // Illegal seek */
/*#define EROFS           30      // Read-only file system */
/*#define EMLINK          31      // Too many links */

#ifndef EPIPE
#define EPIPE           32      // Broken pipe
#endif

/* non-blocking and interrupt i/o */

#ifndef EWOULDBLOCK
#define EWOULDBLOCK     35      /* Operation would block */
#endif

#ifndef EAGAIN
#define EAGAIN          EWOULDBLOCK      /* Try again */
#endif

#ifndef EINPROGRESS
#define EINPROGRESS     36      /* Operation now in progress */
#endif

#ifndef EALREADY
#define EALREADY        37      /* Operation already in progress */
#endif

/* ipc/network software -- argument errors */
#ifndef ENOTSOCK
#define ENOTSOCK        38      /* Socket operation on non-socket */
#endif

/*#define EDESTADDRREQ    39      // Destination address required */

#ifndef EMSGSIZE
#define EMSGSIZE        40      /* Message too long */
#endif

#ifndef EPROTOTYPE
#define EPROTOTYPE      41      /* Protocol wrong type for socket */
#endif

#ifndef ENOPROTOOPT
#define ENOPROTOOPT     42      /* Protocol not available */
#endif

/*#define EPROTONOSUPPORT 43      // Protocol not supported */

#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT 44      /* Socket type not supported */
#endif

#ifndef EOPNOTSUPP
#define EOPNOTSUPP      45      /* Operation not supported */
#endif

#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT    46      /* Protocol family not supported */
#endif

/*#define EAFNOSUPPORT    47      // Address family not supported by protocol family */

#ifndef EADDRINUSE
#define EADDRINUSE      48      /* Address already in use */
#endif

#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL   49      /* Can't assign requested address */
#endif

/* ipc/network software -- operational errors */
/*#define ENETDOWN        50      // Network is down */
/*#define ENETUNREACH     51      // Network is unreachable */
/*#define ENETRESET       52      // Network dropped connection on reset */

#ifndef ECONNABORTED
#define ECONNABORTED    53      /* Software caused connection abort */
#endif

#ifndef ECONNRESET
#define ECONNRESET      54      /* Connection reset by peer */
#endif

#ifndef ENOBUFS
#define ENOBUFS         55      /* No buffer space available */
#endif

#ifndef EISCONN
#define EISCONN         56      /* Socket is already connected */
#endif

#ifndef ENOTCONN
#define ENOTCONN        57      /* Socket is not connected */
#endif

#ifndef ESHUTDOWN
#define ESHUTDOWN       58      /* Can't send after socket shutdown */
#endif

/*#define ETOOMANYREFS    59      // Too many references: can't splice */

#ifndef ETIMEDOUT
#define ETIMEDOUT       60      /* Operation timed out */
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED    61      /* Connection refused */
#endif

/*#define ELOOP           62      // Too many levels of symbolic links */
/*#define ENAMETOOLONG    63      // File name too long */

#ifndef EHOSTDOWN
#define EHOSTDOWN       64      /* Host is down */
#endif

#ifndef EHOSTUNREACH
#define EHOSTUNREACH    65      /* No route to host */
#endif

/* Error values for `getaddrinfo' function. */
#ifndef EAI_BADFLAGS
#define EAI_BADFLAGS    -1    /* Invalid value for `ai_flags' field. */
#endif

#ifndef EAI_NONAME
#define EAI_NONAME      -2    /* NAME or SERVICE is unknown. */
#endif

#ifndef EAI_AGAIN
#define EAI_AGAIN       -3    /* Temporary failure in name resolution. */
#endif

#ifndef EAI_FAIL
#define EAI_FAIL        -4    /* Non-recoverable failure in name res. */
#endif

#ifndef EAI_NODATA
#define EAI_NODATA      -5    /* No address associated with NAME. */
#endif

#ifndef EAI_FAMILY
#define EAI_FAMILY      -6    /* `ai_family' not supported. */
#endif

#ifndef EAI_SOCKTYPE
#define EAI_SOCKTYPE    -7    /* `ai_socktype' not supported. */
#endif

#ifndef EAI_SERVICE
#define EAI_SERVICE     -8    /* SERVICE not supported for `ai_socktype'. */
#endif

#ifndef EAI_ADDRFAMILY
#define EAI_ADDRFAMILY  -9    /* Address family for NAME not supported. */
#endif

#ifndef EAI_MEMORY
#define EAI_MEMORY      -10   /* Memory allocation failure. */
#endif

#ifndef EAI_SYSTEM
#define EAI_SYSTEM      -11   /* System error returned in `errno'. */
#endif

#ifndef EAI_OVERFLOW
#define EAI_OVERFLOW    -12   /* Argument buffer overflow. */
#endif

#endif
