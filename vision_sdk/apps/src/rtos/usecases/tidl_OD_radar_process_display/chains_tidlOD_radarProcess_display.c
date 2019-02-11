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
#include "chains_tidlOD_radarProcess_display_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_tidl.h>
#include <src/include/chains_common_osal.h>
#include "itidl_ti.h"
#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>
#include <include/common/chains_radar.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */
#define TIDL_OD_INPUT_WIDTH          (768)
#define TIDL_OD_INPUT_HEIGHT         (320)

#define DEC_OUT_WIDTH               (768)
#define DEC_OUT_HEIGHT              (320)

#define TIDL_OD_DISPLAY_WIDTH        (TIDL_OD_INPUT_WIDTH*2)
#define TIDL_OD_DISPLAY_HEIGHT       (TIDL_OD_INPUT_HEIGHT*2)
#define TIDL_OD_DISPLAY_STARTX       (1920 - TIDL_OD_DISPLAY_WIDTH)/2
#define TIDL_OD_DISPLAY_STARTY       (64)

/* Num of TIDL processing pipelines */
#define NUM_PIPELINES               (1)

/* Semantic Segmenation input fps */
/* This should be based on the TIDL performance on 4 EVEs */
/* It should be less than the cumulative TIDL performance on 4 EVEs */
/* For eg if each TIDL is giving performace of 3 fps then it should be less than (4 x 3)*/
#define TIDL_OD_FPS_OPPHIGH          (NUM_PIPELINES * 6)

#define TIDL_OD_FPS_OPPNOM           (NUM_PIPELINES * 5)

#define OPP_HIGH_FREQUENCY          (650U)

/* Palettes used for color look up */
#define MAX_NUM_PALETTE             (10)

#define SYNC_DELTA                  (10)

/* The threshold should be more than the TIDL process time */
/* For eg. if TIDL process time is 400 msec then this should be more than 400 msec */
#define SYNC_THRESHOLD              (600)

/* OCMC */
#define OCMC_1_BASE_ADDRESS         (0x40300000U)
#define OCMC_1_SIZE                 (512 * 1024)

#define OCMC_2_BASE_ADDRESS         (0x40400000U)
#define OCMC_2_SIZE                 (1024 * 1024)

#define OCMC_3_BASE_ADDRESS         (0x40500000U)
#define OCMC_3_SIZE                 (1024 * 1024)

#define NET_BIN_FILE                "NET_OD.BIN"
#define PARAMS_BIN_FILE             "PRM_OD.BIN"


/* DSP */
#define TIDL_COREID_DSP1            (1)
#define TIDL_LAYER_GROUPID_DSP1     (2)
#define TIDL_COREID_DSP2            (1)
#define TIDL_LAYER_GROUPID_DSP2     (2)

/* EVE */
#define TIDL_COREID_EVE1            (1)
#define TIDL_LAYER_GROUPID_EVE1     (1)
#define TIDL_COREID_EVE2            (1)
#define TIDL_LAYER_GROUPID_EVE2     (1)

/* Graphics window is just below the video window */
#define GRAPHICS_WIDTH              (1920)
#define GRAPHICS_HEIGHT             (1080 - TIDL_OD_DISPLAY_STARTY - TIDL_OD_DISPLAY_HEIGHT)

/*******************************************************************************
 *  STRUCTURES
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  chains_tidlODAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    chains_tidlOD_radarProcess_displayObj ucObj;
    UInt32 displayWidth;
    UInt32 displayHeight;
    Chains_Ctrl *chainsCfg;
    TIDL_CreateParams *pAlgCreateParams;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;

    /* Algorithm Function Create Parameters */
    AlgorithmFxn_RadarFftCreateParams radarFftParams;
    AlgorithmFxn_RadarPkDetectCreateParams radarPkDetectParams;
    AlgorithmFxn_RadarBeamFormCreateParams radarBeamFormParams;
    AlgorithmFxn_RadarDrawCreateParams radarDrawParams;

} chains_tidlOD_radarProcess_displayAppObj;

chains_tidlOD_radarProcess_displayAppObj gChainsObjtidlOD;

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
static char tidlOD_radarProcessRunTimeMenu[] = {
"\n "
"\n ===================="
"\n Chains Run-time Menu"
"\n ===================="
"\n "
"\n 0: Stop Chain"
"\n "
"\n 1: Pause Chain"
"\n 2: Resume Chain"
"\n "
"\n p: Print Statistics"
"\n "
"\n Enter Choice: "
"\n "
};

