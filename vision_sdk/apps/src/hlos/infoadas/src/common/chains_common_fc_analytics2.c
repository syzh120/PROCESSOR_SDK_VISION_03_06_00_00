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
#include <src/hlos/osa/include/osa_types.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/osa/include/osa_tsk.h>

#if 0
#include <src/include/chains_common.h>
#include <src/include/chains_common_sfm.h>
#endif

#define CAPTURE_SENSOR_WIDTH         (1280)
#define CAPTURE_SENSOR_HEIGHT        (720)

#define SFM_TRACK_POINTS             (1024)

#define SFM_CAM_PRM_FILE             "SFM_POSE.bin"

#define IMG_PMD_ROI_PERCENTAGE       (32)
#define IMG_PMD_SCALE_STEPS           (4)
#define IMG_PMD_NUM_SCALES           (14)

#define LD_ALG_WIDTH                 (640)
#define LD_ALG_HEIGHT                (360)

#define DRAW_SFM                     (0)
#define DRAW_SOF                     (0)

#define LIMP_HOME_DISPLAY_DURATION_MS   (24*60*60*1000)
#define LIMP_HOME_DISPLAY_FONTID        (5)


#define LD_CLIP_START_FRAME     (0)
#define LD_CLIP_END_FRAME       (2356)

#define LHM_INPUT_FPS            (10)
#define LHM_OUTPUT_FPS           (10)

/* Enable below macro to start the 10 seconds LHM on and 10 seconds LHM off test */
/* #define LHM_LOOP_TEST */

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraAnalyticsObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    UInt32  inStartX;
    UInt32  inStartY;
    UInt32  inWidth;
    UInt32  inHeight;

    Chains_CaptureSrc captureSrc;
    Chains_DisplayType displayType;

    UInt32 Alg_ImgPyramidLinkID;
    UInt32 Alg_FPComputeLinkID;
    UInt32 Alg_ObjectDrawLinkID;
    UInt32 Alg_ObjectClassificationLinkID;
    UInt32 Alg_LaneDetectLinkID;
    Bool   useImgPmd;

    Bool   taskExit;
    OSA_TskHndl taskHndl;
    Int8 tskName[32];

    Bool ldDrawEnable;

    AlgorithmLink_ObjectDrawOption drawOption;

    UInt32 currentLHMState;

} ChainsCommon_Analytics2Obj;

ChainsCommon_Analytics2Obj gChainsCommon_analytics2Obj;

Void Chains_vipSingleCameraAnalytics2_EventHandler(UInt32 cmd, Void *pPrm);

static Void ChainsCommon_Analytics2_SetObjectDrawPrms(
            ChainsCommon_Analytics2Obj *pObj,
            AlgorithmLink_ObjectDrawCreateParams *pOdDrawPrm,
            AlgorithmLink_ObjectDetectionCreateParams *pOdPrm,
            AlgorithmLink_ClrCreateParams *pClrPrm,
            AlgorithmLink_LaneDetectCreateParams *pLdPrm
            )
{
    pOdDrawPrm->imgFrameStartX  = pObj->inStartX;
    pOdDrawPrm->imgFrameStartY  = pObj->inStartY;
    pOdDrawPrm->imgFrameWidth   = pObj->inWidth;
    pOdDrawPrm->imgFrameHeight  = pObj->inHeight;

    pOdDrawPrm->numOutBuffers   = 8;

    pOdDrawPrm->objectRectThickness = 1;
    pOdDrawPrm->objectDrawDistance = TRUE;
    pOdDrawPrm->objectTsrDrawTrafficSigns = TRUE;
    pOdDrawPrm->sofMaxTrackPoints = SFM_TRACK_POINTS;
    pOdDrawPrm->laneThickness = 2;
    pOdDrawPrm->laneDrawLines = FALSE;
    pOdDrawPrm->laneScaleX = 2.0;
    pOdDrawPrm->laneScaleY = 2.0;
    pOdDrawPrm->laneRoiStartY = pLdPrm->roiStartY;
    pOdDrawPrm->laneRoiHeight = pLdPrm->roiHeight;
    pOdDrawPrm->laneRoiWidth  = pLdPrm->roiWidth;

    pOdDrawPrm->drawOption = pObj->drawOption;
    pOdDrawPrm->numDrawAlg = 0;

    if(pOdPrm)
    {
        pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
            = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_OD;
        pOdDrawPrm->numDrawAlg++;
    }
    if(pClrPrm)
    {
        pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
            = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_CLR;
        pOdDrawPrm->numDrawAlg++;
    }
    if(pLdPrm)
    {
        pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
            = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_LD;
        pOdDrawPrm->numDrawAlg++;
    }
    /* draw SOF and SFM */
    #if DRAW_SFM
    pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
        = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SFM;
    pOdDrawPrm->numDrawAlg++;
    #endif
    #if DRAW_SOF
    pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
        = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SOF;
    pOdDrawPrm->numDrawAlg++;
    #endif

}

