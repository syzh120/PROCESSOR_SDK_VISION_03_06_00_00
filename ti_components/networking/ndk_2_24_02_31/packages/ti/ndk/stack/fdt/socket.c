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
 * ======== socket.c ========
 *
 * This file handles core BSD style socket calls and pipes.
 *
 */
#include <stkmain.h>
#include "fdt.h"

/**********************************************************************
 ************************* Socket Handling Functions ******************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      This function extracts the first pending connection request
 *      in the socket queue and spawns a new socket to accept the
 *      incoming connection request. This function call is valid only 
 *      for connection-oriented socket types like TCP. 
 *
 *  @param[in]  s
 *      Handle to local bound socket that is waiting/listening on
 *      any incoming connections. The argument s is a socket that
 *      has been created using "socket" function call, bound to a 
 *      local address using "bind" and listening for connections
 *      with "listen" function calls.
 *
 *  @param[in]  pName
 *     Handle to the sockaddr structure that holds the peer host's
 *     address and port information. 
 *
 *  @param[in]  plen
 *     Holds the length of the sockaddr structure being passed as 
 *     argument to this function.
 *
 *  @param[out]  pName
 *     Handle to the sockaddr structure that holds the connected peer's
 *     address and port information. The exact format of this is
 *     based on the address family. Valid only when this function returns
 *     success.
 *
 *  @param[out]  plen
 *     Holds the length of the connected peer's sockaddr structure.
 *     The exact length depends on the address family of the socket
 *     created. Valid only when the function returns success.
 *
 *  @retval
 *      Success -   Handle to the new socket created
 *  @retval
 *      Error   -   INVALID_SOCKET
 *      
 */
SOCKET NDK_accept( SOCKET s, PSA pName, int *plen )
{
    FILEDESC *pfd = (FILEDESC *)s;
    FILEDESC *pfdnew;
    int      error = 0;

    llEnter();

    /* Validate Input */

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return INVALID_SOCKET;
    }

    /* If there's a name, there must be a valid length */
    if (pName && (!plen || (pName->sa_family == AF_INET && *plen < sizeof(SA_IN)) 
#ifdef _INCLUDE_IPv6_CODE      
        || (pName->sa_family == AF_INET6 && *plen < sizeof(SA_IN6))
#endif
       ))
    {
        error = EINVAL;
        goto accept_error;
    }

    /* Accept the new socket */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if (error = Sock6Accept(pfd, (HANDLE *)&pfdnew))
            goto accept_error;
    }
    else
#endif
    {    
        if (error = SockAccept(pfd, (HANDLE *)&pfdnew))
            goto accept_error;
    }

    /* Get the connected address */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if (pName)
            Sock6GetName(pfdnew, 0, pName);
        if (plen)
            *plen = sizeof(SA_IN6);
    }
    else
#endif
    {
        if (pName)
            SockGetName(pfdnew, 0, pName);
        if (plen)
            *plen = sizeof(SA_IN);
    }

    /* Success. Unlock the fd without error */
    fdint_unlockfd(pfd, 0);

    llExit();

    /* Return the file descriptor table index */
    return (pfdnew);

accept_error:    
    /* Accept failed. cleanup and return error */

    /* Unlock the fd with error */
    fdint_unlockfd (pfd, error);

    llExit();

    return (INVALID_SOCKET);
}

/** 
 *  @b Description
 *  @n  
 *      This function assigns a name to an unnamed socket. When a 
 *      socket is created using "socket()" call, it exists in a 
 *      name space (address family) but has no name assigned. The
 *      bind() function requests that name be assigned to the socket.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pName
 *     Handle to the sockaddr structure that holds the local 
 *     address and port information that needs to be assigned to the
 *     socket.
 *
 *  @param[in]  len
 *     Holds the length of the sockaddr structure being passed as 
 *     argument to this function. This in turn depends on the
 *     address family of the socket.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_bind( SOCKET s, PSA pName, int len )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Validate Input */

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Verify Address Size */
    if ((pName->sa_family == AF_INET && len != sizeof(SA_IN))
#ifdef _INCLUDE_IPv6_CODE      
       || (pName->sa_family == AF_INET6 && len != sizeof(SA_IN6))    
#endif
      )
    {
        error = EINVAL;
        goto bind_error;
    }

    /* Bind the socket address */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if (error = Sock6Bind(pfd, pName))
            goto bind_error;
    }
    else
