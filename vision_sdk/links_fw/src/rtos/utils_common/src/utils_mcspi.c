/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_mcspi.c
 *
 * \brief  This file has the implementataion for UART
 *
 * \version 0.0 (Aug 2016) : [PG] First version
 * \version 0.1 (Oct 2017) : [PG] Updated for 4 McSPI
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
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
#include <src/rtos/utils_common/include/utils_mcspi.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>

#define UTILS_MCSPI_NUM_MCSPI_INST (4U)
#define UTILS_MCSPI_NUM_DEVICES    (8U)
/** Num Bufs to be issued and reclaimed */
#define UTILS_MCSPI_NUM_BUFS       (3U)

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
 *  \brief McSPI communication handle object which contains the required
 *         information for communication with McSPI devices.
 */
typedef struct
{
    UInt32           deviceIdx;
    /**< Device Index of the corresponding device instance */
    GIO_Handle       mcspiHandle;
    /**< GIO Handle for McSPI */
    GIO_Params       mcspiIoPrms;
    /**< McSPI GIO parameters used while creating the driver */
    Mcspi_ChanParams mcspiChanParams;
    /**< McSPI Channel parameters */
} Utils_mcspiDeviceCommObj;

/**
 *  \brief Pointer to the radar McSPI communication object.
 */
typedef Utils_mcspiDeviceCommObj *Utils_mcspiCommHandle;
/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * MISRAC_WAIVER: All global variables are defined at the top of the file
 * to increase readability and maintenance of code.
 */
static Utils_mcspiDeviceCommObj gUtils_mcspiDeviceCommObj[UTILS_MCSPI_NUM_DEVICES];

/*******************************************************************************
 *  Function Declarations
 *******************************************************************************
 */

/* MISRA.FUNC.NOPROT.CALL Rule 8.2 fix */
static inline void ti_sysbios_io_GIO_Params_init(ti_sysbios_io_GIO_Params *prms);

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
            case 0U: GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi0UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_0);
                    break;
            case 1U: GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi1UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_1);
                    break;
            case 2U: /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
            #ifdef IPU_PRIMARY_CORE_IPU2
                                CPU_IPU2, XBAR_INST_IPU1_IRQ_59, MCSPI3_IRQ);
            #else
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_59, MCSPI3_IRQ);
            #endif
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi2UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_2);
                    break;
            case 3U:
                    /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
            #ifdef IPU_PRIMARY_CORE_IPU2
                                CPU_IPU2, XBAR_INST_IPU1_IRQ_60, MCSPI4_IRQ);
            #else
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_60, MCSPI4_IRQ);
            #endif
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi3UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_3);
                    break;
            default:
                    /* Should not come here */
                    break;
        }
    }
}
/**
 *******************************************************************************
 *
 * \brief De-Initializes the McSPI and removes the GIO_Device
 *
 * \param mcSpiInstNum McSPI Instance Number
 * \return  None
 *
 *******************************************************************************
 */
Void Utils_mcspiDeinit(UInt32 mcSpiInstNum)
{
    GIO_removeDevice(gMcspiDriverNames[mcSpiInstNum]);
}
/**
 *******************************************************************************
 *
 * \brief Get the McSPI Device Name
 *
 * \param mcSpiInstNum McSPI Instance Number
 * \param devName      Device Name returned by the API.
 * \return  None
 *
 *******************************************************************************
 */
void Utils_mcspiGetDevName (UInt32 mcSpiInstNum, xdc_String devName)
{
    if (mcSpiInstNum < UTILS_MCSPI_NUM_MCSPI_INST)
    {
        strcpy(devName, gMcspiDriverNames[mcSpiInstNum]);
    }
}
/**
 *******************************************************************************
 *
 * \brief  Open the McSPI Device Handle
 *
 * \param deviceId          Index of the device being communicated with
 * \param mcSpiInstNum      McSPI Instance Number
 * \param mcSpiChannelNum   Channel number of the McSPI instance.
 * \param edmaHandle        EDMA handle to be used for the McSPI transfers.
 *
 * \return  Pointer to the handle of the mcspi communication handle.
 *
 *******************************************************************************
 */