static Void ChainsCommon_Analytics2_SetLaneDetectPrm(
                    ChainsCommon_Analytics2Obj *pObj,
                    AlgorithmLink_LaneDetectCreateParams *pLdPrm,
                    UInt32 ldImgPmdScaleIdx
                    )
{
    pLdPrm->imgFrameStartX = 0;
    pLdPrm->imgFrameStartY = 0;
    pLdPrm->imgFrameWidth  = LD_ALG_WIDTH;
    pLdPrm->imgFrameHeight = LD_ALG_HEIGHT;

    pLdPrm->roiStartX    = 190U;
    pLdPrm->roiStartY    = 210U;
    pLdPrm->roiWidth     = 222U;
    pLdPrm->roiHeight    = 70U;

    pLdPrm->numOutBuffers  = 8;

    if(pObj->useImgPmd)
    {
        pLdPrm->isImgPmdInputType = TRUE;
        pLdPrm->imgPmdScaleIdx = ldImgPmdScaleIdx;
    }
}

static Void ChainsCommon_Analytics2_SetObjectDetectPrms(
            ChainsCommon_Analytics2Obj *pObj,
            AlgorithmLink_ImagePreProcessCreateParams  *pImgPreProcPrm,
            AlgorithmLink_ImgPyramidCreateParams *pImgPmd,
            AlgorithmLink_FPComputeCreateParams *pFpcPrm,
            AlgorithmLink_ObjectDetectionCreateParams *pOdPrm,
            AlgorithmLink_ObjectClassificationCreateParams *pOcPrm
)
{
    pImgPreProcPrm->imgFrameStartX = pObj->inStartX;
    pImgPreProcPrm->imgFrameStartY = pObj->inStartY;
    pImgPreProcPrm->imgFrameWidth  = pObj->inWidth;
    pImgPreProcPrm->imgFrameHeight = pObj->inHeight;
    pImgPreProcPrm->numOutBuffers  = 8;

#ifdef TDA3XX_BUILD
    pImgPmd->rszModule      = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_ISS;
#else
    pImgPmd->rszModule      = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_VPE;
#endif
    pImgPmd->numOutBuffers  = 8;
    pImgPmd->enableRoi      = TRUE;
    pImgPmd->roiWidth       = pObj->inWidth;
    pImgPmd->roiHeight      = ((pObj->inHeight*IMG_PMD_ROI_PERCENTAGE)/100) & (~1);
    pImgPmd->roiStartX      = 0;
    pImgPmd->roiStartY      = ((pObj->inHeight - pImgPmd->roiHeight)/2) & (~1);
    pImgPmd->numScales      = IMG_PMD_NUM_SCALES;
    pImgPmd->scaleSteps     = IMG_PMD_SCALE_STEPS;

    pFpcPrm->imgFrameStartX = 0;
    pFpcPrm->imgFrameStartY = 0;
    pFpcPrm->imgFrameWidth  = pObj->inWidth;
    pFpcPrm->imgFrameHeight = pObj->inHeight;
    pFpcPrm->numOutBuffers  = 8;

    pOdPrm->numOutBuffers   = 8;
    pOdPrm->enablePD        = TRUE;
    pOdPrm->enableTSR       = TRUE;
    pOdPrm->enableVD        = TRUE;
    pOdPrm->imgFrameWidth   = pObj->inWidth;
    pOdPrm->imgFrameHeight  = pObj->inHeight;

    pOcPrm->numOutBuffers    = 8;
    pOcPrm->imgFrameWidth    = pObj->inWidth;
    pOcPrm->imgFrameHeight   = pObj->inHeight;
    pOcPrm->numScales        = IMG_PMD_NUM_SCALES;

}