#endif
    {
        if (error = SockBind(pfd, pName))
            goto bind_error;
    }

    /* Success. Unlock the fd without error */
    fdint_unlockfd(pfd, 0);

    llExit();
    
    return (0);

bind_error:
    /* Check error condition */

    /* Unlock the fd with error */
    fdint_unlockfd(pfd, error);

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *      This function establishes a logical connection from
 *      the socket specified by s to the foreign name (address) 
 *      specified by pName.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pName
 *     Handle to the sockaddr structure that holds the remote host's
 *     address and port information to which the socket needs to connect to.
 *     For UDP/SOCK_DGRAM socket pName specifies the address to which
 *     packets would be sent by default or can be received from. 
 *     For TCP/SOCK_STREAM socket this call attempts to make a connection
 *     to the socket that is bound to address specified by pName.
 *
 *  @param[in]  len
 *     Holds the length of the sockaddr structure being passed as 
 *     argument to this function. This in turn depends on the
 *     address family of the socket.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_connect( SOCKET s, PSA pName, int len )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Validate Input */

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Verify Address Size */
    if ((pName->sa_family == AF_INET && len != sizeof(SA_IN))
#ifdef _INCLUDE_IPv6_CODE      
       || (pName->sa_family == AF_INET6 && len != sizeof(SA_IN6))    
#endif
      )
    {
        error = EINVAL;
        goto connect_error;
    }

    /* Connect to the remote host */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if (error = Sock6Connect( pfd, pName ))
            goto connect_error;
    }
    else
#endif
    {
        if (error = SockConnect( pfd, pName ))
            goto connect_error;
    }

    /* Success. Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return (0);

connect_error:
    /* Error. Unlock the fd with error */
    fdint_unlockfd( pfd, error );

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *      The getpeername() function retrieves the peer address of 
 *      the specified socket, store this address in the sockaddr 
 *      structure pointed to by the pName argument, and store the 
 *      length of this address in plen argument.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[out]  pName
 *     Handle to the sockaddr structure that holds the remote host's
 *     address and port information to which the socket is connected to.
 *     Valid only when this function returns success.
 *
 *  @param[out]  plen
 *     Holds the length of the sockaddr structure being passed as 
 *     result from this function. Valid only when this function returns
 *     success.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_getpeername( SOCKET s, PSA pName, int *plen )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Verify Address Size */
    if (!pName || !plen || (pName->sa_family == AF_INET && *plen < sizeof(SA_IN))
#ifdef _INCLUDE_IPv6_CODE      
        || (pName->sa_family == AF_INET6 && *plen < sizeof(SA_IN6))                    
#endif
      )
    {
        error = EINVAL;
        goto peername_error;
    }

    /* Get peer socket's name */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if (error = Sock6GetName(pfd, 0, pName))
            goto peername_error;

        /* Return Addr size when pointer is supplied */
        if (plen)
            *plen = sizeof(SA_IN6);
    }
    else
#endif
    {
        if (error = SockGetName(pfd, 0, pName))
            goto peername_error;

        /* Return Addr size when pointer is supplied */
        if (plen)
            *plen = sizeof(SA_IN);
    }

    /* Unlock the fd without error */
    fdint_unlockfd(pfd, 0);

    llExit();

    return (0);

peername_error:
    /* Unlock the fd with error */
    fdint_unlockfd(pfd, error);

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *      The getsockname() function retrieves the local address of 
 *      the specified socket, store this address in the sockaddr 
 *      structure pointed to by the pName argument, and store the 
 *      length of this address in plen argument.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[out]  pName
 *     Handle to the sockaddr structure that holds the local host's
 *     address and port information to which the socket is bound to.
 *     Valid only when this function returns success.
 *
 *  @param[out]  plen
 *     Holds the length of the sockaddr structure being passed as 
 *     result from this function. Valid only when this function returns
 *     success.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_getsockname( SOCKET s, PSA pName, int *plen )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Verify Address Size */
    if (!pName || !plen || (pName->sa_family == AF_INET && *plen < sizeof(SA_IN))
#ifdef _INCLUDE_IPv6_CODE      
        || (pName->sa_family == AF_INET6 && *plen < sizeof(SA_IN6))                    
#endif
       )
    {
        error = EINVAL;
        goto sockname_error;
    }

    /* Get socket's name */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if(error = Sock6GetName(pfd, pName, 0))
            goto sockname_error;

        /* Return Addr size when pointer is supplied */
        if (plen)
            *plen = sizeof(SA_IN6);
    }
    else
