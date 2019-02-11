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
 * ======== contest.c ========
 *
 * TCP/IP Sockets test code
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>
#include "console.h"

static void ConfigTest();
static void EchoTest( IPN IPAddr );
static void SendTest( IPN IPAddr );
static void RaceTest( IPN IPAddr );
static void ShutdownTest( IPN IPAddr );
static void ReuseTest( IPN IPAddr );
static void ShareTest( IPN IPAddr );
static void TcpShareRX( HANDLE hTaskParent, SOCKET s, int *pFlag );
static void TcpShareTX( HANDLE hTaskParent, SOCKET s );
static void TimeoutTest();
static void ConnectTest1( IPN IPAddr );
static void ConnectTest2( IPN IPAddr );
static void ConnectFlood( IPN IPAddr );
static void ShutdownTest1( IPN IPAddr, int fClose );
static void ShutdownTest2( IPN IPAddr, int fClose );
static void CloseTask( HANDLE hTaskParent, SOCKET s );
static void ShutdownTask( HANDLE hTaskParent, SOCKET s );
static void StatusTest( IPN IPAddr );
static void PollCounter();
static void MulticastTest (void);
static volatile UINT32 PollCount = 0;
static volatile UINT32 PollRunning = 0;

static void ShareRxTest( IPN IPAddr );
static void UdpShareRX( SOCKET s, int index );



