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
 *  \file   bsp_mcspiEdma.c
 *
 *  \brief  This files contains the edma functions required for the Mcspi driver
 *          to function in the EDMA mode.
 *
 *  \version   0.1 Created for DM814x/C6A811x platform.
 */

/* ========================================================================== */
/*                             INCLUDE FILES                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <assert.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/hal/Cache.h>
#include <xdc/runtime/System.h>

#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <bsp_mcspiPriv.h>
#include <ti/csl/csl_mcspi.h>
#include <ti/csl/soc.h>
#include <ti/sdo/edma3/drv/src/edma3.h>

/* ========================================================================== */
/*                         LOCAL FUNCTION PROTOTYPES                          */
/* ========================================================================== */
static Void mcspiUpdateError(const Mcspi_ChanObj *chanHandle, UInt32 intStatus);

/* ========================================================================== */
/*                          FUNCTION DEFINITIONS                              */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static Void doNothing(Uns tcc, EDMA3_RM_TccStatus edmaStatus, Ptr appData);
#ifdef __cplusplus
}
#endif
/* Edma dummy function*/
static Void doNothing(Uns tcc, EDMA3_RM_TccStatus edmaStatus, Ptr appData)
{
    /* DO NOTHING (This is a callback for the dummy transfer)                 */
}

/**
 *  \brief  This function is called during channel creation (during open)
 *          This function does the following
 *          1) Request the Xfer (in/out depends on mode) channel to EDMA
 *             driver for this peripheral;
 *          2) Requests the link channels for linking (exclusive for each
 *             direction (tx/rx)
 *
 *  \param  chanHandle  [IN]  pointer to the channel object
 *  \param  eb          [OUT] pointer to error block
 *
 *  \return  status     IOM_COMPLETED if is sucess
 *                      error id in case of failure
 *
 *  \entry   chanHandle  should be non NULL and valid pointer
 *
 *  \leave   Not implemented
 */
