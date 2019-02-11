/******************************************************************************
Copyright (c) [2012 - 2018] Texas Instruments Incorporated

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
******************************************************************************/


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/common/chains_radar.h>
#include <src/rtos/utils_common/include/utils_mcspi.h>
#include <src/rtos/utils_common/include/utils_uart.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>
#include <ti/drv/vps/include/vip/vps_captureVipDataTypes.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_gpio.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief MCSPI Instance Number used to communicate with the radar sensor */
#define CHAINS_AWR1243_SENSOR_MCSPI_INST0 (0U)
#define CHAINS_AWR1243_SENSOR_MCSPI_INST1 (1U)
#define CHAINS_AWR1243_SENSOR_MCSPI_INST2 (2U)
#define CHAINS_AWR1243_SENSOR_MCSPI_INST3 (3U)

/* Uncomment below to enable synthetic input from the AR12x sensor. Kindly note
 * Test source is not available when CHAINS_RADAR_NUM_TX_ANTENNA > 1 */
/* #define ENABLE_TEST_SOURCE */

/* Uncomment below to enable updating the parameters at run time after stopping the sensor and
 * restarting.
 */
#if defined (TDA3XX_AR12_ALPS)
#define CHAINS_AR1243_STOP_RESTART
#endif

/* ========================================================================== */
/*                           Globals                                          */
/* ========================================================================== */

static Bsp_Ar12xxInitParams gAr12xx_initParams;
static UInt32 gChainsCommon_ar12xxFrameType[CHAINS_MAX_NUM_RADARS] = {0U};

static DEV_Struct uartAr12FlashDevObj;

