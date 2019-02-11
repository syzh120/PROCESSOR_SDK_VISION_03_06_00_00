/*
 *  Copyright (c) Texas Instruments Incorporated 2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file utils_mcspi.c
 *
 *  \brief Cascade Radar sample application McSPI Utilities.
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <CascadeFlashFpga_main.h>

#define UTILS_MCSPI_NUM_MCSPI_INST (4U)

/** \brief McSPI Configuration parameters */
static Mcspi_Params mcspiCfgPrms[UTILS_MCSPI_NUM_MCSPI_INST];

/** \brief String identifiers for the McSPI driver names */
static xdc_String gMcspiDriverNames[UTILS_MCSPI_NUM_MCSPI_INST] =
{
    "/mcspi0",
    "/mcspi1",
    "/mcspi2",
    "/mcspi3"
};

/**
 *  \brief FPGA communication handle object which contains the required
 *         information for communication with the AR12 devices.
 */
typedef struct
{
    UInt32           deviceIdx;
    /**< Device Index of the corresponding AR12x instance */
    GIO_Handle       mcspiHandle;
    /**< GIO Handle for McSPI */
    GIO_Params       mcspiIoPrms;
    /**< McSPI GIO parameters used while creating the driver */
    Mcspi_ChanParams mcspiChanParams;
    /**< McSPI Channel parameters */
    UInt32           backChI2cInstId;
    /**< Satellite Radar Back Channel I2C instance ID */
    UInt32           backChI2cAddr;
    /**< Satellite Radar Back Channel I2C device address */
} Bsp_FPGADeviceCommObj;

/**
 *  \brief Pointer to the radar McSPI communication object.
 */
typedef Bsp_FPGADeviceCommObj *Bsp_FPGARadarCommHandle;

static Bsp_FPGADeviceCommObj gRadarDevCommObj;

/**
 *******************************************************************************
 *  \brief  User defined function which will initialize the McSPI. This function
 *          is called when the driver for McSPI is created.
 *
 * \return  None
 *
 *******************************************************************************
 */
static void Utils_mcspiUserCommonInit(uint32_t mcSPINum);

static void Utils_mcspi0UserInit(void);
static void Utils_mcspi1UserInit(void);
static void Utils_mcspi2UserInit(void);
static void Utils_mcspi3UserInit(void);

/**
 *******************************************************************************
 *
 * \brief Initializes the McSPI and adds the GIO_Device
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Utils_mcspiInit(UInt32 mcSpiInstNum)
{
    if (mcSpiInstNum < UTILS_MCSPI_NUM_MCSPI_INST)
    {
        /* Set the mcspi params */
        switch(mcSpiInstNum)
        {
            case 0: PlatformMCSPI1SetPinMux();
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi0UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    break;
            case 1: PlatformMCSPI2SetPinMux();
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi1UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    break;
            case 2: /* Pin Mux for the McSPI3 is being done in CascadeFlashFpga_InitPadMux */
                    /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_59, MCSPI3_IRQ);
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi2UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    break;
            case 3:
                    /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_60, MCSPI4_IRQ);
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi3UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    break;
        }
    }
}

Void Utils_mcspiDeinit(UInt32 mcSpiInstNum)
{
    GIO_removeDevice(gMcspiDriverNames[mcSpiInstNum]);
}

void Utils_mcspiGetDevName (UInt32 mcSpiInstNum, xdc_String devName)
{
    if (mcSpiInstNum < UTILS_MCSPI_NUM_MCSPI_INST)
    {
        strcpy(devName, gMcspiDriverNames[mcSpiInstNum]);
    }
}

static void Utils_mcspi0UserInit(void)
{
    Utils_mcspiUserCommonInit(0);
}

static void Utils_mcspi1UserInit(void)
{
    Utils_mcspiUserCommonInit(1);
}

static void Utils_mcspi2UserInit(void)
{
    Utils_mcspiUserCommonInit(2);
}

static void Utils_mcspi3UserInit(void)
{
    Utils_mcspiUserCommonInit(3);
}

static void Utils_mcspiUserCommonInit(uint32_t mcSPINum)
{
    UInt32       i = 0U;
    static uint32_t done = 0;
    if (done == 0)
    {
        Mcspi_init();
        done = 1;
    }
    memcpy((Void *)&mcspiCfgPrms[mcSPINum], (const Void *)&Mcspi_PARAMS, sizeof(Mcspi_Params));
    /* Set the McSPI parameters */
    mcspiCfgPrms[mcSPINum].instNum = mcSPINum;
    mcspiCfgPrms[mcSPINum].opMode          = MCSPI_OPMODE_INTERRUPT;
    mcspiCfgPrms[mcSPINum].hwiNumber       = 7;
    mcspiCfgPrms[mcSPINum].enableCache     = (UInt32) TRUE;
    mcspiCfgPrms[mcSPINum].edma3EventQueue = 0;
    mcspiCfgPrms[mcSPINum].enableErrIntr   = (UInt32) FALSE;
    mcspiCfgPrms[mcSPINum].prcmPwrmEnable = TRUE;

    mcspiCfgPrms[mcSPINum].spiHWCfgData.masterOrSlave         = MCSPI_COMMMODE_MASTER;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.singleOrMultiChEnable = MCSPI_SINGLE_CHANNEL;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.pinOpModes    = MCSPI_PINOPMODE_4PIN;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.fifoRxTrigLvl = 32;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.fifoTxTrigLvl = 32;

    for (i = 0U; i < CSL_MCSPI_0_NumOfPhyChannels; i++)
    {
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].charLength = MCSPI_LEN_8BIT;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].multiWordAccessEnable =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiChipSelectEnablePol =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].clockMode =
            MCSPI_MODE0;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].clockRatioExtension = 0;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiWordInitDelay    =
            MCSPI_NO_DELAY;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].trasmitReceiveMode =
            MCSPI_BOTH_RXTX;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].granularityEnable =
            (UInt32) TRUE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].busFreq           = 80000;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spienHighPolarity =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].slaveModeChipSelect =
            MCSPI_SPIEN_0;
        if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
        {
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_IN;
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_OUT;
        }
        else
        {
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_OUT;
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_IN;
        }
    }

    if (MCSPI_OPMODE_INTERRUPT == mcspiCfgPrms[mcSPINum].opMode)
    {
        GT_0trace(BspAppTrace, GT_INFO, " UTILS_MCSPI: McSPI is configured in interrupt mode!!\r\n");
    }
}

