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
 *  \file avbtp_test.c
 *
 *  \brief AVBTP test application
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

/* AVBTP Dependencies */
#include <ti/avbtp/inc/avbtp.h>

/* Client/Server Common Header */
#include "../../../common/test_common.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define NUM_LISTENERS 	(4U)
#define NUM_TALKERS 	(1U)
#define BUFF_COUNT 		(10U)
#define BUFF_SIZE 		(300000U)

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct buff_desc_
{
    struct app_buff_details details;
    uint8_t *ptrs[BUFF_COUNT];
    uint8_t state[BUFF_COUNT];
    uint32_t validLen[BUFF_COUNT];
} buff_desc;

typedef struct tx_buff_desc
{
    avbtp_tx_buffer buffer[BUFF_COUNT];
} tx_buff_desc;

typedef struct tx_stats_
{
    uint32_t sum;
    uint32_t frameCount;
    uint32_t lastStart;
    uint32_t msPerTick;
} tx_stats;

typedef enum stats_instance_e
{
    STATS_GLOBAL = 0,
    STATS_LISTENER
}
StatInstance_e;

typedef struct avb_talker_instance_
{
    avbtp_talker_handle_t handle;
}
avb_talker;

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
static int onFrameReady(uint8_t *buf, uint32_t size, avbtp_sd_info_t *rinfo,
                              void *cbdata, uint32_t chan, uint32_t buffIndex);
static int avbInit(void);
static void avbDeinit(void);
static int avbTalkerInit(avbtp_handle_t avh);

static void initTxStats();
static void txStatsMeasure();
static void printTxStats();

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

static int LOCAL_sendAVBStats(SOCKET s, uint32_t instance);
static int LOCAL_clearAVBStats(uint32_t instance);
static int sendBuffCnt(SOCKET s);
static int sendBuffer(SOCKET s, uint8_t *pBuf, uint32_t size);
static int sendFrames(SOCKET s);


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

/* IDs used in NSP stub test data */
static const uint8_t streamId[NUM_LISTENERS][8] =
{
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00 },
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01 },
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02 },
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x03 }
};

static avbtp_handle_t gAVBHandle = NULL;
static avbtp_listener_handle_t gAVBListenerHandles[NUM_LISTENERS];
static avbtp_talker_handle_t gAVBTalkerHandles[NUM_TALKERS];
static uint32_t gStopTalker = false;
static tx_stats gTxStats;

static HANDLE hTCPEcho = 0;
static HANDLE hUDPEcho = 0;
static HANDLE hTestServer = 0;
static GMACSW_DeviceHandle hGMACSW;
static uint32_t gAVBNotifyMode = BUFF_NOTIFY_DEFAULT;

static bool     LOCAL_TCPEchoOn = true;
static bool     LOCAL_UDPEchoOn = true;
static uint32_t LOCAL_tcpPacketCount = 0;
static uint32_t LOCAL_udpPacketCount = 0;

#if defined(__GNUC__)
static uint8_t gBufferArrays[NUM_LISTENERS][BUFF_COUNT][BUFF_SIZE] __attribute__(( aligned(128), section(".far:DESTINATION_BUFF") ));
#else
#pragma DATA_ALIGN(gBufferArrays, 128);
#pragma DATA_SECTION(gBufferArrays, ".far:DESTINATION_BUFF");
static uint8_t gBufferArrays[NUM_LISTENERS][BUFF_COUNT][BUFF_SIZE];
#endif
static buff_desc gBufferDescriptors[NUM_LISTENERS];
static tx_buff_desc gTXBuffers[NUM_TALKERS];
static avbtp_tx_buffer *gTxBufferArray[NUM_TALKERS * BUFF_COUNT];


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

void netOpenHook(void)
{
    printf("[Test server]: netOpenHook!\n");

    /* Set the control port daemon to be normal priority */
    hTestServer = DaemonNew( SOCK_STREAMNC, 0, TEST_CMD_PORT, LOCAL_commandServer,
                           OS_TASKPRINORM, OS_TASKSTKNORM, 0, 1 );

    /* Set the traffic test daemons to be higher priority */
    hTCPEcho = DaemonNew( SOCK_STREAMNC, 0, TEST_TCP_PORT, my_tcp_echo,
                       OS_TASKPRIHIGH, OS_TASKSTKNORM, 0, 3 );

    hUDPEcho = DaemonNew( SOCK_DGRAM, 0, TEST_UDP_PORT, my_udp_echo,
                       OS_TASKPRIHIGH, OS_TASKSTKNORM, 0, 1 );

    avbInit();

    /* Get GMACSW hardware driver handle */
    hGMACSW = GMACSW_open(NULL);

    /* Clear HW Stats */
    LOCAL_clearHWStats();

    /* Clear SW Stats */
    LOCAL_clearSWStats();

    /* Clear NDK IP stack stats */
    LOCAL_clearNDKIpStats();
}

