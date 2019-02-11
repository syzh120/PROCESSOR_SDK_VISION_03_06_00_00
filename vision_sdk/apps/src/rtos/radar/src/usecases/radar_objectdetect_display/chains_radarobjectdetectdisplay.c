/******************************************************************************
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

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
#include "chains_radarobjectdetectdisplay_priv.h"
#include <include/common/chains_radar.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/**
 *******************************************************************************
 *
 *  \brief  Chains_radarobjectdetectdisplayObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_radarobjectdetectdisplayObj ucObj;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;

    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    /* Algorithm Function Create Parameters */
    AlgorithmFxn_RadarFftCreateParams radarFftParams;
    AlgorithmFxn_RadarPkDetectCreateParams radarPkDetectParams;
    AlgorithmFxn_RadarBeamFormCreateParams radarBeamFormParams;
    AlgorithmFxn_RadarDrawCreateParams radarDrawParams;

} Chains_radarobjectdetectdisplayAppObj;

static char Chains_radarobjectdetectdisplay_runTimeMenu();
Void Chains_radarUnitTest_StartTestPattern(void);
Void Chains_radarunittest_programTestConfig(Void * appObj);

static UInt32 gAwrRadarUnitTest_noStop = 0U;
static UInt32 gAwrRadarUnitTest_noStart = 0U;
Void chains_radarobjectdetectdisplay_SetDisplayVideoPrms(DisplayLink_CreateParams *pPrm,
                         Chains_DisplayType displayType,
                         UInt32 w,
                         UInt32 h)
{
    if (pPrm)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
           (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm->rtParams.tarWidth  = w;
        pPrm->rtParams.tarHeight = h;
        pPrm->rtParams.posX      = 0;
        pPrm->rtParams.posY      = 0;
        pPrm->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Start the Links
 *
 *          Function sends a control command to all the links to
 *          to Start them. Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_radarobjectdetectdisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_radarobjectdetectdisplay_StartApp(Chains_radarobjectdetectdisplayAppObj *pObj)
{
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    Chains_memPrintHeapStatus();

    chains_radarobjectdetectdisplay_Start(&pObj->ucObj);

    if (gAwrRadarUnitTest_noStart == 0U)
    {
        ChainsCommon_ar12xxStart();
    }
    else
    {
        Chains_radarUnitTest_StartTestPattern();
    }
    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the usecase Links
 *
 *          Function sends a control command to all usecase links to
 *          to delete them
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_radarobjectdetectdisplayAppObj
 *
 *******************************************************************************
*/
Void chains_radarobjectdetectdisplay_StopAndDeleteApp(Chains_radarobjectdetectdisplayAppObj *pObj)
{
    chains_radarobjectdetectdisplay_Stop(&pObj->ucObj);
    chains_radarobjectdetectdisplay_Delete(&pObj->ucObj);

    if (gAwrRadarUnitTest_noStop == 0U)
    {
        ChainsCommon_ar12xxStop(&pObj->ar12xxCfg);
    }
    else
    {
        ChainsCommon_ar12xxDeInit(&pObj->ar12xxCfg);
    }
    ChainsCommon_ar12xxBeamFormDeInit(&pObj->ar12xxCfg, &pObj->radarBeamFormParams);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_radarobjectdetectdisplay_SetAppPrms(chains_radarobjectdetectdisplayObj *pUcObj, Void *appObj)
{
    Chains_radarobjectdetectdisplayAppObj *pObj
        = (Chains_radarobjectdetectdisplayAppObj*)appObj;

    Chains_radarunittest_programTestConfig(appObj);

    ChainsCommon_ar12xxConfig(&pObj->ar12xxCfg);
    ChainsCommon_ar12xxSetIssCaptureParams(&pUcObj->IssCapturePrm, &pObj->ar12xxCfg);

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );
    ChainsCommon_ar12xxSetFFTParams(
        &pObj->radarFftParams,
        &pObj->ar12xxCfg
        );
    ChainsCommon_ar12xxSetPkDetectParams(
        &pObj->radarPkDetectParams,
        &pObj->ar12xxCfg
        );
    ChainsCommon_ar12xxSetBeamFormParams(
        &pObj->radarBeamFormParams,
        &pObj->ar12xxCfg
        );
    ChainsCommon_ar12xxSetRadarDrawParams(
        &pObj->radarDrawParams,
        &pObj->ar12xxCfg,
        pObj->displayWidth,
        pObj->displayHeight);

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight
                                );

    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGRA16_4444;

    ChainsCommon_SetDisplayPrms(NULL,
                                &pUcObj->Display_GrpxPrm,
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight
                               );
    chains_radarobjectdetectdisplay_SetDisplayVideoPrms(&pUcObj->DisplayPrm,
                        pObj->chainsCfg->displayType,
                        pObj->displayWidth,
                        pObj->displayHeight);
    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    return;
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel radar sensor (AR1243) capture processing and display
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarobjectdetectdisplay(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_radarobjectdetectdisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.ucObj.Alg_RadarProcess_fftPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams;

    chainsObj.ucObj.Alg_RadarProcess_pkDetectPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarPkDetectParams;
    chainsObj.ucObj.Alg_RadarProcess_beamFormPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarBeamFormParams;
    chainsObj.ucObj.Alg_RadarProcess_drawObjsPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarDrawParams;

    chains_radarobjectdetectdisplay_Create(&chainsObj.ucObj, &chainsObj);

    chains_radarobjectdetectdisplay_StartApp(&chainsObj);

    while(!done)
    {

        ch = Chains_radarobjectdetectdisplay_runTimeMenu();
        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'c':
            case 'C':
                ChainsCommon_ar12xxCheckParameters(&chainsObj.ar12xxCfg);
                break;
            case 'd':
            case 'D':
                /* For the 0th Profile */
                ChainsCommon_ar12xxChangeParameters(
                    chainsObj.ucObj.Alg_RadarProcess_drawObjsLinkID,
                    &chainsObj.ar12xxCfg);
                ChainsCommon_ar12xxSetDrawProfile(
                    chainsObj.ucObj.Alg_RadarProcess_drawObjsLinkID,
                    &chainsObj.ar12xxCfg,
                    chainsObj.ar12xxCfg.radarParams[0].currProfileId);
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_radarobjectdetectdisplay_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_radarobjectdetectdisplay_StopAndDeleteApp(&chainsObj);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
static char gChains_radarCaptProcWrite_customRunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n c: Read-back and Check AR params"
    "\r\n "
    "\r\n d: Dynamically change params "
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

static char Chains_radarobjectdetectdisplay_runTimeMenu()
{
    Vps_printf(gChains_radarCaptProcWrite_customRunTimeMenu);

    return Chains_readChar();
}

static char gChains_radarUnitTestMenu[] = {
    "\r\n "
    "\r\n ========================"
    "\r\n Unit Test case Selection"
    "\r\n ========================"
    "\r\n "
    "\r\n 1: Default Sample Normal Frame Configuration"
    "\r\n "
    "\r\n 2: Default Sample Advanced Frame Configuration"
    "\r\n "
    "\r\n 3: Binary Phase Modulation"
    "\r\n "
    "\r\n 4: Finite Frames"
    "\r\n "
    "\r\n 5: Test Pattern Generation "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


static rlChirpCfg_t   gAwrBpmChirpCfgArgs[] =
{
    {
        .chirpStartIdx   = (rlUInt16_t) 0x0,
        .chirpEndIdx     = (rlUInt16_t) 0x0,
        .profileId       = (rlUInt16_t) 0x0, /* First profile */
        .startFreqVar    = (rlUInt32_t) 0x0,
        .freqSlopeVar    = (rlInt16_t) 0x0,
        .idleTimeVar     = (rlUInt16_t) 0x0,
        .adcStartTimeVar = (rlUInt16_t) 0x0,
        .txEnable        = (rlUInt16_t) 0x5, /* TX1 */
        .reserved        = (rlUInt16_t) 0x0
    },
    {
        .chirpStartIdx   = (rlUInt16_t) 0x1,
        .chirpEndIdx     = (rlUInt16_t) 0x1,
        .profileId       = (rlUInt16_t) 0x0, /* First profile */
        .startFreqVar    = (rlUInt32_t) 0x0,
        .freqSlopeVar    = (rlInt16_t) 0x0,
        .idleTimeVar     = (rlUInt16_t) 0x0,
        .adcStartTimeVar = (rlUInt16_t) 0x0,
        .txEnable        = (rlUInt16_t) 0x5, /* TX2 */
        .reserved        = (rlUInt16_t) 0x0
    }
};
static rlBpmChirpCfg_t   gAwrBpmTestArgs[] =
{
    {
        .chirpStartIdx = (rlUInt16_t) 0x0,
        .chirpEndIdx   = (rlUInt16_t) 0x0,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    },
    {
        .chirpStartIdx = (rlUInt16_t) 0x1,
        .chirpEndIdx   = (rlUInt16_t) 0x1,
        .constBpmVal   = (rlUInt16_t) 0x20,
        .reserved      = (rlUInt16_t) 0x0
    }
};

Void Chains_radarunittest_programTestConfig(Void * appObj)
{
    char ch;
    UInt32 done = FALSE;
    Chains_radarobjectdetectdisplayAppObj *pObj
        = (Chains_radarobjectdetectdisplayAppObj*)appObj;

    Chains_ar12xxGetSampleConfig(&pObj->ar12xxCfg, 0U);
    gAwrRadarUnitTest_noStop = 0U;
    gAwrRadarUnitTest_noStart = 0U;
    while(!done)
    {
        Vps_printf(gChains_radarUnitTestMenu);
        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                pObj->ar12xxCfg.frameType = 0U;
                done = TRUE;
                break;
            case '2':
                pObj->ar12xxCfg.frameType = 1U;
                done = TRUE;
                break;
            case '3':
                pObj->ar12xxCfg.radarParams[0].ar12xxConfig.bpmChirpCfgArgs = gAwrBpmTestArgs;
                pObj->ar12xxCfg.radarParams[0].ar12xxConfig.numBpmChirpCfgArgs = sizeof(gAwrBpmTestArgs)/sizeof(rlBpmChirpCfg_t);
                pObj->ar12xxCfg.radarParams[0].ar12xxConfig.chirpCfgArgs      = gAwrBpmChirpCfgArgs;
                pObj->ar12xxCfg.radarParams[0].ar12xxConfig.numChirpCfgArgs   = sizeof(gAwrBpmChirpCfgArgs)/sizeof(rlChirpCfg_t);
                pObj->ar12xxCfg.radarParams[0].ar12xxConfig.rfChanCfgArgs.txChannelEn = 0x7;
                done = TRUE;
                break;
            case '4':
                pObj->ar12xxCfg.radarParams[0].ar12xxConfig.frameCfgArgs->numFrames = 10;
                gAwrRadarUnitTest_noStop = 1U;
                done = TRUE;
                break;
            case '5':
                gAwrRadarUnitTest_noStart = 1U;
                gAwrRadarUnitTest_noStop = 1U;
                done = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

}

Void Chains_radarUnitTest_StartTestPattern(void)
{
    UInt32 i = 0U;
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    rltestPattern_t testPatternCfg =
        {
            .testPatGenCtrl = 0x1,
            .testPatGenTime = 32,
            .testPatrnPktSize = 256,
            .numTestPtrnPkts = 128,
            .testPatRx0Icfg = 0x00020000,
            .testPatRx0Qcfg = 0x00020001,
            .testPatRx1Icfg = 0x0000AAAA,
            .testPatRx1Qcfg = 0x00005555,
            .testPatRx2Icfg = 0x00020000,
            .testPatRx2Qcfg = 0x00020001,
            .testPatRx3Icfg = 0x00001111,
            .testPatRx3Qcfg = 0x00008888
        };
    for (i = 0U; i < 10U; i++)
    {
        retVal = Bsp_ar12xxStartTestPattern(&testPatternCfg);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);
        Task_sleep(33);
    }
}


