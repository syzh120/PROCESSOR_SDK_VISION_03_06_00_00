/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
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
 */

/*!
 *   \file  interrupts.c
 *
 *   \brief
 *          GMAC_SW Interrupt Service Routines
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* OS/Posix headers */

/* Project dependency headers */
#if defined(USE_CSLR)
#include "cslr.h"
#include "cslr_gmacsw.h"
#else
#include "soc.h"
#include "gmac_sw.h"
#endif

#include "private/gmacsw_.h"
#include "cpdma.h"
#include "private/cpdma_.h"
#include "stats.h"
#include "private/stats_.h"
#include "cpts.h"
#include "private/cpts_.h"

/* This module's header */


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_serviceRxChannel(CPDMA_State *pCPDMAState, uint32_t channelNum, uint32_t threshInt);
static void LOCAL_serviceTxChannel(CPDMA_State *pCPDMAState, uint32_t channelNum);

void HwIntRx(void);
void HwIntTx(void);
void HwIntRxThresh(void);
void HwIntMisc(void);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief
 *      GMAC_SW RX_PULSE ISR.
 *
 *  \retval
 *      void
 */
void HwIntRx(void)
{
    CPDMA_State     *pCPDMAState = NULL;
    uint32_t        intFlags = 0U;
    uint32_t        channelNum = 0U;

#if defined(USE_CSLR)
    /* Read the Rx interrupt cause from WR_C0_RX_STAT */
    intFlags        = (uint32_t)(GMACSW_REGS->WR.WR_C0_RX_STAT & 0xFFU);
#else
#endif

    pCPDMAState = CPDMA_open(NULL);

    if (pCPDMAState == NULL)
    {
        /* If a crash occurs while interrupts were pending and the core is restored (no system wide reset)
         * we can end up here since the GMAC ISRs are hooked at init before the driver has a chance to reset the HW.
         * TODO: Consider hooking the ISRs as part of the driver initialization instead of SYS/BIOS init
         */
        while (0U != intFlags)
        {
            uint32_t channelMask = (uint32_t)((uint32_t)0x00000001U << (uint32_t)channelNum);

            uint32_t cp = GMACSW_REGS->STATERAM.RX_CP[channelNum];
            GMACSW_REGS->STATERAM.RX_CP[channelNum] = cp;
            /* Clear the channel flag for the channel just handled */
            intFlags &= ~channelMask;
            channelNum++;
        }
    }
    else
    {
        /* Handle both Rx threshold and paced Rx interrupts */
#if defined(USE_CSLR)
        uint32_t threshIntFlags = (uint32_t)(GMACSW_REGS->WR.WR_C0_RX_THRESH_STAT & 0xFFU);
#else
#endif
        intFlags |= threshIntFlags;

        /* Look for receive interrupts from across all CPDMA Rx Channels */
        while (0U != intFlags)
        {
            uint32_t channelMask = (uint32_t)((uint32_t)0x00000001U << (uint32_t)channelNum);

            if ( (uint32_t)0U != (uint32_t)(intFlags & channelMask))
            {
                LOCAL_serviceRxChannel(pCPDMAState, channelNum, (uint32_t)(threshIntFlags & channelMask));
            }

            /* Clear the channel flag for the channel just handled */
            intFlags &= ~channelMask;
            channelNum++;
        }

        /* Decrement the reference count on the CPDMA_State object */
        CPDMA_close(pCPDMAState);

        if (0U != threshIntFlags)
        {
#if defined(USE_CSLR)
            /* All outstanding RX_THRESH interrupts were handled */
            GMACSW_REGS->CPDMA.CPDMA_EOI_VECTOR = 0x0U;
#else
#endif
        }
    }

    /* Write the EOI register */
#if defined(USE_CSLR)
    GMACSW_REGS->CPDMA.CPDMA_EOI_VECTOR = 0x1U;
#else
#endif
}

