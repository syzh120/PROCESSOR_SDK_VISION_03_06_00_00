/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

/*!
 *  \file nsp_test_server.c
 *
 *  \brief NSP test server
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Hwi.h>

/* NDK Dependencies */
#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/tools/servers.h>
#include <ti/ndk/inc/stkmain.h>
#include <ti/ndk/inc/stack/stack.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>

/* NULL stack header file */
#include "null_stack.h"

/* Client/Server Common Header */
#include "../../../common/test_common.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

extern xdc_Void ti_ndk_config_Global_stackThread(xdc_UArg,xdc_UArg);


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define EXPERIMENTAL_ETHERTYPE      (0x88B5U)
#define CPTS_ETHERTYPE              (0x88F7U)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef enum status_e
{
    SUCCESS = 0,
    RESTART = 1,
    FAILURE = -1,
    SEND_SIZE_FAILURE = -2,
    UNABLE_TO_OBTAIN_LOAD = -3,
    UNEXPECTED_CMD_SIZE = -4,
    NULL_POINTER = -5,
    ACK_FAILURE = -6
}
Status_e;


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static int LOCAL_sendLoadInfo(SOCKET s);

static int LOCAL_sendHWErrors(SOCKET s);
static int LOCAL_sendHWStats(SOCKET s);
static int LOCAL_clearHWStats(void);

static int LOCAL_sendSWStats(SOCKET s);
static int LOCAL_clearSWStats(void);

static int LOCAL_sendNDKIpStats(SOCKET s);
static int LOCAL_clearNDKIpStats(void);

static bool LOCAL_needsAck(uint32_t cmdId);
static int LOCAL_handleCommand(SOCKET s, uint8_t *buf, uint32_t size);
static int LOCAL_commandServer(SOCKET s, UINT32 unused);

static void LOCAL_restartTask(UArg arg0, UArg arg1);

static void LOCAL_cptsEventNotify(void *hCallbackArg);
static int LOCAL_sendCPTSFreqs(SOCKET s, uint32_t measured, uint32_t reported);
static int LOCAL_sendCPTSEvent(SOCKET s);
static int LOCAL_sendTxCPTSFrames(void);
static int LOCAL_checkCPTSFreq(SOCKET s);


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

static HANDLE hTCPEcho = 0;
static HANDLE hUDPEcho = 0;
static HANDLE hTestServer = 0;
static Task_Handle hRawEchoTask = NULL;
static GMACSW_DeviceHandle hGMACSW = NULL;
static NULL_Handle hNullStack = NULL;

static bool     LOCAL_TCPEchoOn = true;
static bool     LOCAL_UDPEchoOn = true;
static bool     LOCAL_RawEchoOn = false;

static bool     LOCAL_CPTSHandlerRegistered = false;

/* Semaphore to sync the NSP/NDK restart activity */
static Semaphore_Handle restartSem = NULL;

static volatile uint32_t LOCAL_tcpPacketCount = 0;
static volatile uint32_t LOCAL_udpPacketCount = 0;
static volatile uint32_t LOCAL_rawPacketCount = 0;
static volatile uint32_t LOCAL_cptsEventCount = 0;

/* Memory to be used for the CPTS event SW queue */
static CPTS_Event gCPTSEvents[16];


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* my_tcp_echo() - TCP Echo Server Daemon Function (SOCK_STREAMNC) */
/* (SOCK_STREAMNC, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int my_tcp_echo( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i;
    char           *pBuf;
    HANDLE         hBuffer;

    (void)unused;

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    i = 1;
    setsockopt( s, IPPROTO_TCP, TCP_NOPUSH, &i, 4 );

    for(;;)
    {
        i = (int)recvnc( s, (void **)&pBuf, 0, &hBuffer );

        /* If we read data, echo it back if echo is enabled */
        if( i > 0 )
        {
            if (LOCAL_TCPEchoOn)
            {
                if( send( s, pBuf, i, 0 ) < 0 )
                    break;
            }
            LOCAL_tcpPacketCount++;
            recvncfree( hBuffer );
        }
        /* If the connection got an error or disconnect, close */
        else
            break;
    }

    fdClose( s );

    /* Return "0" since we closed the socket */
    return(0);
}

/* my_udp_echo() - UDP Echo Server Daemon Function */
/* (SOCK_DGRAM, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int my_udp_echo( SOCKET s, UINT32 unused )
{
    struct sockaddr_in sin1;
    int                i,tmp;
    char               *pBuf;
    HANDLE             hBuffer;

    (void)unused;

    /* Configure our socket timeout to be 3 seconds */
    {
        struct timeval     to;

        to.tv_sec  = 3;
        to.tv_usec = 0;
        setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
        setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );
    }

