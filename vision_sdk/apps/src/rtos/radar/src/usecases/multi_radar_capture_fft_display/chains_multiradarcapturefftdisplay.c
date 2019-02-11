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
#include "chains_multiradarcapturefftdisplay_priv.h"
#include <include/common/chains_radar.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *******************************************************************************
 *
 *  \brief  Chains_multiradarcapturefftdisplayObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_multiradarcapturefftdisplayObj ucObj;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;

    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    /* Algorithm Function Create Parameters */
    AlgorithmFxn_RadarFftCreateParams radarFftParams;
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams RadarDrawFFTHeatMapPrm;

} Chains_multiradarcapturefftdisplayAppObj;

static char Chains_multiradarcapturefftdisplay_runTimeMenu();

Void chains_multiradarcapturefftdisplay_SetSelectLinkOutputCh(UInt32 linkId, UInt32 ch)
{
    SelectLink_OutQueChInfo ctrlPrms;
    ctrlPrms.inChNum[0] = ch;
    ctrlPrms.numOutCh = 1;
    ctrlPrms.outQueId = 0;

    System_linkControl(
                    linkId,
                    SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO,
                    &ctrlPrms,
                    sizeof(ctrlPrms),
                    TRUE
                    );

}

Void chains_multiradarcapturefftdisplay_SetDisplayVideoPrms(DisplayLink_CreateParams *pPrm,
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
 * \param   pObj  [IN] Chains_multiradarcapturefftdisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_multiradarcapturefftdisplay_StartApp(Chains_multiradarcapturefftdisplayAppObj *pObj)
{
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    Chains_memPrintHeapStatus();

    chains_multiradarcapturefftdisplay_Start(&pObj->ucObj);

    ChainsCommon_ar12xxStart();

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
 * \param   pObj   [IN]   Chains_multiradarcapturefftdisplayAppObj
 *
 *******************************************************************************
*/
Void chains_multiradarcapturefftdisplay_StopAndDeleteApp(Chains_multiradarcapturefftdisplayAppObj *pObj)
{
    chains_multiradarcapturefftdisplay_Stop(&pObj->ucObj);
    chains_multiradarcapturefftdisplay_Delete(&pObj->ucObj);

    ChainsCommon_ar12xxStop(&pObj->ar12xxCfg);

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
Void chains_multiradarcapturefftdisplay_SetAppPrms(chains_multiradarcapturefftdisplayObj *pUcObj, Void *appObj)
{
    Chains_multiradarcapturefftdisplayAppObj *pObj
        = (Chains_multiradarcapturefftdisplayAppObj*)appObj;

    Chains_ar12xxGetSampleConfig(&pObj->ar12xxCfg, 0U);
    ChainsCommon_ar12xxConfig(&pObj->ar12xxCfg);
    ChainsCommon_ar12xxSetIssCaptureParams(&pUcObj->IssCapturePrm, &pObj->ar12xxCfg);

    pUcObj->SelectPrm.numOutQue = 1;
    pUcObj->SelectPrm.outQueChInfo[0].numOutCh = 1;
    pUcObj->SelectPrm.outQueChInfo[0].inChNum[0] = 0;
    pUcObj->SelectPrm.outQueChInfo[0].outQueId = 0;


    ChainsCommon_ar12xxSetFFTParams(
        &pObj->radarFftParams,
        &pObj->ar12xxCfg
        );

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_ar12xxSetFFTHeatMapParams(
        &pObj->RadarDrawFFTHeatMapPrm,
        &pObj->ar12xxCfg,
        pObj->displayWidth,
        pObj->displayHeight
        );

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

    chains_multiradarcapturefftdisplay_SetDisplayVideoPrms(&pUcObj->Display_VideoPrm,
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
Void Chains_multiradarcapturefftdisplay(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_multiradarcapturefftdisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.ucObj.Alg_RadarProcess_fftPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams;

    chainsObj.ucObj.Alg_RadarProcess_drawPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.RadarDrawFFTHeatMapPrm;

    chains_multiradarcapturefftdisplay_Create(&chainsObj.ucObj, &chainsObj);

    chains_multiradarcapturefftdisplay_StartApp(&chainsObj);

    while(!done)
    {

        ch = Chains_multiradarcapturefftdisplay_runTimeMenu();
        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                chains_multiradarcapturefftdisplay_SetSelectLinkOutputCh(
                                                    chainsObj.ucObj.SelectLinkID, 0);
                break;
            case '2':
                chains_multiradarcapturefftdisplay_SetSelectLinkOutputCh(
                                                    chainsObj.ucObj.SelectLinkID, 1);
                break;
            case '3':
                chains_multiradarcapturefftdisplay_SetSelectLinkOutputCh(
                                                    chainsObj.ucObj.SelectLinkID, 2);
                break;
            case '4':
                chains_multiradarcapturefftdisplay_SetSelectLinkOutputCh(
                                                    chainsObj.ucObj.SelectLinkID, 3);
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_multiradarcapturefftdisplay_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_multiradarcapturefftdisplay_StopAndDeleteApp(&chainsObj);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
static char gChains_multiradarCaptProcWrite_customRunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n Change Radar:"
    "\r\n              1: Radar 1"
    "\r\n              2: Radar 2"
    "\r\n              3: Radar 3"
    "\r\n              4: Radar 4"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

static char Chains_multiradarcapturefftdisplay_runTimeMenu()
{
    Vps_printf(gChains_multiradarCaptProcWrite_customRunTimeMenu);

    return Chains_readChar();
}