void * Utils_mcspiOpen(UInt8            deviceId,
                       UInt8            mcSpiDevInstNum,
                       UInt8            mcSpiChannelNum,
                       EDMA3_DRV_Handle edmaHandle)
{
    Utils_mcspiCommHandle commHndl = &gUtils_mcspiDeviceCommObj[deviceId];
    static UInt32 fifoEnabled[UTILS_MCSPI_NUM_MCSPI_INST] = {0U, 0U, 0U, 0U};
    void * returnHandle    = NULL;

    if (mcSpiDevInstNum < UTILS_MCSPI_NUM_MCSPI_INST)
    {
        Error_Block eb;
        Error_init(&eb);
        /*
         * Initialize channel attributes.
         */
        GIO_Params_init(&commHndl->mcspiIoPrms);

        /* Update the McSPI channel parameters */
        commHndl->mcspiChanParams.hEdma = edmaHandle;
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
        commHndl->mcspiChanParams.chanNum = mcSpiChannelNum;

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
        commHndl->mcspiIoPrms.numPackets = UTILS_MCSPI_NUM_BUFS + 1U;

        commHndl->deviceIdx = (UInt32) deviceId;

        commHndl->mcspiHandle = (GIO_Handle) GIO_create(
            (xdc_String) gMcspiDriverNames[mcSpiDevInstNum], (UInt32) GIO_INOUT,
            &commHndl->mcspiIoPrms, &eb);
        if (commHndl->mcspiHandle == NULL)
        {
            Vps_printf(" UTILS_MCSPI: McSPI GIO Create Failed!!\r\n");
        }
        returnHandle = (void*) commHndl;
    }
    else
    {
        returnHandle = NULL;
    }
    return returnHandle;
}

/**
 *******************************************************************************
 *
 * \brief  Close the McSPI Device Handle
 *
 * \param fd    Pointer to the McSPI commnication Handle.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Utils_mcspiClose(void * fd)
{
    Utils_mcspiCommHandle commHndl = (Utils_mcspiCommHandle) fd;
    GIO_delete((GIO_Handle *) &commHndl->mcspiHandle);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief  Function to read from the McSPI device
 *
 * \param fd    Pointer to the McSPI commnication Handle.
 * \param pBuff Pointer to the buffer to which the data is written.
 * \param len   Number of bytes to read.
 *
 * \return  SYSTEM_LINK_STATUS_SOK if operation successful,
 *          SYSTEM_LINK_STATUS_EFAIL otherwise.
 *
 *******************************************************************************
 */
Int32 Utils_mcspiRead(void * fd, UInt8 *pBuff, UInt16 len)
{
    UInt32                    size             = 0U;
    Int                       status           = IOM_COMPLETED;
    Mcspi_DataParam           issueDataparam   = {0};
    Mcspi_DataParam           reclaimDataparam = {0};
    Ptr                       pReclaimDataParam;
    Int32                     retVal   = SYSTEM_LINK_STATUS_SOK;
    Utils_mcspiCommHandle commHndl = (Utils_mcspiCommHandle) fd;

    issueDataparam.inBuffer = (UInt8 *) pBuff;
    issueDataparam.bufLen   = (UInt32) len;
    if ((UInt32)len > 0x1000U)
    {
        /* Something is wrong if this condition is met */
        Vps_printf(" UTILS_MCSPI: Too large read requested!! Length = %x\r\n",
                  (UInt32)len);
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }
    if (retVal == SYSTEM_LINK_STATUS_SOK)
    {
        issueDataparam.outBuffer = NULL;
        size = (UInt32)len;

        /* Issue the first & second empty buffers to the input stream */
        status = GIO_issue(commHndl->mcspiHandle, &issueDataparam, size,
                           NULL);

        if ((status != IOM_PENDING) && (status != IOM_COMPLETED))
        {
            Vps_printf(" UTILS_MCSPI: Failed to issue empty buffer to stream!!\r\n");
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
            Vps_printf(" UTILS_MCSPI: SPI Read Failed\r\n");
            retVal = SYSTEM_LINK_STATUS_EFAIL;
        }
        else
        {
            retVal = (Int32) len;
        }
    }
    return retVal;
}
/**
 *******************************************************************************
 *
 * \brief  Function to write to the McSPI device
 *
 * \param fd    Pointer to the McSPI commnication Handle.
 * \param pBuff Pointer to the buffer to which the data is written.
 * \param len   Number of bytes to read.
 *
 * \return  SYSTEM_LINK_STATUS_SOK if operation successful,
 *          SYSTEM_LINK_STATUS_EFAIL otherwise.
 *
 *******************************************************************************
 */