void netCloseHook(void)
{
    printf("[Test server]: netCloseHook!\n");

    if (hGMACSW != NULL)
    {
        GMACSW_close(hGMACSW);
    }

    avbDeinit();

    DaemonFree(hUDPEcho);
    DaemonFree(hTCPEcho);
    DaemonFree(hTestServer);
}

int main()
{
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
        case TEST_CMD_START_AVB:
            /* ACK is done if init is successful only */
            retVal = false;
            break;
        case TEST_CMD_STOP_AVB:
        case TEST_CMD_GET_AVB_STATS:
        case TEST_CMD_CLEAR_AVB_STATS:
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
        case TEST_CMD_ENABLE_RST_MARKER_DETECTION:
        case TEST_CMD_START_AVB_TALKER:
        case TEST_CMD_STOP_AVB_TALKER:
            retVal = true;
            break;
        default:
            break;
    }
    return retVal;
}

static int LOCAL_handleCommand(SOCKET s, uint8_t *buf, uint32_t size)
{
    uint32_t cmdId;
    uint32_t *pBuf = (uint32_t *)buf;
    int ret;

    if (size < 4)
        return UNEXPECTED_CMD_SIZE;

    cmdId = ntohl(pBuf[0]);

    /*
     * Protocol is 32-bit command ID,  0 or more arguments depending on
     * command id. ACK is done by echoing the command ID back to the host.
     */
    if (LOCAL_needsAck(cmdId) == true)
    {
        int result = send(s, buf, size, 0);
        if (result < 0)
            return ACK_FAILURE;
        if (result != size)
            return SEND_SIZE_FAILURE;
    }

    switch(cmdId)
    {
        case TEST_CMD_START_AVB:
            if (NULL == gAVBHandle)
            {
                printf("Starting AVB \n");
                ret = avbInit();
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
        case TEST_CMD_STOP_AVB:
            avbDeinit();
            printf("Stopped AVB \n");
            ret = SUCCESS;
            break;
        case TEST_CMD_GET_AVB_STATS:
            if (size != 8)
            {
                ret = UNEXPECTED_CMD_SIZE;
            }
            else
            {
                /* 0 - Global stats */
                /* 1..x - Stats for listener x */
                uint32_t instance = ntohl(pBuf[1]);
                ret = LOCAL_sendAVBStats(s, instance);
            }
            break;
        case TEST_CMD_CLEAR_AVB_STATS:
            if (size != 8)
            {
                ret = UNEXPECTED_CMD_SIZE;
            }
            else
            {
                /* 0 - Global stats */
                /* 1..x - Stats for listener x */
                uint32_t instance = ntohl(pBuf[1]);
                ret = LOCAL_clearAVBStats(instance);
            }
            break;
        case TEST_CMD_DUMP_OUTPUT_FRAMES:
            ret = sendFrames(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_LOAD_INFO:
            ret = LOCAL_sendLoadInfo(s);
            break;
        case TEST_CMD_GET_HW_ERRORS:
            ret = LOCAL_sendHWErrors(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_HW_STATS:
            ret = LOCAL_sendHWStats(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_CLEAR_HW_STATS:
            ret = LOCAL_clearHWStats();
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_SW_STATS:
            ret = LOCAL_sendSWStats(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_CLEAR_SW_STATS:
            ret = LOCAL_clearSWStats();
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_GET_NDK_STATS:
            ret = LOCAL_sendNDKIpStats(s);
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_CLEAR_NDK_STATS:
            ret = LOCAL_clearNDKIpStats();
            if ( SUCCESS != ret)
            {
                while(1);
            }
            break;
        case TEST_CMD_DISABLE_TCP_ECHO:
            LOCAL_TCPEchoOn = false;
            ret = SUCCESS;
            break;
        case TEST_CMD_ENABLE_TCP_ECHO:
            LOCAL_TCPEchoOn = true;
            ret = SUCCESS;
            break;
        case TEST_CMD_GET_BUFFER_COUNT:
            ret = sendBuffCnt(s);
            break;
        case TEST_CMD_ENABLE_RST_MARKER_DETECTION:
            gAVBNotifyMode = BUFF_NOTIFY_MJPEG_RST;
            ret = SUCCESS;
            break;
        case TEST_CMD_START_AVB_TALKER:
            printf("Start AVB Talker \n");
            gStopTalker = false;
            initTxStats();
            avbtp_talker_enqueue(gAVBHandle, gTxBufferArray, NUM_TALKERS * BUFF_COUNT);
            ret = SUCCESS;
            break;
        case TEST_CMD_STOP_AVB_TALKER:
            gStopTalker = true;
            printTxStats();
            ret = SUCCESS;
            break;
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

        ret = LOCAL_handleCommand(s, pBuf, recv_size);
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
    printf("[Test server]: exiting test server daemon!\n");
    return ret;

}


/*! \brief Callback function given to AVB. Once a JPEG frame is complete this will be invoked.
 */
static int onFrameReady(uint8_t *buf, uint32_t size, avbtp_sd_info_t *rinfo,
                              void *cbdata, uint32_t chan, uint32_t buffIndex)
{
    app_buff_details_t bufD = (app_buff_details_t)cbdata;
    uint32_t bufState = bufD->buffState[buffIndex];
    switch (bufState)
    {
        case BUFF_FULL:

            /* Placeholder to decode/process buffer */
            /* Done with the buffer - so mark it as empty */
            bufD->buffState[buffIndex] = BUFF_EMPTY;
            break;
        case BUFF_PARTIAL:
            if (bufD->error != BUFF_NOERROR)
            {
                /* Error notification - Return the buffer to the queue */
                bufD->buffState[buffIndex] = BUFF_EMPTY;
            }
            break;
        default:
            break;
    }
    return 0;
}

static void onFrameEmpty(avbtp_tx_buffer *buffer, void *cbdata, uint32_t channelNum)
{
    if (!gStopTalker)
    {
        txStatsMeasure();
        avbtp_talker_enqueue(gAVBHandle, &buffer, 1);
    }
}

static int avbInit(void)
{
    avbtp_handle_t avh;
    avbtp_listener_handle_t avlh;
    int lisIdx;
    int nFrame;
    int ret;

    avh = avbtp_open();
    if (avh == NULL)
        return FAILURE;

    for (lisIdx = 0; lisIdx < NUM_LISTENERS; lisIdx++)
    {
        /* A buffer array is allocated per channel */
        app_buff_details_t bufArrayDesc = &gBufferDescriptors[lisIdx].details;

        /* Bind to a specific talker
         * The talker address is specified in the first 6-bytes of a streamID so we reuse it
         */
        avlh = avbtp_listener_open(avh, streamId[lisIdx], &onFrameReady, bufArrayDesc, NULL, NULL, streamId[lisIdx]);

        if (avlh == NULL) {
            /* This will also closes any opened listeners */
            avbtp_close(avh);
            return FAILURE;
        }

        bufArrayDesc->arrBuffPtr = &gBufferDescriptors[lisIdx].ptrs[0];
        bufArrayDesc->buffCount = BUFF_COUNT;
        bufArrayDesc->buffSize = BUFF_SIZE;
        bufArrayDesc->channelNum = lisIdx;

        bufArrayDesc->buffState = &gBufferDescriptors[lisIdx].state[0];
        bufArrayDesc->dataLength = &gBufferDescriptors[lisIdx].validLen[0];

        for (nFrame = 0; nFrame < BUFF_COUNT; nFrame++)
        {
            bufArrayDesc->arrBuffPtr[nFrame] = gBufferArrays[lisIdx][nFrame];
            bufArrayDesc->buffState[nFrame] = BUFF_EMPTY;
            bufArrayDesc->dataLength[nFrame] = 0;
        }

        bufArrayDesc->configBits = gAVBNotifyMode;

        avbtp_submit_buffer(avlh, bufArrayDesc);

        gAVBListenerHandles[lisIdx] = avlh;
    }

    ret = avbtp_start(avh);
    if (ret < 0) {
        avbtp_close(avh);
        return FAILURE;
    }

    gAVBHandle = avh;

    ret = avbTalkerInit(avh);
    if (ret < 0) {
        avbDeinit();
        return FAILURE;
    }


    return SUCCESS;
}

static void avbDeinit(void)
{
    if (gAVBHandle != NULL)
    {
        avbtp_close(gAVBHandle);
        gAVBHandle = NULL;
        gAVBNotifyMode = BUFF_NOTIFY_DEFAULT;
    }
}

static int avbTalkerInit(avbtp_handle_t avh)
{
    uint32_t nFrame, talkerIdx, count = 0;
    if (NULL == avh)
        return NULL_POINTER;

    memset(&gAVBTalkerHandles, 0, sizeof(gAVBTalkerHandles));
    memset(&gTXBuffers, 0, sizeof(gTXBuffers));

    for (talkerIdx = 0; talkerIdx < NUM_TALKERS; talkerIdx++)
    {
        avbtp_talker_handle_t avth = avbtp_talker_open(avh, NULL, onFrameEmpty, NULL, 0x3, 0x0 );
        if (avth == NULL) {
            return FAILURE;
        }
        for (nFrame = 0; nFrame < BUFF_COUNT; nFrame++)
        {
            memset(gBufferArrays[talkerIdx][nFrame], nFrame+0xBE, BUFF_SIZE);

            /* Create fake JPEG frame */
            gBufferArrays[talkerIdx][nFrame][0] = 0xFF;
            gBufferArrays[talkerIdx][nFrame][1] = 0xD8;


            gBufferArrays[talkerIdx][nFrame][BUFF_SIZE - 2] = 0xFF;
            gBufferArrays[talkerIdx][nFrame][BUFF_SIZE - 1] = 0xD9;

            Cache_inv((Ptr) &gBufferArrays[talkerIdx][nFrame], (SizeT)BUFF_SIZE, (Bits16)Cache_Type_ALLD, (Bool)1U);

            gTXBuffers[talkerIdx].buffer[nFrame].avth = avth;
            gTXBuffers[talkerIdx].buffer[nFrame].needsFlushing = false;
            gTXBuffers[talkerIdx].buffer[nFrame].pData = gBufferArrays[talkerIdx][nFrame];
            gTXBuffers[talkerIdx].buffer[nFrame].size = BUFF_SIZE;

            gTxBufferArray[count] = &gTXBuffers[talkerIdx].buffer[nFrame];
            count++;
        }
        gAVBTalkerHandles[talkerIdx] = avth;
    }

    initTxStats();
    return 0;
}

static void initTxStats()
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

static void txStatsMeasure()
{
    gTxStats.sum += (Timestamp_get32() - gTxStats.lastStart)/gTxStats.msPerTick;
    gTxStats.lastStart = Timestamp_get32();
    gTxStats.frameCount++;
}

static void printTxStats()
{
    if (gTxStats.sum > 0) {
        uint32_t numBytes = gTxStats.frameCount * BUFF_SIZE;
        uint32_t rate = (numBytes/gTxStats.sum) * 1000;
        printf("Sent %u bytes in %u ms\n", numBytes, gTxStats.sum);
        printf("Average Tx rate: %u Mbit/s\n", rate/131072);
    }
}

static int LOCAL_sendAVBStats(SOCKET s, uint32_t instance)
{
    int ret;
    struct avbtp_stats stats;
    uint32_t buf[16];

    if (instance == STATS_GLOBAL)
    {
        avbtp_get_statistics(gAVBHandle, &stats);
    }
    else if (instance <= NUM_LISTENERS)
    {
        avbtp_get_listener_stats(gAVBListenerHandles[instance - 1], &stats);
    }
    else
    {
        return INVALID_STATS_INSTANCE;
    }

    buf[0] = htonl(stats.packetCnt);
    buf[1] = htonl(stats.ignoredPacketCnt);
    buf[2] = htonl(stats.errorCnt);
    buf[3] = htonl(stats.controlPacketCnt);
    buf[4] = htonl(stats.unexpectedEtherType);
    buf[5] = htonl(stats.unexpectedSubType);
    buf[6] = htonl(stats.unexpectedStreamID);
    buf[7] = htonl(stats.svFlagError);
    buf[8] = htonl(stats.invalidPacketSizeError);
    buf[9] = htonl(stats.outOfSequenceError);
    buf[10] = htonl(stats.noBuffersAvailable);
    buf[11] = htonl(stats.insufficientSizeError);
    buf[12] = htonl(stats.missedEOIError);
    buf[13] = htonl(stats.numRestartMarkers);
    buf[14] = htonl(stats.numSOIMarkers);
    buf[15] = htonl(stats.numEOIMarkers);

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int LOCAL_clearAVBStats(uint32_t instance)
{
    if (instance == STATS_GLOBAL)
    {
        avbtp_clear_statistics(gAVBHandle);
    }
    else if (instance <= NUM_LISTENERS)
    {
        avbtp_clear_listener_stats(gAVBListenerHandles[instance - 1]);
    }
    else
    {
        return INVALID_STATS_INSTANCE;
    }

    return SUCCESS;
}

static int LOCAL_sendLoadInfo(SOCKET s)
{
    Load_Stat stat;
    uint32_t buf[6];
    int ret;

    ret = Load_getGlobalHwiLoad(&stat);
    if (ret == 0)
        return UNABLE_TO_OBTAIN_LOAD;

    buf[0] = htonl(Load_getCPULoad());
    buf[1] = htonl(Load_calculateLoad(&stat));
    /* TODO: Get actual ndk2nsp task loads here */
    buf[2] = htonl(0);
    buf[3] = htonl(0);
    if (NULL != gAVBHandle)
    {
        buf[4] = htonl(avbtp_get_rx_load(gAVBHandle));
        buf[5] = htonl(avbtp_get_tx_load(gAVBHandle));
    }
    else
    {
        buf[4] = htonl(0);
        buf[5] = htonl(0);
    }

    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int sendBuffCnt(SOCKET s)
{
    int ret;
    uint32_t buf[1];
    buf[0] = htonl(BUFF_COUNT);
    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;
    return SUCCESS;
}

static int sendBuffer(SOCKET s, uint8_t *pBuf, uint32_t size)
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

    if (sizeSent < 0)
    	return sizeSent;
    if (sizeSent != sizeof(buf))
    	return SEND_SIZE_FAILURE;

    while (remaining > 0) {
        sizeToSend = (remaining > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : remaining;
        sizeSent = send(s, pBuf, sizeToSend, 0);
        if (sizeSent < 0)
        	return sizeSent;
        pBuf += sizeSent;
        remaining -= sizeSent;
    }

    return SUCCESS;
}

static int sendFrames(SOCKET s)
{
    int ret;
    uint32_t buf[2];
    uint32_t i, j;

    /* Protocol for sending frames is as follows:
     *  0 Number of listeners
     *  1 Number of buffers per listener
     *  2 Buffer size
     *  3 Buffer contents
     *  4 [ Repeat 2-3 for all remaining buffers]
     */
    buf[0] = htonl(NUM_LISTENERS);
    buf[1] = htonl(BUFF_COUNT);

    ret = send(s, &buf, sizeof(buf), 0);

    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;

    for (i = 0; i < NUM_LISTENERS; i++)
    {
        for (j = 0; j < BUFF_COUNT; j++)
        {
            ret = sendBuffer(s, gBufferDescriptors[i].ptrs[j], gBufferDescriptors[i].validLen[j]);
            if (ret < 0)
                return ret;
        }
    }
    return SUCCESS;
}

static int LOCAL_sendHWErrors(SOCKET s)
{
    int ret;
    STATS_Statistics stats;
    uint32_t buf[9];

    if (hGMACSW == NULL)
        return NULL_POINTER;

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
    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_sendHWStats(SOCKET s)
{
    int ret;
    STATS_Statistics stats;
    uint32_t buf[10];

    if (hGMACSW == NULL)
        return NULL_POINTER;

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
    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;

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

    if (NULL != gAVBHandle)
    {
        struct avbtp_stats stats;
        avbtp_get_statistics(gAVBHandle, &stats);

        buf[2] = htonl(stats.packetCnt);
        buf[3] = htonl(stats.errorCnt);
    }

    ret = send(s, &buf, sizeof(buf), 0);
    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_clearSWStats(void)
{
    LOCAL_tcpPacketCount = 0;
    LOCAL_udpPacketCount = 0;

    LOCAL_clearAVBStats(0);

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
    if (ret < 0)
        return ret;
    if (ret != sizeof(buf))
        return SEND_SIZE_FAILURE;

    return SUCCESS;
}

static int LOCAL_clearNDKIpStats(void)
{
    mmZeroInit( &udps, sizeof( UDPSTATS ) );
    mmZeroInit( &tcps, sizeof( TCPSTATS ) );
    mmZeroInit( &ips, sizeof( IPSTATS ) );

    return SUCCESS;
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
