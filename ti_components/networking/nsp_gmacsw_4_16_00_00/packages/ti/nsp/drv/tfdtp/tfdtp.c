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
 *  \file   tfdtp.c
 *
 *  \brief  TFDTP stack implementation file.
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */

#include <stdlib.h>
#include <string.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/utils/Load.h>

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* TFDTP_NDK2_NSP layer Dependencies */
#include <ti/nsp/drv/ndk2nsp/ndk2nsp.h>

/* This module's header */
#include "tfdtp.h"
#include "tfdtp_priv.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

/* The EDMA driver does not expose this in a top level header - hence we define the extern here */
extern uint16_t determineProcId(void);
/* The PBM Q free count */
extern PBMQ PBMQ_free;

/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define TFDTP_TX_PACKETS (TFDTP2NSP_TX_PACKETS * (uint32_t)2U)

#define OPT_STATIC_SHIFT (0x3U)

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static inline int32_t Local_checkTxChParams(TFDTP_TxChOpenPrm_t *pTfdtpTxChOpenPrms);
static inline tfdtp_rx_channel_handle_t LOCAL_findRxChannel(tfdtp_handle_t hTfdtp, uint16_t channelId);
static bool LOCAL_findEmptyBuffer(tfdtp_rx_channel_handle_t hTfdtpRxCh);
static void LOCAL_dispatchCurrentBuffer(tfdtp_rx_channel_handle_t hTfdtpRxCh, tfdtp_rx_buf_handle_t appBuffh, uint32_t errorStatus);
static void LOCAL_getPortMAC(tfdtp_handle_t hTfdtp, uint8_t *pMACData);
static void LOCAL_fillTxPacket(tfdtp_tx_channel_handle_t hTfdtpTxCh, TFDTP_TxPacket *pPacket, uint16_t packetSize, tfdtp_tx_buf_t *pBuffer);
static bool LOCAL_checkForData(tfdtp_tx_channel_handle_t hTfdtpTxCh);

static void LOCAL_waitForEdmaTransfer(tfdtp_handle_t hTfdtp);
static void LOCAL_startEdmaTransfer(tfdtp_handle_t hTfdtp, queue_t *pTransferQueue);
static void LOCAL_addToEdmaTransferQueue(queue_t *pTransferQueue, TFDTP_RxPacket *pTFDTPPacket, uint8_t const *pDst, uint32_t size);
static EDMA3_DRV_Result LOCAL_edmaInit(tfdtp_handle_t hTfdtp);
static EDMA3_DRV_Result LOCAL_edmaDeInit(tfdtp_handle_t hTfdtp, NDK2NSP_Handle hNDK2NSP);
static EDMA3_DRV_Result LOCAL_setEdmaParam(tfdtp_handle_t hTfdtp, TFDTP_RxPacket *pPacket);
#if defined(USE_DMA_INTERRUPTS)
static void LOCAL_edmaTransferCompleteCb(uint32_t tcc, EDMA3_RM_TccStatus status, void *appData);
#endif
static inline uint32_t LOCAL_checkEmpty(const uint8_t * buf, uint32_t size) ;
static inline bool LOCAL_checkForSOF(uint32_t flags);

#if 0U
static void LOCAL_myUdpChecksum( UDPHDR *pUdpHdr, uint8_t *payload, uint16_t packetSize );
static int32_t LOCAL_findFrameBuffer(tfdtp_rx_channel_handle_t hTfdtpRxCh, uint16_t pckFrameId);
static bool LOCAL_checkForEoF(uint32_t flags);
#endif

static void inline TFDTP_print(char *prnStr, ...);

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
struct tfdtp_object TFDTP_stateObj;
#endif

