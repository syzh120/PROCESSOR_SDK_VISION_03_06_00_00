/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file   bspdrv_ar12xxMcspiCfgPriv.c
 *
 *  \brief  This file contains function definitions used privately by the
 *          AR12xx Radar sensor driver for McSPI configuration.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bspdrv_ar12xxPriv.h>
#include <xdc/runtime/Error.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Num Bufs to be issued and reclaimed */
#define BSP_AR12XX_NUM_BUFS              (3U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief String identifiers for the McSPI driver names */
static char *gMcspiDriverNames[] =
{
    "/mcspi0",
    "/mcspi1",
    "/mcspi2",
    "/mcspi3"
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* MISRA.FUNC.NOPROT.CALL Rule 8.2 fix */
static inline void ti_sysbios_io_GIO_Params_init(ti_sysbios_io_GIO_Params *prms);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

rlComIfHdl_t Bsp_ar12xxSpiOpenCb(rlUInt8_t deviceIndex, UInt32 flags)
{
    Bsp_ar12xxRadarCommHandle commHndl =
        &gBspAr12xxObj.radarDevCommObj[deviceIndex];
    UInt32       mcSpiDevInstNum =
        gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].mcSpiDevInst;
    rlComIfHdl_t returnHandle    = NULL;
    static UInt32 fifoEnabled[BSP_AR12XX_NUM_MCSPI_INST] = {0U, 0U, 0U, 0U};

    if (mcSpiDevInstNum < BSP_AR12XX_NUM_MCSPI_INST)
    {
        Error_Block eb;
        Error_init(&eb);
        /*
         * Initialize channel attributes.
         */
        GIO_Params_init(&commHndl->mcspiIoPrms);

        /* Update the McSPI channel parameters */
        commHndl->mcspiChanParams.hEdma = gBspAr12xxObj.initPrmsCopy.
            devParams[deviceIndex].edmaHandle;
        commHndl->mcspiChanParams.chipSelTimeControl = MCSPI_CLK_CYCLE3;
        /* Fifo can be enabled for only one channel */
        if (fifoEnabled[mcSpiDevInstNum] == 0U)
        {
            commHndl->mcspiChanParams.fifoEnable         = (Bool) TRUE;
            fifoEnabled[mcSpiDevInstNum] = 1U;
        }
        else
        {
            commHndl->mcspiChanParams.fifoEnable         = (Bool) FALSE;
        }
        commHndl->mcspiChanParams.spiChipSelectHold  = (Bool) FALSE;
        commHndl->mcspiChanParams.chanNum = gBspAr12xxObj.initPrmsCopy.
            devParams[deviceIndex].mcspiChannel;

        /* If cross bar events are being used then make isCrossBarIntEn = TRUE
         * and
         * choose appropriate interrupt number to be mapped (assign it to
         * intNumToBeMapped)
         */
        /* Cross bar evt disabled */
        commHndl->mcspiChanParams.crossBarEvtParam.isCrossBarIntEn =
            (Bool) FALSE;
        /* Program an invalid value */
        commHndl->mcspiChanParams.crossBarEvtParam.intNumToBeMapped = 0xFF;

        commHndl->mcspiIoPrms.chanParams = (Ptr) & commHndl->mcspiChanParams;
        commHndl->mcspiIoPrms.model      = GIO_Model_ISSUERECLAIM;
        commHndl->mcspiIoPrms.numPackets = BSP_AR12XX_NUM_BUFS + 1U;

        commHndl->deviceIdx = (UInt32) deviceIndex;

        commHndl->mcspiHandle = (GIO_Handle) GIO_create(
            (xdc_String) gMcspiDriverNames[mcSpiDevInstNum], (UInt32) GIO_INOUT,
            &commHndl->mcspiIoPrms, &eb);
        if (commHndl->mcspiHandle == NULL)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      " AR12XX: McSPI GIO Create Failed!!\r\n");
        }
        returnHandle = (rlComIfHdl_t) commHndl;
    }
    else
    {
        /* Should ideally not reach here as the check is done earlier inBuffer
         * #Bsp_ar12xxCheckInitParams function.
         */
        returnHandle = NULL;
    }
    return returnHandle;
}

Int32 Bsp_ar12xxSpiCloseCb(rlComIfHdl_t fd)
{
    Bsp_ar12xxRadarCommHandle commHndl = (Bsp_ar12xxRadarCommHandle) fd;
    GIO_delete((GIO_Handle *) &commHndl->mcspiHandle);
    return BSP_SOK;
}