static Void chains_tidlOD_radarProcess_display_SetVPEPrms(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 displayWidth,
                    UInt32 displayHeight,
                    UInt32 inputWidth,
                    UInt32 inputHeight
                    )
{
    UInt16 chId;

    pPrm->enableOut[0] = TRUE;

    for(chId = 0; chId < numCh; chId++)
    {
        pPrm->chParams[chId].outParams[0].numBufsPerCh = 6;

        pPrm->chParams[chId].outParams[0].width = displayWidth;
        pPrm->chParams[chId].outParams[0].height = displayHeight;
        pPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;

        pPrm->chParams[chId].scCfg.bypass       = FALSE;
        pPrm->chParams[chId].scCfg.nonLinear    = FALSE;
        pPrm->chParams[chId].scCfg.stripSize    = 0;

        pPrm->chParams[chId].scCropCfg.cropStartX = 32;
        pPrm->chParams[chId].scCropCfg.cropStartY = 24;
        pPrm->chParams[chId].scCropCfg.cropWidth = inputWidth-32;
        pPrm->chParams[chId].scCropCfg.cropHeight = inputHeight-24;
    }
}

static Void tidlODInit(chains_tidlOD_radarProcess_displayAppObj *pObj)
{
    /* Read the network file */
    Chains_tidlReadNet(&pObj->pAlgCreateParams->net, NET_BIN_FILE);

    /* Allocate memory for the net */
    Chains_tidlAllocNetParamsMem(&pObj->pAlgCreateParams->net);

    /* Fill the new parameters */
    Chains_tidlFillNetParamsMem(&pObj->pAlgCreateParams->net, PARAMS_BIN_FILE);

    /* Init all the 3 instances of the OCMC */
    Utils_cbufOcmcInit(UTILS_OCMC_RAM1);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM2);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM3);
}


