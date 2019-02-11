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
 * ======== conipv6.c ========
 *
 * Console command processing which allows configuration and testing
 * of the various IPv6 API available to application developers.
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>
#include "console.h"

#ifdef _INCLUDE_IPv6_CODE

#define MAXPACKET       1520        /* max packet size */
#define DATALEN         100         /* default data length */

/** 
 *  @b Description
 *  @n  
 *      The function displays the various IPv6 commands which can 
 *      be invoked from the command line.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DisplayUsage (void)
{
    ConPrintf("\n[ipv6 Command]\n");
    ConPrintf("\nUse this to configure/display the IPv6 stack properties\n\n");
    ConPrintf("ipv6                             - Displays the Usage screen.\n");
    ConPrintf("ipv6 init   <if>                 - Initialize the IPv6 stack on an interface.\n");
    ConPrintf("ipv6 deinit <if>                 - Deinitialize the IPv6 stack on an interface.\n");
    ConPrintf("ipv6 add  <if> <IPAddr> <NumBits> <VLT> <PLT> <ANYCAST/UNICAST> - Adds IPv6 Adddress\n");
    ConPrintf("ipv6 del  <if> <IPAddr>          - Deletes an IPv6 Address.\n");
    ConPrintf("ipv6 neigh                       - Display the Neighbor table.\n");
    ConPrintf("ipv6 route                       - Display the IPv6 Routing Table\n");
    ConPrintf("ipv6 flushroutes <if>            - Deletes routes to non-local hosts & clears their neigh cache entries\n");
    ConPrintf("ipv6 bind                        - Display a list of all configured IPv6 Addresses\n");
    ConPrintf("ipv6 stats                       - Displays IPv6 stack statistics for core IPv6, TCP, UDP, RAW, ICMPv6 modules \n");
    ConPrintf("ipv6 test                        - Test Commands used to test the IPv6 API \n");
    ConPrintf("                                 - Type ipv6 test to get a list of all the test commands available\n");
    return;
}

/**
 *  @b Description
 *  @n  
 *      The function is registered as the call back function and 
 *      indicates the status of IPv6 DAD State machine. System 
 *      Developers can use this to ensure the uniqueness of the IPv6
 *      Address assignment.
 *
 *      This function is called OUTSIDE kernel mode.
 *
 *  @param[in]  Address
 *      The IPv6 address on which the DAD state machine has been executed
 *  @param[in]  dev_index
 *      Interface Index on which the IPv6 Address was assigned.
 *  @param[in]  Status
 *      This is the status of DAD state Machine.
 *          - Value of 1 indicates that the address was UNIQUE
 *          - Value of 0 indicates that the address was DUPLICATE
 *
 *  @retval
 *      Not Applicable.
 */