#if (0)
    /* Increase the socket buffer size */
    {
        int32_t size = 32*1024;
        setsockopt( s, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)));
    }
#endif

    for(;;)
    {
        tmp = sizeof( sin1 );
        i = (int)recvncfrom( s, (void **)&pBuf, 0,(struct sockaddr *)&sin1, &tmp, &hBuffer );

        /* Spit any data back out */
        if( i >= 0 )
        {
            if (LOCAL_UDPEchoOn)
            {
                sendto( s, pBuf, i, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
            }
            LOCAL_udpPacketCount++;
            recvncfree( hBuffer );
        }
        else
            break;
    }

    /* Since the socket is still open, return "1" */
    /* (we need to leave UDP sockets open) */
    return(1);
}

/* Rx task for RAW socket packets */
void my_raw_echo_task(UArg arg0, UArg arg1)
{
    SOCKET s = INVALID_SOCKET;
    uint8_t macAddress[6];

    HANDLE pBufHandle = NULL;
    uint8_t *pRecvPacket = NULL;
    int32_t i;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Open the raw socket which gets used for both Tx and Rx */
    s = socket(AF_RAWETH, SOCK_RAWETH, EXPERIMENTAL_ETHERTYPE);

    if( s == INVALID_SOCKET )
    {
        printf("Fail socket, %d\n", fdError());
        fdCloseSession (Task_self());
        return;
    }

    /* Set some socket options */
    {
        int ifVal = 1;
        int retVal = 0;

        /* Set socket option to set IF device */
        retVal = setsockopt(s, SOL_SOCKET, SO_IFDEVICE, &ifVal, sizeof(ifVal));
        if (retVal)
        {
            printf("Error in setsockopt() API.\n");
        }

        /*
         * Set max receive size to handle all possible packets that could be received at
         * once from the hardware.
         */
        ifVal = 64*1536;
        retVal = setsockopt(s, SOL_SOCKET, SO_RCVBUF, &ifVal, sizeof(ifVal));
        if (retVal)
        {
            printf("Error in setsockopt() API.\n");
        }
    }

    /* Get the interface MAC address using the NIMU ioctl()*/
    {
        int ret_code;
        uint16_t        dev_index;
        NIMU_IF_REQ     if_req;

        if_req.index = 1;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            printf ("Error: Incorrect device index specified\n");
            exit(1);
        }

        if_req.name[0] = 0;
        if_req.index   = dev_index;

        /* Get the device MAC Address */
        ret_code = NIMUIoctl (NIMU_GET_DEVICE_MAC, &if_req, &macAddress, sizeof(macAddress));
        if (ret_code < 0)
        {
            printf ("NIMUIOCTL Failed with error code: %d\n",ret_code);
            return;
        }
    }

    /* Rx/Loopback loop */
    for(;;)
    {
        /* Attempt to recv a packet */
        i = recvnc(s, (void **)&pRecvPacket, 0x0, &pBufHandle);

        if( i >= 0 )
        {
            if (LOCAL_RawEchoOn)
            {
                /* Swap source and destination MAC address */
                memcpy((void *)&pRecvPacket[0],(void *)&pRecvPacket[6],sizeof(macAddress));

                memcpy((void *)&pRecvPacket[6], (void *)macAddress, sizeof(macAddress));

                send(s, (void *)pRecvPacket, i, 0x0);
            }
            LOCAL_rawPacketCount++;
            recvncfree(pBufHandle);
        }
        else
        {
            break;
        }
    }
}

