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
 *  \file   avbtp.c
 *
 *  \brief  AVB stack implementation file.
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/utils/Load.h>

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* This module's header */
#include "avbtp.h"
#include "avbtp_priv.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

/* The EDMA driver does not expose this in a top level header - hence we define the extern here */
extern uint16_t determineProcId(void);

/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#if defined(DEBUG)
#define LOGE(x, y) printf(x, y)
#else
#define LOGE(x, y)
#endif

#define AVB_RX_PACKETS (AVB2NSP_RX_PACKETS * (uint32_t)2U)
#define AVB_TX_PACKETS (AVB2NSP_TX_PACKETS * (uint32_t)2U)

#define JPEG_MARKER_H 0xFFU
#define JPEG_SOI 0xD8U
#define JPEG_EOI 0xD9U
#define JPEG_EOI_CHECK_NBYTES 10U
/* JPEG RST MARKER IS 0XFFDn (n=0..7) */
#define JPEG_RST_MASK_H 0xD0U
#define JPEG_RST_MASK_L 0x07U

/*! Non- IDR Picture (I, P and B slice type) */
#define H264_NALU_TYPE_NONIDR  1U
/*! IDR Picture */
#define H264_NALU_TYPE_IDR  5U
/*! IDR Picture */
#define H264_NALU_TYPE_SPS  7U
/*! IDR Picture */
#define H264_NALU_TYPE_PPS  8U


#define VLAN_TPID 0x8100U
#define AVBTP_STREAM_ID_VALID (1U << 7U)
#define AVBTP_TIMESTAMP_VALID (1U << 0)
#define AVBTP_MEDIACLOCK_RESTART (1U << 3U)
#define AVBTP_TIMESTAMP_UNCERTAIN (1U << 0)

#if defined(USE_EXPERIMENTAL_ETHTYPE)
#define EXPECTED_ETHERTYPE 0x88B5U
#else
#define EXPECTED_ETHERTYPE 0x22F0U
#endif

/* For debug - variable can be changed through CCS */
volatile uint32_t expectedEtherType = EXPECTED_ETHERTYPE;

/*
 * When parsing AVBTP packets, the header size + the 61883 header size (part of the AVB payload)
 * is looked at
 */
#define AVBTP_61883_HEADER_SIZE (sizeof(ether_frame_header_t) + sizeof(avbtp_cm_stream_header_t) + 8)

/* EDMA driver does not publicly define all bit shifts to be used to get/set register fields
 * in an EDMA PaRAM set. This shift is to access the STATIC field in the OPTION register of an
 * EDMA PaRAM set.
 */
#define OPT_STATIC_SHIFT (0x3U)

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static bool checkForJpegSOI(uint8_t const *buffer);
static bool checkForJpegRST(uint8_t const *buffer);
static bool checkForJpegEOI(uint8_t const *buffer, const uint32_t size);
static bool isBrokenSequence(uint32_t seqNum, uint32_t prevSeqNum);

static bool checkForH264IPFrame(uint8_t const *buffer, uint32_t bufLength);

static avbtp_listener_handle_t findListener(avbtp_handle_t avh, uint8_t const *pStreamID);
static void nextBufferIdx(app_buff_details_t bufD);
static bool findEmptyBuffer(app_buff_details_t bufD);
static void dispatchCurrentBuffer(avbtp_listener_handle_t avlh, uint32_t errorStatus);
static void notifyClient(avbtp_listener_handle_t avlh);

static void getPortMAC(avbtp_handle_t avh, uint8_t *pMACData);
static void getPTPStamp(avbtp_talker_handle_t avth, avbtp_cm_stream_packet_t *cmsp);
static void fillTxPacket(avbtp_talker_handle_t avth, AVBTP_TxPacket *pPacket, uint16_t packetSize, avbtp_tx_buffer *buffer);
static bool hasDataAvailable(avbtp_talker_handle_t avth);

static uint32_t getBit8(uint8_t x);
static uint32_t get7lsb(uint8_t x);

static void waitForEdmaTransfer(avbtp_handle_t avh);
static void startEdmaTransfer(avbtp_handle_t avh, queue_t *pTransferQueue);
static void addToEdmaTransferQueue(queue_t *pTransferQueue, AVBTP_RxPacket *pAVBTPPacket, uint8_t const *pDst, uint32_t size);
static EDMA3_DRV_Result edmaInit(avbtp_handle_t avh);
static EDMA3_DRV_Result edmaDeInit(avbtp_handle_t avh);
static EDMA3_DRV_Result setEdmaParam(avbtp_handle_t avh, AVBTP_RxPacket *pPacket);
#if defined(USE_DMA_INTERRUPTS)
static void edmaTransferCompleteCb(uint32_t tcc, EDMA3_RM_TccStatus status, void *appData);
#endif


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(AVB_DYNAMIC_ALLOCATION)
struct avbtp_state AVBTP_stateObj;
struct avbtp_listener AVBTP_listeners[AVBTP_MAX_LISTENERS];
struct avbtp_talker AVBTP_talkers[AVBTP_MAX_TALKERS];
#endif