Int32 Mcspi_localSetupEdmaDuringOpen(Mcspi_ChanObj *chanHandle)
{
    static UInt32       dummyParamSetAddr;
    UInt32              reqTcc      = EDMA3_DRV_TCC_ANY;
    EDMA3_RM_EventQueue queueNum    = 0;
    UInt32              linkCnt     = 0;
    UInt32              edmaChanNum = 0;
    UInt32              count       = 0;
    Int32 status = IOM_COMPLETED;

    assert(NULL != chanHandle);

/****************************** RX Section ************************************/

    /* For receive use EDMA Queue 1 and for transmit use EDMA queue 0     */
    queueNum = (EDMA3_RM_EventQueue) MCSPI_RXEVENTQUE;

    status = EDMA3_DRV_requestChannel(
        (EDMA3_DRV_Handle) chanHandle->hEdma,
        &(chanHandle->rxDmaEventNumber),
        &(chanHandle->rxDmaEventNumber),
        queueNum,
        &Mcspi_localCallbackReceive,
        chanHandle);

    if (IOM_COMPLETED != status)
    {
        /* Reutn to application with bad args. */
        status = IOM_EBADARGS;
    }
    if (IOM_COMPLETED == status)
    {
        /* Continue only when the above request channel is successful.
         * Otherwise error status is returned to application. */
        /* Acquire the  PaRAM entries used for EDMA transfers linking. */
        for (count = 0; count < MCSPI_MAXLINKCNT; count++)
        {
            /* For requesting for a PaRam set
             *                                  */
            edmaChanNum = EDMA3_DRV_LINK_CHANNEL;
            reqTcc      = EDMA3_DRV_TCC_ANY;

            status = EDMA3_DRV_requestChannel(
                (EDMA3_DRV_Handle) chanHandle->hEdma,
                &edmaChanNum,
                &reqTcc,
                queueNum,
                &Mcspi_localCallbackReceive,
                NULL);

            if (IOM_COMPLETED == status)
            {
                chanHandle->pramTblRx[count] = edmaChanNum;

                status = EDMA3_DRV_getPaRAMPhyAddr(
                    (EDMA3_DRV_Handle) chanHandle->hEdma,
                    chanHandle->pramTblRx[count],
                    &(chanHandle->pramTblAddrRx[count]));
            }

            if (IOM_COMPLETED != status)
            {
                /* free the Synchonized EDMA channel
                 *                           */
                EDMA3_DRV_freeChannel(
                    (EDMA3_DRV_Handle) chanHandle->hEdma,
                    chanHandle->rxDmaEventNumber);

                /* free the already allocated PaRAM entries
                 *                    */
                for (linkCnt = 0; linkCnt < count; linkCnt++)
                {
                    EDMA3_DRV_freeChannel(
                        (EDMA3_DRV_Handle) chanHandle->hEdma,
                        chanHandle->pramTblRx[linkCnt]);
                }

                status = IOM_EBADARGS;
                break;
            }
        }
    }
/********************************* TX Section *********************************/

    if (IOM_COMPLETED == status)
    {
        queueNum = (EDMA3_RM_EventQueue) MCSPI_TXEVENTQUE;

        status = EDMA3_DRV_requestChannel(
            (EDMA3_DRV_Handle) chanHandle->hEdma,
            &(chanHandle->txDmaEventNumber),
            &(chanHandle->txDmaEventNumber),
            queueNum,
            &Mcspi_localCallbackTransmit,
            chanHandle);
    }
    if (IOM_COMPLETED != status)
    {
        /* Reutn to application with bad args. */
        status = IOM_EBADARGS;
    }

    if (IOM_COMPLETED == status)
    {
        /* Continue only when the above request channel is successful.
         * Otherwise error status is returned to application. */
        /* Acquire the  PaRAM entries used for EDMA transfers linking. */
        Mcspi_edmaChanNum[chanHandle->chanNum] = EDMA3_DRV_LINK_CHANNEL;
        reqTcc = EDMA3_DRV_TCC_ANY;

        status = EDMA3_DRV_requestChannel(
            chanHandle->hEdma,
            &Mcspi_edmaChanNum[chanHandle->chanNum],
            &reqTcc,
            queueNum,
            &doNothing,
            NULL);

        if (IOM_COMPLETED == status)
        {
            status = EDMA3_DRV_getPaRAMPhyAddr(
                chanHandle->hEdma,
                Mcspi_edmaChanNum[chanHandle->chanNum],
                &dummyParamSetAddr);
        }

        if (IOM_COMPLETED != status)
        {
            /* free the already allocated PaRAM entries
             *                    */
            EDMA3_DRV_freeChannel(chanHandle->hEdma,
                                  Mcspi_edmaChanNum[chanHandle->chanNum]);
            status = IOM_EBADARGS;
        }

        if (IOM_COMPLETED != status)
        {
            status = IOM_EBADARGS;
        }

        if (IOM_COMPLETED == status)
        {
            /* Acquire the  PaRAM entries used for EDMA transfers linking     */
            for (count = 0; count < MCSPI_MAXLINKCNT; count++)
            {
                /* For requesting for a PaRam set                             */
                edmaChanNum = EDMA3_DRV_LINK_CHANNEL;
                reqTcc      = EDMA3_DRV_TCC_ANY;

                status = EDMA3_DRV_requestChannel(
                    (EDMA3_DRV_Handle) chanHandle->hEdma,
                    &edmaChanNum,
                    &reqTcc,
                    queueNum,
                    &Mcspi_localCallbackTransmit,
                    NULL);

                if (IOM_COMPLETED == status)
                {
                    chanHandle->pramTblTx[count] = edmaChanNum;

                    status = EDMA3_DRV_getPaRAMPhyAddr(
                        (EDMA3_DRV_Handle) chanHandle->hEdma,
                        chanHandle->pramTblTx[count],
                        &(chanHandle->pramTblAddrTx[count]));
                }

                if (IOM_COMPLETED != status)
                {
                    /* free the Synchonized EDMA channel                      */
                    EDMA3_DRV_freeChannel(
                        (EDMA3_DRV_Handle) chanHandle->hEdma,
                        chanHandle->txDmaEventNumber);

                    /* free the already allocated PaRAM entries               */
                    for (linkCnt = 0; linkCnt < count; linkCnt++)
                    {
                        EDMA3_DRV_freeChannel(
                            (EDMA3_DRV_Handle) chanHandle->hEdma,
                            chanHandle->pramTblTx[linkCnt]);
                    }
                    status = IOM_EBADARGS;
                    break;
                }
            }
        }
    }

    return status;
}

/**
 *  \brief  This function is called in response to the completion of transmit.
 *          This is the Callback for the EDMA transmit completion event.
 *          Tx channel transfer for Edma is disable done here.
 *
 *  \param  tcc         [IN]   Transmit interrupt event channel
 *  \param  edmaStatus  [IN]   Transfer status whether transfer completed or not
 *  \param  appData     [IN]   Data passed Edma during initiation
 *
 */
