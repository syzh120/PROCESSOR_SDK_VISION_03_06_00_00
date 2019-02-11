/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 */

/**
 *  \file   bspdrv_uartEdma.c
 *
 *  \brief  This files contains the edma functions required for the Uart driver
 *          to function in the EDMA mode.
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */
#include <string.h>
#include <assert.h>

#include <xdc/std.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/IOM.h>
#if defined (__ARM_ARCH_7A__)
#include <ti/sysbios/family/arm/a15/Cache.h>
#else
#include <ti/sysbios/hal/Cache.h>
#endif

#include <ti/sdo/edma3/drv/edma3_drv.h>

#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <bspdrv_uartPriv.h>
#include <ti/drv/vps/include/common/bsp_types.h>

/* Include Family specific hwi files */
#if defined (__TI_ARM_V7M4__) || defined (BUILD_M3)
#include <ti/sysbios/family/arm/m3/Hwi.h>
#elif defined (_TMS320C6X)
#include <ti/sysbios/family/c64p/Hwi.h>
#elif defined (__ARM_ARCH_7A__)
#include <ti/sysbios/family/arm/gic/Hwi.h>
#elif defined (BUILD_A8)
#include <ti/sysbios/family/arm/a8/intcps/Hwi.h>
#elif defined (BUILD_ARP32)
#include <ti/sysbios/family/arp32/Hwi.h>
#else
#include <ti/sysbios/hal/Hwi.h>
#endif

#include <ti/csl/soc.h>

#define MODE_B (0x000000BF)

/* ========================================================================== */
/*                        LOCAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */

static Void uartStartEdmaTxTransfer(Uart_ChanObj *chanHandle, Error_Block *eb);
static Void uartStartEdmaRxTransfer(Uart_ChanObj *chanHandle, Error_Block *eb);

/* ========================================================================== */
/*                       FUNCTION DEFINITIONS                                 */
/* ========================================================================== */
/**
 *  \brief  Edma transfer
 *
 *          This function initiates Edma mode of operation
 *
 *  \note   As this function is also executed in interrupt context
 *          validation of the retVal is not done. Once this is tested
 *          there  should be no issues, unless DMA is changed
 *
 *  \param  chanHandle  [IN]  Handle of the Channel Object
 *  \param  cmd         [IN]  Read\Write cmd
 *  \param  eb          [OUT] Pointer to the error block
 *
 *  \return If successful, returns IOM_COMPLETED else IOM Error
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *          cmd         must be a valid READ/WRITE command.
 *          eb          if null raise error and aborts the program, if not null
 *                      and valid raises error but shall allow continuation of
 *                      execution
 *
 *  \leave  Not Implemented.
 *
 */

Int32 Uart_localStartEdmaTransfer(Uart_ChanObj *chanHandle,
                                  UInt32        cmd,
                                  Error_Block  *eb)
{
    Int32 retVal = IOM_COMPLETED;

    assert(NULL != chanHandle);

    chanHandle->ioCompleted = (Bool) FALSE;

    if ((UInt32)IOM_READ == cmd)
    {
        uartStartEdmaRxTransfer(chanHandle, eb);
    }
    else if ((UInt32) IOM_WRITE == cmd)
    {
        uartStartEdmaTxTransfer(chanHandle, eb);
    }
    else
    {
        retVal = IOM_ENOTIMPL;
    }

    return retVal;
}

/**
 *  \brief  Callback for the receive transaction
 *
 *          This function is the callback for the receive operation when
 *          it is completed
 *
 *  \param  tcc     [IN]   Handle of the Edma Object
 *  \param  status  [IN]   Error code returned by the Edma
 *  \param  appData [IN]   Data passed Edma during initiation
 *
 *  \return None
 *
 *  \enter  tcc       must be a valid interrupt event channel.
 *          status    must be a valid error code status.
 *          appData   must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 *
 */
