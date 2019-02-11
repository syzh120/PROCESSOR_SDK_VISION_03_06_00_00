/*
 * Copyright (c) 2014, Texas Instruments Incorporated
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
 * ======== socket.h ========
 * BSD compatible socket layer. BSD apps should typcially include this header.
 * We then proceed to bring in NDK headers for the user, to allow BSD code to
 * work "as is."
 */

#ifndef _BSD_SOCKET_H_
#define _BSD_SOCKET_H_

#include <stddef.h>

/* include NDK's socket API */
#include <ti/ndk/inc/bsd/socketndk.h>
#include <ti/ndk/inc/bsd/serrno.h>

/* fix for SDOCM00113145 */
#if defined (__TI_COMPILER_VERSION__) || defined (__IAR_SYSTEMS_ICC__)
typedef int ssize_t;
#else
/* include sys/types.h for GNU */
#include <sys/types.h>
#endif

#include <netinet/in.h>

typedef int socklen_t; /* see NOTES under man page for accept (man 2 accept) */
typedef unsigned short sa_family_t;

/*
 * define generic socket address struct (holds either IPv4 or IPv6 address)
 * Struct must be large enough to hold either sockaddr_in (size 16)
 * or sockaddr_in6 (size 28).  Therefore, make total struct size 32 bytes.
 */
struct sockaddr_storage {
    sa_family_t ss_family;
    char ss_data[30];
};

/* IPV6 Address in Network Format. */
typedef struct IP6N
{
    union
    {
        unsigned char addr8[16];
        unsigned short addr16[8];
        unsigned int addr32[4];
    }u;
}IP6N;

/*
 * To use the following macros & APIs, app must define _INCLUDE_IPv6_CODE
 * and set Global.IPv6 = true
 */
#ifdef _INCLUDE_IPv6_CODE
/* IPv6 unspecified address */
extern  IP6N  IPV6_UNSPECIFIED_ADDRESS;
#define in6addr_any (*(struct in6_addr *)&IPV6_UNSPECIFIED_ADDRESS)
#endif

/* IPv4 unspecified address */
#define INADDR_ANY 0x00000000     /* 0.0.0.0 */

/*
 * Select uses bit masks of file descriptors.  These macros
 * manipulate handle lists.
 *
 * For GCC, the below macros have differing definitions than what the NDK
 * originally set.  We want to ensure the origninal NDK values are used,
 * regardless of the compiler being used.  So for each of the conflicting
 * definitions, undefine it (if defined already) and then define it to be
 * the value expected by the NDK.
 */
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif
#define FD_SETSIZE NDK_FD_SETSIZE

/*
 * ======== FD_ZERO ========
 */
#ifdef FD_ZERO
#undef FD_ZERO
#endif
static inline void FD_ZERO(fd_set *set)
{
    NDK_FD_ZERO(set);
}

/*
 * ======== FD_CLR ========
 */
#ifdef FD_CLR
#undef FD_CLR
#endif
static inline void FD_CLR(int fd, fd_set *set)
{
    NDK_FD_CLR((SOCKET)fd, set);
}

/*
 * ======== FD_ISSET ========
 */
#ifdef FD_ISSET
#undef FD_ISSET
#endif
static inline int FD_ISSET(int fd, fd_set *set)
{
    return (NDK_FD_ISSET((SOCKET)fd, set));
}

/*
 * ======== FD_SET ========
 */
#ifdef FD_SET
#undef FD_SET
#endif
static inline void FD_SET(int fd, fd_set *set)
{
    NDK_FD_SET((SOCKET)fd, set);
}

/*
 * ======== accept ========
 */
static inline int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    return ((int)NDK_accept((SOCKET)sockfd, addr, addrlen));
}

/*
 * ======== bind ========
 */
static inline int bind(int sockfd, const struct sockaddr *my_addr,
        socklen_t addrlen)
{
    return NDK_bind((SOCKET)sockfd, (PSA)my_addr, addrlen);
}

/*
 * ======== connect ========
 */
static inline int connect(int sockfd, const struct sockaddr *serv_addr,
        socklen_t addrlen)
{
    return NDK_connect((SOCKET)sockfd, (PSA)serv_addr, addrlen);
}

/*
 * ======== getsockopt ========
 */
static inline int getsockopt(int sockfd, int level, int optname, void *optval,
        socklen_t *optlen)
{
    return NDK_getsockopt((SOCKET)sockfd, level, optname, optval, optlen);
}

/*
 * ======== listen ========
 */
static inline int listen(int sockfd, int backlog)
{
    return NDK_listen((SOCKET)sockfd, backlog);
}

/*
 * ======== recv ========
 */
static inline ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
    return NDK_recv((SOCKET)sockfd, buf, len, flags);
}

/*
 * ======== recvfrom ========
 */
static inline ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
        struct sockaddr *from, socklen_t *fromlen)
{
    return NDK_recvfrom((SOCKET)sockfd, buf, len, flags, (PSA)from, fromlen);
}

/*
 * ======== send ========
 */
static inline ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
    return NDK_send((SOCKET)sockfd, (void *)buf, len, flags);
}

/*
 * ======== sendto ========
 */
static inline ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
        const struct sockaddr *to, socklen_t tolen)
{
    return NDK_sendto((SOCKET)sockfd, (void *)buf, len, flags, (PSA)to, tolen);
}

/*
 * ======== setsockopt ========
 */
static inline int setsockopt(int sockfd, int level, int optname,
        const void *optval, socklen_t optlen)
{
    return NDK_setsockopt((SOCKET)sockfd, level, optname, (void *)optval,
            optlen);
}

/*
 * ======== socket ========
 */
static inline int socket(int domain, int type, int protocol)
{
    return ((int)(NDK_socket(domain, type, protocol)));
}

/*
 * ======== close ========
 */
static inline int close(int sockfd)
{
    return fdClose((SOCKET)sockfd);
}

/*
 * ======== select ========
 */
static inline int select(int nfds, fd_set *readfds, fd_set *writefds,
        fd_set *exceptfds, struct timeval *timeout)
{
    return fdSelect(nfds, readfds, writefds, exceptfds, timeout);
}

/*
 * ======== errno ========
 * Must use NDK's fdError to get error codes. BSD compatibility layer simply
 * calls NDK sockets APIs, so system's errno macro won't give us proper error
 * that's set by NDK.
 */
#ifdef errno
#undef errno
#endif
#define errno ((int)fdError())

#endif
