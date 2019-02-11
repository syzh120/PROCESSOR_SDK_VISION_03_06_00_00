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
 *  \brief Monitor Radar sample application McSPI Utilities.
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
#include <MonitorRadar_main.h>

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
                    #if defined(BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_0);
                    #endif
                    break;
            case 1: PlatformMCSPI2SetPinMux();
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi1UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    #if defined(BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_1);
                    #endif
                    break;
            case 2: /* Pin Mux for the McSPI3 is being done in MonitorRadar_InitPadMux */
                    /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_59, MCSPI3_IRQ);
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi2UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    #if defined(BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_2);
                    #endif
                    break;
            case 3:
                    /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_60, MCSPI4_IRQ);
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi3UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    #if defined(BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_3);
                    #endif
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
        /* 800 KHz Bus Frequency */
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].busFreq           = 24000000;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spienHighPolarity =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].slaveModeChipSelect =
            MCSPI_SPIEN_0;
        if (mcSPINum == 2)
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