/* Data to keep track of open references to the GMACSW Hardware Driver */
static uint32_t              LOCAL_tfdtpRefCount = 0;
static tfdtp_handle_t        LOCAL_tfdtpRef     = NULL;
static uint32_t              gTfdtpStackInitFlag = (uint32_t)FALSE;

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(__GNUC__)
uint8_t gTFDTPTxMemPool[TFDTP_TX_PACKETS][TFDTP_PACKET_HEADER_SIZE] __attribute__(( aligned(128), section(".far:TFDTP_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gTFDTPTxMemPool, 128);
#pragma DATA_SECTION(gTFDTPTxMemPool, ".far:TFDTP_MEMPOOL");
uint8_t gTFDTPTxMemPool[TFDTP_TX_PACKETS][TFDTP_PACKET_HEADER_SIZE];
#endif

#if defined(__GNUC__)
TFDTP_TxPacket gTFDTPTxPackets[TFDTP_TX_PACKETS] __attribute__(( aligned(128), section(".far:TFDTP_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gTFDTPTxPackets, 128);
#pragma DATA_SECTION(gTFDTPTxPackets, ".far:TFDTP_MEMPOOL");
TFDTP_TxPacket gTFDTPTxPackets[TFDTP_TX_PACKETS];
#endif

/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

tfdtp_handle_t TFDTP_initStack(NDK2NSP_Handle hNDK2NSP)
{
    tfdtp_handle_t      hTfdtp;
    TFDTP_RxPacket      *pCurr, *pPrev, *pHead;
    uint32_t            i;
    EDMA3_DRV_Result    edmaResult;

    /* Set TFDTP flag to true */
    gTfdtpStackInitFlag = (uint32_t) TRUE;

#if defined(NSP_DYNAMIC_ALLOCATION)
    hTfdtp = calloc(1U, sizeof(struct tfdtp_object));
    if (hTfdtp == NULL) return NULL;
#else
    hTfdtp = &TFDTP_stateObj;
    memset(hTfdtp, 0, sizeof(struct tfdtp_object));
#endif

    hTfdtp->hNDK2NSP = hNDK2NSP;
    LOCAL_edmaInit(hTfdtp);
    if (hTfdtp->edma == NULL)
    {
        goto teardown;
    }

    /* Initialize the AV packet pools for associating EDMA PaRAMs to NDK2NSP
     * rxFreeTFDTPPacketQueue packets queue (which is used by the NDK2NSP translation
     * layer to receive/transmit data
     */
    pHead = (TFDTP_RxPacket *) TFDTP_dequeue (&hNDK2NSP->rxFreeTFDTPNDKPacketQueue);
    /* Allocate PaRAM for head, for remaining packets it will be done in loop */
    edmaResult = LOCAL_setEdmaParam(hTfdtp, pHead);
    if (edmaResult != (EDMA3_DRV_Result)EDMA3_DRV_SOK) { goto teardown; }
    /* Keep track of head for linking last packet */
    pPrev = pHead;
    for (i = 0U; i < ((uint32_t)NDK_RX_PACKETS - 1U); i++)
    {
        /* Link up the packet's PaRAMs ahead of time to reduce
        * time spent writing to DMA registers during normal operation.
        * The link list can still be updated during processing but by linking at init
        * we minimize the amount of register writes necessary to form a full linked list
        */
        pCurr = (TFDTP_RxPacket *) TFDTP_dequeue (&hNDK2NSP->rxFreeTFDTPNDKPacketQueue);
        edmaResult = LOCAL_setEdmaParam(hTfdtp, pCurr);
        if (edmaResult != (EDMA3_DRV_Result)EDMA3_DRV_SOK) { goto teardown; }
        pPrev->pNextEdmaParams = pCurr->pEdmaParams;
        pPrev->pEdmaParams->LINK_BCNTRLD = (uint32_t)pCurr->pEdmaParams & 0xFFFFU;

        TFDTP_enqueue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue, (node_t *)pPrev);
        pPrev = pCurr;
    }

    pPrev->pNextEdmaParams = pHead->pEdmaParams;
    pPrev->pEdmaParams->LINK_BCNTRLD = (uint32_t)pHead->pEdmaParams & 0xFFFFU;
    TFDTP_enqueue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue, (node_t *)pPrev);

    /* Initialize Tx packets */
    TFDTP_queueInit(&hTfdtp->txFreeTFDTPPacketQueue);
    for (i = 0U; i < (uint32_t)TFDTP_TX_PACKETS; i++)
    {
        gTFDTPTxPackets[i].pHeader = gTFDTPTxMemPool[i];
        gTFDTPTxPackets[i].notifyFree = false;
        TFDTP_enqueue(&hTfdtp->txFreeTFDTPPacketQueue, (node_t *)&gTFDTPTxPackets[i]);
    }

    /* Store free packet queue handle used by TFDTP process packet functions,
     * this is needed as buffers are allocated by NDK2NSP layer */
    hTfdtp->rxFreeTFDTPPacketQueue = &hNDK2NSP->rxFreeTFDTPNDKPacketQueue;
    /* Store TFDTP handle to be returned to application */
    LOCAL_tfdtpRef = hTfdtp;
    return hTfdtp;

teardown:
    TFDTP_deInitStack(hNDK2NSP, hTfdtp);
    return NULL;
}

void TFDTP_deInitStack(NDK2NSP_Handle hNDK2NSP, tfdtp_handle_t hTfdtp)
{
    if ((uint32_t)TRUE == gTfdtpStackInitFlag)
    {
        /* As this is called from NDK2NSP we'll remove receive side reference which
         * is shared by TFDTP and NDK  */
        hTfdtp->rxFreeTFDTPPacketQueue = NULL;

        LOCAL_edmaDeInit(hTfdtp, hNDK2NSP);

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(hTfdtp);
#endif
        /* Set TFDTP flag false */
        gTfdtpStackInitFlag = (uint32_t) FALSE;
    }
}


tfdtp_handle_t TFDTP_open(TFDTP_OpenPrm_t *tfdtpOpenPrms)
{
    tfdtp_handle_t hTfdtp;

    if ((uint32_t) FALSE == gTfdtpStackInitFlag)
    {
        /* Should not come here as NDK should have initialized TFDTP stack during initialization */
        TFDTP_print ("In TFDTP_open...exiting\n");
        hTfdtp = NULL;
    }
    else
    {
        /* Increment the reference count */
        LOCAL_tfdtpRefCount++;

        if (LOCAL_tfdtpRefCount == (uint32_t)1U)
        {
            hTfdtp = LOCAL_tfdtpRef;
            /* Store TFDTP information in TFDTP state object */
            hTfdtp->rxUdpPort = tfdtpOpenPrms->rxUdpPort;
            if (NULL != tfdtpOpenPrms->printFxnCb)
            {
                hTfdtp->printFxnCb = tfdtpOpenPrms->printFxnCb;
                /* Register same function with NDK and GMAC */
                NDK2NSP_registerPrintFxnCb(hTfdtp->hNDK2NSP, (GMACSW_PrintFxnCallback)tfdtpOpenPrms->printFxnCb);
            }
            #if defined (DEBUG)
            else
            {
                /* If debug print callback fxn not given, use printf as default */
                hTfdtp->printFxnCb = (void (*)(const char *))printf;
            }
            #endif
            if ( 0U != tfdtpOpenPrms->myIpAddr)
            {
                hTfdtp->myIpAddr = tfdtpOpenPrms->myIpAddr;
            }
            else
            {
                /*  255.255.255.255 is broadcast address which in Internet Protocol
                * standards stands for this network, i.e. the local network */
                hTfdtp->myIpAddr = INADDR_BROADCAST;
            }

            memset(&hTfdtp->stats, 0, sizeof (hTfdtp->stats));

        }
        else
        {
           /*
            * If reference count at entry was non-zero, TFDTP was already opened, so
            * we just return a pointer to the state structure and increment the reference count
            */
            hTfdtp = LOCAL_tfdtpRef;
        }
    }
    return hTfdtp;
}

int32_t TFDTP_close(tfdtp_handle_t hTfdtp)
{
    uint32_t i;
    int32_t retVal = -1;

    if (NULL != hTfdtp)
    {
        /* Decrement reference counter and return if still non-zero */
        LOCAL_tfdtpRefCount--;

        if ((uint32_t)0U == LOCAL_tfdtpRefCount)
        {
            for (i = 0; i < hTfdtp->numRxChannelsOpen; i++)
            {
                if (TRUE == hTfdtp->rxChannels[i].isAllocated)
                {
                    TFDTP_closeRxChannel(&hTfdtp->rxChannels[i]);
                }
            }

            for (i = 0; i < hTfdtp->numTxChannelsOpen; i++)
            {
                if (TRUE == hTfdtp->txChannels[i].isAllocated)
                {
                    TFDTP_closeTxChannel(&hTfdtp->txChannels[i]);
                }
            }

            /*
            * We cant release TFDTP handle as it is initialized from NDK2NSP so
            * clear parameters initialized from user application
            */
            hTfdtp->numRxChannelsOpen = 0U;
            hTfdtp->numTxChannelsOpen = 0U;
            hTfdtp->rxUdpPort = 0U;
            hTfdtp->myIpAddr = 0U;
            hTfdtp->printFxnCb = NULL;
            memset(&hTfdtp->stats, 0, sizeof (hTfdtp->stats));

            /* Close transmit channel */
            TFDTP2NSP_close(hTfdtp->hTFDTP2NSP);

            /* Stop TFDTP Rx processing */
            NDK2NSP_stopTfdtpRx(hTfdtp->hNDK2NSP);

            /* Deinit TFDTP handle */
            hTfdtp->initFlag = FALSE;
            retVal = 0;
        }
    }

    return retVal;
}

tfdtp_rx_channel_handle_t TFDTP_openRxChannel(tfdtp_handle_t hTfdtp, TFDTP_RxChOpenPrm_t *pTfdtpRxChOpenPrms)
{
    tfdtp_rx_channel_handle_t hTfdtpRxCh;
    uint32_t free_idx;

    if (NULL == hTfdtp)
    {
        hTfdtpRxCh = NULL;
    }
    else if (NULL == pTfdtpRxChOpenPrms->rcv_cb_fxn)
    {
        TFDTP_print(" Channel Receive Callback function not set \n");
        hTfdtpRxCh = NULL;
    }
    else
    {
        /* Find empty TFDTP receive channel handle & return a pointer to it */
        for (free_idx = 0U; free_idx < TFDTP_MAX_RX_CHANNELS; free_idx++)
        {
            if (FALSE == hTfdtp->rxChannels[free_idx].isAllocated)
            {
                break;
            }
        }

        if (free_idx >= TFDTP_MAX_RX_CHANNELS)
        {
            return NULL;
        }

        hTfdtpRxCh = &hTfdtp->rxChannels[free_idx];
        memset(hTfdtpRxCh, 0, sizeof(struct tfdtp_rx_channel));
        hTfdtp->rxChannels[free_idx].isAllocated = TRUE;

        hTfdtpRxCh->index = free_idx;
        hTfdtpRxCh->hTfdtp = hTfdtp;
        hTfdtpRxCh->channelId = pTfdtpRxChOpenPrms->channelId;
        /* Initialize receiver configuration */

        hTfdtpRxCh->rcv_cb_fxn = pTfdtpRxChOpenPrms->rcv_cb_fxn;
        hTfdtpRxCh->rcv_cb_data = pTfdtpRxChOpenPrms->rcv_cb_data;

        /* Increment the channel count */
        hTfdtp->numRxChannelsOpen++;
    }

    return hTfdtpRxCh;
}

tfdtp_tx_channel_handle_t TFDTP_openTxChannel(tfdtp_handle_t hTfdtp, TFDTP_TxChOpenPrm_t *pTfdtpTxChOpenPrms)
{
    tfdtp_tx_channel_handle_t hTfdtpTxCh;
    uint32_t free_idx;

    if ( (NULL == hTfdtp) || (0U != Local_checkTxChParams(pTfdtpTxChOpenPrms)) )
    {
        hTfdtpTxCh = NULL;
    }
    else
    {
        /* Find empty TFDTP transmit channel handle & return a pointer to it */

        for (free_idx = 0U; free_idx < TFDTP_MAX_TX_CHANNELS; free_idx++) {
            if (FALSE == hTfdtp->txChannels[free_idx].isAllocated)
            {
                break;
            }
        }

        if (free_idx >= TFDTP_MAX_TX_CHANNELS)
        {
            return NULL;
        }

        hTfdtpTxCh = &hTfdtp->txChannels[free_idx];
        memset(hTfdtpTxCh, 0, sizeof(struct tfdtp_tx_channel));
        hTfdtp->txChannels[free_idx].isAllocated = TRUE;

        hTfdtpTxCh->index = free_idx;
        hTfdtpTxCh->hTfdtp = hTfdtp;
        hTfdtpTxCh->channelId = pTfdtpTxChOpenPrms->channelId;

        /* Initialize transmitter configuration */
        hTfdtpTxCh->hostInfo.hostUdpPort  = pTfdtpTxChOpenPrms->hostUdpPort;
        hTfdtpTxCh->hostInfo.hostIpAddr = pTfdtpTxChOpenPrms->hostIpAddr;
        hTfdtpTxCh->txCbFxn  = pTfdtpTxChOpenPrms->tx_cb_fxn;
        hTfdtpTxCh->txCbData = pTfdtpTxChOpenPrms->tx_cb_data;
        hTfdtpTxCh->frame_id = 0U;
        hTfdtpTxCh->prevSeqNum = 0U;
        hTfdtpTxCh->inUseBuffer = NULL;
        memcpy(hTfdtpTxCh->hostInfo.hostMACAddr, pTfdtpTxChOpenPrms->hostMacAddr, sizeof(hTfdtpTxCh->hostInfo.hostMACAddr));
        TFDTP_queueInit(&hTfdtpTxCh->readyBufferQ);

        LOCAL_getPortMAC(hTfdtp, hTfdtpTxCh->srcMAC);

        /* Increment the channel count */
        hTfdtp->numTxChannelsOpen++;

    }

    return hTfdtpTxCh;
}

int32_t TFDTP_closeRxChannel(tfdtp_rx_channel_handle_t hTfdtpRxCh)
{
    tfdtp_handle_t hTfdtp = hTfdtpRxCh->hTfdtp;
    int32_t retVal = -1;

    if (FALSE != hTfdtp->rxChannels[hTfdtpRxCh->index].isAllocated)
    {
        /* Decrement reference counter and return if still non-zero */
        hTfdtp->numRxChannelsOpen--;
        /* Find Corresponding channel from hTfdtpRxCh and mark it free. */
        hTfdtp->rxChannels[hTfdtpRxCh->index].isAllocated = FALSE;
        memset(&hTfdtp->rxChannels[hTfdtpRxCh->index], 0, sizeof(struct tfdtp_rx_channel));;
    }

    return retVal;
}

int32_t TFDTP_closeTxChannel(tfdtp_tx_channel_handle_t hTfdtpTxCh)
{
    tfdtp_handle_t hTfdtp = hTfdtpTxCh->hTfdtp;
    int32_t retVal = -1;

    if (FALSE != hTfdtp->txChannels[hTfdtpTxCh->index].isAllocated)
    {
        /* Decrement reference counter and return if still non-zero */
        hTfdtp->numTxChannelsOpen--;
        /* Find Corresponding channel from hTfdtpTxCh and mark it free. */
        hTfdtp->txChannels[hTfdtpTxCh->index].isAllocated = FALSE;
        memset(&hTfdtp->txChannels[hTfdtpTxCh->index], 0, sizeof(struct tfdtp_tx_channel));;
    }

    return retVal;
}

int32_t TFDTP_start(tfdtp_handle_t hTfdtp)
{
    int32_t retVal = -1;

    if (NULL != hTfdtp)
    {
        if (FALSE == hTfdtp->initFlag)
        {
            TFDTP2NSP_Config tfdtp2NspConfig;

            tfdtp2NspConfig.clientData = hTfdtp;
            tfdtp2NspConfig.txFreeTFDTPPacketQueue = &hTfdtp->txFreeTFDTPPacketQueue;

            /* Enable TFDTP receive */
            NDK2NSP_startTfdtpRx( hTfdtp->hNDK2NSP );
            /* Open new CPDMA Tx channel and enable TFDTP Transmit */
            hTfdtp->hTFDTP2NSP = TFDTP2NSP_open(&tfdtp2NspConfig);
            if (hTfdtp->hTFDTP2NSP == NULL) { return -1; }

            TFDTP2NSP_start(hTfdtp->hTFDTP2NSP);
            hTfdtp->initFlag =  TRUE;
        }

        retVal = 0;
    }

    return retVal;
}

int32_t TFDTP_submitRxBuf(tfdtp_rx_channel_handle_t hTfdtpRxCh, tfdtp_rx_buf_details_t buff_details)
{
    int32_t retVal = 0U;
    uint32_t i;

    if (buff_details->bufCount > TFDTP_MAX_APP_BUF_CNT)
    {
        retVal = -1;
    }
    else
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        hTfdtpRxCh->buffDetails = buff_details;
        /* Mark current and prev buffers as invalid */
        hTfdtpRxCh->inUseBufferIdx = 0;
        hTfdtpRxCh->pCurrAppBuff  = NULL;
        hTfdtpRxCh->pPrevAppBuff  = NULL;

        /* Make sure buffers are initialized correctly */
        for (i = 0U; i < hTfdtpRxCh->buffDetails->bufCount; i++)
        {
            hTfdtpRxCh->buffDetails->appBufArray[i].bufState = BUFF_EMPTY;
            hTfdtpRxCh->buffDetails->appBufArray[i].dataLength = 0U;
            hTfdtpRxCh->buffDetails->appBufArray[i].total_seq_num = 0U;
            hTfdtpRxCh->buffDetails->appBufArray[i].seq_num_cnt = 0U;
        }

        GMACSW_AL_globalInterruptEnable(key);
    }

    return retVal;
}

void TFDTP_submitTxBuf(tfdtp_handle_t hTfdtp, tfdtp_tx_buf_t **buffers, uint32_t numBufs)
{
    uint32_t i;
    for (i = 0; i < numBufs; i++)
    {
        tfdtp_tx_buf_t *pAppTxBuf = buffers[i];
        tfdtp_tx_channel_handle_t hTfdtpTxCh = pAppTxBuf->hTfdtpTxCh;

        /* Set frame id for this buffer */
        pAppTxBuf->buf_id = hTfdtpTxCh->frame_id++;
        pAppTxBuf->total_seq_num = (uint16_t)((pAppTxBuf->size+TFDTP_MAX_STREAM_PAYLOAD_SIZE-1)/TFDTP_MAX_STREAM_PAYLOAD_SIZE);
        pAppTxBuf->pRead = pAppTxBuf->pData;
        pAppTxBuf->remaining = pAppTxBuf->size;
        TFDTP_enqueue(&hTfdtpTxCh->readyBufferQ, (node_t *)pAppTxBuf);
    }
    TFDTP2NSP_kickTx(hTfdtp->hTFDTP2NSP);
}

void TFDTP_getStats(tfdtp_handle_t hTfdtp, struct tfdtp_stats *stats)
{
    if (NULL != hTfdtp)
    {
        *stats = hTfdtp->stats;
    }
}

void TFDTP_clearStats(tfdtp_handle_t hTfdtp)
{
    if (NULL != hTfdtp)
    {
        memset(&(hTfdtp->stats), 0, sizeof (struct tfdtp_stats));
    }
}

void TFDTP_getRcvrStats(tfdtp_rx_channel_handle_t hTfdtpRxCh, struct tfdtp_stats *stats)
{
    if (NULL != hTfdtpRxCh)
    {
        *stats = hTfdtpRxCh->stats;
    }
}

void TFDTP_clearRcvrStats(tfdtp_rx_channel_handle_t hTfdtpRxCh)
{
    if (NULL != hTfdtpRxCh)
    {
        memset(&(hTfdtpRxCh->stats), 0, sizeof (struct tfdtp_stats));
    }
}

uint32_t TFDTP_getRxLoad(tfdtp_handle_t hTfdtp)
{
    return (int)NDK2NSP_ioctl(hTfdtp->hNDK2NSP, NDK2NSP_IOCTL_GET_RXTASK_LOAD, 0, 0);
}

uint32_t TFDTP_getTxLoad(tfdtp_handle_t hTfdtp)
{
    Load_Stat stat;
    if (Load_getTaskLoad(hTfdtp->hTFDTP2NSP->txPacketTask, &stat))
    {
        return Load_calculateLoad(&stat);
    }
    return 0;
}

void TFDTP_fillTxQueue(tfdtp_handle_t hTfdtp, queue_t *pReadyQueue)
{
    uint32_t                    i;
    tfdtp_tx_buf_t             *pAppTxBuf;
    TFDTP_TxPacket              *pPacket;
    uint32_t                    packetSize;
    tfdtp_tx_channel_handle_t   txChannels[TFDTP_MAX_TX_CHANNELS];
    uint32_t                    activeChannels;

    if (hTfdtp->numTxChannelsOpen == 0) { return; }

    activeChannels = hTfdtp->numTxChannelsOpen;
    for (i = 0;  i < hTfdtp->numTxChannelsOpen; i++)
    {
        txChannels[i] = &hTfdtp->txChannels[i];
    }
    while (activeChannels > 0 && hTfdtp->txFreeTFDTPPacketQueue.count > 0)
    {
        for (i = 0; i < hTfdtp->numTxChannelsOpen; i++)
        {
            packetSize = TFDTP_MAX_STREAM_PAYLOAD_SIZE;
            tfdtp_tx_channel_handle_t hTfdtpTxCh = txChannels[i];

            if (NULL == hTfdtpTxCh) { continue; }

            if (!LOCAL_checkForData(hTfdtpTxCh))
            {
                /* Remove from the list if there's no more data */
                txChannels[i] = NULL;
                activeChannels--;
                continue;
            }

            pAppTxBuf = hTfdtpTxCh->inUseBuffer;
            if (pAppTxBuf->remaining <= packetSize)
            {
                packetSize = pAppTxBuf->remaining;
            }

            pPacket = (TFDTP_TxPacket *)TFDTP_dequeue(&hTfdtp->txFreeTFDTPPacketQueue);
            if (NULL == pPacket)
            {
                tfdtp2NspStats.txFreeTFDTPPacketQueueUnderflow++;
                break;
            }

            LOCAL_fillTxPacket(hTfdtpTxCh, pPacket, packetSize, pAppTxBuf);

            /* Add callback details to only last packet in the application
             * buffer */
            if (pAppTxBuf->remaining == 0)
            {
                pPacket->notifyFree = true;
                pPacket->txCbFxn = hTfdtpTxCh->txCbFxn;
                pPacket->txCbData = hTfdtpTxCh->txCbData;
                pPacket->pAppTxBuf  = pAppTxBuf;
                hTfdtpTxCh->inUseBuffer = NULL;
            }

            TFDTP_enqueue(pReadyQueue, (node_t *)pPacket);

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
            tfdtp2NspStats.txReadyTFDTPPacketEnqueue++;
#endif
        }
    }
}

void TFDTP_waitPendingRxPackets(tfdtp_handle_t hTfdtp)
{
    TFDTP_RxPacket *pTFDTPPacket;

    LOCAL_waitForEdmaTransfer(hTfdtp);

    /* DMA transfer is now complete so packets can be returned to the free list */
    pTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(&hTfdtp->pendingDMAPacketQueue);
    while (pTFDTPPacket != NULL)
    {
       TFDTP_enqueue(hTfdtp->rxFreeTFDTPPacketQueue, (node_t *)pTFDTPPacket);
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
       ndk2NspStats.rxFreeTFDTPPBMPacketEnqueue++;
#endif
       pTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(&hTfdtp->pendingDMAPacketQueue);
    }
}

void TFDTP_processRxPackets(tfdtp_handle_t hTfdtp, queue_t *pReadyQueue)
{
    TFDTP_RxPacket      *pTFDTPPacket;
    queue_t             dmaTransferQueue;
    uint32_t            packetCount = 0;

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
    static uint32_t procCount = 0;
    uint32_t time1;
    tfdtp2NspStats.rxStats.rawNotificationCount++;
#endif

    TFDTP_queueInit(&dmaTransferQueue);
    pTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(pReadyQueue);

    /* Go through each received packet and process it */
    while (pTFDTPPacket != NULL)
    {
        /* We know TFDTP packet will always come through Eth interface and not thru
         * PPPoE so add PKT_PREPAD to data buffer */
        uint8_t                     *pBuffer = PBM_getDataBuffer(pTFDTPPacket->hPBMPacket) + PKT_PREPAD;
        ether_frame_t               *framePtr = (ether_frame_t *)((void *)pBuffer);
        tfdtp_stream_packet_t       *pTfdtpBlockPck = (tfdtp_stream_packet_t *)framePtr->payload;
        tfdtp_header_t              *pTfdtpHeader = &pTfdtpBlockPck->tfdtp_bhdr.tfdtp_hdr;
        tfdtp_rx_channel_handle_t   hTfdtpRxCh = NULL;
        uint32_t                    origPacketCnt = hTfdtp->stats.packetCount;
        uint8_t                     *destPtr = NULL;
        struct tfdtp_rx_buf           *pInUseAppBuff = NULL;
        uint32_t                    newFrameFlag = 0U, inUseBuffDispatchFlag = FALSE;
        ErrorStatus_e               errorCode;


        /* Variable to store TFDTP header fields. Make sure data type in header matches */
        uint32_t                    payloadSize;
        uint16_t                    pckFrameId;

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
        tfdtp2NspStats.rxReadyTFDTPPacketDequeue++;
        ndk2NspStats.rxReadyTFDTPPacketDequeue++;
        time1 = TIMER_READ();
#endif
        /* Cache invalidate for TFDTP header is already done by LOCAL_checkTfdtpPacket()
         * during packet seggregation. We don't need to do it again here */

        packetCount++;

        hTfdtpRxCh = LOCAL_findRxChannel(hTfdtp, pTfdtpHeader->channel_id);

        if ( NULL != hTfdtpRxCh )
        {
            uint32_t validBufFlag = TRUE;

            pckFrameId = pTfdtpHeader->frame_id;


            if ( NULL != hTfdtpRxCh->pCurrAppBuff )
            {
                pInUseAppBuff = hTfdtpRxCh->pCurrAppBuff;
                if ( pckFrameId != pInUseAppBuff->frame_id )
                {
                    if (hTfdtpRxCh->buffDetails->bufCount > 1U)
                    {
                        /*
                        * Support out of order packets only if bufCount is more than one
                        * else application needs to take care of packet drop/out of order
                        * packets
                        */
                        if ( NULL != hTfdtpRxCh->pPrevAppBuff )
                        {
                            if ( pckFrameId == hTfdtpRxCh->pPrevAppBuff->frame_id )
                            {
                                /* Out of order packet - for previous frame */
                                pInUseAppBuff = hTfdtpRxCh->pPrevAppBuff;

                                if (TRUE == LOCAL_checkForSOF(pTfdtpHeader->flags) )
                                {
                                    /* If previous frame is retransmitted then start filling fresh */
                                    pInUseAppBuff->dataLength = 0U;
                                    pInUseAppBuff->seq_num_cnt = 0U;
                                }
                            }
                            else
                            {
                                LOCAL_dispatchCurrentBuffer(hTfdtpRxCh, hTfdtpRxCh->pPrevAppBuff, BUFF_ERR_PACKET_DROP);

                                /* Make next buffer as active buffer */
                                hTfdtpRxCh->hTfdtp->stats.errorCnt++;
                                hTfdtpRxCh->hTfdtp->stats.outOfSequenceError++;
                                hTfdtpRxCh->stats.errorCnt++;
                                hTfdtpRxCh->stats.outOfSequenceError++;

                                hTfdtpRxCh->pPrevAppBuff = hTfdtpRxCh->pCurrAppBuff;
                                newFrameFlag = 1U;
                            }
                        }
                        else
                        {
                            hTfdtpRxCh->pPrevAppBuff = hTfdtpRxCh->pCurrAppBuff;
                            newFrameFlag = 1U;
                        }
                    }
                    else
                    {
                        /*
                         * Discard current frame as app has given us only one frame
                         * for which packet drop cant be handled
                         */
                        hTfdtpRxCh->pCurrAppBuff->bufState = BUFF_EMPTY;

                        hTfdtpRxCh->hTfdtp->stats.errorCnt++;
                        hTfdtpRxCh->hTfdtp->stats.outOfSequenceError++;
                        hTfdtpRxCh->stats.errorCnt++;
                        hTfdtpRxCh->stats.outOfSequenceError++;
                        newFrameFlag = 1U;
                    }
                }
            }
            else
            {
                /* This is first packet for frame, allocate new buffer */
                newFrameFlag = 1U;
            }

            if (1U == newFrameFlag)
            {
                /* Allocate new buffer */
                if (LOCAL_findEmptyBuffer(hTfdtpRxCh) != false)
                {
                    pInUseAppBuff = hTfdtpRxCh->pCurrAppBuff;
                    pInUseAppBuff->bufState = BUFF_PARTIAL;
                    pInUseAppBuff->frame_id =  pckFrameId;
                    pInUseAppBuff->total_seq_num = pTfdtpHeader->total_seq_num;
                }
                else
                {
                    validBufFlag = FALSE;
                    hTfdtp->stats.errorCnt++;
                    hTfdtp->stats.noBuffersAvailable++;
                    hTfdtpRxCh->stats.errorCnt++;
                    hTfdtpRxCh->stats.noBuffersAvailable++;
                }
            }

            if (TRUE == validBufFlag)
            {
                pInUseAppBuff->seq_num_cnt++;
                payloadSize = pTfdtpHeader->length;

                if ((payloadSize == 0) || (payloadSize > TFDTP_MAX_STREAM_PAYLOAD_SIZE))
                {
                    inUseBuffDispatchFlag = TRUE;
                    errorCode = BUFF_ERR_PACKET_SIZE;
                    hTfdtp->stats.errorCnt++;
                    hTfdtp->stats.invalidPacketSizeError++;
                }
                else
                {
                    /* Add this packet to EDMA queue which will be triggered at the end of loop */
                    destPtr = ( pInUseAppBuff->bufPtr + pTfdtpHeader->frame_offset);

                    /* If there is no more space to copy, drop the packet */
                    if ((payloadSize + pInUseAppBuff->dataLength) > hTfdtpRxCh->buffDetails->bufSize)
                    {
                        inUseBuffDispatchFlag = TRUE;
                        errorCode = BUFF_ERR_SIZE;

                        hTfdtp->stats.errorCnt++;
                        hTfdtp->stats.insufficientSizeError++;
                        hTfdtpRxCh->stats.errorCnt++;
                        hTfdtpRxCh->stats.insufficientSizeError++;
                    }
                    else if (pInUseAppBuff->seq_num_cnt > pInUseAppBuff->total_seq_num)
                    {
                        inUseBuffDispatchFlag = TRUE;
                        errorCode = BUFF_ERR_SIZE;

                        hTfdtp->stats.errorCnt++;
                        hTfdtpRxCh->stats.errorCnt++;
                        hTfdtpRxCh->stats.invalidBufferSizeError++;
                    }
                    else
                    {
                        LOCAL_addToEdmaTransferQueue(&dmaTransferQueue, pTFDTPPacket, destPtr, payloadSize);
                        pTFDTPPacket = NULL;
                        pInUseAppBuff->dataLength += payloadSize;
                        hTfdtp->stats.packetCount++;
                        hTfdtpRxCh->stats.packetCount++;
                    }

                    if ( pInUseAppBuff->total_seq_num == pInUseAppBuff->seq_num_cnt)
                    {
                        LOCAL_startEdmaTransfer(hTfdtp, &dmaTransferQueue);
                        /* Call receive buffer ready callBack */
                        pInUseAppBuff->bufState = BUFF_FULL;
                        inUseBuffDispatchFlag   = TRUE;
                        errorCode = BUFF_NOERROR;

                        #if defined(TFDTP_INSTRUMENTATION_ENABLED)
                        tfdtp2NspStats.procStats.fullFrameCnt[hTfdtpRxCh->index]++;
                        #endif
                    }

                    if ( TRUE == inUseBuffDispatchFlag )
                    {
                        if ((NULL != hTfdtpRxCh->pPrevAppBuff) && (pInUseAppBuff != hTfdtpRxCh->pPrevAppBuff ))
                        {
                            /* Previous frame is partially received while current is full  */
                            LOCAL_dispatchCurrentBuffer(hTfdtpRxCh, hTfdtpRxCh->pPrevAppBuff, BUFF_ERR_PACKET_DROP);;
                            hTfdtpRxCh->pPrevAppBuff = NULL;
                            /* Make next buffer as active buffer */
                            hTfdtpRxCh->hTfdtp->stats.errorCnt++;
                            hTfdtpRxCh->hTfdtp->stats.outOfSequenceError++;
                            hTfdtpRxCh->stats.errorCnt++;
                            hTfdtpRxCh->stats.outOfSequenceError++;
                        }

                        LOCAL_dispatchCurrentBuffer(hTfdtpRxCh, pInUseAppBuff, errorCode);
                        if (pInUseAppBuff == hTfdtpRxCh->pCurrAppBuff )
                        {
                            hTfdtpRxCh->pCurrAppBuff = NULL;
                        }
                    }

                }
            }
        }
        else
        {
            hTfdtp->stats.errorCnt++;
        }

        /* Count ignored packets */
        if (hTfdtp->stats.packetCount == origPacketCnt)
        {
            hTfdtp->stats.ignoredPacketCnt++;
            if (hTfdtpRxCh != NULL)
            {
                hTfdtpRxCh->stats.ignoredPacketCnt++;
            }
        }

        if (pTFDTPPacket != NULL)
        {
            TFDTP_enqueue(hTfdtp->rxFreeTFDTPPacketQueue, (node_t *)pTFDTPPacket);
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreeTFDTPPBMPacketEnqueue++;
#endif
        }

        pTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(pReadyQueue);

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
        tfdtp2NspStats.rxFreeTFDTPPacketEnqueue++;
        {
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);

            tfdtp2NspStats.procStats.lastCycleCnt = timeDiff;
            tfdtp2NspStats.procStats.totalCycleCnt += timeDiff;
        }
#endif
    }

    LOCAL_startEdmaTransfer(hTfdtp, &dmaTransferQueue);

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
    tfdtp2NspStats.procStats.edmaPacketsPerProcessingCall[procCount] =
                                                    dmaTransferQueue.count;
    tfdtp2NspStats.procStats.packetsPerProcessingCall[procCount] = packetCount;
    tfdtp2NspStats.procStats.totalPacketCount += packetCount;
    if (packetCount > tfdtp2NspStats.procStats.packetsPerProcessingCallMax)
    {
       tfdtp2NspStats.procStats.packetsPerProcessingCallMax = packetCount;
    }
    procCount = (procCount + 1) & 0xFF;
#endif

}

static void inline TFDTP_print(char *prnStr,...)
{
    static char str[100];
    if ( (LOCAL_tfdtpRef != NULL) && (NULL != LOCAL_tfdtpRef->printFxnCb) )
    {
        /* Function is non- reentrant */
        snprintf (str, 100U, prnStr);
        (*LOCAL_tfdtpRef->printFxnCb)(str);
    }
    else
    {
#if defined (DEBUG)
        printf(prnStr);
#endif
    }
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/
static inline int32_t Local_checkTxChParams(TFDTP_TxChOpenPrm_t *pTfdtpTxChOpenPrms)
{
    int32_t status = 0;

    /* Check Transmit channel callBack */
    if (NULL == pTfdtpTxChOpenPrms->tx_cb_fxn)
    {
        TFDTP_print(" Channel Transmit Callback function not set \n");
        status = -1;
    }

    if (0U == pTfdtpTxChOpenPrms->hostIpAddr)
    {
        TFDTP_print(" Destination IP address should be set \n");
        status = -1;
    }

    if ( 1U == LOCAL_checkEmpty(pTfdtpTxChOpenPrms->hostMacAddr, sizeof(uint8_t)*6U) )
    {
        TFDTP_print(" Destination MAC address should be set \n");
        status = -1;
    }

    return status;
}

static inline tfdtp_rx_channel_handle_t LOCAL_findRxChannel(tfdtp_handle_t hTfdtp, uint16_t channelId)
{
    uint32_t i;

    for (i = 0; i < (uint32_t)TFDTP_MAX_RX_CHANNELS; i++)
    {
       if ((hTfdtp->rxChannels[i].isAllocated != FALSE))
       {
           if ( channelId == hTfdtp->rxChannels[i].channelId )
           {
               return (&hTfdtp->rxChannels[i]);
           }
       }
    }

    return NULL;
}

static bool LOCAL_findEmptyBuffer(tfdtp_rx_channel_handle_t hTfdtpRxCh)
{
    tfdtp_rx_buf_details_t        bufD = hTfdtpRxCh->buffDetails;

    uint32_t                    numBufsToCheck = bufD->bufCount;
    bool                        ret = (bool)true;

    while (bufD->appBufArray[hTfdtpRxCh->inUseBufferIdx].bufState != BUFF_EMPTY)
    {
        hTfdtpRxCh->inUseBufferIdx++;

        if (hTfdtpRxCh->inUseBufferIdx >= bufD->bufCount)
        {
            hTfdtpRxCh->inUseBufferIdx = 0;
        }

        numBufsToCheck--;

        if (0 == numBufsToCheck)
        {
            ret = (bool)false;
            break;
        }
    }

    if (0 != numBufsToCheck)
    {
        hTfdtpRxCh->pCurrAppBuff = &bufD->appBufArray[hTfdtpRxCh->inUseBufferIdx];
        /* Clear contents when application has returned buffer */
        hTfdtpRxCh->pCurrAppBuff->dataLength = 0U;
        hTfdtpRxCh->pCurrAppBuff->seq_num_cnt = 0U;
    }

    return ret;
}

static void LOCAL_dispatchCurrentBuffer(tfdtp_rx_channel_handle_t hTfdtpRxCh, tfdtp_rx_buf_handle_t appBuffh, uint32_t errorStatus)
{

    if ( (BUFF_PARTIAL == appBuffh->bufState) ||
         (BUFF_FULL == appBuffh->bufState) )
    {
        appBuffh->error = errorStatus;

        TFDTP_waitPendingRxPackets(hTfdtpRxCh->hTfdtp);

        /* Call application frame reception notify callback  */
        hTfdtpRxCh->rcv_cb_fxn(appBuffh, hTfdtpRxCh->rcv_cb_data, hTfdtpRxCh->index);

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
 *  - The TFDTP parser may have decided to ignore certain packets (for example waiting for Frame SOF, or ignoring control data packets). In this case,
 *    the LINK field has to be updated as we form the link list, hence there will be an upper bound of 3N+6 writes per DMA list
 */
#if defined(USE_DMA_INTERRUPTS)
static void LOCAL_edmaTransferCompleteCb(uint32_t tcc, EDMA3_RM_TccStatus status, void *appData)
{
    tfdtp_handle_t hTfdtp = (tfdtp_handle_t)appData;
    Semaphore_post(hTfdtp->edmaSem);
}
#endif

static void LOCAL_waitForEdmaTransfer(tfdtp_handle_t hTfdtp)
{
    TFDTP_RxPacket *pLastPacket = (TFDTP_RxPacket *)hTfdtp->pendingDMAPacketQueue.pTail;

    if (pLastPacket != NULL)
    {
        /* Wait for previous transfer to finish */
#if defined(USE_DMA_INTERRUPTS)
        Semaphore_pend(hTfdtp->edmaSem, BIOS_WAIT_FOREVER);
#else
        EDMA3_DRV_waitAndClearTcc(hTfdtp->edma, hTfdtp->edmaTCC);
#endif
        /* Reset options as next link list terminator will be a different PaRAM set */
        pLastPacket->pEdmaParams->OPT = 0;
    }
}

static void LOCAL_startEdmaTransfer(tfdtp_handle_t hTfdtp, queue_t *pTransferQueue)
{
    if (pTransferQueue->count != 0)
    {
        TFDTP_RxPacket *pFirstPacket = (TFDTP_RxPacket *)pTransferQueue->pHead;
        TFDTP_RxPacket *pLastPacket = (TFDTP_RxPacket *)pTransferQueue->pTail;
        EDMA3_DRV_ParamentryRegs *dummyParam = hTfdtp->pEdmaParams;

        TFDTP_waitPendingRxPackets(hTfdtp);

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
        pLastPacket->pEdmaParams->OPT = ((hTfdtp->edmaTCC << (uint32_t)OPT_TCC_SHIFT) & (uint32_t)OPT_TCC_MASK) |
                          ((uint32_t)1U << (uint32_t)OPT_TCINTEN_SHIFT) | ((uint32_t)1U << (uint32_t)OPT_STATIC_SHIFT);

        /* Kick-off the transfer as QDMA trigger word is ccnt */
        dummyParam->CCNT = 1U;

        /* Keep a record of the pending transfers;
         * this is just a shallow copy as the nodes are already linked together */
        TFDTP_queueCopy(&hTfdtp->pendingDMAPacketQueue, pTransferQueue);
        TFDTP_queueInit(pTransferQueue);
    }
}

static void LOCAL_addToEdmaTransferQueue(queue_t *pTransferQueue, TFDTP_RxPacket *pTFDTPPacket, uint8_t const *pDst, uint32_t size)
{
    TFDTP_RxPacket *pPrevPacket = (TFDTP_RxPacket *)pTransferQueue->pTail;
    EDMA3_DRV_ParamentryRegs *packetParam = pTFDTPPacket->pEdmaParams;

    TFDTP_enqueue(pTransferQueue, (node_t *)pTFDTPPacket);

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

EDMA3_DRV_Result LOCAL_setEdmaParam(tfdtp_handle_t hTfdtp, TFDTP_RxPacket *pPacket)
{
    EDMA3_DRV_Result result = (EDMA3_DRV_Result)EDMA3_DRV_SOK;
    uint32_t paramAddr = 0;
    EDMA3_DRV_ParamentryRegs *pEdmaParams;
    uint32_t chId = EDMA3_DRV_LINK_CHANNEL;
    /* We know TFDTP packet will always come through Eth interface and not thru
     * PPPoE so add PKT_PREPAD to data buffer */
     uint8_t             *pBuffer = PBM_getDataBuffer(pPacket->hPBMPacket) + PKT_PREPAD;
    /* Double cast to avoid MISRA-C:2004 11.4 */
    ether_frame_t *frame = (ether_frame_t *)((void *)pBuffer);
    tfdtp_stream_packet_t *tfdtpsp = (tfdtp_stream_packet_t *)frame->payload;

    result = EDMA3_DRV_requestChannel(hTfdtp->edma, &chId, NULL, (EDMA3_RM_EventQueue)0, NULL, NULL);
    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        TFDTP_print("failed requesting EDMA channel %d\n", result);
        return result;
    }

    result = EDMA3_DRV_getPaRAMPhyAddr(hTfdtp->edma, chId, &paramAddr);
    if ((result != (EDMA3_DRV_Result)EDMA3_DRV_SOK) || (paramAddr == 0))
    {
        TFDTP_print("failed requesting PaRAM address %d\n", result);
        EDMA3_DRV_freeChannel(hTfdtp->edma, chId);
        return result;
    }

    pEdmaParams = (EDMA3_DRV_ParamentryRegs *)paramAddr;

    /* We minimize the amount of PaRAM set updates needed after the channels get started by filling fields
     * that will remain constant after setup.
     */
    pEdmaParams->SRC = (uint32_t)tfdtpsp->payload;
    pEdmaParams->CCNT = 1U;

    pPacket->pEdmaParams = pEdmaParams;
    pPacket->edmaChId = chId;

    return result;
}

static EDMA3_DRV_Result LOCAL_edmaInit(tfdtp_handle_t hTfdtp)
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
        hTfdtp->edmaSem = Semaphore_create(0, &semParams, NULL);
        if (hTfdtp->edmaSem == NULL) return -1;
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
        TFDTP_print("failed edma3init %d\n", result);
        return result;
    }

#if defined(USE_DMA_INTERRUPTS)
    result = EDMA3_DRV_requestChannel(edma, &chId, &tcc, (EDMA3_RM_EventQueue)0, &LOCAL_edmaTransferCompleteCb, (void *)hTfdtp);
#else
    result = EDMA3_DRV_requestChannel(edma, &chId, &tcc, (EDMA3_RM_EventQueue)0, NULL, NULL);
#endif
    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        TFDTP_print("failed requesting EDMA channel %d\n", result);
        edma3deinit(0, edma);
        return result;
    }

    result = EDMA3_DRV_getPaRAMPhyAddr(edma, chId, &paramAddr);
    if ((result != (EDMA3_DRV_Result)EDMA3_DRV_SOK) || (0 == paramAddr))
    {
        TFDTP_print("failed requesting PaRAM address %d\n", result);
        EDMA3_DRV_freeChannel(edma, chId);
        edma3deinit(0, edma);
        return result;
    }

    hTfdtp->edma = edma;
    hTfdtp->edmaChId = chId;
    hTfdtp->edmaTCC = tcc;
    hTfdtp->pEdmaParams = (EDMA3_DRV_ParamentryRegs *)paramAddr;

    TFDTP_queueInit(&hTfdtp->pendingDMAPacketQueue);
    return result;
}

static EDMA3_DRV_Result LOCAL_edmaDeInit(tfdtp_handle_t hTfdtp, NDK2NSP_Handle hNDK2NSP)
{
    uint32_t i;
    EDMA3_DRV_Result result = (EDMA3_DRV_Result)EDMA3_DRV_SOK;
    TFDTP_RxPacket *pTFDTPPacket;

    if (hTfdtp->edma == NULL) { return result; }

    result = EDMA3_DRV_freeChannel(hTfdtp->edma, hTfdtp->edmaChId);
    if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
    {
        TFDTP_print("failed freeing EDMA channel %d\n", result);
    }

    for (i = 0U; i < (uint32_t)NDK_RX_PACKETS; i++)
    {
        pTFDTPPacket = (TFDTP_RxPacket *) TFDTP_dequeue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue);
        if (pTFDTPPacket->pEdmaParams != NULL)
        {
            result = EDMA3_DRV_freeChannel(hTfdtp->edma, pTFDTPPacket->edmaChId);
            if (result != (EDMA3_DRV_Result)EDMA3_DRV_SOK)
            {
                TFDTP_print("failed freeing edma PaRAM set %d\n", result);
            }
        }
    }

    result = edma3deinit(0, hTfdtp->edma);
    hTfdtp->edma = NULL;

#if defined(USE_DMA_INTERRUPTS)
    Semaphore_delete(&hTfdtp->edmaSem);
#endif

    return result;
}

static void LOCAL_getPortMAC(tfdtp_handle_t hTfdtp, uint8_t *pMACData)
{

#ifndef TFDTP_USE_MAC_SPOOF
    mmCopy (pMACData, &hTfdtp->hNDK2NSP->bMacAddr[0][0], (uint)6U);
#else
    pMACData[0] = 0x00U;
    pMACData[1] = 0x01U;
    pMACData[2] = 0x02U;
    pMACData[3] = 0x03U;
    pMACData[4] = 0x04U;
    pMACData[5] = 0x05U;
#endif
}

static void LOCAL_fillTxPacket(tfdtp_tx_channel_handle_t hTfdtpTxCh, TFDTP_TxPacket *pPacket, uint16_t packetSize, tfdtp_tx_buf_t *pBuffer)
{
    ether_frame_t *frame = (ether_frame_t *)((void *)pPacket->pHeader);
    tfdtp_stream_packet_t *tfdtpsp = (tfdtp_stream_packet_t *)frame->payload;
    ip_header_t    *pIpHdr;
    udp_header_t   *pUdpHdr;
    tfdtp_header_t *pTfdtpHdr;

    /* Set Ethernet header contents */
    memcpy(frame->header.srcMac, hTfdtpTxCh->srcMAC, sizeof(frame->header.srcMac));
    memcpy(frame->header.dstMac, hTfdtpTxCh->hostInfo.hostMACAddr, sizeof(frame->header.dstMac));
    frame->header.etherType = htons(ETHERTYPE_IPV4);

    /* Set TFDTP block header contents */
    /* Get the IP header pointer & set contents of IP header */
    pIpHdr = &tfdtpsp->tfdtp_bhdr.ip_hdr;
    pIpHdr->VerLen   = 0x45;
    uint16_t hlen = (pIpHdr->VerLen & 0xF) * 4;
    pIpHdr->Tos = SOCK_TOS_DEFAULT;
    pIpHdr->TotalLen = HNC16( packetSize + hlen + TFDTP_HDR_SIZE + UDP_HDR_SIZE);
    pIpHdr->Id = HNC16( IP_HDR_INDEX );
    pIpHdr->FlagOff = HNC16( IP_DF );
    pIpHdr->Ttl = SOCK_TTL_DEFAULT;
    pIpHdr->Protocol = IPPROTO_UDP;
    pIpHdr->IPSrc = htonl(hTfdtpTxCh->hTfdtp->myIpAddr);
    pIpHdr->IPDst = htonl(hTfdtpTxCh->hostInfo.hostIpAddr);

    /* Perform Checksum */
    IPChecksum( (IPHDR *)pIpHdr );

    /* Get the UDP header pointer & set contents of UDP header */
    pUdpHdr   = &tfdtpsp->tfdtp_bhdr.udp_hdr;
    pUdpHdr->SrcPort = HNC16(hTfdtpTxCh->hTfdtp->rxUdpPort);
    pUdpHdr->DstPort = HNC16(hTfdtpTxCh->hostInfo.hostUdpPort);
    pUdpHdr->Length  = HNC16(UDPHDR_SIZE + TFDTP_HDR_SIZE + (uint)packetSize);
#if defined (USE_UDP_CHECKSUM)
    /* Checksum Header */
    upseudoIPHdr.IPSrc    = pIpHdr->IPSrc;
    upseudoIPHdr.IPDst    = pIpHdr->IPDst;
    upseudoIPHdr.Null     = 0;
    upseudoIPHdr.Protocol = 17;
    LOCAL_myUdpChecksum((UDPHDR *)pUdpHdr, pBuffer->pRead, packetSize);
#else
    pUdpHdr->UDPChecksum = 0x0;
#endif

    /* Get the TFDTP header pointer & set contents of TFDTP header */
    pTfdtpHdr   = &tfdtpsp->tfdtp_bhdr.tfdtp_hdr;
    pTfdtpHdr->flags        = TFDTP_VER;
    pTfdtpHdr->channel_id   = hTfdtpTxCh->channelId;
    pTfdtpHdr->frame_id     = pBuffer->buf_id;
    pTfdtpHdr->seq_num      = hTfdtpTxCh->prevSeqNum++;
    pTfdtpHdr->total_seq_num  = pBuffer->total_seq_num;
    pTfdtpHdr->frame_offset = (pBuffer->size - pBuffer->remaining);
    pTfdtpHdr->length = packetSize;
    if (0U == pTfdtpHdr->frame_offset)
    {
        pTfdtpHdr->flags |= TFDTP_SOF;
    }

    pPacket->dataPtr = pBuffer->pRead;
    pPacket->bufferSize = packetSize;
    pBuffer->pRead += packetSize;
    pBuffer->remaining -= packetSize;
    if (0U == pBuffer->remaining)
    {
        pTfdtpHdr->flags |= TFDTP_EOF;
    }

    /* Invalidate Eth Frame Header packet header as it is updated  here */
    Cache_wb((Ptr)pPacket->pHeader, TFDTP_PACKET_HEADER_SIZE, (Bits16)Cache_Type_ALLD, (Bool)1U);


    /* The headers are assumed to be in a write-through region */
    if (pBuffer->needsFlushing)
    {
        /*TODO: consider not waiting for the writeback here - wait later using Cache_wait */
        Cache_wbInv((Ptr)pPacket->dataPtr, (SizeT)pPacket->bufferSize, (Bits16)Cache_Type_ALLD, (Bool)1U);
    }
}

static bool LOCAL_checkForData(tfdtp_tx_channel_handle_t hTfdtpTxCh)
{
    if (NULL == hTfdtpTxCh->inUseBuffer)
    {
        hTfdtpTxCh->inUseBuffer = (tfdtp_tx_buf_t *)TFDTP_dequeue(&hTfdtpTxCh->readyBufferQ);
        /* Reset prevSeqNum counter for new */
        hTfdtpTxCh->prevSeqNum = 0U;
    }

    return ( NULL != hTfdtpTxCh->inUseBuffer );
}

static inline uint32_t LOCAL_checkEmpty(const uint8_t * buf, uint32_t size)
{
    uint32_t i;
    uint32_t flag = (uint32_t)TRUE;
    for(i = 0U; i < size; i++)
    {
        if(buf[i] != 0)
        {
            flag = (uint32_t) FALSE;
        }
    }

    return flag;
}

static inline bool LOCAL_checkForSOF(uint32_t flags)
{
    return (bool)( flags & (uint32_t)TFDTP_SOF );
}

#if 0
/*-------------------------------------------------------------------- */
/* void UdpChecksum( UDPHDR *pbHdr ) */
/* Checksums the UDP header */
/*-------------------------------------------------------------------- */
static void LOCAL_myUdpChecksum( UDPHDR *pUdpHdr, uint8_t *payload, uint16_t packetSize )
{
    uint16_t     tmp1;
    uint16_t  *pw;
    uint32_t  TSum;
    PSEUDO   upseudoIPHdr;

    /* Get header size in bytes */
    tmp1 = (UDPHDR_SIZE + TFDTP_HDR_SIZE);

    /* Checksum field is NULL in checksum calculations */
    pUdpHdr->UDPChecksum = 0;

    /* Checksum the header */
    pw = (uint16_t *)pUdpHdr;
    TSum = 0;
    for( ; tmp1 > 1; tmp1 -= 2 )
        TSum += (uint32_t)*pw++;
    if( tmp1 )
        TSum += (uint32_t)(*pw & 0x00FF);

    /* Get packet size in bytes */
    tmp1 = packetSize;
    pw = (uint16_t*)payload;
    for ( ; tmp1 > 1; tmp1 -= 2)
        TSum += (uint32_t)*pw++;
    if( tmp1 )
        TSum += (uint32_t)(*pw & 0x00FF);

    /* Checksum the pseudo header */
    pw = (uint16_t *)&upseudoIPHdr;
    for( tmp1=0; tmp1 < 6; tmp1++ )
        TSum += (uint32_t)*pw++;

    TSum = (TSum&0xFFFF) + (TSum>>16);
    TSum = (TSum&0xFFFF) + (TSum>>16);

    /* Special case the 0xFFFF checksum - don't use a checksum */
    /* value of 0x0000 */
    if( TSum != 0xFFFF )
        TSum = ~TSum;

    /* Note checksum is Net/Host byte order independent */
    pUdpHdr->UDPChecksum = (uint16_t)TSum;
}

static int32_t LOCAL_findFrameBuffer(tfdtp_rx_channel_handle_t hTfdtpRxCh, uint16_t pckFrameId)
{
    uint16_t i;
    int32_t bufIndex = -1;
    uint32_t bufCount = hTfdtpRxCh->buffDetails->bufCount;
    tfdtp_rx_buf_handle_t appBufArray = &hTfdtpRxCh->buffDetails->appBufArray[0U];

    for(i = 0; i < bufCount; i++)
    {
        if( (pckFrameId == appBufArray[i].frame_id) && (BUFF_EMPTY != appBufArray[i].bufState) )
        {
            bufIndex = i;
            break;
        }
    }

    return bufIndex;
}

static bool LOCAL_checkForEoF(uint32_t flags)
{
    return (bool)( flags & (uint32_t)TFDTP_EOF );
}

#endif

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