void * Bsp_FPGASpiOpenCb(UInt32 mcSpiIdx)
{
    Bsp_FPGARadarCommHandle commHndl = &gRadarDevCommObj;
    UInt32       mcSpiDevInstNum = mcSpiIdx;
    void * returnHandle    = NULL;

    if (mcSpiDevInstNum < 4)
    {
        Error_Block eb;
        Error_init(&eb);
        /*
         * Initialize channel attributes.
         */
        GIO_Params_init(&commHndl->mcspiIoPrms);

        /* Update the McSPI channel parameters */
        commHndl->mcspiChanParams.hEdma = gEdmaHandle;
        commHndl->mcspiChanParams.chipSelTimeControl = MCSPI_CLK_CYCLE3;
        commHndl->mcspiChanParams.fifoEnable         = (Bool) FALSE;
        commHndl->mcspiChanParams.spiChipSelectHold  = (Bool) TRUE;
        if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
        {
            commHndl->mcspiChanParams.chanNum = 0;
        }
        else
        {
            commHndl->mcspiChanParams.chanNum = 1;
        }

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
        commHndl->mcspiIoPrms.numPackets = 3U + 1U;

        commHndl->deviceIdx = (UInt32) mcSpiIdx;

        commHndl->mcspiHandle = (GIO_Handle) GIO_create(
            (xdc_String) gMcspiDriverNames[mcSpiDevInstNum], (UInt32) GIO_INOUT,
            &commHndl->mcspiIoPrms, &eb);
        if (commHndl->mcspiHandle == NULL)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      " FPGA: McSPI GIO Create Failed!!\r\n");
        }
        returnHandle = (void*) commHndl;
    }
    else
    {
        /* Should ideally not reach here as the check is done earlier inBuffer
         * #Bsp_FPGACheckInitParams function.
         */
        returnHandle = NULL;
    }
    return returnHandle;
}

Int32 Bsp_FPGASpiCloseCb(void* fd)
{
    Bsp_FPGARadarCommHandle commHndl = (Bsp_FPGARadarCommHandle) fd;
    GIO_delete((GIO_Handle *) &commHndl->mcspiHandle);
    return BSP_SOK;
}

Int32 Bsp_FPGASpiReadCb(void * fd, UInt8 *pBuff, UInt16 len)
{
    UInt32                    size             = 0U;
    Int                       status           = IOM_COMPLETED;
    Mcspi_DataParam           issueDataparam   = {0};
    Mcspi_DataParam           reclaimDataparam = {0};
    Ptr                       pReclaimDataParam;
    Int32                     retVal   = BSP_SOK;
    Bsp_FPGARadarCommHandle commHndl = (Bsp_FPGARadarCommHandle) fd;

    issueDataparam.inBuffer = (UInt8 *) pBuff;
    issueDataparam.bufLen   = (UInt32) len;
    if ((UInt32)len > 0x1000U)
    {
        /* Something is wrong if this condition is met */
        GT_1trace(BspAppTrace, GT_ERR,
                  " FPGA: Too large read requested!! Length = %x\r\n",
                  (UInt32)len);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        issueDataparam.outBuffer = NULL;
        size = (UInt32)len;

        /* Issue the first & second empty buffers to the input stream */
        status = GIO_issue(commHndl->mcspiHandle, &issueDataparam, size,
                           NULL);

        if ((status != IOM_PENDING) && (status != IOM_COMPLETED))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      " FPGA: Failed to issue empty buffer to stream!!\r\n");
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
            GT_0trace(BspAppTrace, GT_ERR, " FPGA: SPI Read Failed\r\n");
            retVal = BSP_EFAIL;
        }
        else
        {
            retVal = (Int32) len;
        }
    }
    return retVal;
}

Int32 Bsp_FPGASpiWriteCb(void * fd, UInt8 *pBuff, UInt16 len)
{
    UInt32                    size             = 0;
    Int                       status           = IOM_COMPLETED;
    Mcspi_DataParam           issueDataparam   = {0};
    Mcspi_DataParam           reclaimDataparam = {0};
    Ptr                       pReclaimDataparam;
    Int32                     retVal   = BSP_SOK;
    Bsp_FPGARadarCommHandle commHndl = (Bsp_FPGARadarCommHandle) fd;

    issueDataparam.outBuffer = (UInt8 *) pBuff;
    issueDataparam.bufLen    = (UInt32) len;
    issueDataparam.inBuffer  = (UInt8 *) pBuff;
    size = (UInt32) len;

    /* Issue the first & second empty buffers to the input stream */
    status = GIO_issue(commHndl->mcspiHandle, &issueDataparam, size,
                       NULL);

    if ((status != IOM_PENDING) && (status != IOM_COMPLETED))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  " FPGA: Failed to issue empty buffer to stream!!\r\n");
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
        GT_0trace(BspAppTrace, GT_ERR, " FPGA: SPI Write Failed\r\n");
        retVal = BSP_EFAIL;
    }
    else
    {
        retVal = (Int32) len;
    }
    return retVal;
}