static Void ChainsCommon_Analytics2_SetClrPrm(
                    ChainsCommon_Analytics2Obj *pObj,
                    AlgorithmLink_ClrCreateParams *pClrPrm
                    )
{
    pClrPrm->imgFrameStartX = pObj->inStartX;
    pClrPrm->imgFrameStartY = pObj->inStartY;
    pClrPrm->imgFrameWidth  = pObj->inWidth;
    pClrPrm->imgFrameHeight = pObj->inHeight;
    pClrPrm->roiStartX      = 32;
    pClrPrm->roiStartY      = 8;
    pClrPrm->roiWidth       = 1200;
    pClrPrm->roiHeight      = 370;
    pClrPrm->numOutBuffers  = 8;
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
Void ChainsCommon_Analytics2_SetPrms(
            CaptureLink_CreateParams *pCapturePrm,
            AlgorithmLink_SparseOpticalFlowCreateParams *pSofPrm,
            AlgorithmLink_SfmCreateParams *pSfmPrm,
            AlgorithmLink_ImagePreProcessCreateParams  *pImgPreProcPrm,
            AlgorithmLink_ImgPyramidCreateParams *pImgPmdPrm,
            AlgorithmLink_FPComputeCreateParams *pFpcPrm,
            AlgorithmLink_ObjectDetectionCreateParams *pOdPrm,
            AlgorithmLink_ObjectClassificationCreateParams *pOcPrm,
            SyncLink_CreateParams *pSyncFcwPrm,
            AlgorithmLink_FcwCreateParams *pFcwPrm,
            AlgorithmLink_LaneDetectCreateParams *pLdPrm,
            AlgorithmLink_ClrCreateParams *pClrPrm,
            SyncLink_CreateParams *pSyncAlgPrm,
            AlgorithmLink_ObjectDrawCreateParams *pOdDrawPrm,
            SyncLink_CreateParams *pSyncOdPrm,
            DisplayLink_CreateParams *pDisplayVideoPrm,
            GrpxSrcLink_CreateParams *pGrpxSrcPrm,
            DisplayLink_CreateParams *pDisplayGrpxPrm,
            Chains_CaptureSrc captureSrc,
            Chains_DisplayType displayType,
            UInt32 Alg_ImgPyramidLinkID,
            UInt32 Alg_FPComputeLinkID,
            UInt32 Alg_ObjectDrawLinkID,
            UInt32 Alg_ObjectClassificationLinkID,
            UInt32 Alg_LaneDetectLinkID,
            UInt32 isInputModeFile
        )
{
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;

    /* draw all but LD by default */
    pObj->drawOption = (AlgorithmLink_ObjectDrawOption)
        (
          (UInt32)ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD
        | (UInt32)ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR
        | (UInt32)ALGORITHM_LINK_OBJECT_DETECT_DRAW_VD
        | (UInt32)ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR
        | (UInt32)ALGORITHM_LINK_OBJECT_DETECT_DRAW_LD
        | (UInt32)ALGORITHM_LINK_OBJECT_DETECT_DRAW_SOF
        )
        ;

    gChainsCommon_analytics2Obj.ldDrawEnable = FALSE;

    if(gChainsCommon_analytics2Obj.ldDrawEnable==FALSE)
    {
        pObj->drawOption &= ~ALGORITHM_LINK_OBJECT_DETECT_DRAW_LD;
        pObj->drawOption |= ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR;
    }

    pObj->captureSrc  = captureSrc;
    pObj->displayType = displayType;
    pObj->useImgPmd   = FALSE;

    if(pImgPmdPrm)
    {
        pObj->useImgPmd = TRUE;
    }

    pObj->Alg_ImgPyramidLinkID = Alg_ImgPyramidLinkID;
    pObj->Alg_FPComputeLinkID = Alg_FPComputeLinkID;
    pObj->Alg_ObjectDrawLinkID = Alg_ObjectDrawLinkID;
    pObj->Alg_ObjectClassificationLinkID = Alg_ObjectClassificationLinkID;
    pObj->Alg_LaneDetectLinkID = Alg_LaneDetectLinkID;


    pObj->captureOutWidth  = 1280; // 1920;
    pObj->captureOutHeight = 720;  // 1080;

    if(isInputModeFile)
    {
        pObj->inStartX =  320 + 32; /* decoder offset */
        pObj->inStartY =  180 + 24; /* decoder offset */
#if 0
        ChainsCommon_Sfm_Init(TRUE);
#endif
    }
    else
    {
        pObj->inStartX =  0; // 320;
        pObj->inStartY =  0; // 180;
#if 0
        ChainsCommon_Sfm_Init(FALSE);
#endif
    }

    pObj->inWidth  = 1280;
    pObj->inHeight =  720;

    ChainsCommon_GetDisplayWidthHeight(
        displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );



    if(pCapturePrm)
        ChainsCommon_SingleCam_SetCapturePrms(pCapturePrm,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            captureSrc
            );

    if(pGrpxSrcPrm)
    {
        ChainsCommon_SetGrpxSrcPrms(pGrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight
                                );

        pGrpxSrcPrm->fcAnalytics2LayoutEnable = TRUE;
    }

#if 0
    ChainsCommon_SetDisplayPrms(pDisplayVideoPrm,
                                pDisplayGrpxPrm,
                                displayType,
                                pObj->displayWidth,
                                pObj->displayHeight
                                );
#endif
    if(pSofPrm && pSfmPrm && pFcwPrm)
    {
#if 0
        ChainsCommon_Sfm_SetSfmPrm(
            pCapturePrm,
            pSofPrm,
            pSfmPrm,
            pFcwPrm,
            NULL,
            pObj->inStartX,
            pObj->inStartY,
            pObj->inWidth,
            pObj->inHeight,
            SFM_TRACK_POINTS,
            SFM_CAM_PRM_FILE
        );
#endif
    }

    if(pSyncFcwPrm)
    {
        pSyncFcwPrm->syncDelta = 1;
        pSyncFcwPrm->syncThreshold = 300;
    }

    if(pSyncOdPrm)
    {
        pSyncOdPrm->syncDelta = 1;
        pSyncOdPrm->syncThreshold = 300;
    }

    if(pSyncAlgPrm)
    {
        pSyncAlgPrm->syncDelta = 1;
        pSyncAlgPrm->syncThreshold = 300;
    }

    if(pImgPreProcPrm && pImgPmdPrm && pFpcPrm && pOdPrm && pOcPrm)
    {
        ChainsCommon_Analytics2_SetObjectDetectPrms(
                    pObj,
                    pImgPreProcPrm,
                    pImgPmdPrm,
                    pFpcPrm,
                    pOdPrm,
                    pOcPrm
                );
    }

    if(pClrPrm)
    {
        ChainsCommon_Analytics2_SetClrPrm(
            pObj,
            pClrPrm
            );
    }

    if(pLdPrm)
    {
        UInt32 ldImgPmdScaleIdx = 0;

        if(pObj->useImgPmd)
        {
            /* pick the /2 scale as input for LD */
            ldImgPmdScaleIdx = pImgPmdPrm->scaleSteps;
        }

        ChainsCommon_Analytics2_SetLaneDetectPrm(
            pObj,
            pLdPrm,
            ldImgPmdScaleIdx
            );
    }

    ChainsCommon_Analytics2_SetObjectDrawPrms(
        pObj,
        pOdDrawPrm,
        pOdPrm,
        pClrPrm,
        pLdPrm
        );
#if 0
    ChainsCommon_StartDisplayCtrl(
        displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );
#endif
}

static Int32 ChainsCommon_Analytics2_TskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;
    AlgorithmLink_ObjectDrawSetDrawParams drawPrm;
    AlgorithmLink_LaneDetectAlgParams ldPrm;
#if 0
    UInt32 curFrameNum;
#endif
    Bool sendCmd;

    drawPrm.baseClassControl.size = sizeof(drawPrm);
    drawPrm.baseClassControl.controlCmd = ALGORITHM_LINK_OBJECT_DRAW_CMD_SET_DRAW_PRMS;
    drawPrm.drawOption = gChainsCommon_analytics2Obj.drawOption;

    ldPrm.baseClassControl.size = sizeof(ldPrm);
    ldPrm.baseClassControl.controlCmd = ALGORITHM_LINK_LD_CMD_SET_PARAMS;
    ldPrm.enableAdvConfig = FALSE;
    ldPrm.changeEnableLD = TRUE;



    while(!pObj->taskExit)
    {
        Task_sleep(10);

#if 0
        curFrameNum = ChainsCommon_Sfm_CaptureGetCurrentFrameNum();
        sendCmd = FALSE;

        if(curFrameNum > LD_CLIP_START_FRAME && curFrameNum <= LD_CLIP_END_FRAME)
        {
            if(gChainsCommon_analytics2Obj.ldDrawEnable==FALSE)
            {
                #if 1
                drawPrm.drawOption |= ALGORITHM_LINK_OBJECT_DETECT_DRAW_LD;
                drawPrm.drawOption &= ~ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR;
                ldPrm.enableLD        = TRUE;
                gChainsCommon_analytics2Obj.ldDrawEnable = TRUE;
                sendCmd = TRUE;
                #endif
            }
        }
        else
        {
#endif
            if(gChainsCommon_analytics2Obj.ldDrawEnable==TRUE)
            {
                drawPrm.drawOption &= ~ALGORITHM_LINK_OBJECT_DETECT_DRAW_LD;
                drawPrm.drawOption |= ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR;
                ldPrm.enableLD        = FALSE;
                gChainsCommon_analytics2Obj.ldDrawEnable = FALSE;
                sendCmd = TRUE;
            }
#if 0
        }
#endif

        if(sendCmd)
        {
                System_linkControl(
                    pObj->Alg_LaneDetectLinkID,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &ldPrm,
                    sizeof(ldPrm),
                    TRUE
                    );


                System_linkControl(
                    pObj->Alg_ObjectDrawLinkID,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &drawPrm,
                    sizeof(drawPrm),
                    TRUE
                    );
        }

    }
    return (0);
}