Void Mcspi_localCallbackTransmit(UInt               tcc,
                                 EDMA3_RM_TccStatus edmaStatus,
                                 Ptr                appData)
{
    Mcspi_Object  *instHandle     = NULL;
    Mcspi_ChanObj *chanHandle     = NULL;
    static Void   *tx_edma_handle = NULL;
    UInt32         hwiKey         = 0x00;
    UInt           ch_Tx          = tcc;

    hwiKey = (UInt32) Hwi_disable();

    assert(NULL != appData);

    chanHandle = (Mcspi_ChanObj *) appData;
    assert(NULL != chanHandle);

    assert(NULL != chanHandle->instHandle);

    instHandle = (Mcspi_Object *) chanHandle->instHandle;

    tx_edma_handle = chanHandle->hEdma;
    assert(NULL != tx_edma_handle);

    if (edmaStatus != EDMA3_RM_XFER_COMPLETE)
    {
        /* Error interrupt cannot be aVoided because the SPI re-sends event to
         * the EDMA after last byte has been transferred, and software cannot
         * disable the channel before this happens.
         */
        EDMA3_DRV_clearErrorBits((EDMA3_DRV_Handle) tx_edma_handle,
                                 (UInt32) ch_Tx);

        chanHandle->currentPacketErrorStatus = IOM_EABORT;
    }
    else
    {
        chanHandle->currentPacketErrorStatus = IOM_COMPLETED;
    }
    /* EDMA Rx is done disable the Rx DMA channel */
    EDMA3_DRV_disableTransfer(
        tx_edma_handle,
        ch_Tx,
        EDMA3_DRV_TRIG_MODE_EVENT);
    /* clear the error bits in the EDMA(as this is the last packet)   */
    EDMA3_DRV_clearErrorBits((EDMA3_DRV_Handle) tx_edma_handle,
                             (UInt32) ch_Tx);

    if (MCSPI_RX_EDMA_CALLBACK_OCCURED == chanHandle->edmaCbCheck)
    {
        UInt32 intStatus = 0x00;

        chanHandle->edmaCbCheck = 0x0;

        intStatus = McSPIChannelStatusGet(
            (UInt32) instHandle->deviceInfo.baseAddress,
            chanHandle->chanNum);
        mcspiUpdateError(chanHandle, intStatus);

        Mcspi_localCompleteIOedmaCbk(instHandle);
    }
    else
    {
        if (EDMA3_RM_XFER_COMPLETE == edmaStatus)
        {
            chanHandle->edmaCbCheck = MCSPI_TX_EDMA_CALLBACK_OCCURED;
        }
    }

    /* end the critical section
     *                                                */
    Hwi_restore(hwiKey);
}

/**
 *  \brief  This function is called in response to the completion of receive.
 *          This is the Callback for the EDMA receive completion event.
 *          Rx channel transfer for Edma is disable done here.
 *
 *  \param  tcc         [IN]    receive interrupt event channel
 *  \param  edmaStatus  [IN]    receive status whether transfer completed or not
 *  \param  appData     [IN]    Data passed Edma during initiation
 *
 */