static Void tidlODDeInit(chains_tidlOD_radarProcess_displayAppObj *pObj)
{
    /* Free the net memories */
    Chains_tidlFreeNetParamsMem(&pObj->pAlgCreateParams->net);
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_tidlOD_radarProcess_displayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_tidlOD_radarProcess_display_StartApp(chains_tidlOD_radarProcess_displayAppObj *pObj)
{
    Chains_memPrintHeapStatus();
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
    ChainsCommon_ar12xxStart();
    chains_tidlOD_radarProcess_display_Start(&pObj->ucObj);
    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlOD_radarProcess_displayAppObj
 *
 *******************************************************************************
*/
Void chains_tidlOD_radarProcess_display_StopAndDelete(chains_tidlOD_radarProcess_displayAppObj *pObj)
{
    chains_tidlOD_radarProcess_display_Stop(&pObj->ucObj);
    chains_tidlOD_radarProcess_display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);
    ChainsCommon_ar12xxStop(&pObj->ar12xxCfg);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}


static Void ChainsCommon_tidlODSetObjectDrawPrms(
            AlgorithmLink_ObjectDrawCreateParams *pOdDrawPrm)
{

    pOdDrawPrm->imgFrameStartX   = 0;
    pOdDrawPrm->imgFrameStartY   = 0;
    pOdDrawPrm->imgFrameWidth   = TIDL_OD_INPUT_WIDTH;
    pOdDrawPrm->imgFrameHeight  = TIDL_OD_INPUT_HEIGHT;
    pOdDrawPrm->numOutBuffers    = 3;
    pOdDrawPrm->objectRectThickness = 1;
    pOdDrawPrm->objectTsrDrawTrafficSigns = FALSE;
    pOdDrawPrm->laneThickness = 2;
    pOdDrawPrm->laneDrawLines = FALSE;
    pOdDrawPrm->laneScaleX = 2.0;
    pOdDrawPrm->laneScaleY = 2.0;
    pOdDrawPrm->drawOption = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALL;
    pOdDrawPrm->numDrawAlg = 0;
    pOdDrawPrm->scoreThreshold = 0.5;
    pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
            = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_TIDL_OD;
    pOdDrawPrm->numDrawAlg++;
}
/**
 *******************************************************************************
 *
 * \brief   Semantic Segmentation
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void chains_tidlOD_radarProcess_display_SetAppPrms(chains_tidlOD_radarProcess_displayObj *pUcObj, Void *appObj)
{
    UInt32 frequency =  0;
    UInt32 FileReadFps = TIDL_OD_FPS_OPPNOM;

    chains_tidlOD_radarProcess_displayAppObj *pObj = (chains_tidlOD_radarProcess_displayAppObj*)appObj;

    frequency = Utils_getClkHz(UTILS_CLK_ID_EVE) / 1000000U;
    /*
     * Set the framerate according to the frequency
     */
    if (frequency >= OPP_HIGH_FREQUENCY)
    {
        FileReadFps = TIDL_OD_FPS_OPPHIGH;
    }
    else
    {
        FileReadFps = TIDL_OD_FPS_OPPNOM;
    }

    ChainsCommon_GetDisplayWidthHeight(
                                pObj->chainsCfg->displayType,
                                &pObj->displayWidth,
                                &pObj->displayHeight);

    ChainsCommon_SetFileRxPrms(
                        &pUcObj->NullSourcePrm,
                        &pUcObj->DecodePrm,
                        DEC_OUT_WIDTH,
                        DEC_OUT_HEIGHT,
                        1,                  /* numCh */
                        FileReadFps);        /* fps */

    /* SetFileRxPrm sets the file open to inHeader and inData overriding the same*/
    strncpy(pUcObj->NullSourcePrm.channelParams[0].nameDataFile, "inData_OD", 260);
    strncpy(pUcObj->NullSourcePrm.channelParams[0].nameIndexFile, "inHeader_OD", 260);

    chains_tidlOD_radarProcess_display_SetVPEPrms(
                    &pUcObj->VPEPrm,
                    1,
                    DEC_OUT_WIDTH,
                    DEC_OUT_HEIGHT,
                    DEC_OUT_WIDTH,
                    DEC_OUT_HEIGHT
                    );

    /* YUV420SP to planar RGB conversion */
    pUcObj->Alg_tidlpreprocPrm.outPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpreprocPrm.numOutputQueues = NUM_PIPELINES;
    pUcObj->Alg_tidlpreprocPrm.procMode = TIDLPREPROC_LINK_PROCMODE_Y2R;

    /* TIDL on EVE1 */
    pUcObj->Alg_tidl_Eve1Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_Eve1Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_Eve1Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_Eve1Prm.curCoreId = TIDL_COREID_EVE1;
    pUcObj->Alg_tidl_Eve1Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE1;
    pUcObj->Alg_tidl_Eve1Prm.ocmcAddr = OCMC_3_BASE_ADDRESS;

    /* TIDL on DSP */
    pUcObj->Alg_tidl_DspPrm.cacheInvInBuf = 1;
    pUcObj->Alg_tidl_DspPrm.cacheWbOutBuf = 1;
    pUcObj->Alg_tidl_DspPrm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_DspPrm.curCoreId = TIDL_COREID_DSP1;
    pUcObj->Alg_tidl_DspPrm.currLayersGroupId = TIDL_LAYER_GROUPID_DSP1;

    /* Sync parameters */
    pUcObj->SyncPrm.syncDelta = SYNC_DELTA;
    pUcObj->SyncPrm.syncThreshold = SYNC_THRESHOLD;

    ChainsCommon_tidlODSetObjectDrawPrms(&pUcObj->Alg_ObjectDrawPrm);
    ChainsCommon_SetDisplayPrms(
                                &pUcObj->DisplayPrm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = TIDL_OD_DISPLAY_WIDTH;
    pUcObj->DisplayPrm.rtParams.tarHeight = TIDL_OD_DISPLAY_HEIGHT;
    pUcObj->DisplayPrm.rtParams.posX = TIDL_OD_DISPLAY_STARTX;
    pUcObj->DisplayPrm.rtParams.posY = TIDL_OD_DISPLAY_STARTY;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight);

    /* Graphics source parameters */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = GRAPHICS_WIDTH;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = GRAPHICS_HEIGHT;
    pUcObj->GrpxSrcPrm.tidlOdOverlay = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = TIDL_OD_INPUT_WIDTH;
    pUcObj->GrpxSrcPrm.captureHeight = TIDL_OD_INPUT_HEIGHT;

    /* Graphics Display parameters */
    /* Graphics display will be at the end of the video display window */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = GRAPHICS_WIDTH;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = GRAPHICS_HEIGHT;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = \
            (pUcObj->DisplayPrm.rtParams.posY + TIDL_OD_DISPLAY_HEIGHT);
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;

    /* Radar Configurations */
    Chains_ar12xxGetSampleConfig(&pObj->ar12xxCfg, 0U);
    ChainsCommon_ar12xxConfig(&pObj->ar12xxCfg);
    ChainsCommon_ar12xxSetIssCaptureParams(&pUcObj->IssCapturePrm, &pObj->ar12xxCfg);

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
        pObj->displayWidth/2,
        pObj->displayHeight/2);

    pUcObj->Display_RadarPrm.rtParams.tarWidth = pObj->displayWidth/2;
    pUcObj->Display_RadarPrm.rtParams.tarHeight = pObj->displayHeight/2;
    pUcObj->Display_RadarPrm.rtParams.posX = pObj->displayWidth/4;
    pUcObj->Display_RadarPrm.rtParams.posY = pObj->displayHeight/2;
    pUcObj->Display_RadarPrm.displayId = DISPLAY_LINK_INST_DSS_VID2;

}

