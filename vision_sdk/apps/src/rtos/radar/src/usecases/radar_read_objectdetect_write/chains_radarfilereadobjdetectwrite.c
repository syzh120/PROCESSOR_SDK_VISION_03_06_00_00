/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
#include "chains_radarfilereadobjdetectwrite_priv.h"
#include <include/common/chains_radar.h>
#include <include/common/chains_radar_file_io.h>


#define CHAINS_RADAR_INPUT_FILE             "Input_512x128_4Rx_1Tx_1TS_10Frm.bin"
#define CHAINS_RADAR_CHIRP_SIZE             (512U)
#define CHAINS_RADAR_HEIGHT                 (128U)
#define CHAINS_RADAR_NUM_RX_ANTENNA           (4U)
#define CHAINS_RADAR_NUM_TX_ANTENNA           (1U)
#define CHAINS_RADAR_NUM_FRAMES              (10U)
#define CHAINS_RADAR_HEAT_MAP_RANGE_RES     ((float)0.07862822061191625)
#define CHAINS_RADAR_HEAT_MAP_VELOCITY_RES  ((float)0.2256548202963532)

/**
 *******************************************************************************
 *
 *  \brief  Chains_radarreadobjdetectwriteObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_radarfilereadobjdetectwriteObj ucFileObj;

    UInt32  displayWidth;
    UInt32  displayHeight;
    FileIO_CreateParams FileIoPrm;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;

    Chains_Ctrl *chainsCfg;

    /* Algorithm Function Create Parameters */
    AlgorithmFxn_RadarFftCreateParams radarFftParams;
    AlgorithmFxn_RadarPkDetectCreateParams radarPkDetectParams;
    AlgorithmFxn_RadarBeamFormCreateParams radarBeamFormParams;
    AlgorithmFxn_RadarDrawCreateParams radarDrawParams;

} Chains_radarreadobjdetectwriteAppObj;

static char Chains_customfftRunTimeMenu();