#endif
    {
        if(error = SockGetName(pfd, pName, 0))
            goto sockname_error;

        /* Return Addr size when pointer is supplied */
        if (plen)
            *plen = sizeof(SA_IN);
    }

    /* Success. Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return(0);

sockname_error:
    /* getsockname() failed. Unlock the fd with error */
    fdint_unlockfd( pfd, error );

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *      This function enables the socket to wait for any incoming 
 *      connection requests. It also configures the size of the pending 
 *      connection request queue of the socket. This call is applicable 
 *      only for connection oriented sockets (SOCK_STREAM/TCP).
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  maxcon
 *      Specifies the maximum length of the queue of pending connections.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_listen( SOCKET s, int maxcon )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Listen */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if((error = Sock6Listen(pfd, maxcon)))
            goto listen_error;
    }
    else
#endif
    {
        if((error = SockListen(pfd, maxcon)))
            goto listen_error;
    }

    
    /* Success. Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return (0);

listen_error:    
    /* Unlock the fd with error */
    fdint_unlockfd(pfd, error);

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to read data received on a 
 *      specified socket. 
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pbuf
 *      Specifies the buffer to which the data has to be copied to.
 *
 *  @param[in]  size
 *      Specifies the maximum size of the buffer.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @retval
 *      Success -   Number of bytes of data received successfully
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_recv( SOCKET s, void *pbuf, int size, int flags )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    INT32    rxsize;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 / PIPE / RAWETH */
    if ((fdint_lockfd(pfd, 0) == SOCKET_ERROR) )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Receive data  */
    if( pfd->Type == HTYPE_SOCK )
        error = SockRecv(pfd, pbuf, (INT32)size, flags, 0, &rxsize);
#ifdef _INCLUDE_IPv6_CODE      
    else if( pfd->Type == HTYPE_SOCK6 )
        error = Sock6Recv(pfd, pbuf, (INT32)size, flags, 0, &rxsize);
#endif
    else if( pfd->Type == HTYPE_RAWETHSOCK )
    {
        /* For now, we only support no-copy version of recv on 
         * raw ethernet sockets, so return error on recv().
         */
        error = EOPNOTSUPP;
    }
    else
        error = PipeRecv(pfd, pbuf, (INT32)size, flags, &rxsize);

    if (error)
    {
        /* Unlock the fd with error */
        fdint_unlockfd( pfd, error );

        llExit();

        return (SOCKET_ERROR);
    }

    /* Success. Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return ((int)rxsize);
}

/** 
 *  @b Description
 *  @n  
 *      This function attempts to receive data from a socket. It is 
 *      normally called with unconnected, non-connection oriented sockets. 
 *      The data is placed into the buffer specified by pbuf, up to a maximum 
 *      length specified by size. The options in flags can be used to change 
 *      the default behavior of the operation. The name (address) of the sender
 *      is written to pName.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pbuf
 *      Specifies the buffer to which the data has to be copied to.
 *
 *  @param[in]  size
 *      Specifies the maximum size of the buffer.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @param[out] pName
 *      Pointer to place name (address) of sender
 *
 *  @param[out] plen
 *      Pointer to size of pName
 *
 *  @retval
 *      Success -   Number of bytes of data received successfully
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_recvfrom( SOCKET s, void *pbuf, int size, int flags, PSA pName, int *plen )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    INT32    rxsize;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
      )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Validate Sizes and Pointers */
    if (pName && (!plen || (pName->sa_family == AF_INET && *plen < sizeof(SA_IN)) 
#ifdef _INCLUDE_IPv6_CODE      
        ||  (pName->sa_family == AF_INET6 && *plen < sizeof(SA_IN6))                           
#endif
       ))
    {
        error = EINVAL;
        goto recv_error;
    }

    /* Receive data - use Socket or Pipe send based on type */
#ifdef _INCLUDE_IPv6_CODE
    if (pfd->Type == HTYPE_SOCK6)
    {
        if ((error = Sock6Recv(pfd, pbuf, (INT32)size, flags, pName, &rxsize)))
            goto recv_error;

        /* Return Addr size */
        if (plen)
            *plen = sizeof(SA_IN6);
    }
    else