/*!
 *  \brief
 *     GMAC_SW TX_PULSE ISR.
 *
 *  \details
 *     This interrupt is triggered by the hardware when a packet has completed
 *     being sent and the buffer descriptors (the linked chain of descriptors
 *     starting with an SOP descriptor and ending with an EOP descriptor). The
 *     actual firing of this interrupt can be delayed by the interrupt rate
 *     limiting capability of the hardware.
 *
 *     This ISR must start with the first descriptor in the active chain, working
 *     forward until we find the end of the active queue that is no longer in use
 *     by the hardware. Those descriptors should then be returnes the end of the
 *     free queue.
 *
 *  \retval
 *      void
 */
void HwIntTx(void)
{
    CPDMA_State     *pCPDMAState = NULL;
    uint32_t        intFlags = 0;
    uint32_t        channelNum = 0;

    /* Read the Tx interrupt cause from WR_C0_TX_STAT */
#if defined(USE_CSLR)
    intFlags = (uint32_t)(GMACSW_REGS->WR.WR_C0_TX_STAT & 0xFFU);
#else
#endif

    pCPDMAState = CPDMA_open(NULL);

    if (pCPDMAState == NULL)
    {
        /* If a crash occurs while interrupts were pending and the core is restored (no system wide reset)
         * we can end up here since the GMAC ISRs are hooked at init before the driver has a chance to reset the HW.
         * TODO: Consider hooking the ISRs as part of the driver initialization instead of SYS/BIOS init
         */
        while (0U != intFlags)
        {
            uint32_t channelMask = (uint32_t)((uint32_t)0x00000001U << (uint32_t)channelNum);

            uint32_t cp = GMACSW_REGS->STATERAM.TX_CP[channelNum];
            GMACSW_REGS->STATERAM.TX_CP[channelNum] = cp;
            /* Clear the channel flag for the channel just handled */
            intFlags &= ~channelMask;
            channelNum++;
        }
    }
    else
    {
        /* Look for transmit interrupts across all CPDMA Tx Channels */
        while (0U != intFlags)
        {
            uint32_t channelMask = (uint32_t)((uint32_t)0x00000001U << (uint32_t)channelNum);

            if ((uint32_t)0U != (uint32_t)(intFlags & channelMask))
            {
                LOCAL_serviceTxChannel(pCPDMAState, channelNum);
            }

            /* Clear the channel flag for the channel just handled */
            intFlags &= ~channelMask;
            channelNum++;
        }

        /* Decrement the reference count on the CPDMA_State object */
        CPDMA_close(pCPDMAState);
    }

    /* Write the EOI register */
#if defined(USE_CSLR)
    GMACSW_REGS->CPDMA.CPDMA_EOI_VECTOR = 0x2U;
#else
#endif
}

/*!
 *  @b HwIntRxThres
 *  @n
 *      GMACSW Receive Threshold ISR.
 *
 *  \param[in]  void
 *
 *  \retval
 *      void
 */