Int32 Bsp_ar12xxSpiReadCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len)
{
    UInt32                    size             = 0U;
    Int                       status           = IOM_COMPLETED;
    Mcspi_DataParam           issueDataparam   = {0};
    Mcspi_DataParam           reclaimDataparam = {0};
    Ptr                       pReclaimDataParam;
    Int32                     retVal   = BSP_SOK;
    Bsp_ar12xxRadarCommHandle commHndl = (Bsp_ar12xxRadarCommHandle) fd;
    Mcspi_FifoTrigLvl         fifoLevel;

    issueDataparam.inBuffer = (UInt8 *) pBuff;
    issueDataparam.bufLen   = (UInt32) len;
    if ((UInt32)len > 0x1000U)
    {
        /* Something is wrong if this condition is met */
        GT_1trace(BspAppTrace, GT_ERR,
                  " AR12XX: Too large read requested!! Length = %x\r\n",
                  (UInt32)len);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        if (len < MCSPI_RX_FIFO_LEN)
        {
             fifoLevel.rxTriggerLvl = len;
             fifoLevel.txTriggerLvl = len;
        }
        else
        {
             fifoLevel.rxTriggerLvl = MCSPI_RX_FIFO_LEN;
             fifoLevel.txTriggerLvl = MCSPI_TX_FIFO_LEN;
        }
        issueDataparam.outBuffer = NULL;
        size = (UInt32)len;

        status = GIO_control(commHndl->mcspiHandle, IOCTL_MCSPI_SET_TRIGGER_LVL,
                             &fifoLevel);
        if (IOM_COMPLETED == status)
        {
            /* Issue the first & second empty buffers to the input stream */
            status = GIO_issue(commHndl->mcspiHandle, &issueDataparam, size,
                           NULL);
        }

        if ((status != IOM_PENDING) && (status != IOM_COMPLETED))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      " AR12XX: Failed to issue empty buffer to stream!!\r\n");
        }
        /* Reclaim is done after every issue and buffers are not primed. If
         * the buffers are primed next transfer is initialized as soon as
         * the first one is completed. We wont be able to ensure transfer
         * initializaton on Slave before master for second buffer
         */
        pReclaimDataParam = (Ptr) & reclaimDataparam;
        status =
            GIO_reclaim((GIO_Object *) commHndl->mcspiHandle,
                        (Ptr *) &pReclaimDataParam,
                        NULL,
                        NULL);
        if (IOM_COMPLETED != status)
        {
            GT_0trace(BspAppTrace, GT_ERR, " AR12XX: SPI Read Failed\r\n");
            retVal = BSP_EFAIL;
        }
        else
        {
            retVal = (Int32) len;
        }
    }
    return retVal;
}

Int32 Bsp_ar12xxSpiWriteCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len)
{
    UInt32                    size             = 0;
    Int                       status           = IOM_COMPLETED;
    Mcspi_DataParam           issueDataparam   = {0};
    Mcspi_DataParam           reclaimDataparam = {0};
    Ptr                       pReclaimDataparam;
    Int32                     retVal   = BSP_SOK;
    Bsp_ar12xxRadarCommHandle commHndl = (Bsp_ar12xxRadarCommHandle) fd;
    Mcspi_FifoTrigLvl         fifoLevel;

    issueDataparam.outBuffer = (UInt8 *) pBuff;
    issueDataparam.bufLen    = (UInt32) len;
    issueDataparam.inBuffer  = NULL;
    size = (UInt32) len;
    if (len < MCSPI_TX_FIFO_LEN)
    {
         fifoLevel.rxTriggerLvl = len;
         fifoLevel.txTriggerLvl = len;
    }
    else
    {
         fifoLevel.rxTriggerLvl = MCSPI_RX_FIFO_LEN;
         fifoLevel.txTriggerLvl = MCSPI_TX_FIFO_LEN;
    }

    status = GIO_control(commHndl->mcspiHandle, IOCTL_MCSPI_SET_TRIGGER_LVL,
                         &fifoLevel);
    if (IOM_COMPLETED == status)
    {
        /* Issue the first & second empty buffers to the input stream */
        status = GIO_issue(commHndl->mcspiHandle, &issueDataparam, size,
                       NULL);
    }

    if ((status != IOM_PENDING) && (status != IOM_COMPLETED))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  " AR12XX: Failed to issue empty buffer to stream!!\r\n");
    }
    /* Reclaim is done after every issue and buffers are not primed. If
     * the buffers are primed next transfer is initialized as soon as
     * the first one is completed. We wont be able to ensure transfer
     * initializaton on Slave before master for second buffer
     */
    pReclaimDataparam = (Ptr) & reclaimDataparam;
    status =
        GIO_reclaim(commHndl->mcspiHandle,
                    (Ptr *) &pReclaimDataparam,
                    NULL,
                    NULL);
    if (IOM_COMPLETED != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, " AR12XX: SPI Write Failed\r\n");
        retVal = BSP_EFAIL;
    }
    else
    {
        retVal = (Int32) len;
    }
    return retVal;
}