void netOpenHook(void)
{
    printf("[Test server]: netOpenHook!\n");

    /* Get GMACSW hardware driver handle */
    hGMACSW = GMACSW_open(NULL);

    /* Clear HW Stats */
    LOCAL_clearHWStats();

    /* Clear SW Stats */
    LOCAL_clearSWStats();

    /* Clear NDK IP stack stats */
    LOCAL_clearNDKIpStats();

    /* Set the control port daemon to be normal priority */
    hTestServer = DaemonNew( SOCK_STREAMNC, 0, TEST_CMD_PORT, LOCAL_commandServer,
                           OS_TASKPRINORM, OS_TASKSTKNORM, 0, 1 );

    /* Set the traffic test daemons to be higher priority */
    hTCPEcho = DaemonNew( SOCK_STREAMNC, 0, TEST_TCP_PORT, my_tcp_echo,
                       OS_TASKPRIHIGH, OS_TASKSTKNORM, 0, 3 );

    hUDPEcho = DaemonNew( SOCK_DGRAM, 0, TEST_UDP_PORT, my_udp_echo,
                       OS_TASKPRIHIGH, OS_TASKSTKNORM, 0, 1 );

    /* NDK Raw socket Rx task */
    {
        Task_Params taskParams;
        Task_Params_init(&taskParams);
        taskParams.instance->name = "Raw_Receiver";
        taskParams.stackSize = 0x1000;
        taskParams.priority = 1;
        hRawEchoTask = Task_create((Task_FuncPtr)my_raw_echo_task, &taskParams,NULL);
    }
}

void netCloseHook(void)
{
    printf("[Test server]: netCloseHook!\n");

    Task_delete(&hRawEchoTask);

    DaemonFree(hUDPEcho);
    DaemonFree(hTCPEcho);
    DaemonFree(hTestServer);

    if (hGMACSW != NULL)
    {
        GMACSW_close(hGMACSW);
    }

    Semaphore_post(restartSem);
}