#endif
    {
        if ((error = SockRecv(pfd, pbuf, (INT32)size, flags, pName, &rxsize)))
            goto recv_error;

        /* Return Addr size */
        if (plen)
            *plen = sizeof(SA_IN);
    }

    /* Success. Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return ((int)rxsize);

recv_error:
    /* Unlock the fd with error */
    fdint_unlockfd( pfd, error );

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *     This function attempts to send data on a socket. It is used on 
 *     connected sockets only. The data to send is contained in the buffer 
 *     specified by pbuf, with a length specified by size. The options in flags 
 *     can be used to change the default behavior of the operation. The functions 
 *     returns the length of the data transmitted on successful completion.
 *      
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pbuf
 *     Data buffer holding data to transmit 
 *
 *  @param[in]  size
 *     Size of data.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @retval
 *      Success -   Number of bytes of data sent successfully
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_send( SOCKET s, void *pbuf, int size, int flags )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    INT32    txsize;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 / PIPE */
    if ((fdint_lockfd(pfd, 0) == SOCKET_ERROR) )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Send data */
    if (pfd->Type == HTYPE_SOCK)
    {
        error = SockSend(pfd, pbuf, (INT32)size, flags, &txsize);
    }
#ifdef _INCLUDE_IPv6_CODE      
    else if (pfd->Type == HTYPE_SOCK6)
        error = Sock6Send(pfd, pbuf, (INT32)size, flags, &txsize);
#endif
    else if (pfd->Type == HTYPE_RAWETHSOCK)
    {
        error = RawEthSockSend(pfd, pbuf, (INT32)size, &txsize);
    }
    else
        error = PipeSend(pfd, pbuf, (INT32)size, flags, &txsize);

    if (error)
    {
        /* Unlock the fd with error */
        fdint_unlockfd( pfd, error );

        llExit();
    
        return (SOCKET_ERROR);
    }

    /* Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return ((int)txsize);
}

/** 
 *  @b Description
 *  @n  
 *      This function allocates bufSize bytes memory for the
 *      data buffer and required memory for the packet buffer to 
 *      hold this data. On successful memory allocation, it 
 *      initializes the phBuf and phPkt pointers with the data
 *      buffer and packet buffer handles. The data buffer obtained
 *      from this API can be used by the application to fill in 
 *      required data. The application then would need to use the
 *      data buffer and packet buffer handles in its call to sendnc()
 *      API to send the packet out without any copy on transmit path
 *      by the stack. The packet and data buffers are freed up automatically
 *      once the packet transmission is completed in the ethernet driver.
 *      However, if for some reason the application would like to free
 *      the buffer and packet obtained using this call, it can to do so
 *      by passing the packet buffer handle to sendncfree() API call and it
 *      would free up both the packet and data buffers.
 *
 *      This API is currently only supported for AF_RAWETH family sockets.
 *      
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  bufSize
 *     Size of data buffer to allocate memory for.
 *
 *  @param[in]  phBuf
 *     Pointer to data buffer handle in which the application can
 *     fill in the required data to send using sendnc() API.
 *
 * *  @param[in]  phPkt
 *     Pointer to the packet buffer handle which holds the data buffer
 *     in turn.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_getsendncbuff(SOCKET s, UINT32 bufSize, void** phBuf, HANDLE* phPkt)
{
    FILEDESC *pfd = (FILEDESC *)s;
    PBM_Pkt*    pPkt;
    UINT32      error;

    llEnter();

    /* Lock the fd - type must be RAWETHSOCK */
    if (fdint_lockfd(pfd, HTYPE_RAWETHSOCK) == SOCKET_ERROR)
    {
        llExit();
        return( SOCKET_ERROR );
    }        

    /* Allocate space for packet and data buffers. */
    pPkt = (HANDLE)RawEthSockCreatePacket(pfd, bufSize, &error);    

    /* Check if the operation succeeded */
    if( !pPkt )
    {
        /* Unlock the fd with error */
        fdint_unlockfd( pfd, error );

        llExit();
        return( SOCKET_ERROR );            
    }
    else
    {
        /* Successfully obtained a packet. */

        *phBuf = (HANDLE)(pPkt->pDataBuffer + pPkt->DataOffset);

        *phPkt = (HANDLE)pPkt;

        /* Unlock the fd without error */
        fdint_unlockfd( pfd, 0 );

        llExit();            
    }

    /* Return Success */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *     This function attempts to send data on a socket without copy. The data to 
 *     send is contained in the buffer specified by pbuf, with a length 
 *     specified by size. Also, a valid handle to the packet buffer hPkt needs to be specified.
 *     This packet handle and the buffer pointer should have been obtained from getsendncbuf() call
 *     before calling this API. The options in flags can be used to change the default 
 *     behavior of the operation. The functions returns the length of the data 
 *     transmitted on successful completion.
 *
 *     This API is currently only supported for AF_RAWETH family sockets.
 *      
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pbuf
 *     Data buffer holding data to transmit 
 *
 *  @param[in]  size
 *     Size of data.
 *
 *  @param[in]  hPkt
 *     packet handle obtained previously from getsendncbuf() call.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @retval
 *      Success -   Number of bytes of data sent successfully
 *  @retval
 *      Error   -   -1
 *      
 */