static Void pausetidlOD(chains_tidlOD_radarProcess_displayAppObj *pObj)
{
    Int32 status;

    status = System_linkControl(
                    pObj->ucObj.NullSourceLinkID,
                    NULL_SRC_LINK_CMD_PAUSE,
                    NULL,
                    0,
                    TRUE);
    UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);
}

static Void resumetidlOD(chains_tidlOD_radarProcess_displayAppObj *pObj)
{
    Int32 status;

    status = System_linkControl(
                    pObj->ucObj.NullSourceLinkID,
                    NULL_SRC_LINK_CMD_RESUME,
                    NULL,
                    0,
                    TRUE);
    UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);
}

/**
 *******************************************************************************
 *
 * \brief   Semantic Segmentation
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void Chains_tidlOD_radarProcess_display(Chains_Ctrl *chainsCfg)
{
    char ch;
    Bool done = FALSE;

    gChainsObjtidlOD.chainsCfg = chainsCfg;

    /* Allocate the Algorithm create structure */
    gChainsObjtidlOD.pAlgCreateParams = ChainsCommon_Osal_memAlloc(
                                        sizeof(TIDL_CreateParams),
                                        32);
    UTILS_assert(NULL != gChainsObjtidlOD.pAlgCreateParams);

    /* Semantic Segmentation Init */
    tidlODInit(&gChainsObjtidlOD);

    gChainsObjtidlOD.ucObj.Alg_RadarProcess_fftPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&gChainsObjtidlOD.radarFftParams;

    gChainsObjtidlOD.ucObj.Alg_RadarProcess_pkDetectPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&gChainsObjtidlOD.radarPkDetectParams;
    gChainsObjtidlOD.ucObj.Alg_RadarProcess_beamFormPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&gChainsObjtidlOD.radarBeamFormParams;
    gChainsObjtidlOD.ucObj.Alg_RadarProcess_drawObjsPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&gChainsObjtidlOD.radarDrawParams;

    chains_tidlOD_radarProcess_display_Create(&gChainsObjtidlOD.ucObj, &gChainsObjtidlOD);

    chains_tidlOD_radarProcess_display_StartApp(&gChainsObjtidlOD);

    do
    {
        Vps_printf(tidlOD_radarProcessRunTimeMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':
                pausetidlOD(&gChainsObjtidlOD);
                break;

            case '2':
                resumetidlOD(&gChainsObjtidlOD);
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_tidlOD_radarProcess_display_printStatistics(&gChainsObjtidlOD.ucObj);
                break;

            default:
                break;
        }
    }while(FALSE == done);

    chains_tidlOD_radarProcess_display_StopAndDelete(&gChainsObjtidlOD);

    /* Semantic Segmentation DeInit */
    tidlODDeInit(&gChainsObjtidlOD);

    /* Free the Algorithm create structure */
    ChainsCommon_Osal_memFree(
                gChainsObjtidlOD.pAlgCreateParams,
                sizeof(TIDL_CreateParams));
}