int main()
{
    Semaphore_Params semParams;
    Task_Params taskParams;

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_COUNTING;
    restartSem = Semaphore_create(0, &semParams, NULL);

    Task_Params_init(&taskParams);
    taskParams.stackSize = 2048;
    taskParams.priority = 1;
    taskParams.instance->name = "NSP_Test_Server_RestartTask";
    Task_create(&LOCAL_restartTask, &taskParams, NULL);

    BIOS_start();

    return 0;
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static bool LOCAL_needsAck(uint32_t cmdId)
{
    bool retVal = false;

    switch(cmdId)
    {
        case TEST_CMD_RESTART_NSP:
        case TEST_CMD_START_NULL_STACK:
        case TEST_CMD_STOP_NULL_STACK:
        case TEST_CMD_GET_LOAD_INFO:
        case TEST_CMD_GET_HW_ERRORS:
        case TEST_CMD_GET_HW_STATS:
        case TEST_CMD_CLEAR_HW_STATS:
        case TEST_CMD_GET_SW_STATS:
        case TEST_CMD_CLEAR_SW_STATS:
        case TEST_CMD_GET_NDK_STATS:
        case TEST_CMD_CLEAR_NDK_STATS:
        case TEST_CMD_DISABLE_TCP_ECHO:
        case TEST_CMD_ENABLE_TCP_ECHO:
        case TEST_CMD_DISABLE_UDP_ECHO:
        case TEST_CMD_ENABLE_UDP_ECHO:
        case TEST_CMD_CPTS_REGISTER:
        case TEST_CMD_CPTS_UNREGISTER:
        case TEST_CMD_CPTS_FREQ_CHECK:
        case TEST_CMD_CPTS_SEND_ETH_TX:
        case TEST_CMD_GET_CPTS_EVENT:
            retVal = true;
            break;
        default:
            break;
    }
    return retVal;
}

static int LOCAL_handleCommand(SOCKET s, uint8_t *buf, uint32_t size)
{
    uint32_t *pBuf = (uint32_t *)buf;
    uint32_t cmdId;
    int ret = SUCCESS;

    if (size < 4) return UNEXPECTED_CMD_SIZE;

    cmdId = ntohl(pBuf[0]);

    /*
     * Protocol is 32-bit command ID,  0 or more arguments depending on
     * command id. ACK is done by echoing the command ID back to the host.
     */
    if (LOCAL_needsAck(cmdId) == true)
    {
        int result = send(s, buf, size, 0);
        if (result < 0) return ACK_FAILURE;
        if (result != size) return SEND_SIZE_FAILURE;
    }

    switch(cmdId)
    {
        case TEST_CMD_RESTART_NSP:
            printf("[Test server]: TEST_CMD_RESTART_NSP!\n");
            /* Stop the network stack. */
            NC_NetStop(0);
            ret = RESTART;
            break;
        case TEST_CMD_START_NULL_STACK:
            hNullStack = NULL_open();
            if (NULL == hNullStack)
            {
                ret = FAILURE;
            }
            else
            {
                ret = SUCCESS;
            }
            break;
        case TEST_CMD_STOP_NULL_STACK:
            NULL_close(hNullStack);
            hNullStack = NULL;
            ret = SUCCESS;
            break;
        case TEST_CMD_GET_LOAD_INFO:
            ret = LOCAL_sendLoadInfo(s);
            break;
        case TEST_CMD_GET_HW_ERRORS:
            ret = LOCAL_sendHWErrors(s);
            break;
        case TEST_CMD_GET_HW_STATS:
            ret = LOCAL_sendHWStats(s);
            break;
        case TEST_CMD_CLEAR_HW_STATS:
            ret = LOCAL_clearHWStats();
            break;
        case TEST_CMD_GET_SW_STATS:
            ret = LOCAL_sendSWStats(s);
            break;
        case TEST_CMD_CLEAR_SW_STATS:
            ret = LOCAL_clearSWStats();
            break;
        case TEST_CMD_GET_NDK_STATS:
            ret = LOCAL_sendNDKIpStats(s);
            break;
        case TEST_CMD_CLEAR_NDK_STATS:
            ret = LOCAL_clearNDKIpStats();
            break;
        case TEST_CMD_DISABLE_TCP_ECHO:
            LOCAL_TCPEchoOn = false;
            ret = SUCCESS;
            break;
        case TEST_CMD_ENABLE_TCP_ECHO:
            LOCAL_TCPEchoOn = true;
            ret = SUCCESS;
            break;
        case TEST_CMD_DISABLE_UDP_ECHO:
            LOCAL_UDPEchoOn = false;
            ret = SUCCESS;
            break;
        case TEST_CMD_ENABLE_UDP_ECHO:
            LOCAL_UDPEchoOn = true;
            ret = SUCCESS;
            break;
        case TEST_CMD_CPTS_REGISTER:
        {
            CPTS_StackConfig  cptsStackConfig;
            uint32_t status;

            cptsStackConfig.eventMem                = gCPTSEvents;
            cptsStackConfig.eventCount              = 16;
            cptsStackConfig.vlanType                = CPTS_VLAN_TYPE_NONE;
            cptsStackConfig.portSelection           = CPTS_PORT_SELECTION_MAC_BOTH;
            cptsStackConfig.pEventNotifyCallback    = &LOCAL_cptsEventNotify;
            cptsStackConfig.hEventNotifyCallbackArg = (void *) &LOCAL_cptsEventCount;

            /* ToDo: Check return value to make sure it worked */
            status = GMACSW_ioctl(hGMACSW,
                        GMACSW_IOCTL_CPTS_REGISTER_STACK,
                        (void *)&cptsStackConfig,
                        sizeof(CPTS_StackConfig));

            ret = (status == CPTS_SUCCESS) ? SUCCESS : FAILURE;
            LOCAL_CPTSHandlerRegistered = (status == CPTS_SUCCESS) ?  true : false;


            break;
        }
        case TEST_CMD_CPTS_UNREGISTER:
        {
            uint32_t status;

            /* Unregister the CPTS notify callback */
            status = GMACSW_ioctl(hGMACSW,
                        GMACSW_IOCTL_CPTS_UNREGISTER_STACK,
                        NULL,
                        0U);

            LOCAL_CPTSHandlerRegistered = false;

            ret = (status == CPTS_SUCCESS) ? SUCCESS : FAILURE;
            break;
        }
        case TEST_CMD_CPTS_FREQ_CHECK:
        {
            ret = LOCAL_checkCPTSFreq(s);
            break;
        }
        case TEST_CMD_GET_CPTS_EVENT:
        {
            ret = LOCAL_sendCPTSEvent(s);
            break;
        }
        case TEST_CMD_CPTS_SEND_ETH_TX:
        {
            ret = LOCAL_sendTxCPTSFrames();
            break;
        }
        default:
            printf("[Test server]: Received unknown command = 0x%8X!\n", (unsigned int)cmdId);
            ret = FAILURE;
            break;
    }
    return ret;
}

static int LOCAL_commandServer(SOCKET s, UINT32 unused)
{
    struct timeval to;
    int ret, recv_size;
    uint8_t *pBuf;
    HANDLE hBuffer;
    const int socketOptVal = 1;

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec = 5;
    to.tv_usec = 0;
    ret = setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof(to));
    if (ret < 0) {
        printf("[Test server]: Unable to configure send timeout!\n");
        goto teardown;
    }

    ret = setsockopt(s, IPPROTO_TCP, TCP_NOPUSH, (void *)&socketOptVal, sizeof(socketOptVal));
    if (ret < 0) {
        printf("[Test server]: Unable to configure NOPUSH option for TCP!\n");
        goto teardown;
    }

    while (true)
    {
        pBuf = NULL;
        hBuffer = NULL;
        recv_size = recvnc(s, (void **)&pBuf, 0, &hBuffer);
        if (recv_size < 0) {
            printf("[Test server]: receive failed!\n");
            ret = recv_size;
            break;
        }
        if (recv_size == 0) {
            printf("[Test server]: server connection closed!\n");
            ret = FAILURE;
            break;
        }

        if (pBuf == NULL || hBuffer == NULL) {
            printf("[Test server]: no valid buffer pointer or handle!\n");
            ret = FAILURE;
            break;
        }

        ret = LOCAL_handleCommand(s, pBuf, recv_size);
        recvncfree(hBuffer);
        if (ret == RESTART)
        {
            goto teardown;
        }
        else if (ret != SUCCESS)
        {
            if (ret == ACK_FAILURE)
            {
                printf("[Test server]: command acknowledgement failed!\n");
            }
            else
            {
                printf("[Test server]: error handling command (ret: %d)!\n", ret);
            }
        }
    }

teardown:
    fdClose(s);
    printf("[Test server]: exiting test server daemon!\n");
    return ret;
}