/* ARGSUSED */
int NDK_sendnc( SOCKET s, void *pbuf, int size, HANDLE hPkt, int flags )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    INT32    txsize;

    llEnter();

    /* Lock the fd - type must be SOCKRAWETH */
    if ((fdint_lockfd(pfd, HTYPE_RAWETHSOCK) == SOCKET_ERROR) )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Send data */
    if ((error = RawEthSockSendNC(pfd, pbuf, (INT32)size, hPkt, &txsize)))
    {
        /* Unlock the fd with error */
        fdint_unlockfd( pfd, error );

        llExit();
    
        return (SOCKET_ERROR);
    }

    /* Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return ((int)txsize);
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to free data buffers obtained using
 *      getsendncbuff() calls. This is supported only for Raw ethernet socket /
 *      AF_RAWETH family sockets.
 *
 *  @param[in]  hFrag
 *      Handle to receive buffer to free.
 *
 *  @retval
 *      None
 */
void NDK_sendncfree( HANDLE hFrag )
{
    llEnter();
    if( hFrag )
        PBM_free( (PBM_Handle)hFrag );
    llExit();
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to read data received on a 
 *      specified socket without copying. This is supported
 *      only on IPv4/AF_INET family and Raw ethernet/AF_RAWETH sockets.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[out]  ppbuf
 *      Pointer to receive data buffer pointer.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @param[out]  phFrag
 *      Pointer to receive buffer handle.
 *
 *  @retval
 *      Success -   Number of bytes of data received successfully
 *  @retval
 *      Error   -   -1
 *
 *      Returns 0 on connection oriented sockets where the connection
 *      has been closed by the peer (or socket shutdown for read)
 */
int NDK_recvnc( SOCKET s, void **ppbuf, int flags, HANDLE *phFrag )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    PBM_Pkt  *pPkt;

    llEnter();

    /* Lock the fd - type must be SOCK/RAWETHSOCK */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) &&
        (fdint_lockfd(pfd, HTYPE_RAWETHSOCK) == SOCKET_ERROR))
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Validate Sizes and Pointers */
    if( !ppbuf || !phFrag )
    {
        error = EINVAL;
        goto recvnc_error;
    }

    /* Receive the data */
    if (pfd->Type == HTYPE_RAWETHSOCK)
    {
        if (error = RawEthSockRecvNC(pfd, &pPkt))
            goto recvnc_error;
    }
	else if (error = SockRecvNC(pfd, flags, 0, &pPkt))
        goto recvnc_error;

    /* Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    /* Check size from return frag */
    if( pPkt && !pPkt->ValidLen )
    {
        PBM_free( pPkt );
        pPkt = 0;
    }

    /* Return the frag and buffer pointer */
    *phFrag = (HANDLE)pPkt;
    if( pPkt )
    {
        /* Return pointer and length of data */
        *ppbuf = pPkt->pDataBuffer + pPkt->DataOffset;
        return ((int)pPkt->ValidLen);
    }

    return(0);

recvnc_error:
    /* Unlock the fd with error */
    fdint_unlockfd( pfd, error );

    llExit();
    return( SOCKET_ERROR );
}

/** 
 *  @b Description
 *  @n  
 *      This function attempts to receive data from a socket. It is 
 *      normally called with unconnected, non-connection oriented sockets. 
 *      A pointer to data is returned in ppbuf. A system handle used to free
 *      the buffer is returned in phFrag. Both of these pointers must be
 *      valid. The name (address) of the sender is written to pName. This 
 *      function is only valid for IPv4/AF_INET family sockets.
 *
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[out]  ppbuf
 *      Pointer to receive data buffer pointer.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @param[out] pName
 *      Pointer to place name (address) of sender
 *
 *  @param[out] plen
 *      Pointer to size of pName
 *
 *  @param[out]  phFrag
 *      Pointer to receive buffer handle.
 *
 *  @retval
 *      Success -   Number of bytes of data received successfully
 *  @retval
 *      Error   -   -1
 *
 *      Returns 0 on connection oriented sockets where the connection
 *      has been closed by the peer (or socket shutdown for read)
 */