/*------------------------------------------------------------------------- */
/* ConCmdTest() */
/* Function to run tests */
/*------------------------------------------------------------------------- */
void ConCmdTest( int ntok, char *tok1, char *tok2 )
{
    IPN IPTmp;

    /* Check for 'test echo x.x.x.x' */
    if( ntok == 2 && !strcmp( tok1, "echo" ) )
    {
        if( !ConStrToIPN( tok2, &IPTmp ) )
            ConPrintf("Invalid address\n\n");
        else
            EchoTest( IPTmp );
    }
    /* Check for 'test send x.x.x.x' */
    else if( ntok == 2 && !strcmp( tok1, "send" ) )
    {
        if( !ConStrToIPN( tok2, &IPTmp ) )
            ConPrintf("Invalid address\n\n");
        else
            SendTest( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "race" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            RaceTest( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "shutdown" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ShutdownTest( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "close1" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ShutdownTest1( IPTmp, 1 );
    }
    else if( ntok == 1 && !strcmp( tok1, "shutdown1" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ShutdownTest1( IPTmp, 0 );
    }
    else if( ntok == 1 && !strcmp( tok1, "close2" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ShutdownTest2( IPTmp, 1 );
    }
    else if( ntok == 1 && !strcmp( tok1, "shutdown2" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ShutdownTest2( IPTmp, 0 );
    }
    else if( ntok == 1 && !strcmp( tok1, "status" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            StatusTest( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "reuse" ) )
    {
        /* Get the public IP address */
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ReuseTest( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "config" ) )
    {
        ConfigTest();
    }
    else if( ntok == 1 && !strcmp( tok1, "timeout" ) )
    {
        TimeoutTest();
    }
    else if( ntok == 1 && !strcmp( tok1, "multicast" ) )
    {
        MulticastTest();
    }
    else if( ntok == 2 && !strcmp( tok1, "shared" ) )
    {
        if( !ConStrToIPN( tok2, &IPTmp ) )
            ConPrintf("Invalid address\n\n");
        else
            ShareTest( IPTmp );
    }
    else if( ntok == 2 && !strcmp( tok1, "sharedrx" ) )
    {
        if( !ConStrToIPN( tok2, &IPTmp ) )
            ConPrintf("Invalid address\n\n");
        else
            ShareRxTest( IPTmp );
    }
    else if( ntok == 2 && !strcmp( tok1, "connect1" ) )
    {
        if( !ConStrToIPN( tok2, &IPTmp ) )
            ConPrintf("Invalid address\n\n");
        else
            ConnectTest1( IPTmp );
    }
    else if( ntok == 2 && !strcmp( tok1, "connect2" ) )
    {
        if( !ConStrToIPN( tok2, &IPTmp ) )
            ConPrintf("Invalid address\n\n");
        else
            ConnectTest2( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "conflood" ) )
    {
        if( !NtGetPublicHost( &IPTmp, 0, 0 ) )
            ConPrintf("Device not configured\n");
        else
            ConnectFlood( IPTmp );
    }
    else if( ntok == 1 && !strcmp( tok1, "counter" ) )
    {
        if( !PollRunning )
        {
            ConPrintf("[Launching Background Task]\n");
            TaskCreate( PollCounter, "Counter", 1, 1000, 0, 0, 0 );
        }
        ConPrintf("Counter = %d\n",PollCount);
        PollCount = 0;
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[Test Command]\n");
        ConPrintf("\nRun various TCP/IP stack tests.\n\n");
        ConPrintf("test echo x.x.x.x     - High volume TCP echo test\n");
        ConPrintf("test send x.x.x.x     - High volume TCP send test\n");
        ConPrintf("test race             - Race condition\n");
        ConPrintf("test shutdown         - Shutdown function\n");
        ConPrintf("test close1           - fdClose on LISTEN/ACCEPT socket\n");
        ConPrintf("test close2           - fdClose on LISTEN/SELECT socket\n");
        ConPrintf("test shutdown1        - Shutdown on LISTEN/ACCEPT socket\n");
        ConPrintf("test shutdown2        - Shutdown on LISTEN/SELECT socket\n");
        ConPrintf("test status           - Test the fdStatus() call\n");
        ConPrintf("test reuse            - Error socket reuse (uses echo)\n");
        ConPrintf("test config           - Getting various config info\n");
        ConPrintf("test timeout          - Select and socket timeouts\n");
        ConPrintf("test shared x.x.x.x   - Shared sockets (uses echo)\n");
        ConPrintf("test sharedrx x.x.x.x - Shared sockets on RX\n");
        ConPrintf("test connect1 x.x.x.x - Non-block Connect (uses echo)\n");
        ConPrintf("test connect2 x.x.x.x - Non-block Connect w/fdSelect (uses echo)\n");
        ConPrintf("test conflood         - Connection (TIMEWAIT) Flood (uses echo)\n");
        ConPrintf("test counter          - Install/Check background counting task\n\n");
    }
    else
        ConPrintf("\nCommand error. Type 'test' for help\n");
}

/*********************************************************************
 * FUNCTION NAME : ConfigTest
 *********************************************************************
 * DESCRIPTION   :
 *  The function prints the information which is stored in the various
 *  configuration information blocks.
 *********************************************************************/
static void ConfigTest()
{
    char        IPString[16];
    IPN         IPAddr;
    int         i,j,rc;
    CI_IPNET    NA;
    CI_ROUTE    RT;
    int         ret_code;
    UINT16      ifcnt;
    UINT16*     device_index;

    /* Get the number of NIMU devices which exist in the System */
    ret_code = NIMUIoctl (NIMU_GET_NUM_NIMU_OBJ, NULL, &ifcnt, sizeof(ifcnt));
    if (ret_code < 0)
    {
        ConPrintf ("ConfigTest: NIMUIOCTL (NIMU_GET_NUM_NIMU_OBJ) Failed with error code: %d\n",ret_code);
        ConPrintf ("CONTEST has FAILED\n");
        return;
    }

    /* Print it */
    ConPrintf("\nNumber of interfaces : %d\n",ifcnt);

    /* Allocate memory to get the device handles for all devices. */
    device_index = mmAlloc (sizeof(UINT16)*ifcnt);
    if(device_index == NULL)
    {
        ConPrintf("\nOOM Error\nCONTEST has FAILED\n");
        return;
    }

    /* Get information about all the device handles present. */
    ret_code = NIMUIoctl (NIMU_GET_ALL_INDEX, NULL, device_index,sizeof(UINT16)*ifcnt);
    if (ret_code < 0)
    {
        ConPrintf ("ConfigTest: NIMUIOCTL (NIMU_GET_ALL_INDEX) Failed with error code: %d\n",ret_code);
        ConPrintf ("CONTEST has FAILED\n");
        mmFree (device_index);
        return;
    }

    /* Scan all IF's in the CFG for network information */
    ConPrintf("\nIP Networks Installed:\n");
    for( i=0; i<ifcnt; i++ )
    {
        j = 1;
        for(;;)
        {
            /* Try and get a IP network address */
            rc = CfgGetImmediate( 0, CFGTAG_IPNET, *(device_index+i), j,
                                  sizeof(NA), (UINT8 *)&NA );
            if( rc != sizeof(NA) )
                break;

            /* We got something */

            /* Convert IP to a string: */
            NtIPN2Str( NA.IPAddr, IPString );
            ConPrintf("On IF-%d, IP Addr='%s', ",*(device_index+i), IPString);
            NtIPN2Str( NA.IPMask, IPString );
            ConPrintf("NetMask='%s', Domain='%s'\n",IPString, NA.Domain);
            j++;
        }
    }

    /* Now scan all routes entered via the configuration */
    ConPrintf("\nManually Configured Routes:\n");
    for(i=1;;i++)
    {
        /* Try and get a route */
        rc = CfgGetImmediate( 0, CFGTAG_ROUTE, 0, i,
                             sizeof(RT), (UINT8 *)&RT );
        if( rc != sizeof(RT) )
            break;

        /* We got something */

        /* Convert IP to a string: */
        NtIPN2Str( RT.IPDestAddr, IPString );
        ConPrintf("Route, Dest='%s', ",IPString);
        NtIPN2Str( RT.IPDestMask, IPString );
        ConPrintf("Mask='%s', ",IPString);
        NtIPN2Str( RT.IPGateAddr, IPString );
        ConPrintf("Gateway='%s'\n",IPString);
    }
    if( i==1 )
        ConPrintf("None\n");

    /* Now scan all DNS servers entered via the configuration */
    ConPrintf("\nExternal DNS Server Information:\n");
    for(i=1;;i++)
    {
        /* Try and get a DNS server */
        rc = CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_DOMAINNAMESERVER,
                              i, 4, (UINT8 *)&IPAddr );
        if( rc != 4 )
            break;

        /* We got something */

        /* Convert IP to a string: */
        NtIPN2Str( IPAddr, IPString );
        ConPrintf("DNS Server %d = '%s'\n", i, IPString);
    }
    if( i==1 )
        ConPrintf("None\n\n");
    else
        ConPrintf("\n");

    /* Now scan all NBNS servers entered via the configuration */
    ConPrintf("External NBNS Server Information:\n");
    for(i=1;;i++)
    {
        /* Try and get a DNS server */
        rc = CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_NBNS,
                              i, 4, (UINT8 *)&IPAddr );
        if( rc != 4 )
            break;

        /* We got something */

        /* Convert IP to a string: */
        NtIPN2Str( IPAddr, IPString );
        ConPrintf("NBNS Server %d = '%s'\n", i, IPString);
    }
    if( i==1 )
        ConPrintf("None\n\n");
    else
        ConPrintf("\n");
}

/*---------------------------------------------------------------------- */
/* MulticastTest() */
/* Test the Multicast socket API. */
/*---------------------------------------------------------------------- */
static void MulticastTest (void)
{
    SOCKET           sudp1 = INVALID_SOCKET;
    SOCKET           sudp2 = INVALID_SOCKET;
    struct sockaddr_in sin1;
    char             buffer[1000];
    int              reuse = 1;
    struct ip_mreq    group;
    fd_set          msockets;
    int             iterations = 0;
    int             cnt;
    CI_IPNET        NA;

    ConPrintf ("=== Executing Multicast Test on Interface 1 ===\n");

    /* Create our UDP Multicast socket1 */
    sudp1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( sudp1 == INVALID_SOCKET )
    {
        ConPrintf ("Error: Unable to create socket\n");
        return;
    }

    /* Create our UDP Multicast socket1 */
    sudp2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( sudp2 == INVALID_SOCKET )
    {
        ConPrintf ("Error: Unable to create socket\n");
        return;
    }
    
    /* Set Port = 4040, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(4040);

    /* Print the IP address information only if one is present. */
    if (CfgGetImmediate( 0, CFGTAG_IPNET, 1, 1, sizeof(NA), (UINT8 *)&NA) != sizeof(NA))
    {
        ConPrintf ("Error: Unable to get IP Address Information\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }

    /* Set the Reuse Ports Socket Option for both the sockets.  */
    if (setsockopt(sudp1, SOL_SOCKET, SO_REUSEPORT, (char *)&reuse, sizeof(reuse)) < 0)
    {
        ConPrintf ("Error: Unable to set the reuse port socket option\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }    
    /* Reuse the ports; since multiple multicast clients will be executing. */
    if (setsockopt(sudp2, SOL_SOCKET, SO_REUSEPORT, (char *)&reuse, sizeof(reuse)) < 0)
    {
        ConPrintf ("Error: Unable to set the reuse port socket option\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }

    /* Now bind both the sockets. */
    if (bind (sudp1, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf ("Error: Unable to bind the socket.\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }
    if (bind (sudp2, (PSA) &sin1, sizeof(sin1)) < 0)
    {
        ConPrintf ("Error: Unable to bind the socket.\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }

    /* Now we join the groups for socket1
     *  Group: 224.1.2.4 
     *  Group: 224.1.2.5 */
    group.imr_multiaddr.s_addr = inet_addr("224.1.2.4");
    group.imr_interface.s_addr = NA.IPAddr;
    if (setsockopt (sudp1, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&group, sizeof(group)) < 0)
    {
        ConPrintf ("Error: Unable to join multicast group\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }
    group.imr_multiaddr.s_addr = inet_addr("224.1.2.5");
    group.imr_interface.s_addr = NA.IPAddr;
    if (setsockopt (sudp1, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&group, sizeof(group)) < 0)
    {
        ConPrintf ("Error: Unable to join multicast group\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }
    ConPrintf ("-----------------------------------------\n");
    ConPrintf ("Socket Identifier %d has joined the following:-\n", sudp1);
    ConPrintf (" - Group 224.1.2.4\n");
    ConPrintf (" - Group 224.1.2.5\n");
    ConPrintf ("-----------------------------------------\n");

    /* Now we join the groups for socket2
     *  Group: 224.1.2.5 
     *  Group: 224.1.2.6 */
    group.imr_multiaddr.s_addr = inet_addr("224.1.2.5");
    group.imr_interface.s_addr = NA.IPAddr;
    if (setsockopt (sudp2, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&group, sizeof(group)) < 0)
    {
        ConPrintf ("Error: Unable to join multicast group\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }
    group.imr_multiaddr.s_addr = inet_addr("224.1.2.6");
    group.imr_interface.s_addr = NA.IPAddr;
    if (setsockopt (sudp2, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&group, sizeof(group)) < 0)
    {
        ConPrintf ("Error: Unable to join multicast group\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;
    }
    ConPrintf ("-----------------------------------------\n");
    ConPrintf ("Socket Identifier %d has joined the following:-\n", sudp2);
    ConPrintf (" - Group 224.1.2.5\n");
    ConPrintf (" - Group 224.1.2.6\n");
    ConPrintf ("-----------------------------------------\n");
            
    while (iterations < 4)
    {
        /* Initialize the FD Set. */
        FD_ZERO(&msockets);
        FD_SET(sudp1, &msockets);
        FD_SET(sudp2, &msockets);

        /* Wait for the multicast packets to arrive. */
        cnt = fdSelect( (int)sudp2, &msockets, 0, 0 , 0);

        if(FD_ISSET(sudp1, &msockets))
        {
            cnt = (int)recv (sudp1, (void *)&buffer, sizeof(buffer), 0);
            if( cnt >= 0 )
                ConPrintf ("Socket Identifier %d received %d bytes of multicast data\n", sudp1, cnt);
            else
                ConPrintf ("Error: Unable to receive data\n");

            /* Increment the iterations. */
            iterations++;
        }
        if(FD_ISSET(sudp2, &msockets))
        {
            cnt = (int)recv (sudp2, (void *)&buffer, sizeof(buffer), 0);
            if( cnt >= 0 )
                ConPrintf ("Socket Identifier %d received %d bytes of multicast data\n", sudp2, cnt);
            else
                ConPrintf ("Error: Unable to receive data\n");

            /* Increment the iterations. */
            iterations++;            
        }
    }

    /* Once the packet has been received. Leave the Multicast group! */
    if (setsockopt (sudp2, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *)&group, sizeof(group)) < 0)
    {
        ConPrintf ("Error: Unable to leave multicast group\n");
        fdClose (sudp1);
        fdClose (sudp2);
        return;        
    }

    /* Leave only one of the multicast groups through the proper API. */
    NtIPN2Str (group.imr_multiaddr.s_addr, &buffer[0]);
    ConPrintf ("Leaving group %s through IP_DROP_MEMBERSHIP\n", buffer); 

    /* Once we get out of the loop close socket2; this should internally leave all the groups. */
    fdClose (sudp1);
    fdClose (sudp2);
    ConPrintf("== End Multicast Test ==\n\n");
}

/*---------------------------------------------------------------------- */
/* EchoTest() */
/* Test ECHO with a TCP socket */
/*---------------------------------------------------------------------- */
#define TEST_ITER       2500
static void EchoTest( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    UINT32  test,i,j;
    int     k;
    char    *pBuf = 0;
    char    *pBufRx;
    HANDLE  hBuffer;
    struct  timeval timeout;
    UINT32  startS, startMS;
    UINT32  endS, endMS;

    ConPrintf("\n== Start TCP Echo Client Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(7);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( 8192 )) )
    {
        ConPrintf("failed temp buffer allocation\n");
        goto leave;
    }

    startS = llTimerGetTime( &startMS );

    /* Start Test */
    test = 8192;
    for( j=0; j<TEST_ITER; j++ )
    {
        /* Send the buffer */
        if( send( s, pBuf, (int)test, 0 ) < 0 )
        {
            ConPrintf("send failed (%d)\n",fdError());
            break;
        }

        /* Try and receive the buffer */
        i = 0;
        while( i < test )
        {
            k = recvnc( s, (void **)&pBufRx, 0, &hBuffer );
            if( k < 0 )
            {
                ConPrintf("recv failed (%d)\n",fdError());
                goto leave;
            }
            if( !k )
            {
                ConPrintf("connection dropped\n");
                goto leave;
            }
            recvncfree( hBuffer );
            i += (UINT32)k;
        }

        /* Verify reception size */
        if( i != test )
        {
            ConPrintf("received %d (not %d) bytes\n",i,test);
            break;
        }
    }

    if( j == TEST_ITER )
    {
        endS = llTimerGetTime( &endMS );
        endS -= startS;
        endS *= 1000;
        endMS += endS;
        endMS -= startMS;
        endS = (endMS+50)/100;
        ConPrintf("Passed in %d ms, %d bytes/sec\n",endMS,(j*test*10)/endS);
    }

leave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End TCP Echo Client Test ==\n\n");
}

/*---------------------------------------------------------------------- */
/* SendTest() */
/* Test sending on a TCP socket */
/*---------------------------------------------------------------------- */
#define SEND_ITER       25000
static void SendTest( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    UINT32  test,j;
    char    *pBuf = 0;
    struct  timeval timeout;
    UINT32  startS, startMS;
    UINT32  endS, endMS;

    ConPrintf("\n== Start TCP Send Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(1001);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( 8192 )) )
    {
        ConPrintf("failed temp buffer allocation\n");
        goto leave;
    }

    startS = llTimerGetTime( &startMS );

    /* Start Test */
    test = 8192;
    for( j=0; j<SEND_ITER; j++ )
    {
        /* Send the buffer */
        if( send( s, pBuf, (int)test, 0 ) < 0 )
        {
            ConPrintf("send failed (%d)\n",fdError());
            break;
        }
    }

    if( j == SEND_ITER )
    {
        endS = llTimerGetTime( &endMS );
        endS -= startS;
        endS *= 1000;
        endMS += endS;
        endMS -= startMS;
        endS = (endMS+50)/100;
        ConPrintf("Passed in %d ms, %d bytes/sec\n",endMS,(j*test*10)/endS);
    }

leave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End TCP Send Test ==\n\n");
}

static void RaceTest( IPN IPAddr )
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    char    buffer[128];
    struct  sockaddr_in sin1;
    int     rc,size;

    ConPrintf("\n== Test Listen/Accept Race Condition ==\n");

    /* Create test socket1 */
    s1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s1 == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(12345);

    /* Bind the socket */
    if( bind( s1, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if( listen( s1, 1) < 0 )
    {
        ConPrintf("failed listen (%d)\n",fdError());
        goto leave;
    }

    /* Create test socket2 */
    s2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s2 == INVALID_SOCKET )
    {
        ConPrintf("failed socket create2 (%d)\n",fdError());
        goto leave;
    }

    /* Connect the socket */
    if( connect( s2, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Send some test data */
    if( send( s2, "Hello World", 11, 0 ) < 0 )
    {
        ConPrintf("failed send (%d)\n",fdError());
        goto leave;
    }

    /* Close test socket2 */
    fdClose( s2 );
    s2 = INVALID_SOCKET;

    /* Get the accept socket */
    size = sizeof( sin1 );
    s2 = accept( s1, (PSA)&sin1, &size );
    if( s2 == INVALID_SOCKET )
    {
        ConPrintf("failed accept (%d)\n",fdError());
        goto leave;
    }

    for(;;)
    {
        rc = recv( s2, buffer, 127, MSG_PEEK );

        if( rc >= 0 )
        {
            ConPrintf("Successful PEEK read (%d bytes)\n",rc);
            buffer[rc]=0;
            if( rc )
                ConPrintf("Data = '%s'\n",buffer);
        }
        else
        {
            ConPrintf("PEEK Read returned %d, error = %d\n",rc,fdError());
            break;
        }
        rc = recv( s2, buffer, 127, 0 );

        if( rc >= 0 )
        {
            ConPrintf("Successful read (%d bytes)\n",rc);
            buffer[rc]=0;
            if( rc )
                ConPrintf("Data = '%s'\n",buffer);
            else
                break;
        }
        else
        {
            ConPrintf("Read returned %d, error = %d\n",rc,fdError());
            break;
        }
     }

leave:
     if( s2 != INVALID_SOCKET )
         fdClose(s2);
     if( s1 != INVALID_SOCKET )
         fdClose(s1);

    ConPrintf("== End Test ==\n\n");
}

static void ShutdownTest( IPN IPAddr )
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    SOCKET  s3 = INVALID_SOCKET;
    char    buffer[128];
    struct  sockaddr_in sin1;
    int     rc,size;

    ConPrintf("\n== Test shutdown(WRITE) Condition ==\n");

    /* Create test socket1 */
    s1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s1 == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(12345);

    /* Bind the socket */
    if( bind( s1, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if( listen( s1, 1) < 0 )
    {
        ConPrintf("failed listen (%d)\n",fdError());
        goto leave;
    }

    /* Create test socket2 */
    s2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s2 == INVALID_SOCKET )
    {
        ConPrintf("failed socket create2 (%d)\n",fdError());
        goto leave;
    }

    /* Connect the socket */
    if( connect( s2, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Shut down the write side */
    if( shutdown( s2, SHUT_WR ) < 0 )
    {
        ConPrintf("failed shutdown (%d)\n",fdError());
        goto leave;
    }

    /* Get the accept socket */
    size = sizeof( sin1 );
    s3 = accept( s1, (PSA)&sin1, &size );
    if( s3 == INVALID_SOCKET )
    {
        ConPrintf("failed accept (%d)\n",fdError());
        goto leave;
    }

    /* Send some test data on s3 */
    if( send( s3, "Hello World", 11, 0 ) < 0 )
    {
        ConPrintf("failed send (%d)\n",fdError());
        goto leave;
    }

    /* Close test socket3 */
    fdClose( s3 );
    s3 = INVALID_SOCKET;

    /* We should be able to read data on s2 */
    for(;;)
    {
        rc = recv( s2, buffer, 127, MSG_PEEK );

        if( rc >= 0 )
        {
            ConPrintf("Successful PEEK read (%d bytes)\n",rc);
            buffer[rc]=0;
            if( rc )
                ConPrintf("Data = '%s'\n",buffer);
        }
        else
        {
            ConPrintf("PEEK Read returned %d, error = %d\n",rc,fdError());
            break;
        }
        rc = recv( s2, buffer, 127, 0 );

        if( rc >= 0 )
        {
            ConPrintf("Successful read (%d bytes)\n",rc);
            buffer[rc]=0;
            if( rc )
                ConPrintf("Data = '%s'\n",buffer);
            else
                break;
        }
        else
        {
            ConPrintf("Read returned %d, error = %d\n",rc,fdError());
            break;
        }
     }

leave:
     if( s2 != INVALID_SOCKET )
         fdClose(s2);
     if( s1 != INVALID_SOCKET )
         fdClose(s1);

    ConPrintf("== End Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* TimeoutTest() */
/* Test timeouts on TCP socket read and select */
/*---------------------------------------------------------------------- */
static void TimeoutTest()
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    char    Buffer[32];
    struct  timeval timeout;
    fd_set  ibits;
    int     cnt;

    ConPrintf("\n== Start fdSelect()/recv() Timeout Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Bind socket to port 12345 (we don't want any data) */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_port        = htons(12345);

    if( bind( s,(struct sockaddr *)&sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed socket bind (%d)\n",fdError());
        goto leave;
    }

    ConPrintf("\nSetting fdSelect() timeout to 2 sec (1s + 1000000uS)\n");

    timeout.tv_sec  = 1;
    timeout.tv_usec = 1000000;

    FD_ZERO(&ibits);
    FD_SET(s, &ibits);

    ConPrintf("Calling fdSelect() ...");
    cnt = fdSelect( (int)s, &ibits, 0, 0, &timeout );
    if( !cnt )
        ConPrintf(" timeout!\n");
    else
        ConPrintf(" input data detected - error!\n");

    ConPrintf("\nCalling fdSelect() [with no descriptors]...");
    cnt = fdSelect( (int)s, 0, 0, 0, &timeout );
    if( !cnt )
        ConPrintf(" timeout!\n");
    else
        ConPrintf(" input data detected - error!\n");

    ConPrintf("\nSetting recv() timeout to 2 sec (1s + 1000000uS)\n");

    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    ConPrintf("Calling recv() ...");
    cnt = recv( s, Buffer, 32, 0 );
    if( cnt < 0 )
    {
        if( fdError() == EWOULDBLOCK )
            ConPrintf(" timeout!\n");
        else
            ConPrintf(" unexpected error %d\n",fdError());
    }
    else
        ConPrintf(" input data detected - error!\n");

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("\n== End Timeout Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* ReuseTest() */
/* Test Socket Reuse */
/*---------------------------------------------------------------------- */
static void ReuseTest(IPN IPAddr)
{
    SOCKET  s;
    struct  sockaddr_in sin1;

    ConPrintf("\n== Test Error Socket Resue Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(12345);

    /* Connect the socket */
    ConPrintf("Connecting to local port 12345 (should fail)\n");
    if( connect( s, (PSA) &sin1, sizeof(sin1) ) >=0 )
    {
        ConPrintf("First connect passed unexpectedly - abort\n");
        goto leave;
    }
    ConPrintf("Connect failed (%d)\n",fdError());

    sin1.sin_port        = htons(7);

    /* Connect the socket again */
    ConPrintf("Connecting to local port 7 (should pass)\n");
    if( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("Connect failed (%d)\n",fdError());
        goto leave;
    }

    ConPrintf("Connect Passed\n");

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("\n== End Socket Error Reuse Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* ShareTest() */
/* Test ECHO with a shared TCP socket using two tasks */
/*---------------------------------------------------------------------- */
static void ShareTest( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    struct  timeval timeout;
    fd_set  xbits;

    ConPrintf("\n== Start Shared TCP Socket Echo Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(7);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Create a thread to receive data */
    if( !TaskCreate( TcpShareRX, "Receiver", OS_TASKPRINORM, 0x1000,
                     (UINT32)TaskSelf(), (UINT32)s, 0 ) )
        goto leave;

    /* Create a thread to send us data */
    TaskCreate( TcpShareTX, "Sender", OS_TASKPRINORM, 0x1000,
                (UINT32)TaskSelf(), (UINT32)s, 0 );

    ConPrintf("Main task waiting with select() for test to complete\n");
    FD_ZERO(&xbits);
    FD_SET(s, &xbits);
    fdSelect( (int)s, 0, 0, &xbits, 0 );

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End Shared TCP Socket Echo Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* TcpShareRX() */
/* Task to receive data on a shared socket */
/*---------------------------------------------------------------------- */
/* ARGSUSED */
static void TcpShareRX( HANDLE hTaskParent, SOCKET s, int *pFlag )
{
    char    *pBufRx;
    HANDLE  hBuffer;
    UINT32  test,i,j;
    int     k;
    UINT32  startS, startMS;
    UINT32  endS, endMS;

    fdOpenSession( TaskSelf() );

    /* Here we'll "share" socket 's' to up its reference count */
    fdShare(s);

    ConPrintf("RX Child task spawned successfully\n");

    startS = llTimerGetTime( &startMS );

    /* Start Test */
    test = 8192;
    i = 0;
    for( j=0; j<TEST_ITER; j++ )
    {
        /* Try and receive the buffer */
        while( i < test )
        {
            k = recvnc( s, (void **)&pBufRx, 0, &hBuffer );
            if( k < 0 )
            {
                ConPrintf("RX Child recv failed (%d)\n",fdError());
                goto leave;
            }
            if( !k )
            {
                ConPrintf("RX Child connection dropped\n");
                goto leave;
            }
            recvncfree( hBuffer );
            i += (UINT32)k;
        }
        i -= test;
    }

    /* Verify reception size */
    if( i != 0 )
        ConPrintf("RX Child received %d too many bytes\n",i);

    if( j == TEST_ITER )
    {
        endS = llTimerGetTime( &endMS );
        endS -= startS;
        endS *= 1000;
        endMS += endS;
        endMS -= startMS;
        endS = (endMS+500)/1000;
        ConPrintf("Passed in %d ms, %d bytes/sec\n",endMS,(j*test)/endS);
    }

    /* Closing our socket will eventually wake up our parent, but */
    /* we want to test shutdown first. We shutdown read as a stronger */
    /* form of the test. Shutting down write would cause the echo server */
    /* to close the socket, which is the same as calling close() from */
    /* our side. */
    shutdown( s, SHUT_RD );

    /* Small delay so we can see the main thread quitting immediately */
    /* after the "Passed" message */
    TaskSleep(2000);

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    fdCloseSession( TaskSelf() );
    TaskExit();
}


/*------------------------------------------------------------------------- */
/* TcpShareTX() */
/* This function sends TCP data over a shared socket. */
/*------------------------------------------------------------------------- */
/* ARGSUSED */
static void TcpShareTX( HANDLE hTaskParent, SOCKET s )
{
    UINT32  test,i;
    char    *pBuf = 0;

    fdOpenSession( TaskSelf() );

    /* Here we'll "share" socket 's' to up its reference count */
    fdShare(s);

    ConPrintf("TX Child task spawned successfully\n");

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( 8192 )) )
    {
        ConPrintf("TX Child failed temp buffer allocation\n");
        goto leave;
    }

    /* Start Test - Just Send */
    test = 8192;
    for( i=0; i<TEST_ITER; i++ )
    {
        /* Send the buffer */
        if( send( s, pBuf, (int)test, 0 ) < 0 )
        {
            ConPrintf("TX Child send failed (%d)\n",fdError());
            break;
        }
    }

leave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    fdCloseSession( TaskSelf() );
    TaskExit();
}


/*---------------------------------------------------------------------- */
/* ConnectTest1() */
/* Test Connect using non-Blocking IO */
/*---------------------------------------------------------------------- */
static void ConnectTest1( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    int     tmp;

    ConPrintf("\n== Start Non-Blocking Connect Test (polls connect()) ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(7);

    /* Setup for non-blocking */
    tmp = 0;
    setsockopt( s, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof( tmp ) );

    /* Connect socket */
    while( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        tmp = fdError();

        if( tmp == EINPROGRESS )
            ConPrintf("Connect returned EINPROGRESS\n");
        else if( tmp == EALREADY )
            ConPrintf("Connect returned EALREADY\n");
        else if( tmp == EISCONN )
        {
            ConPrintf("Connect returned EISCONN\n");
            break;
        }
        else if( tmp == ETIMEDOUT )
        {
            ConPrintf("Connect returned ETIMEDOUT\n");
            break;
        }
        else if( tmp == ECONNREFUSED )
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

    if( !tmp )
        ConPrintf("Connect returned success (IP address was local?)\n");

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End Non-Blocking Connect Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* ConnectTest2() */
/* Test Connect using non-Blocking IO */
/*---------------------------------------------------------------------- */
static void ConnectTest2( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    int     tmp;
    struct  timeval timeout;
    fd_set  obits;
    int     cnt;

    ConPrintf("\n== Start Non-Blocking Connect Test (uses fdSelect()) ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(7);

    /* Setup for non-blocking */
    tmp = 0;
    setsockopt( s, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof( tmp ) );

    /* Connect socket */
    if( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        tmp = fdError();

        if( tmp != EINPROGRESS )
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

        cnt = fdSelect( (int)s, 0, &obits, 0, &timeout );
        if( !cnt )
            ConPrintf("Connection timeout!\n");
        else
        {
            ConPrintf("Socket reports writable\n");
            if( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
            {
                tmp = fdError();

                if( tmp == EISCONN )
                {
                    ConPrintf("Connect returned EISCONN\n");
                    goto leave;
                }
                else  if( tmp == ECONNREFUSED )
                {
                    ConPrintf("Connect returned ECONNREFUSED\n");
                    goto leave;
                }
                ConPrintf("Connect returned error %d\n",tmp);
            }
        }

        ConPrintf("Connect failed\n");
    }

    if( !tmp )
        ConPrintf("Connect returned success (IP address was local?)\n");

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End Non-Blocking Connect Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* ConnectFlood() */
/* Test Connect Flood */
/*---------------------------------------------------------------------- */
static void ConnectFlood( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    int     i;

    ConPrintf("\n== Start Connect (TIMEWAIT) Flood Test ==\n");

    for( i=0; i<1000; i++ )
    {
        /* Create test socket */
        s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
        if( s == INVALID_SOCKET )
        {
            ConPrintf("failed socket create (%d)\n",fdError());
            goto leave;
        }

        /* Prepare address for connect */
        bzero( &sin1, sizeof(struct sockaddr_in) );
        sin1.sin_family      = AF_INET;
        sin1.sin_addr.s_addr = IPAddr;
        sin1.sin_port        = htons(7);

        /* Connect socket */
        if( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
        {
            ConPrintf("failed socket connect (%d)\n",fdError());
            goto leave;
        }

        fdClose( s );

        /* We still need to give the timer loop some time to run */
        TaskSleep( 6 );
    }

leave:
    if( i < 1000 )
        ConPrintf("Failed on iteration %d\n",i);
    else
        ConPrintf("Passed with %d iterations\n",i);

    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End Connect (TIMEWAIT) Flood Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* ShutdownTest1() */
/* Test shutdown/close of a listening socket in "accept" */
/*---------------------------------------------------------------------- */
static void ShutdownTest1( IPN IPAddr, int fClose )
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    int     size,tmp;
    struct  sockaddr_in sin1;

    if( fClose )
        ConPrintf("\n== Test fdClose() on Listen/Accept sondition ==\n");
    else
        ConPrintf("\n== Test shutdown() on Listen/Accept sondition ==\n");

    /* Create test socket1 */
    s1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s1 == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(12345);

    /* Bind the socket */
    if( bind( s1, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if( listen( s1, 1) < 0 )
    {
        ConPrintf("failed listen (%d)\n",fdError());
        goto leave;
    }

    /* Setup for non-blocking */
    tmp = 0;
    setsockopt( s1, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof( tmp ) );

    ConPrintf("Calling non-blocking Accept()...\n");
    size = sizeof( sin1 );
    s2 = accept( s1, (PSA)&sin1, &size );
    if( s2 != INVALID_SOCKET )
        ConPrintf("Accept returned a socket - This is an error\n");

    if( fdError() == EWOULDBLOCK )
        ConPrintf("Accept correctly returned EWOULDBLOCK\n");
    else
        ConPrintf("Accept returned bad error code\n");

    ConPrintf("Calling blocking Accept()...\n");

    /* Setup for blocking */
    tmp = 1;
    setsockopt( s1, SOL_SOCKET, SO_BLOCKING, &tmp, sizeof( tmp ) );

    /* Create a thread to close or shutdown this socket */
    if( fClose )
    {
        if( !TaskCreate( CloseTask, "CloseTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }
    else
    {
        if( !TaskCreate( ShutdownTask, "ShutdownTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }

    size = sizeof( sin1 );
    s2 = accept( s1, (PSA)&sin1, &size );
    if( s2 != INVALID_SOCKET )
        ConPrintf("Accept returned a socket - This is an error\n");

    tmp = fdError();
    if( tmp==EBADF && fClose )
    {
        ConPrintf("Accept correctly returned EBADF\n");
        s1 = INVALID_SOCKET;
    }
    else if( tmp==ECONNABORTED && !fClose )
        ConPrintf("Accept correctly returned ECONNABORTED\n");
    else
        ConPrintf("Accept returned unexpected error code (%d)\n",tmp);

leave:
     if( s2 != INVALID_SOCKET )
         fdClose(s2);
     if( s1 != INVALID_SOCKET )
         fdClose(s1);

    ConPrintf("== End Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* ShutdownTest2() */
/* Test shutdown/close of a listening socket in "select" */
/*---------------------------------------------------------------------- */
static void ShutdownTest2( IPN IPAddr, int fClose )
{
    SOCKET  s1 = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    int     tmp,cnt,size;
    fd_set  ibits;
    struct  sockaddr_in sin1;

    if( fClose )
        ConPrintf("\n== Test fdClose() on Listen/Select sondition ==\n");
    else
        ConPrintf("\n== Test shutdown() on Listen/Select sondition ==\n");

    /* Create test socket1 */
    s1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( s1 == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(12345);

    /* Bind the socket */
    if( bind( s1, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if( listen( s1, 1) < 0 )
    {
        ConPrintf("failed listen (%d)\n",fdError());
        goto leave;
    }

    /* Create a thread to close or shutdown this socket */
    if( fClose )
    {
        if( !TaskCreate( CloseTask, "CloseTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }
    else
    {
        if( !TaskCreate( ShutdownTask, "ShutdownTask", OS_TASKPRINORM,
                         0x1000, (UINT32)TaskSelf(), (UINT32)s1, 0 ) )
            goto leave;
    }

    FD_ZERO(&ibits);
    FD_SET(s1, &ibits);

    ConPrintf("Calling fdSelect() ...\n");
    cnt = fdSelect( (int)s1, &ibits, 0, 0, 0 );

    if( !cnt )
        ConPrintf("Select returned NULL - This is an error\n");
    if( cnt < 0 )
    {
        tmp = fdError();
        if( fClose && tmp == EBADF )
        {
            ConPrintf("fdSelect correctly returned EBADF\n");
            s1 = INVALID_SOCKET;
        }
        else
            ConPrintf("fdSelect returned unexpected error code (%d)\n",tmp);
    }
    else
    {
        if( fClose )
            ConPrintf("Error: we should not be here!\n");

        if( FD_ISSET(s1, &ibits) )
        {
            ConPrintf("Socket is now readable\n");

            size = sizeof( sin1 );
            s2 = accept( s1, (PSA)&sin1, &size );
            if( s2 != INVALID_SOCKET )
                ConPrintf("Accept returned a socket - This is an error\n");

            if( fdError() == ECONNABORTED )
                ConPrintf("Accept correctly returned ECONNABORTED\n");
            else
                ConPrintf("Accept returned bad error code\n");
        }
    }

leave:
     if( s2 != INVALID_SOCKET )
         fdClose(s2);
     if( s1 != INVALID_SOCKET )
         fdClose(s1);

    ConPrintf("== End Test ==\n\n");
}

/*---------------------------------------------------------------------- */
/* CloseTask() */
/* Task to close a shared LISTEN socket */
/*---------------------------------------------------------------------- */
/* ARGSUSED */
static void CloseTask( HANDLE hTaskParent, SOCKET s )
{
    fdOpenSession( TaskSelf() );

    ConPrintf("Child task spawned successfully - Calling fdClose()\n");

    /* Shutting down listen for read should wake our parent */
    fdClose(s);

    /* Small delay so we can see the main thread quitting immediately */
    /* after the "Passed" message */
    TaskSleep(2000);

    fdCloseSession( TaskSelf() );
    TaskExit();
}

/*---------------------------------------------------------------------- */
/* ShutdownTask() */
/* Task to shutdown a shared LISTEN socket */
/*---------------------------------------------------------------------- */
/* ARGSUSED */
static void ShutdownTask( HANDLE hTaskParent, SOCKET s )
{
    fdOpenSession( TaskSelf() );

    ConPrintf("Child task spawned successfully - Calling shutdown()\n");

    /* Shutting down listen for read should wake our parent */
    shutdown( s, SHUT_RD );

    /* Small delay so we can see the main thread quitting immediately */
    /* after the "Passed" message */
    TaskSleep(2000);

    fdCloseSession( TaskSelf() );
    TaskExit();
}

/*------------------------------------------------------------------------- */
/* StatusTest() */
/* Test the various status conditions of file descriptors */
/*------------------------------------------------------------------------- */
static void StatusTest( IPN IPAddr )
{
    SOCKET stcpl      = INVALID_SOCKET;
    SOCKET stcp_peer  = INVALID_SOCKET;
    SOCKET stcp_child = INVALID_SOCKET;
    SOCKET stcp       = INVALID_SOCKET;
    SOCKET sudp       = INVALID_SOCKET;
    SOCKET pipe1      = INVALID_SOCKET;
    SOCKET pipe2      = INVALID_SOCKET;
    struct  sockaddr_in sin1;
    int    error,status,size;
    char   *buffer;

    buffer = mmAlloc(1024);
    if( !buffer )
    {
        ConPrintf("failed to allocate temp buffer\n");
        goto leave;
    }

    /* Create TCP listen socket */
    stcpl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( stcpl == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for bind */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(12345);

    /* Bind the socket */
    if( bind( stcpl, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Start listening */
    if( listen( stcpl, 1) < 0 )
    {
        ConPrintf("failed listen (%d)\n",fdError());
        goto leave;
    }

    /* Setting socket buffer sizes on a listening socket only */
    /* affects spawned sockets returned from accept() */

    /* Set the TCP TX buffer to 1234; */
    size = 1234;
    if( setsockopt( stcpl, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size) ) )
    {
        ConPrintf("failed setsockopt (%d)\n",fdError());
        goto leave;
    }
    /* Set the TCP RX buffer to 4321; */
    size = 4321;
    if( setsockopt( stcpl, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size) ) )
    {
        ConPrintf("failed setsockopt (%d)\n",fdError());
        goto leave;
    }

    /* Create UDP socket */
    sudp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( sudp == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Set the UDP RX buffer to 1024; */
    size = 1024;
    if( setsockopt( sudp, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size) ) )
    {
        ConPrintf("failed setsockopt (%d)\n",fdError());
        goto leave;
    }

    /* Bind the socket */
    if( bind( sudp, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Connect the socket (to the same address) */
    if( connect( sudp, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    // Create the pipes
    if( pipe( &pipe1, &pipe2 ) != 0 )
    {
        ConPrintf("pipe create failed\n");
        goto leave;
    }

    /* Create a TCP peer socket */
    stcp_peer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( stcp_peer == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
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
        ConPrintf("failed connect (%d)\n",fdError());
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
        ConPrintf("failed accept (%d)\n",fdError());
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

    if( !error )
        ConPrintf("\nTest Complete - No errors detected\n\n");
    else
        ConPrintf("\nTest Completed with Errors!\n\n");

leave:
    if( stcpl      != INVALID_SOCKET)
        fdClose(stcpl);
    if( stcp_peer  != INVALID_SOCKET)
        fdClose(stcp_peer);
    if( stcp_child != INVALID_SOCKET)
        fdClose(stcp_child);
    if( stcp       != INVALID_SOCKET)
        fdClose(stcp);
    if( sudp       != INVALID_SOCKET)
        fdClose(sudp);
    if( pipe1      != INVALID_SOCKET)
        fdClose(pipe1);
    if( pipe2      != INVALID_SOCKET)
        fdClose(pipe2);

    if( buffer )
        mmFree(buffer);
}


/*------------------------------------------------------------------------- */
/* PollCounter() */
/* This function counts in a loop. It is launched as a low priority */
/* task the first time the "test counter" command it used. The current */
/* counter can then be checked/cleared by typing the "test counter" */
/* command again. Note there is no way to unload the counting loop, and */
/* it will interfere with IDLE loop based operations. */
/*------------------------------------------------------------------------- */
static void PollCounter()
{
    volatile int i;

    PollRunning = 1;

    for(;;)
    {
        for(i=0; i<10000; i++);
        PollCount++;
    }
}


/*---------------------------------------------------------------------- */
/* ShareRxTest() */
/* Test ECHO with a shared UDP socket using two tasks */
/*---------------------------------------------------------------------- */
static void ShareRxTest( IPN IPAddr )
{
    SOCKET  s = INVALID_SOCKET;
    SOCKET  s2 = INVALID_SOCKET;
    struct  sockaddr_in sin1;
    int     i;
    int     bytesReceived;

    ConPrintf("\n== Start Shared RX UDP Socket Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(1234);

    /* Connect socket */
    if ( bind( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Create a thread to receive data */
    if( !TaskCreate( UdpShareRX, "Receiver", OS_TASKPRINORM, 0x1000,
                     (UINT32)s, 1, 0 ) )
        goto leave;

    /* Create a second thread to receive data */
    if( !TaskCreate( UdpShareRX, "Receiver", OS_TASKPRINORM, 0x1000,
                     (UINT32)s, 2, 0 ) )
        goto leave;

    for( i=0; i<3; i++ )
    {
        ConPrintf("Sender sleeping...\n");
        TaskSleep(3000);

        ConPrintf("Sender sending...\n");

        /* Create test socket */
        s2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if( s2 == INVALID_SOCKET )
        {
            ConPrintf("failed socket create (%d)\n",fdError());
            goto leave;
        }

        bytesReceived = sendto( s2, (UINT8 *)&s2, 4, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
        if (bytesReceived < 0) {
            ConPrintf("ShareRxTest: error sending to host.\n");
        }

        fdClose( s2 );
    }

    ConPrintf("Sender sleeping...\n");
    TaskSleep(3000);

    ConPrintf("Sender closing...\n");

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End Shared TCP Socket Echo Test ==\n\n");
}


/*---------------------------------------------------------------------- */
/* UdpShareRX() */
/* Task to receive data on a shared socket */
/*---------------------------------------------------------------------- */
static void UdpShareRX( SOCKET s, int index )
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