Void chains_radarreadobjdetectwrite_SetDisplayVideoPrms(DisplayLink_CreateParams *pPrm,
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
 * \param   pObj  [IN] Chains_radarreadobjdetectwriteAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_radarreadobjdetectwrite_StartApp(Chains_radarreadobjdetectwriteAppObj *pObj)
{
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    Chains_memPrintHeapStatus();

    chains_radarfilereadobjdetectwrite_Start(&pObj->ucFileObj);

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
 * \param   pObj   [IN]   Chains_radarreadobjdetectwriteAppObj
 *
 *******************************************************************************
*/
Void chains_radarreadobjdetectwrite_StopAndDeleteApp(Chains_radarreadobjdetectwriteAppObj *pObj)
{
    chains_radarfilereadobjdetectwrite_Stop(&pObj->ucFileObj);
    chains_radarfilereadobjdetectwrite_Delete(&pObj->ucFileObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    Chains_fileClose();
    Chains_fileDeInit(&pObj->FileIoPrm);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}
/**
 *******************************************************************************
 *
 * \brief   Set link Parameters for file link
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcFileObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_radarfilereadobjdetectwrite_SetAppPrms(chains_radarfilereadobjdetectwriteObj *pUcFileObj, Void *appObj)
{
    Chains_radarreadobjdetectwriteAppObj *pObj
        = (Chains_radarreadobjdetectwriteAppObj*)appObj;
    UInt32 chId;
    NullSrcLink_CreateParams *pNullSrcPrm;
    NullLink_CreateParams *pNullPrm;
    System_LinkChInfo *pChInfo;
    FileIO_CreateParams *pFileIoPrm;

    pObj->ar12xxCfg.radarParams[0].csi2OutWidth = CHAINS_RADAR_CHIRP_SIZE*2*CHAINS_RADAR_NUM_RX_ANTENNA;
    pObj->ar12xxCfg.radarParams[0].csi2OutHeight= CHAINS_RADAR_HEIGHT*CHAINS_RADAR_NUM_TX_ANTENNA;
    pObj->ar12xxCfg.radarParams[0].radarWidth[0]   = CHAINS_RADAR_CHIRP_SIZE;
    pObj->ar12xxCfg.radarParams[0].radarHeight[0]  = CHAINS_RADAR_HEIGHT;
    pObj->ar12xxCfg.radarParams[0].numTxAntenna[0] = CHAINS_RADAR_NUM_TX_ANTENNA;
    pObj->ar12xxCfg.radarParams[0].numRxAntenna[0] = CHAINS_RADAR_NUM_RX_ANTENNA;
    pObj->ar12xxCfg.radarParams[0].numProfiles = 1;
    pObj->ar12xxCfg.radarParams[0].numValidBits = 16;
    pObj->ar12xxCfg.radarParams[0].inBufAddrOffset = 0;
    pObj->ar12xxCfg.radarParams[0].offsetBwAntennas[0] = CHAINS_RADAR_CHIRP_SIZE*4;
    pObj->ar12xxCfg.numRadars = 1;

    pNullSrcPrm = &pUcFileObj->NullSourcePrm;
    pNullPrm = &pUcFileObj->NullPrm;
    pFileIoPrm = &pObj->FileIoPrm;

    /*
     * Set NullSrc Params
     */
    pNullSrcPrm->outQueInfo.numCh = 1;
    for (chId = 0; chId < pNullSrcPrm->outQueInfo.numCh; chId++)
    {
        pNullSrcPrm->channelParams[chId].fileReadMode = NULLSRC_LINK_FILEREAD_DISABLE;

        pChInfo = &pNullSrcPrm->outQueInfo.chInfo[chId];

        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                                    SYSTEM_DF_YUV422I_YUYV);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                                    SYSTEM_SF_PROGRESSIVE);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                               SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
        pChInfo->width = pObj->ar12xxCfg.radarParams[0].csi2OutWidth;
        pChInfo->height = pObj->ar12xxCfg.radarParams[0].csi2OutHeight;
        pChInfo->startX = 0U;
        pChInfo->startY = 0U;
        pChInfo->pitch[0U] = SystemUtils_align(pChInfo->width*2, 32U);
        pChInfo->pitch[1U] = pChInfo->pitch[0U];

        pNullSrcPrm->channelParams[chId].numBuffers
                                        = NULL_SRC_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }

    pNullSrcPrm->timerPeriodMilliSecs = 40;

    pNullSrcPrm->dataRxMode = NULLSRC_LINK_DATA_RX_MODE_CUSTOM;
    pNullSrcPrm->appCb = Chains_readFrameCb;
    pNullSrcPrm->appCbArg = pFileIoPrm;

    /*
     * Set Null Params
     */
    pNullPrm->appCb = Chains_writeFrameCb;
    pNullPrm->appCbArg = pFileIoPrm;

    /*
     * Set FileIO Params
     */
    pChInfo = &pNullSrcPrm->outQueInfo.chInfo[0];

    strncpy(pFileIoPrm->channelParams[0].nameDataFile, CHAINS_RADAR_INPUT_FILE, 260);

    pFileIoPrm->channelParams[0].frameSize =
                            (pChInfo->pitch[0] * pChInfo->height);

    pFileIoPrm->readFromCfg = FALSE;
    pFileIoPrm->cfgOptions.startFrameNum = 0;
    pFileIoPrm->cfgOptions.stopFrameNum = CHAINS_RADAR_NUM_FRAMES;
    pFileIoPrm->cfgOptions.repeatMode = TRUE;

    Chains_fileInit(pFileIoPrm);

    /*
     * Set Display Params
     */
    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SetGrpxSrcPrms(&pUcFileObj->GrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight
                                );

    pUcFileObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGRA16_4444;

    ChainsCommon_SetDisplayPrms(NULL,
                                &pUcFileObj->Display_GrpxPrm,
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight
                               );

    chains_radarreadobjdetectwrite_SetDisplayVideoPrms(&pUcFileObj->Display_VideoPrm,
                        pObj->chainsCfg->displayType,
                        pObj->displayWidth,
                        pObj->displayHeight);

    /*
     * Set FFT Params
     */
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

    pObj->radarDrawParams.rangeRes[0] = CHAINS_RADAR_HEAT_MAP_RANGE_RES;
    pObj->radarDrawParams.velocityRes[0] = CHAINS_RADAR_HEAT_MAP_VELOCITY_RES;

    /*
     * Set Display Control Params
     */
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
 * \brief   Pre-recorded SD card read, radar frame copy and write to SD Card
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
Void Chains_radarfilereadobjdetectwrite(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_radarreadobjdetectwriteAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.ucFileObj.Alg_RadarProcess_fftPrm =
                (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams;
    chainsObj.ucFileObj.Alg_RadarProcess_pkDetectPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarPkDetectParams;
    chainsObj.ucFileObj.Alg_RadarProcess_beamFormPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarBeamFormParams;
    chainsObj.ucFileObj.Alg_RadarProcess_drawObjsPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarDrawParams;

    chains_radarfilereadobjdetectwrite_Create(&chainsObj.ucFileObj, &chainsObj);

    chains_radarreadobjdetectwrite_StartApp(&chainsObj);

    while(!done)
    {

        ch = Chains_customfftRunTimeMenu(&chainsObj);
        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_radarfilereadobjdetectwrite_printStatistics(&chainsObj.ucFileObj);
                break;
            case 'f' :
                Chains_fileIOMenu();
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_radarreadobjdetectwrite_StopAndDeleteApp(&chainsObj);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
static char gChains_customfftFileRunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n f: File IO Menu "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

static char Chains_customfftRunTimeMenu(Chains_radarreadobjdetectwriteAppObj *pchainsObj)
{
    Vps_printf(gChains_customfftFileRunTimeMenu);

    return Chains_readChar();
}