int NDK_recvncfrom( SOCKET s, void **ppbuf, int flags, PSA pName, int *plen, HANDLE *phFrag )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    PBM_Pkt  *pPkt;

    llEnter();

    /* Lock the fd - type must be SOCK */
    if((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR))
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Validate Sizes and Pointers */
    if( !ppbuf || !phFrag || !pName || !plen || (pName->sa_family == AF_INET && *plen < sizeof(SA_IN)))
    {
        error = EINVAL;
        goto recvnc_error;
    }

    /* Receive data - works only with socket type */
    if(error = SockRecvNC(pfd, flags, pName, &pPkt))
        goto recvnc_error;

    /* Return Addr size */
    if (plen)
        *plen = sizeof( SA_IN );

    /* Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    /* Check size from return frag */
    if( pPkt && !pPkt->ValidLen )
    {
        PBM_free( pPkt );
        pPkt = 0;
    }

    /* Return the frag and buffer pointer */
    *phFrag = (HANDLE)pPkt;

    if( pPkt )
    {
        /* Return pointer and length of data */
        *ppbuf = pPkt->pDataBuffer + pPkt->DataOffset;
        return((int)pPkt->ValidLen);
    }
    return(0);

recvnc_error:
    /* Unlock the fd with error */
    fdint_unlockfd( pfd, error );

    llExit();

    return( SOCKET_ERROR );
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to free data buffers obtained using
 *      recvnc() or recvncfrom() calls. This is supported
 *      only IPv4/AF_INET family sockets.
 *
 *  @param[in]  hFrag
 *      Handle to receive buffer to free.
 *
 *  @retval
 *      None
 */
void NDK_recvncfree( HANDLE hFrag )
{
    llEnter();
    if( hFrag )
        PBM_free( (PBM_Handle)hFrag );
    llExit();
}

/** 
 *  @b Description
 *  @n  
 *      This function attempts to send data on a socket to a specified 
 *      destination. It is used on unconnected, non-connection oriented \
 *      sockets only. The data to send is contained in the buffer specified 
 *      by pbuf, with a length specified by size. The options in flags can 
 *      be used to change the default behavior of the operation.
 *      
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in]  pbuf
 *     Data buffer holding data to transmit 
 *
 *  @param[in]  size
 *     Size of data.
 *
 *  @param[in]  flags
 *      Options flags
 *
 *  @param[out] pName
 *      Pointer to name (address) of destination
 *
 *  @param[out] len
 *     size of pName
 *
 *  @retval
 *      Success -   Number of bytes of data sent successfully
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_sendto( SOCKET s, void *pbuf, int size, int flags, PSA pName, int len )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;
    INT32    txsize;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) 
#ifdef _INCLUDE_IPv6_CODE      
       && (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR)
#endif
       )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Verify Address Size */
    if (((pfd->Type == HTYPE_SOCK) && len != sizeof(SA_IN)) 
#ifdef _INCLUDE_IPv6_CODE      
       || ((pfd->Type == HTYPE_SOCK6) && len != sizeof(SA_IN6))
#endif
       )
    {
        error = EINVAL;
        goto sendto_error;
    }

    /* Connect */
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        if ((error = Sock6Connect(pfd, pName)))
            goto sendto_error;
    
        /* Send */
        error = Sock6Send(pfd, pbuf, (INT32)size, flags, &txsize);

        /* Disconnect */
        Sock6Disconnect(pfd);
    }
    else
#endif
    {
        if ((error = SockConnect(pfd, pName)))
            goto sendto_error;

        /* Send */
        error = SockSend(pfd, pbuf, (INT32)size, flags, &txsize);

        /* Disconnect */
        SockDisconnect(pfd);
    }

    /* Record any error condition */
    if (error)
        goto sendto_error;

    /* Unlock the fd without error */
    fdint_unlockfd(pfd, 0);

    llExit();

    return ((int)txsize);

sendto_error:
    /* Unlock the fd with error */
    fdint_unlockfd(pfd, error);

    llExit();

    return (SOCKET_ERROR);
}