static void LOCAL_restartTask(UArg arg0, UArg arg1)
{
    while (1)
    {
        Semaphore_pend(restartSem, BIOS_WAIT_FOREVER);

        printf("[Test server]: restarting the NDK/NSP!\n");

        /* NDK Stack will be started. */
        {
            Task_Handle hNetStackTask = NULL;
            Task_Params taskParams;

            Task_Params_init(&taskParams);
            taskParams.instance->name = "ti_ndk_config_Global_stackThread";
            taskParams.priority = 0x5;
            taskParams.arg0 = 0u;
            taskParams.arg1 = 0u;
            taskParams.stackSize = (SizeT) 0x2000;

            hNetStackTask = Task_create(&ti_ndk_config_Global_stackThread, &taskParams, NULL);
            if (hNetStackTask == NULL)
            {
                printf("[Test server]: restarting ti_ndk_config_Global_stackThread failed\n");
                break;
            }
            else
            {
                /* Register with NDK. Only then socket open will succeed.*/
                fdOpenSession(hNetStackTask);
            }
        }
    }
}

static int LOCAL_sendLoadInfo(SOCKET s)
{
    Load_Stat stat;
    uint32_t buf[6];
    int ret;

    ret = Load_getGlobalHwiLoad(&stat);
    if (ret == 0) return UNABLE_TO_OBTAIN_LOAD;

    buf[0] = htonl(Load_getCPULoad());
    buf[1] = htonl(Load_calculateLoad(&stat));
    /* TODO: Get actual ndk2nsp task loads here */
    //buf[2] = htonl(NDK2NSP_ioctl(hTfdtp->hNDK2NSP, NDK2NSP_IOCTL_GET_RXTASK_LOAD, 0, 0));
    //buf[3] = htonl(NDK2NSP_ioctl(hTfdtp->hNDK2NSP, NDK2NSP_IOCTL_GET_TXTASK_LOAD, 0, 0));
    buf[2] = htonl(0);
    buf[3] = htonl(0);
    if (NULL != hNullStack)
    {
        buf[4] = htonl(NULL_getRxLoad(hNullStack));
        buf[5] = htonl(NULL_getTxLoad(hNullStack));
    }
    else
    {
        buf[4] = htonl(0);
        buf[5] = htonl(0);
    }

    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int LOCAL_sendHWErrors(SOCKET s)
{
    int ret;
    STATS_Statistics stats;
    uint32_t buf[9];

    if (hGMACSW == NULL) return NULL_POINTER;

    GMACSW_ioctl(hGMACSW,
                 GMACSW_IOCTL_STATS_GET_STATS,
                 (void *)&stats,
                 sizeof(STATS_Statistics));

    buf[0] = htonl((uint32_t)stats.RxSOFOverruns);
    buf[1] = htonl((uint32_t)stats.RxMOFOverruns);
    buf[2] = htonl((uint32_t)stats.RxDMAOverruns);
    buf[3] = htonl((uint32_t)stats.RxCRCErrors);
    buf[4] = htonl((uint32_t)stats.RxAlignCodeErrors);
    buf[5] = htonl((uint32_t)stats.RxOversized);
    buf[6] = htonl((uint32_t)stats.RxJabber);
    buf[7] = htonl((uint32_t)stats.RxUndersized);
    buf[8] = htonl((uint32_t)stats.RxFragments);

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_sendHWStats(SOCKET s)
{
    int ret;
    STATS_Statistics stats;
    uint32_t buf[10];

    if (hGMACSW == NULL) return NULL_POINTER;

    GMACSW_ioctl(hGMACSW,
                 GMACSW_IOCTL_STATS_GET_STATS,
                 (void *)&stats,
                 sizeof(STATS_Statistics));

    buf[0] = htonl((uint32_t)stats.RxGoodFrames);
    buf[1] = htonl((uint32_t)stats.RxBCastFrames);
    buf[2] = htonl((uint32_t)stats.RxMCastFrames);
    buf[3] = htonl((uint32_t)stats.RxPauseFrames);
    buf[4] = htonl((uint32_t)stats.RxOctets);
    buf[5] = htonl((uint32_t)stats.TxGoodFrames);
    buf[6] = htonl((uint32_t)stats.TxBCastFrames);
    buf[7] = htonl((uint32_t)stats.TxMCastFrames);
    buf[8] = htonl((uint32_t)stats.TxPauseFrames);
    buf[9] = htonl((uint32_t)stats.TxOctets);

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_clearHWStats(void)
{
    GMACSW_ioctl(
        hGMACSW,
        GMACSW_IOCTL_STATS_CLEAR_STATS,
        NULL,
        0U);

    return SUCCESS;
}

static int LOCAL_sendSWStats(SOCKET s)
{
    int ret;
    uint32_t buf[4];

    buf[0] = htonl((uint32_t)LOCAL_tcpPacketCount);
    buf[1] = htonl((uint32_t)LOCAL_udpPacketCount);

    if (NULL != hNullStack)
    {
        NULL_Stats stats;
        NULL_getStatistics(hNullStack, &stats);
        buf[2] = htonl(stats.packetCnt);
    }
    else
    {
        buf[2] = htonl((uint32_t)LOCAL_rawPacketCount);
    }

    buf[3] = htonl(LOCAL_cptsEventCount);

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_clearSWStats(void)
{
    LOCAL_tcpPacketCount = 0;
    LOCAL_udpPacketCount = 0;

    if (NULL != hNullStack)
    {
        NULL_clearStatistics(hNullStack);
    }
    else
    {
        LOCAL_rawPacketCount = 0;
    }

    if (LOCAL_CPTSHandlerRegistered)
    {
        GMACSW_ioctl(
            hGMACSW,
            GMACSW_IOCTL_CPTS_CLEAR_ALL_EVENTS,
            NULL,
            0U);
    }
    LOCAL_cptsEventCount = 0;

    return SUCCESS;
}

static int LOCAL_sendNDKIpStats(SOCKET s)
{
    int ret;
    uint32_t buf[20];

    /* UDP Tx Stats */
    buf[0]  = htonl((uint32_t)udps.RcvTotal);
    buf[1]  = htonl((uint32_t)udps.RcvShort);
    buf[2]  = htonl((uint32_t)udps.RcvBadLen);
    buf[3]  = htonl((uint32_t)udps.RcvBadSum);
    buf[4]  = htonl((uint32_t)udps.RcvFull);
    buf[5]  = htonl((uint32_t)udps.RcvNoPort);
    buf[6]  = htonl((uint32_t)udps.RcvNoPortB);

    /* TCP Tx Stats */
    buf[7]  = htonl((uint32_t)tcps.RcvTotal);
    buf[8]  = htonl((uint32_t)tcps.RcvShort);
    buf[9]  = htonl((uint32_t)tcps.RcvHdrSize);
    buf[10] = htonl((uint32_t)tcps.RcvBadSum);

    /* IP stats */
    buf[11] = htonl((uint32_t)ips.Total);
    buf[12] = htonl((uint32_t)ips.Odropped);
    buf[13] = htonl((uint32_t)ips.Badsum);
    buf[14] = htonl((uint32_t)ips.Badhlen);
    buf[15] = htonl((uint32_t)ips.Badlen);
    buf[16] = htonl((uint32_t)ips.Badoptions);
    buf[17] = htonl((uint32_t)ips.Badvers);
    buf[18] = htonl((uint32_t)ips.Noproto);
    buf[19] = htonl((uint32_t)ips.Delivered);

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_clearNDKIpStats(void)
{
    mmZeroInit( &udps, sizeof( UDPSTATS ) );
    mmZeroInit( &tcps, sizeof( TCPSTATS ) );
    mmZeroInit( &ips, sizeof( IPSTATS ) );

    return SUCCESS;
}

static void LOCAL_cptsEventNotify(void *hCallbackArg)
{
    uint32_t *pCounter = (uint32_t *) hCallbackArg;

    uint32_t key = Hwi_disable();

    *pCounter = *pCounter + 1;

    Hwi_restore(key);
}

static int LOCAL_sendCPTSFreqs(SOCKET s, uint32_t measured, uint32_t reported)
{
    int ret;
    uint32_t buf[2];

    buf[0] = htonl(measured);
    buf[1] = htonl(reported);

    ret = send(s, &buf, sizeof(buf), 0);
    return (ret < 0 ) ? ret : 0;
}

static int LOCAL_sendCPTSEvent(SOCKET s)
{
    int ret = FAILURE;
    uint32_t status;
    CPTS_Event *pEvent;
    uint32_t buf[5];

     /* Get CPTS events from GMACSW driver */
    status = GMACSW_ioctl(
        hGMACSW,
        GMACSW_IOCTL_CPTS_GET_EVENT,
        (void *) &pEvent,
        sizeof(CPTS_Event *));

    if (CPTS_SUCCESS == status)
    {
        uint32_t tsVal;

        {
            uint32_t key = Hwi_disable();
            LOCAL_cptsEventCount--;
            Hwi_restore(key);
        }
        buf[0] = htonl(pEvent->eventType);
        buf[1] = htonl(pEvent->messageType);
        buf[2] = htonl(pEvent->sequenceId);
        tsVal = (uint32_t)((pEvent->timeStamp >> 32) & 0xFFFFFFFFU);
        buf[3] = htonl(tsVal);
        tsVal = (uint32_t)(pEvent->timeStamp & 0xFFFFFFFFU);
        buf[4] = htonl(tsVal);

        /* Release the event back to the driver */
        GMACSW_ioctl(
            hGMACSW,
            GMACSW_IOCTL_CPTS_RELEASE_EVENT,
            pEvent,
            sizeof(CPTS_Event *));

        ret = send(s, &buf, sizeof(buf), 0);
        return (ret < 0 ) ? ret : SUCCESS;
    }

    return ret;
}

static int LOCAL_sendTxCPTSFrames(void)
{
    SOCKET s = INVALID_SOCKET;
    uint8_t srcMacAddress[6];
    uint8_t destMacAddress[6];

    HANDLE pBufHandle = NULL;
    uint8_t *pRecvPacket = NULL;
    int32_t i;

    int16_t sequenceID = 0;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Open the raw socket which gets used for both Tx and Rx */
    s = socket(AF_RAWETH, SOCK_RAWETH, CPTS_ETHERTYPE);

    if( s == INVALID_SOCKET )
    {
        printf("Fail socket, %d\n", fdError());
        fdCloseSession (Task_self());
        return FAILURE;
    }

    /* Set some socket options */
    {
        int ifVal = 1;
        int retVal = 0;

        /* Set socket option to set IF device */
        retVal = setsockopt(s, SOL_SOCKET, SO_IFDEVICE, &ifVal, sizeof(ifVal));
        if (retVal)
        {
            printf("Error in setsockopt() API.\n");
        }
    }

    /* Get the interface MAC address using the NIMU ioctl()*/
    {
        int ret_code;
        uint16_t        dev_index;
        NIMU_IF_REQ     if_req;

        if_req.index = 1;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            printf ("Error: Incorrect device index specified\n");
            exit(1);
        }

        if_req.name[0] = 0;
        if_req.index   = dev_index;

        /* Get the device MAC Address */
        ret_code = NIMUIoctl (NIMU_GET_DEVICE_MAC, &if_req, &srcMacAddress, sizeof(srcMacAddress));
        if (ret_code < 0)
        {
            printf ("NIMUIOCTL Failed with error code: %d\n",ret_code);
            return FAILURE;
        }
    }

    /* Attempt to recv a packet to get destination MAC and indicate readiness */
    i = recvnc(s, (void **)&pRecvPacket, 0x0, &pBufHandle);
    if( i >= 0 )
    {
        /* Swap source and destination MAC address */
        memcpy((void *)destMacAddress,(void *)&pRecvPacket[6],sizeof(destMacAddress));

        /* Setup the source and destination MAC addresses */
        memcpy((void *)&pRecvPacket[0], (void *)destMacAddress, sizeof(destMacAddress));
        memcpy((void *)&pRecvPacket[6], (void *)srcMacAddress, sizeof(srcMacAddress));

        /* Don't need to set Ethertype, it should be there already from what we received */

        /* Set message type and the sequence number*/
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_SYNC);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_DELAY_REQ);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_PDELAY_REQ);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_PDELAY_RESP);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_FOLLOW_UP);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_DELAY_RESP);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_PDELAY_RESP_FOLLOW_UP);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_ANNOUNCE);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_SIGNALING);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        /* Set message type and the sequence number */
        pRecvPacket[14] = (0x10U | CPTS_MESSAGE_MANAGEMENT);
        *((int16_t *)(pRecvPacket + 44)) = htons(sequenceID);
        sequenceID++;

        /* Send the packet */
        send(s, (void *)pRecvPacket, 64, 0x0);

        Task_sleep(10);

        recvncfree(pBufHandle);
    }
    else
    {
        return FAILURE;
    }

    fdClose(s);

    return SUCCESS;
}