void HwIntRxThresh(void)
{
    CPDMA_State     *pCPDMAState = NULL;
    uint32_t        intFlags;
    uint32_t        channelNum = 0;

#if defined(USE_CSLR)
    /* Read the RX_THRESH interrupt cause from WR_C0_RX_THRESH_STAT */
    intFlags        = (uint32_t)(GMACSW_REGS->WR.WR_C0_RX_THRESH_STAT & 0xFFU);
#else
#endif

    pCPDMAState = CPDMA_open(NULL);

    if (pCPDMAState == NULL)
    {
        /* If a crash occurs while interrupts were pending and the core is restored (no system wide reset)
         * we can end up here since the GMAC ISRs are hooked at init before the driver has a chance to reset the HW.
         * TODO: Consider hooking the ISRs as part of the driver initialization instead of SYS/BIOS init
         */
        while (0U != intFlags)
        {
            uint32_t channelMask = (uint32_t)((uint32_t)0x00000001U << (uint32_t)channelNum);

            uint32_t cp = GMACSW_REGS->STATERAM.RX_CP[channelNum];
            GMACSW_REGS->STATERAM.RX_CP[channelNum] = cp;
            /* Clear the channel flag for the channel just handled */
            intFlags &= ~channelMask;
            channelNum++;
        }
    }
    else
    {
#if defined(USE_CSLR)
        /* Read the Rx interrupt cause from WR_C0_RX_STAT */
        uint32_t rxIntFlags = (uint32_t)(GMACSW_REGS->WR.WR_C0_RX_STAT & 0xFFU);
#else
#endif
        /* Look for receive threshold interrupts from across all CPDMA Rx Channels */
        while (0U != intFlags)
        {
            uint32_t channelMask = (uint32_t)((uint32_t)0x00000001U << (uint32_t)channelNum);

            if ( (uint32_t)0U != (uint32_t)(intFlags & channelMask))
            {
                LOCAL_serviceRxChannel(pCPDMAState, channelNum, 1U);
            }

            /* Clear the channel flags for the channel just handled */
            intFlags    &= ~channelMask;
            rxIntFlags  &= ~channelMask;
            channelNum++;
        }

        /* Decrement the reference count on the CPDMA_State object */
        CPDMA_close(pCPDMAState);


        /* Write the EOI register for RX_PULSE interrupts if there are none left */
        if (0U == rxIntFlags)
        {
#if defined(USE_CSLR)
            /* All RX_PULSE interrupts were handled as RX_THRESH interrupts */
            GMACSW_REGS->CPDMA.CPDMA_EOI_VECTOR = 0x1U;
#else
#endif
        }
    }

    /* Write the EOI register */
#if defined(USE_CSLR)
    GMACSW_REGS->CPDMA.CPDMA_EOI_VECTOR = 0x0U;
#else
#endif
}

/*!
 *  @b HwIntMisc
 *  @n
 *      GMACSW Misc ISR.
 *
 *  \param[in]  void
 *
 *  \retval
 *      void
 */