/** 
 *  @b Description
 *  @n  
 *      This function causes all or part of a full-duplex 
 *      connection on the socket associated with a socket to be shut down.
 *      If how is SHUT_RD (0), further receives will be disallowed. 
 *      If how is SHUT_WR (1), further sends will be disallowed. If how is
 *      SHUT_RDWR (2), further sends and receives will be disallowed.
 *      
 *  @param[in]  s
 *      Handle to a socket obtained using "socket" function call.
 *
 *  @param[in] how
 *      Manner of shutdown.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_shutdown( SOCKET s, int how )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Lock the fd - type must be SOCK / SOCK6 */
    if ((fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR) &&
#ifdef _INCLUDE_IPv6_CODE      
       (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR) &&
#endif
       (fdint_lockfd(pfd, HTYPE_RAWETHSOCK) == SOCKET_ERROR))
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Shutdown the socket */
    if (pfd->Type == HTYPE_RAWETHSOCK)
    {
        error = RawEthSockShutdown(pfd, how);
    }
    else 
#ifdef _INCLUDE_IPv6_CODE      
    if (pfd->Type == HTYPE_SOCK6)
    {
        error = Sock6Shutdown(pfd, how);
    }
    else 
#endif
    {
        error = SockShutdown(pfd, how);
    }

    /* Check error condition */
    if (error)
    {
        /* Unlock the fd with error */
        fdint_unlockfd( pfd, error );

        llExit();

        return (SOCKET_ERROR);
    }

    /* Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return (0);
}

/** 
 *  @b Description
 *  @n  
 *      This function creates a socket, an endpoint for 
 *      communication and returns the socket in the form 
 *      of a file descriptor.
 *      
 *  @param[in]  domain
 *      Socket domain/family. Valid values are AF_INET/AF_INET6.
 *
 *  @param[in] type
 *      Socket type (SOCK_DGRAM, SOCK_STREAM, SOCK_RAW).
 *
 *  @param[in] protocol
 *      Socket protocol (Normally IPPROTO_TCP or IPPROTO_UDP, but
 *      can be anything when type is set to SOCK_RAW)
 *
 *  @retval
 *      Success -   socket handle
 *  @retval
 *      Error   -   INVALID_SOCKET
 *      
 */
SOCKET NDK_socket( int domain, int type, int protocol )
{
    FDTABLE  *pfdt;
    FILEDESC *pfd;
    int      error = 0;

    llEnter();

    /* Verify Socket Session */
    if (!fdint_getfdt(0))
    {
        llExit();
        return( INVALID_SOCKET );
    }

#ifdef _INCLUDE_IPv6_CODE      
    if (domain == AF_INET6)
    {
        /* Create a new IPv6 socket */
        if ((error=Sock6New(domain, type, protocol, 0, 0, (HANDLE *)&pfd)))
            goto socket_error;
    }
    else 
#endif
    if (domain == AF_INET)
    {
        /* Create a new IPv4 socket */
        if((error=SockNew(domain, type, protocol, 0, 0, (HANDLE *)&pfd)))
            goto socket_error;
    } 
    else if (domain == AF_RAWETH)
    {
        /* Create a new Raw Ethernet socket */
        if((error=RawEthSockNew(domain, type, protocol, 0, 0, (HANDLE *)&pfd)))
            goto socket_error;            
    }
    else
    {
        /* Unknown Protocol Family type. Only Supported Families are:
         * AF_INET/AF_INET6/AF_RAWETH.
         */
        error = EPFNOSUPPORT;
        goto socket_error;            
    }


    /* Success. Return the file descriptor table index */
    llExit();

    return (pfd);

socket_error:
    if (((pfdt=fdint_getfdt(0)) != 0))
        pfdt->error = error;

    llExit();

    return (INVALID_SOCKET);
}

/** 
 *  @b Description
 *  @n  
 *     This function returns the options associated with a
 *     socket.
 *      
 *  @param[in]  s
 *      Socket handle
 *
 *  @param[in] level
 *      Option level (SOL_SOCKET, IPPROTO_IP, IPPROTO_IPV6,IPPROTO_TCP)
 *
 *  @param[in] op
 *      Socket option to get
 *
 *  @param[in] pbuf
 *      Pointer to memory buffer
 *
 *  @param[in] pbufsize
 *      Pointer to size of memory buffer
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_getsockopt( SOCKET s, int level, int op, void *pbuf, int *pbufsize )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Lock the fd - type must be SOCK/SOCK6 */
    if (fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR &&
#ifdef _INCLUDE_IPv6_CODE      
       (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR) &&
#endif
       (fdint_lockfd(pfd, HTYPE_RAWETHSOCK) == SOCKET_ERROR))
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Get Option */
    if (pfd->Type == HTYPE_RAWETHSOCK)
    {
        error = RawEthSockGet(pfd, level, op, pbuf, pbufsize);
    }
    else 