char gChains_ub960RunTimeMenu[] = {
    "\r\n "
    "\r\n =========================="
    "\r\n Select UB960 Configuration"
    "\r\n =========================="
    "\r\n "
    "\r\n 1: 2Gbps Mode "
    "\r\n 2: 4Gbps Mode "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

static Void ChainsCommon_ar12xxInit(ChainsCommon_Ar12xxConfigOut *pCfgOut);
static Void ChainsCommon_CalcResolution(rlProfileCfg_t *profile,
                                        float          *range,
                                        float          *velocity,
                                        uint32_t       numChirps);
static Int32 Chains_ar12xxGetDataRateParams(ChainsCommon_Ar12xxConfigOut *pCfgOut,
                                            UInt32 radarIdx,
                                            UInt32 *issClkParam,
                                            UInt32 *issDataParam);
UInt32 Bsp_ar12xxGetDeviceRevision(void);
static Void ChainsCommon_CalcChirpRows(ChainsCommon_Ar12xxConfigOut *pCfgOut);
/**
 *******************************************************************************
 *
 * \brief   Function to print run time menu of the frame configuration selection
 *
 * \param   None
 * /return  char   User Input choice.
 *
 *******************************************************************************
*/
char ChainsCommon_ar12xxRunTimeMenu(char * pMenu)
{
    Vps_printf(pMenu);
    return Chains_readChar();
}

/**
 *******************************************************************************
 *
 * \brief   Function to enable the dummy input of objects from AR12xx
 *
 * \param   None
 * /return  retVal   SYSTEM_LINK_STATUS_SOK if the test source is set correctly.
 *
 *******************************************************************************
*/
Int32 ChainsCommon_ar12xxEnableTestSource(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Bsp_Ar12xxTestSource tsArgs = {0};
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    Int32 i = 0;

    for (i = 0; i < pCfgOut->numRadars; i++)
    {
        tsArgs.testObj[0].posX = 0;

        tsArgs.testObj[0].posY = 100 + i*100;
        tsArgs.testObj[0].posZ = 0;
        /* The Velocity is kept 0 specifically when the number of antennas
         * is higher than 1
         */
        tsArgs.testObj[0].velX = 0;
        tsArgs.testObj[0].velY = 0;
        tsArgs.testObj[0].velZ = 0;

        tsArgs.testObj[0].posXMin = -32700;
        tsArgs.testObj[0].posYMin = 0;
        tsArgs.testObj[0].posZMin = -32700;

        tsArgs.testObj[0].posXMax = 32700;
        tsArgs.testObj[0].posYMax = 32700;
        tsArgs.testObj[0].posZMax = 32700;

        tsArgs.testObj[0].sigLvl = 150;

        tsArgs.testObj[1].posX = 0;
        tsArgs.testObj[1].posY = 32700;
        tsArgs.testObj[1].posZ = 0;

        tsArgs.testObj[1].velX = 0;
        tsArgs.testObj[1].velY = 0;
        tsArgs.testObj[1].velZ = 0;

        tsArgs.testObj[1].posXMin = -32700;
        tsArgs.testObj[1].posYMin = 0;
        tsArgs.testObj[1].posZMin = -32700;

        tsArgs.testObj[1].posXMax = 32700;
        tsArgs.testObj[1].posYMax = 32700;
        tsArgs.testObj[1].posZMax = 32700;

        tsArgs.testObj[1].sigLvl = 948;

        tsArgs.rxAntPos[0].antPosX = 0;
        tsArgs.rxAntPos[0].antPosZ = 0;
        tsArgs.rxAntPos[1].antPosX = 4;
        tsArgs.rxAntPos[1].antPosZ = 0;
        tsArgs.rxAntPos[2].antPosX = 8;
        tsArgs.rxAntPos[2].antPosZ = 0;
        tsArgs.rxAntPos[3].antPosX = 12;
        tsArgs.rxAntPos[3].antPosZ = 0;

        tsArgs.txAntPos[0].antPosX = 0;
        tsArgs.txAntPos[0].antPosZ = 0;
        tsArgs.txAntPos[1].antPosX = 0;
        tsArgs.txAntPos[1].antPosZ = 0;
        tsArgs.txAntPos[2].antPosX = 0;
        tsArgs.txAntPos[2].antPosZ = 0;

        retVal = Bsp_ar12xxEnableDummySource(i, &tsArgs);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    }
    retVal = Bsp_ar12xxSetTestSourceSeeds();
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief   Function to Initialize and configure the AR12 sensor.
 *
 * \param   pCfgOut Configuration parameters populated by the AR12 parameters.
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxConfig(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal;
    UInt32 i, j;
    Bsp_BoardId boardId;
    UInt32 numChirps[CHAINS_MAX_NUM_RADARS][CHAINS_AR1243_MAX_PROFILES] = {{0U}};

    Vps_printf(" CHAINS: Init AR12xx ... \n\r");
    ChainsCommon_ar12xxInit(pCfgOut);

    boardId = Bsp_boardGetId();
    if (boardId == BSP_BOARD_TDA3XX_AR12XX_ALPS)
    {
        /* For the ALPS board assume the AR12 Flash is already programmed
         * with firmware. Hence not downloading firmware again through SPI.
         * If the firmware has to be downloaded through SPI, make the input to
         * this API as 1 and ensure the AR12 Flash is erased.
         */
        retVal = Bsp_ar12xxBoot(0U);
    }
    else if ((boardId == BSP_BOARD_TDA3XX_RVP_ALPHA)
            || (boardId == BSP_BOARD_TDA3XX_RVP_BETA)
            || (boardId == BSP_BOARD_TDA3XX_RVP_A)
            || (boardId == BSP_BOARD_TDA3XX_D3_SK)
            || (boardId == BSP_BOARD_VISION))
    {
        retVal = Bsp_ar12xxBoot(0U);
    }
    else
    {
        /* For the TDA3xx EVM + DIB + VAB + Booster Pack setup always load the
         * firmware via SPI.
         */
        retVal = Bsp_ar12xxBoot(1U);
    }
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

    for (i = 0U; i < pCfgOut->numRadars; i++)
    {
        retVal = Bsp_ar12xxGetWidthHeight(i, &pCfgOut->radarParams[i].csi2OutWidth,
                                          &pCfgOut->radarParams[i].csi2OutHeight);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    }

    Vps_printf(" CHAINS: Config AR12xx ... \n\r");
    /* Find the number of loops corresponding to each sub frame.
     * this is later used to find the velocity resolution corresponding
     * to each sub frame.
     */
    for (j = 0; j < pCfgOut->numRadars; j++)
    {
        pCfgOut->radarParams[j].currProfileId = 0;
        if (pCfgOut->frameType == 1U)
        {
            Vps_printf(" CHAINS: Configuring the parameters for Advanced Frame for Radar Num: %d\n\r", j + 1U);
            gChainsCommon_ar12xxFrameType[j] = 2U;
            pCfgOut->radarParams[j].ar12xxConfig.frameType = BSP_AR12XX_FRAME_TYPE_ADVANCED;
            for (i = 0;
                 i < pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs.
                 frameSeq.numOfSubFrames;
                 i++)
            {
                /* Assumption is profile is always forced in
                 * advanced frames
                 */
                uint32_t profileIndexChosen =
                    pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs.frameSeq.
                    subFrameCfg[i].forceProfileIdx;
                numChirps[j][profileIndexChosen] = pCfgOut->radarParams[j].
                    ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[i].numLoops;
                /* Making a simplistic assumption here that the number of chirps is equal to the
                 * number of antennas. This is not always the case if the numLoops is > 255 in which
                 * case the number of chirps may be double the number of tx antennas and the number
                 * of loops may be half. This is currently not handled.
                 */
                pCfgOut->radarParams[j].numTxAntenna[i] =
                       pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[i].numOfChirps;
                pCfgOut->radarParams[j].numRxAntenna[i] = Chains_ar12xxCountOnes(
                       (UInt32)pCfgOut->radarParams[j].ar12xxConfig.dataFmtCfgArgs.rxChannelEn);
                pCfgOut->radarParams[j].radarWidth[i] =
                        pCfgOut->radarParams[j].ar12xxConfig.profileCfgArgs[i].numAdcSamples;
                pCfgOut->radarParams[j].radarHeight[i] = pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs.frameSeq.
                    subFrameCfg[i].numLoops * pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs.frameSeq.
                    subFrameCfg[i].numOfBurst * pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs.frameSeq.
                    subFrameCfg[i].numOfBurstLoops;
            }
        }
        else
        {
            /* Default to Normal Frame */
            Vps_printf(" CHAINS: Configuring the parameters for Normal Frame for Radar Number %d\n\r", j + 1U);
            gChainsCommon_ar12xxFrameType[j] = 1U;
            pCfgOut->radarParams[j].ar12xxConfig.frameType = BSP_AR12XX_FRAME_TYPE_NORMAL;
            for (i = 0; i < pCfgOut->radarParams[j].numProfiles; i++)
            {
                if (pCfgOut->radarParams[j].ar12xxConfig.frameCfgArgs != NULL)
                {
                    numChirps[j][i] =
                        pCfgOut->radarParams[j].ar12xxConfig.frameCfgArgs->numLoops;
                }
                else
                {
                    numChirps[j][i] = 0U;
                }
                /* Making a simplistic assumption here that the number of chirps is equal to the
                 * number of antennas. This is not always the case if the numLoops is > 255 in which
                 * case the number of chirps may be double the number of tx antennas and the number
                 * of loops may be half. This is currently not handled.
                 */
                pCfgOut->radarParams[j].numTxAntenna[i] =
                     pCfgOut->radarParams[j].ar12xxConfig.frameCfgArgs->chirpEndIdx + 1U;
                pCfgOut->radarParams[j].numRxAntenna[i] = Chains_ar12xxCountOnes(
                     (UInt32)pCfgOut->radarParams[j].ar12xxConfig.dataFmtCfgArgs.rxChannelEn);
                pCfgOut->radarParams[j].radarWidth[i] =
                     pCfgOut->radarParams[j].ar12xxConfig.profileCfgArgs[i].numAdcSamples;
                pCfgOut->radarParams[j].radarHeight[i] =
                     pCfgOut->radarParams[j].ar12xxConfig.frameCfgArgs->numLoops;
            }
        }
    }
    retVal = Bsp_ar12xxConfigParams(BSP_AR12XX_CONFIG_ALL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

#if defined(ENABLE_TEST_SOURCE)
    Vps_printf(" CHAINS: Enabling test source ...\n\r");
    ChainsCommon_ar12xxEnableTestSource(pCfgOut);
#endif
    for (i = 0; i < pCfgOut->radarParams[0].numProfiles; i++)
    {
        for (j = 0; j < pCfgOut->numRadars; j++)
        {
            if (pCfgOut->radarParams[j].ar12xxConfig.dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 6)
            {
                pCfgOut->radarParams[j].inBufAddrOffset = 4U;
                pCfgOut->radarParams[j].offsetBwAntennas [i] = pCfgOut->radarParams[j].radarWidth[i] * sizeof(UInt32) + 4U;
            }
            else if (pCfgOut->radarParams[j].ar12xxConfig.dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 9)
            {
                pCfgOut->radarParams[j].inBufAddrOffset = 0U;
                pCfgOut->radarParams[j].offsetBwAntennas [i] = pCfgOut->radarParams[j].radarWidth[i] * sizeof(UInt32) + 4U;
            }
            else
            {
                pCfgOut->radarParams[j].inBufAddrOffset = 0U;
                pCfgOut->radarParams[j].offsetBwAntennas [i] = pCfgOut->radarParams[j].radarWidth[i] * sizeof(UInt32);
            }
            ChainsCommon_CalcResolution(
                &pCfgOut->radarParams[j].ar12xxConfig.profileCfgArgs[i],
                &pCfgOut->radarParams[j].rangeRes[i],
                &pCfgOut->radarParams[j].velocityRes[i],
                numChirps[j][i]);
        }
    }
    if (pCfgOut->radarParams[j].chirpRow != NULL)
    {
        ChainsCommon_CalcChirpRows(pCfgOut);
    }
    Vps_printf(" CHAINS: Init AR12xx ... DONE !!!\n\r");
}
/**
 *******************************************************************************
 *
 * \brief   Function to Start the AR12 sensor
 *
 * \param   None
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxStart(void)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;

    Vps_printf(" CHAINS: AR12xx Starting Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxStartRadar();
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    Vps_printf(" CHAINS: AR12xx Starting Radar Sensor ... DONE !!!\n\r");

    if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_FPDLINK)
    {
        /*
         * UB960 CSI2 output is disabled by default after initialization
         * if radar sensor is connected.
         */
        BspUtils_enableUb960CsiOutput();
    }

}

Void ChainsCommon_ar12xxStop(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;

    Vps_printf(" CHAINS: AR12xx Stopping Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxStopRadar();
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    Task_sleep(100);
    ChainsCommon_ar12xxDeInit(pCfgOut);
    Vps_printf(" CHAINS: AR12xx Stopping Radar Sensor ... DONE !!!\n\r");
}

/**
 *******************************************************************************
 *
 * \brief   Function to Set up the ISS capture parameters
 *
 * \param   pPrm     ISS Capture params
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetIssCaptureParams(IssCaptureLink_CreateParams *pPrm,
                                            ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    UInt32 idx, i;
    Bsp_BoardId boardId;
    UInt32 issClkParam = 0U, issDataFormat = 0U;
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    UInt32 numSensors;

    if (pCfgOut->fusionEnabled == 0U)
    {
        boardId = Bsp_boardGetId();

        memset(pPrm, 0, sizeof(IssCaptureLink_CreateParams));
        /* Set CSI2 Capture params */
        pPrm->videoIfMode = SYSTEM_VIFM_SCH_CSI2;
        pPrm->videoIfWidth = SYSTEM_VIFW_4LANES;
        pPrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;
        pPrm->allocBufferForRawDump = 0U;
        pPrm->numCh = pCfgOut->numRadars;

        for (i=0; i<pCfgOut->numRadars; i++)
        {
            retVal = Chains_ar12xxGetDataRateParams(pCfgOut, i, &issClkParam, &issDataFormat);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

            pPrm->outParams[i].dataFormat = SYSTEM_DF_BAYER_BGGR;
            pPrm->outParams[i].outBpp = SYSTEM_BPP_BITS16;
            pPrm->outParams[i].inCsi2DataFormat = (System_Csi2DataFormat) issDataFormat;
            pPrm->outParams[i].inCsi2VirtualChanNum = i;
            pPrm->outParams[i].numOutBuf = 3U;

            if (pPrm->outParams[i].inCsi2DataFormat == SYSTEM_CSI2_RAW8)
            {
                pPrm->outParams[i].width = pCfgOut->radarParams[i].csi2OutWidth * 2U;
            }
            else
            {
                pPrm->outParams[i].width = pCfgOut->radarParams[i].csi2OutWidth;
            }
            pPrm->outParams[i].height = pCfgOut->radarParams[i].csi2OutHeight;

            pPrm->outParams[i].maxWidth = pPrm->outParams[i].width;
            pPrm->outParams[i].maxHeight = pPrm->outParams[i].height;
        }

        for(idx = 0U; idx < ISSCAPT_LINK_MAX_CMPLXIO_INST; idx++)
        {
            pPrm->csi2Params[idx].isCmplxIoCfgValid = FALSE;
            pPrm->csi2Params[idx].cmplxIoCfg.clockLane.pol      = (UInt32) FALSE;
            pPrm->csi2Params[idx].cmplxIoCfg.clockLane.position = CHAINS_AR1243_TDA_CSI_CLOCKLANE_POS;
            pPrm->csi2Params[idx].cmplxIoCfg.data1Lane.pol      = (UInt32) FALSE;
            pPrm->csi2Params[idx].cmplxIoCfg.data1Lane.position = CHAINS_AR1243_TDA_CSI_DATA1LANE_POS;
            pPrm->csi2Params[idx].cmplxIoCfg.data2Lane.pol      = (UInt32) FALSE;
            pPrm->csi2Params[idx].cmplxIoCfg.data2Lane.position = CHAINS_AR1243_TDA_CSI_DATA2LANE_POS;
            pPrm->csi2Params[idx].cmplxIoCfg.data3Lane.pol      = (UInt32) FALSE;
            pPrm->csi2Params[idx].cmplxIoCfg.data3Lane.position = CHAINS_AR1243_TDA_CSI_DATA3LANE_POS;
            pPrm->csi2Params[idx].cmplxIoCfg.data4Lane.pol      = (UInt32) FALSE;
            pPrm->csi2Params[idx].cmplxIoCfg.data4Lane.position = CHAINS_AR1243_TDA_CSI_DATA4LANE_POS;
            if (((boardId == BSP_BOARD_TDA3XX_RVP_ALPHA)
                    || (boardId == BSP_BOARD_TDA3XX_RVP_BETA)
                    || (boardId == BSP_BOARD_TDA3XX_RVP_A)
                    || (boardId == BSP_BOARD_TDA3XX_D3_SK))
                    && (Bsp_boardGetBaseBoardRev() != BSP_BOARD_RADAR_DC_REV_1))
            {
                /* Deserializer CSI2 clock is set to 800Mhz */
                pPrm->csi2Params[idx].csi2PhyClk                    = CHAINS_UB960_CSI_DATA_RATE;
            }
            else
            {
                pPrm->csi2Params[idx].csi2PhyClk                    = issClkParam;
            }
        }
        pPrm->csi2Params[0].isCmplxIoCfgValid = TRUE;
    }
    else
    {
        UTILS_assert(pPrm->videoIfMode == SYSTEM_VIFM_SCH_CSI2);
        UTILS_assert(pPrm->videoIfWidth == SYSTEM_VIFW_4LANES);
        numSensors = pPrm->numCh;
        pPrm->numCh += pCfgOut->numRadars;
        for (i = numSensors; i < pPrm->numCh; i++)
        {
            retVal = Chains_ar12xxGetDataRateParams(pCfgOut, (i-numSensors), &issClkParam, &issDataFormat);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

            pPrm->outParams[i].dataFormat = SYSTEM_DF_BAYER_BGGR;
            pPrm->outParams[i].inCsi2DataFormat = (System_Csi2DataFormat) issDataFormat;
            pPrm->outParams[i].inCsi2VirtualChanNum = i;
            pPrm->outParams[i].numOutBuf = 3U;

            if (pPrm->outParams[i].inCsi2DataFormat == SYSTEM_CSI2_RAW8)
            {
                pPrm->outParams[i].width = pCfgOut->radarParams[i-numSensors].csi2OutWidth * 2U;
            }
            else
            {
                pPrm->outParams[i].width = pCfgOut->radarParams[i-numSensors].csi2OutWidth;
            }
            pPrm->outParams[i].height = pCfgOut->radarParams[i-numSensors].csi2OutHeight;

            pPrm->outParams[i].maxWidth = pPrm->outParams[i].width;
            pPrm->outParams[i].maxHeight = pPrm->outParams[i].height;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to Set up Multiple VIP capture parameters
 *
 * \param   pPrm        VIP Capture Link params
 * \param   pAr12xxCfg  Pointer to the radar configuration structure
 * \param   portId[]    VIP Port Id array
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetMultiVipCaptureParams(
                        CaptureLink_CreateParams *pPrm,
                        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
                        UInt32 portId[]
                        )
{
    UInt32 i, streamId;
    UInt32 numCh = pAr12xxCfg->numRadars;
    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrm;
    CaptureLink_VipPortConfig    *pPortCfg;
    UInt32 defaultPortId[SYSTEM_CAPTURE_VIP_INST_MAX] = {
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA),
    };


    memset(pPrm, 0, sizeof(*pPrm));

    pPrm->numVipInst = numCh;
    pPrm->numDssWbInst = 0;

    if (NULL == portId)
    {
        portId = defaultPortId;
    }

    for (i=0; i<numCh; i++)
    {
        pInstPrm = &pPrm->vipInst[i];

        UTILS_assert(portId != NULL);
        pInstPrm->vipInstId     =   portId[i];

        pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
        pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
        pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
        pInstPrm->numStream     =   1;

        pInprms = &pInstPrm->inParams;
        if (i < numCh)
        {
            pInprms->width      =   pAr12xxCfg->radarParams[i].csi2OutWidth;
            pInprms->height     =   pAr12xxCfg->radarParams[i].csi2OutHeight;
        }
        else
        {
            pInprms->width      =   0;
            pInprms->height     =   0;
        }
        pInprms->dataFormat =   SYSTEM_DF_YUV422I_YUYV;
        pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   pInprms->width;
            pOutprms->height        =   pInprms->height;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV422I_YUYV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            pOutprms->scEnable      =   FALSE;

            /* sub-frame not supported, set to FALSE */
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

        }
        pScPrm = &pInstPrm->scPrms;
        pScPrm->inCropCfg.cropStartX = 0;
        pScPrm->inCropCfg.cropStartY = 0;
        pScPrm->inCropCfg.cropWidth = pInprms->width;
        pScPrm->inCropCfg.cropHeight = pInprms->height;

        pScPrm->scCfg.bypass       = FALSE;
        pScPrm->scCfg.nonLinear    = FALSE;
        pScPrm->scCfg.stripSize    = 0;

        pScPrm->userCoeff = FALSE;

        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;

        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_LOW;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                            SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        if (portId[i] ==  VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA))
        {
            pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        }
        else
        {
            pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_FALLING;
            Bsp_platformSetVipClkInversion(pInstPrm->vipInstId, TRUE);
        }
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;

        pPortCfg->actCropEnable                         =   FALSE;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT + 2;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to flash and erase AR12 QSPI flash via UART communication
 *          interface to the AR12 ROM
 *
 * \param   None
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxFirmwareFlash(void)
{
    char ch;
    Bool done = FALSE;
    Int32 retVal = BSP_SOK;
    static UInt32 eraseDone = 0U;
    Bsp_BoardId boardId;
    ChainsCommon_Ar12xxConfigOut ar12xxConfigOut;

    char gChainsCommon_ar12xxFlashMenu[] = {
        "\r\n "
        "\r\n AR12XX Flash Programming Menu"
        "\r\n -----------------------------"
        "\r\n "
        "\r\n 1: Erase AR12xx Flash."
        "\r\n "
        "\r\n 2: Flash AR12xx Firmware."
        "\r\n "
        "\r\n x: Exit"
        "\r\n "
        "\r\n Enter Choice: "
        "\r\n "
    };
    boardId = Bsp_boardGetId();
    if (boardId == BSP_BOARD_TDA2XX_CASCADE_RADAR)
    {
#if defined (BOARD_TDA2XX_CASCADE_RADAR)
        /* Fill params for cascade, params are used in cascade Algo */
        Chains_ar12xxGetSampleCascadeConfig(&ar12xxConfigOut);
#endif
    }
    else
    {
        Chains_ar12xxGetSampleConfig(&ar12xxConfigOut, 0U);
    }
    ar12xxConfigOut.numRadars = 1;
    ChainsCommon_ar12xxInit(&ar12xxConfigOut);

    while(!done)
    {
        Vps_printf(gChainsCommon_ar12xxFlashMenu);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            case '1':
                /* Only erase the flash such that the flash is empty */
                if (eraseDone == 0U)
                {
                    Vps_printf(" CHAINS: Started erasing the AR12 flash memory....\n\r");
                    retVal = Bsp_ar12xxEraseFirmware();
                    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
                    eraseDone = 1U;
                    Vps_printf(" CHAINS: Erasing AR12 flash memory completed.\n\r");
                }
                else
                {
                    Vps_printf(" CHAINS: Erasing AR12 flash memory already done.\n\r");
                }
                break;
            case '2':
                /* Flash the MSS, BSS and Config sections of the firmware.
                 */
                if (eraseDone == 0U)
                {
                    Vps_printf(" CHAINS: Started erasing the AR12 flash memory....\n\r");
                    retVal = Bsp_ar12xxEraseFirmware();
                    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
                    Vps_printf(" CHAINS: Erasing AR12 flash memory completed.\n\r");
                }
                Vps_printf(" CHAINS: Started flashing the AR12 firmware....\n\r");
                retVal = Bsp_ar12xxFlashFirmware();
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
                eraseDone = 0U;
                Vps_printf(" CHAINS: Finished flashing the AR12 firmware.\n\r");
                break;
            case 'x':
            case 'X':
                done = TRUE;
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
    ChainsCommon_ar12xxDeInit(&ar12xxConfigOut);
}

/**
 *******************************************************************************
 *
 * \brief   Function to check if the profile, chirp and frame configurations
 *          are okay
 *
 * \param   None
 *
 * \return  retval SYSTEM_LINK_STATUS_SOK if the parameters are matching the
 *                 programmed values.
 *
 *******************************************************************************
*/
Int32 ChainsCommon_ar12xxCheckParameters(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    rlProfileCfg_t retProfConfig;
    rlChirpCfg_t   retChirpConfig;
    rlFrameCfg_t   retFrameConfig;
    rlAdvFrameCfg_t retAdvFrame;
    rlDevDataFmtCfg_t retDataFormat;
    rlDevDataPathCfg_t retDataPath;
    rlDevCsi2Cfg_t retCsiLane;

    UInt32 i = 0;
    UInt32 j = 0;
    for (j = 0; j < pCfgOut->numRadars; j++)
    {
        Vps_printf(" CHAINS: Checking Profile Configuration Parameters \n\r");
        /* Check for the profile configurations */
        for (i = 0; i < pCfgOut->radarParams[j].ar12xxConfig.numProfileCfgArgs; i++)
        {
            retVal = Bsp_ar12xxGetConfiguredParam(0, BSP_AR12XX_CONFIG_PROFILE_PARAM,
                                                   i,
                                                   &retProfConfig);
            if ((0 == memcmp(&retProfConfig,
                            &pCfgOut->radarParams[j].ar12xxConfig.profileCfgArgs[i],
                            sizeof(rlProfileCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
            {
                retVal = SYSTEM_LINK_STATUS_SOK;
            }
            else if (retVal == BSP_EUNSUPPORTED_CMD)
            {
                /* Do nothing as an ES1.0 AR device has been detected */
                retVal = SYSTEM_LINK_STATUS_SOK;
                break;
            }
            else
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                Vps_printf(" CHAINS: Profile Config Param Id %d did not match!!\n", i);
            }
        }
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" CHAINS: Checking Chirp Configuration Parameters \n\r");
            /* Check for the chirp configurations */
            for (i = 0U; i < pCfgOut->radarParams[j].ar12xxConfig.numChirpCfgArgs; i++)
            {
                retVal = Bsp_ar12xxGetConfiguredParam(0, BSP_AR12XX_CONFIG_CHIRP_PARAM,
                                                   i,
                                                   &retChirpConfig);
                if ((0 == memcmp(&retChirpConfig,
                                &pCfgOut->radarParams[j].ar12xxConfig.chirpCfgArgs[i],
                                sizeof(rlChirpCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
                {
                    retVal = SYSTEM_LINK_STATUS_SOK;
                }
                else if (retVal == BSP_EUNSUPPORTED_CMD)
                {
                    /* Do nothing as an ES1.0 AR device has been detected */
                    retVal = SYSTEM_LINK_STATUS_SOK;
                    break;
                }
                else
                {
                    retVal = SYSTEM_LINK_STATUS_EFAIL;
                    Vps_printf(" CHAINS: Chirp Config Param Id %d did not match!!\n", i);
                }
            }
        }
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            if (gChainsCommon_ar12xxFrameType[j] == 0U)
            {
                Vps_printf(" CHAINS: Checking Frame Configuration Parameters \n\r");
            }
            else
            {
                Vps_printf(" CHAINS: Checking Advanced Frame Configuration Parameters \n\r");
            }
            /* Check for the frame configurations */
            for (i = 0U; i < 1U; i++)
            {
                retVal += Bsp_ar12xxGetConfiguredParam(0,BSP_AR12XX_CONFIG_FRAME_PARAM,
                                                   i,
                                                   &retFrameConfig);
                if ((0 == memcmp(&retFrameConfig,
                                &pCfgOut->radarParams[j].ar12xxConfig.frameCfgArgs[i],
                                sizeof(rlFrameCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
                {
                    retVal += SYSTEM_LINK_STATUS_SOK;
                }
                else if ((0 == memcmp(&retAdvFrame,
                                &pCfgOut->radarParams[j].ar12xxConfig.advFrameCfgArgs,
                                sizeof(rlAdvFrameCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
                {
                    retVal += SYSTEM_LINK_STATUS_SOK;
                }
                else if (retVal == BSP_EUNSUPPORTED_CMD)
                {
                    /* Do nothing as an ES1.0 AR device has been detected */
                    retVal = SYSTEM_LINK_STATUS_SOK;
                    break;
                }
                else
                {
                    retVal = SYSTEM_LINK_STATUS_EFAIL;
                    Vps_printf(" CHAINS: Frame/Adv Frame Config Param did not match!!\n");
                }
            }
        }
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" CHAINS: Checking Data Format Configuration Parameters \n\r");
            retVal = Bsp_ar12xxGetConfiguredParam(0, BSP_AR12XX_CONFIG_DATA_FORMAT,
                                               0,
                                               &retDataFormat);
            if ((0 == memcmp(&retDataFormat,
                            &pCfgOut->radarParams[j].ar12xxConfig.dataFmtCfgArgs,
                            sizeof(rlDevDataFmtCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
            {
                retVal = SYSTEM_LINK_STATUS_SOK;
            }
            else if (retVal == BSP_EUNSUPPORTED_CMD)
            {
                /* Do nothing as an ES1.0 AR device has been detected */
                retVal = SYSTEM_LINK_STATUS_SOK;
                break;
            }
            else
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                Vps_printf(" CHAINS: Data Format Param did not match!!\n");
            }
        }
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" CHAINS: Checking Data Path Configuration Parameters \n\r");
            retVal = Bsp_ar12xxGetConfiguredParam(0, BSP_AR12XX_CONFIG_DATA_PATH,
                                               0,
                                               &retDataPath);
            if ((0 == memcmp(&retDataPath,
                            &pCfgOut->radarParams[j].ar12xxConfig.dataPathCfgArgs,
                            sizeof(rlDevDataPathCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
            {
                retVal = SYSTEM_LINK_STATUS_SOK;
            }
            else if (retVal == BSP_EUNSUPPORTED_CMD)
            {
                /* Do nothing as an ES1.0 AR device has been detected */
                retVal = SYSTEM_LINK_STATUS_SOK;
                break;
            }
            else
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                Vps_printf(" CHAINS: Data Path Param did not match!!\n");
            }
        }
#if 0
        /* This is currently commented out as this feature is found to fail.
         * Debug discussions ongoing with the firmware team as to why this API is
         * returning 0s.
         */
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            rlDevDataPathClkCfg_t retDataPathClk;
            Vps_printf(" CHAINS: Checking Data Path Clock Configuration Parameters \n\r");
            retVal = Bsp_ar12xxGetConfiguredParam(0, BSP_AR12XX_CONFIG_LVDS_CLK,
                                               0,
                                               &retDataPathClk);
            if ((0 == memcmp(&retDataPathClk,
                            &pCfgOut->radarParams[j].ar12xxConfig.dataPathClkCfgArgs,
                            sizeof(rlDevDataPathClkCfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
            {
                retVal = SYSTEM_LINK_STATUS_SOK;
            }
            else if (retVal == BSP_EUNSUPPORTED_CMD)
            {
                /* Do nothing as an ES1.0 AR device has been detected */
                retVal = SYSTEM_LINK_STATUS_SOK;
                break;
            }
            else
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                Vps_printf(" CHAINS: Data Path Clock Param did not match!!\n");
            }
        }
#endif
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" CHAINS: Checking CSI Lanes Configuration Parameters \n\r");
            retVal = Bsp_ar12xxGetConfiguredParam(0, BSP_AR12XX_CONFIG_CSI_LANES,
                                               0,
                                               &retCsiLane);
            if ((0 == memcmp(&retCsiLane,
                            &pCfgOut->radarParams[j].ar12xxConfig.csiConfigArgs,
                            sizeof(rlDevCsi2Cfg_t))) && (retVal == SYSTEM_LINK_STATUS_SOK))
            {
                retVal = SYSTEM_LINK_STATUS_SOK;
            }
            else if (retVal == BSP_EUNSUPPORTED_CMD)
            {
                /* Do nothing as an ES1.0 AR device has been detected */
                retVal = SYSTEM_LINK_STATUS_SOK;
                break;
            }
            else
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                Vps_printf(" CHAINS: CSI Lane Param did not match!!\n");
            }
        }
        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
    }

    if (retVal == SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf(" CHAINS: Parameters have matched with programmed!!\n");
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief   Function to change the profile parameters at run time
 *
 * \param   algId       Algorithm Link ID for the FFT Heat Map
 * \param   pAr12xxCfg  Pointer to the configuration structure.
 *
 * \return  retval SYSTEM_LINK_STATUS_SOK if the parameter change has happened.
 *
 *******************************************************************************
*/
Int32 ChainsCommon_ar12xxChangeParameters(UInt32 algId, ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
#if defined(CHAINS_AR1243_STOP_RESTART)
    UInt32 numchirps;
    UInt32 timeToSleep = 0U, i = 0U;
    Vps_printf(" CHAINS: AR12xx Stopping Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxStopRadar();
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    Vps_printf(" CHAINS: AR12xx Radar Stopped ...\n\r");

    if (Bsp_ar12xxGetDeviceRevision() == 1U)
    {
        /* This sleep is required else the Radar re-start fails. Fixed in 0.8 DFP
         * with async event for stop frame. Worst case delay assumed with buffer.
         */
        Vps_printf(" CHAINS: Sleeping till frame is done ...\n\r");
        for (i = 0U ; i < pCfgOut->numRadars ; i++)
        {
            if (gChainsCommon_ar12xxFrameType[i] == 1U)
            {
                if (timeToSleep < pCfgOut->radarParams[i].ar12xxConfig.frameCfgArgs->framePeriodicity)
                {
                    timeToSleep = pCfgOut->radarParams[i].ar12xxConfig.frameCfgArgs->framePeriodicity;
                }
            }
            else
            {
                UInt32 time;
                time =
                 pCfgOut->radarParams[i].ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[0].subFramePeriodicity +
                 pCfgOut->radarParams[i].ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[1].subFramePeriodicity +
                 pCfgOut->radarParams[i].ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[2].subFramePeriodicity +
                 pCfgOut->radarParams[i].ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[3].subFramePeriodicity;
                if (timeToSleep < time)
                {
                    timeToSleep = time;
                }
            }
        }
        /* Normal Frame */
        BspOsal_sleep(CHAINS_AR1243_TIME_5NS_TO_MS(timeToSleep));
    }

    /* Change the parameters as required. This is application specific. The consumer of this
     * function can choose to modify any parameter of their choice here corresponding to any Radar Device.
     * Below is just an example of setting one parameter of one Radar.
     */
    if (gChainsCommon_ar12xxFrameType[0] == 1U)
    {
        numchirps = pCfgOut->radarParams[0].ar12xxConfig.frameCfgArgs->numLoops;
    }
    else
    {
        numchirps = pCfgOut->radarParams[0].ar12xxConfig.advFrameCfgArgs.frameSeq.subFrameCfg[0].numLoops;
    }
    if (pCfgOut->radarParams[0].ar12xxConfig.profileCfgArgs[0].freqSlopeConst
            == CHAINS_AR1243_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(62.4))
    {
        pCfgOut->radarParams[0].ar12xxConfig.profileCfgArgs[0].freqSlopeConst =
                CHAINS_AR1243_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(32.4);
    }
    else
    {
        pCfgOut->radarParams[0].ar12xxConfig.profileCfgArgs[0].freqSlopeConst =
                CHAINS_AR1243_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(62.4);
    }
    ChainsCommon_CalcResolution(&pCfgOut->radarParams[0].ar12xxConfig.profileCfgArgs[0],
                                &pCfgOut->radarParams[0].rangeRes[0],
                                &pCfgOut->radarParams[0].velocityRes[0], numchirps);
    pCfgOut->radarParams[0].currProfileId = 0;
    Vps_printf(" CHAINS: Reconfiguring Parameters ...\n\r");
    retVal = Bsp_ar12xxConfigParams(BSP_AR12XX_CONFIG_PROFILE_PARAM);
    Vps_printf(" CHAINS: Reconfigured Parameters ...\n\r");

    Vps_printf(" CHAINS: AR12xx Re-starting Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxStartRadar();
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    Vps_printf(" CHAINS: AR12xx Radar Started ...\n\r");
#else
    /* Performing Dynamic Chirp Configuration of a single Radar */
    static UInt32 currProfile = 1U;
    const UInt32 radarNum = 0U;
    Int32 j = 0;
    rlDynChirpCfg_t dynChirp = {
            .chirpRowSelect = (rlUInt8_t) 0,
            .chirpSegSel = (rlUInt8_t) 0,
            .programMode = (rlUInt16_t) 0,
            .chirpRow    = {0}
    };
    Vps_printf(" CHAINS: AR12xx Chirp Reconfig Started ...\n\r");
    Vps_printf(" CHAINS: AR12xx Profile Id %d ...\n\r", currProfile);
    pCfgOut->radarParams[radarNum].currProfileId = currProfile;
    memcpy(&dynChirp.chirpRow, &pCfgOut->radarParams[radarNum].chirpRow[currProfile * 16], sizeof(rlChirpRow_t) * 16);
    retVal = Bsp_ar12xxReconfigChirp(radarNum, &dynChirp, 1);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    for ( j = 0; j < pCfgOut->radarParams[radarNum].ar12xxConfig.numChirpCfgArgs; j++)
    {
        pCfgOut->radarParams[radarNum].ar12xxConfig.chirpCfgArgs[j].profileId = currProfile;
    }
    Vps_printf(" CHAINS: AR12xx Chirp Reconfig Done ...\n\r");
    currProfile = (currProfile + 1) % pCfgOut->radarParams[radarNum].ar12xxConfig.numProfileCfgArgs;
#endif
    return retVal;
}

static Void ChainsCommon_ar12xxInit(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal = BSP_SOK;
    Bsp_BoardId boardId;
    UInt32 i;
    char ch;
    UInt32 done = FALSE;

    /* Get the initial default parameters for the radar link configuration */
    Bsp_ar12xxInitParams_init (&gAr12xx_initParams);

    gAr12xx_initParams.numRadarDevicesInCascade = pCfgOut->numRadars;
    gAr12xx_initParams.masterDevId = 0;
    boardId = Bsp_boardGetId();

    /* Only RVP with FPD-Link Connection type may have more than 1 radars */
    for (i=0; i<pCfgOut->numRadars; i++)
    {
        if (boardId == BSP_BOARD_TDA3XX_AR12XX_ALPS)
        {
            Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
            {(UInt8) 3, (UInt8) 15, (UInt16) 51};     /* GPIO4, Pin 15, CPU Intr 51 */
            Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
            = {
            /* GPIO2, PIN 7 BSP_AR12XX_GPIO_OUTPUT_NRESET */
            {(UInt8) 1,    (UInt8) 7},
            /* GPIO2, PIN 6: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
            {(UInt8) 1, (UInt8) 6},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
            {(UInt8) 0xFF, (UInt8) 5 },
            /* GPIO1, PIN 5: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
            {(UInt8) 0, (UInt8) 5},
            /* GPIO1 PIN 4:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
            {(UInt8) 0, (UInt8) 4},
            /* GPIO1 PIN 6:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
            {(UInt8) 0, (UInt8) 6},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
            {(UInt8) 0xFF, (UInt8) 0},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
            {(UInt8) 0xFF, (UInt8) 0}
            };
            memcpy(&gAr12xx_initParams.devParams[i].inGpioParams, &inGpioParamsDef,
                   sizeof (inGpioParamsDef));
            memcpy(&gAr12xx_initParams.devParams[i].outGpioParams, outGpioParamsDef,
                   sizeof (outGpioParamsDef));

            /* Use McSPI 2 */
            gAr12xx_initParams.devParams[i].mcSpiDevInst = 1U;
            gAr12xx_initParams.devParams[i].mcspiChannel = 0U;
            Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST1);
        }
        else if ((boardId == BSP_BOARD_TDA3XX_RVP_ALPHA)
                || (boardId == BSP_BOARD_TDA3XX_RVP_BETA)
                || (boardId == BSP_BOARD_TDA3XX_RVP_A)
                || (boardId == BSP_BOARD_TDA3XX_D3_SK))
        {
            Bsp_Ar12xxGpioInputParams  inGpioParamsDef;

            if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_DIRECT)
            {
                /* GPIO4, Pin 15, CPU Intr 51 */
                inGpioParamsDef.gpioInstId = 3;
                inGpioParamsDef.gpioPinNum = 15;
                inGpioParamsDef.cpuIntrIdForGpio = 51;

                Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
                = {
                /* GPIO2, PIN 7 BSP_AR12XX_GPIO_OUTPUT_NRESET */
                {(UInt8) 1,    (UInt8) 7},
                /* Not Used: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
                {(UInt8) 0xFF, (UInt8) 17},
                /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
                {(UInt8) 0xFF, (UInt8) 5 },
                /* GPIO2, PIN 14: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
                {(UInt8) 1, (UInt8) 14},
                /* GPIO2, PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
                {(UInt8) 1, (UInt8) 13},
                /* GPIO2, PIN 12:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
                {(UInt8) 1, (UInt8) 12},
                /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
                {(UInt8) 0xFF, (UInt8) 0},
                /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
                {(UInt8) 0xFF, (UInt8) 0}
                };
                memcpy(&gAr12xx_initParams.devParams[i].inGpioParams, &inGpioParamsDef,
                       sizeof (inGpioParamsDef));
                memcpy(&gAr12xx_initParams.devParams[i].outGpioParams, outGpioParamsDef,
                       sizeof (outGpioParamsDef));
                gAr12xx_initParams.devParams[i].mcSpiDevInst = 1U;
                gAr12xx_initParams.devParams[i].mcspiChannel = 0U;
                Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST1);
            }
            else
            {
                /* GPIO2, Pin 6 ~ 9, CPU Intr 51 */
                inGpioParamsDef.gpioInstId = 1;
                inGpioParamsDef.gpioPinNum = 6 + i;
                inGpioParamsDef.cpuIntrIdForGpio = 51;
                memcpy(&gAr12xx_initParams.devParams[i].inGpioParams, &inGpioParamsDef,
                       sizeof (inGpioParamsDef));

                gAr12xx_initParams.devParams[i].i2cDevInst = UB960_ACCESSIBLE_FROM_I2C_INST;
                gAr12xx_initParams.devParams[i].i2cDevAddr = D3_AR1243_PORT_0_SENSOR_ADDR + i*2;
                gAr12xx_initParams.devParams[i].desPortMap = i;
                gAr12xx_initParams.devParams[i].uartDevInst = 0xFF;
            }
        }
        else if (boardId == BSP_BOARD_TDA2XX_CASCADE_RADAR)
        {
            /* Master AR1243 */
            if (i == 0)
            {
                Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
                {(UInt8) 6, (UInt8) 24, (UInt16) 51};     /* GPIO7, Pin 24, CPU Intr 51 */
                Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
                = {
                    /* GPIO2, PIN 2 BSP_AR12XX_GPIO_OUTPUT_NRESET */
                    {(UInt8) 1,    (UInt8) 2},
                    /* GPIO2, PIN 12: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
                    {(UInt8) 1, (UInt8) 12},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
                    {(UInt8) 0xFF, (UInt8) 5 },
                    /* GPIO1, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
                    {(UInt8) 1, (UInt8) 22},
                    /* GPIO1 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
                    {(UInt8) 1, (UInt8) 25},
                    /* GPIO1 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
                    {(UInt8) 1, (UInt8) 13},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
                    {(UInt8) 0, (UInt8) 16},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
                    {(UInt8) 0, (UInt8) 17}

                };
                memcpy(&gAr12xx_initParams.devParams[0].inGpioParams, &inGpioParamsDef,
                       sizeof (inGpioParamsDef));
                memcpy(&gAr12xx_initParams.devParams[0].outGpioParams, outGpioParamsDef,
                       sizeof (outGpioParamsDef));

                /* Use McSPI1 */
                gAr12xx_initParams.devParams[0].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST0;
                gAr12xx_initParams.devParams[0].mcspiChannel = 0U;
                Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST0);
                /* Set the EDMA Handle */
                gAr12xx_initParams.devParams[0].uartDevInst = 2;
            }
            if (i == 1)
            /* Slave 1 AR1243 */
            {
                Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
                {(UInt8) 4, (UInt8) 10, (UInt16) 52};  /* GPIO5, Pin 10, CPU Intr 52 */

                Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
                = {
                    /* GPIO2, PIN 9 BSP_AR12XX_GPIO_OUTPUT_NRESET */
                    {(UInt8) 1,    (UInt8) 9},
                    /* GPIO2, PIN 15: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
                    {(UInt8) 1, (UInt8) 12 },
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
                    {(UInt8) 0xFF, (UInt8) 19 },
                    /* GPIO2, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
                    {(UInt8) 1, (UInt8) 22},
                    /* GPIO2 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
                    {(UInt8) 1, (UInt8) 25},
                    /* GPIO2 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
                    {(UInt8) 1, (UInt8) 13},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
                    {(UInt8) 0xFF, (UInt8) 0},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
                    {(UInt8) 0xFF, (UInt8) 0}

                };
                memcpy(&gAr12xx_initParams.devParams[1].inGpioParams, &inGpioParamsDef,
                       sizeof (inGpioParamsDef));
                memcpy(&gAr12xx_initParams.devParams[1].outGpioParams, outGpioParamsDef,
                       sizeof (outGpioParamsDef));

                if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
                {
                    /* Use McSPI3 */
                    gAr12xx_initParams.devParams[1].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST2;
                    gAr12xx_initParams.devParams[1].mcspiChannel = 0U;
                }
                else
                {
                    /* Use McSPI2 */
                    gAr12xx_initParams.devParams[1].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST1;
                    gAr12xx_initParams.devParams[1].mcspiChannel = 0U;
                    Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST1);
                }
                gAr12xx_initParams.devParams[1].uartDevInst = 0xFF;
            }
            /* Slave 2 AR1243 */
            if (i == 2)
            {
                Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
                {(UInt8) 4, (UInt8) 11, (UInt16) 52}; /* GPIO5, Pin 11, CPU Intr 52 */
                Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
                =
                {
                    /* GPIO2, PIN 10 BSP_AR12XX_GPIO_OUTPUT_NRESET */
                    {(UInt8) 1,    (UInt8) 10},
                    /* GPIO2, PIN 12: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
                    {(UInt8) 1, (UInt8) 12 },
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
                    {(UInt8) 0xFF, (UInt8) 19 },
                    /* GPIO2, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
                    {(UInt8) 1, (UInt8) 22},
                    /* GPIO2 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
                    {(UInt8) 1, (UInt8) 25},
                    /* GPIO2 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
                    {(UInt8) 1, (UInt8) 13},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
                    {(UInt8) 0xFF, (UInt8) 0},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
                    {(UInt8) 0xFF, (UInt8) 0}
                };
                memcpy(&gAr12xx_initParams.devParams[2].inGpioParams, &inGpioParamsDef,
                       sizeof (inGpioParamsDef));
                memcpy(&gAr12xx_initParams.devParams[2].outGpioParams, outGpioParamsDef,
                       sizeof (outGpioParamsDef));

                if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
                {
                    /* Use McSPI3 */
                    gAr12xx_initParams.devParams[2].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST2;
                    gAr12xx_initParams.devParams[2].mcspiChannel = 1U;
                    Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST2);
                }
                else
                {
                    /* Use McSPI3 */
                    gAr12xx_initParams.devParams[2].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST2;
                    gAr12xx_initParams.devParams[2].mcspiChannel = 0U;
                    Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST2);
                }
                gAr12xx_initParams.devParams[2].uartDevInst = 0xFF;
            }
            /* Slave 3 AR1243 */
            if (i == 3)
            {
                Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
                {(UInt8) 6, (UInt8) 25, (UInt16) 51}; /* GPIO7, Pin 25, CPU Intr 51 */
                Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
                =
                {
                    /* GPIO2, PIN 11 BSP_AR12XX_GPIO_OUTPUT_NRESET */
                    {(UInt8) 1,    (UInt8) 11},
                    /* GPIO2, PIN 15: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
                    {(UInt8) 1, (UInt8) 12 },
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
                    {(UInt8) 0xFF, (UInt8) 19 },
                    /* GPIO2, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
                    {(UInt8) 1, (UInt8) 22},
                    /* GPIO2 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
                    {(UInt8) 1, (UInt8) 25},
                    /* GPIO2 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
                    {(UInt8) 1, (UInt8) 13},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
                    {(UInt8) 0xFF, (UInt8) 0},
                    /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
                    {(UInt8) 0xFF, (UInt8) 0}
                };
                memcpy(&gAr12xx_initParams.devParams[3].inGpioParams, &inGpioParamsDef,
                       sizeof (inGpioParamsDef));
                memcpy(&gAr12xx_initParams.devParams[3].outGpioParams, outGpioParamsDef,
                       sizeof (outGpioParamsDef));

                if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
                {
                    /* Use McSPI3 */
                    gAr12xx_initParams.devParams[3].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST0;
                    gAr12xx_initParams.devParams[3].mcspiChannel = 1U;
                }
                else
                {
                    /* Use McSPI4 */
                    gAr12xx_initParams.devParams[3].mcSpiDevInst = CHAINS_AWR1243_SENSOR_MCSPI_INST3;
                    gAr12xx_initParams.devParams[3].mcspiChannel = 0U;
                    Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST3);
                }
                gAr12xx_initParams.devParams[3].uartDevInst = 0xFF;
            }
        }
        else if (boardId == BSP_BOARD_VISION)
        {
#if (defined(TDA2PX_BUILD) && defined(PLATFORM_EVM_SI))
            /* TDA2P EVM with Fusion Board*/
            /* Enable Board Mux for CSI2 via setting SEL_CSI2 in EXPANDER3 */
            UInt8  regValue[2];
            UInt32 i2cInst, ioExpAddr, numRegs;
            Int32  retVal;

            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = 0x26U;
            numRegs   = 2U;
            retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
            UTILS_assert(BSP_SOK == retVal);

            regValue[1] &= 0xFE;
            retVal    = Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
            UTILS_assert(BSP_SOK == retVal);

            /* Set GPIO7_7 to HIGH for I2C_SW_SOC_TDA2XX on Fusion Board */
            /* Set GPIO7_9 as input for AWR1243 Host IRQ */
            Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                                      (UInt32) CTRL_CORE_PAD_SPI1_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                                      (UInt32) CTRL_CORE_PAD_SPI1_D0,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            GPIOModuleEnable(SOC_GPIO7_BASE);
            GPIODirModeSet(
                    SOC_GPIO7_BASE,
                    7,
                    GPIO_DIR_OUTPUT);
            GPIOPinWrite(
                    SOC_GPIO7_BASE,
                    7,
                    GPIO_PIN_HIGH);
            GPIODirModeSet(
                    SOC_GPIO7_BASE,
                    9,
                    GPIO_DIR_INPUT);

            Bsp_Ar12xxGpioInputParams  inGpioParamsDef;
            /* GPIO7, Pin 9, CPU Intr 51 */
            inGpioParamsDef.gpioInstId = 6;
            inGpioParamsDef.gpioPinNum = 9;
            inGpioParamsDef.cpuIntrIdForGpio = 51;
            memcpy(&gAr12xx_initParams.devParams[i].inGpioParams, &inGpioParamsDef,
                   sizeof (inGpioParamsDef));

            gAr12xx_initParams.devParams[i].i2cDevInst = UB960_ACCESSIBLE_FROM_I2C_INST;
            if (pCfgOut->fusionEnabled == 0U)
            {
                gAr12xx_initParams.devParams[i].i2cDevAddr = D3_AR1243_PORT_0_SENSOR_ADDR + i*2;
                gAr12xx_initParams.devParams[i].desPortMap = i;
            }
            else
            {
                gAr12xx_initParams.devParams[0].i2cDevAddr = D3_AR1243_FUSION_SENSOR_ADDR;
                gAr12xx_initParams.devParams[0].desPortMap = 1;
            }
            gAr12xx_initParams.devParams[i].uartDevInst = 0xFF;
#else
            Vps_printf("ChainsCommon_ar12xxInit: Warning!! Unsupported Platform...");
#endif
        }
        else
        {
            Utils_mcspiInit(CHAINS_AWR1243_SENSOR_MCSPI_INST0);
        }

        if ((Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_DIRECT) &&
            (gAr12xx_initParams.devParams[i].uartDevInst != 0xFF))
        {
            Utils_uartCreateDevice(gAr12xx_initParams.devParams[i].uartDevInst, &uartAr12FlashDevObj);
        }

        retVal = Bsp_ar12xxRegisterConfig(pCfgOut->radarParams[i].configName,
                                          &pCfgOut->radarParams[i].ar12xxConfig);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
        strcpy(gAr12xx_initParams.devParams[i].radarConfigName, pCfgOut->radarParams[i].configName);

        /* Set the EDMA Handle */
        gAr12xx_initParams.devParams[i].edmaHandle = Utils_dmaGetEdma3Hndl(UTILS_DMA_SYSTEM_EDMA_INST_ID);
    }

    retVal = Bsp_ar12xxInit(&gAr12xx_initParams);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

    /* This is an optional step if the only a single AR1243 configuration is used.
     * If there are more than one configurations used then one can use the following API to
     * switch between configurations after performing Bsp_ar12xxInit.
     */
    for (i=0; i<pCfgOut->numRadars; i++)
    {
        retVal = Bsp_ar12xxSwitchConfig(i, pCfgOut->radarParams[i].configName);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
    }

    if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_FPDLINK)
    {
        if (pCfgOut->fusionEnabled == 0U)
        {
            /* Select FVID2_VID_SENSOR_AR1243_2G_DRV or FVID2_VID_SENSOR_AR1243_4G_DRV */
            done = FALSE;
            while (!done)
            {
                ch = ChainsCommon_ar12xxRunTimeMenu(gChains_ub960RunTimeMenu);
                if (ch == '1')
                {
                    Vps_printf(" CHAINS: UB960 is configured for 2Gbps Mode \n\r");
                    BspUtils_appUb960InitAR12xx(FVID2_VID_SENSOR_AR1243_2G_DRV, pCfgOut->numRadars);
                    done = TRUE;
                }
                else if (ch == '2')
                {
                    Vps_printf(" CHAINS: UB960 is configured for 4Gbps Mode \n\r");
                    BspUtils_appUb960InitAR12xx(FVID2_VID_SENSOR_AR1243_4G_DRV, pCfgOut->numRadars);
                    done = TRUE;
                }
                else
                {
                    Vps_printf(" CHAINS: Unsupported option '%c'. Please try again\n", ch);
                }
            }
        }
        else
        {
            /* UB960 is already initialized by ISS Sensor driver for Fusion */
            BspUtils_appUb960InitAR12xx(FVID2_VID_SENSOR_FUSION_DRV, (pCfgOut->numRadars + 1));
        }
    }
}

Void ChainsCommon_ar12xxDeInit(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    Bsp_BoardId boardId;
    UInt32 i;
    UInt32 uartDeInitRequired = 0U;

    boardId = Bsp_boardGetId();
    Vps_printf(" CHAINS: AR12xx De-initing Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxDeInit();
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

    for(i=0; i<pCfgOut->numRadars; i++)
    {
        retVal = Bsp_ar12xxUnRegisterConfig(pCfgOut->radarParams[i].configName);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
        if (gAr12xx_initParams.devParams[i].uartDevInst != 0xFF)
        {
            uartDeInitRequired = 1U;
        }
    }

    Vps_printf(" CHAINS: AR12xx De-initing McSPI ...\n\r");

    if (boardId == BSP_BOARD_TDA3XX_AR12XX_ALPS)
    {
        Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST1);
    }
    else if ((boardId == BSP_BOARD_TDA3XX_RVP_ALPHA)
            || (boardId == BSP_BOARD_TDA3XX_RVP_BETA)
            || (boardId == BSP_BOARD_TDA3XX_RVP_A)
            || (boardId == BSP_BOARD_TDA3XX_D3_SK))
    {
        if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_DIRECT)
        {
            Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST1);
        }
    }
    else if (boardId == BSP_BOARD_TDA2XX_CASCADE_RADAR)
    {
        Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST0);
        Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST2);
        if (Bsp_boardGetBaseBoardRev() >= BSP_BOARD_REV_E)
        {
            Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST1);
            Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST3);
        }
    }
    else
    {
        Utils_mcspiDeinit(CHAINS_AWR1243_SENSOR_MCSPI_INST0);
    }
    if ((Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_DIRECT) && (uartDeInitRequired == 1U))
    {
        Utils_uartDeleteDevice(&uartAr12FlashDevObj);
    }
}

static Void ChainsCommon_CalcResolution(rlProfileCfg_t *profile,
                                        float          *range,
                                        float          *velocity,
                                        uint32_t       numChirps)
{
    float sampling_rate, slope, speedOfLight;
    float startFreq, chirpRepetitionTime;

    /* Range resolution is derived using the formula:
     * deltaR =       speed of light
     *          --------------------------- (in meters)
     *          (2 x Radar Chirp Bandwidth)
     * Radar Chirp Bandwidth = Chirp Slope * Number of samples per chirp
     *                         -----------------------------------------
     *                                     Sampling Rate
     */
    sampling_rate = profile->digOutSampleRate * 100.0;
    slope = profile->freqSlopeConst * 48.0;
    speedOfLight = 3.0;
    *range = (sampling_rate * speedOfLight)/
                    (2.0 * slope * (float)profile->numAdcSamples);

    /* Velocity Resolution is derived using the formula:
    *                         1                    speed of light
    * deltaV = ----------------------------- x ------------------------ (in m/s)
    *          Doppler Dimention x Chirp Time    2 x Starting Frequency
    */
    startFreq = profile->startFreqConst * 54.0;
    chirpRepetitionTime = (profile->rampEndTime
                    + profile->idleTimeConst)
                    * 10.0/1000000000;
    *velocity = (speedOfLight * 100000000.0)/
                            (numChirps * 2.0 * chirpRepetitionTime * startFreq);
}

static Void ChainsCommon_CalcChirpRows(ChainsCommon_Ar12xxConfigOut *pCfgOut)
{
    Int32 i = 0, j = 0, k = 0;
    for (k = 0; k < pCfgOut->numRadars; k++)
    {
        rlChirpRow_t    * chirpRowPtr = pCfgOut->radarParams[k].chirpRow;
        for ( i = 0; i < pCfgOut->radarParams[k].ar12xxConfig.numProfileCfgArgs; i++)
        {
            for ( j = 0; j < pCfgOut->radarParams[k].ar12xxConfig.numChirpCfgArgs; j++)
            {
                rlChirpCfg_t * chirpCfg = &pCfgOut->radarParams[k].ar12xxConfig.chirpCfgArgs[j];
                rlBpmChirpCfg_t * bpmChirp = &pCfgOut->radarParams[k].ar12xxConfig.bpmChirpCfgArgs[j];
                chirpRowPtr[i * 16 + j].chirpNR1 = (rlUInt32_t)(((chirpCfg->profileId + i) & 0xF) |
                                                           ((chirpCfg->freqSlopeVar << 8) & 0x3F00) |
                                                           ((chirpCfg->txEnable << 16) & 0x70000)   |
                                                           ((bpmChirp->constBpmVal << 24) & 0x3F000000));
                chirpRowPtr[i * 16 + j].chirpNR2 = (rlUInt32_t)((chirpCfg->startFreqVar & 0x7FFFFF));
                chirpRowPtr[i * 16 + j].chirpNR3 = (rlUInt32_t)((chirpCfg->idleTimeVar & 0xFFF) |
                                                           ((chirpCfg->adcStartTimeVar << 16) & 0xFFF0000));
            }
            for ( j = pCfgOut->radarParams[k].ar12xxConfig.numChirpCfgArgs; j < 16; j++)
            {
                chirpRowPtr[i * 16 + j].chirpNR1 = (rlUInt32_t)0;
                chirpRowPtr[i * 16 + j].chirpNR2 = (rlUInt32_t)0;
                chirpRowPtr[i * 16 + j].chirpNR3 = (rlUInt32_t)0;
            }
        }
    }
}

UInt32 Chains_ar12xxCountOnes(UInt32 num)
{
    UInt32 count = 0U;
    /* Count the number of binary ones in the given number. */
    while (num != 0U)
    {
        count++;
        num = num & (num - 1U);
    }
    return count;
}

static Int32 Chains_ar12xxGetDataRateParams(ChainsCommon_Ar12xxConfigOut *pCfgOut,
                                            UInt32 radarIdx,
                                            UInt32 *issClkParam,
                                            UInt32 *issDataParam)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    /* Derive the ISS clock from the dataRate parameter */
    switch (pCfgOut->radarParams[radarIdx].ar12xxConfig.dataPathClkCfgArgs.dataRate)
    {
        case 6: *issClkParam = 75U; break;
        case 4: *issClkParam = 150U; break;
        case 3: *issClkParam = 200U; break;
        case 2: *issClkParam = 225U; break;
        case 1: *issClkParam = 300U; break;
        default: retVal = SYSTEM_LINK_STATUS_EFAIL;
    }
    if (retVal == SYSTEM_LINK_STATUS_SOK)
    {
        switch (pCfgOut->radarParams[radarIdx].ar12xxConfig.dataFmtCfgArgs.adcBits)
        {
            case RL_ADC_DATA_12_BIT: *issDataParam = SYSTEM_CSI2_RAW12; break;
            case RL_ADC_DATA_14_BIT: *issDataParam = SYSTEM_CSI2_RAW14; break;
            case RL_ADC_DATA_16_BIT: *issDataParam = SYSTEM_CSI2_RAW8; break;
            default: retVal = SYSTEM_LINK_STATUS_EFAIL;
        }
    }
    return retVal;
}
