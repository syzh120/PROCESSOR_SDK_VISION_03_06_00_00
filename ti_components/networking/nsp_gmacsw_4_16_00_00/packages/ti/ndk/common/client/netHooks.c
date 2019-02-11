/*
 *  netHooks.c
 */

/*
 * Copyright (C) 2007-2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/_stack.h>
#include <ti/ndk/inc/tools/servers.h>
#include <ti/ndk/inc/tools/console.h>
#include <ti/nsp/drv/inc/gmacsw.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

extern Void receive();
extern void AddWebFiles(void);

static HANDLE hEcho = 0;
static HANDLE hEchoUdp = 0;
static HANDLE hData = 0;
static HANDLE hNull = 0;
static HANDLE hOob = 0;

#if defined (NDK_ENABLE_IPV6)
#define TCPPORT 5544
#define TCPHANDLERSTACK 1024
#endif

#if defined (NDK_ENABLE_IPV6)
/*
 *  ======== IPv6DADStatus ========
 *  IPv6 initialization callback function
 */
static void IPv6DADStatus(IP6N Address, unsigned short dev_index,
                                 unsigned char Status)
{
    char strIPAddress[40];

    /* Convert the IP Address to String Format. */
    inet_ntop(AF_INET6, &Address, strIPAddress, 40);

    /* Print the status of the address. */
    printf("  Network :Address %s on device %d is %s\n", strIPAddress, dev_index,
            (Status == 1) ? "UNIQUE" : "DUPLICATE");

    System_flush();

    return;
}
#endif
/*
 *  ======== stackInitHookStaticEth1 ========
 *  This function configures the static IP settings for interface 2
 *  It is called when 'enableStaticIpEth1' flag is set to 1 in application cfg
 */
void stackInitHookStaticEth1(void *hCfg)
{
    /*Static IP Address settings for interface 2*/
    const char *ip_addr_2 = "192.168.2.4";
    const char *ip_mask_2 = "255.255.255.0";
    const char *ip_gateway_2 = "192.168.2.1";

    CI_IPNET ip_net;
    CI_ROUTE route;
    /*Add IP Address for the interface 2*/
    ip_net.IPAddr = inet_addr(ip_addr_2);
    ip_net.IPMask = inet_addr(ip_mask_2);
    CfgAddEntry(hCfg, CFGTAG_IPNET, 2, 0, sizeof(CI_IPNET), (UINT8 *)&ip_net, 0);

    /*Add gateway for interface 2*/
    bzero(&route, sizeof(route));
    route.IPDestAddr = 0;
    route.IPDestMask = 0;
    route.IPGateAddr = inet_addr(ip_gateway_2);
    CfgAddEntry(hCfg, CFGTAG_ROUTE, 0, 0, sizeof(CI_ROUTE), (UINT8 *)&route, 0);

    AddWebFiles();
}
/*
 *  ======== stackInitHookDynEth1 ========
 *  This function configures the dynamic IP settings for interface 2
 *  It is called when 'enableStaticIpEth1' flag is set to 0 in application cfg
 */
void stackInitHookDynEth1(void *hCfg)
{
    /*Add the setup for DHCP for interface 2*/
    CI_SERVICE_DHCPC dhcpc;
    static UINT8 DHCP_OPTIONS[] = { DHCPOPT_SUBNET_MASK };

    bzero(&dhcpc, sizeof(dhcpc));
    dhcpc.cisargs.Mode = 1;
    dhcpc.cisargs.IfIdx = 2;
    dhcpc.param.pOptions = DHCP_OPTIONS;
    dhcpc.param.len = 1;

    CfgAddEntry(hCfg, CFGTAG_SERVICE, CFGITEM_SERVICE_DHCPCLIENT, 0, sizeof(dhcpc), (UINT8 *)&dhcpc, 0);

    AddWebFiles();
}


void netOpenHook()
{
    // Create our local servers
    hEcho = DaemonNew( SOCK_STREAMNC, 0, 7, dtask_tcp_echo,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    hEchoUdp = DaemonNew( SOCK_DGRAM, 0, 7, dtask_udp_echo,
                          OS_TASKPRINORM, OS_TASKSTKNORM, 0, 1 );
    hData = DaemonNew( SOCK_STREAM, 0, 1000, dtask_tcp_datasrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    hNull = DaemonNew( SOCK_STREAMNC, 0, 1001, dtask_tcp_nullsrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    hOob  = DaemonNew( SOCK_STREAMNC, 0, 999, dtask_tcp_oobsrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );

#if defined (NDK_ENABLE_IPV6)
    Error_Block eb;
    Int32 status;
    UInt32 dev_index = 1;

    /* Make sure Error_Block is initialized */
    Error_init(&eb);

    status = IPv6InterfaceInit(dev_index, IPv6DADStatus);
    if (status < 0) {
        printf("  Network: Error %d: failed to add IPv6 interface\n", status);
    }
#if defined (NDK_ENABLE_IPV6)
    /* Make sure to start this task after IP address is acquired */
    HANDLE taskHandle;
    Task_Params taskParams;
    Void tcpHandler(UArg arg0, UArg arg1);

    /*
     *  Create the Task that farms out incoming TCP connections.
     *  arg0 will be the port that this task listens to. arg1 is the family,
     *  set for IPv6 in this example.
     */
    Task_Params_init(&taskParams);
    taskParams.stackSize = TCPHANDLERSTACK;
    taskParams.priority = 1;
    taskParams.arg0 = TCPPORT;
    taskParams.arg1 = AF_INET6;
    taskHandle = Task_create((Task_FuncPtr)tcpHandler, &taskParams, &eb);
    if (taskHandle == NULL)
    {
        System_printf("Error: Failed to create tcpHandler Task\n");
    }
#endif

#endif
#ifdef UDP_BENCHMARKING_TEST
    void UdpBenchmarkingTestTask(UArg arg0, UArg arg1);

    HANDLE udpTestTask = 0;

    /* Start the packet processing tasks now that the channels are open */
    udpTestTask  = TaskCreate(&UdpBenchmarkingTestTask,
                              "UdpBenchmarkingTestTask",
                              (uint32_t)OS_TASKPRINORM,
                              (uint)2048,
                              (uint32_t) 0, (uint32_t)0, (uint32_t)0 );
#endif
}

void netCloseHook()
{
    DaemonFree(hOob);
    DaemonFree(hNull);
    DaemonFree(hData);
    DaemonFree(hEchoUdp);
    DaemonFree(hEcho);

#if defined (NDK_ENABLE_IPV6)
    Int32 status;
    UInt32 dev_index = 1;
    /* Enter the kernel Mode. */
    llEnter ();
    status = IPv6InterfaceDeInit(dev_index);
    llExit ();
    /* Were we able to deinitialize the stack? */
    if (status < 0)
    {
        printf(
                "  Network: Error - Unable to de-initialize the IPv6 stack on device %d\n",
                dev_index);
    }
    else
    {
        printf("  Network: IPv6 stack has been deinitialized on %d\n", dev_index);
    }
#endif

    // Kill any active console
    ConsoleClose();
}