Void Uart_localIsrEdma(UInt32 tcc, EDMA3_RM_TccStatus status, Ptr appData)
{
    Uart_ChanObj *chanHandle  = NULL;
    Uart_Object  *instHandle  = NULL;
    Bool          bFalseWhile = (Bool) TRUE;
    UInt32        key         = 0;

#ifdef BIOS_PWRM_ENABLE
    PWRM_Status   retVal = PWRM_SOK;
    UInt32        count  = 0x00;
#endif

    assert(NULL != appData);
    chanHandle = (Uart_ChanObj *) appData;

    assert(NULL != (chanHandle->devHandle));
    instHandle = (Uart_Object *) chanHandle->devHandle;

    assert(NULL != instHandle);

    /* To remove the compiler warning                                     */
    tcc = tcc;

    /* enter critical section                                             */
    key = (UInt32) Hwi_disable();

    if (EDMA3_RM_XFER_COMPLETE == status)
    {
        chanHandle->ioCompleted = (Bool) TRUE;
    }

    EDMA3_DRV_disableLogicalChannel(
        (EDMA3_DRV_Handle) chanHandle->hEdma,
        (UInt32) chanHandle->edmaChId,
        (EDMA3_DRV_TrigMode) EDMA3_DRV_TRIG_MODE_EVENT);

    do
    {
        bFalseWhile = (Bool) FALSE;

        if (EDMA3_RM_XFER_COMPLETE != status)
        {
            /* Ensure to clear the error bits of EDMA channel                 */
            EDMA3_DRV_clearErrorBits((EDMA3_DRV_Handle) chanHandle->hEdma,
                                     chanHandle->edmaChId);

            if (TRUE == chanHandle->ioCompleted)
            {
                break;
            }

            if (NULL != chanHandle->activeIOP)
            {
                /* Update the current errors status                           */
                chanHandle->errors++;
                Uart_localCompleteCurrentIO(chanHandle);
            }
        }
        else
        {
            if (UART_INPUT == chanHandle->mode)
            {
                instHandle->stats.rxBytes += chanHandle->bytesRemaining;
            }
            else
            {
                instHandle->stats.txBytes += chanHandle->bytesRemaining;
            }

            chanHandle->ioCompleted = (Bool) FALSE;

            if (NULL != chanHandle->activeIOP)
            {
                Uart_localCompleteCurrentIO(chanHandle);
            }
        }
#ifdef BIOS_PWRM_ENABLE
        if (FALSE == instHandle->pwrmInfo.ioSuspend)
        {
#endif
        Uart_loadPendedIops(chanHandle);
#ifdef BIOS_PWRM_ENABLE
    }
    else
    {
        if (TRUE == instHandle->devParams.pscPwrmEnable)
        {
            /* set the current active IOP as NULL                         */
            chanHandle->activeIOP = NULL;
            instHandle->devState  = UART_DRIVERSTATE_PWRM_SUSPEND;

            if ((NULL == instHandle->rcvChanObj.activeIOP) &&
                (NULL == instHandle->xmtChanObj.activeIOP))
            {
                /* if both the channels are inactive then reset the       *
                 * io suspend flag                                        */
                instHandle->pwrmInfo.ioSuspend = FALSE;

                if ((PWRM_GOINGTOSLEEP ==
                     instHandle->pwrmInfo.pwrmEvent) ||
                    (PWRM_GOINGTODEEPSLEEP ==
                     instHandle->pwrmInfo.pwrmEvent))
                {
                    /* reduce the dependency count                        */
                    retVal =
                        PWRM_getDependencyCount(
                            (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId,
                            &count);

                    instHandle->pwrmInfo.dependencyCount = count;

                    if (PWRM_SOK == retVal)
                    {
                        while (count > 0)
                        {
                            retVal = PWRM_releaseDependency(
                                (PWRM_Resource)
                                instHandle->deviceInfo.pwrmPrcmId);

                            if (PWRM_SOK != retVal)
                            {
                                break;
                            }
                            count--;
                        }
                    }
                }

                /* call the delayed completion function                   */
                (instHandle->pwrmInfo.delayedCompletionFxn \
                 [instHandle->pwrmInfo.pwrmEvent])();
            }
        }
    }
#endif
    } while (bFalseWhile);

    /* exit critical section                                                  */
    Hwi_restore(key);
}

/**
 *  \brief  process the RX edma transfer start command
 *
 *          This function starts the RX side edma transfers
 *
 *  \param  chanHandle  [IN]   Handle to the channel
 *  \param  eb          [OUT]  pointer to the error block
 *
 *  \return None
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *          eb          if null raise error and aborts the program, if not null
 *                      and valid raises error but shall allow continuation of
 *                      execution
 *
 *  \leave  Not Implemented.
 */
static Void uartStartEdmaRxTransfer(Uart_ChanObj *chanHandle, Error_Block *eb)
{
    Int32 retVal                   = IOM_COMPLETED, edmaRetVal;
    EDMA3_DRV_Handle hEdma         = NULL;
    Uart_Object        *instHandle = NULL;
    EDMA3_DRV_PaRAMRegs paramSet   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    UInt32              actualThreshold;

    assert(NULL != chanHandle);

    hEdma      = (EDMA3_DRV_Handle) chanHandle->hEdma;
    instHandle = (Uart_Object *) chanHandle->devHandle;

    assert(NULL != hEdma);
    assert(NULL != instHandle);

    if ((Bool) TRUE == instHandle->enableCache)
    {
        /* Move the data to physical memory and invalidate the cache line     */
        Cache_wbInv(
            (Ptr) chanHandle->activeBuf,
            (UInt32) chanHandle->bytesRemaining,
            (Bits16) Cache_Type_ALL,
            (Bool) TRUE);
    }

    /* When FIFO is disabled, trigger level is set to 1 bytes by UART */
    if (TRUE == instHandle->devParams.fifoEnable)
    {
        actualThreshold = instHandle->devParams.rxThreshold;
    }
    else
    {
        actualThreshold = BSP_UART_FIFO_DISABLED_CHUNK_SIZE;
    }

    /* Get the PaRAM set for default parameters                               */
    EDMA3_DRV_getPaRAM((EDMA3_DRV_Handle) hEdma,
                       (UInt32) chanHandle->edmaChId, &paramSet);

    if ((Bool) FALSE == chanHandle->optFlag)
    {
        chanHandle->optFlag  = (Bool) TRUE;
        chanHandle->optValue = (UInt32) paramSet.opt;
    }
    paramSet.opt = (UInt32) chanHandle->optValue;

#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    paramSet.srcAddr = (UInt32) ((instHandle->deviceInfo.baseAddress)
                                 + UART_RHR);
#else
    paramSet.srcAddr = (UInt32) (((instHandle->deviceInfo.baseAddress)
                                  + UART_RHR) + BSP_UART_EDMA_BASE_ADDR);
#endif
    paramSet.destAddr = (UInt32) (chanHandle->activeBuf);
    paramSet.aCnt     = BSP_UART_EDMA3CC_PARAM_ACNT;
    paramSet.bCnt     = (UInt16) actualThreshold;
    paramSet.srcBIdx  = (UInt16) 0;
    paramSet.srcCIdx  = (UInt16) 0;
    paramSet.destBIdx = BSP_UART_EDMA3CC_DST_BINDEX;
    paramSet.destCIdx = (UInt16) actualThreshold;

    if (chanHandle->bytesRemaining <= BSP_UART_EDMA3CC_COUNT_VALUE)
    {
        paramSet.cCnt =
            (UInt16) (BSP_UART_EDMA3CC_COUNT_VALUE &
                        (chanHandle->bytesRemaining / actualThreshold));
    }
    else
    {
        retVal = IOM_EBADIO;
    }

    paramSet.bCntReload = (UInt16) 0;
    paramSet.linkAddr = (UInt16) (chanHandle->edmaLinkChPhyAddr
                                  & BSP_UART_EDMA3CC_PARAM_LINK_ADDR_MASK_VALUE);

    /* Src is in CONST addr mode & Dest is in INCR addr modes                 */
    paramSet.opt &= BSP_UART_EDMA3CC_OPT_DAM_INCR_MODE;
    paramSet.opt |= BSP_UART_EDMA3CC_OPT_SAM_CONST_MODE;

    /* FIFO width is 8 bit                                                    */
    paramSet.opt &= BSP_UART_EDMA3CC_OPT_FIFO_WIDTH;

    /* EDMA3_DRV_SYNC_AB                                                      */
    paramSet.opt &= BSP_UART_EDMA3CC_OPT_SYNC_MASK_VALUE;
    paramSet.opt |= BSP_UART_EDMA3CC_OPT_SYNC_AB;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                            */
    paramSet.opt |= ((UInt32) 1U << BSP_UART_OPT_TCINTEN_SHIFT);

    /* ADDED FOR ARM PLATFORM                                                 */
    /* update the transfer completion code                                    */
    paramSet.opt &= (~BSP_UART_EDMA3CC_OPT_TCC_MASK);
    paramSet.opt |= ((chanHandle->edmaTcc) << BSP_UART_EDMA3CC_OPT_TCC_SHIFT);

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the PaRAM Set.                                          */
        retVal = EDMA3_DRV_setPaRAM((EDMA3_DRV_Handle) hEdma,
                                    (UInt32) chanHandle->edmaChId,
                                    &paramSet);

        if (IOM_COMPLETED != retVal)
        {
            retVal = IOM_EBADARGS;
        }
    }

    if (IOM_COMPLETED == retVal)
    {
        retVal = EDMA3_DRV_getPaRAM((EDMA3_DRV_Handle) chanHandle->hEdma,
                                    (UInt32) chanHandle->edmaLinkChId,
                                    &paramSet);

        paramSet.aCnt     = BSP_UART_EDMA3CC_PARAM_ACNT;
        paramSet.linkAddr = BSP_UART_EDMA3CC_PARAM_LINK_ADDRESS;
        paramSet.opt     &= ~((UInt32) BSP_UART_EDMA3CC_OPT_SYNC_A <<
                               BSP_UART_EDMA3CC_OPT_SYNCDIM_SHIFT);
    }

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the PaRAM Set.                                          */
        retVal = EDMA3_DRV_setPaRAM((EDMA3_DRV_Handle) chanHandle->hEdma,
                                    (UInt32) chanHandle->edmaLinkChId,
                                    &paramSet);
    }

    if (IOM_COMPLETED == retVal)
    {
        retVal = EDMA3_DRV_linkChannel((EDMA3_DRV_Handle) chanHandle->hEdma,
                                       (UInt32) chanHandle->edmaChId,
                                       (UInt32) chanHandle->edmaLinkChId);
    }

    if (IOM_COMPLETED == retVal)
    {
        UInt32 isRxFifoFull = FALSE, fifoLevel;
        UInt32 edmaStatus = 0U, isEdmaEventPending = FALSE;

        /* In FIFO mode, DMA events are generated as soon as there are
         * RX threshold level bytes become available in the FIFO. Hence it is
         * required to check the FIFO level in order to check if DMA events
         * are consumed */
        fifoLevel =
            UARTRxFIFOLevelGet((UInt32) instHandle->deviceInfo.baseAddress);
        if (TRUE == instHandle->devParams.fifoEnable)
        {
            if (fifoLevel >= instHandle->devParams.rxThreshold)
            {
                isRxFifoFull = (UInt32) TRUE;
            }
        }
        else
        {
            /* Incase of FIFO disable, FIFO size is 1. So for FIFO empty,
             * check for zero */
            if (fifoLevel > 0U)
            {
                isRxFifoFull = (UInt32) TRUE;
            }
        }

        /* Get EDMA event pending status */
        edmaRetVal = EDMA3_DRV_getChannelStatus(
                            (EDMA3_DRV_Handle) hEdma,
                            (UInt32) chanHandle->edmaChId,
                            &edmaStatus);
        if (edmaRetVal != ((Int32) EDMA3_DRV_SOK))
        {
            retVal = IOM_EBADARGS;
        }
        if ((UInt32) EDMA3_DRV_CHANNEL_EVENT_PENDING ==
                (edmaStatus & ((UInt32) EDMA3_DRV_CHANNEL_EVENT_PENDING)))
        {
            isEdmaEventPending = (UInt32) TRUE;
        }

        /* Note: Getting the FIFO status and EDMA event pend should be
         * done prior to enabling the EDMA channel */
        edmaRetVal = EDMA3_DRV_enableTransfer(
                        (EDMA3_DRV_Handle) hEdma,
                        (UInt32) chanHandle->edmaChId,
                        (EDMA3_DRV_TrigMode) EDMA3_DRV_TRIG_MODE_EVENT);
        if (edmaRetVal != ((Int32) EDMA3_DRV_SOK))
        {
            retVal = IOM_EBADARGS;
        }

        /* Workaround: In case of DMA mode, the UART IP generates the
         * next EDMA event as soon as the FIFO gets full or when there are
         * RX threshold level bytes present in FIFO. In the EDMA ISR,
         * the DMA mode is disabled and EDMA channel is disabled.
         * There is a race condition between software (CPU) disabling the DMA
         * mode and the UART IP generating the DMA event to EDMA.
         *
         * In cases when the software is slower (multi-tasking systems or
         * in heavily CPU loaded systems or for lower FIFO trigger levels),
         * the UART IP DMA event gets generated before the CPU could disable
         * the DMA event generation.
         *
         * When this happens, since the EDMA channel is enabled, the EDMA will
         * acknowledge the EDMA event but it doesn't have proper param set to
         * do the actual transfer to the UART FIFO. Hence the event gets lost
         * and the UART IP doesn't generate the next EDMA event unless the FIFO
         * is read. This becomes a deadlock!!
         *
         * To break the dead lock, first we need to identify whether this had
         * happened by checking the UART FIFO level and the EDMA channel status.
         * As per UART IP, in DMA mode, when ever the FIFO is full or has RX
         * threshold amount of bytes it should have raised an DMA event.
         * Hence we check if the UART FIFO is full and see if the event is
         * latched in the EDMA register.
         * So if FIFO is full and event is not latched, then we are in a
         * deadlock.
         *
         * To recover from the deadlock, we do a manual trigger for the first
         * time and the rest of the transfer is taken care automatically
         * by further UART events.
         */
        if (((UInt32) TRUE == isRxFifoFull) && ((UInt32)FALSE == isEdmaEventPending))
        {
            edmaRetVal = EDMA3_DRV_enableTransfer(
                            (EDMA3_DRV_Handle) hEdma,
                            (UInt32) chanHandle->edmaChId,
                            (EDMA3_DRV_TrigMode) EDMA3_DRV_TRIG_MODE_MANUAL);
            if (edmaRetVal != ((Int32) EDMA3_DRV_SOK))
            {
                retVal = IOM_EBADARGS;
            }
        }
    }
}