rlComIfHdl_t Bsp_spi2cOpenCb(rlUInt8_t deviceIndex, UInt32 flags)
{
    Bsp_ar12xxRadarCommHandle commHndl =
            &gBspAr12xxObj.radarDevCommObj[deviceIndex];
    rlComIfHdl_t returnHandle = NULL;
    Int32 ret = BSP_SOK;
    /* MSB first, clock idle low, transfer on rising clock edge, 1843KHz */
    UInt8 tempData[2] = {0xF0, 0x00};

    commHndl->deviceIdx = (UInt32) deviceIndex;
    commHndl->backChI2cInstId = gBspAr12xxObj.initPrmsCopy.
                                    devParams[deviceIndex].i2cDevInst;
    commHndl->backChI2cAddr = gBspAr12xxObj.initPrmsCopy.
                                    devParams[deviceIndex].i2cDevAddr;

    ret = Bsp_deviceRawWrite8(commHndl->backChI2cInstId,
                              commHndl->backChI2cAddr,
                              tempData,
                              2U);

    if (ret == BSP_SOK)
    {
        returnHandle = (rlComIfHdl_t) commHndl;
    }

    return returnHandle;
}

Int32 Bsp_spi2cCloseCb(rlComIfHdl_t fd)
{
    return BSP_SOK;
}

Int32 Bsp_spi2cWriteCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len)
{
    UInt8 sendBuff[3];
    Int32 retVal = BSP_SOK;
    UInt32 i = 0;
    UInt16 numWrites = (len >> 1);
    Bsp_ar12xxRadarCommHandle commHndl = (Bsp_ar12xxRadarCommHandle) fd;

    for(i = 0; i < numWrites; i++)
    {
        sendBuff[0] = 1U;
        sendBuff[1] = pBuff[(2U*i) + 1U];
        sendBuff[2] = pBuff[2U*i];
        retVal = Bsp_deviceRawWrite8(commHndl->backChI2cInstId,
                                     commHndl->backChI2cAddr,
                                     sendBuff,
                                     3U);
        if(retVal != BSP_SOK)
        {
            break;
        }
        BspOsal_sleep(1U);
    }

    if((retVal == BSP_SOK) && ((len % (UInt16)2) != (UInt16)0))
    {
        sendBuff[0] = 1U;
        sendBuff[1] = pBuff[len - (UInt16)1];
        retVal = Bsp_deviceRawWrite8(commHndl->backChI2cInstId,
                                     commHndl->backChI2cAddr,
                                     sendBuff,
                                     2U);
    }

    if(retVal == BSP_SOK)
    {
        retVal = (Int32) len;
    }

    return retVal;
}

Int32 Bsp_spi2cReadCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len)
{
    Int32 retVal = BSP_SOK;
    UInt32 numReads = (UInt32)len/2U;
    UInt32 i = 0U;
    UInt8 readCmdBuff[3] = {0x01, 0xFF, 0xFF};
    Bsp_ar12xxRadarCommHandle commHndl = (Bsp_ar12xxRadarCommHandle) fd;

    for(i = 0U; i < numReads; i++)
    {
        retVal = Bsp_deviceRawWrite8(commHndl->backChI2cInstId,
                                     commHndl->backChI2cAddr,
                                     readCmdBuff,
                                     3U);
        if (retVal == BSP_SOK)
        {
            retVal = Bsp_deviceRawRead8(commHndl->backChI2cInstId,
                                    commHndl->backChI2cAddr,
                                    &pBuff[2U*i],
                                    2U);
        }
        if (retVal != BSP_SOK)
        {
            break;
        }
        /* Swap bytes to correct endianness. */
        pBuff[2U*i] ^= pBuff[(2U*i) + 1U];
        pBuff[(2U*i) + 1U] ^= pBuff[2U*i];
        pBuff[2U*i] ^= pBuff[(2U*i) + 1U];

        BspOsal_sleep(1U);
    }

    if((retVal == BSP_SOK) && ((len % (UInt16)2) != (UInt16)0))
    {
        retVal = Bsp_deviceRawWrite8(commHndl->backChI2cInstId,
                                     commHndl->backChI2cAddr,
                                     readCmdBuff,
                                     3U);
        if (retVal == BSP_SOK)
        {
            retVal = Bsp_deviceRawRead8(commHndl->backChI2cInstId,
                                        commHndl->backChI2cAddr,
                                        &pBuff[len - (UInt16)1],
                                        1U);
        }
    }

    if(retVal == BSP_SOK)
    {
        retVal = (Int32) len;
    }

    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/* None */

