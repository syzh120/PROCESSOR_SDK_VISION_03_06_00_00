/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file tfdtp_test.c
 *
 *  \brief TFDTP test application
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

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>

/* NDK Dependencies */
#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/tools/servers.h>
#include <ti/ndk/inc/stkmain.h>
#include <ti/ndk/inc/stack/stack.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>

/* TFDTP Dependencies */
#include <ti/nsp/drv/inc/tfdtp.h>

/* Client/Server Common Header */
#include "../../../common/test_common.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define TEST_NUM_RX_CHANNELS               (1U)
#define TEST_NUM_TX_CHANNELS               (1U)
#define TEST_BUFF_COUNT                 (TFDTP_MAX_APP_BUF_CNT)
#define TEST_BUFF_SIZE                  (3000000)
#define TFDTP_TX_MAX_THROUGHPUT         (1000)
#define NO_CLIENT_MODE                  (0U)

#if (1 ==  NO_CLIENT_MODE)
#define TEST_DEFUALT_TX_THPUT           (400U)
#define TEST_DEFUALT_NUM_TX_FRAMES      (200U)
#endif

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct appRxBufDesc_
{
    struct tfdtp_rx_buf_details details;
    struct tfdtp_rx_buf appBuffers[TEST_BUFF_COUNT];
} appRxBufDesc;

typedef struct appTxBufDesc
{
    tfdtp_tx_buf_t appTxBuf[TEST_BUFF_COUNT];
} appTxBufDesc;

typedef struct appTxStats_
{
    uint32_t sum;
    uint32_t frameCount;
    uint32_t lastStart;
    uint32_t msPerTick;
} appTxStats;

typedef enum stats_instance_e
{
    STATS_GLOBAL = 0,
    STATS_LISTENER
}
StatInstance_e;


typedef enum status_e
{
    SUCCESS = 0,
    FAILURE = -1,
    SEND_SIZE_FAILURE = -2,
    UNABLE_TO_OBTAIN_LOAD = -3,
    UNEXPECTED_CMD_SIZE = -4,
    NULL_POINTER = -5,
    ACK_FAILURE = -6,
    INVALID_STATS_INSTANCE = -7
}
Status_e;

/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static int      TFDTPApp_init(TestStartCmdParams *cmdParams);
static void     TFDTPApp_deInit(void);
static void     TFDTPApp_initTxStats();
static void     TFDTPApp_initTxBuffers();
static void     TFDTPApp_setTxStats();
static void     TFDTPApp_printTxStats();
static int      TFDTPApp_sendLoadInfo(SOCKET s);
static int      TFDTPApp_sendHWErrors(SOCKET s);
static int      TFDTPApp_sendHWStats(SOCKET s);
static uint32_t TFDTPApp_clearHWStats(void);
static int      TFDTPApp_sendSWStats(SOCKET s);
static uint32_t TFDTPApp_clearSWStats(void);
static int      TFDTPApp_sendNDKIPStats(SOCKET s);
static uint32_t TFDTPApp_clearNDKIPStats(void);
static bool     TFDTPApp_checkNeedsAck(uint32_t cmdId);
static int      TFDTPApp_handleCommand(SOCKET s, uint8_t *buf, uint32_t size);
static int      TFDTPApp_commandServer(SOCKET s, UINT32 unused);
static int      TFDTPApp_sendTFDTPStats(SOCKET s, uint32_t instance);
static int      TFDTPApp_clearTFDTPStats(uint32_t instance);
static int      TFDTPApp_sendBuffCnt(SOCKET s);
static int      TFDTPApp_sendBuffer(SOCKET s, uint8_t *pBuf, uint32_t size);
static int      TFDTPApp_sendFrames(SOCKET s);
static void     TFDTPApp_createTFDTPTask();
static int      TFDTPApp_receiveFrameCb(tfdtp_rx_buf_handle_t appBuffh,
                                   void *cbdata, uint32_t chan);

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

static tfdtp_handle_t         gTFDTPHandle = NULL;
static tfdtp_rx_channel_handle_t gTFDTPRxChHandles[TEST_NUM_RX_CHANNELS];
static tfdtp_tx_channel_handle_t gTFDTPTxChHandles[TEST_NUM_TX_CHANNELS];
static uint32_t               gStopTx = false;
static appTxStats             gTxStats;

static HANDLE appTask           = 0;
static HANDLE hNull             = 0;
static HANDLE hTCPEcho          = 0;
static HANDLE hUDPEcho          = 0;
static HANDLE hTestServer       = 0;
static GMACSW_DeviceHandle hGMACSW;

static bool     gTCPEchoOn = true;
static bool     gUDPEchoOn = true;
static uint32_t gTCPPacketCount = 0;
static uint32_t gUDPPacketCount = 0;

#if defined(__GNUC__)
static uint8_t gRxBufferArrays[TEST_NUM_TX_CHANNELS][TEST_BUFF_COUNT][TEST_BUFF_SIZE]
                                __attribute__(( aligned(128), section(".far:DESTINATION_BUFF") ));