Void Mcspi_localCallbackReceive(UInt               tcc,
                                EDMA3_RM_TccStatus edmaStatus,
                                Ptr                appData)
{
    Mcspi_Object *instHandle = NULL;
    Mcspi_ChanObj           *chanHandle = NULL;
    Uns           chan_Rx = (Uns) tcc;
    UInt32        hwiKey  = 0x00;
    static Void  *rx_edma_handle;

    /* complete the receive IOP now
     *                                            */
    hwiKey = (UInt32) Hwi_disable();

    assert(NULL != appData);

    chanHandle     = (Mcspi_ChanObj *) appData;
    instHandle     = (Mcspi_Object *) chanHandle->instHandle;
    rx_edma_handle = chanHandle->hEdma;

    assert(NULL != appData);

    chanHandle = (Mcspi_ChanObj *) appData;
    assert(NULL != chanHandle);
    instHandle = (Mcspi_Object *) chanHandle->instHandle;
    assert(NULL != instHandle);

    if (edmaStatus != EDMA3_RM_XFER_COMPLETE)
    {
        /* Error interrupt cannot be avoided because the SPI re-sends event to
         * the EDMA after last byte has been transferred, and software cannot
         * disable the channel before this happens.
         */
        EDMA3_DRV_clearErrorBits((EDMA3_DRV_Handle) rx_edma_handle,
                                 (UInt32) chan_Rx);

        chanHandle->currentPacketErrorStatus = IOM_EABORT;
    }
    else
    {
        chanHandle->currentPacketErrorStatus = IOM_COMPLETED;
    }
    /* EDMA Rx is done disable the Rx DMA channel */
    EDMA3_DRV_disableTransfer(
        rx_edma_handle,
        chan_Rx,
        EDMA3_DRV_TRIG_MODE_EVENT);
    /* clear the error bits in the EDMA(as this is the last packet)   */
    EDMA3_DRV_clearErrorBits((EDMA3_DRV_Handle) rx_edma_handle,
                             (UInt32) chan_Rx);

    if (MCSPI_TX_EDMA_CALLBACK_OCCURED == chanHandle->edmaCbCheck)
    {
        /* Now Both Tx and Rx EDMA Callbacks have happened */
        Uint32 intStatus = 0x00;

        chanHandle->edmaCbCheck = 0x0;

        intStatus = McSPIChannelStatusGet(
            (UInt32) instHandle->deviceInfo.baseAddress,
            chanHandle->chanNum);

        mcspiUpdateError(chanHandle, intStatus);

        Mcspi_localCompleteIOedmaCbk(instHandle);
    }
    else
    {
        if (EDMA3_RM_XFER_COMPLETE == edmaStatus)
        {
            chanHandle->edmaCbCheck = MCSPI_RX_EDMA_CALLBACK_OCCURED;
        }
    }

    /* end the critical section
     *                                                */
    Hwi_restore(hwiKey);
}

/**
 *  \brief Function used after edma callback
 *
 *  This function will be called after the completion of edma callback. This
 *  function requests the next channel and also calls the app callback
 *  function.
 *
 *  \param   instHandle  [IN]   Pointer to the spi driver instance object
 *
 *  \return  None
 *
 *  \enter  instHandle must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
Void Mcspi_localCompleteIOedmaCbk(Mcspi_Object *instHandle)
{
    Mcspi_ChanObj *chanHandle = NULL;
    IOM_Packet    *ioPacket   = NULL;
    UInt32         hwiKey     = 0;

    assert(NULL != instHandle);

    chanHandle = instHandle->currentActiveChannel;
    assert(NULL != chanHandle);

    /* disable all the spi transfers                                          */
    McSPIChannelDisable((UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
    /* Clear all the interrupts here, only related to the perticular
     * channel
     */
    mcspiChIntrStatClear(instHandle, chanHandle);
    /* call the application completion callback function registered
     * with us during opening of the channel
     */
    if (TRUE == chanHandle->spiChipSelectHold)
    {
        McSPICSDeAssert(instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
    }
    /* In Case If the FIFO is not used word count is not set.
     * when the receive Callback of McSPI comes Tx would be empty and generate
     * another EDMA event. Hense transfer is disabled on both Tx and Rx.
     * This will ensure EDMA state is proper for next transfer */
    EDMA3_DRV_disableTransfer(
        chanHandle->hEdma,
        chanHandle->txDmaEventNumber,
        EDMA3_DRV_TRIG_MODE_EVENT);
    EDMA3_DRV_disableTransfer(
        chanHandle->hEdma,
        chanHandle->rxDmaEventNumber,
        EDMA3_DRV_TRIG_MODE_EVENT);

    if (NULL != chanHandle->cbFxn)
    {
        if (TRUE == chanHandle->txBufFlag)
        {
            chanHandle->activeIOP->size -= chanHandle->txBufferLen;
        }
        else
        {
            chanHandle->activeIOP->size -= chanHandle->rxBufferLen;
        }

        /* power off the module                                               */
        Mcspi_localPrcmOff(instHandle, NULL);

        if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg))
        {
            /* Invoke Application callback for this channel
             *                    */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, chanHandle->activeIOP);
        }
    }
    /* There is no transaction for now.It will be set again when actual
     * transaction is to be started.
     */

    chanHandle->pendingState = (Bool) FALSE;
    chanHandle->activeIOP    = NULL;
    chanHandle->currError    = 0;
    /* Check if the abort flag is set for this channel. If set, we need to
     * remove all (empty) the pending packets from the list and send it back
     * to the upper layer. We do it here because, the packets should be dealt
     * with  in FIFO order
     */
    if (TRUE == chanHandle->abortAllIo)
    {
        while (FALSE == Queue_empty(Queue_handle(&(
                                                     chanHandle->
                                                     queuePendingList))))
        {
            /* we have atleast one packet                                     */
            ioPacket = (IOM_Packet *) Queue_get(
                Queue_handle(&(chanHandle->queuePendingList)));

            if (NULL != ioPacket)
            {
                ioPacket->status = IOM_ABORT;
                ioPacket->size   = 0;

                /* power off the module                                       */
                Mcspi_localPrcmOff(instHandle, NULL);

                /* Invoke Application callback for this channel               */
                if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg))
                {
                    (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
                }

                instHandle->stats.pendingPacket--;
            }
        }
        chanHandle->abortAllIo = (Bool) FALSE;
    }
    else
    {
        /* Initiate next transfer if any in pending queue */
        /* start the critical section                                         */
        hwiKey = (UInt32) Hwi_disable();
        /* If pending queue is empty no other IOPs disable interrupt */
        if ((Bool) TRUE ==
            Queue_empty(Queue_handle(&chanHandle->queuePendingList)))
        {
            /* No transfer pending on Current instance */
            instHandle->currentActiveChannel = NULL;
            /* End critical section */
            Hwi_restore(hwiKey);
        }
        else
        {
            /* Get next IO packet and end interrupt */
            ioPacket = (IOM_Packet *)
                       Queue_get(Queue_handle(&(chanHandle->queuePendingList)));
            Hwi_restore(hwiKey);
            mcspiEdmaModeTransfer(instHandle, chanHandle,
                                  ioPacket);
        }
    }
}