static int LOCAL_checkCPTSFreq(SOCKET s)
{
    uint64_t ts1, ts2;
    uint32_t measuredFreq;
    uint32_t reportedFreq;
    uint32_t status;
    uint32_t currEventCount;

    CPTS_Event eventTemplate;
    CPTS_Event *pEvent = NULL;
    CPTS_LookupEventIoctlCmd cmd;

    eventTemplate.eventType = CPTS_EVENT_TIME_STAMP_PUSH;

    cmd.pEventTemplate = &eventTemplate;
    cmd.pReturnEvent = &pEvent;

    /* First issue a TS push and wait for it to get noticed */
    currEventCount = LOCAL_cptsEventCount;
    status = GMACSW_ioctl(hGMACSW,
                 GMACSW_IOCTL_CPTS_TIMESTAMP_PUSH,
                 NULL,
                 0U);
    if (CPTS_SUCCESS == status)
    {
        while (LOCAL_cptsEventCount == currEventCount);
    }
    else
    {
        return FAILURE;
    }



    /* Get CPTS events from GMACSW driver */
    status = GMACSW_ioctl(hGMACSW,
                 GMACSW_IOCTL_CPTS_LOOKUP_EVENT,
                 (void *) &cmd,
                 sizeof(CPTS_LookupEventIoctlCmd));
    if (CPTS_SUCCESS == status)
    {
        {
            uint32_t key = Hwi_disable();
            LOCAL_cptsEventCount--;
            Hwi_restore(key);
        }
        ts1 = pEvent->timeStamp;

        /* Release the CPTS event back to the GMACSW driver */
        GMACSW_ioctl(hGMACSW,
                     GMACSW_IOCTL_CPTS_RELEASE_EVENT,
                     (void *) pEvent,
                     sizeof(CPTS_Event *));

        /* Sleep 1 s */
        Task_sleep(1000);

        /* Issue another TS push */
        currEventCount = LOCAL_cptsEventCount;
        status = GMACSW_ioctl(hGMACSW,
                     GMACSW_IOCTL_CPTS_TIMESTAMP_PUSH,
                     NULL,
                     0U);
        if (CPTS_SUCCESS == status)
        {
            /* Wait for push event to get noticed */
            while (LOCAL_cptsEventCount == currEventCount);
        }
        else
        {
            return FAILURE;
        }

        /* Get CPTS events from GMACSW driver */
        status = GMACSW_ioctl(hGMACSW,
                    GMACSW_IOCTL_CPTS_LOOKUP_EVENT,
                    (void *) &cmd,
                    sizeof(CPTS_LookupEventIoctlCmd));

        if (CPTS_SUCCESS == status)
        {
            LOCAL_cptsEventCount--;
            ts2 = pEvent->timeStamp;

            /* Release the CPTS event back to the GMACSW driver */
            GMACSW_ioctl(hGMACSW,
                         GMACSW_IOCTL_CPTS_RELEASE_EVENT,
                         (void *) pEvent,
                         sizeof(CPTS_Event *));

            /* Calculate frequency based on timestamp measurements */
            measuredFreq = (uint32_t) (ts2-ts1);

            GMACSW_ioctl(hGMACSW,
                         GMACSW_IOCTL_CPTS_GET_FREQUENCY,
                         (void *) &reportedFreq,
                         sizeof(reportedFreq));
            return LOCAL_sendCPTSFreqs(s, measuredFreq, reportedFreq);
        }
        else
        {
            return FAILURE;
        }
    }
    else
    {
        return FAILURE;
    }

    return SUCCESS;
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