#ifdef _INCLUDE_IPv6_CODE
    if (pfd->Type == HTYPE_SOCK6)
    {
        error = Sock6Get(pfd, level, op, pbuf, pbufsize);
    }
    else
#endif
    {
        error = SockGet(pfd, level, op, pbuf, pbufsize);
    }

    /* Check error condition */
    if (error)
    {
        /* Unlock the fd with error */
        fdint_unlockfd(pfd, error);

        llExit();

        return (SOCKET_ERROR);
    }

    /* Success.Unlock the fd without error */
    fdint_unlockfd( pfd, 0 );

    llExit();

    return (0);
}

/** 
 *  @b Description
 *  @n  
 *     This function sets the option values associated with a
 *     socket.
 *      
 *  @param[in]  s
 *      Socket handle
 *
 *  @param[in] level
 *      Option level (SOL_SOCKET, IPPROTO_IP, IPPROTO_IPV6,IPPROTO_TCP)
 *
 *  @param[in] op
 *      Socket option to set
 *
 *  @param[in] pbuf
 *      Pointer to memory buffer
 *
 *  @param[in] bufsize
 *      Size of memory buffer pointed to by pbuf
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int NDK_setsockopt( SOCKET s, int level, int op, void *pbuf, int bufsize )
{
    FILEDESC *pfd = (FILEDESC *)s;
    int  error = 0;

    llEnter();

    /* Lock the fd - type must be SOCK/SOCK6 */
    if (fdint_lockfd(pfd, HTYPE_SOCK) == SOCKET_ERROR &&
#ifdef _INCLUDE_IPv6_CODE      
       (fdint_lockfd(pfd, HTYPE_SOCK6) == SOCKET_ERROR) &&
#endif
       (fdint_lockfd(pfd, HTYPE_RAWETHSOCK) == SOCKET_ERROR))
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Set Option */
    if (pfd->Type == HTYPE_RAWETHSOCK)
    {
        error = RawEthSockSet(pfd, level, op, pbuf, bufsize);
    }
	else 
#ifdef _INCLUDE_IPv6_CODE    
    if (pfd->Type == HTYPE_SOCK6)
    {
        error = Sock6Set(pfd, level, op, pbuf, bufsize);
    }
    else
#endif
    {
        error = SockSet(pfd, level, op, pbuf, bufsize);
    }

    /* Check error condition */
    if (error)
    {
        /* Unlock the fd with error */
        fdint_unlockfd(pfd, error);

        llExit();
        
        return (SOCKET_ERROR);
    }

    /* Unlock the fd without error */
    fdint_unlockfd(pfd, 0);

    llExit();

    return (0);
}

/** 
 *  @b Description
 *  @n  
 *      Creates a pre-connected full duplex pipe. The returned file 
 *      descriptors can be used with all the fd file descriptor functions, 
 *      as well as the send() and recv() socket functions.
 *      
 *  @param[in]  pfdret1
 *      Pointer to file descriptor to first end of pipe.
 *
 *  @param[in] pfdret2
 *      Pointer to file descriptor to second end of pipe.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 *      
 */
int pipe( HANDLE *pfdret1, HANDLE *pfdret2 )
{
    FDTABLE  *pfdt;
    FILEDESC *pfd1=0,*pfd2=0;
    int      error = 0;

    llEnter();

    /* Verify Socket Session */
    if (!fdint_getfdt(0))
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Verify the fd pointers */
    if (!pfdret1 || !pfdret2)
    {
        error = EINVAL;
        goto pipe_error;
    }

    /* Create a new pipe */
    if ((error=PipeNew( (HANDLE *)&pfd1, (HANDLE *)&pfd2 )))
        goto pipe_error;

    llExit();

    /* Return the file descriptor table indicies */
    *pfdret1 = pfd1;
    *pfdret2 = pfd2;

    return (0);

pipe_error:
    if ((pfdt=fdint_getfdt(0)) != 0)
        pfdt->error = error;

    llExit();

    return (SOCKET_ERROR);
}