Void ChainsCommon_Analytics2_Start(UInt32 isInputModeFile)
{
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;
    Int32 status;

    if(pObj->useImgPmd)
    {
        AlgorithmLink_ImgPyramidImgPyramidInfoControlParams imgPyramidCtrlPrms;

        imgPyramidCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_LINK_IMAGE_PYRAMID_CMD_GET_PYRAMID_INFO;
        imgPyramidCtrlPrms.baseClassControl.size = sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams);

        /* get results */
        status = System_linkControl(
            pObj->Alg_ImgPyramidLinkID,
            ALGORITHM_LINK_CMD_CONFIG,
            &imgPyramidCtrlPrms,
            sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams),
            TRUE);

        imgPyramidCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_LINK_FPCOMPUTE_CMD_CREATE_ALG;
        imgPyramidCtrlPrms.baseClassControl.size = sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams);

        /* set image pyramid info */
        status = System_linkControl(
            pObj->Alg_FPComputeLinkID,
            ALGORITHM_LINK_CMD_CONFIG,
            &imgPyramidCtrlPrms,
            sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams),
            TRUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        imgPyramidCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_LINK_OBJECTCLASSIFICATION_CMD_CREATE_ALG;
        imgPyramidCtrlPrms.baseClassControl.size = sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams);

        /* set image pyramid info */
        status = System_linkControl(
            pObj->Alg_ObjectClassificationLinkID,
            ALGORITHM_LINK_CMD_CONFIG,
            &imgPyramidCtrlPrms,
            sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams),
            TRUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

