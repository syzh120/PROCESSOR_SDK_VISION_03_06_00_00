/*
 *  ======== sockets.h ========
 *
 *  Simple (incomplete) compatibility header file to make it easier to
 *  write portable sockets-based C programs for Linux and Windows.
 *  This is meant to be just good enough for the simple NDK examples.
 */
#ifndef _SOCKETS_H_
#define _SOCKETS_H_

#if defined(__GNUC__) && defined(linux)

#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>

typedef int SOCKET;

#define closesocket(s) close(s)

/* these are not needed for Linux */
#define socketsShutdown()
#define socketsStartup()

#define kbhit() 0

#define getError() (errno)

#elif defined(__MINGW32__) || defined(_MSC_VER)

#if defined(__MINGW32__)
#define _WIN32_WINNT 0x0601
#endif

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <iphlpapi.h>

#define getError() WSAGetLastError()

#define socketsShutdown() WSACleanup()

#else

#error "Unrecognized compiler"

#endif

#endif /* _SOCKETS_H_ */