/*!
 *  \brief  This function updates the link param set accordingly with data or
 *          loopjobbuffer. This uses properly maintained index to idendtify to
 *          what param set the info has to be updated.
 *
 *  \param  chanHandle  [IN]  Handle to the mcasp channel
 *  \param  ioPacket    [IN]  Pointer to I/O packet
 *
 *  \return IOM_COMPLETED in case of sucess
 *          else Error code in case of failure
 *
 *  \entry  chanHandle  should be non NULL and valid pointer
 *          ioPacket    shoudl be non NULL and valid pointer
 *
 *  \leave  Not implemented
 */
Int32 Mcspi_localUpdtDtPktToLnkPrms(Mcspi_ChanObj    *chanHandle,
                                    const IOM_Packet *ioPacket)
{
    Mcspi_Object       *instHandle    = NULL;
    EDMA3_DRV_PaRAMRegs rxParamSet    = {0};
    EDMA3_DRV_PaRAMRegs txParamSet    = {0};
    EDMA3_DRV_PaRAMRegs dummyParamSet = {0};
    Int32 status = IOM_COMPLETED;

    assert(NULL != chanHandle);

    assert(NULL != chanHandle->instHandle);

    instHandle = (Mcspi_Object *) chanHandle->instHandle;

    assert(NULL != instHandle);

    status = EDMA3_DRV_getPaRAM(
        (EDMA3_DRV_Handle) chanHandle->hEdma,
        chanHandle->rxDmaEventNumber,
        &rxParamSet);
    if (IOM_COMPLETED == status)
    {
        status = EDMA3_DRV_getPaRAM(
            (EDMA3_DRV_Handle) chanHandle->hEdma,
            chanHandle->txDmaEventNumber,
            &txParamSet);
    }
    if (IOM_COMPLETED != status)
    {
        status = IOM_EBADARGS;
    }

    /* control will reach this function in two contexts                   *
     *  1) From submitreq function for first time packets                 *
     *  2) From EDMA callback for further handling of packets in Queue    *
     *  -we are from EDMA callback becuase we have completed some user    *
     *  data packet just now                                              */
    if ((NULL != ioPacket) && (IOM_COMPLETED == status))
    {
        /* 1) when control comes to this function from submitreq control  *
         *    will surely come into the block                             *
         * 2) When control comes to this function from EDMA callback,     *
         *    control will come only if there is fuirther more packets to *
         *    handle                                                      */

        status = Mcspi_localEdmaUpdateParams(chanHandle,
                                             &rxParamSet,
                                             &txParamSet);
        if (IOM_COMPLETED != status)
        {
            status = IOM_EBADIO;
        }
    }
    else
    {
        status = IOM_EBADARGS;
    }
    if (IOM_COMPLETED == status)
    {
        /* Dummy paramSet Configuration */
        status = EDMA3_DRV_getPaRAM(chanHandle->hEdma,
                                    Mcspi_edmaChanNum[chanHandle->chanNum],
                                    &dummyParamSet);

        dummyParamSet.aCnt     = MCSPI_EDMA3CC_PARAM_ACNT;
        dummyParamSet.linkAddr = MCSPI_EDMA3CC_PARAM_LINK_ADDRESS;
        dummyParamSet.opt     &=
            ~((UInt32) 0x01U << MCSPI_EDMA3CC_OPT_STATIC_SHIFT);
    }
    if (IOM_COMPLETED != status)
    {
        status = IOM_EBADARGS;
    }
    if (IOM_COMPLETED == status)
    {
        /* Now, write the PaRAM Set.                            */
        status = EDMA3_DRV_setPaRAM(chanHandle->hEdma,
                                    Mcspi_edmaChanNum[chanHandle->chanNum],
                                    &dummyParamSet);

        status = EDMA3_DRV_setPaRAM(
            (EDMA3_DRV_Handle) chanHandle->hEdma,
            chanHandle->rxDmaEventNumber,
            &rxParamSet);
        if (IOM_COMPLETED == status)
        {
            status = EDMA3_DRV_setPaRAM(
                (EDMA3_DRV_Handle) chanHandle->hEdma,
                chanHandle->txDmaEventNumber,
                &txParamSet);
        }
        if (IOM_COMPLETED == status)
        {
            /* Link the Dummy paramset */
            status = EDMA3_DRV_linkChannel(chanHandle->hEdma,
                                           chanHandle->txDmaEventNumber,
                                           Mcspi_edmaChanNum[chanHandle->
                                                             chanNum]);
        }
        if (IOM_COMPLETED != status)
        {
            status = IOM_EBADIO;
        }
    }

    return status;
}