static uint8_t gTxBufferArrays[TEST_NUM_TX_CHANNELS][TEST_BUFF_COUNT][TEST_BUFF_SIZE]
                                __attribute__(( aligned(128), section(".far:DESTINATION_BUFF") ));
#else
#pragma DATA_ALIGN(gRxBufferArrays, 128);
#pragma DATA_SECTION(gRxBufferArrays, ".far:DESTINATION_BUFF");
static uint8_t gRxBufferArrays[TEST_NUM_TX_CHANNELS][TEST_BUFF_COUNT][TEST_BUFF_SIZE];
#pragma DATA_ALIGN(gTxBufferArrays, 128);
#pragma DATA_SECTION(gTxBufferArrays, ".far:DESTINATION_BUFF");
static uint8_t gTxBufferArrays[TEST_NUM_TX_CHANNELS][TEST_BUFF_COUNT][TEST_BUFF_SIZE];
#endif

static struct tfdtp_rx_buf_details gBufferDescriptors[TEST_NUM_TX_CHANNELS];
static appTxBufDesc              gTxBufDescArray[TEST_NUM_TX_CHANNELS];
static tfdtp_tx_buf_t           *gTxBufArray[TEST_NUM_TX_CHANNELS * TEST_BUFF_COUNT];
static volatile uint32_t         gMyIpAddr = 0U;

uint32_t volatile gRxFullFrameCnt   = 0U;
int32_t  volatile gTxDelay          = 0U;
uint32_t volatile gRxErrorFrameCnt  = 0U;
uint32_t volatile dataMatchFailCntr = 0U;
uint32_t volatile gTxFrameCnt       = 0U;
/* Use uint16_t as this should match tfdtp_transmitter's frame_id field */
uint16_t volatile gTxTotalFrameCnt  = 0U;
uint32_t gPacketMissedCnt[100]      = { 0 };

/* Below variables will be set through client application */
uint32_t volatile gDataValidationEnabled    = FALSE;
uint32_t volatile gTransmitFrameCount       = 0U;

/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* Main Fxn */
int main()
{
    BIOS_start();

    return 0;
}

/* Get IP Address NDK hook function. This function is called from NDK every time IP address changes */
void TFDTPApp_ndkIPAddrHookFxn(IPN IPAddr, uint IfIdx, uint fAdd)
{
    /* We are doing network to host conversion as TFDTP driver will also does
     * same. So effectively we negating that it here */
    gMyIpAddr = ntohl(IPAddr);
}

/* TFDTPApp_tcpEchoFxn() - TCP Echo Server Daemon Function (SOCK_STREAMNC) */
/* (SOCK_STREAMNC, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int TFDTPApp_tcpEchoFxn( SOCKET s, UINT32 unused )
{
    struct timeval to;
    uint32_t            i;
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
        i = (uint32_t)recvnc( s, (void **)&pBuf, 0, &hBuffer );

        /* If we read data, echo it back if echo is enabled */
        if( i > 0 )
        {
            if (gTCPEchoOn)
            {
                if( send( s, pBuf, i, 0 ) < 0 )
                    break;
            }
            gTCPPacketCount++;
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

/* TFDTPApp_udpEchoFxn() - UDP Echo Server Daemon Function */
/* (SOCK_DGRAM, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int TFDTPApp_udpEchoFxn( SOCKET s, UINT32 unused )
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
        i = (uint32_t)recvncfrom( s, (void **)&pBuf, 0,(struct sockaddr *)&sin1, &tmp, &hBuffer );

        /* Spit any data back out */
        if( i >= 0 )
        {
            if (gUDPEchoOn)
            {
                sendto( s, pBuf, i, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
            }
            gUDPPacketCount++;
            recvncfree( hBuffer );
        }
        else
            break;
    }

    /* Since the socket is still open, return "1" */
    /* (we need to leave UDP sockets open) */
    return(1);
}