void HwIntMisc(void)
{
    uint32_t        intFlags;

    /* Read the Misc interrupt cause from WR_C0_MISC_STAT */
#if defined(USE_CSLR)
    intFlags = (uint32_t)(GMACSW_REGS->WR.WR_C0_MISC_STAT & 0xFFU);
#else
#endif

    /* Look for CPTS Event Interrupt */
    if ((intFlags & CSL_FMK(GMACSW_WR_C0_MISC_STAT_EVNT_PEND, 1)) != 0)
    {
        /* Get Handle to the CPTS state */
        CPTS_Handle hCptsState = CPTS_open(NULL);

        /* Call the CPTS module to handle all CPTS event interrupts */
        CPTS_handleEvents(hCptsState);

        CPTS_close(hCptsState);
#ifdef NSP_INSTRUMENTATION_ENABLED
        cpdmaStats.hwIntMiscCnt[0]++;
#endif
    }

    /* Look for Statistics Interrupt */
    else if ((intFlags & CSL_FMK(GMACSW_WR_C0_MISC_STAT_STAT_PEND, 1)) != 0)
    {
        /* Get Handle to statistics state */
        STATS_Handle hStats = STATS_open(NULL, 0U);

        /* Update the driver statistics structure */
        STATS_update(hStats);

        STATS_close(hStats);
#ifdef NSP_INSTRUMENTATION_ENABLED
        cpdmaStats.hwIntMiscCnt[1]++;
#endif
    }

    /* Look for CPDMA Host Error Interrupt */
    else if ((intFlags & CSL_FMK(GMACSW_WR_C0_MISC_STAT_HOST_PEND, 1)) != 0)
    {
#ifdef NSP_INSTRUMENTATION_ENABLED
        cpdmaStats.hwIntMiscCnt[2]++;
#endif

        /*
         * TODO: Handle host errors, which is a catastrophic failure
         * condition which we cannot overcome without peripheral reset
         */
        GMACSW_DeviceHandle hGMACSW = GMACSW_open(NULL);
        GMACSW_printFxn(hGMACSW, "Can't recover from GMAC host error, exiting...\n");
        exit(-1);
    }

    else if ((intFlags & CSL_FMK(GMACSW_WR_C0_MISC_STAT_MDIO_LINKINT, 1)) != 0)
    {
        /* not supported since only works for Port 0/PHY 0 */
#ifdef NSP_INSTRUMENTATION_ENABLED
        cpdmaStats.hwIntMiscCnt[3]++;
#endif
    }
    else
    {
        if ((intFlags & CSL_FMK(GMACSW_WR_C0_MISC_STAT_MDIO_USERINT, 1)) != 0)
        {
            /* not supported since only works for Port 0/PHY 0 */
        }
#ifdef NSP_INSTRUMENTATION_ENABLED
        cpdmaStats.hwIntMiscCnt[3]++;
#endif
    }

    /* Write the EOI register */
    GMACSW_REGS->CPDMA.CPDMA_EOI_VECTOR = 0x3U;
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_serviceRxChannel(CPDMA_State *pCPDMAState, uint32_t channelNum, uint32_t threshInt)
{
    CPDMA_BuffDesc  *pLastBuffDesc;
    uint32_t        newPacketCount = 0;
    uint32_t        completionType = 0;
#if defined(NSP_INSTRUMENTATION_ENABLED)
    CPDMA_InterruptStats *intStats;
    uint32_t        time1;
    uint32_t        interruptIndex;

    if (0U != threshInt)
    {
        intStats = &cpdmaStats.rxThreshChannelStats[channelNum];
    }
    else
    {
        intStats = &cpdmaStats.rxChannelStats[channelNum];
    }

    interruptIndex = (uint32_t)(intStats->totalInterruptCnt & (INTERRUPT_HISTORY_CNT - 1U));

    intStats->totalInterruptCnt++;
    time1 = (uint32_t) TIMER_READ();
#endif
    pLastBuffDesc = (CPDMA_BuffDesc *)GMACSW_REGS->STATERAM.RX_CP[channelNum];

    /* Only do stuff if not a teardown request for this channel */
    if (0xFFFFFFFCU != (uint32_t)pLastBuffDesc)
    {
        /* Double cast to avoid MISRA-C:2004 11.4 */
        CPDMA_Channel       *pCPDMAChannel          = (CPDMA_Channel *) ((void *)&pCPDMAState->rxChannel[channelNum]);
        CPDMA_PacketQueue   *pInUseQueue            = &pCPDMAChannel->inUsePacketQueue;
        CPDMA_PacketQueue   *pFromHardwareQueue     = &pCPDMAChannel->fromHardwarePacketQueue;
        CPDMA_Packet        *pCurrentPacket         = pInUseQueue->pHead;
        CPDMA_Packet        *pLastPacketAtEntry     = pInUseQueue->pTail;

        CPDMA_Packet        *pFirstNewPacket        = pCurrentPacket;
        CPDMA_Packet        *pLastNewPacket         = NULL;

        /* We got a non-teardown interrupt for this channel, which means at least one packet was received */
        while ((0U == completionType) && (NULL != pCurrentPacket))
        {
            uint32_t startOfPacketFlags = pCurrentPacket->buffDescQueue.pHead->flagsAndPacketLength;

            if ((startOfPacketFlags & CPDMA_BUF_DESC_OWNER_FLAG) != 0)
            {
                /* This packet is hardware owned, so we are done processing completed packets */
                completionType = (uint32_t)1U;
            }
            else
            {
                /* We have a new packet from the hardware */
                newPacketCount++;
                pLastNewPacket      = pCurrentPacket;
                pLastBuffDesc       = pLastNewPacket->buffDescQueue.pTail;

                /* Check for misqueued packet at end of queue*/
                if ((pLastBuffDesc->flagsAndPacketLength & CPDMA_BUF_DESC_EOQ_FLAG) != 0)
                {
                    if (pLastBuffDesc->pNextBufferDescriptor != NULL)
                    {
                        /*
                         * The hardware set the EOQ flag, but our EOP descriptor points
                         * to another following descriptor in a new packet -> misqueued packet,
                         * so restart the channel reception with that new packet.
                         */
                        GMACSW_REGS->STATERAM.RX_HDP[channelNum] = (uint32_t) pLastBuffDesc->pNextBufferDescriptor;
                    }
                    completionType = (uint32_t)2U;
                }
                /* Check to see if we hit the end of the completed queue, as it was observed upon ISR entry*/
                else
                {
                    if (pLastNewPacket == pLastPacketAtEntry)
                    {
                        completionType = (uint32_t)3U;
                    }
                }

                /* Move to next packet in the inUse queue */
                pCurrentPacket = pCurrentPacket->pNextPacket;
            }
        }
        if (NULL == pCurrentPacket)
        {
            completionType = (uint32_t)4U;
        }

        /* If there are new used packets, form the used packet queue and update the inUse queue*/
        if (0U != newPacketCount)
        {
            /*
             * We don't need to link the new used packets since they should still
             * be linked from being on the InUse Queue.
             */

            /* Increment the used queue count by number of new packets */
            pFromHardwareQueue->count               = pFromHardwareQueue->count + newPacketCount;
            if (NULL != pFromHardwareQueue->pHead)
            {
                /* If the used queue is not empty, let's add to the end */
                pFromHardwareQueue->pTail->pNextPacket      = pFirstNewPacket;
            }
            else
            {
                /* If the used queue is empty, point to the first new packet */
                pFromHardwareQueue->pHead                   = pFirstNewPacket;
            }
            /* Terminate the queue with the last new packet */
            pLastNewPacket->pNextPacket             = NULL;
            pFromHardwareQueue->pTail               = pLastNewPacket;

            /* Update the start of the active InUse queue */
            pInUseQueue->pHead                      = pCurrentPacket;
            pInUseQueue->count                      = pInUseQueue->count - newPacketCount;

            /* Notify the translation layer there are packets in the Used queue */
            (*pCPDMAChannel->callbacks.pFxnCbUsedPacketNotify)(pCPDMAChannel->callbacks.hCallbackArg);
        }
    }

    /* Clear the interrupt condition by writing completion pointer of last descriptor serviced */
    GMACSW_REGS->STATERAM.RX_CP[channelNum] = (uint32_t) pLastBuffDesc;

    if (0U != threshInt)
    {
        /*
         * Clear the threshold value so that this ISR won't immediately fire again
         * for this channel. This value will get set again in the CPDMA_deliverPackets()
         * routine when the stack returns packets back to the Rx CPDMA hardware. Note that
         * since we are relying on an asynchronous task to run to fill in the hardware descriptor
         * queue, you should not set the threshold too low for the channel. It is recommended
         * to use a value between 25% and 50% of the total buffer descriptors assigned to the
         * channel
         */
        GMACSW_REGS->CPDMA.CPDMA_RX_PENDTHRESH[channelNum] = 0;
    }

#if defined(NSP_INSTRUMENTATION_ENABLED)
    /* Per-channel interrupt stats gathering */
    {
        uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
        uint32_t timePerPacket = 0;
        if(newPacketCount) timePerPacket = timeDiff / newPacketCount;

        intStats->completionType[interruptIndex] = completionType;

        intStats->totalPacketCnt += newPacketCount;
        intStats->totalCycleCnt += timeDiff;

        intStats->cycleCountPerInterrupt[interruptIndex] = timeDiff;
        if (timeDiff > intStats->cycleCountPerInterruptMax)
        {
            intStats->cycleCountPerInterruptMax = timeDiff;
            intStats->cycleCountPerInterruptMaxEventNumber = intStats->totalInterruptCnt;
        }

        intStats->packetsPerInterrupt[interruptIndex] = newPacketCount;
        if (newPacketCount > intStats->packetsPerInterruptMax)
        {
            intStats->packetsPerInterruptMax = newPacketCount;
            intStats->packetsPerInterruptMaxEventNumber = intStats->totalInterruptCnt;
        }

        intStats->cycleCountPerPacket[interruptIndex] = timePerPacket;
        if (timePerPacket > intStats->cycleCountPerPacketMax)
        {
            intStats->cycleCountPerPacketMax = timePerPacket;
            intStats->cycleCountPerPacketMaxEventNumber = intStats->totalInterruptCnt;
        }
    }
#endif
}

static void LOCAL_serviceTxChannel(CPDMA_State *pCPDMAState, uint32_t channelNum)
{
    CPDMA_BuffDesc  *pLastBuffDesc;
    uint32_t        newPacketCount = 0;
    uint32_t        completionType = 0;
#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t        time1;
    uint32_t        interruptIndex = (uint32_t)(cpdmaStats.txChannelStats[channelNum].totalInterruptCnt & (INTERRUPT_HISTORY_CNT - 1U));

    cpdmaStats.txChannelStats[channelNum].totalInterruptCnt++;
    time1 = (uint32_t) TIMER_READ();
#endif
    pLastBuffDesc  = (CPDMA_BuffDesc *)GMACSW_REGS->STATERAM.TX_CP[channelNum];

    /* Only do stuff if not a teardown request for this channel */
    if (0xFFFFFFFCU != (uint32_t)pLastBuffDesc)
    {
        /* Double cast to avoid MISRA-C:2004 11.4 */
        CPDMA_Channel       *pCPDMAChannel          = (CPDMA_Channel *) ((void *) &pCPDMAState->txChannel[channelNum]);
        CPDMA_PacketQueue   *pInUseQueue            = &pCPDMAChannel->inUsePacketQueue;
        CPDMA_PacketQueue   *pFromHardwareQueue     = &pCPDMAChannel->fromHardwarePacketQueue;
        CPDMA_Packet        *pCurrentPacket         = pInUseQueue->pHead;
        CPDMA_Packet        *pLastPacketAtEntry     = pInUseQueue->pTail;

        CPDMA_Packet        *pFirstNewPacket        = pCurrentPacket;
        CPDMA_Packet        *pLastNewPacket         = NULL;

        /* We got a non-teardown interrupt for this channel, which means at least one packet was sent */
        while ((0U == completionType) && (NULL != pCurrentPacket))
        {
            CPDMA_BuffDesc *pFirstBuffDesc = pCurrentPacket->buffDescQueue.pHead;

            if ((pFirstBuffDesc->flagsAndPacketLength & CPDMA_BUF_DESC_OWNER_FLAG) != 0)
            {
                /* This packet is hardware owned, so we are done processing completed packets */
                completionType = (uint32_t)1U;
            }
            else
            {
                /* We have a new packet from the hardware */
                newPacketCount++;
                pLastNewPacket      = pCurrentPacket;
                pLastBuffDesc       = pLastNewPacket->buffDescQueue.pTail;

                /* Check for misqueued packet */
                if ((pLastBuffDesc->flagsAndPacketLength & CPDMA_BUF_DESC_EOQ_FLAG) != 0)
                {
                    if (pLastBuffDesc->pNextBufferDescriptor != NULL)
                    {
                        /*
                         * The hardware set the EOQ flag, but our EOP descriptor points
                         * to another following descriptor in a new packet -> misqueued packet,
                         * so restart the channel transmission with that new packet.
                         */
                        GMACSW_REGS->STATERAM.TX_HDP[channelNum] = (uint32_t) pLastBuffDesc->pNextBufferDescriptor;
                    }
                    completionType = (uint32_t)2U;
                }
                else
                {
                    if (pLastNewPacket == pLastPacketAtEntry)
                    {
                        completionType = (uint32_t)3U;
                    }
                }

                /* Unlink the new packets' descriptor queues */
                pLastBuffDesc->pNextBufferDescriptor = NULL;

                /* Move to next packet in the inUse queue */
                pCurrentPacket = pCurrentPacket->pNextPacket;
            }

        }
        if (NULL == pCurrentPacket)
        {
            completionType = (uint32_t)4U;
        }

        /*
         * If there are new packets coming out of the hardware, form the fromHardware packet queue
         * and update the inUse queue
         */
        if (0U != newPacketCount)
        {
            /*
             * We don't need to link the new used packets since they should still
             * be linked from being in the InUse Queue.
             */

            /* Increment the fromHardware queue count by number of new packets */
            pFromHardwareQueue->count = pFromHardwareQueue->count + newPacketCount;
            if (NULL != pFromHardwareQueue->pHead)
            {
                /* If the fromHardware queue is not empty, let's add to the end */
                pFromHardwareQueue->pTail->pNextPacket = pFirstNewPacket;
            }
            else
            {
                /* If the fromHardware queue is empty, point to the first new packet */
                pFromHardwareQueue->pHead = pFirstNewPacket;
            }
            /* Terminate the queue with the last new packet */
            pLastNewPacket->pNextPacket             = NULL;
            pFromHardwareQueue->pTail               = pLastNewPacket;

            /* Update the start of the active in-use queue */
            pInUseQueue->pHead                      = pCurrentPacket;
            pInUseQueue->count                      = pInUseQueue->count - newPacketCount;

            /* Notify the translation layer there are packets in the Used queue */
            (*pCPDMAChannel->callbacks.pFxnCbUsedPacketNotify)(pCPDMAChannel->callbacks.hCallbackArg);
        }
    }

    /* Clear the interrupt condition by writing completion pointer of last descriptor serviced */
    GMACSW_REGS->STATERAM.TX_CP[channelNum] = (uint32_t) pLastBuffDesc;

#if defined(NSP_INSTRUMENTATION_ENABLED)
    /* Per-channel interrupt stats gathering */
    {
        uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
        uint32_t timePerPacket = 0;
        if(newPacketCount) timePerPacket = timeDiff / newPacketCount;

        cpdmaStats.txChannelStats[channelNum].totalPacketCnt += newPacketCount;
        cpdmaStats.txChannelStats[channelNum].totalCycleCnt += timeDiff;

        cpdmaStats.txChannelStats[channelNum].cycleCountPerInterrupt[interruptIndex] = timeDiff;
        if (timeDiff > cpdmaStats.txChannelStats[channelNum].cycleCountPerInterruptMax)
        {
            cpdmaStats.txChannelStats[channelNum].cycleCountPerInterruptMax = timeDiff;
            cpdmaStats.txChannelStats[channelNum].packetsPerInterruptMaxEventNumber = cpdmaStats.txChannelStats[channelNum].totalInterruptCnt;
        }

        cpdmaStats.txChannelStats[channelNum].packetsPerInterrupt[interruptIndex] = newPacketCount;
        if (newPacketCount > cpdmaStats.txChannelStats[channelNum].packetsPerInterruptMax)
        {
            cpdmaStats.txChannelStats[channelNum].packetsPerInterruptMax = newPacketCount;
            cpdmaStats.txChannelStats[channelNum].packetsPerInterruptMaxEventNumber = cpdmaStats.txChannelStats[channelNum].totalInterruptCnt;
        }

        cpdmaStats.txChannelStats[channelNum].cycleCountPerPacket[interruptIndex] = timePerPacket;
        if (timePerPacket > cpdmaStats.txChannelStats[channelNum].cycleCountPerPacketMax)
        {
            cpdmaStats.txChannelStats[channelNum].cycleCountPerPacketMax = timePerPacket;
            cpdmaStats.txChannelStats[channelNum].packetsPerInterruptMaxEventNumber = cpdmaStats.txChannelStats[channelNum].totalInterruptCnt;
        }
    }
#endif
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