/**
 *  \brief  Mcspi_localEdmaUpdateParams
 *
 *  This function computes the parameters requied to configure EDMA 3 based
 *  on the buffer format seleted while creating the driver.
 *
 *  Entry Criteria : This function expects channel variables such as no of slots
 *                     serializers, length of buffers is updated.
 *
 *  \param    chanHandle       [IN]    Pointer to channel handle
 *  \param    rxParamSet       [IN]    Pointer to store RX PaRAMSET
 *  \param    txParamSet       [IN]    Pointer to store TX PaRAMSET
 *
 * CAUTION : This function could be called with pointer pointing to EDMA3
 *           paramset pointer (avoiding couple of variables). Care should be
 *           take to ensure that data types used in EDMA 3 paramset is
 *           consistent with EDMA 3 defined data types.
 *
 *  \return  IOM_EBADIO for invalid parameters, else IOM_COMPLETED
 */

Int32 Mcspi_localEdmaUpdateParams(Mcspi_ChanObj       *chanHandle,
                                  EDMA3_DRV_PaRAMRegs *rxParamSet,
                                  EDMA3_DRV_PaRAMRegs *txParamSet)
{
    Mcspi_Object *instHandle    = NULL;
    UInt32        acntFlag      = 1U;
    Int32         status        = IOM_COMPLETED;
    UInt16        tempRxTrigLvl = 0;
    UInt16        tempTxTrigLvl = 0;

    assert(NULL != chanHandle);

    instHandle    = (Mcspi_Object *) chanHandle->instHandle;
    tempRxTrigLvl = instHandle->spiHWconfig.fifoRxTrigLvl;
    tempTxTrigLvl = instHandle->spiHWconfig.fifoTxTrigLvl;

/*************************************************************************/

    /* check the number of bytes to be transferred per sync event        */
    if (chanHandle->cfgChfmt.charLength <= 8)
    {
        acntFlag = 1U;
        if ((FALSE == chanHandle->fifoEnable) || (tempRxTrigLvl < (UInt16) 1))
        {
            tempRxTrigLvl = (UInt16) 1;
        }
        if ((FALSE == chanHandle->fifoEnable) || (tempTxTrigLvl < (UInt16) 1))
        {
            tempTxTrigLvl = (UInt16) 1;
        }
    }
    else if (chanHandle->cfgChfmt.charLength <= 16)
    {
        acntFlag = 2U;
        if ((FALSE == chanHandle->fifoEnable) || (tempRxTrigLvl < (UInt16) 2))
        {
            tempRxTrigLvl = (UInt16) 2;
        }
        tempRxTrigLvl = tempRxTrigLvl / (UInt16) 2;
        if ((FALSE == chanHandle->fifoEnable) || (tempTxTrigLvl < (UInt16) 2))
        {
            tempTxTrigLvl = (UInt16) 2;
        }
        tempTxTrigLvl = tempTxTrigLvl / (UInt16) 2;
    }
    else if (chanHandle->cfgChfmt.charLength <= 32)
    {
        acntFlag = 4U;
        if ((FALSE == chanHandle->fifoEnable) || (tempRxTrigLvl < (UInt16) 4))
        {
            tempRxTrigLvl = (UInt16) 4;
        }
        if ((FALSE == chanHandle->fifoEnable) || (tempTxTrigLvl < (UInt16) 4))
        {
            tempTxTrigLvl = (UInt16) 4;
        }
        tempRxTrigLvl = tempRxTrigLvl / (UInt16) 4;
        tempTxTrigLvl = tempTxTrigLvl / (UInt16) 4;
    }
    else
    {
        /* Never comes here                                              */
    }

    if ((TRUE == chanHandle->rxBufFlag) &&
        (TRUE == instHandle->enableCache))
    {
        /* Read intialization for DMA mode                               */
        Cache_wbInv((Ptr) chanHandle->rxBuffer,
                    chanHandle->rxBufferLen,
                    Cache_Type_ALL,
                    (Bool) TRUE);
    }

    /* Configure the source and destination address
     * The FIFO address (src address) needs to be mentioned here
     */
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    rxParamSet->srcAddr = instHandle->deviceInfo.baseAddress +
                          MCSPI_CHRX(chanHandle->chanNum);
#else
    rxParamSet->srcAddr = instHandle->deviceInfo.baseAddress +
                          MCSPI_CHRX(chanHandle->chanNum) +
                          (UInt32) MCSPI_EDMA_BASE_ADDR;
#endif
    rxParamSet->destAddr = (UInt32) chanHandle->rxBuffer;

    /* configure the source and destination indexes                      */
    rxParamSet->srcBIdx  = (UInt16) 0;
    rxParamSet->srcCIdx  = (UInt16) 0;
    rxParamSet->destCIdx = (UInt16) (tempRxTrigLvl * acntFlag);
    rxParamSet->destBIdx = (UInt16) acntFlag;

    /* Configuring aCnt, bCnt, cCnt and bCntReload                       */
    rxParamSet->aCnt = (UInt16) acntFlag;
    rxParamSet->bCnt = (UInt16) tempRxTrigLvl;
    rxParamSet->cCnt = (UInt16) (chanHandle->rxBufferLen /
                                 ((rxParamSet->aCnt) * (rxParamSet->bCnt)));
    rxParamSet->bCntReload = rxParamSet->bCnt;

    /* configure the OPT field of the EDMA paramset
     * Linking is disabled
     */
    rxParamSet->linkAddr = 0xFFFFU;

    /* By default SAM and DAM bits are set to INCR mode                  */
    rxParamSet->opt &= (UInt) 0xFFFFFFFCU;

    if (TRUE != chanHandle->rxBufFlag)
    {
        /* Since the EDMA is using the driver internal buffer, so no need to
         * increment the buffer. INCR mode is disabled
         */
        rxParamSet->opt |= (UInt) MCSPI_EDMA3CC_OPT_DAM_CONST_MODE;
    }

    /* FIFO width is 8 bit                                               */
    rxParamSet->opt &= (UInt) 0xFFFFF8FFU;

    /* EDMA3_DRV_SYNC_AB                                                 */
    rxParamSet->opt &= MCSPI_EDMA3CC_OPT_SYNC_MASK_VALUE;
    rxParamSet->opt |= MCSPI_EDMA3CC_OPT_SYNC_AB;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                       */
    rxParamSet->opt |= (UInt32) 1U << MCSPI_OPT_TCINTEN_SHIFT;

    /* update the transfer completion code                               */
    rxParamSet->opt &= (~MCSPI_OPT_TCC_MASK);
    rxParamSet->opt |= ((chanHandle->rxDmaEventNumber) <<
                        MCSPI_OPT_TCC_SHIFT);

/*************************************************************************/

    /* now update the paramset for the TX transfer channel               */
    if ((TRUE == chanHandle->txBufFlag) &&
        (TRUE == instHandle->enableCache))
    {
        /* Write intialization for DMA mode                              */
        Cache_wbInv((Ptr) chanHandle->txBuffer,
                    chanHandle->txBufferLen,
                    Cache_Type_ALL,
                    (Bool) TRUE);
    }

    /* configure the source and destination address
     * The FIFO address needs to be mentioned here - destination address
     */
    txParamSet->srcAddr = (UInt32) chanHandle->txBuffer;
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    txParamSet->destAddr = (UInt32) instHandle->deviceInfo.baseAddress +
                           MCSPI_CHTX(chanHandle->chanNum);
#else
    txParamSet->destAddr = (UInt32) instHandle->deviceInfo.baseAddress +
                           MCSPI_CHTX(chanHandle->chanNum) +
                           MCSPI_EDMA_BASE_ADDR;
#endif

    /* configure the source and destination indexes                      */
    txParamSet->srcBIdx  = acntFlag;
    txParamSet->srcCIdx  = (tempRxTrigLvl * acntFlag);
    txParamSet->destBIdx = 0;
    txParamSet->destCIdx = 0;

    /* Configuring aCnt, bCnt, cCnt and bCntReload                       */
    txParamSet->aCnt = (UInt16) acntFlag;
    txParamSet->bCnt = (UInt16) tempTxTrigLvl;
    txParamSet->cCnt = (UInt16) (chanHandle->txBufferLen /
                                 ((txParamSet->aCnt) * (txParamSet->bCnt)));
    txParamSet->bCntReload = txParamSet->bCnt;
    txParamSet->linkAddr   = MCSPI_EDMA3CC_PARAM_LINK_ADDRESS;

    /* By default SAM and DAM bits are set to INCR mode                  */
    txParamSet->opt &= MCSPI_EDMA3CC_OPT_SAM_DAM_INCR_MODE;

    if (TRUE != chanHandle->txBufFlag)
    {
        /* Since the EDMA is using the driver internal buffer, so no need to
         * increment the buffer. INCR mode is disabled.
         */
        txParamSet->opt |= (UInt) MCSPI_EDMA3CC_OPT_SAM_CONST_MODE;
    }

    /* FIFO width is 8 bit                                               */
    txParamSet->opt &= MCSPI_EDMA3CC_OPT_FIFO_WIDTH;

    /* EDMA3_DRV_SYNC_AB                                                 */
    txParamSet->opt &= MCSPI_EDMA3CC_OPT_SYNC_MASK_VALUE;
    txParamSet->opt |= MCSPI_EDMA3CC_OPT_SYNC_AB;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                       */
    txParamSet->opt |= ((UInt32) 1 << MCSPI_OPT_TCINTEN_SHIFT);

    /* update the transfer completion code                               */
    txParamSet->opt &= (~MCSPI_OPT_TCC_MASK);
    txParamSet->opt |= ((chanHandle->txDmaEventNumber) <<
                        MCSPI_OPT_TCC_SHIFT);

/*************************************************************************/

    return status;
}