/* Data to keep track of open references to the GMACSW Hardware Driver */
static uint32_t         LOCAL_avbtpRefCount = 0;
static avbtp_handle_t   LOCAL_avbtpRef     = NULL;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(__GNUC__)
uint8_t gAVBRxMemPool[DEFAULT_PACKET_SIZE * AVB_RX_PACKETS] __attribute__(( aligned(128), section(".far:AVBTP_MEMPOOL") ));
uint8_t gAVBTxMemPool[AVBTP_PACKET_HEADER_SIZE * AVB_TX_PACKETS] __attribute__(( aligned(128), section(".far:AVBTP_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gAVBRxMemPool, 128);
#pragma DATA_SECTION(gAVBRxMemPool, ".far:AVBTP_MEMPOOL");
uint8_t gAVBRxMemPool[DEFAULT_PACKET_SIZE * AVB_RX_PACKETS];

#pragma DATA_ALIGN(gAVBTxMemPool, 128);
#pragma DATA_SECTION(gAVBTxMemPool, ".far:AVBTP_MEMPOOL");
uint8_t gAVBTxMemPool[AVBTP_PACKET_HEADER_SIZE * AVB_TX_PACKETS];
#endif

#if defined(__GNUC__)
AVBTP_RxPacket gAVBRxPackets[AVB_RX_PACKETS] __attribute__(( aligned(128), section(".far:AVBTP_MEMPOOL") ));
AVBTP_TxPacket gAVBTxPackets[AVB_TX_PACKETS] __attribute__(( aligned(128), section(".far:AVBTP_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gAVBRxPackets, 128);
#pragma DATA_SECTION(gAVBRxPackets, ".far:AVBTP_MEMPOOL");
AVBTP_RxPacket gAVBRxPackets[AVB_RX_PACKETS];

#pragma DATA_ALIGN(gAVBTxPackets, 128);
#pragma DATA_SECTION(gAVBTxPackets, ".far:AVBTP_MEMPOOL");
AVBTP_TxPacket gAVBTxPackets[AVB_TX_PACKETS];
#endif


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

avbtp_handle_t avbtp_open(void)
{
    avbtp_handle_t avh;
    uint32_t i;

    /* Increment the reference count */
    LOCAL_avbtpRefCount++;

    if (LOCAL_avbtpRefCount > (uint32_t)1U)
    {
        /*
         * If reference count at entry was non-zero, AVBTP was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
        return LOCAL_avbtpRef;
    }

#if defined(AVB_DYNAMIC_ALLOCATION)
    avh = calloc(1, sizeof(struct avbtp_state));
    if (avh == NULL) return NULL;
#else
    avh = &AVBTP_stateObj;
    memset(avh, 0, sizeof(struct avbtp_state));
#endif

    edmaInit(avh);
    if (avh->edma == NULL) { goto teardown; }

    /* Clear the entire array as we'd like to avoid releasing
     * garbage edma channels during teardown when failing to
     * obtain a PaRAM set from setEdmaParam below
     */
    memset(gAVBRxPackets, 0, sizeof(gAVBRxPackets));

    /* Initialize the AV packet pools which are used by the AVB2NSP translation
     * layer to receive/transmit data
     */
    AVBTP_queueInit(&avh->rxFreeAVBPacketQueue);
    for (i = 0U; i < (uint32_t)AVB_RX_PACKETS; i++)
    {
        EDMA3_DRV_Result ret;

        gAVBRxPackets[i].pBuffer = &gAVBRxMemPool[i * (uint32_t)DEFAULT_PACKET_SIZE];
        gAVBRxPackets[i].bufferSize = DEFAULT_PACKET_SIZE;

        ret = setEdmaParam(avh, &gAVBRxPackets[i]);
        if (ret != (EDMA3_DRV_Result)EDMA3_DRV_SOK) { goto teardown; }

        AVBTP_enqueue(&avh->rxFreeAVBPacketQueue, (node_t *)&gAVBRxPackets[i]);
    }

    AVBTP_queueInit(&avh->txFreeAVBPacketQueue);
    for (i = 0U; i < (uint32_t)AVB_TX_PACKETS; i++)
    {
        gAVBTxPackets[i].pHeader = &gAVBTxMemPool[i * (uint32_t)AVBTP_PACKET_HEADER_SIZE];
        gAVBTxPackets[i].notifyFree = false;
        AVBTP_enqueue(&avh->txFreeAVBPacketQueue, (node_t *)&gAVBTxPackets[i]);
    }

    /* Link up the packet's PaRAMs ahead of time to reduce
     * time spent writing to DMA registers during normal operation.
     * The link list can still be updated during processing but by linking at init
     * we minimize the amount of register writes necessary to form a full linked list
     */
    for (i = 0U; i < ((uint32_t)AVB_RX_PACKETS - (uint32_t)1U); i++)
    {
        gAVBRxPackets[i].pNextEdmaParams = gAVBRxPackets[i+1U].pEdmaParams;
        gAVBRxPackets[i].pEdmaParams->LINK_BCNTRLD = (uint32_t)gAVBRxPackets[i+1U].pEdmaParams & 0xFFFFU;
    }
    gAVBRxPackets[(AVB_RX_PACKETS-1U)].pNextEdmaParams = gAVBRxPackets[0].pEdmaParams;
    gAVBRxPackets[(AVB_RX_PACKETS-1U)].pEdmaParams->LINK_BCNTRLD = (uint32_t)gAVBRxPackets[0].pEdmaParams & 0xFFFFU;

    LOCAL_avbtpRef = avh;
    return avh;

teardown:
    avbtp_close(avh);
    return NULL;
}

void avbtp_close(avbtp_handle_t avh)
{
    uint32_t i;

    /* Decrement reference counter and return if still non-zero */
    LOCAL_avbtpRefCount--;

    if ((uint32_t)0U == LOCAL_avbtpRefCount)
    {
        AVB2NSP_close(avh->hAVB2NSP);

        for (i = 0; i < (uint32_t)AVBTP_MAX_LISTENERS; i++)
        {
            if (avh->listeners[i] != NULL)
            {
                avbtp_listener_close(avh->listeners[i]);
            }
        }

        for (i = 0; i < (uint32_t)AVBTP_MAX_TALKERS; i++)
        {
            if (avh->talkers[i] != NULL)
            {
               avbtp_talker_close(avh->talkers[i]);
            }
        }

        edmaDeInit(avh);

#if defined(AVB_DYNAMIC_ALLOCATION)
        free(avh);
#endif
    }
}

avbtp_listener_handle_t avbtp_listener_open(
        avbtp_handle_t avh,
        const uint8_t *talker_addr,
        avbtp_rcv_sd_cb_t rcv_sd_cb,
        void *rcv_sd_cbdata,
        avbtp_rcv_cd_cb_t rcv_cd_cb,
        void *rcv_cd_cbdata,
        const uint8_t *streamID)
{
    avbtp_listener_handle_t avlh;
    uint32_t free_idx;

    for (free_idx = 0U; free_idx < (uint32_t)AVBTP_MAX_LISTENERS; free_idx++) {
        if (NULL == avh->listeners[free_idx])
        {
            break;
        }
    }

    if (free_idx >= AVBTP_MAX_LISTENERS)
    {
        return NULL;
    }

#if defined(AVB_DYNAMIC_ALLOCATION)
    avlh = calloc(1, sizeof(struct avbtp_listener));
    if (avlh == NULL) return NULL;
#else
    avlh = &AVBTP_listeners[free_idx];
    memset(avlh, 0, sizeof(struct avbtp_listener));
#endif

    avlh->avh = avh;
    avlh->rcv_sd_cb = rcv_sd_cb;
    avlh->rcv_sd_cbdata = rcv_sd_cbdata;
    /* Sequencing starts at 0, so previous Seq num at init should be one less (8-bit field rolled over is 255) */
    avlh->prevSeqNum = 255;
    avlh->avbTpSubType  = -1;
    memcpy(&avlh->streamID[0], streamID, sizeof(avlh->streamID));
    memcpy(&avlh->talker_addr[0], talker_addr, sizeof(avlh->talker_addr));

    avlh->index = free_idx;
    avh->listeners[free_idx] = avlh;

    return avlh;
}

void avbtp_listener_close(avbtp_listener_handle_t avlh)
{
    avlh->avh->listeners[avlh->index] = NULL;
#if defined(AVB_DYNAMIC_ALLOCATION)
    free(avlh);
#endif
}

avbtp_talker_handle_t avbtp_talker_open(
        avbtp_handle_t avh,
        const uint8_t *listenerMAC,
        avbtp_talker_cb cb,
        void *talker_cbdata,
        uint32_t avbTpSubType,
        uint32_t cvFormatSubType)
{
    avbtp_talker_handle_t avth;
    uint32_t free_idx;

    for (free_idx = avh->numTalkersOpen; free_idx < (uint32_t)AVBTP_MAX_TALKERS; free_idx++) {
        if (NULL == avh->talkers[free_idx])
        {
            break;
        }
    }

    if (free_idx >= AVBTP_MAX_TALKERS)
    {
        return NULL;
    }

#if defined(AVB_DYNAMIC_ALLOCATION)
    avth = calloc(1, sizeof(struct avbtp_talker));
    if (avth == NULL) return NULL;
#else
    avth = &AVBTP_talkers[free_idx];
    memset(avth, 0, sizeof(struct avbtp_talker));
#endif

    avth->avh = avh;
    avth->index = free_idx;
    avth->prevSeqNum = 255;
    avth->avbTpSubType  = avbTpSubType;
    avth->cvFormatSubType  = cvFormatSubType;
    avth->vlanId = AVBTP_VLAN_ID;
    avth->vlanPriority = AVBTP_VLAN_PRIORITY;
    avth->callBack = cb;
    avth->txCbData = talker_cbdata;
    avth->inUseBuffer = NULL;
    AVBTP_queueInit(&avth->readyBufferQ);

    if (NULL == listenerMAC)
    {
        memset(avth->dstMAC, 0xFFU, sizeof(avth->dstMAC));
    }
    else
    {
        memcpy(avth->dstMAC, listenerMAC, sizeof(avth->dstMAC));
    }

    getPortMAC(avh, avth->srcMAC);
    avh->talkers[free_idx] = avth;
    avh->numTalkersOpen++;

    return avth;
}

void avbtp_talker_close(avbtp_talker_handle_t avth)
{
    avth->avh->talkers[avth->index] = NULL;
    avth->avh->numTalkersOpen--;

#if defined(AVB_DYNAMIC_ALLOCATION)
    free(avth);
#endif
}

void avbtp_submit_buffer(avbtp_listener_handle_t avlh, app_buff_details_t buff_details)
{
    avlh->buffDetails = buff_details;
    avlh->buffDetails->buffIndex = 0;
    avlh->buffDetails->writePtr = avlh->buffDetails->arrBuffPtr[0];

    if ((buff_details->configBits & BUFF_NOTIFY_PACKET) == BUFF_NOTIFY_PACKET)
    {
        avlh->notifyPerPacket = 1U;
    }
    else
    {
        avlh->notifyPerPacket = 0U;
    }

    if ((buff_details->configBits & BUFF_NOTIFY_MJPEG_RST) == BUFF_NOTIFY_MJPEG_RST)
    {
        avlh->notifyJpegRestart = 1U;
    }
    else
    {
        avlh->notifyJpegRestart = 0U;
    }
}

int32_t avbtp_start(avbtp_handle_t avh)
{
    int32_t retVal = -1;

    if (NULL != avh)
    {

        if (FALSE == avh->initFlag)
        {
            AVB2NSP_Config avb2NspConfig;

            avb2NspConfig.clientData = avh;
            avb2NspConfig.rxFreeAVBTPPacketQueue = &avh->rxFreeAVBPacketQueue;
            avb2NspConfig.txFreeAVBTPPacketQueue = &avh->txFreeAVBPacketQueue;

            avh->hAVB2NSP = AVB2NSP_open(&avb2NspConfig);
            if (avh->hAVB2NSP == NULL) { return -1; }

            AVB2NSP_start(avh->hAVB2NSP);
            avh->initFlag =  TRUE;
        }

        retVal = 0;
    }
    return retVal;
}

void avbtp_get_statistics(avbtp_handle_t avh, struct avbtp_stats *stats)
{
    *stats = avh->stats;
}

void avbtp_clear_statistics(avbtp_handle_t avh)
{
    memset(&(avh->stats), 0, sizeof (struct avbtp_stats));
}

void avbtp_get_listener_stats(avbtp_listener_handle_t avlh, struct avbtp_stats *stats)
{
    *stats = avlh->stats;
}

void avbtp_clear_listener_stats(avbtp_listener_handle_t avlh)
{
    memset(&(avlh->stats), 0, sizeof (struct avbtp_stats));
}

uint32_t avbtp_get_rx_load(avbtp_handle_t avh)
{
    Load_Stat stat;
    if (Load_getTaskLoad(avh->hAVB2NSP->rxPacketTask, &stat))
    {
        return Load_calculateLoad(&stat);
    }
    return 0;
}

uint32_t avbtp_get_tx_load(avbtp_handle_t avh)
{
    Load_Stat stat;
    if (Load_getTaskLoad(avh->hAVB2NSP->txPacketTask, &stat))
    {
        return Load_calculateLoad(&stat);
    }
    return 0;
}

void avbtp_talker_set_vlan_info(avbtp_talker_handle_t avth, uint16_t vlanId, uint8_t vlanPriority)
{
    avth->vlanId = vlanId;
    avth->vlanPriority = vlanPriority;
}

void avbtp_talker_enqueue(avbtp_handle_t avh, avbtp_tx_buffer **buffers, uint32_t size)
{
    uint32_t i;
    for (i = 0; i < size; i++)
    {
        avbtp_tx_buffer *buffer = buffers[i];
        avbtp_talker_handle_t avth = buffer->avth;
        buffer->pRead = buffer->pData;
        buffer->remaining = buffer->size;
        AVBTP_enqueue(&avth->readyBufferQ, (node_t *)buffer);
    }
    AVB2NSP_kickTx(avh->hAVB2NSP);
}

void AVBTP_fillTxQueue(avbtp_handle_t avh, queue_t *pReadyQueue)
{
    uint32_t i;
    avbtp_tx_buffer *buffer;
    AVBTP_TxPacket *pPacket;
    uint32_t packetSize;
    avbtp_talker_handle_t avth;
    avbtp_talker_handle_t talkers[AVBTP_MAX_TALKERS];
    uint32_t activeTalkers;

    if (avh->numTalkersOpen == 0) { return; }

    activeTalkers = avh->numTalkersOpen;
    memcpy(talkers, avh->talkers, sizeof(talkers));

    while (activeTalkers > 0 && avh->txFreeAVBPacketQueue.count > 0)
    {
        for (i = 0; i < avh->numTalkersOpen; i++)
        {
            packetSize = AVBTP_MAX_STREAM_PAYLOAD_SIZE;
            avth = talkers[i];

            if (NULL == avth) { continue; }

            if (!hasDataAvailable(avth))
            {
                /* Remove from the list if there's no more data */
                talkers[i] = NULL;
                activeTalkers--;
                continue;
            }

            buffer = avth->inUseBuffer;
            if (buffer->remaining < packetSize)
            {
                packetSize = buffer->remaining;
            }

            pPacket = (AVBTP_TxPacket *)AVBTP_dequeue(&avh->txFreeAVBPacketQueue);
            if (NULL == pPacket) { break; }

            fillTxPacket(avth, pPacket, packetSize, buffer);

            if (buffer->remaining == 0)
            {
                pPacket->notifyFree = true;
                pPacket->callBack = avth->callBack;
                pPacket->txCbData= avth->txCbData;
                pPacket->talkerIndex= avth->index;
                pPacket->buffer = buffer;
                avth->inUseBuffer = NULL;
            }

            AVBTP_enqueue(pReadyQueue, (node_t *)pPacket);
        }
    }
}

void AVBTP_waitForPendingRxPackets(avbtp_handle_t avh)
{
    AVBTP_RxPacket *pAVBTPPacket;

    waitForEdmaTransfer(avh);

    /* DMA transfer is now complete so packets can be returned to the free list */
    pAVBTPPacket = (AVBTP_RxPacket *)AVBTP_dequeue(&avh->pendingDMAPacketQueue);
    while (pAVBTPPacket != NULL)
    {
       AVBTP_enqueue(&avh->rxFreeAVBPacketQueue, (node_t *)pAVBTPPacket);
       pAVBTPPacket = (AVBTP_RxPacket *)AVBTP_dequeue(&avh->pendingDMAPacketQueue);
    }
}

void AVBTP_processRxPackets(avbtp_handle_t avh, queue_t *pReadyQueue)
{
    AVBTP_RxPacket *pAVBTPPacket;
    queue_t dmaTransferQueue;
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    static uint32_t procCount = 0;
    uint32_t packetCount = 0;
    uint32_t time1;
#endif

    AVBTP_queueInit(&dmaTransferQueue);
    pAVBTPPacket = (AVBTP_RxPacket *)AVBTP_dequeue(pReadyQueue);
    /* Go through each arrived packet and process it */
    while (pAVBTPPacket != NULL)
    {
        /* Double cast to avoid MISRA-C:2004 11.4 */
        ether_frame_t *frame = (ether_frame_t *)((void *)pAVBTPPacket->pBuffer);
        avbtp_cm_stream_packet_t *cmsp = (avbtp_cm_stream_packet_t *)frame->payload;
        uint8_t *pPayload = cmsp->payload;
        avbtp_listener_handle_t avlh = NULL;
        app_buff_details_t bufD;
        uint32_t avbTpSubType, cvFormatSubType, cvFormatType;
        uint32_t payloadSize;
        uint32_t seqNum;
        bool brokenSeq;
        uint32_t origPacketCnt = avh->stats.packetCnt;

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        packetCount++;
        avb2NspStats.rxReadyAVBTPPacketDequeue++;
        time1 = TIMER_READ();
#endif
        /* Packet data is written to memory by hardware so we need to ensure cache coherency when
         * parsing header through MPU
         */
        Cache_inv((Ptr)pAVBTPPacket->pBuffer, (SizeT)AVBTP_61883_HEADER_SIZE, (Bits16)Cache_Type_ALLD, (Bool)1U);

        if (frame->header.etherType != ntohs(expectedEtherType))
        {
            avh->stats.errorCnt++;
            avh->stats.unexpectedEtherType++;
            goto next_packet;
        }

        /* Ignore control data packets */
        if (getBit8(cmsp->cmsh.cmh.oct[0]) != 0)
        {
            avh->stats.controlPacketCnt++;
            goto next_packet;
        }

        /* Only stream data is currently parsed. The IEEE722 spec requires a stream data packet to
         * always have the stream ID valid flag set to 1
         */
        if (getBit8(cmsp->cmsh.cmh.oct[1]) == 0)
        {
            avh->stats.errorCnt++;
            avh->stats.svFlagError++;
            goto next_packet;
        }

        avlh = findListener(avh, cmsp->cmsh.cmh.stream_id);
        if (avlh == NULL)
        {
            avh->stats.errorCnt++;
            avh->stats.unexpectedStreamID++;
            goto next_packet;
        }

        bufD = avlh->buffDetails;

        avbTpSubType = get7lsb(cmsp->cmsh.cmh.oct[0]);

        if (-1 == avlh->avbTpSubType)
        {
            /* First packet for this stream, set AVBTP data format for stream*/
            if ( (avbTpSubType != (uint32_t)AVBTP_SUBTYPE_CVF) &&
                 (avbTpSubType != (uint32_t)AVBTP_SUBTYPE_61883_IIDC) )
            {
                avh->stats.errorCnt++;
                avh->stats.unexpectedSubType++;
                goto next_packet;
            }
            else
            {
                avlh->avbTpSubType = avbTpSubType;
            }
        }

        if ( avbTpSubType != avlh->avbTpSubType )
        {
            avh->stats.errorCnt++;
            avh->stats.unexpectedSubType++;
            goto next_packet;
        }
        if ( AVBTP_SUBTYPE_CVF == avlh->avbTpSubType )
        {
            avbtp_cvf_fmt_data_t *cvFmtData =
                            (avbtp_cvf_fmt_data_t *)cmsp->cmsh.format_specific_data;
            /* Get format subtype from CVF format info */
            cvFormatType = cvFmtData->format_info[0];
            if (AVBTP_CV_FORMAT_RFC != cvFormatType)
            {
                avh->stats.errorCnt++;
                avh->stats.unexpectedCvformatType++;
                goto next_packet;
            }
            cvFormatSubType = cvFmtData->format_info[1];

            payloadSize = ntohs(cvFmtData->pd_length);

            if ((payloadSize == 0) || (payloadSize > AVBTP_MAX_STREAM_PAYLOAD_SIZE))
            {
                avh->stats.errorCnt++;
                avh->stats.invalidPacketSizeError++;
                dispatchCurrentBuffer(avlh, BUFF_ERR_PACKET_SIZE);
                goto next_packet;
            }

            if (AVBTP_CVF_FORMAT_SUBTYPE_MJPEG == cvFormatSubType)
            {
                bool containsJPEGSOI, containsJPEGEOI, containsJPEGRST;

                containsJPEGSOI = (bool)checkForJpegSOI(pPayload);
                if (avlh->notifyJpegRestart != 0U)
                {
                    containsJPEGRST = checkForJpegRST(pPayload);
                }
                else
                {
                    containsJPEGRST = (bool)false;
                }
                seqNum = (uint32_t)cmsp->cmsh.cmh.oct[2];
                brokenSeq = (bool)isBrokenSequence(seqNum, avlh->prevSeqNum);
                avlh->prevSeqNum = seqNum;

                Cache_inv((Ptr)(pPayload + payloadSize - JPEG_EOI_CHECK_NBYTES),
                                (SizeT)JPEG_EOI_CHECK_NBYTES, (Bits16)Cache_Type_ALLD, (Bool)1U);
                containsJPEGEOI = checkForJpegEOI(pPayload + payloadSize - JPEG_EOI_CHECK_NBYTES, JPEG_EOI_CHECK_NBYTES);

                /* we only care about broken sequences after we find the JPEG SOI marker.
                * If this packet happens to contain it, then don't drop it
                */
                if ((brokenSeq == (bool)true) && (containsJPEGSOI == false))
                {
                    avh->stats.errorCnt++;
                    avh->stats.outOfSequenceError++;
                    avlh->stats.errorCnt++;
                    avlh->stats.outOfSequenceError++;
                    dispatchCurrentBuffer(avlh, BUFF_ERR_PACKET_DROP | BUFF_ERR_PACKET_SEQUENCE);
                    goto next_packet;
                }

                if (containsJPEGSOI == (bool)true)
                {
                    if (BUFF_PARTIAL == bufD->buffState[bufD->buffIndex])
                    {
                        avh->stats.errorCnt++;
                        avh->stats.missedEOIError++;
                        avlh->stats.errorCnt++;
                        avlh->stats.missedEOIError++;
                        startEdmaTransfer(avh, &dmaTransferQueue);
                        dispatchCurrentBuffer(avlh, BUFF_ERR_NO_EOI_DETECTED);
                    }

                    if (findEmptyBuffer(bufD) == false)
                    {
                        avh->stats.errorCnt++;
                        avh->stats.noBuffersAvailable++;
                        avlh->stats.errorCnt++;
                        avlh->stats.noBuffersAvailable++;
                        goto next_packet;
                    }

                    bufD->dataLength[bufD->buffIndex] = 0;
                    bufD->buffState[bufD->buffIndex] = BUFF_PARTIAL;

                    avh->stats.numSOIMarkers++;
                    avlh->stats.numSOIMarkers++;
                }

                if (containsJPEGRST == (bool)true)
                {
                    avh->stats.numRestartMarkers++;
                    avlh->stats.numRestartMarkers++;
                    startEdmaTransfer(avh, &dmaTransferQueue);
                    /* Notify the listener client of the progress in the buffer */
                    notifyClient(avlh);
                }

                if (BUFF_PARTIAL == bufD->buffState[bufD->buffIndex])
                {
                    uint8_t *pDest = bufD->writePtr + (bufD->buffIndex * bufD->buffSize);
                    pDest += bufD->dataLength[bufD->buffIndex];

                    /* If there is no more space to copy, drop the packet */
                    if ((payloadSize + bufD->dataLength[bufD->buffIndex]) > bufD->buffSize)
                    {
                        avh->stats.errorCnt++;
                        avh->stats.insufficientSizeError++;
                        avlh->stats.errorCnt++;
                        avlh->stats.insufficientSizeError++;
                        dispatchCurrentBuffer(avlh, BUFF_ERR_SIZE);
                        goto next_packet;
                    }

                    addToEdmaTransferQueue(&dmaTransferQueue, pAVBTPPacket, pDest, payloadSize);
                    pAVBTPPacket = NULL;

                    bufD->dataLength[bufD->buffIndex] += payloadSize;
                    avh->stats.packetCnt++;
                    avlh->stats.packetCnt++;
                }

                if (containsJPEGEOI)
                {
                    avh->stats.numEOIMarkers++;
                    avlh->stats.numEOIMarkers++;
                    startEdmaTransfer(avh, &dmaTransferQueue);
                    dispatchCurrentBuffer(avlh, BUFF_NOERROR);
                }
            }
            else if (AVBTP_CVF_FORMAT_SUBTYPE_H264 == cvFormatSubType)
            {
                bool containsH264IPFrame;

                containsH264IPFrame = (bool)checkForH264IPFrame(pPayload, payloadSize);

                seqNum = (uint32_t)cmsp->cmsh.cmh.oct[2];
                brokenSeq = (bool)isBrokenSequence(seqNum, avlh->prevSeqNum);
                avlh->prevSeqNum = seqNum;

                /* we only care about broken sequences after we find the JPEG SOI marker.
                * If this packet happens to contain it, then don't drop it
                */
                if ((brokenSeq == (bool)true) && (containsH264IPFrame == false))
                {
                    avh->stats.errorCnt++;
                    avh->stats.outOfSequenceError++;
                    avlh->stats.errorCnt++;
                    avlh->stats.outOfSequenceError++;
                    dispatchCurrentBuffer(avlh, BUFF_ERR_PACKET_DROP | BUFF_ERR_PACKET_SEQUENCE);
                    goto next_packet;
                }

                if (containsH264IPFrame == (bool)true)
                {
                    if ( (BUFF_PARTIAL == bufD->buffState[bufD->buffIndex]) && (avlh->stats.numSOIMarkers > 1) )
                    {
                        startEdmaTransfer(avh, &dmaTransferQueue);
                        dispatchCurrentBuffer(avlh, BUFF_NOERROR);
                        avlh->stats.numEOIMarkers++;
                        avh->stats.numEOIMarkers++;
                    }

                    if (findEmptyBuffer(bufD) == false)
                    {
                        avh->stats.errorCnt++;
                        avh->stats.noBuffersAvailable++;
                        avlh->stats.errorCnt++;
                        avlh->stats.noBuffersAvailable++;
                        goto next_packet;
                    }

                    bufD->dataLength[bufD->buffIndex] = 0;
                    bufD->buffState[bufD->buffIndex] = BUFF_PARTIAL;

                    avh->stats.numSOIMarkers++;
                    avlh->stats.numSOIMarkers++;
                }

                if (BUFF_PARTIAL == bufD->buffState[bufD->buffIndex])
                {
                    uint8_t *pDest = bufD->writePtr + (bufD->buffIndex * bufD->buffSize);
                    pDest += bufD->dataLength[bufD->buffIndex];

                    /* If there is no more space to copy, drop the packet */
                    if ((payloadSize + bufD->dataLength[bufD->buffIndex]) > bufD->buffSize)
                    {
                        avh->stats.errorCnt++;
                        avh->stats.insufficientSizeError++;
                        avlh->stats.errorCnt++;
                        avlh->stats.insufficientSizeError++;
                        dispatchCurrentBuffer(avlh, BUFF_ERR_SIZE);
                        goto next_packet;
                    }

                    addToEdmaTransferQueue(&dmaTransferQueue, pAVBTPPacket, pDest, payloadSize);
                    pAVBTPPacket = NULL;

                    bufD->dataLength[bufD->buffIndex] += payloadSize;
                    avh->stats.packetCnt++;
                    avlh->stats.packetCnt++;
                }

            }
            else
            {
                /* Other format subtype not supported yet */
                avh->stats.errorCnt++;
                avh->stats.unexpectedCvformatSubType++;
                goto next_packet;
            }
        }
        else
        {
            avh->stats.errorCnt++;
            avh->stats.unexpectedSubType++;
            goto next_packet;
        }

        if (avlh->notifyPerPacket == true)
        {
            startEdmaTransfer(avh, &dmaTransferQueue);
            notifyClient(avlh);
        }

next_packet:
        /* Count ignored packets */
        if (avh->stats.packetCnt == origPacketCnt)
        {
            avh->stats.ignoredPacketCnt++;
            if (avlh != NULL)
            {
                avlh->stats.ignoredPacketCnt++;
            }
        }
        if (pAVBTPPacket != NULL)
        {
            AVBTP_enqueue(&avh->rxFreeAVBPacketQueue, (node_t *)pAVBTPPacket);
        }

        pAVBTPPacket = (AVBTP_RxPacket *)AVBTP_dequeue(pReadyQueue);

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        avb2NspStats.rxFreeAVBTPPacketEnqueue++;
        {
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);

            avb2NspStats.procStats.lastCycleCnt = timeDiff;
            avb2NspStats.procStats.totalCycleCnt += timeDiff;
        }
#endif
    }

    startEdmaTransfer(avh, &dmaTransferQueue);

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    avb2NspStats.procStats.packetsPerProcessingCall[procCount] = packetCount;
    avb2NspStats.procStats.totalPacketCount += packetCount;
    if (packetCount > avb2NspStats.procStats.packetsPerProcessingCallMax)
    {
       avb2NspStats.procStats.packetsPerProcessingCallMax = packetCount;
    }

    procCount = (procCount + 1) & 0xFF;
#endif
}



/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static bool checkForH264IPFrame(uint8_t const *buffer, uint32_t bufferLen)
{
    uint32_t loopCount, newNalType;
    bool     h264IPFrameFlag = FALSE;

    loopCount = 0;

    if (bufferLen < 8)
        return (0);

    if ((buffer[loopCount++] == 0 && buffer[loopCount++] == 0 &&
         buffer[loopCount++] == 0 && buffer[loopCount++] == 0x01) ||
        (buffer[loopCount++] == 0 && buffer[loopCount++] == 0 &&
         buffer[loopCount++] == 1))
    {
        newNalType = buffer[loopCount++] & 0x1f;

        if ( (H264_NALU_TYPE_IDR == newNalType) ||
            (H264_NALU_TYPE_NONIDR == newNalType) )
        {
            h264IPFrameFlag = TRUE;
        }
        else if ( H264_NALU_TYPE_SPS == newNalType )
        {
            // TODO add logic to parse till IDR frame
            h264IPFrameFlag = TRUE;
        }
    }
    else
    {
        h264IPFrameFlag = FALSE;
    }

    return h264IPFrameFlag;
}

static bool checkForJpegSOI(uint8_t const *buffer)
{
    /*
     * TODO: In the future, we may have to deal with SOI flags that do not
     *        appear at the start of the payload.
     */
    return (bool)((buffer[0] == (uint8_t)JPEG_MARKER_H) && (buffer[1] == (uint8_t)JPEG_SOI));
}

static bool checkForJpegRST(uint8_t const *buffer)
{
    /*
     * TODO: In the future, we may have to deal with RST flags that do not
     *        appear at the start of the payload.
     */
    return (bool)((buffer[0] == (uint8_t)JPEG_MARKER_H) &&
            ((buffer[1] & JPEG_RST_MASK_H) == JPEG_RST_MASK_H) &&
            ((buffer[1] & 0x0FU) <= JPEG_RST_MASK_L));
}

static bool checkForJpegEOI(uint8_t const *buffer, const uint32_t size)
{
    uint32_t i;
    for (i = size - 1U; i > 0U; --i)
    {
        if ((buffer[i - 1U] == (uint8_t)JPEG_MARKER_H) && (buffer[i] == (uint8_t)JPEG_EOI))
        {
            return (bool)true;
        }
    }
    return (bool)false;
}

static bool isBrokenSequence(uint32_t seqNum, uint32_t prevSeqNum)
{
    /* 8-bit packet sequence number field rolls-over*/
    uint32_t expectedSeq = (prevSeqNum + 1U) & (uint32_t)0xFFU;
    return (bool)(expectedSeq != seqNum);
}

static avbtp_listener_handle_t findListener(avbtp_handle_t avh, uint8_t const *pStreamID)
{
    uint32_t i;
    for (i = 0; i < (uint32_t)AVBTP_MAX_LISTENERS; i++)
    {
       if ((avh->listeners[i] != NULL))
       {
           if (0 == memcmp(pStreamID, avh->listeners[i]->streamID, (size_t)8U))
           {
               return avh->listeners[i];
           }
       }
    }
    return NULL;
}

static void nextBufferIdx(app_buff_details_t bufD)
{
    bufD->buffIndex++;
    if (bufD->buffIndex >= bufD->buffCount)
    {
        bufD->buffIndex = 0;
    }
}

static bool findEmptyBuffer(app_buff_details_t bufD)
{
    uint32_t numBufsToCheck = bufD->buffCount;
    bool ret = (bool)true;

    while (bufD->buffState[bufD->buffIndex] != BUFF_EMPTY)
    {
        nextBufferIdx(bufD);
        numBufsToCheck--;
        if (0 == numBufsToCheck)
        {
            ret = (bool)false;
            break;
        }
    }

    return ret;
}

static void dispatchCurrentBuffer(avbtp_listener_handle_t avlh, uint32_t errorStatus)
{
    app_buff_details_t bufD = avlh->buffDetails;
    if (BUFF_PARTIAL == bufD->buffState[bufD->buffIndex])
    {
        uint8_t *pBuffer = bufD->writePtr + (bufD->buffIndex * bufD->buffSize);
        uint32_t size = bufD->dataLength[bufD->buffIndex];

        bufD->buffState[bufD->buffIndex] = BUFF_FULL;
        bufD->error = errorStatus;
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        avb2NspStats.procStats.jpegFrameFullCallbackCount[avlh->index]++;
#endif

        AVBTP_waitForPendingRxPackets(avlh->avh);
        avlh->rcv_sd_cb(pBuffer, size, NULL, avlh->rcv_sd_cbdata, avlh->index, bufD->buffIndex);
        nextBufferIdx(bufD);
    }
}

static void notifyClient(avbtp_listener_handle_t avlh)
{
    app_buff_details_t bufD = avlh->buffDetails;
    if (BUFF_PARTIAL == bufD->buffState[bufD->buffIndex])
    {
        uint8_t *pBuffer = bufD->writePtr + (bufD->buffIndex * bufD->buffSize);
        uint32_t size = bufD->dataLength[bufD->buffIndex];
        bufD->error = 0;
        AVBTP_waitForPendingRxPackets(avlh->avh);
        avlh->rcv_sd_cb(pBuffer, size, NULL, avlh->rcv_sd_cbdata, avlh->index, bufD->buffIndex);
    }
}

/* The DMA setup codes attempts to minimize writes to PaRAM registers by using a linked list of PaRAM sets as follows:
 * dummy (active set mapped in QDMA channel) -> head of list -> next -> .... -> end of list
 * Using this approach then:
 *  - only the DST and ACNT parameters need to be updated per PaRAM set
 *  - OPT field is updated on the end of list PaRAM set to mark it as end of list and enable completion notifications.
 *  - The LINK field of the last packet does not have to be updated as we can use the "STATIC" bit in the OPT field to mark the end.
 *  - OPT field is cleared in the end-of-list PaRAM set after the transfer as it may not necessarily represent the end of a list in a future transaction.
 *  - only two fields need update in the dummy PaRAM set to clear the dirty fields after the last transaction (OPT and A_B_CNT)
 *  - an additional two fields are updated in the dummy PaRAM set to kickoff the transfer - link to the head of the list and the CCNT trigger word.
 *  - This is a a total of 2*N + 6 (where N is number of PaRAM sets to transfer) total 32-bit writes to PaRAM registers in the ideal scenario
 *  - The AVB parser may have decided to ignore certain packets (for example waiting for JPEG SOI, or ignoring control data packets). In this case,
 *    the LINK field has to be updated as we form the link list, hence there will be an upper bound of 3N+6 writes per DMA list
 */
#if defined(USE_DMA_INTERRUPTS)
static void edmaTransferCompleteCb(uint32_t tcc, EDMA3_RM_TccStatus status, void *appData)
{
    avbtp_handle_t avh = (avbtp_handle_t)appData;
    Semaphore_post(avh->edmaSem);
}
#endif

static void waitForEdmaTransfer(avbtp_handle_t avh)
{
    AVBTP_RxPacket *pLastPacket = (AVBTP_RxPacket *)avh->pendingDMAPacketQueue.pTail;

    if (pLastPacket != NULL)
    {
        /* Wait for previous transfer to finish */
#if defined(USE_DMA_INTERRUPTS)
        Semaphore_pend(avh->edmaSem, BIOS_WAIT_FOREVER);
#else
        EDMA3_DRV_waitAndClearTcc(avh->edma, avh->edmaTCC);
#endif
        /* Reset options as next link list terminator will be a different PaRAM set */
        pLastPacket->pEdmaParams->OPT = 0;
    }
}

static void startEdmaTransfer(avbtp_handle_t avh, queue_t *pTransferQueue)
{
    if (pTransferQueue->count != 0)
    {
        AVBTP_RxPacket *pFirstPacket = (AVBTP_RxPacket *)pTransferQueue->pHead;
        AVBTP_RxPacket *pLastPacket = (AVBTP_RxPacket *)pTransferQueue->pTail;
        EDMA3_DRV_ParamentryRegs *dummyParam = avh->pEdmaParams;

        AVBTP_waitForPendingRxPackets(avh);

        /* Clear dirty field, this may have options set from the last transfer */
        dummyParam->OPT = 0;

        /* A-synchronized dummy transfers need ACNT = 0, BCNT = 1, CCNT = 1, otherwise the EDMA CC marks it as a
         * null transfer instead.*/
        dummyParam->A_B_CNT = 1U << 16U;

        /* Link dummy transfer to head of valid param set list */
        dummyParam->LINK_BCNTRLD = (uint32_t)pFirstPacket->pEdmaParams & 0xFFFFU;

        /* Enable completion bit as its the last packet in the list.
         * Setting the static bit terminates the linked list.
         */
        pLastPacket->pEdmaParams->OPT = ((avh->edmaTCC << (uint32_t)OPT_TCC_SHIFT) & (uint32_t)OPT_TCC_MASK) |
                          ((uint32_t)1U << (uint32_t)OPT_TCINTEN_SHIFT) | ((uint32_t)1U << (uint32_t)OPT_STATIC_SHIFT);

        /* Kick-off the transfer as QDMA trigger word is ccnt */
        dummyParam->CCNT = 1U;

        /* Keep a record of the pending transfers;
         * this is just a shallow copy as the nodes are already linked together */
        AVBTP_queueCopy(&avh->pendingDMAPacketQueue, pTransferQueue);
        AVBTP_queueInit(pTransferQueue);
    }
}

static void addToEdmaTransferQueue(queue_t *pTransferQueue, AVBTP_RxPacket *pAVBTPPacket, uint8_t const *pDst, uint32_t size)
{
    AVBTP_RxPacket *pPrevPacket = (AVBTP_RxPacket *)pTransferQueue->pTail;
    EDMA3_DRV_ParamentryRegs *packetParam = pAVBTPPacket->pEdmaParams;

    AVBTP_enqueue(pTransferQueue, (node_t *)pAVBTPPacket);

    /* Bcnt = 1, Acnt = size */
    packetParam->A_B_CNT = ((uint32_t)1U << 16U) | size;
    packetParam->DST = (uint32_t)pDst;

    if (pPrevPacket != NULL)
    {
        EDMA3_DRV_ParamentryRegs *prevPacketParam = pPrevPacket->pEdmaParams;
        EDMA3_DRV_ParamentryRegs *expectedPacketParam = pPrevPacket->pNextEdmaParams;
        /* To avoid reading the LINK_BCNTRLD field, we cache the value
         * and only update it when necessary to avoid a write to LINK_BCNTRLD
         */
        if (expectedPacketParam != packetParam)
        {
            prevPacketParam->LINK_BCNTRLD = (uint32_t)packetParam & 0xFFFFU;
            pPrevPacket->pNextEdmaParams = packetParam;
        }
    }
}

static EDMA3_DRV_Result setEdmaParam(avbtp_handle_t avh, AVBTP_RxPacket *pPacket)
{
    EDMA3_DRV_Result result = (EDMA3_DRV_Result)EDMA3_DRV_SOK;
    uint32_t paramAddr = 0;
    EDMA3_DRV_ParamentryRegs *pEdmaParams;
    uint32_t chId = EDMA3_DRV_LINK_CHANNEL;
    /* Double cast to avoid MISRA-C:2004 11.4 */
    ether_frame_t *frame = (ether_frame_t *)((void *)pPacket->pBuffer);
    avbtp_cm_stream_packet_t *cmsp = (avbtp_cm_stream_packet_t *)frame->payload;

    result = EDMA3_DRV_requestChannel(avh->edma, &chId, NULL, (EDMA3_RM_EventQueue)0, NULL, NULL);
    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        LOGE("failed requesting EDMA channel %d\n", result);
        return result;
    }

    result = EDMA3_DRV_getPaRAMPhyAddr(avh->edma, chId, &paramAddr);
    if ((result != (EDMA3_DRV_Result)EDMA3_DRV_SOK) || (paramAddr == 0))
    {
        LOGE("failed requesting PaRAM address %d\n", result);
        EDMA3_DRV_freeChannel(avh->edma, chId);
        return result;
    }

    pEdmaParams = (EDMA3_DRV_ParamentryRegs *)paramAddr;

    /* We minimize the amount of PaRAM set updates needed after the listeners get started by filling fields
     * that will remain constant after setup.
     */
    pEdmaParams->SRC = (uint32_t)cmsp->payload;
    pEdmaParams->CCNT = 1U;

    pPacket->pEdmaParams = pEdmaParams;
    pPacket->edmaChId = chId;

    return result;
}

static EDMA3_DRV_Result edmaInit(avbtp_handle_t avh)
{
    EDMA3_DRV_Handle edma;
    EDMA3_DRV_Result result = (EDMA3_DRV_Result)EDMA3_DRV_SOK;
    uint32_t tcc = EDMA3_DRV_TCC_ANY;
    uint32_t chId = EDMA3_DRV_QDMA_CHANNEL_ANY;
    uint32_t paramAddr = 0;

#if defined(USE_DMA_INTERRUPTS)
    {
        Semaphore_Params semParams;
        Semaphore_Params_init(&semParams);
        avh->edmaSem = Semaphore_create(0, &semParams, NULL);
        if (avh->edmaSem == NULL) return -1;
    }
#endif

    edma = edma3init(0, &result);
    if ((EDMA3_DRV_Result)EDMA3_DRV_E_INST_ALREADY_EXISTS == result)
    {
        EDMA3_RM_RegionId regionId = determineProcId();
        edma = EDMA3_DRV_getInstHandle(0, regionId, &result);
    }

    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        LOGE("failed edma3init %d\n", result);
        return result;
    }

#if defined(USE_DMA_INTERRUPTS)
    result = EDMA3_DRV_requestChannel(edma, &chId, &tcc, (EDMA3_RM_EventQueue)0, &edmaTransferCompleteCb, (void *)avh);
#else
    result = EDMA3_DRV_requestChannel(edma, &chId, &tcc, (EDMA3_RM_EventQueue)0, NULL, NULL);
#endif
    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        LOGE("failed requesting EDMA channel %d\n", result);
        edma3deinit(0, edma);
        return result;
    }

    result = EDMA3_DRV_getPaRAMPhyAddr(edma, chId, &paramAddr);
    if ((result != (EDMA3_DRV_Result)EDMA3_DRV_SOK) || (0 == paramAddr))
    {
        LOGE("failed requesting PaRAM address %d\n", result);
        EDMA3_DRV_freeChannel(edma, chId);
        edma3deinit(0, edma);
        return result;
    }

    avh->edma = edma;
    avh->edmaChId = chId;
    avh->edmaTCC = tcc;
    avh->pEdmaParams = (EDMA3_DRV_ParamentryRegs *)paramAddr;

    AVBTP_queueInit(&avh->pendingDMAPacketQueue);
    return result;
}

static EDMA3_DRV_Result edmaDeInit(avbtp_handle_t avh)
{
    uint32_t i;
    EDMA3_DRV_Result result = (EDMA3_DRV_Result)EDMA3_DRV_SOK;

    if (avh->edma == NULL) { return result; }

    result = EDMA3_DRV_freeChannel(avh->edma, avh->edmaChId);
    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        LOGE("failed freeing EDMA channel %d\n", result);
    }

    for (i = 0U; i < (uint32_t)AVB_RX_PACKETS; i++)
    {
        if (gAVBRxPackets[i].pEdmaParams != NULL)
        {
            result = EDMA3_DRV_freeChannel(avh->edma, gAVBRxPackets[i].edmaChId);
            if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
            {
                LOGE("failed freeing edma PaRAM set %d\n", result);
            }
        }
    }

    result = edma3deinit(0, avh->edma);
    avh->edma = NULL;

#if defined(USE_DMA_INTERRUPTS)
    Semaphore_delete(&avh->edmaSem);
#endif

    return result;
}

static uint32_t getBit8(uint8_t x)
{
    return (uint32_t)x & (uint32_t)0x80U;
}

static uint32_t get7lsb(uint8_t x)
{
    return (uint32_t)x & (uint32_t)0x7FU;
}

static void getPortMAC(avbtp_handle_t avh, uint8_t *pMACData)
{
    /*TODO: Obtain the port MAC address from NSP */
    pMACData[0] = 0xABU;
    pMACData[1] = 0xCDU;
    pMACData[2] = 0xEFU;
    pMACData[3] = 0xABU;
    pMACData[4] = 0xCDU;
    pMACData[5] = 0xEFU;
}

static void getPTPStamp(avbtp_talker_handle_t avth, avbtp_cm_stream_packet_t *cmsp)
{
    /*TODO: Hook this up with a PTP framework */
    cmsp->cmsh.timestamp = 0;
    /* Clear the TV valid bit as we don't have a timestamp right now */
    cmsp->cmsh.cmh.oct[1] &= ~(AVBTP_TIMESTAMP_VALID | AVBTP_MEDIACLOCK_RESTART);
    /* Uncertainty is determinted by the PTP framework */
    cmsp->cmsh.cmh.oct[3] &= ~AVBTP_TIMESTAMP_UNCERTAIN;
}

static void fillTxPacket(avbtp_talker_handle_t avth, AVBTP_TxPacket *pPacket, uint16_t packetSize, avbtp_tx_buffer *buffer)
{

    ether_frame_t *frame = (ether_frame_t *)((void *)pPacket->pHeader);
    avbtp_cm_stream_packet_t *cmsp = (avbtp_cm_stream_packet_t *)frame->payload;

    memcpy(frame->header.srcMac, avth->srcMAC, sizeof(frame->header.srcMac));
    memcpy(frame->header.dstMac, avth->dstMAC, sizeof(frame->header.dstMac));

    frame->header.vlanaf.tpid = htons(VLAN_TPID);
    frame->header.vlanaf.tci = htons((avth->vlanPriority << 13) | avth->vlanId);

    frame->header.etherType = htons(expectedEtherType);

    if (-1 == avth->avbTpSubType)
    {
        cmsp->cmsh.cmh.oct[0] = AVBTP_SUBTYPE_CVF;
    }
    else
    {
        cmsp->cmsh.cmh.oct[0] = avth->avbTpSubType;
    }

    getPTPStamp(avth, cmsp);

    /* The AVBTP stream id is a combination of the talker MAC address and 2-byte unique id - here we simply
     * use the index of this talker in our talker list for the unique id
     */
    memcpy(cmsp->cmsh.cmh.stream_id, frame->header.srcMac, sizeof(frame->header.srcMac));
    cmsp->cmsh.cmh.stream_id[6] = 0x00U;
    cmsp->cmsh.cmh.stream_id[7] = (uint8_t)avth->index;
    cmsp->cmsh.cmh.oct[1] |= AVBTP_STREAM_ID_VALID;

    avth->prevSeqNum++;
    cmsp->cmsh.cmh.oct[2] = avth->prevSeqNum;

    if (AVBTP_SUBTYPE_CVF == avth->avbTpSubType)
    {
        avbtp_cvf_fmt_data_t *cvFmtData =
                        (avbtp_cvf_fmt_data_t *)cmsp->cmsh.format_specific_data;
        cvFmtData->format_info[0] = AVBTP_CV_FORMAT_RFC;
        cvFmtData->format_info[1] = avth->cvFormatSubType;

        cvFmtData->format_info[2] = 0x0; //reserved
        cvFmtData->format_info[3] = 0x0; //reserved

        cvFmtData->pd_length = htons(packetSize);
    }
    else
    {
        avbtp_IEC_61883_fmt_data_t *iecFmtData =
                        (avbtp_IEC_61883_fmt_data_t *)cmsp->cmsh.format_specific_data;
        iecFmtData->pd_length = htons(packetSize);
    }

    pPacket->pBuffer = buffer->pRead;
    pPacket->bufferSize = packetSize;
    buffer->pRead += packetSize;
    buffer->remaining -= packetSize;

    /* Invalidate Eth Frame Header packet header as it is updated  here */
    Cache_wb((Ptr)pPacket->pHeader, AVBTP_PACKET_HEADER_SIZE, Cache_Type_ALLD, TRUE);

    /* The headers are assumed to be in a write-through region */
    if (buffer->needsFlushing)
    {
        /*TODO: consider not waiting for the writeback here - wait later using Cache_wait */
        Cache_inv((Ptr)pPacket->pBuffer, (SizeT)pPacket->bufferSize, (Bits16)Cache_Type_ALL, (Bool)1U);
    }
}

static bool hasDataAvailable(avbtp_talker_handle_t avth)
{
    if (NULL == avth->inUseBuffer)
    {
        avth->inUseBuffer = (avbtp_tx_buffer *)AVBTP_dequeue(&avth->readyBufferQ);
    }

    return avth->inUseBuffer != NULL;
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