#if 0
    ChainsCommon_StartDisplayDevice(pObj->displayType);

    if(!isInputModeFile)
    {
        ChainsCommon_StartCaptureDevice(
            pObj->captureSrc,
            pObj->captureOutWidth,
            pObj->captureOutHeight);
    }

#endif
    /*
     * Create a task to update the peraMat table into QSPI flash after 5 min
     */
    pObj->taskExit = FALSE;
    snprintf(pObj->tskName, 32, "Analytics2_TskMain");
    status = OSA_tskCreate(&pObj->taskHndl,
                           ChainsCommon_Analytics2_TskMain,
                           OSA_THR_PRI_DEFAULT,
                           OSA_TSK_STACK_SIZE_DEFAULT,
                           0,
                           pObj,
                           pObj->tskName);

    OSA_assert((OSA_TskHndl*)(&pObj->taskHndl) != NULL);
}

Void ChainsCommon_Analytics2_Stop(UInt32 isInputModeFile)
{
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;

#if 0
    ChainsCommon_StopDisplayCtrl();
    if(!isInputModeFile)
    {

        ChainsCommon_StopCaptureDevice(pObj->captureSrc);
    }
    ChainsCommon_StopDisplayDevice(pObj->displayType);
#endif
    pObj->taskExit = TRUE;

    OSA_tskDelete(&pObj->taskHndl);
}