/* ARGSUSED */
static void IPv6DADStatus(IP6N Address, UINT16 dev_index, UINT8 Status)
{
    char strIPAddress[40];

    /* Convert the IP Address to String Format. */
    IPv6IPAddressToString (Address, strIPAddress);

    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to initialize the IPv6 stack over a
 *      specific Interface.
 *
 *  @param[in]  ifId
 *      Interface Identifier over which the stack it to be initialized
 *      This can either be the name or device index 
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6InitializeStack (char* ifId)
{
    UINT16      dev_index;    
    NIMU_IF_REQ if_req;
    int         status;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (ifId);
    if (dev_index == 0)
    {
        if (strlen(ifId) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, ifId);
        }
        else {
            ConPrintf(
                "CmdIPv6InitializeStack: error interface ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("Error: Device does not exist.\n");
            return;
        }
    }

    /* Enter the kernel Mode. */
    llEnter ();
    status = IPv6InterfaceInit (dev_index, IPv6DADStatus);
    llExit ();

    /* Were we able to initialize the IPv6 stack? */
    if (status < 0)
        ConPrintf ("Error: Unable to initialize the IPv6 stack on device %d\n", dev_index);
    else
        ConPrintf ("IPv6 stack has been initialized on %d\n", dev_index);

    /* Work has been done. */
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to deinitialize the IPv6 stack over a
 *      specific Interface.
 *
 *  @param[in]  ifId
 *      Interface Identifier over which the stack it to be deinitialized
 *      This can either be the name or device index 
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DeinitializeStack (char* ifId)
{
    UINT16      dev_index;    
    NIMU_IF_REQ if_req;
    int         status;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (ifId);
    if (dev_index == 0)
    {
        if (strlen(ifId) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, ifId);
        }
        else {
            ConPrintf(
                "CmdIPv6DeinitializeStack: error interface ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("Error: Device does not exist.\n");
            return;
        }
    }

    /* Enter the kernel Mode. */
    llEnter ();
    status = IPv6InterfaceDeInit (dev_index);
    llExit ();

    /* Were we able to deinitialize the stack? */
    if (status < 0)
        ConPrintf ("Error: Unable to de-initialize the IPv6 stack on device %d\n", dev_index);
    else
        ConPrintf ("IPv6 stack has been deinitialized on %d\n", dev_index);

    /* Work has been done. */
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to add an IPv6 Address to the specific interface.
 *
 *  @param[in]  ifId
 *      Interface Identifier over which the address is to be added.
 *  @param[in]  Address
 *      IPv6 Address to be configured.
 *  @param[in]  PrefixBits
 *      The network mask on which this address resides.
 *  @param[in]  VLT
 *      Valid Lifetime of the address
 *  @param[in]  PLT
 *      Preferred Lifetime of the address
 *  @param[in]  Type
 *      Type of Address (UNICAST or ANYCAST).
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6AddAddress(char* ifId, char* Address, char* PrefixBits, char* VLT, char* PLT, char* Type)
{
    UINT16      dev_index;    
    NIMU_IF_REQ if_req;
    UINT8       isAnycast = 0;
    UINT16      NumBits;
    UINT32      ValidLifetime;
    UINT32      PrefLifetime;
    IP6N        IPAddress;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (ifId);
    if (dev_index == 0)
    {
        if (strlen(ifId) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, ifId);
        }
        else {
            ConPrintf("CmdIPv6AddAddress: error interface ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("Error: Device does not exist.\n");
            return;
        }
    }

    /* Convert the Address from CHAR to IP6N format. */
    IPv6StringToIPAddress (Address, &IPAddress);

    /* Make sure the number of prefix bits is correct. */
    NumBits = atoi (PrefixBits);
    if (NumBits == 0)
    {
        /* Error: Incorrect number of prefix bits. */
        ConPrintf ("Error: Incorrect Number of PREFIX Bits Specified %s\n", PrefixBits);
        return;
    }

    /* Configure the Valid Lifetime. Check if INFINITE was specified? */
    if (!strcmp (VLT, "INFINITE"))
    {
        /* YES. Set the Valid Lifetime. */
        ValidLifetime = INFINITE_LT;
    }
    else
    {
        /* NO; convert from string to integer format. */
        ValidLifetime = atoi (VLT);
    }


    /* Configure the Preferred Lifetime. Check if INFINITE was specified? */
    if (!strcmp (PLT, "INFINITE"))
    {
        /* YES. Set the Preferred Lifetime. */
        PrefLifetime = INFINITE_LT;
    }
    else
    {
        /* NO; convert from string to integer format. */
        PrefLifetime = atoi (PLT);
    }

    /* Determine the Type of address: UNICAST or ANYCAST */
    if (strcmp(Type,"ANYCAST") == 0)
        isAnycast = 1;

    /* Set the IPv6 Address in the System */
    if (IPv6AddAddress (dev_index, IPAddress, NumBits, ValidLifetime, PrefLifetime, isAnycast) < 0)
        ConPrintf ("Error: Unable to add the IPv6 Address\n");
    else
        ConPrintf ("IPv6 Address has been configured.\n");

    /* Work has been done. */
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to delete an IPv6 Address from the specific interface.
 *
 *  @param[in]  ifId
 *      Interface Identifier over which the address is to be deleted.
 *  @param[in]  Address
 *      IPv6 Address to be removed.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DelAddress (char* ifId, char* Address)
{
    UINT16      dev_index;    
    NIMU_IF_REQ if_req;
    IP6N        IPAddress;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (ifId);
    if (dev_index == 0)
    {
        if (strlen(ifId) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, ifId);
        }
        else {
            ConPrintf("CmdIPv6DelAddress: error interface ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("Error: Device does not exist.\n");
            return;
        }
    }

    /* Convert the Address from CHAR to IP6N format. */
    IPv6StringToIPAddress (Address, &IPAddress);

    /* Delete the IPv6 Address from the */
    if (IPv6DelAddress (dev_index, IPAddress) < 0)
        ConPrintf ("Error: Unable to remove the address\n");
    else
        ConPrintf ("IPv6 address has been removed from the interface\n");

    return;
}

#if 0
/** 
 *  @b Description
 *  @n  
 *      Creates two sockets and binds them to the same port. 
 *      The idea is to detect BIND Fails on the second socket.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6DuplicateBind1Test ()
{
    SOCKET               sudp1;
    SOCKET               sudp2;
    struct  sockaddr_in6 sin1;
   
    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("Duplicate BIND1 TEST\n");
    
    /* Create the first UDP socket for the IPv6 Protocol. */ 
    sudp1 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sudp1 == INVALID_SOCKET)
    {
        ConPrintf ("Error: Invalid V6 Socket\n");
        return;
    }

    /* Create the first UDP socket for the IPv6 Protocol. */ 
    sudp2 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sudp2 == INVALID_SOCKET)
    {
        ConPrintf ("Error: Invalid V6 Socket\n");
        return;
    }    

    /* Bind the socket to port 8000. */ 
    bzero( &sin1, sizeof(struct sockaddr_in6) );
    sin1.sin6_family    = AF_INET6;
    sin1.sin6_port      = htons(8000);
    if ( bind(sudp1, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf ("Error: Unable to bind socket Error:%d\n", fdError());
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }

    /* Bind the socket to port 8000. */ 
    bzero( &sin1, sizeof(struct sockaddr_in6) );
    sin1.sin6_family    = AF_INET6;
    sin1.sin6_port      = htons(8000);
    if ( bind(sudp2, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        /* This should FAIL as expected; Error code should be EADDRINUSE. */
        int errorCode = fdError();
        if (errorCode == EADDRINUSE)
            ConPrintf ("TEST PASSED\n");
        else
            ConPrintf ("TEST WARNING: BIND Failed but Error Code: %d\n", errorCode);
    }
    else
    {
        /* The second BIND Succeeded; this should have failed. */
        ConPrintf ("TEST FAILED: Duplicate BIND Failure.\n");
    }

    /* Close the sockets. */
    fdClose (sudp1);
    fdClose (sudp2);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function tests the Destination (Port) Unreachable
 *      message. The function creates a V6 socket and sends 
 *      a packet to a PEER on port 8000. Since there is no entity
 *      residing on port 8000; the peer resonds with a Destination
 *      Unreachable message. 
 *
 *  @param[in]  Address
 *      IPv6 Address of the destination host.
 *  @retval
 *      Not Applicable.
 */
static void V6TestDstUnreachablePort (char* Address)
{
    SOCKET               sudp;
    int                  cnt;
    char                 Buffer[100];
    struct  sockaddr_in6 sin1;
    IP6N                 PeerAddress;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING Port Unreachable\n");

    /* Convert the string IP address to IP6N format. */
    IPv6StringToIPAddress (Address, &PeerAddress);
 
    /* Create the UDP socket for the IPv6 Protocol. */ 
    sudp = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sudp == INVALID_SOCKET)
    {
        ConPrintf ("TEST FAILED: Unable to Create Socket Error: %d\n", fdError());
        return;
    }

    /* Bind the socket to port 8000 and any address. */ 
    bzero( &sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family    = AF_INET6;
    sin1.sin6_port      = htons(8000);
    if (bind(sudp, (PSA) &sin1, sizeof(sin1) ) < 0)
    {
        ConPrintf ("TEST FAILED: Unable to BIND socket Error: %d\n", fdError());
        fdClose(sudp);        
        return;
    }

    /* Copy the Peer address into the structure. */
    mmCopy ((void *)&sin1.sin6_addr, (void *)&PeerAddress, sizeof(struct sockaddr_in6));

    /* ASSUMPTION: Scope ID is 1. If there are more interfaces this needs to be modified. */
    sin1.sin6_scope_id  = 1;

    /* Create the data payload. */
    strcpy (Buffer, "Test Code V6\n");

    /* Send the first packet out; this should always succeed. */
    cnt = sendto (sudp,(void *)&Buffer[0], strlen (Buffer), 0, (PSA)&sin1, sizeof(sin1));
    if (cnt < 0)
    {
        /* In the first iteration; the packet send should always succeed. If not then 
         * there is a FATAL Error. On all subsequent iterations; since we got the DST
         * Unreachable message we accept the failure. */
        ConPrintf ("TEST FAILED: Unable to send out packet Error: %d\n", fdError());
        fdClose(sudp);
        return;
    }

    /* Wait for some time before sending the next packet. Sufficient time to send out 
     * NS and let the lower layer state machine complete. */
    TaskSleep(1000);

    /* Now send the next packet out; this should FAIL. */
    cnt = sendto (sudp,(void *)&Buffer[0], strlen (Buffer), 0, (PSA)&sin1, sizeof(sin1));
    if (cnt < 0)
    {
        ConPrintf ("TEST PASSED: Expected sendto failure Error: %d\n", fdError());        
    }
    else
    {
        ConPrintf ("TEST FAILED: Packet transmission was successful.\n");
    }

    /* Close the socket. */
    fdClose(sudp);
    return;
}
#endif

/** 
 *  @b Description
 *  @n  
 *      The function tests the TCP Connect/Send/Recv APIs over the V6 
 *      socket layer. This test tries to connect to a TCP echo
 *      server listening on port 7 and sends and tries to receive 8K bytes 
 *      of data. It validates the data size received and ensures it's same
 *      as what we had sent. This test is repeated TEST_ITER times and if the test
 *      passes, the total time taken to complete the test and the data rate
 *      is printed on the console.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the ECHO server
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
#define TEST_ITER       2
static void V6TestTCPEcho (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET               stcp;
    int                  cnt;
    struct  sockaddr_in6 sin1;
    IP6N                 PeerAddress;
    struct  timeval      timeout;
    UINT32               test,i,j;
    char*                pBuffer = NULL;
    UINT32               startS, startMS;
    UINT32               endS, endMS;
    UINT32               ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING IPv6 TCPEcho \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }
 
    /* Create the TCP socket for the IPv6 Protocol. */ 
    stcp = socket(AF_INET6, SOCK_STREAM, 0);
    if (stcp == INVALID_SOCKET)
    {
        ConPrintf ("TEST FAILED: Unable to Create Socket Error: %d\n", fdError());
        return;
    }

    bzero( &sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family    = AF_INET6;
    sin1.sin6_port      = htons(7);
    sin1.sin6_scope_id  = ScopeId;

    /* Copy the Peer address into the structure. */
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Initialize the timeout; we will wait for 5 seconds. */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt (stcp, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ));
    setsockopt (stcp, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ));

    /* Connect to the remote peer on port 7. */
    if (connect (stcp, (struct sockaddr *)&sin1, sizeof(struct sockaddr_in6)) < 0)
    {
        ConPrintf("TEST FAILED: connect Failed with error: %d\n",fdError());
        goto leave;
    }

    startS = llTimerGetTime( &startMS );

    /* Allocate a working buffer */
    if( !(pBuffer = mmBulkAlloc( 8192 )) )
    {
        ConPrintf("failed temp buffer allocation\n");
        goto leave;
    }

    /* Create the data payload. */
    strcpy (pBuffer, "TCP Test Connect API over V6\n");

    /* Start the Test */
    test = 8192;
    for (j=0; j<TEST_ITER; j++)
    {
        /* Once the socket has connected we need to send out the data payload. */
        if (send (stcp, pBuffer, test, 0) < 0)
        {
            ConPrintf("TEST FAILED: send failed (%d)\n",fdError());
            goto leave;
        }

        /* Receive the packet. */
        i = 0;
        while (i < test)
        {
            cnt = recv (stcp, pBuffer, test, 0);
            if (cnt < 0)
            {
                ConPrintf("TEST FAILED:Unable to receive data error: (%d)\n", fdError());
                goto leave;
            }
            else if (cnt == 0)
            {
                ConPrintf ("TEST FAILED: Connection Dropped ?\n");            
                goto leave;
            }
            i += cnt;
        }

        /* Verify reception size */
        if (i != test)
        {
            ConPrintf("TEST FAILED: Sent %d bytes but Received only %d bytes\n",test, i);
            break;
        }
    }

    if (j == TEST_ITER)
    {
        endS = llTimerGetTime( &endMS );
        endS -= startS;
        endS *= 1000;
        endMS += endS;
        endMS -= startMS;
        endS = (endMS+50)/100;
        ConPrintf("TEST PASSED in %d ms, Data Rate: %d bytes/sec\n",endMS,(j*test*10)/endS);
    }

leave:
    if (pBuffer)
        mmBulkFree (pBuffer);

    /* Close the socket. */    
    fdClose(stcp);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      This function tests for a race condition between TCP listen/accept 
 *      socket calls on V6. 
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPRaceTest (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    char    buffer[128];
    struct  sockaddr_in6 sin1;
    int     rc,size;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING IPv6 TCP Listen/Accept Race Condition \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket1 */
    if (((s1 = socket (AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET))
    {
        ConPrintf("TEST FAILED: Error creating socket. Error: (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind to port 4000 */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(4000);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));
 
    /* Bind the socket */
    if (bind (s1, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Unable to Bind the socket. Error: (%d)\n",fdError());
        goto leave;
    }

    /* Start listening. We specify the maximum number of connections to 1. */
    if (listen (s1, 1) < 0)
    {
        ConPrintf("TEST FAILED: Listen failure. Error: (%d)\n",fdError());
        goto leave;
    }

    /* Create test socket2 */
    if ((s2 = socket (AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Error creating socket. Error: (%d)\n",fdError());
        goto leave;
    }

    /* Connect the second socket to the first */
    if (connect (s2, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Unable to connect, Error: (%d)\n",fdError());
        goto leave;
    }

    /* Send some test data */
    if (send (s2, "Hello World", 11, 0) < 0)
    {
        ConPrintf("TEST FAILED: Send failed. Error: (%d)\n",fdError());
        goto leave;
    }

    /* Close test socket2 */
    fdClose (s2);
    s2 = INVALID_SOCKET;

    /* Get the accept socket */
    size = sizeof (sin1);
    if ((s2 = accept (s1, (PSA)&sin1, &size)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Accept error (%d)\n",fdError());
        goto leave;
    }

    /* Try to receive the data */
    for(;;)
    {
        rc = recv (s2, buffer, 127, MSG_PEEK);

        if (rc >= 0)
        {
            ConPrintf("TEST PASSED: Successful PEEK read (%d bytes)\n",rc);
            buffer[rc]=0;
            if (rc)
                ConPrintf("Data Receieved = '%s'\n",buffer);
        }
        else
        {
            ConPrintf("TEST FAILED: PEEK Read returned %d, error = %d\n",rc,fdError());
            break;
        }

        rc = recv (s2, buffer, 127, 0);

        if (rc >= 0)
        {
            ConPrintf("TEST PASSED: Successful read (%d bytes)\n",rc);
            buffer[rc]=0;
            if (rc)
                ConPrintf("Data Received = '%s'\n",buffer);
            else
                break;
        }
        else
        {
            ConPrintf("TEST FAILED: Read returned %d, error = %d\n",rc,fdError());
            break;
        }
    }

leave:
    if (s2 != INVALID_SOCKET)
        fdClose(s2);
    if (s1 != INVALID_SOCKET)
        fdClose(s1);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests Shutdown() API on a V6 TCP 
 *      socket with write condition; i.e., it checks if a
 *      TCP socket which is shutdown for write/send can 
 *      receive data correctly.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the host to which the connection is done.
 *      This should be one of the local bind address.
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPShutdownWriteAPITest (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    SOCKET  s3 = INVALID_SOCKET;
    char    buffer[128];
    struct  sockaddr_in6 sin1;
    int     rc,size;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING Shutdown (write) condition \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket1 */
    if ((s1 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET )
    {
        ConPrintf("TEST Failed: Socket create error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(4000);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Bind the socket */
    if (bind (s1, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Bind error (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if (listen (s1, 1) < 0)
    {
        ConPrintf("TEST FAILED: Listen failure (%d)\n",fdError());
        goto leave;
    }

    /* Create test socket2 */
    if ((s2 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: Socket2 Create error (%d)\n",fdError());
        goto leave;
    }

    /* Connect the socket */
    if (connect (s2, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Connect failure (%d)\n",fdError());
        goto leave;
    }

    /* Shut down the write side, i.e. disallow any more "send" 
     * using this socket
     */
    if (shutdown (s2, SHUT_WR) < 0)
    {
        ConPrintf("TEST FAILED: Shutdown error (%d)\n",fdError());
        goto leave;
    }

    /* Get the accept socket */
    size = sizeof (sin1);
    if ((s3 =  accept(s1, (PSA)&sin1, &size)) == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: Accept error (%d)\n",fdError());
        goto leave;
    }

    /* Send some test data on s3 */
    if (send (s3, "Hello World", 11, 0) < 0)
    {
        ConPrintf("TEST FAILED: Send Error (%d)\n",fdError());
        goto leave;
    }

    /* Close test socket3 */
    fdClose (s3);
    s3 = INVALID_SOCKET;

    /* We should still be able to read data on s2, 
     * although "Write/Send" is shutdown on this socket.
     */
    for(;;)
    {
        rc = recv (s2, buffer, 127, MSG_PEEK);

        if (rc >= 0)
        {
            ConPrintf("TEST PASSED: Successful PEEK read (%d bytes)\n",rc);
            buffer[rc]=0;
            if (rc)
                ConPrintf("Data Read = '%s'\n",buffer);
        }
        else
        {
            ConPrintf("TEST FAILED: PEEK Read returned %d, error = %d\n",rc,fdError());
            break;
        }

        rc = recv (s2, buffer, 127, 0);

        if (rc >= 0)
        {
            ConPrintf("TEST PASSED: Successful read (%d bytes)\n",rc);
            buffer[rc]=0;
            if (rc)
                ConPrintf("Data Read= '%s'\n",buffer);
            else
                break;
        }
        else
        {
            ConPrintf("TEST FAILED: Read returned %d, error = %d\n",rc,fdError());
            break;
        }
     }

leave:
     if (s2 != INVALID_SOCKET)
         fdClose(s2);
     if (s1 != INVALID_SOCKET)
         fdClose(s1);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests if a V6 socket can be reused
 *      across multiple connect() calls with different
 *      parameters.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6ReuseTest (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING Socket reuse across multiple connect() with different params \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket */
    if ((s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket create error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(12345);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Connect the socket */
    ConPrintf("Connecting to local port 12345 (should fail)\n");
    if (connect (s, (PSA)&sin1, sizeof(sin1)) >=0)
    {
        ConPrintf("TEST FAILED: First connect passed unexpectedly - abort\n");
        goto leave;
    }

    ConPrintf("Connect failed (%d)\n",fdError());

    /* Change the connect port to 7. We should have a local TCP echo server
     * listening on that port.
     */
    sin1.sin6_port        = htons(7);

    /* Connect the socket again */
    ConPrintf("Connecting to local port 7 (should pass)\n");
    if (connect (s, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Connect failed with error (%d)\n",fdError());
        goto leave;
    }

    ConPrintf("TEST PASSED: Connect Passed\n");

leave:
    if (s != INVALID_SOCKET)
        fdClose( s );
}

/** 
 *  @b Description
 *  @n  
 *      Task that handles data reception on a shared socket.
 *      It tries to receive data on the shared socket and 
 *      repeats this test TEST_ITER number of times.
 *
 *  @param[in]  hTaskParent
 *      Handle to the parent task.
 *      
 *  @param[in]  s
 *      Handle to the shared socket over which data is to be
 *      received.
 *
 *  @param[in]  pFlag
 *      Pointer to flags.
 *      
 *  @retval
 *      Not Applicable.
 */
/* ARGSUSED */
static void V6TcpShareRX (HANDLE hTaskParent, SOCKET s, int *pFlag)
{
    char    *pBufRx;
    UINT32  test,i,j;
    int     k;
    UINT32  startS, startMS;
    UINT32  endS, endMS;

    /* Create a new file descriptor table for this task. */
    fdOpenSession (TaskSelf());

    /* Here we'll "share" socket 's' to up its reference count */
    fdShare(s);

    ConPrintf("RX Child task spawned successfully\n");

    startS = llTimerGetTime( &startMS );

    /* Allocate a working buffer */
    if (!(pBufRx = mmBulkAlloc(8192)))
    {
        ConPrintf("TX Child failed temp buffer allocation\n");
        goto leave;
    }

    /* Start Test */
    test = 8192;
    i = 0;
    for (j=0; j<TEST_ITER; j++)
    {
        /* Try and receive the buffer */
        while (i < test)
        {
            k = recv (s, pBufRx, test, 0);
            if (k < 0)
            {
                ConPrintf("TEST FAILED: RX Child recv failed (%d)\n",fdError());
                goto leave;
            }
            if (!k)
            {
                ConPrintf("TEST FAILED: RX Child connection dropped\n");
                goto leave;
            }
            i += (UINT32)k;
        }
        i -= test;
    }

    /* Verify reception size */
    if (i != 0)
        ConPrintf("TEST FAILED: RX Child received %d too many bytes\n",i);

    /* Test complete */
    if (j == TEST_ITER)
    {
        endS = llTimerGetTime( &endMS );
        endS -= startS;
        endS *= 1000;
        endMS += endS;
        endMS -= startMS;
        endS = (endMS+500)/1000;
        ConPrintf("TEST PASSED in %d ms, Data Rate: %d bytes/sec\n",endMS,(j*test)/endS);
    }

    /* Closing our socket will eventually wake up our parent, but */
    /* we want to test shutdown first. We shutdown read as a stronger */
    /* form of the test. Shutting down write would cause the echo server */
    /* to close the socket, which is the same as calling close() from */
    /* our side. */
    shutdown(s, SHUT_RD);

    /* Small delay so we can see the main thread quitting immediately */
    /* after the "Passed" message */
    TaskSleep(2000);

leave:
    if (pBufRx)
        mmBulkFree(pBufRx);
    if (s != INVALID_SOCKET)
        fdClose (s);

    fdCloseSession (TaskSelf());
    TaskExit();
}

/** 
 *  @b Description
 *  @n  
 *      Task that handles data transmission on a shared socket.
 *      It tries to send data TEST_ITER number of times whenevr 
 *      woken up on the shared socket.
 *
 *  @param[in]  hTaskParent
 *      Handle to the parent task.
 *      
 *  @param[in]  s
 *      Handle to the shared socket over which data is to be
 *      received.
 *
 *  @retval
 *      Not Applicable.
 */
/* ARGSUSED */
static void V6TcpShareTX( HANDLE hTaskParent, SOCKET s )
{
    UINT32  test,i;
    char    *pBuf = 0;

    /* Create a new file descriptor table for this task. */
    fdOpenSession (TaskSelf());

    /* Here we'll "share" socket 's' to up its reference count */
    fdShare(s);

    ConPrintf("TX Child task spawned successfully\n");

    /* Allocate a working buffer */
    if (!(pBuf = mmBulkAlloc( 8192 )))
    {
        ConPrintf("TEST FAILED: TX Child Task failed temp buffer allocation\n");
        goto leave;
    }

    /* Start Test - Just Send */
    test = 8192;
    for (i=0; i<TEST_ITER; i++)
    {
        /* Send the buffer */
        if (send(s, pBuf, (int)test, 0 ) < 0)
        {
            ConPrintf("TX Child send failed (%d)\n",fdError());
            break;
        }
    }

leave:
    /* Clean up and exit */
    if (pBuf)
        mmBulkFree( pBuf );
    if (s != INVALID_SOCKET)
        fdClose(s);

    fdCloseSession( TaskSelf() );
    TaskExit();
}

/** 
 *  @b Description
 *  @n  
 *      This function tests for socket sharing between 2 tasks.
 *      It creates a sender and receiver tasks that using the same
 *      socket pass back and forth data in a loop for TEST_ITER number
 *      of times.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6ShareTest (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    struct  timeval timeout;
    fd_set  xbits;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING V6 TCPEcho using Socket Sharing between 2 tasks \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket */
    if ((s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket Create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(7);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect socket */
    if (connect(s,(PSA)&sin1,sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Connect failed with (%d)\n",fdError());
        goto leave;
    }

    /* Create a thread to receive data */
    if (!TaskCreate(V6TcpShareRX, "Receiver", OS_TASKPRINORM, 0x1000,
                     (UINT32)TaskSelf(), (UINT32)s, 0 ))
        goto leave;

    /* Create a thread to send us data */
    if(!TaskCreate (V6TcpShareTX, "Sender", OS_TASKPRINORM, 0x1000,
                (UINT32)TaskSelf(), (UINT32)s, 0))
        goto leave;

    ConPrintf("Main task waiting with select() for test to complete\n");
    FD_ZERO (&xbits);
    FD_SET (s, &xbits);
    fdSelect ((int)s, 0, 0, &xbits, 0);

leave:
    if (s != INVALID_SOCKET)
        fdClose(s);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests socket read/select timeout using a 
 *      test TCP socket and recv() API with SO_RCVTIMEO set and
 *      fdselect() APIs with timeout set.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TimeoutTest(void)
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    char    Buffer[32];
    struct  timeval timeout;
    fd_set  ibits;
    int     cnt;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING V6 socket timeout using fdselect()/recv() APIs \n");

    /* Create test socket */
    if((s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Bind socket to port 12345 (we don't want any data) */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(12345);
    if(bind(s,(PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Socket bind failed with error: (%d)\n",fdError());
        goto leave;
    }

    ConPrintf("\nSetting fdSelect() timeout to 2 sec (1s + 1000000uS)\n");

    timeout.tv_sec  = 1;
    timeout.tv_usec = 1000000;

    FD_ZERO(&ibits);
    FD_SET(s, &ibits);

    ConPrintf("Calling fdSelect() ...");
    cnt = fdSelect ((int)s,&ibits,0,0,&timeout);
    if (!cnt)
        ConPrintf(" timeout!\n");
    else
        ConPrintf(" input data detected - error!\n");

    ConPrintf("\nCalling fdSelect() [with no descriptors]...");
    cnt = fdSelect ((int)s, 0, 0, 0, &timeout);
    if (!cnt)
        ConPrintf("timeout!\n");
    else
        ConPrintf("input data detected - error!\n");

    ConPrintf("\nSetting recv() timeout to 2 sec (1s + 1000000uS)\n");

    setsockopt (s,SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    ConPrintf("Calling recv() ...");
    cnt = recv (s, Buffer, 32, 0);
    if (cnt < 0)
    {
        if (fdError() == EWOULDBLOCK)
            ConPrintf(" timeout!\n");
        else
            ConPrintf(" unexpected error %d\n",fdError());
    }
    else
        ConPrintf(" input data detected - error!\n");

leave:
    if(s != INVALID_SOCKET)
        fdClose (s);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests connect using non-blocking I/O.
 *      It tries connecting to a TCP server on port 7 continuously and checks 
 *      if the connect returns with an error in time, if it does it dumps 
 *      the error and quits the test.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPConnectAPITest1 (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    int     tmp;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING V6 TCP Non-blocking connect by polling on it continuously \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket */
    if ((s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(7);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Setup the socket for non-blocking */
    tmp = 0;
    setsockopt (s, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof(tmp));

    /* Connect socket */
    while (connect(s, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        tmp = fdError();

        if( tmp == EINPROGRESS )
            ConPrintf("Connect returned EINPROGRESS\n");
        else if (tmp == EALREADY)
            ConPrintf("Connect returned EALREADY\n");
        else if (tmp == EISCONN)
        {
            ConPrintf("Connect returned EISCONN\n");
            break;
        }
        else if (tmp == ETIMEDOUT)
        {
            ConPrintf("Connect returned ETIMEDOUT\n");
            break;
        }
        else if (tmp == ECONNREFUSED)
        {
            ConPrintf("Connect returned ECONNREFUSED\n");
            break;
        }
        else
        {
            ConPrintf("Connect returned (unexpected) %d\n",tmp);
            break;
        }
        TaskSleep( 100 );
    }

    if (!tmp)
        ConPrintf("Connect returned success (IP address was local?)\n");

leave:
    if (s != INVALID_SOCKET)
        fdClose(s);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests connect using non-blocking I/O. 
 *      If the IPv6 Address passed to this function is loopback then
 *      the connect passes successfully, however on any other V6 address
 *      on which there is no server listening on port 7, the connect
 *      would timeout and we would have to retry.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPConnectAPITest2(int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    int     tmp;
    struct  timeval timeout;
    fd_set  obits;
    int     cnt;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING V6 TCP Non-blocking connect using timeout, i.e. fdselect() \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create the test socket */
    if ((s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(7);
    sin1.sin6_scope_id  = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Setup the socket for non-blocking read/write */
    tmp = 0;
    setsockopt(s, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof(tmp));

    /* Connect socket */
    if (connect( s, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        tmp = fdError();

        if (tmp != EINPROGRESS)
        {
            ConPrintf("Connect returned error %d\n",tmp);
            goto leave;
        }

        ConPrintf("Connect returned EINPROGRESS\n");
        ConPrintf("Setting fdSelect() timeout to 8 seconds\n");

        timeout.tv_sec  = 8;
        timeout.tv_usec = 0;

        FD_ZERO(&obits);
        FD_SET(s,&obits);

        cnt = fdSelect((int)s, 0, &obits, 0, &timeout);
        if (!cnt)
            ConPrintf("Connection timeout!\n");
        else
        {
            ConPrintf("Socket reports writable\n");
            if (connect( s, (PSA) &sin1, sizeof(sin1)) < 0)
            {
                tmp = fdError();

                if (tmp == EISCONN)
                {
                    ConPrintf("Connect returned EISCONN\n");
                    goto leave;
                }
                else  if (tmp == ECONNREFUSED)
                {
                    ConPrintf("Connect returned ECONNREFUSED\n");
                    goto leave;
                }
                ConPrintf("Connect returned error %d\n",tmp);
            }
        }

        ConPrintf("Connect failed\n");
    }

    if (!tmp)
        ConPrintf("Connect returned success (IP address was local?)\n");

leave:
    if (s != INVALID_SOCKET)
        fdClose(s);
}


/** 
 *  @b Description
 *  @n  
 *      This tests tries to do a series of socket()/
 *      connect() API calls to check for robustness.
 *      The test passes if all the iterations of socket/connect
 *      calls succeeds. It tries to connect to a TCP server
 *      on port 7 of the destination address passed to this
 *      function.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPConnectFlood(int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    int     i;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    ConPrintf ("TESTING V6 TCP Connect (TIMEWAIT state) flood \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    for (i=0; i<1000; i++)
    {
        /* Create the test socket */
        if ((s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
            ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
            goto leave;
        }

        /* Prepare address for connect */
        bzero (&sin1, sizeof(struct sockaddr_in6));
        sin1.sin6_family      = AF_INET6;
        sin1.sin6_port        = htons(7);
        sin1.sin6_scope_id    = ScopeId;
        mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

        /* Connect socket */
        if (connect(s, (PSA) &sin1, sizeof(sin1)) < 0)
        {
            ConPrintf("failed socket connect (%d)\n",fdError());
            goto leave;
        }

        fdClose(s);

        /* We still need to give the timer loop some time to run */
        TaskSleep( 6 );
    } /* end of for (i=0; i<1000; i++) */

leave:
    if( i < 1000 )
        ConPrintf("TEST FAILED on iteration %d\n",i);
    else
        ConPrintf("TEST PASSED with %d iterations\n",i);

    if(s != INVALID_SOCKET)
        fdClose(s);
}

/** 
 *  @b Description
 *  @n  
 *      Task to close the shared listening socket.
 *
 *  @param[in]  hTaskParent
 *      Handle to the parent task.
 *
 *  @param[in]  s
 *      Handle to the shared socket.
 *
 *  @retval
 *      Not Applicable.
 */
/* ARGSUSED */
static void V6CloseTask( HANDLE hTaskParent, SOCKET s )
{
    fdOpenSession( TaskSelf() );

    ConPrintf("Child task spawned successfully - Calling fdClose()\n");

    /* Shutting down listen for read should wake our parent */
    fdClose(s);

    /* Small delay so we can see the main thread quitting immediately
     * after the "Passed" message
     */
    TaskSleep(2000);

    fdCloseSession(TaskSelf());
    TaskExit();
}

/** 
 *  @b Description
 *  @n  
 *      Task to shutdown the Read side of shared 
 *      listening socket.
 *
 *  @param[in]  hTaskParent
 *      Handle to the parent task.
 *
 *  @param[in]  s
 *      Handle to the shared socket.
 *
 *  @retval
 *      Not Applicable.
 */
/* ARGSUSED */
static void V6ShutdownTask( HANDLE hTaskParent, SOCKET s )
{
    fdOpenSession( TaskSelf() );

    ConPrintf("Child task spawned successfully - Calling shutdown()\n");

    /* Shutting down listen for read should wake our parent */
    shutdown(s, SHUT_RD);

    /* Small delay so we can see the main thread quitting immediately
     * after the "Passed" message
     */
    TaskSleep(2000);

    fdCloseSession( TaskSelf() );
    TaskExit();
}

/** 
 *  @b Description
 *  @n  
 *      This function tests shutdown()/close() APIs on a 
 *      V6 TCP listening socket. It validates the socket shutdown
 *      by using accept() call on the shutdown socket and making
 *      sure an error is returned.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *  @param[in]  fClose
 *      Flags to indicate whether to run test using fdClose() API / shutdown() API.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPShutdownTest1(int ntok, char* strIPAddress, char* ptrScopeId, int fClose)
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    int     size,tmp;
    struct  sockaddr_in6 sin1;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    if (fClose)
        ConPrintf("TESTING fdClose() API on V6 TCP Socket in Listen state using Accept \n");
    else
        ConPrintf("TESTING shutdown() API on V6 TCP Socket in Listen state using Accept \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket1 */
    if ((s1 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(12345);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Bind the socket to port 12345 */
    if (bind(s1, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Socket bind failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if (listen(s1, 1) < 0)
    {
        ConPrintf("TEST FAILED: Socket listen failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Setup for non-blocking */
    tmp = 0;
    setsockopt(s1, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof(tmp));

    ConPrintf("Calling non-blocking Accept()...\n");
    size = sizeof(sin1);
    if((s2 = accept(s1, (PSA)&sin1, &size)) != INVALID_SOCKET)
        ConPrintf("Accept returned a socket - This is an error\n");

    if (fdError() == EWOULDBLOCK)
        ConPrintf("Accept correctly returned EWOULDBLOCK\n");
    else
        ConPrintf("Accept returned bad error code\n");

    ConPrintf("Calling blocking Accept()...\n");

    /* Setup for blocking */
    tmp = 1;
    setsockopt(s1, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof(tmp));

    /* Create a thread to close or shutdown this socket */
    if (fClose)
    {
        if( !TaskCreate( V6CloseTask, "CloseTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }
    else
    {
        if( !TaskCreate( V6ShutdownTask, "ShutdownTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }

    /* Try accepting the closed socket. Must return an error. */
    size = sizeof(sin1);
    if((s2 = accept(s1, (PSA)&sin1, &size)) != INVALID_SOCKET)
        ConPrintf("TEST FAILED: Accept returned a socket - This is an error\n");

    tmp = fdError();
    if (tmp==EBADF && fClose)
    {
        ConPrintf("TEST PASSED: Accept correctly returned EBADF\n");
        s1 = INVALID_SOCKET;
    }
    else if (tmp==ECONNABORTED && !fClose)
        ConPrintf("TEST PASSED: Accept correctly returned ECONNABORTED\n");
    else
        ConPrintf("Accept returned unexpected error code (%d)\n",tmp);

leave:
     if (s2 != INVALID_SOCKET)
         fdClose(s2);
     if (s1 != INVALID_SOCKET)
         fdClose(s1);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests shutdown()/close() APIs on a 
 *      V6 TCP listening socket. It validates the socket shutdown
 *      by using fdSelect() call on the shutdown socket and making
 *      sure an error is returned. 
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *  @param[in]  fClose
 *      Flags to indicate whether to run test using fdClose() API / shutdown() API.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPShutdownTest2(int ntok, char* strIPAddress, char* ptrScopeId, int fClose)
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    int     tmp,cnt,size;
    fd_set  ibits;
    struct  sockaddr_in6 sin1;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    /* Let the world know what we are testing. */
    ConPrintf ("------------------------\n");
    if (fClose)
        ConPrintf("TESTING fdClose() API on V6 TCP Socket in Listen state using fdSelect \n");
    else
        ConPrintf("TESTING shutdown() API on V6 TCP Socket in Listen state using fdSelect \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket1 */
    if ((s1 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(12345);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Bind the socket */
    if (bind(s1, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Socket bind failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if (listen(s1, 1) < 0)
    {
        ConPrintf("TEST FAILED: Socket listen failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Create a thread to close or shutdown this socket */
    if (fClose)
    {
        if( !TaskCreate( V6CloseTask, "CloseTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }
    else
    {
        if( !TaskCreate( V6ShutdownTask, "ShutdownTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }

    FD_ZERO(&ibits);
    FD_SET(s1, &ibits);

    ConPrintf("Calling fdSelect() on shutdown socket ...\n");
    cnt = fdSelect( (int)s1, &ibits, 0, 0, 0 );

    if (!cnt)
        ConPrintf("Select returned NULL - This is an error\n");
    if (cnt < 0)
    {
        tmp = fdError();
        if (fClose && tmp == EBADF)
        {
            ConPrintf("TEST PASSED: fdSelect correctly returned EBADF\n");
            s1 = INVALID_SOCKET;
        }
        else
            ConPrintf("fdSelect returned unexpected error code (%d)\n",tmp);
    }
    else
    {
        if (fClose)
            ConPrintf("Error: we should not be here!\n");

        if (FD_ISSET(s1, &ibits))
        {
            ConPrintf("Socket is now readable\n");

            size = sizeof(sin1);
            if((s2 = accept(s1, (PSA)&sin1, &size)) != INVALID_SOCKET)
                ConPrintf("TEST FAILED: Accept returned a socket - This is an error\n");

            if (fdError() == ECONNABORTED)
                ConPrintf("TEST PASSED: Accept correctly returned ECONNABORTED\n");
            else
                ConPrintf("Accept returned bad error code\n");
        }
    }

leave:
     if (s2 != INVALID_SOCKET)
         fdClose(s2);
     if (s1 != INVALID_SOCKET)
         fdClose(s1);
}

/** 
 *  @b Description
 *  @n  
 *      This function tests various status conditions of file
 *      descriptors. TCP, UDP sockets and Pipes are used in this
 *      test.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6StatusTest (int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET stcpl      = INVALID_SOCKET;
    SOCKET stcp_peer  = INVALID_SOCKET;
    SOCKET stcp_child = INVALID_SOCKET;
    SOCKET stcp       = INVALID_SOCKET;
    SOCKET sudp       = INVALID_SOCKET;
    SOCKET pipe1      = INVALID_SOCKET;
    SOCKET pipe2      = INVALID_SOCKET;
    struct  sockaddr_in6 sin1;
    int    error,status,size;
    char   *buffer;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    buffer = mmAlloc(1024);
    if (!buffer)
    {
        ConPrintf("TEST FAILED: Error allocating temp buffer\n");
        goto leave;
    }

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create TCP listen socket */
    if ((stcpl = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_scope_id    = ScopeId;    
    sin1.sin6_port        = htons(12345);
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Bind the socket */
    if (bind(stcpl, (PSA)&sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Error binding socket (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if (listen( stcpl, 1) < 0)
    {
        ConPrintf("TEST FAILED: Socket listen failed with error (%d)\n",fdError());
        goto leave;
    }

    /*
     * Setting socket buffer sizes on a listening socket only
     * affects spawned sockets returned from accept()
     */

    /* Set the TCP TX buffer to 1234 */
    size = 1234;
    if (setsockopt(stcpl, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size)))
    {
        ConPrintf("TEST FAILED: setsockopt returned error (%d)\n",fdError());
        goto leave;
    }

    /* Set the TCP RX buffer to 4321 */
    size = 4321;
    if (setsockopt(stcpl, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)))
    {
        ConPrintf("TEST FAILED: setsockopt returned error (%d)\n",fdError());
        goto leave;
    }

    /* Create UDP socket */
    if ((sudp = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: UDP Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Set the UDP RX buffer to 1024 */
    size = 1024;
    if (setsockopt( sudp, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)))
    {
        ConPrintf("TEST FAILED: setsockopt returned error (%d)\n",fdError());
        goto leave;
    }

    /* Bind the socket */
    if (bind(sudp, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Socket bind returned error (%d)\n",fdError());
        goto leave;
    }

    /* Connect the socket (to the same address) */
    if (connect(sudp, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Connect failed to itself (%d)\n",fdError());
        goto leave;
    }

    /* Create the pipes */
    if (pipe(&pipe1, &pipe2) != 0)
    {
        ConPrintf("TEST FAILED: Pipe create failed\n");
        goto leave;
    }

    /* Create a TCP peer socket */
    if ((stcp_peer = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: TCP socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    ConPrintf("\nSocket Type Check\n");
    error = fdStatus( stcpl, FDSTATUS_TYPE, &status );
    ConPrintf("stcpl type is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_TYPE, &status );
    ConPrintf("sudp type is %d\n",status);
    error |= fdStatus( pipe1, FDSTATUS_TYPE, &status );
    ConPrintf("pipe1 type is %d\n",status);
    error |= fdStatus( stcp_peer, FDSTATUS_RECV, &status );
    ConPrintf("stcp_peer (unconnected) recv status = %d\n",status);
    error |= fdStatus( stcp_peer, FDSTATUS_SEND, &status );
    ConPrintf("stcp_peer (unconnected) send status = %d\n",status);

    ConPrintf("\nListening Status Check\n");

    /* Get status of listen socket for recv */
    error |= fdStatus( stcpl, FDSTATUS_RECV, &status );
    ConPrintf("stcpl connection available = %d\n",status);

    ConPrintf("Calling connect...\n");
    if( connect( stcp_peer, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("TEST FAILED: Socket connect failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Get status of listen socket for recv */
    error |= fdStatus( stcpl, FDSTATUS_RECV, &status );
    ConPrintf("stcpl connection available = %d\n",status);

    ConPrintf("Calling accept...\n");
    size = sizeof( sin1 );
    stcp_child = accept( stcpl, (PSA)&sin1, &size );
    if( stcp_child == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: Socket accept failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Get status of listen socket for recv */
    error |= fdStatus( stcpl, FDSTATUS_RECV, &status );
    ConPrintf("stcpl connection available = %d\n",status);

    /* Get some socket buffer status */
    size = sizeof(size);
    error |= getsockopt(stcp_peer, SOL_SOCKET, SO_SNDBUF, &status, &size);
    ConPrintf("\nstcp_peer TCP send buffer size is %d\n",status);
    error |= getsockopt(stcp_peer, SOL_SOCKET, SO_RCVBUF, &status, &size);
    ConPrintf("stcp_peer TCP recv buffer size is %d\n",status);
    error |= getsockopt(stcp_child, SOL_SOCKET, SO_SNDBUF, &status, &size);
    ConPrintf("stcp_child TCP send buffer size is %d\n",status);
    error |= getsockopt(stcp_child, SOL_SOCKET, SO_RCVBUF, &status, &size);
    ConPrintf("stcp_child TCP recv buffer size is %d\n",status);
    error |= getsockopt(sudp, SOL_SOCKET, SO_SNDBUF, &status, &size);
    ConPrintf("sudp UDP send buffer size is %d\n",status);
    error |= getsockopt(sudp, SOL_SOCKET, SO_RCVBUF, &status, &size);
    ConPrintf("sudp UDP recv buffer size is %d\n",status);

    /* Get some other status */
    ConPrintf("\nCurrent RECV/SEND Status\n");
    error |= fdStatus( stcp_child, FDSTATUS_RECV, &status );
    ConPrintf("stcp_child recv status is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_RECV, &status );
    ConPrintf("sudp recv status is %d\n",status);
    error |= fdStatus( pipe2, FDSTATUS_RECV, &status );
    ConPrintf("pipe2 recv status is %d\n",status);

    error |= fdStatus( stcp_peer, FDSTATUS_SEND, &status );
    ConPrintf("stcp_peer send status is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_SEND, &status );
    ConPrintf("sudp send status is %d\n",status);
    error |= fdStatus( pipe1, FDSTATUS_SEND, &status );
    ConPrintf("pipe1 send status is %d\n",status);

    /* Send 1024 bytes to everyone */
    ConPrintf("\nCalling Send Data...\n");
    send( stcp_peer, buffer, 1024, 0 );
    send( sudp, buffer, 1024, 0 );
    send( pipe1, buffer, 1024, 0 );

    ConPrintf("\nCurrent RECV/SEND Status\n");
    error |= fdStatus( stcp_child, FDSTATUS_RECV, &status );
    ConPrintf("stcp_child recv status is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_RECV, &status );
    ConPrintf("sudp recv status is %d\n",status);
    error |= fdStatus( pipe2, FDSTATUS_RECV, &status );
    ConPrintf("pipe2 recv status is %d\n",status);

    error |= fdStatus( stcp_peer, FDSTATUS_SEND, &status );
    ConPrintf("stcp_peer send status is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_SEND, &status );
    ConPrintf("sudp send status is %d\n",status);
    error |= fdStatus( pipe1, FDSTATUS_SEND, &status );
    ConPrintf("pipe1 send status is %d\n",status);

    /* Recv 1024 bytes from everyone */
    ConPrintf("\nCalling Recv Data...\n");
    recv( stcp_child, buffer, 1024, 0 );
    recv( sudp, buffer, 1024, 0 );
    recv( pipe2, buffer, 1024, 0 );

    ConPrintf("\nCurrent RECV/SEND Status\n");
    error |= fdStatus( stcp_child, FDSTATUS_RECV, &status );
    ConPrintf("stcp_child recv status is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_RECV, &status );
    ConPrintf("sudp recv status is %d\n",status);
    error |= fdStatus( pipe2, FDSTATUS_RECV, &status );
    ConPrintf("pipe2 recv status is %d\n",status);

    error |= fdStatus( stcp_peer, FDSTATUS_SEND, &status );
    ConPrintf("stcp_peer send status is %d\n",status);
    error |= fdStatus( sudp, FDSTATUS_SEND, &status );
    ConPrintf("sudp send status is %d\n",status);
    error |= fdStatus( pipe1, FDSTATUS_SEND, &status );
    ConPrintf("pipe1 send status is %d\n",status);

    /* Close peers */
    ConPrintf("\nCalling close on receive side (tcp_child and pipe2)\n");
    fdClose( stcp_child );
    stcp_child = INVALID_SOCKET;
    fdClose( pipe2 );
    pipe2 = INVALID_SOCKET;

    ConPrintf("\nCurrent RECV/SEND Status\n");
    error |= fdStatus( stcp_peer, FDSTATUS_RECV, &status );
    ConPrintf("stcp_peer recv status is %d\n",status);
    error |= fdStatus( pipe1, FDSTATUS_RECV, &status );
    ConPrintf("pipe1 recv status is %d\n",status);

    error |= fdStatus( stcp_peer, FDSTATUS_SEND, &status );
    ConPrintf("stcp_peer send status is %d\n",status);
    error |= fdStatus( pipe1, FDSTATUS_SEND, &status );
    ConPrintf("pipe1 send status is %d\n",status);

    if (!error)
        ConPrintf("\nTest Complete - No errors detected\n\n");
    else
        ConPrintf("\nTest Completed with Errors!\n\n");

leave:
    if (stcpl != INVALID_SOCKET)
        fdClose(stcpl);
    if (stcp_peer  != INVALID_SOCKET)
        fdClose(stcp_peer);
    if (stcp_child != INVALID_SOCKET)
        fdClose(stcp_child);
    if (stcp       != INVALID_SOCKET)
        fdClose(stcp);
    if (sudp       != INVALID_SOCKET)
        fdClose(sudp);
    if (pipe1      != INVALID_SOCKET)
        fdClose(pipe1);
    if (pipe2      != INVALID_SOCKET)
        fdClose(pipe2);

    if (buffer)
        mmFree(buffer);
}

/** 
 *  @b Description
 *  @n  
 *      Task to handle data reception over shared UDP socket.
 *
 *  @param[in]  s
 *      Handle to the shared V6 UDP socket.
 *
 *  @param[in] index
 *     Index to identify receiver task.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6UdpShareRX( SOCKET s, int index )
{
    int i;
    UINT8 buffer[32];

    fdOpenSession( TaskSelf() );

    ConPrintf("RX Child task %d spawned successfully\n",index);

    for(;;)
    {
        i= recv( s, buffer, 32, 0 );

        if( i < 0 )
        {
            ConPrintf("RX child task %d recv failed (%d)\n",index,fdError());
            break;
        }

        ConPrintf("RX child task %d received %d bytes\n",index,i);
    }

    fdCloseSession( TaskSelf() );
    TaskExit();
}

/** 
 *  @b Description
 *  @n  
 *      This function tests V6 UDP socket for sharing between
 *      various threads.
 *
 *  @param[in]  ntok
 *      Number of tokens
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host
 *  @param[in]  ptrScopeId
 *      Scope Identifier.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6UDPShareRxTest(int ntok, char* strIPAddress, char* ptrScopeId) 
{
    SOCKET  s = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    struct  sockaddr_in6 sin1;
    int     i;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    ConPrintf ("------------------------\n");
    ConPrintf("TESTING V6 UDP Socket sharing \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create test socket1 */
    if ((s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero (&sin1, sizeof(struct sockaddr_in6));
    sin1.sin6_family      = AF_INET6;
    sin1.sin6_port        = htons(1234);
    sin1.sin6_scope_id    = ScopeId;
    mmCopy ((void *)&sin1.sin6_addr.s6_addr, (void *)&PeerAddress, sizeof(IP6N));

    /* Connect socket */
    if (bind(s, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf("TEST FAILED: Socket bind failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Create a thread to receive data */
    if( !TaskCreate( V6UdpShareRX, "Receiver", OS_TASKPRINORM, 0x1000,
                     (UINT32)s, 1, 0 ) )
        goto leave;

    /* Create a second thread to receive data */
    if( !TaskCreate( V6UdpShareRX, "Receiver", OS_TASKPRINORM, 0x1000,
                     (UINT32)s, 2, 0 ) )
        goto leave;

    for (i=0; i<3; i++)
    {
        ConPrintf("Sender sleeping...\n");
        TaskSleep(3000);

        ConPrintf("Sender sending...\n");

        /* Create test socket */
        if ((s2 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP))  == INVALID_SOCKET)
        {
            ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
            goto leave;
        }

        /* Send data to receiver threads */
        sendto (s2, (UINT8 *)&s2, 4, 0,(PSA)&sin1, sizeof(sin1));

        fdClose (s2);
    }

    ConPrintf("Sender sleeping...\n");
    TaskSleep(3000);

    ConPrintf("Sender closing...\n");

leave:
    if (s != INVALID_SOCKET)
        fdClose (s);
    ConPrintf("== End Shared UDP Echo Test ==\n\n");
}

/** 
 *  @b Description
 *  @n  
 *      The function tests the OOB on IPv6 TCP Sockets. 
 *
 *  @param[in]  strIPAddress
 *      IPv6 Address of the destination host in string format.
 *      By default, this is loopback address.
 *
 *  @param[in]  fInline
 *      Flags to indicate whether to connect Inline or not.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TCPOOBTest(int ntok, char* strIPAddress, char* ptrScopeId, uint fInline )
{
    SOCKET  s;
    struct  sockaddr_in6 sin1;
    int     test,i;
    char    buf[48];
    struct  timeval timeout;
    IP6N    PeerAddress;
    UINT32  ScopeId = 0;

    ConPrintf ("------------------------\n");
    ConPrintf("TESTING V6 TCP OOB Test \n");

    /* Convert the string IP address to IP6N format. */
    if (IPv6StringToIPAddress (strIPAddress, &PeerAddress) < 0)
    {
        ConPrintf ("Error: Invalid IP Address specified\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(PeerAddress) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 2) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Create the test socket */
    if ((s =  socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET )
    {
        ConPrintf("TEST FAILED: Socket create failed with error (%d)\n",fdError());
        goto leave;
    }

    /* Prepare the address for connecting */
    bzero( &sin1, sizeof(struct sockaddr_in6) );
    sin1.sin6_family    = AF_INET6;
    sin1.sin6_port      = htons(999);
    sin1.sin6_scope_id  = ScopeId;

    mmCopy (&sin1.sin6_addr,(void *)&PeerAddress, sizeof(struct in6_addr));

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /*
     * Sending a single byte to *OUR* ECHO server will trigger the OOB
     * test. This test will fail if connected to a generic echo server
     */
    if( !fInline )
        ConPrintf("\nConnected in NORMAL mode\n");
    else
    {
        ConPrintf("\nConnected in INLINE mode\n");

        /* Setup socket for "inline" OOB data */
        i = 1;
        if( setsockopt( s, SOL_SOCKET, SO_OOBINLINE, (char * )&i, sizeof(i) ) < 0 )
        {
            ConPrintf("TEST FAILED: setsockopt failed with error (%d)\n",fdError());
            goto leave;
        }
    }

    /* Connect the socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("TEST FAILED: Socket connect failed with error (%d)\n",fdError());
        goto leave;
    }

    /* We need to sleep for a bit to make sure all the packets get here */
    TaskSleep( 2*1000 );

    /* Call receive without the OOB flag
     * This should return all the data bytes up to the OOB mark.
     */
    if( (test = recv( s, buf, sizeof(buf), 0 )) < 0 )
        ConPrintf("failed read 1 (%d)\n",fdError());
    else
    {
        ConPrintf("Received %d normal bytes ( ",test);
        for( i=0; i<test; i++ )
            ConPrintf("%d ",*(buf+i));

        ConPrintf(")\n");
    }

    /* Call receive with the OOB flag
     * This should return a single OOB data byte in NORMAL
     * mode, and an error in INLINE mode
     */
    if( (test=recv( s, buf, sizeof(buf), MSG_OOB )) < 0 )
    {
        if( !fInline )
            ConPrintf("failed read 2 (%d)\n",fdError());
    }
    else
    {
        if( fInline )
            ConPrintf("read 2 passed - should have failed\n");
        ConPrintf("Received %d OOB byte(s) (%d)\n",test,*buf);
    }


    /* Call receive without the OOB flag
     * This should return remainder of the data in the buffer
     */
    if((test = recv( s, buf, sizeof(buf), 0 )) < 0)
        ConPrintf("failed read 3 (%d)\n",fdError());
    else
    {
        ConPrintf("Received %d normal bytes ( ",test);

        for( i=0; i<test; i++ )
            ConPrintf("%d ",*(buf+i));

        ConPrintf(")\n");
    }

leave:
    if (s != INVALID_SOCKET)
        fdClose(s);
}

/** 
 *  @b Description
 *  @n  
 *      The function tests the TFTP protocol over IPv6.
 *
 *  @retval
 *      Not Applicable.
 */
static void v6TestTFTP (int ntok, char* strIPAddress, char *File, char* ptrScopeId)
{
    int    rc;
    char   *buffer;
    UINT16 ErrorCode;
    UINT32 Size = 3000;
    IP6N   IPAddr;
    UINT32 ScopeId = 0;

    /* Convert the string IP Address to IP6N format */
    if (IPv6StringToIPAddress (strIPAddress, &IPAddr) < 0)
    {
        ConPrintf("Error: Invalid IP Address specified.\n");
        return;
    }

    /* Check if the address specified is Link Local? */
    if (IPv6IsLinkLocal(IPAddr) == 1)
    {
        /* Ensure that the scope id was specified? */
        if ((ntok != 3) || (ptrScopeId == NULL))
        {
            ConPrintf("Error: No scope identifier specified!\n");
            return;
        }

        /* Convert the Scope ID. */
        ScopeId = atoi (ptrScopeId);
    }

    /* Allocate memory for the buffer. */
    buffer = mmAlloc(Size);
    if( !buffer )
    {
        ConPrintf("\nFailed allocating temp buffer\n");
        return;
    }
   
    /* Initiate the TFTP Protocol to get the file.  */ 
    rc = Nt6TftpRecv(IPAddr, ScopeId, File, buffer, &Size, &ErrorCode );
    if( rc >= 0 )
    {
        /* File has been downloaded successfuly. */
        UINT32 i;
        int    c;

        ConPrintf("\nFile Retrieved: Size is %d\n",Size);

        /* Check if the file downloaded exceeds the buffer space? If so
         * we display only the requested file size. */
        if( !rc )
            Size = 3000;

        ConPrintf("\nDisplay (%d bytes) (y/n)\n",Size);
        do { c=ConGetCh(); }
            while( c != 'y' && c !='Y' && c != 'N' && c != 'n' );
        if( c=='Y' || c=='y' )
            for( i=0; i<Size; i++ )
                ConPrintf( "%c", *(buffer+i) );

        ConPrintf("\n");
    }
    else if( rc < 0 )
    {
        /* Error was detected in file download. */
        ConPrintf("\nTFTP Reported Error: %d\n",rc);
        if( rc == TFTPERROR_ERRORREPLY )
            ConPrintf("TFTP Server Error: %d (%s)\n",ErrorCode,buffer);
    }

    /* Cleanup the temporary buffer. */
    mmFree( buffer );
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function tests the IPv6 Conversion API i.e. IPv6StringToIPAddress 
 *      and IPv6IPAddressToString and verifies that the output generated by 
 *      these are correct.
 *
 *  @retval
 *      Not Applicable.
 */
static void V6TestIPv6ConversionAPI(void)
{
    IP6N    address;
    char    strIPAddress[40];

    ConPrintf ("-------------------------------\n");
    ConPrintf ("TESTING IPv6 Address Conversion\n");
 
    /* Loopback Address. */
    IPv6StringToIPAddress ("::1", &address);
    IPv6IPAddressToString (address, &strIPAddress[0]);
    if (strcmp (strIPAddress, "::1") != 0)
        ConPrintf ("Loopback Address: Fail\n");
    else
        ConPrintf ("Loopback Address: Success\n");

    /* Unspecified Address. */
    IPv6StringToIPAddress ("::", &address);
    IPv6IPAddressToString (address, &strIPAddress[0]);
    if (strcmp (strIPAddress, "::") != 0)
        ConPrintf ("Unspecified Address: Fail\n");
    else
        ConPrintf ("Unspecified Address: Success\n");

    /* Link Local Address not zero compressed. */
    IPv6StringToIPAddress ("fe80:0000:0000:0000:a00:9ff:fedc:fbdc", &address);
    IPv6IPAddressToString (address, &strIPAddress[0]);
    if (strcmp (strIPAddress, "fe80::a00:9ff:fedc:fbdc") != 0)
        ConPrintf ("Unicast (not Zero Compressed) Address: Fail\n");
    else
        ConPrintf ("Unicast (not Zero Compressed) Address: Success\n");

    /* Link Local Address Zero Compressed. */
    IPv6StringToIPAddress ("fe80::a00:9ff:fedc:fbdc", &address);
    IPv6IPAddressToString (address, &strIPAddress[0]);
    if (strcmp (strIPAddress, "fe80::a00:9ff:fedc:fbdc") != 0)
        ConPrintf ("Unicast (Zero Compressed) Address: Fail\n");
    else
        ConPrintf ("Unicast (Zero Compressed) Address: Success\n");

    /* Invalid Link Local Address */
    if (IPv6StringToIPAddress ("fe80:::a00:9ff:fedc:fbdc", &address) < 0)
        ConPrintf ("Invalid Unicast Address: Success\n");
    else
        ConPrintf ("Invalid Unicast Address: Fail\n");

    /* Global Address */
    IPv6StringToIPAddress ("4ffe::a00:1", &address);
    IPv6IPAddressToString (address, &strIPAddress[0]);    
    if (IPv6StringToIPAddress ("4ffe::a00:1", &address) < 0)
        ConPrintf ("Global Address: Fail\n");
    else
        ConPrintf ("Global Address: Success\n");
 
    return;
}

/**
 *  @b Description
 *  @n
 *      Deletes all non-local IPv6 routes on a specific interface.
 *
 *      Routes for local networks/addresses such as fe80::, ::1 and the IP
 *      address of the NDK will not be deleted.  Removing the route for any
 *      non-local network host will also clear that host's neighbor cache
 *      entry.
 *
 *  @param[in]  ptr_device
 *      Pointer to the device for which all routes will be cleaned.
 *
 *  @retval
 *      Not Applicable.
 */
static void flushNonLocalRoutes(NETIF_DEVICE* ptr_device)
{
    RT6_ENTRY* ptr_rt6;
    RT6_ENTRY* ptr_RoutingTable = NULL;
    char       strIPAddress[50];

    /* Get a reference to the routing table from the ROUTE6 Module. */
    ptr_RoutingTable = Rt6GetTable();

    /*
     * Cycle through all the routing entries in the IPv6 Routing Table and
     * clean out all routes for non-local hosts.
     */
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&ptr_RoutingTable);
    while (ptr_rt6 != NULL)
    {
        /*
         * Remove routes for non-local hosts
         *
         * Need to remove routes to other hosts, but not local ones
         * such as fe80::, ::1 and the IP address of the NDK
         */
        if ((ptr_rt6->Flags & FLG_RTE_HOST) &&
                !(ptr_rt6->Flags & FLG_RTE_IFLOCAL)) {

            /* Clean this route and notify the socket layer */
            IPv6IPAddressToString (ptr_rt6->NetworkAddr, &strIPAddress[0]);
            ConPrintf ("Removing route to non-local host %s\n", strIPAddress);
            Sock6PcbRtChange (ptr_rt6);
            Rt6Free (ptr_rt6);

            /* Removing the route changes the Routing Table; so we start again from the beginning. */
            ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&ptr_RoutingTable);
        }
        else {
            /* continue to the next route table element */
            ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
        }
    }
    return;
}

/**
 *  @b Description
 *  @n
 *      The function flushes the non-local routes from the IPv6 Routing Table
 *      for the specified interface.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6FlushNonLocalRoutes (char *ifId)
{
    UINT16 dev_index = 0;
    NETIF_DEVICE *ptr_device = NULL;

    /* get the device index; by first trying it to be an identifier. */
    dev_index = atoi(ifId);

    /* get the device corresponding to the interface ID passed in by the user */
    ptr_device = NIMUFindByIndex(dev_index);

    if (!ptr_device) {
        ConPrintf("Error: could not find device object for interface %d\n", dev_index);
        return;
    }

    /* remove non-local routes from the route table for this interface */
    flushNonLocalRoutes(ptr_device);

    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function displays the IPv6 Routing Table.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DisplayRouteTable (void)
{
    RT6_ENTRY*  ptr_RoutingTable = NULL;
    RT6_ENTRY*  ptr_rt6;
    char        strIPAddress[50];

    /* Get a copy of the routing table from the ROUTE6 Module. */
    ptr_RoutingTable = Rt6GetTable ();

    /* Search the routing table for a match? */
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&ptr_RoutingTable);
    while (ptr_rt6 != NULL)
    {
        ConPrintf ("-------------------------------------------------\n");
        ConPrintf ("Interface Name   : %s\n", ptr_rt6->ptr_device->name);
        IPv6IPAddressToString (ptr_rt6->NetworkAddr, &strIPAddress[0]);
        ConPrintf ("Network  Address : %s\n", strIPAddress);
        IPv6IPAddressToString (ptr_rt6->NextHop, &strIPAddress[0]);
        ConPrintf ("Next Hop Address : %s\n", strIPAddress);
       
        /* Print the Route Type. */ 
        if (ptr_rt6->Flags & FLG_RTE_CLONING)
            ConPrintf ("Route Type       : CLONING\n");
        else if (ptr_rt6->Flags & FLG_RTE_IFLOCAL)
            ConPrintf ("Route Type       : LOCAL\n");
        else if (ptr_rt6->Flags & FLG_RTE_GATEWAY)
            ConPrintf ("Route Type       : GATEWAY\n");
        else if (ptr_rt6->Flags & FLG_RTE_HOST)
            ConPrintf ("Route Type       : HOST\n");

        /* Display the timeouts 
         *  Note: Internally the timeouts are kept as absolute values */
        if (ptr_rt6->dwTimeout == INFINITE_LT)
            ConPrintf ("Timeout          : Infinite\n");
        else
            ConPrintf ("Timeout          : %d seconds\n", ptr_rt6->dwTimeout - llTimerGetTime(0));

        /* Get the next routing entry. */
        ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
    }
    ConPrintf ("-------------------------------------------------\n"); 

    /* Now cleanup the allocated list */
    Rt6CleanTable (ptr_RoutingTable);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function displays the IPv6 Neighbor Table.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DisplayNeighTable (void)
{
    RT6_ENTRY*  ptr_RoutingTable = NULL;
    RT6_ENTRY*  ptr_rt6;
    LLI6_ENTRY  lli6;
    LLI6_ENTRY* ptr_lli6;
    char        strIPAddress[50];
    char        NeighState[18];

    /* Get a copy of the routing table from the ROUTE6 Module. */
    ptr_RoutingTable = Rt6GetTable ();

    /* Search the routing table for a match? */
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&ptr_RoutingTable);
    while (ptr_rt6 != NULL)
    {   
        /* Move into kernel mode; since we need to get access to the LLI6 Entry. */     
        llEnter();

        /* Check if the routing entry has an LLI6 Entry associated with it. */
        if (Rt6GetLLI (ptr_rt6) != NULL)
        {
            /* YES. Create a local 'stack' copy of the LLI6 Entry. This is required
             * because we can operate on the local copy here and not interfere with the
             * LLI6 state machine which can execute in the NDK core */
            memcpy ((void *)&lli6, (void *)Rt6GetLLI (ptr_rt6), sizeof(LLI6_ENTRY));
            ptr_lli6 = &lli6;
        }
        else
        {
            /* NO. There is no LLI6 Entry which needs to be processed here. */
            ptr_lli6 = NULL;
        }

        /* Move out of kernel mode. */
        llExit ();

        /* Check if we got an LLI6 Entry and if so display it here */
        if (ptr_lli6 != NULL)
        {
            ConPrintf ("-------------------------------------------------\n");
            ConPrintf ("Interface Name   : %s\n", ptr_lli6->ptr_device->name);            
            IPv6IPAddressToString (ptr_rt6->IPAddr, &strIPAddress[0]);
            ConPrintf ("IP Address       : %s\n", strIPAddress);
            ConPrintf ("MAC Address      : %02x-%02x-%02x-%02x-%02x-%02x\n", 
                       ptr_lli6->MacAddr[0], ptr_lli6->MacAddr[1], ptr_lli6->MacAddr[2], 
                       ptr_lli6->MacAddr[3], ptr_lli6->MacAddr[4], ptr_lli6->MacAddr[5]);

            /* Display the Neighbor state. */
            if (ptr_lli6->status == ICMPV6_LLI_INCOMPLETE)
                strcpy (NeighState, "INCOMPLETE");
            else if (ptr_lli6->status == ICMPV6_LLI_REACHABLE)
                strcpy (NeighState, "REACHABLE");
            else if (ptr_lli6->status == ICMPV6_LLI_STALE)
                strcpy (NeighState, "STALE");
            else if (ptr_lli6->status == ICMPV6_LLI_DELAY)
                strcpy (NeighState, "DELAY");
            else if (ptr_lli6->status == ICMPV6_LLI_PROBE)
                strcpy (NeighState, "PROBE");
            else if (ptr_lli6->status == ICMPV6_LLI_DEAD)
                strcpy (NeighState, "DEAD");
            else
                strcpy (NeighState, "UNKNOWN");
            ConPrintf ("Neighbor State   : %s\n", NeighState);
            ConPrintf ("IsRouter         : %s\n", (ptr_lli6->IsRouter == 1) ? "YES" : "NO");
        }

        /* Get the next routing entry. */
        ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
    }
    ConPrintf ("-------------------------------------------------\n"); 

    /* Now cleanup the allocated list */
    Rt6CleanTable (ptr_RoutingTable);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function displays the IPv6 Bindings.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DisplayBindTable (void)
{
    BIND6_ENTRY*  ptr_BindTable = NULL;
    BIND6_ENTRY*  ptr_bind;
    char          strIPAddress[50];

    /* Get a copy of the routing table from the ROUTE6 Module. */
    ptr_BindTable = Bind6GetTable ();

    /* Search the routing table for a match? */
    ptr_bind = (BIND6_ENTRY *)list_get_head ((LIST_NODE**)&ptr_BindTable);
    while (ptr_bind != NULL)
    {
        ConPrintf ("-------------------------------------------------\n");
        ConPrintf ("Interface Name   : %s\n", ptr_bind->ptr_device->name);
        IPv6IPAddressToString (ptr_bind->IPHost, &strIPAddress[0]);
        ConPrintf ("IPv6  Address    : %s\n", strIPAddress);

        /* Display the Address Properties. */ 
        if (ptr_bind->flags & BIND6_TENTATIVE_ADDRESS)
            ConPrintf ("Address Type     : TENTATIVE\n");
        else if (ptr_bind->flags & BIND6_DEPRECATED_ADDRESS)
            ConPrintf ("Address Type     : DEPRECATED\n");
        else if (ptr_bind->flags & BIND6_ANYCAST_ADDRESS)
            ConPrintf ("Address Type     : ANYCAST\n");
        else
            ConPrintf ("Address Type     : PERMANENT\n");

        /* Display the Valid Lifetime. 
         *  Internally the timeouts are kept as "absolute" values. */
        if (ptr_bind->ValidLifetime == INFINITE_LT)
            ConPrintf ("Valid Lifetime   : Infinite\n");
        else
            ConPrintf ("Valid Lifetime   : %d seconds\n", ptr_bind->ValidLifetime - llTimerGetTime(0));

        /* Display the Preferred Lifetime. */
        if (ptr_bind->PreferredLifetime == INFINITE_LT)
            ConPrintf ("Pref. Lifetime   : Infinite\n");
        else
            ConPrintf ("Pref. Lifetime   : %d seconds\n", ptr_bind->PreferredLifetime - llTimerGetTime(0));

        /* Get the next bind entry. */
        ptr_bind = (BIND6_ENTRY *)list_get_next((LIST_NODE*)ptr_bind);
    }
    ConPrintf ("-------------------------------------------------\n"); 

    /* Now cleanup the allocated list */
    Bind6CleanTable (ptr_BindTable);
    return;        
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to display the help for all the TEST
 *      commands available.
 *
 *  @retval
 *      Not Applicable.
 */
static void CmdIPv6DisplayTestHelp (void)
{
    ConPrintf("\n[ipv6 test Command]\n");
    ConPrintf("The IPv6 Test Command Submenu is used to test various IPv6 API\n");
    ConPrintf("All commands are invoked as follows:-\n");
    ConPrintf("ipv6 test <Command>\n");
    ConPrintf("The following are a list of commands which are available\n\n");
    ConPrintf("zctest                          - Tests the Zero-Compression API. The TEST is VALID only\n");
    ConPrintf("                                  if Zero compression has been enabled in the stack.\n");
    ConPrintf("tftp <SrvIP> <File> [scopeid]   - Downloads file from the specified TFTP Server\n");
    ConPrintf("oob  <IPAddress> [scopeid]      - Tests the OOB. The IPAddress should be a 'local' NDK address\n");
    ConPrintf("echo <IPAddress> [scopeid]      - Tests the ECHO Server and verifies data received. The IPAddress\n");
    ConPrintf("                                  should be a 'local' NDK address.\n");
    ConPrintf("race <IPAddress> [scopeid]      - Ensures that TCP Sockets are able to receive data\n");
    ConPrintf("                                  after the peer socket is closed. The IPAddress should\n");
    ConPrintf("                                  be a 'local' NDK Address\n");
    ConPrintf("shutdown <IPAddress> [scopeid]  - Tests the SOCKET Shutdown API by closing WRITE & ensuring READ\n");
    ConPrintf("                                  still works. The IPAddress should be a 'local' NDK Address\n");
    ConPrintf("reuse <IPAddress> [scopeid]     - Tests socket REUSE across multiple connects. The IPAddress\n");
    ConPrintf("                                  should be a 'local' NDK Address\n");
    ConPrintf("share <IPAddress> [scopeid]     - Tests socket sharing between threads. The IPAddress\n");
    ConPrintf("                                  should be a 'local' NDK Address\n");
    ConPrintf("timeout                         - Tests the select TIMEOUT\n");
    ConPrintf("connect1 <IPAddress> [scopeid]  - Tests non-blocking connect API. The IPAddress\n");
    ConPrintf("                                  should be a 'local' NDK Address\n");
    ConPrintf("connect2 <IPAddress> [scopeid]  - Tests non-blocking connect API with timeout. The IPAddress\n");
    ConPrintf("                                  should be a 'local' NDK Address\n");
    ConPrintf("flood <IPAddress> [scopeid]     - Test multiple connects to the ECHO Server. The IPAddress\n");
    ConPrintf("                                  should be a 'local' NDK Address\n");
    ConPrintf("shutdown1 <IPAddress> [scopeid] - Test shutdown/close API on a listening socket using accept\n");
    ConPrintf("                                  The IPAddress should be a 'local' NDK Address\n");
    ConPrintf("shutdown2 <IPAddress> [scopeid] - Test shutdown/close API on a listening socket using select.\n");
    ConPrintf("                                  The IPAddress should be a 'local' NDK Address\n");
    ConPrintf("status <IPAddress> [scopeid]    - Test status conditions of UDP/TCP sockets & Pipes.\n");
    ConPrintf("                                  The IPAddress should be a 'local' NDK Address\n");
    ConPrintf("udp <IPAddress> [scopeid]       - Test UDP Sockets for sharing between tasks\n");
    ConPrintf("                                  The IPAddress should be a 'local' NDK Address\n");
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function prints out the IPv6 core stack statistics.
 *
 *  @retval
 *      Not Applicable.
 */
static void DumpIPv6CoreStats()
{
    ConPrintf("\nIPv6 Core Statistics:\n");
    ConPrintf("   InReceives        = %010u  ", ipv6mcb.ip6stats.InReceives);
    ConPrintf("   InHdrErrors       = %010u\n", ipv6mcb.ip6stats.InHdrErrors);
    ConPrintf("   InMcastPkts       = %010u  ", ipv6mcb.ip6stats.InMcastPkts);
    ConPrintf("   InTruncatedPkts   = %010u\n", ipv6mcb.ip6stats.InTruncatedPkts);
    ConPrintf("   InForwErrors      = %010u  ", ipv6mcb.ip6stats.InForwErrors);
    ConPrintf("   InExtnHdrErrors   = %010u\n", ipv6mcb.ip6stats.InExtnHdrErrors);
    ConPrintf("   InReasmReqds      = %010u  ", ipv6mcb.ip6stats.InReasmReqds);
    ConPrintf("   InReasmFails      = %010u\n", ipv6mcb.ip6stats.InReasmFails);
    ConPrintf("   InReasmOKs        = %010u  ", ipv6mcb.ip6stats.InReasmOKs);
    ConPrintf("   InUnknownProtos   = %010u\n", ipv6mcb.ip6stats.InUnknownProtos);
    ConPrintf("   InDelivers        = %010u  ", ipv6mcb.ip6stats.InDelivers);
    ConPrintf("   OutRequests       = %010u\n", ipv6mcb.ip6stats.OutRequests);
    ConPrintf("   OutNoRoutes       = %010u  ", ipv6mcb.ip6stats.OutNoRoutes);
    ConPrintf("   OutFragReqds      = %010u\n", ipv6mcb.ip6stats.OutFragReqds);
    ConPrintf("   OutFragFails      = %010u  ", ipv6mcb.ip6stats.OutFragFails);
    ConPrintf("   OutFragOKs        = %010u\n", ipv6mcb.ip6stats.OutFragOKs);
    ConPrintf("   OutFragCreates    = %010u\n", ipv6mcb.ip6stats.OutFragCreates);
    ConPrintf("   OutMcastPkts      = %010u  ", ipv6mcb.ip6stats.OutMcastPkts);
    ConPrintf("   OutDiscards       = %010u\n", ipv6mcb.ip6stats.OutDiscards);
    ConPrintf("   OutTransmits      = %010u  ", ipv6mcb.ip6stats.OutTransmits);
}

/** 
 *  @b Description
 *  @n  
 *      The function prints out the ICMPv6 statistics.
 *
 *  @retval
 *      Not Applicable.
 */
static void DumpICMPv6Stats()
{
    ConPrintf("\nICMPv6 Statistics:\n");
    ConPrintf("   InMsgs        = %010u  ", icmp6stats.InMsgs);
    ConPrintf("   InErrors      = %010u\n", icmp6stats.InErrors);
    ConPrintf("   OutMsgs       = %010u  ", icmp6stats.OutMsgs);
    ConPrintf("   OutErrors     = %010u\n", icmp6stats.OutErrors);
    ConPrintf("   DADSuccess    = %010u  ", icmp6stats.DADSuccess);
    ConPrintf("   DADFailures   = %010u\n", icmp6stats.DADFailures);
}

/** 
 *  @b Description
 *  @n  
 *      The function prints out the IPV6 TCP statistics.
 *
 *  @retval
 *      Not Applicable.
 */
static void DumpIPv6TCPStats()
{
    ConPrintf("\nIPv6 TCP Statistics:\n");
    ConPrintf("  RcvTotal       = %010u  ", tcp6_stats.RcvTotal        );
    ConPrintf("  RcvShort       = %010u\n", tcp6_stats.RcvShort        );
    ConPrintf("  RcvHdrSize     = %010u  ", tcp6_stats.RcvHdrSize      );
    ConPrintf("  RcvBadSum      = %010u\n", tcp6_stats.RcvBadSum       );
    ConPrintf("  RcvAfterClose  = %010u  ", tcp6_stats.RcvAfterClose   );
    ConPrintf("  RcvDupAck      = %010u\n", tcp6_stats.RcvDupAck       );
    ConPrintf("  RcvPack        = %010u  ", tcp6_stats.RcvPack         );
    ConPrintf("  RcvByte        = %010u\n", tcp6_stats.RcvByte         );
    ConPrintf("  RcvAckPack     = %010u  ", tcp6_stats.RcvAckPack      );
    ConPrintf("  RcvAckByte     = %010u\n", tcp6_stats.RcvAckByte      );
    ConPrintf("  RcvDupPack     = %010u  ", tcp6_stats.RcvDupPack      );
    ConPrintf("  RcvDupByte     = %010u\n", tcp6_stats.RcvDupByte      );
    ConPrintf("  RcvPartDupPack = %010u  ", tcp6_stats.RcvPartDupPack  );
    ConPrintf("  RcvPartDupByte = %010u\n", tcp6_stats.RcvPartDupByte  );
    ConPrintf("  RcvAfterWinPack= %010u  ", tcp6_stats.RcvAfterWinPack );
    ConPrintf("  RcvAfterWinByte= %010u\n", tcp6_stats.RcvAfterWinByte );
    ConPrintf("  RcvOOPack      = %010u  ", tcp6_stats.RcvOOPack       );
    ConPrintf("  RcvOOByte      = %010u\n", tcp6_stats.RcvOOByte       );
    ConPrintf("  RcvWinUpd      = %010u  ", tcp6_stats.RcvWinUpd       );
    ConPrintf("  RcvWinProbe    = %010u\n", tcp6_stats.RcvWinProbe     );
    ConPrintf("  RcvAckTooMuch  = %010u  ", tcp6_stats.RcvAckTooMuch   );
    ConPrintf("  SndNoBufs      = %010u\n", tcp6_stats.SndNoBufs       );

    ConPrintf("  SndTotal       = %010u  ", tcp6_stats.SndTotal        );
    ConPrintf("  SndProbe       = %010u\n", tcp6_stats.SndProbe        );
    ConPrintf("  SndPack (data) = %010u  ", tcp6_stats.SndPack         );
    ConPrintf("  SndByte (data) = %010u\n", tcp6_stats.SndByte         );
    ConPrintf("  SndRexmitPack  = %010u  ", tcp6_stats.SndRexmitPack   );
    ConPrintf("  SndRexmitByte  = %010u\n", tcp6_stats.SndRexmitByte   );
    ConPrintf("  SndAcks        = %010u  ", tcp6_stats.SndAcks         );
    ConPrintf("  SndCtrl        = %010u\n", tcp6_stats.SndCtrl         );
    ConPrintf("  SndUrg         = %010u  ", tcp6_stats.SndUrg          );
    ConPrintf("  SndWinUp       = %010u\n", tcp6_stats.SndWinUp        );

    ConPrintf("  SegsTimed      = %010u  ", tcp6_stats.SegsTimed       );
    ConPrintf("  RttUpdated     = %010u\n", tcp6_stats.RttUpdated      );
    ConPrintf("  Connects       = %010u  ", tcp6_stats.Connects        );
    ConPrintf("  ConnAttempt    = %010u\n", tcp6_stats.ConnAttempt     );
    ConPrintf("  Drops          = %010u  ", tcp6_stats.Drops           );
    ConPrintf("  ConnDrops      = %010u\n", tcp6_stats.ConnDrops       );
    ConPrintf("  Accepts        = %010u  ", tcp6_stats.Accepts         );
    ConPrintf("  TimeoutDrops   = %010u\n", tcp6_stats.TimeoutDrops    );
    ConPrintf("  KeepDrops      = %010u  ", tcp6_stats.KeepDrops       );
    ConPrintf("  DelAck         = %010u\n", tcp6_stats.DelAck          );
    ConPrintf("  KeepProbe      = %010u  ", tcp6_stats.KeepProbe       );
    ConPrintf("  PersistTimeout = %010u\n", tcp6_stats.PersistTimeout  );
    ConPrintf("  KeepTimeout    = %010u  ", tcp6_stats.KeepTimeout     );
    ConPrintf("  RexmtTimeout   = %010u\n", tcp6_stats.RexmtTimeout    );
}

/** 
 *  @b Description
 *  @n  
 *      The function prints out the IPV6 UDP statistics.
 *
 *  @retval
 *      Not Applicable.
 */
static void DumpIPv6UDPStats()
{
    ConPrintf("\nIPv6 UDP Statistics:\n");
    ConPrintf("  RcvTotal       = %010u\n", udp6_stats.RcvTotal        );
    ConPrintf("  RcvShort       = %010u\n", udp6_stats.RcvShort        );
    ConPrintf("  RcvBadLen      = %010u\n", udp6_stats.RcvBadLen       );
    ConPrintf("  RcvBadSum      = %010u\n", udp6_stats.RcvBadSum       );
    ConPrintf("  RcvFull        = %010u\n", udp6_stats.RcvFull         );
    ConPrintf("  RcvNoPort      = %010u\n", udp6_stats.RcvNoPort       );
    ConPrintf("  RcvNoPortB     = %010u\n", udp6_stats.RcvNoPortB      );
    ConPrintf("  SndTotal       = %010u\n", udp6_stats.SndTotal        );
    ConPrintf("  SndNoPacket    = %010u\n", udp6_stats.SndNoPacket     );

    ConPrintf("\nRAW Statistics:\n");
    ConPrintf("  RcvTotal       = %010u\n", raw6_stats.RcvTotal        );
    ConPrintf("  RcvFull        = %010u\n", raw6_stats.RcvFull         );
    ConPrintf("  SndTotal       = %010u\n", raw6_stats.SndTotal        );
    ConPrintf("  SndNoPacket    = %010u\n", raw6_stats.SndNoPacket     );
}

/** 
 *  @b Description
 *  @n  
 *      The function prints out the IPv6 stack statistics.
 *
 *  @param[in]  module_name
 *      IPv6 module whose stats needs to be displayed. 
 *      Valid options are core/icmp/tcp/udp
 *
 *  @retval
 *      Not Applicable.
 */
void V6DisplayStats (int ntok, char *tok1)
{
    /* Check for 'ipv6 stats core' */
    if( ntok == 1 && !stricmp( tok1, "core" ) )
        DumpIPv6CoreStats();
    /* Check for 'ipv6 stats icmp' */
    else if( ntok == 1 && !stricmp( tok1, "icmp" ) )
        DumpICMPv6Stats();
    /* Check for 'ipv6 stats tcp' */
    else if( ntok == 1 && !stricmp( tok1, "tcp" ) )
        DumpIPv6TCPStats();
    /* Check for 'ipv6 stats udp' */
    else if( ntok == 1 && !stricmp( tok1, "udp" ) )
        DumpIPv6UDPStats();
    else if( ntok == 0 )
    {
        ConPrintf("\n[IPv6 Stats Command]\n");
        ConPrintf("\nCalled to dump out internal IPv6 stack statistics.\n\n");
        ConPrintf("ipv6 stats core      - Print out IPv6 core stack statistics\n");
        ConPrintf("ipv6 stats icmp      - Print out ICMPv6 statistics\n");
        ConPrintf("ipv6 stats tcp       - Print out IPv6 TCP statistics\n");
        ConPrintf("ipv6 stats udp       - Print out IPv6 UDP and RAW statistics\n");
    }
    else
        ConPrintf("\nIllegal argument. Type 'ipv6 stats' for help\n");
}

/** 
 *  @b Description
 *  @n  
 *      The function is called from the console application after 
 *      detecting that the command entered is an "ipv6" command. 
 *      The console application parses the command line and tokenizes
 *      the command line and passes them to this function.
 *
 *  @param[in]  ntok
 *      The number of tokens passed to this API.
 *  @param[in]  tok1
 *      Token 1 can be NULL
 *  @param[in]  tok2
 *      Token 2 can be NULL
 *  @param[in]  tok3
 *      Token 3 can be NULL
 *  @param[in]  tok4
 *      Token 4 can be NULL
 *  @param[in]  tok5
 *      Token 5 can be NULL
 *  @param[in]  tok6
 *      Token 6 can be NULL
 *  @param[in]  tok7
 *      Token 7 can be NULL
 *
 *  @retval
 *      Not Applicable.
 */
void ConCmdIPv6(int ntok, char *tok1, char *tok2, char *tok3, char* tok4, char* tok5, char* tok6, char* tok7)
{
    /* If there are no tokens specified; print the usage */
    if (ntok == 0)
    {
        /* Print the usage and all the IPv6 command available. */
        CmdIPv6DisplayUsage ();
        return;
    } 

    /* Process the various commands. */
    if ((ntok == 2) && !strcmp (tok1, "init"))
    {
        /* Initialize the IPv6 Stack on the specific interface. */
        CmdIPv6InitializeStack (tok2);
        return;
    }

    /* Check if this is deinit command. */
    if ((ntok == 2) && !strcmp (tok1, "deinit"))
    {
        /* Initialize the IPv6 Stack on the specific interface. */
        CmdIPv6DeinitializeStack (tok2);
        return;
    }

    /* Check if this is the Route display command. */
    if ((ntok == 1) && !strcmp (tok1, "route"))
    {
        /* Display the Routing Table. */
        CmdIPv6DisplayRouteTable ();
        return;
    }

    /* Check if this is the Route clear command. */
    if ((ntok == 2) && !strcmp (tok1, "flushroutes"))
    {
        /* Clear out the routing table. */
        CmdIPv6FlushNonLocalRoutes (tok2);
        return;
    }


    /* Check if this is the Neigh Display Command. */
    if ((ntok == 1) && !strcmp (tok1, "neigh"))
    {
        /* Display the Neighbor Table. */
        CmdIPv6DisplayNeighTable ();
        return;
    }

    /* Check if this is the Bind6 Display Command. */
    if ((ntok == 1) && !strcmp (tok1, "bind"))
    {
        /* Display the Bind6 Table. */
        CmdIPv6DisplayBindTable ();
        return;
    }

    /* Check if this is an IPv6 Add Address Command. */
    if ((ntok == 7) && !strcmp (tok1, "add"))
    {
        /* Add an IPv6 Address to the interface. */
        CmdIPv6AddAddress(tok2, tok3, tok4, tok5, tok6, tok7);
        return;
    }

    /* Check if this is an IPv6 Del Address Command. */
    if ((ntok == 3) && !strcmp (tok1, "del"))
    {
        /* Delete an IPv6 Address to the interface. */
        CmdIPv6DelAddress(tok2, tok3);
        return;
    }
    
    /* Check if the request is to dump IPv6 stack stats */
    if ((ntok >= 0) && !strcmp(tok1, "stats"))
    {
        /* Dump IPv6 stats */
        V6DisplayStats (ntok-1, tok2);
        return;
    }

    /* Check if this is the TEST Command. */
    if (!strcmp(tok1, "test"))
    {
        /* YES. We are in the TEST Sub Menu and decrement the number of tokens to account 
         * for the test command. */
        ntok = ntok - 1;

        /* Did the user wish to display the test help? */
        if (ntok == 0)
        {
            /* YES. Print the Help submenu for TEST Commands. */
            CmdIPv6DisplayTestHelp ();
            return;
        }

        /* Check if the request is to test the ZC API. */
        if ((ntok == 1) && !strcmp(tok2, "zctest"))
        {
            /* Test the IPv6 String to IP6N conversion API. */
            V6TestIPv6ConversionAPI ();
            return;
        }

        /* Check if the request is to test the TFTP6 API. */
        if ((ntok > 1) && !strcmp(tok2, "tftp"))
        {
            /* Download the file from the specified TFTP Server */
            v6TestTFTP (ntok-1, tok3, tok4, tok5);
            return;
        }

        /* Check if the request is to test OOB? */
        if ((ntok > 1) && !strcmp(tok2, "oob"))
        {
            /* Test both the INLINE and NORMAL modes. */
            V6TCPOOBTest (ntok-1, tok3, tok4, 1);
            V6TCPOOBTest (ntok-1, tok3, tok4, 0);
            return;
        }

        /* Check if the request is to test TCP Echo? */
        if ((ntok > 1) && !strcmp(tok2, "echo"))
        {
            /* Test the TCP Echo. */
            V6TestTCPEcho (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test TCP Race? */
        if ((ntok > 1) && !strcmp(tok2, "race"))
        {
            /* Test the TCP Race. */
            V6TCPRaceTest (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test shutdown? */
        if ((ntok > 1) && !strcmp(tok2, "shutdown"))
        {
            /* Test the TCP Write Shuwdown API. */
            V6TCPShutdownWriteAPITest (ntok-1, tok3, tok4);
            return;
        }
        
        /* Check if the request is to test TCP Reuse? */
        if ((ntok > 1) && !strcmp(tok2, "reuse"))
        {
            /* Test the TCP Reuse. */
            V6ReuseTest (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test socket sharing? */
        if ((ntok > 1) && !strcmp(tok2, "share"))
        {
            /* Test the Share */
            V6ShareTest (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test the 'select' timeout API*/
        if ((ntok == 1) && !strcmp(tok2, "timeout"))
        {
            /* Test the select timeout. */
            V6TimeoutTest ();
            return;
        }

        /* Check if the request is to test the TCP Connect API without timeout? */
        if ((ntok > 1) && !strcmp(tok2, "connect1"))
        {
            /* Test the TCP Connect API */
            V6TCPConnectAPITest1 (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test the TCP Connect API with timeout? */
        if ((ntok > 1) && !strcmp(tok2, "connect2"))
        {
            /* Test the TCP Connect API */
            V6TCPConnectAPITest2 (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test the TCP Connect Flood? */
        if ((ntok > 1) && !strcmp(tok2, "flood"))
        {
            /* Test the TCP Connect Flood API */
            V6TCPConnectFlood (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test the TCP Shutdown/Close API through accept*/
        if ((ntok > 1) && !strcmp(tok2, "shutdown1"))
        {
            /* Test the TCP Shutdown API */
            V6TCPShutdownTest1 (ntok-1, tok3, tok4, 1);
            V6TCPShutdownTest1 (ntok-1, tok3, tok4, 0);
            return;
        }

        /* Check if the request is to test the TCP Shutdown/Close API through select*/
        if ((ntok > 1) && !strcmp(tok2, "shutdown2"))
        {
            /* Test the TCP Shutdown API */
            V6TCPShutdownTest2 (ntok-1, tok3, tok4, 1);
            V6TCPShutdownTest2 (ntok-1, tok3, tok4, 0);
            return;
        }

        /* Check if the request is to test the status API */
        if ((ntok > 1) && !strcmp(tok2, "status"))
        {
            /* Test the TCP Shutdown API */
            V6StatusTest (ntok-1, tok3, tok4);
            return;
        }

        /* Check if the request is to test the status API */
        if ((ntok > 1) && !strcmp(tok2, "udp"))
        {
            /* Test the UDP Share API */
            V6UDPShareRxTest (ntok-1, tok3, tok4);
            return;
        }

        /* Run all the tests for V6. */
#if 0
        V6DuplicateBind1Test ();
        V6TestDstUnreachablePort (tok2);
        V6TestIPv6ConversionAPI ();
        V6TestTCPEcho (tok2);
        V6TCPRaceTest ("::1");
        V6TCPShutdownWriteAPITest (tok2);
        V6ReuseTest ("::1");
        V6ShareTest ("::1");
        V6TimeoutTest();
        V6TCPConnectAPITest1(tok2);
        V6TCPConnectAPITest2(tok2);
        V6TCPConnectFlood("::1");
        V6TCPShutdownTest1("::1", 1);
        V6TCPShutdownTest1("::1", 0);
        V6TCPShutdownTest2("::1", 1);
        V6TCPShutdownTest2("::1", 0);
        V6UDPShareRxTest(tok2);
        V6TCPOOBTest(tok2, 1);
        V6TCPOOBTest(tok2, 0);
        V6StatusTest("::1");
#else
#endif
    }

    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function creates ECHO Request header and data payload for the
 *      PING6 packet. 
 *
 *  @param[in]  pBuf
 *      The data buffer in which the payload is created.
 *  @param[in]  id
 *      ICMP Sequence Number which will be populated in the ECHO Header.
 *
 *  @retval
 *      Not Applicable.
 */
static void CreatePing6Payload (char* pBuf, UINT16 id)
{
    int                 cc;
    ICMPV6_ECHO_HDR*    ptr_echoHdr;

    /* Get the pointer to the ICMPv6 Header. */
    ptr_echoHdr = (ICMPV6_ECHO_HDR *)pBuf;

    /* Populate the ICMPv6 Header. */
    ptr_echoHdr->Type        = ICMPV6_ECHO_REQUEST;
    ptr_echoHdr->Code        = 0;    
    ptr_echoHdr->Identifier  = 0;
    ptr_echoHdr->SequenceNum = htons(id);
    ptr_echoHdr->Checksum    = 0;

    /* Fill in the ping data buffer */
    for( cc = sizeof(ICMPV6_ECHO_HDR); cc < DATALEN; cc++ )
        *(pBuf+cc) = '0'+cc;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function validates the received echo reply packet
 *      and prints the status of the validation on the console.
 *
 *  @param[in]  pBuf
 *      The data buffer in which the payload is created.
 *  @param[in]  num_bytes
 *      The size of the received packet.
 *  @param[in]  from
 *      Peer Information who has responded to the ECHO Request
 *
 *  @retval
 *      Not Applicable.
 */
static void CheckPing6(char* pBuf, int num_bytes, struct sockaddr_in6* from)
{
    ICMPV6_ECHO_HDR*  ptr_icmpv6hdr;
    UINT16            Seq;
    char              FromAddress[40];
    IP6N              IPv6Addr;
   
    /* Get the pointer to the ICMPv6 Header. */
    ptr_icmpv6hdr = (ICMPV6_ECHO_HDR *)pBuf;

    /* Make sure we received an ECHO Reply packet. */ 
    if( ptr_icmpv6hdr->Type != ICMPV6_ECHO_REPLY )
        return;

    /* Get the sequence number from the packet. */ 
    Seq = (int)HNC16(ptr_icmpv6hdr->SequenceNum);

    mmCopy (IPv6Addr.u.addr8, from->sin6_addr.in6_u.u6_addr8, 16);

    /* Initialize the From Address */
    mmZeroInit((void *)&FromAddress[0], sizeof(FromAddress));
    IPv6IPAddressToString(IPv6Addr, &FromAddress[0]);

    /* Print ou the information. */ 
    ConPrintf("Reply from %s, %d bytes, Seq=%u \n", FromAddress, num_bytes, Seq);

    /* Validate the data payload. */
    if( num_bytes != DATALEN )
        ConPrintf("Data length error in reply (%d of %d)\n",num_bytes,DATALEN);

    /* Cycle through and make sure the same data payload is received. */
    for (num_bytes = sizeof(ICMPV6_ECHO_HDR); num_bytes < DATALEN; num_bytes++)
    {
        if( *(UINT8 *)((pBuf+num_bytes)) != (UINT8)('0'+num_bytes) )
        {
            ConPrintf("Data verification error in reply (%d 0x%x 0x%x)\n", 
                      num_bytes, *(UINT8 *)((pBuf+num_bytes)), '0'+num_bytes );
            break;
        }
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      This is the command handler for the PING6 command.
 *      The following is the valid syntax for using this from the
 *      console.
 *          ping6 <x>:<x>:<x>:<x>:<x>:<x>:<x>:<x> [scope-id]
 *      Zero compression is not allowed and also if the address
 *      specified is a LINK LOCAL address then a SCOPE ID needs 
 *      to be defined.  
 *
 *  @param[in]  ntok
 *      The number of tokens passed to this API.
 *  @param[in]  tok1
 *      Token 1 can be NULL
 *  @param[in]  tok2
 *      Token 2 can be NULL
 *
 *  @retval
 *      Not Applicable.
 */
void ConCmdPing6 ( int ntok, char *tok1, char *tok2 )
{
    struct  sockaddr_in6 to;
    struct  sockaddr_in6 from;
    struct  timeval      timeout;        
    IP6N                 IPPing;
    int                  scope_id = -1;
    SOCKET               s;
    UINT16               cnt_send = 0;
    char*                pBuf;
    int                  num_bytes;
    int                  fromlen;
    fd_set               ibits;

    /* Make sure the number of arguments are valid. */
    if((ntok == 0) || (ntok > 2))
    {
        ConPrintf("\n[Ping Command]\n");
        ConPrintf("\nCalled to generate ICMP echo requests\n\n");
        ConPrintf("ping x:x:x:x [scope-id] - Ping IP address\n");
        ConPrintf("scope-id - This is the interface ID on which the packet will be routed\n");
        ConPrintf("           and is applicable only if the address specified is Link Local\n");
        return;
    }

    /* Get the IPv6 Address from the token. */
    if (IPv6StringToIPAddress (tok1, &IPPing) < 0)
    {
        /* IPv6 Address passed seemed to be incorrect. */
        ConPrintf("Error: Invalid IPv6 Address detected\n");
        return;
    }

    /* Check if scope-id is specified. */
    if (ntok == 2)
        scope_id = atoi (tok2);

    /* Basic validation: Check if the address is LINK Local and if so we need to have a scope-id 
     * Else we will not be able to send out the packet. */
    if((IPv6IsLinkLocal(IPPing) == 1) && (scope_id == -1))
    {
        ConPrintf("Please specify the scope-id for link local addresses.\n");
        return;
    }

    /* Create a socket for PING. */
    s = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        return;
    }

    /* Allocate memory for the PING6 packets. */ 
    pBuf = mmBulkAlloc (MAXPACKET);
    if(pBuf == NULL)
    {
        ConPrintf("failed allocate working buffer\n");
        fdClose (s);
        return;
    }    

    /* Initialize the "TO" structure. */ 
    bzero( &to, sizeof(struct sockaddr_in6));
    to.sin6_family       = AF_INET6;
    to.sin6_scope_id     = scope_id;
    mmCopy ((void *)&to.sin6_addr.in6_u, (void *)&IPPing, sizeof(struct in6_addr));

    /* Initialize the "FROM" structure. */
    bzero( &from, sizeof(struct sockaddr_in6));
    from.sin6_family     = AF_INET6;

    /* Configure our timeout to be 1 second. */
    timeout.tv_sec  = 1;
    timeout.tv_usec = 0;

    /* Ping Away. */ 
    while( cnt_send < 5 )
    {
        /* Create the PING6 Payload; every ECHO Request packet we send out we increment 
         * the sequence number. */
        CreatePing6Payload (pBuf, cnt_send);

        /* Send the ping. */
        num_bytes = sendto( s, pBuf, DATALEN, 0,(struct sockaddr *)&to, sizeof(to) );
        if( num_bytes < 0 )
            ConPrintf("failed sendto (%d)\n",fdError());
        else if( num_bytes != DATALEN )
            ConPrintf("sendto - partial write!\n");

        /* We now wait for the response to come. */
        FD_ZERO(&ibits);
        FD_SET(s, &ibits);
        num_bytes = fdSelect((int)s, &ibits, 0, 0, &timeout);

        /* Check for an error. */
        if(num_bytes < 0 )
        {
            ConPrintf("failed select (%d)\n",fdError());
            mmBulkFree (pBuf);
            fdClose (s);
            return;
        }

        /* Check if data has been received or not? */ 
        if( FD_ISSET(s, &ibits) )
        {
            /* Receive the packet from the socket layer */
            fromlen = sizeof(from);
            num_bytes = (int)recvfrom(s, pBuf, MAXPACKET, 0,(struct sockaddr *)&from, &fromlen);
            if(num_bytes < 0 )
            {
                /* Error: Unable to receive data from the socket. */
                ConPrintf("failed recvfrom (%d)\n",fdError());
                mmBulkFree (pBuf);
                fdClose (s);
                return;
            }

            /* Validate the response packet. */
            CheckPing6( pBuf, num_bytes, &from ); 
        }
        else
        {
            /* If there was no data; then it must be a Timeout. */
            ConPrintf("Reply timeout\n");
        }

        /* We need to sleep for some time before we send another request. */
        fdSelect(0, 0, 0, 0, &timeout);

        /* Increment the number of echo request which have been sent. */
        cnt_send++;
    }

    /* The command has been processed. */
    mmBulkFree (pBuf);
    fdClose (s);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which prints the IPv6 address on console. The IP address passed
 *      has to be specified in network order (IP6N).
 *
 *  @param[in]   address
 *      IPv6 Address to be displayed.
 *  @retval
 *   Not Applicable.
 */
void ConIPv6DisplayIPAddress (IP6N address)
{
    char    strIPAddress[40];

    /* Convert to string format. */
    IPv6IPAddressToString (address, &strIPAddress[0]);

    /* Print out the address on the console. */
    ConPrintf ("%s\n", strIPAddress);

    return;
}

#endif /* _INCLUDE_IPv6_CODE */