/**
 *  \brief  process the TX edma transfer start command
 *
 *          This function process the TX edma transfer starting.
 *
 *  \param  chanHandle  [IN]   Handle to the channel
 *  \param  eb          [OUT]  pointer to the error block
 *
 *  \return None
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *          eb          if null raise error and aborts the program, if not null
 *                      and valid raises error but shall allow continuation of
 *                      execution
 *
 *  \leave  Not Implemented.
 */
static Void uartStartEdmaTxTransfer(Uart_ChanObj *chanHandle, Error_Block *eb)
{
    Int32 retVal                   = IOM_COMPLETED, edmaRetVal;
    EDMA3_DRV_Handle hEdma         = NULL;
    Uart_Object        *instHandle = NULL;
    EDMA3_DRV_PaRAMRegs paramSet   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    UInt32              actualThreshold;

    assert(NULL != chanHandle);

    hEdma      = (EDMA3_DRV_Handle) chanHandle->hEdma;
    instHandle = (Uart_Object *) chanHandle->devHandle;

    assert(NULL != hEdma);
    assert(NULL != instHandle);

    if ((Bool) TRUE == instHandle->enableCache)
    {
        Cache_wb(
            (Ptr) chanHandle->activeBuf,
            (UInt32) chanHandle->bytesRemaining,
            sizeof (UInt16),
            (Bool) TRUE);
    }

    /* When FIFO is disabled, trigger level is set to 1 bytes by UART */
    if (TRUE == instHandle->devParams.fifoEnable)
    {
        actualThreshold = instHandle->devParams.txThreshold;
    }
    else
    {
        actualThreshold = BSP_UART_FIFO_DISABLED_CHUNK_SIZE;
    }

    /* Get the PaRAM set for default parameters                               */
    EDMA3_DRV_getPaRAM((EDMA3_DRV_Handle) hEdma,
                       (UInt32) chanHandle->edmaChId,
                       &paramSet);

    if ((Bool) FALSE == chanHandle->optFlag)
    {
        chanHandle->optFlag  = (Bool) TRUE;
        chanHandle->optValue = paramSet.opt;
    }
    paramSet.opt = chanHandle->optValue;

    paramSet.srcAddr = (UInt32) (chanHandle->activeBuf);
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    paramSet.destAddr = (UInt32) ((instHandle->deviceInfo.baseAddress)
                                  + UART_THR);
#else
    paramSet.destAddr = (UInt32) (((instHandle->deviceInfo.baseAddress)
                                   + UART_THR) + BSP_UART_EDMA_BASE_ADDR);
#endif

    paramSet.aCnt     = BSP_UART_EDMA3CC_PARAM_ACNT;
    paramSet.bCnt     = (UInt16) actualThreshold;
    paramSet.srcBIdx  = BSP_UART_EDMA3CC_SRC_BINDEX;
    paramSet.srcCIdx  = (UInt16) actualThreshold;
    paramSet.destBIdx = (UInt16) 0;
    paramSet.destCIdx = (UInt16) 0;

    if ((chanHandle->bytesRemaining <= BSP_UART_EDMA3CC_COUNT_VALUE) &&
        (chanHandle->bytesRemaining > actualThreshold))
    {
        paramSet.cCnt =
            (UInt16) (BSP_UART_EDMA3CC_COUNT_VALUE &
                      (chanHandle->bytesRemaining / actualThreshold));
    }
    else if ((chanHandle->bytesRemaining <= actualThreshold) &&
             (chanHandle->bytesRemaining > 0))
    {
        paramSet.cCnt = 1;
    }
    else
    {
        retVal = IOM_EBADIO;
    }

    paramSet.bCntReload = (UInt16) 0;
    /* This linkAdddr is a 16 bit Address                                     */
    paramSet.linkAddr = (UInt16) (chanHandle->edmaLinkChPhyAddr
                                  & BSP_UART_EDMA3CC_PARAM_LINK_ADDR_MASK_VALUE);

    /* Src is in INCR mode & Dest is in FIFO modes                            */
    paramSet.opt &= BSP_UART_EDMA3CC_OPT_SAM_INCR_MODE;
    paramSet.opt |= BSP_UART_EDMA3CC_OPT_DAM_CONST_MODE;

    /* FIFO width is 8 bit                                                    */
    paramSet.opt &= BSP_UART_EDMA3CC_OPT_FIFO_WIDTH;

    /* EDMA3_DRV_SYNC_AB                                                      */
    paramSet.opt &= BSP_UART_EDMA3CC_OPT_SYNC_MASK_VALUE;
    paramSet.opt |= BSP_UART_EDMA3CC_OPT_SYNC_AB;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                            */
    paramSet.opt |= ((UInt32) BSP_UART_OPT_TCINTEN << BSP_UART_OPT_TCINTEN_SHIFT);

    /* update the transfer completion code                                    */
    paramSet.opt &= (~BSP_UART_EDMA3CC_OPT_TCC_MASK);
    paramSet.opt |= ((chanHandle->edmaTcc) << BSP_UART_EDMA3CC_OPT_TCC_SHIFT);

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the PaRAM Set.                                          */
        retVal = EDMA3_DRV_setPaRAM((EDMA3_DRV_Handle) hEdma,
                                    (UInt32) chanHandle->edmaChId,
                                    &paramSet);
        if (IOM_COMPLETED != retVal)
        {
            retVal = IOM_EBADARGS;
        }
    }

    retVal = EDMA3_DRV_getPaRAM((EDMA3_DRV_Handle) chanHandle->hEdma,
                                (UInt32) chanHandle->edmaLinkChId,
                                &paramSet);

    paramSet.aCnt     = BSP_UART_EDMA3CC_PARAM_ACNT;
    paramSet.linkAddr = BSP_UART_EDMA3CC_PARAM_LINK_ADDRESS;
    paramSet.opt     &= ~((UInt32) BSP_UART_EDMA3CC_OPT_SYNC_A <<
                           BSP_UART_EDMA3CC_OPT_SYNCDIM_SHIFT);

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the PaRAM Set.                                          */
        retVal = EDMA3_DRV_setPaRAM((EDMA3_DRV_Handle) chanHandle->hEdma,
                                    (UInt32) chanHandle->edmaLinkChId,
                                    &paramSet);
    }

    if (IOM_COMPLETED == retVal)
    {
        retVal = EDMA3_DRV_linkChannel((EDMA3_DRV_Handle) chanHandle->hEdma,
                                       (UInt32) chanHandle->edmaChId,
                                       (UInt32) chanHandle->edmaLinkChId);
    }

    if (IOM_COMPLETED == retVal)
    {
        UInt32 lineStatus, isTxFifoEmpty = FALSE, fifoLevel;
        UInt32 edmaStatus = 0U, isEdmaEventPending = FALSE;

        /* Get TX FIFO status - This should be before EDMA status */
        lineStatus = (UInt32)
            UARTReadStatus((UInt32) instHandle->deviceInfo.baseAddress);
        if ((UInt32) UART_LSR_TX_FIFO_E_MASK ==
           (lineStatus & (UInt32) UART_LSR_TX_FIFO_E_MASK))
        {
            isTxFifoEmpty = (UInt32) TRUE;
        }

        /* In FIFO mode, DMA events are generated as soon as there are
         * TX threshold level bytes become free in the FIFO. Hence it is
         * required to check the FIFO level as well in order to check if
         * DMA events are consumed */
        fifoLevel =
            UARTTxFIFOLevelGet((UInt32) instHandle->deviceInfo.baseAddress);
        if (TRUE == instHandle->devParams.fifoEnable)
        {
            if (fifoLevel <=
               ((UInt32) BSP_UART_FIFO_SIZE -
               instHandle->devParams.txThreshold))
            {
                isTxFifoEmpty = (UInt32) TRUE;
            }
        }
        else
        {
            /* Incase of FIFO disable, FIFO size is 1. So for FIFO empty,
             * check for zero */
            if (0U == fifoLevel)
            {
                isTxFifoEmpty = (UInt32) TRUE;
            }
        }

        /* Get EDMA event pending status */
        edmaRetVal = EDMA3_DRV_getChannelStatus(
                            (EDMA3_DRV_Handle) hEdma,
                            (UInt32) chanHandle->edmaChId,
                            &edmaStatus);
        if (edmaRetVal != ((Int32) EDMA3_DRV_SOK))
        {
            retVal = IOM_EBADARGS;
        }
        if ((UInt32) EDMA3_DRV_CHANNEL_EVENT_PENDING ==
                (edmaStatus & ((UInt32) EDMA3_DRV_CHANNEL_EVENT_PENDING)))
        {
            isEdmaEventPending = (UInt32) TRUE;
        }

        /* Note: Getting the FIFO status and EDMA event pend should be
         * done prior to enabling the EDMA channel */
        edmaRetVal = EDMA3_DRV_enableTransfer(
                        (EDMA3_DRV_Handle) hEdma,
                        (UInt32) chanHandle->edmaChId,
                        (EDMA3_DRV_TrigMode) EDMA3_DRV_TRIG_MODE_EVENT);
        if (edmaRetVal != ((Int32) EDMA3_DRV_SOK))
        {
            retVal = IOM_EBADARGS;
        }

        /* Workaround: In case of DMA mode, the UART IP generates the
         * next EDMA event as soon as the FIFO gets emptied or when there are
         * TX threshold level bytes free in FIFO. In the EDMA ISR,
         * the DMA mode is disabled and EDMA channel is disabled.
         * There is a race condition between software (CPU) disabling the DMA
         * mode and the UART IP generating the DMA event to EDMA.
         *
         * In cases when the software is slower (multi-tasking systems or
         * in heavily CPU loaded systems or for lower FIFO trigger levels),
         * the UART IP DMA event gets generated before the CPU could disable
         * the DMA event generation.
         *
         * When this happens, since the EDMA channel is enabled, the EDMA will
         * acknowledge the EDMA event but it doesn't have proper param set to
         * do the actual transfer to the UART FIFO. Hence the event gets lost
         * and the UART IP doesn't generate the next EDMA event unless the FIFO
         * is written. This becomes a deadlock!!
         *
         * To break the dead lock, first we need to identify whether this had
         * happened by checking the UART FIFO level and the EDMA channel status.
         * As per UART IP, in DMA mode, when ever the FIFO is empty or has TX
         * threshold amount of free space it should have raised an DMA event.
         * Hence we check if the UART FIFO has room and see if the event is
         * latched in the EDMA register.
         * So if FIFO is empty and event is not latched, then we are in a
         * deadlock.
         *
         * To recover from the deadlock, we do a manual trigger for the first
         * time and the rest of the transfer is taken care automatically
         * by further UART events.
         */
        if (((UInt32) TRUE == isTxFifoEmpty) &&
            ((UInt32) FALSE == isEdmaEventPending))
        {
            edmaRetVal = EDMA3_DRV_enableTransfer(
                            (EDMA3_DRV_Handle) hEdma,
                            (UInt32) chanHandle->edmaChId,
                            (EDMA3_DRV_TrigMode) EDMA3_DRV_TRIG_MODE_MANUAL);
            if (edmaRetVal != ((Int32) EDMA3_DRV_SOK))
            {
                retVal = IOM_EBADARGS;
            }
        }
    }
}

/* ========================================================================== */
/*                            END OF FILE                                     */
/* ========================================================================== */