Int32 Utils_mcspiWrite(void * fd, UInt8 *pBuff, UInt16 len)
{
    UInt32                    size             = 0;
    Int                       status           = IOM_COMPLETED;
    Mcspi_DataParam           issueDataparam   = {0};
    Mcspi_DataParam           reclaimDataparam = {0};
    Ptr                       pReclaimDataparam;
    Int32                     retVal   = SYSTEM_LINK_STATUS_SOK;
    Utils_mcspiCommHandle commHndl = (Utils_mcspiCommHandle) fd;

    issueDataparam.outBuffer = (UInt8 *) pBuff;
    issueDataparam.bufLen    = (UInt32) len;
    issueDataparam.inBuffer  = NULL;
    size = (UInt32) len;

    /* Issue the first & second empty buffers to the input stream */
    status = GIO_issue(commHndl->mcspiHandle, &issueDataparam, size,
                       NULL);

    if ((status != IOM_PENDING) && (status != IOM_COMPLETED))
    {
        Vps_printf(" UTILS_MCSPI: Failed to issue empty buffer to stream!!\r\n");
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
        Vps_printf(" UTILS_MCSPI: SPI Write Failed\r\n");
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        retVal = (Int32) len;
    }
    return retVal;
}

static void Utils_mcspi0UserInit(void)
{
    Utils_mcspiUserCommonInit(0U);
}

static void Utils_mcspi1UserInit(void)
{
    Utils_mcspiUserCommonInit(1U);
}

static void Utils_mcspi2UserInit(void)
{
    Utils_mcspiUserCommonInit(2U);
}

static void Utils_mcspi3UserInit(void)
{
    Utils_mcspiUserCommonInit(3U);
}

static void Utils_mcspiUserCommonInit(uint32_t mcSPINum)
{
    UInt32       i = 0U;
    static uint32_t done = 0U;
    if (done == 0U)
    {
        Mcspi_init();
        done = 1U;
    }
    memcpy((Void *)&mcspiCfgPrms[mcSPINum], (const Void *)&Mcspi_PARAMS, sizeof(Mcspi_Params));
    /* Set the McSPI parameters */
    mcspiCfgPrms[mcSPINum].instNum = mcSPINum;
    mcspiCfgPrms[mcSPINum].opMode          = MCSPI_OPMODE_INTERRUPT;
    mcspiCfgPrms[mcSPINum].hwiNumber       = 7;
    mcspiCfgPrms[mcSPINum].enableCache     = (UInt32) TRUE;
    mcspiCfgPrms[mcSPINum].edma3EventQueue = 0;
    mcspiCfgPrms[mcSPINum].enableErrIntr   = (UInt32) FALSE;
#ifdef A15_TARGET_OS_LINUX
    mcspiCfgPrms[mcSPINum].prcmPwrmEnable = FALSE;
#else
    mcspiCfgPrms[mcSPINum].prcmPwrmEnable = TRUE;
#endif
    mcspiCfgPrms[mcSPINum].spiHWCfgData.masterOrSlave         = MCSPI_COMMMODE_MASTER;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.singleOrMultiChEnable = MCSPI_MULTI_CHANNEL;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.pinOpModes    = MCSPI_PINOPMODE_4PIN;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.fifoRxTrigLvl = 32;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.fifoTxTrigLvl = 32;

    for (i = 0U; i < CSL_MCSPI_0_NumOfPhyChannels; i++)
    {
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].charLength = MCSPI_LEN_16BIT;
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
#if defined (TDA3XX_AR12_ALPS)
        /* 8 MHz Bus Frequency */
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].busFreq           = 8000000;
#else
        /* 24 MHz Bus Frequency */
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].busFreq           = 24000000;
#endif
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spienHighPolarity =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].slaveModeChipSelect =
            MCSPI_SPIEN_0;
#if defined (BOARD_TDA2XX_CASCADE_RADAR)
        if ((mcSPINum == 2) || (mcSPINum == 3))
        {
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_IN;
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_OUT;
        }
        else
        {
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_OUT;
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_IN;
        }
#else
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_OUT;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_IN;
#endif
    }

    if (MCSPI_OPMODE_INTERRUPT == mcspiCfgPrms[mcSPINum].opMode)
    {
        Vps_printf(" UTILS_MCSPI: McSPI is configured in interrupt mode!!\r\n");
    }
}