void netOpenHook(void)
{
    printf("[Test server]: netOpenHook!\n");

    /* To test NDK path using NDK Winapps Send utility */
    hNull = DaemonNew( SOCK_STREAMNC, 0, 1001, dtask_tcp_nullsrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    /* Set the control port daemon to be normal priority */
    hTestServer = DaemonNew( SOCK_STREAMNC, 0, TEST_CMD_PORT, TFDTPApp_commandServer,
                           OS_TASKPRINORM, OS_TASKSTKNORM, 0, 1 );
    /* Set the traffic test daemons to be higher priority */
    hTCPEcho = DaemonNew( SOCK_STREAMNC, 0, TEST_TCP_PORT, TFDTPApp_tcpEchoFxn,
                       OS_TASKPRIHIGH, OS_TASKSTKNORM, 0, 3 );
#if 0U
    hUDPEcho = DaemonNew( SOCK_DGRAM, 0, TEST_UDP_PORT, TFDTPApp_udpEchoFxn,
                       OS_TASKPRIHIGH, OS_TASKSTKNORM, 0, 1 );
#endif

    TFDTPApp_createTFDTPTask();

    /* Get GMACSW hardware driver handle */
    hGMACSW = GMACSW_open(NULL);
}

void netCloseHook(void)
{
    printf("[Test server]: netCloseHook!\n");

    if (hGMACSW != NULL)
    {
        GMACSW_close(hGMACSW);
    }

    TFDTPApp_deInit();

    DaemonFree(hNull);
    DaemonFree(hUDPEcho);
    DaemonFree(hTCPEcho);
    DaemonFree(hTestServer);

    TaskDestroy(appTask);
}

static void TFDTPApp_appTask(UArg arg0, UArg arg1)
{
    HANDLE rxTaskShutDownSem;

    rxTaskShutDownSem   = SemCreateBinary(0);

    // Wait for the link to come up.
	Task_sleep(1000);

    printf ("TFDTP App Task has been started\n");

    // Allocate the file environment for this task
    fdOpenSession( TaskSelf() );

#if (1 == NO_CLIENT_MODE)
    uint32_t ret;
    /* Wait for NDK to initialize and get IP address */
    while(0U == gMyIpAddr);

    if (NULL == gTFDTPHandle)
    {
        uint8_t hostIpAddr[16] = "192.168.1.1";

#if ENABLED_BROADCAST
        uint32_t i;
        for (i = 0; i < 6U ; i++)
        {
            dstMacAddr[i] = 0xFF;
        }
#else
        uint8_t dstMacAddr[6U] = {0x18, 0x03, 0x73, 0xB2, 0xCC, 0x01};
#endif
        TestStartCmdParams cmdParams;
        memcpy (&cmdParams.MACAddress, dstMacAddr, sizeof(dstMacAddr));
        memcpy (&cmdParams.IPAddress, hostIpAddr, sizeof(hostIpAddr));
        gDataValidationEnabled = FALSE;
        cmdParams.chanId = TEST_CHANNEL_ID;
        cmdParams.numRxFrame = TEST_DEFUALT_NUM_TX_FRAMES;
        cmdParams.thruput = TEST_DEFUALT_TX_THPUT;
        ret = TFDTPApp_init(&cmdParams);
        if( SUCCESS != ret)
        {
            while(1);
        }
    }

    uint32_t loopCntr = 0;
    while(loopCntr)
    {
        TaskSleep(1000);
    }
    /* Submit all TX buffers initially */
    TFDTP_submitTxBuf(gTFDTPHandle, gTxBufArray, TEST_NUM_TX_CHANNELS * TEST_BUFF_COUNT );
#endif

    SemPend(rxTaskShutDownSem, SEM_FOREVER);
    {
        /* Process received data */
    }

    /* Delete the semaphore objects */
    SemDelete(rxTaskShutDownSem);
    TFDTPApp_deInit();
}

#define TFDTP_PACKET_TASK_PRI      (OS_TASKPRINORM)
#define TFDTP_PACKET_TASK_STACK    (2048)

static void TFDTPApp_createTFDTPTask()
{

    /* Start the packet processing tasks now that the channels are open */
    appTask  = TaskCreate(&TFDTPApp_appTask, "APP_PacketTask",
                                         (uint32_t)TFDTP_PACKET_TASK_PRI,
                                         (uint)TFDTP_PACKET_TASK_STACK,
                                         (uint32_t) 0, (uint32_t)0, (uint32_t)0 );
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*! \brief Callback function given to TFDTP. Once a JPEG frame is complete this will be invoked.
 */
static int TFDTPApp_receiveFrameCb( tfdtp_rx_buf_handle_t appBuffh, void *cbdata, uint32_t chan)
{
    //app_rx_buf_details_t bufD = (app_rx_buf_details_t)cbdata;
    uint32_t *dataPtr;
    uint32_t rxVal, i;
    uint32_t bufState = appBuffh->bufState;

    switch (bufState)
    {
        case BUFF_FULL:
            /* Placeholder to decode/process buffer */
            if(TRUE == gDataValidationEnabled)
            {
                /* Validate test data on receive */
                dataPtr = (uint32_t *)(appBuffh->bufPtr);
                /* Do data validation check only at lower data rate */
                Cache_inv((Ptr)dataPtr, (SizeT)TEST_DATA_SIZE, (Bits16)Cache_Type_ALLD, (Bool)1U);
                for (i =0; i < TEST_DATA_SIZE; i+= 4)
                {
                    rxVal = ( appBuffh->frame_id + (TEST_DATA_PATTERN * i) );
                    if (*dataPtr != rxVal)
                    {
                        dataMatchFailCntr++;
                        break;
                    }
                    dataPtr++;
                }
                if(i == TEST_DATA_SIZE)
                {
                    dataPtr = (uint32_t *)(appBuffh->bufPtr + appBuffh->dataLength);
                    Cache_inv((Ptr)(dataPtr-(TEST_DATA_SIZE/4)), (SizeT)TEST_DATA_SIZE, (Bits16)Cache_Type_ALLD, (Bool)1U);
                    for (i = 0; i <TEST_DATA_SIZE; i+= 4)
                    {
                        dataPtr--;
                        rxVal = ( appBuffh->frame_id + ( TEST_DATA_PATTERN * i) );
                        if (*dataPtr != rxVal)
                        {
                            dataMatchFailCntr++;
                            break;
                        }
                    }
                }
            }
            /* Done with the buffer - so mark it as empty */
            appBuffh->bufState = BUFF_EMPTY;
            gRxFullFrameCnt++;
            break;
        case BUFF_PARTIAL:
            if (appBuffh->error != BUFF_NOERROR)
            {
                /* Error notification - Return the buffer to the queue */
                appBuffh->bufState = BUFF_EMPTY;
                gPacketMissedCnt[gRxErrorFrameCnt%100] =
                            (appBuffh->total_seq_num - appBuffh->seq_num_cnt);
                gRxErrorFrameCnt++;
            }
            break;
        default:
            break;
    }
    return 0;
}

static int TFDTPApp_txFrameDoneCb(tfdtp_tx_buf_t *appTxBuf, void *cbdata, uint32_t channelNum)
{
    uint32_t *dataPtr;
    uint32_t txVal, i;

    if (!gStopTx)
    {
        TFDTPApp_setTxStats();

        if (1U == gDataValidationEnabled)
        {
            memset(appTxBuf->pData, 0xA5, appTxBuf->size);

            /* Validate test data on receive */
            dataPtr = (uint32_t *)(appTxBuf->pData);
            /* Do data validation check only at lower data rate */
            for (i =0; i < TEST_DATA_SIZE; i+= 4)
            {
                /* gTxFrameCnt will always be equal to no. of transmitted buffers.*/
                txVal = ( (gTxFrameCnt) + (TEST_DATA_PATTERN * i) );
                *dataPtr = txVal;
                dataPtr++;
            }

            dataPtr = (uint32_t *)(appTxBuf->pData + appTxBuf->size);
            for (i = 0; i <TEST_DATA_SIZE; i+= 4)
            {
                dataPtr--;
                txVal = ( (gTxFrameCnt) + ( TEST_DATA_PATTERN * i) );
                *dataPtr = txVal;
            }

            /* Flush the cache before resubmitting transfer */
            Cache_wb((Ptr) appTxBuf->pData, (SizeT) appTxBuf->size, (Bits16) Cache_Type_ALLD, (Bool) 1U);
        }

        /* Total frames submitted from beginning of time */
        gTxTotalFrameCnt++;

        /* Send only enough frames receiver is expecting */
        if(gTransmitFrameCount != gTxFrameCnt)
        {
            /* Total frames submitted from last Start Tx */
            gTxFrameCnt++;
            if (gTxDelay != 0)
            {
                TaskSleep(gTxDelay);
            }
            TFDTP_submitTxBuf(gTFDTPHandle, &appTxBuf, 1);
        }
    }

    return 0;
}

void TFDTPApp_printFxn(const char *str)
{
    printf(str);
}

static int TFDTPApp_init(TestStartCmdParams *cmdParams)
{
    tfdtp_handle_t                  hTfdtp;
    TFDTP_OpenPrm_t                 tfdtpOpenPrm;
    tfdtp_rx_channel_handle_t       hTfdtpRxCh;
    TFDTP_RxChOpenPrm_t             tfdtpRxChOpenPrm;
    tfdtp_tx_channel_handle_t       hTfdtpTxCh;
    TFDTP_TxChOpenPrm_t             tfdtpTxChOpenPrm;

    uint32_t                        nFrame, lisIdx;
    uint32_t                        tfdtpChannelId[TEST_NUM_RX_CHANNELS];
    uint8_t                         *dstMacAddr  = (uint8_t *)cmdParams->MACAddress;
    uint8_t                         *destIpAddr  = (uint8_t *)cmdParams->IPAddress;
    int ret;

    /* We support single channel */
    tfdtpChannelId[0] = cmdParams->chanId;

    /* Wait for NDK to initialize and get IP address */
    while(0U == gMyIpAddr);

    printf("Starting TFDTP Stack Test - Host IP %s\n", destIpAddr);
    printf("Host MAC Address: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n" ,
            dstMacAddr[0], dstMacAddr[1], dstMacAddr[2],
            dstMacAddr[3], dstMacAddr[4], dstMacAddr[5]);

    printf("Client requested throughput = %d\n", cmdParams->thruput);
    /* Calculate Tx delay in ms. For 1Mb data it takes 1.2 mS to transmit
     * (1/850(max. possible troughput)).  */
    /* For 3MB (24Mbps) frame */
    float  delayPerFrame = (TEST_BUFF_SIZE/1000000 * 9.5);
    if(cmdParams->thruput > 1000)
        cmdParams->thruput = 1000;
    gTxDelay = (uint32_t) ((float)((float)TFDTP_TX_MAX_THROUGHPUT / (float)cmdParams->thruput) * delayPerFrame );
    gTxDelay = gTxDelay - delayPerFrame;

    tfdtpOpenPrm.rxUdpPort = TEST_UDP_PORT;
    tfdtpOpenPrm.myIpAddr = gMyIpAddr;
    tfdtpOpenPrm.printFxnCb = &TFDTPApp_printFxn;

    hTfdtp = TFDTP_open(&tfdtpOpenPrm);
    if (hTfdtp == NULL)
        return FAILURE;

    memset(&tfdtpRxChOpenPrm, 0, sizeof(tfdtpRxChOpenPrm));
    tfdtpRxChOpenPrm.rcv_cb_fxn = &TFDTPApp_receiveFrameCb;

    memset (gRxBufferArrays, 0, (TEST_NUM_RX_CHANNELS * TEST_BUFF_COUNT * TEST_BUFF_SIZE));

    for (lisIdx = 0; lisIdx < TEST_NUM_RX_CHANNELS; lisIdx++)
    {
        /* A buffer array is allocated per channel */
        tfdtp_rx_buf_details_t bufArrayDesc = &gBufferDescriptors[lisIdx];

        memset (&gBufferDescriptors[lisIdx], 0, sizeof(struct tfdtp_rx_buf_details));
        tfdtpRxChOpenPrm.rcv_cb_data = bufArrayDesc;
        tfdtpRxChOpenPrm.channelId = tfdtpChannelId[lisIdx];

        /* Open TFDTP channel */
        hTfdtpRxCh = TFDTP_openRxChannel(hTfdtp, &tfdtpRxChOpenPrm);

        if (hTfdtpRxCh == NULL) {
            /* This will also closes any opened channels */
            TFDTP_close(hTfdtp);
            return FAILURE;
        }

        /* Store buffer pointers into global array */
        bufArrayDesc->bufCount = TEST_BUFF_COUNT;
        bufArrayDesc->bufSize = TEST_BUFF_SIZE;
        bufArrayDesc->channelNum = lisIdx;

        for (nFrame = 0; nFrame < TEST_BUFF_COUNT; nFrame++)
        {
            bufArrayDesc->appBufArray[nFrame].bufPtr = gRxBufferArrays[lisIdx][nFrame];
            bufArrayDesc->appBufArray[nFrame].bufState = BUFF_EMPTY;
        }

        ret = TFDTP_submitRxBuf(hTfdtpRxCh, bufArrayDesc);
        if (ret < 0)
        {
            TFDTP_close(hTfdtp);
            return FAILURE;
        }
        gTFDTPRxChHandles[lisIdx] = hTfdtpRxCh;

    }

    memset(&tfdtpTxChOpenPrm, 0, sizeof(tfdtpTxChOpenPrm));
    tfdtpTxChOpenPrm.channelId          = tfdtpChannelId[lisIdx];
    tfdtpTxChOpenPrm.tx_cb_fxn         = &TFDTPApp_txFrameDoneCb;
    tfdtpTxChOpenPrm.tx_cb_data  = NULL;
    tfdtpTxChOpenPrm.hostUdpPort        = TEST_UDP_PORT;
    /* Configure hostIpAddr & hostMacAddr to host mac and ip address received from client */
    tfdtpTxChOpenPrm.hostIpAddr = ntohl(inet_addr((const char *)destIpAddr));
    memcpy (&tfdtpTxChOpenPrm.hostMacAddr, dstMacAddr, sizeof(tfdtpTxChOpenPrm.hostMacAddr));

    for (lisIdx = 0; lisIdx < TEST_NUM_TX_CHANNELS; lisIdx++)
    {
        /* Open TFDTP channel */
        hTfdtpTxCh = TFDTP_openTxChannel(hTfdtp, &tfdtpTxChOpenPrm);

        if (hTfdtpTxCh == NULL) {
            /* This will also closes any opened channels */
            TFDTP_close(hTfdtp);
            return FAILURE;
        }

        gTFDTPTxChHandles[lisIdx] = hTfdtpTxCh;

        memset(&gTxBufDescArray, 0, sizeof(gTxBufDescArray));

        for (nFrame = 0; nFrame < TEST_BUFF_COUNT; nFrame++)
        {
            tfdtp_tx_buf_t *appTxBuf = &gTxBufDescArray[lisIdx].appTxBuf[nFrame];

            appTxBuf->hTfdtpTxCh = hTfdtpTxCh;
            appTxBuf->needsFlushing  = false;
            appTxBuf->pData = gTxBufferArrays[lisIdx][nFrame];
            appTxBuf->size = TEST_BUFF_SIZE;

            gTxBufArray[nFrame] = appTxBuf;
        }
    }

    TFDTPApp_initTxStats();

    ret = TFDTP_start(hTfdtp);

    if (ret < 0) {
        TFDTP_close(hTfdtp);
        return FAILURE;
    }

    gTFDTPHandle = hTfdtp;

    return SUCCESS;
}

static void TFDTPApp_deInit(void)
{
    uint32_t lisIdx;

    if (gTFDTPHandle != NULL)
    {
        for (lisIdx = 0; lisIdx < TEST_NUM_RX_CHANNELS; lisIdx++)
        {
            TFDTP_closeRxChannel(gTFDTPRxChHandles[lisIdx]);
        }

        for (lisIdx = 0; lisIdx < TEST_NUM_TX_CHANNELS; lisIdx++)
        {
            TFDTP_closeTxChannel(gTFDTPTxChHandles[lisIdx]);
        }
        /* Clear Stats */
        TFDTPApp_clearHWStats();
        TFDTPApp_clearSWStats();
        TFDTPApp_clearNDKIPStats();

        TFDTP_close(gTFDTPHandle);
        gTFDTPHandle = NULL;
        gTxTotalFrameCnt = 0;
        gRxFullFrameCnt  = 0;
    }
}

static void TFDTPApp_initTxBuffers()
{
    uint32_t bufNum, j;

    for (bufNum = 0U ; bufNum < TEST_BUFF_COUNT; bufNum++ )
    {
        tfdtp_tx_buf_t *appTxBuf = gTxBufArray[bufNum];

        memset(appTxBuf->pData, 0xA5, TEST_BUFF_SIZE);
        /* Validate test data on receive */
        uint32_t *dataPtr = (uint32_t *)(appTxBuf->pData);
        /* Do data validation check only at lower data rate */
        for (j =0; j < TEST_DATA_SIZE; j+= 4)
        {
            *dataPtr = ( bufNum + (TEST_DATA_PATTERN * j) );
            dataPtr++;
        }

        dataPtr = (uint32_t *)(appTxBuf->pData + appTxBuf->size);
        for (j = 0; j <TEST_DATA_SIZE; j+= 4)
        {
            dataPtr--;
            *dataPtr = ( bufNum + ( TEST_DATA_PATTERN * j) );
        }

        /* Flush the cache before resubmitting transfer */
        Cache_wb((Ptr) appTxBuf->pData, (SizeT) appTxBuf->size, (Bits16) Cache_Type_ALLD, (Bool) 1U);
    }
}

static void TFDTPApp_initTxStats()
{
    Types_FreqHz freq;
    uint32_t msPerTick;

    Timestamp_getFreq(&freq);
    msPerTick = freq.lo/1000;

    gTxStats.frameCount = 0;
    gTxStats.msPerTick = msPerTick;
    gTxStats.lastStart = Timestamp_get32();
    gTxStats.sum = 0;
}

static void TFDTPApp_setTxStats()
{
    gTxStats.sum += (Timestamp_get32() - gTxStats.lastStart)/gTxStats.msPerTick;
    gTxStats.lastStart = Timestamp_get32();
    gTxStats.frameCount++;
}

static void TFDTPApp_printTxStats()
{
    if (gTxStats.sum > 0) {
        uint32_t numBytes = gTxStats.frameCount * TEST_BUFF_SIZE;
        uint32_t rate = (numBytes/gTxStats.sum) * 1000;
        printf("Sent %u bytes in %u ms\n", numBytes, gTxStats.sum);
        printf("Average Tx rate: %u Mbit/s\n", rate/131072);
    }
}

static int TFDTPApp_sendBuffCnt(SOCKET s)
{
    int ret;
    uint32_t buf[1];
    buf[0] = htonl(TEST_BUFF_COUNT);
    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int TFDTPApp_sendBuffer(SOCKET s, uint8_t *pBuf, uint32_t size)
{
    int sizeSent;
    static const uint32_t MAX_PACKET_SIZE = 4096;
    uint32_t remaining = size;
    uint32_t sizeToSend;
    uint32_t buf[1];

    /* PROTOCOL is:
     * 0 Buffer size
     * 1 Data contents
     */
    buf[0] = htonl(size);
    sizeSent = send(s, &buf, sizeof(buf), 0);

    if (sizeSent < 0) return sizeSent;
    if (sizeSent != sizeof(buf)) return SEND_SIZE_FAILURE;

    while (remaining > 0) {
        sizeToSend = (remaining > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : remaining;
        sizeSent = send(s, pBuf, sizeToSend, 0);
        if (sizeSent < 0) return sizeSent;
        pBuf += sizeSent;
        remaining -= sizeSent;
    }

    return SUCCESS;
}

static int TFDTPApp_sendFrames(SOCKET s)
{
    int ret;
    uint32_t buf[2];
    uint32_t i, j;

    /* Protocol for sending frames is as follows:
     *  0 Number of channels
     *  1 Number of buffers per receiver
     *  2 Buffer size
     *  3 Buffer contents
     *  4 [ Repeat 2-3 for all remaining buffers]
     */
    buf[0] = htonl(TEST_NUM_TX_CHANNELS);
    buf[1] = htonl(TEST_BUFF_COUNT);

    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;

    for (i = 0; i < TEST_NUM_RX_CHANNELS; i++)
    {
        for (j = 0; j < TEST_BUFF_COUNT; j++)
        {
            ret = TFDTPApp_sendBuffer(s, gBufferDescriptors[i].appBufArray[j].bufPtr, gBufferDescriptors[i].appBufArray[j].dataLength);
            if (ret < 0)
                return ret;
        }
    }
    return SUCCESS;
}

static bool TFDTPApp_checkNeedsAck(uint32_t cmdId)
{
    bool retVal = false;
    switch(cmdId)
    {
        case TEST_CMD_START_TFDTP:
            /* ACK is done if init is successful only */
            retVal = false;
            break;
        case TEST_CMD_STOP_TFDTP:
        case TEST_CMD_GET_TFDTP_STATS:
        case TEST_CMD_CLEAR_TFDTP_STATS:
        case TEST_CMD_DUMP_OUTPUT_FRAMES:
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
        case TEST_CMD_GET_BUFFER_COUNT:
        case TEST_CMD_START_TFDTP_TX:
        case TEST_CMD_STOP_TFDTP_TX:
            retVal = true;
            break;
        default:
            break;
    }
    return retVal;
}

static int TFDTPApp_handleCommand(SOCKET s, uint8_t *buf, uint32_t size)
{
    uint32_t cmdId;
    uint32_t *pBuf = (uint32_t *)buf;
    int		 ret;

    if (size < 4)
        return UNEXPECTED_CMD_SIZE;

    cmdId = ntohl(pBuf[0]);

    /*
     * Protocol is 32-bit command ID,  0 or more arguments depending on
     * command id. ACK is done by echoing the command ID back to the host.
     */
    if (TFDTPApp_checkNeedsAck(cmdId) == true)
    {
        int result = send(s, buf, size, 0);
        if (result < 0)
            return ACK_FAILURE;
        if (result != size)
            return SEND_SIZE_FAILURE;
    }

    switch(cmdId)
    {
        case TEST_CMD_START_TFDTP:
            if (NULL == gTFDTPHandle)
            {
                /* Get MAC and IP address of host from command params */
                TestStartCmdParams *cmdParams = (TestStartCmdParams *) &pBuf[1];
                gDataValidationEnabled = cmdParams->enableDataValFlag;
                /* We store no. of receive frame client expects in case Transmit is started */
                gTransmitFrameCount = cmdParams->numRxFrame;
                ret = TFDTPApp_init( cmdParams);

                if( SUCCESS != ret)
                {
                    while(1);
                }
            }
            else
            {
                ret = SUCCESS;
            }
            if (ret == SUCCESS) {
                ret = send(s, pBuf, size, 0);
                if (ret > 0 && ret != size)
                    return SEND_SIZE_FAILURE;
                ret = SUCCESS;
            }
            break;
        case TEST_CMD_STOP_TFDTP:
            TFDTPApp_deInit();
            ret = SUCCESS;
            break;
        case TEST_CMD_GET_TFDTP_STATS:
            if (size != 8)
            {
                ret = UNEXPECTED_CMD_SIZE;
            }
            else
            {
                /* 0 - Global stats */
                /* 1..x - Stats for receiver x */
                uint32_t instance = ntohl(pBuf[1]);
                ret = TFDTPApp_sendTFDTPStats(s, instance);
            }
            break;
        case TEST_CMD_CLEAR_TFDTP_STATS:
            if (size != 8)
            {
                ret = UNEXPECTED_CMD_SIZE;
            }
            else
            {
                /* 0 - Global stats */
                /* 1..x - Stats for receiver x */
                uint32_t instance = ntohl(pBuf[1]);
                ret = TFDTPApp_clearTFDTPStats(instance);
            }
            break;
        case TEST_CMD_DUMP_OUTPUT_FRAMES:
            ret = TFDTPApp_sendFrames(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_LOAD_INFO:
            ret = TFDTPApp_sendLoadInfo(s);
            if ( SUCCESS != ret)
            {
                printf(" Please check if Profiling is enabled for load info..\n");
            }
            break;
        case TEST_CMD_GET_HW_ERRORS:
            ret = TFDTPApp_sendHWErrors(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_HW_STATS:
            ret = TFDTPApp_sendHWStats(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_CLEAR_HW_STATS:
            ret = TFDTPApp_clearHWStats();
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_SW_STATS:
            ret = TFDTPApp_sendSWStats(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_CLEAR_SW_STATS:
            ret = TFDTPApp_clearSWStats();
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_NDK_STATS:
            ret = TFDTPApp_sendNDKIPStats(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_CLEAR_NDK_STATS:
            ret = TFDTPApp_clearNDKIPStats();
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_DISABLE_TCP_ECHO:
            gTCPEchoOn = false;
            ret = SUCCESS;
            break;
        case TEST_CMD_ENABLE_TCP_ECHO:
            gTCPEchoOn = true;
            ret = SUCCESS;
            break;
        case TEST_CMD_GET_BUFFER_COUNT:
            ret = TFDTPApp_sendBuffCnt(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_START_TFDTP_TX:
            gStopTx = false;
            /* Set TX frame count to TEST_BUFF_COUNT as we are submitting all buffers initially */
            gTxFrameCnt = TEST_BUFF_COUNT;
            TFDTPApp_initTxStats();
            if (1U == gDataValidationEnabled)
            {
                TFDTPApp_initTxBuffers();
            }
            TFDTP_submitTxBuf(gTFDTPHandle, gTxBufArray, TEST_NUM_TX_CHANNELS * TEST_BUFF_COUNT);
            ret = SUCCESS;
            break;
        case TEST_CMD_STOP_TFDTP_TX:
            gStopTx = true;
            TFDTPApp_printTxStats();
            ret = SUCCESS;
            break;
        default:
            printf("[Test server]: Received unknown command = 0x%8X!\n", (unsigned int)cmdId);
            ret = FAILURE;
            break;
    }
    return ret;
}

static int TFDTPApp_commandServer(SOCKET s, UINT32 unused)
{
    struct timeval to;
    int ret, recv_size;
    uint8_t *pBuf;
    HANDLE hBuffer;
    const uint32_t socketOptVal = 1;

    printf("[Test server]: entering test server daemon!\n");

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

        ret = TFDTPApp_handleCommand(s, pBuf, recv_size);
        recvncfree(hBuffer);
        if (ret != SUCCESS)
        {
            if (ret == ACK_FAILURE)
            {
                printf("[Test server]: command acknowledgement failed!\n");
            }
            else
            {
                printf("[Test server]: error handling command (ret:%d)!\n", ret);
            }
        }

    }

teardown:
    fdClose(s);
    TFDTPApp_deInit();
    printf("[Test server]: exiting test server daemon!\n");
    return ret;

}

static int TFDTPApp_sendTFDTPStats(SOCKET s, uint32_t instance)
{
    int ret;
    struct tfdtp_stats stats;
    uint32_t buf[16];

    if (instance == STATS_GLOBAL)
    {
        TFDTP_getStats(gTFDTPHandle, &stats);
    }
    else if (instance <= TEST_NUM_RX_CHANNELS)
    {
        TFDTP_getRcvrStats(gTFDTPRxChHandles[instance - 1], &stats);
    }
    else
    {
        return INVALID_STATS_INSTANCE;
    }

    buf[0] = htonl(gRxFullFrameCnt);
    buf[1] = htonl(stats.packetCount);
    buf[2] = htonl(stats.ignoredPacketCnt);
    buf[3] = htonl(stats.errorCnt);
    buf[4] = htonl(stats.invalidPacketSizeError);
    buf[5] = htonl(stats.outOfSequenceError);
    buf[6] = htonl(stats.noBuffersAvailable);
    buf[7] = htonl(stats.insufficientSizeError);

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int TFDTPApp_clearTFDTPStats(uint32_t instance)
{
    if (instance == STATS_GLOBAL)
    {
        TFDTP_clearStats(gTFDTPHandle);
    }
    else if (instance <= TEST_NUM_RX_CHANNELS)
    {
        TFDTP_clearRcvrStats(gTFDTPRxChHandles[instance - 1]);
    }
    else
    {
        return INVALID_STATS_INSTANCE;
    }

    return SUCCESS;
}

/* Make sure you enable profiling in .cfg file (enableProfiling = 1) or else this will fail */
static int TFDTPApp_sendLoadInfo(SOCKET s)
{
    Load_Stat stat;
    uint32_t buf[6];
    int	 ret;

    ret = Load_getGlobalHwiLoad(&stat);
    if (ret == 0) return UNABLE_TO_OBTAIN_LOAD;

    buf[0] = htonl(Load_getCPULoad());
    buf[1] = htonl(Load_calculateLoad(&stat));
    if (NULL != gTFDTPHandle)
    {
        buf[2] = htonl(TFDTP_getRxLoad(gTFDTPHandle));
        buf[3] = htonl(TFDTP_getTxLoad(gTFDTPHandle));
    }
    else
    {
        buf[2] = htonl(0);
        buf[3] = htonl(0);
    }

    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int TFDTPApp_sendHWErrors(SOCKET s)
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

static int TFDTPApp_sendHWStats(SOCKET s)
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

static uint32_t TFDTPApp_clearHWStats(void)
{
    GMACSW_ioctl(
        hGMACSW,
        GMACSW_IOCTL_STATS_CLEAR_STATS,
        NULL,
        0U);

    return SUCCESS;
}

static int TFDTPApp_sendSWStats(SOCKET s)
{
    int ret;
    uint32_t buf[4];

    buf[0] = htonl((uint32_t)gTCPPacketCount);
    buf[1] = htonl((uint32_t)gUDPPacketCount);

    if (NULL != gTFDTPHandle)
    {
        struct tfdtp_stats stats;
        TFDTP_getStats(gTFDTPHandle, &stats);

        buf[2] = htonl(stats.packetCount);
        buf[3] = htonl(stats.errorCnt);
    }

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0) return ret;
    if (ret != sizeof(buf)) return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static uint32_t TFDTPApp_clearSWStats(void)
{
    gTCPPacketCount = 0;
    gUDPPacketCount = 0;

    TFDTPApp_clearTFDTPStats(0);

    return SUCCESS;
}

static int TFDTPApp_sendNDKIPStats(SOCKET s)
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

static uint32_t TFDTPApp_clearNDKIPStats(void)
{
    mmZeroInit( &udps, sizeof( UDPSTATS ) );
    mmZeroInit( &tcps, sizeof( TCPSTATS ) );
    mmZeroInit( &ips, sizeof( IPSTATS ) );

    return SUCCESS;
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