/**
 * \brief    Function to set the appropriate error status for the channel
 *
 * \param    chanHandle   [IN]    pointer to channel object
 *
 * \return   None
 */
static Void mcspiUpdateError(const Mcspi_ChanObj *chanHandle,
                             UInt32               intStatus)
{
    Mcspi_Object *instHandle = NULL;

    assert(NULL != chanHandle);

    instHandle = (Mcspi_Object *) chanHandle->instHandle;
    assert(NULL != instHandle);

    /* check Timeout interrupt                                           */
    switch (chanHandle->chanNum)
    {
        case 0:

            if ((UInt32) MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK ==
                (intStatus & (UInt32) MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK))
            {
                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK);
                instHandle->stats.txUnderFlowError++;
            }

            /* rxo overflow is valid only in slave mode*/
            if ((MCSPI_COMMMODE_SLAVE ==
                 instHandle->spiHWconfig.masterOrSlave) &&
                ((UInt32) MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK ==
                 (intStatus & (UInt32) MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK)))
            {
                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK);
                instHandle->stats.rxOverFlowError++;
            }

            break;

        case 1:

            if ((UInt32) MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK ==
                (intStatus & (UInt32) MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK))
            {
                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK);
                instHandle->stats.txUnderFlowError++;
            }
            break;

        case 2:
            if ((UInt32) MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK ==
                (intStatus & (UInt32) MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK))
            {
                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK);
                instHandle->stats.txUnderFlowError++;
            }
            break;

        case 3:

            if ((UInt32) MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK ==
                (intStatus & (UInt32) MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK))
            {
                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK);
                instHandle->stats.txUnderFlowError++;
            }
            break;

        default:
            assert(FALSE);
            break;
    }
}

