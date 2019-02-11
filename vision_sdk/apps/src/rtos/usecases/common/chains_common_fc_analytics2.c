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
#include <src/include/chains_common.h>
#include <src/include/chains_common_sfm.h>
#include <src/rtos/utils_common/include/utils_tsk.h>

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
    BspOsal_TaskHandle taskHndl;

    Bool ldDrawEnable;

    AlgorithmLink_ObjectDrawOption drawOption;

    UInt32 currentLHMState;

} ChainsCommon_Analytics2Obj;

/**
 *******************************************************************************
 * \brief stack for PersMat table write task
 *******************************************************************************
 */
#pragma DATA_ALIGN(gChainsCommon_Analytics2_tskStack, 32)
#pragma DATA_SECTION(gChainsCommon_Analytics2_tskStack, ".bss:taskStackSection")
UInt8 gChainsCommon_Analytics2_tskStack[4*1024];

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


    pObj->captureOutWidth  = 1920;
    pObj->captureOutHeight = 1080;

    if(isInputModeFile)
    {
        pObj->inStartX =  320 + 32; /* decoder offset */
        pObj->inStartY =  180 + 24; /* decoder offset */
        ChainsCommon_Sfm_Init(TRUE);
    }
    else
    {
        pObj->inStartX =  320;
        pObj->inStartY =  180;
        ChainsCommon_Sfm_Init(FALSE);
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

    ChainsCommon_SetDisplayPrms(pDisplayVideoPrm,
                                pDisplayGrpxPrm,
                                displayType,
                                pObj->displayWidth,
                                pObj->displayHeight
                                );

    if(pSofPrm && pSfmPrm && pFcwPrm)
    {
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

    ChainsCommon_StartDisplayCtrl(
        displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

}

static Void ChainsCommon_Analytics2_TskMain(UArg arg1, UArg arg2)
{
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;
    AlgorithmLink_ObjectDrawSetDrawParams drawPrm;
    AlgorithmLink_LaneDetectAlgParams ldPrm;
    UInt32 curFrameNum;
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
        BspOsal_sleep(10);

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
            if(gChainsCommon_analytics2Obj.ldDrawEnable==TRUE)
            {
                drawPrm.drawOption &= ~ALGORITHM_LINK_OBJECT_DETECT_DRAW_LD;
                drawPrm.drawOption |= ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR;
                ldPrm.enableLD        = FALSE;
                gChainsCommon_analytics2Obj.ldDrawEnable = FALSE;
                sendCmd = TRUE;
            }
        }

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

    ChainsCommon_StartDisplayDevice(pObj->displayType);

    if(!isInputModeFile)
    {
        ChainsCommon_StartCaptureDevice(
            pObj->captureSrc,
            pObj->captureOutWidth,
            pObj->captureOutHeight);
    }

    /*
     * Create a task to update the peraMat table into QSPI flash after 5 min
     */
    pObj->taskExit = FALSE;

    pObj->taskHndl = BspOsal_taskCreate(
                            (BspOsal_TaskFuncPtr)ChainsCommon_Analytics2_TskMain,
                            "ChainsCommon_Analytics2_TskMain",
                            4,
                            gChainsCommon_Analytics2_tskStack,
                            sizeof(gChainsCommon_Analytics2_tskStack),
                            NULL,
                            UTILS_TSK_AFFINITY_CORE0
                           );
    UTILS_assert(pObj->taskHndl != NULL);

    status = Utils_prfLoadRegister(pObj->taskHndl,
                                   "CHAINS_ANALYTICS2_TSK");
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
}

Void ChainsCommon_Analytics2_Stop(UInt32 isInputModeFile)
{
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;

    ChainsCommon_StopDisplayCtrl();
    if(!isInputModeFile)
    {

        ChainsCommon_StopCaptureDevice(pObj->captureSrc);
    }
    ChainsCommon_StopDisplayDevice(pObj->displayType);

    pObj->taskExit = TRUE;

    Utils_prfLoadUnRegister(pObj->taskHndl);

    BspOsal_taskDelete(&pObj->taskHndl);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChainsCommon_runTimeMenu_singleCamAnalytics[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n t: Show Thermal Configuration Menu "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection for the single camera analytics usecase
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char ChainsCommon_menuRunTime_SingleCamAnalytics()
{
    Vps_printf(gChainsCommon_runTimeMenu_singleCamAnalytics);

    return Chains_readChar();
}

/**
 *******************************************************************************
 * \brief Run Time Menu Thermal Menu string.
 *******************************************************************************
 */
char gChainsCommon_thermalRunTimeDesc[] = {
    "\r\n "
    "\r\n =============================="
    "\r\n Thermal Management Description"
    "\r\n =============================="
    "\r\n "
    "\r\n The Thermal Management of the device involves reducing the power"
    "\r\n consumption when the temperature of the device becomes hotter than"
    "\r\n the desired THOT temperature. When the temperature becomes lower than"
    "\r\n TCOLD temperature the device power consumption can be restored."
    "\r\n "
    "\r\n The control of power consumption is done by reducing the FPS of"
    "\r\n of the usecase by dropping frames in the capture thread."
    "\r\n "
    "\r\n After every thermal event the temperature thresholds would be changed"
    "\r\n to make sure THOT and TCOLD are as below:"
    "\r\n "
    "\r\n      THOT Temperature    ------------------------"
    "\r\n                                 ^"
    "\r\n                                 |"
    "\r\n                             Step Size"
    "\r\n                                 |"
    "\r\n                                 V"
    "\r\n      Current Temperature ------------------------"
    "\r\n                                 ^"
    "\r\n                                 |"
    "\r\n                             Step Size"
    "\r\n                                 |"
    "\r\n                                 V"
    "\r\n      TCOLD Temperature    ------------------------"
    "\r\n "
};
char gChainsCommon_thermalRunTimeMenu[] = {
    "\r\n "
    "\r\n ============================"
    "\r\n Thermal Menu Options:"
    "\r\n ============================"
    "\r\n "
    "\r\n 1: Change THOT Temperature"
    "\r\n 2: Change TCOLD Temperature"
    "\r\n 3: Show current THOT Temperature"
    "\r\n 4: Show current TCOLD Temperature"
    "\r\n 5: Change Threshold Step Size"
    "\r\n 6: Show Limp Home Status"
    "\r\n 7: Switch to Limp Home Mode"
    "\r\n 8: Return to Normal Usecase Mode"
    "\r\n x: Exit Thermal Menu"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChainsCommon_thermalTemperatureMenu[] = {
    "\r\n Available options for Temperature: "
    "\r\n "
    "\r\n 1: 100 deg C"
    "\r\n 2: 80 deg C"
    "\r\n 3: 60 deg C"
    "\r\n 4: 50 deg C"
    "\r\n 5: 45 deg C"
    "\r\n 6: 40 deg C"
    "\r\n 7: 35 deg C"
    "\r\n 8: 30 deg C"
    "\r\n 9: 20 deg C"
    "\r\n a: 10 deg C"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChainsCommon_thermalStepSizeMenu[] = {
    "\r\n Available options for Step Size: "
    "\r\n "
    "\r\n 1: 3  deg C"
    "\r\n 2: 5  deg C"
    "\r\n 3: 10 deg C"
    "\r\n 4: 15 deg C"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Run time Update of the Thermal Thresholds.
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *
 *******************************************************************************
*/
Void ChainsCommon_thermalConfig()
{
    char ch = '3', ch_temp;
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
#if defined (LHM_LOOP_TEST)
    char my_state = '1';
#endif
    Vps_printf(gChainsCommon_thermalRunTimeDesc);
    do
    {
        Vps_printf(gChainsCommon_thermalRunTimeMenu);
#if defined (LHM_LOOP_TEST)
        BspOsal_sleep(2000U);

        if (ch == '3')
        {
            ch = '1';
        }
        else if (ch == '1')
        {
            ch = '6';
            my_state = '2';
        }
        else if (ch == '6')
        {
            if (my_state == '1')
            {
                ch = '1';
            }
            else
            {
                ch = '2';
            }
        }
        else if (ch == '2')
        {
            ch = '6';
            my_state = '1';
        }
#else
        ch = Chains_readChar();
#endif
        switch (ch)
        {
            case '1':
                    Vps_printf(gChainsCommon_thermalTemperatureMenu);
#if defined (LHM_LOOP_TEST)
                    ch_temp = '9';
#else
                    ch_temp = Chains_readChar();
#endif
                    ChainsCommon_modifyTemperatureThreshold(ch_temp, CHAINS_HOT_TEMPERATURE);
                    break;
            case '2':
                    Vps_printf(gChainsCommon_thermalTemperatureMenu);
#if defined (LHM_LOOP_TEST)
                    ch_temp = '2';
#else
                    ch_temp = Chains_readChar();
#endif
                    ChainsCommon_modifyTemperatureThreshold(ch_temp, CHAINS_COLD_TEMPERATURE);
                    break;
            case '3':
                    ChainsCommon_readTemperatureThreshold(CHAINS_HOT_TEMPERATURE);
                    break;
            case '4':
                    ChainsCommon_readTemperatureThreshold(CHAINS_COLD_TEMPERATURE);
                    break;
            case '5':
                    Vps_printf(gChainsCommon_thermalStepSizeMenu);
                    ch_temp = Chains_readChar();
                    ChainsCommon_modifyTempThresholdStepSize(ch_temp);
                    break;
            case '6':
                    if (Utils_tempGetLimpHomeState())
                    {
                        Vps_printf("\n -------------------------");
                        Vps_printf("\n Limp Home Mode = ACTIVE!!\n");
                        Vps_printf("\n -------------------------");
                    }
                    else
                    {
                        Vps_printf("\n ----------------------------");
                        Vps_printf("\n Limp Home Mode = IN-ACTIVE!!\n");
                        Vps_printf("\n ----------------------------");
                    }
                    break;
            case '7' :
                    if (UTILS_TEMP_LIMP_HOME_INACTIVE == Utils_tempGetLimpHomeState())
                    {
                        Chains_vipSingleCameraAnalytics2_EventHandler(
                                UTILS_TEMP_CMD_EVENT_HOT,
                                (Void*)&voltId );
                    }
                    else
                    {
                        Vps_printf("\n Limp Home Mode Already ACTIVE!!\n");
                    }
                    break;
            case '8' :
                    if (UTILS_TEMP_LIMP_HOME_ACTIVE == Utils_tempGetLimpHomeState())
                    {
                        Chains_vipSingleCameraAnalytics2_EventHandler(
                                UTILS_TEMP_CMD_EVENT_COLD,
                                (Void*)&voltId );
                    }
                    else
                    {
                        Vps_printf("\n Limp Home Mode Already IN-ACTIVE!!\n");
                    }
                    break;
            case 'X':
                    ch = 'x';
            case 'x':
                    break;
            default:
                    Vps_printf("\nUnsupported option '%c'. Please try again. \n", ch);
                    break;
        }
#if !defined (LHM_LOOP_TEST)
        /* This sleep has been added for any pending thermal event to go through before
         * the user places the next input and the display is updated with the message
         * correctly.
         */
         BspOsal_sleep(1000U);
#endif
        /* Update the display print with LHM Active or In-Active */
        if (Utils_tempGetLimpHomeState() !=
                    gChainsCommon_analytics2Obj.currentLHMState)
        {
            gChainsCommon_analytics2Obj.currentLHMState =
                ChainsCommon_displayLHMStatus();
        }
    } while (ch != 'x');
}

/**
 *******************************************************************************
 *
 * \brief   Run time Update of the Thermal Thresholds.
 *
 *          This function updates the THOD or TCOLD thresholds in the software
 *          structures and the hardware registers.
 *
 * \param   ch_temp[IN]     User selected THOT/TCOLD threshold
 * \param   eventType[IN]   THOT or TCOLD selection
 *
 *******************************************************************************
*/
Void ChainsCommon_modifyTemperatureThreshold(char ch_temp, UInt32 eventType)
{
    Int32 threshold = 0;
    UInt32 retVal = 0U;
    switch (ch_temp)
    {
        case '1': threshold = 100000;
                  break;
        case '2': threshold = 80000;
                  break;
        case '3': threshold = 60000;
                  break;
        case '4': threshold = 50000;
                  break;
        case '5': threshold = 45000;
                  break;
        case '6': threshold = 40000;
                  break;
        case '7': threshold = 35000;
                  break;
        case '8': threshold = 30000;
                  break;
        case '9': threshold = 20000;
                  break;
        case 'a': threshold = 10000;
                  break;
        default :
              Vps_printf("\nUnsupported option '%c'. \n", ch_temp);
              retVal = 1U;
    }
    if ( 0U == retVal )
    {
        if (eventType == CHAINS_HOT_TEMPERATURE)
        {
            Utils_tempChangeHotThreshold(threshold);
        }
        else if (eventType == CHAINS_COLD_TEMPERATURE)
        {
            Utils_tempChangeColdThreshold(threshold);
        }
        else
        {
            ; /* Should not reach here */
        }
    }
}
/**
 *******************************************************************************
 *
 * \brief   Run time read of the Thermal Thresholds.
 *
 *          This function reads the THOD or TCOLD thresholds in the software
 *          structures.
 *
 * \param   eventType[IN]   THOT or TCOLD selection
 *
 *******************************************************************************
*/
Void ChainsCommon_readTemperatureThreshold(UInt32 eventType)
{

    if ( eventType == CHAINS_HOT_TEMPERATURE)
    {
        Utils_tempReadAllHotThreshold();
    }
    else if (eventType == CHAINS_COLD_TEMPERATURE)
    {
        Utils_tempReadAllColdThreshold();
    }
    else
    {
        ; /* Should not reach here */
    }
}
/**
 *******************************************************************************
 *
 * \brief   Run time Update of the Thermal Threshold Step Size.
 *
 *          This function updates the Step Size in the software
 *          structures.
 *
 * \param   ch_temp[IN]     User selected THOT/TCOLD threshold
 *
 *******************************************************************************
*/
Void ChainsCommon_modifyTempThresholdStepSize(char ch_temp)
{
    UInt32 stepSize = 0U;
    UInt32 retVal = 0U;
    switch (ch_temp)
    {
        case '1':  stepSize = 3000U; break;
        case '2':  stepSize = 5000U; break;
        case '3':  stepSize = 10000U; break;
        case '4':  stepSize = 15000U; break;
        default :
              Vps_printf("\nUnsupported option '%c'. \n", ch_temp);
              retVal = 1U;
    }
    if (0U == retVal)
    {
        Utils_tempChangeStepSize(stepSize);
    }
}

static void ChainsCommon_updateLDParam(UInt32 eventType)
{
    AlgorithmLink_LaneDetectCreateParams createPrm;
    AlgorithmLink_LaneDetectAlgParams ldPrm;
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;

    ldPrm.baseClassControl.size = sizeof(ldPrm);
    ldPrm.baseClassControl.controlCmd = ALGORITHM_LINK_LD_CMD_SET_PARAMS;
    AlgorithmLink_LaneDetect_Init(&createPrm);
    ldPrm.cannyHighThresh        = createPrm.cannyHighThresh;
    ldPrm.cannyLowThresh         = createPrm.cannyLowThresh;
    ldPrm.houghNmsThresh         = createPrm.houghNmsThresh;
    ldPrm.startThetaLeft         = createPrm.startThetaLeft;
    ldPrm.endThetaLeft           = createPrm.endThetaLeft;
    ldPrm.startThetaRight        = createPrm.startThetaRight;
    ldPrm.endThetaRight          = createPrm.endThetaRight;
    ldPrm.thetaStepSize          = createPrm.thetaStepSize;
    ldPrm.numHoughMaximasDet     = createPrm.numHoughMaximasDet;
    ldPrm.numHoughMaximasTrack   = createPrm.numHoughMaximasTrack;
    ldPrm.trackingMethod         = createPrm.trackingMethod;
    ldPrm.warningMethod          = createPrm.warningMethod;
    ldPrm.departThetaLeftMin     = createPrm.departThetaLeftMin;
    ldPrm.departThetaLeftMax     = createPrm.departThetaLeftMax;
    ldPrm.departRhoLeftMin       = createPrm.departRhoLeftMin;
    ldPrm.departRhoLeftMax       = createPrm.departRhoLeftMax;
    ldPrm.departThetaRightMin    = createPrm.departThetaRightMin;
    ldPrm.departThetaRightMax    = createPrm.departThetaRightMax;
    ldPrm.departRhoRightMin      = createPrm.departRhoRightMin;
    ldPrm.departRhoRightMax      = createPrm.departRhoRightMax;

    if (UTILS_TEMP_CMD_EVENT_HOT == eventType)
    {
        /* Update to paramters for better detection at 10 FPS
         * User needs to update LDW parameters according to what the LHM FPS is chosen.
         */
        ldPrm.enableAdvConfig = TRUE;
        ldPrm.changeEnableLD  = FALSE;

        ldPrm.departThetaLeftMin     = 129U;
        ldPrm.departRhoRightMin      = 152U;
        ldPrm.departRhoRightMax      = 154U;
        ldPrm.changeEnableLD         = FALSE;

        System_linkControl(
                    pObj->Alg_LaneDetectLinkID,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &ldPrm,
                    sizeof(ldPrm),
                    TRUE
                    );
    }
    else if (UTILS_TEMP_CMD_EVENT_COLD == eventType)
    {
        /* Update to default parameters. */
        ldPrm.enableAdvConfig = TRUE;
        ldPrm.changeEnableLD  = FALSE;

        System_linkControl(
                    pObj->Alg_LaneDetectLinkID,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &ldPrm,
                    sizeof(ldPrm),
                    TRUE
                    );
    }
    else
    {
        ; /* Nothing to do */
    }

}

/**
 *******************************************************************************
 *
 * \brief   Print the LHM status on the display
 *
 * \return  currentPrint [OUT] The current status of the print
 *
 *******************************************************************************
*/
UInt32 ChainsCommon_displayLHMStatus()
{
    UInt32 currentPrint = Utils_tempGetLimpHomeState();
    ChainsCommon_Analytics2Obj *pObj = &gChainsCommon_analytics2Obj;
    GrpxSrcLink_StringRunTimePrintParams printPrms;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;

    if (currentPrint == 1U)
    {
        fontPrm.fontIdx = LIMP_HOME_DISPLAY_FONTID;
        Draw2D_getFontProperty(&fontPrm, &fontProp);
        snprintf(printPrms.stringInfo.string,
                     sizeof(printPrms.stringInfo.string) - 1,
                     "LIMP HOME MODE ACTIVE");
        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
        printPrms.duration_ms = LIMP_HOME_DISPLAY_DURATION_MS;
        printPrms.stringInfo.fontType = LIMP_HOME_DISPLAY_FONTID;
        printPrms.stringInfo.startX  = pObj->displayWidth - fontProp.width*23 - fontProp.height ;
        printPrms.stringInfo.startY  = pObj->displayHeight - fontProp.height*9;

        status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                           GRPX_SRC_LINK_CMD_PRINT_STRING,
                           &printPrms,
                           sizeof(printPrms),
                           TRUE);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" CHAINS: TEMPERATURE: Send Command for Limp Home failed \n");
        }
    }
    else
    {
        fontPrm.fontIdx = LIMP_HOME_DISPLAY_FONTID;
        Draw2D_getFontProperty(&fontPrm, &fontProp);

        snprintf(printPrms.stringInfo.string,
                     sizeof(printPrms.stringInfo.string) - 1,
                     "LIMP HOME MODE INACTIVE");
        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
        printPrms.duration_ms = LIMP_HOME_DISPLAY_DURATION_MS;
        printPrms.stringInfo.fontType = LIMP_HOME_DISPLAY_FONTID;
        printPrms.stringInfo.startX  = pObj->displayWidth - fontProp.width*23 - fontProp.height ;
        printPrms.stringInfo.startY  = pObj->displayHeight - fontProp.height*9;

        status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                           GRPX_SRC_LINK_CMD_PRINT_STRING,
                           &printPrms,
                           sizeof(printPrms),
                           TRUE);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" CHAINS: TEMPERATURE: Send Command for Limp Home failed \n");
        }
    }
    return currentPrint;

}
/**
 *******************************************************************************
 *
 * \brief   Thermal Event Handler to handle Hot Events.
 *
 *          This function updates the frame skip parameter and sends a message
 *          to the capture link to update the fps. The hot and cold threshold
 *          is updated and the temperature interrupt is enabled.
 *          Handling VD_CORE is sufficient as other VDs are usually +/-5
 *          degrees different wrt VD_CORE temperature.
 *
 * \param   captureLinkId [IN]  Id to identify capture link.
 * \param   pPrm [IN]           Paramter to identify which voltage domain
 *                              generated the hot event.
 *
 *******************************************************************************
*/
Void ChainsCommon_tempHotEventHandler(UInt32 captureLinkId, Void* pPrm)
{
    pmhalPrcmVdId_t voltId = *(pmhalPrcmVdId_t *)pPrm;
    UInt32 frameSkip;
    Int32 threshold;

    if (voltId == PMHAL_PRCM_VD_CORE)
    {
        Vps_printf(" CHAINS: TEMPERATURE: VD_CORE Hit Thermal Hot Event !\n");

        /* Update the LD parameters for LHM FPS */
        ChainsCommon_updateLDParam(UTILS_TEMP_CMD_EVENT_HOT);

        /* Drop the FPS to 10 fps */
        frameSkip = 0x3EFBEFBE;

        System_linkControl(captureLinkId, CAPTURE_LINK_CMD_SET_FRAME_SKIP_MASK,
                    &frameSkip, sizeof(frameSkip), TRUE);

        /* Update the SFM Frame Skip Parameters */
        Utils_resetSkipBufContext(&gChains_sfmObj.skipFrames,
            LHM_INPUT_FPS,
            LHM_OUTPUT_FPS
        );


        /* Change the threshold for all */
        threshold = Utils_tempGetCurrTemperature(PMHAL_PRCM_VD_CORE);
        if (threshold != UTILS_TEMP_INVALID)
        {
            /* Change Hot Threshold first before Cold for a Hot event
             * to make sure the Hot event is not generated when the
             * interrupt is enabled.
             */
            Utils_tempChangeHotThreshold(threshold + Utils_tempGetStepSize(PMHAL_PRCM_VD_CORE));
            Utils_tempChangeColdThreshold(threshold - Utils_tempGetStepSize(PMHAL_PRCM_VD_CORE));
        }
        else
        {
            Vps_printf(" CHAINS: TEMPERATURE: Get Temperature Failed !!\n");
        }
        Vps_printf(" CHAINS: TEMPERATURE:            HOT Threshold = [%d.%d]\n",
             Utils_tempGetHotThreshold(voltId)/1000,
             abs(Utils_tempGetHotThreshold(voltId))%1000);
        Vps_printf(" CHAINS: TEMPERATURE:            COLD Threshold = [%d.%d]\n",
             Utils_tempGetColdThreshold(voltId)/1000,
             abs(Utils_tempGetColdThreshold(voltId))%1000);
        Utils_tempUpdateAllVoltLimpHomeState(UTILS_TEMP_LIMP_HOME_ACTIVE);


    }
}

/**
 *******************************************************************************
 *
 * \brief   Thermal Event Handler to handle Cold Events.
 *
 *          This function updates the frame skip parameter and sends a message
 *          to the capture link to update the fps. The hot and cold threshold
 *          is updated and the temperature interrupt is enabled.
 *          Handling VD_CORE is sufficient as other VDs are usually +/-5
 *          degrees different wrt VD_CORE temperature.
 *
 * \param   captureLinkId [IN]  Id to identify capture link.
 * \param   pPrm [IN]           Paramter to identify which voltage domain
 *                              generated the hot event.
 *
 *******************************************************************************
*/
Void ChainsCommon_tempColdEventHandler(UInt32 captureLinkId, Void* pPrm)
{
    pmhalPrcmVdId_t voltId = *(pmhalPrcmVdId_t *)pPrm;
    UInt32 frameSkip;
    Int32 threshold;

    if (voltId == PMHAL_PRCM_VD_CORE)
    {
        Vps_printf(" CHAINS: TEMPERATURE: VD_CORE Hit Thermal Cold Event !\n");

        /* Update LD parameters to default */
        ChainsCommon_updateLDParam(UTILS_TEMP_CMD_EVENT_COLD);

        /* Restore the FPS to original fps */
        frameSkip = 0x0;

        System_linkControl(captureLinkId, CAPTURE_LINK_CMD_SET_FRAME_SKIP_MASK,
                    &frameSkip, sizeof(frameSkip), TRUE);

        /* Update the SFM Frame Skip Parameters */
        Utils_resetSkipBufContext(&gChains_sfmObj.skipFrames,
            INPUT_FPS,
            OUTPUT_FPS
        );

        /* Change the threshold for all */
        threshold = Utils_tempGetCurrTemperature(PMHAL_PRCM_VD_CORE);
        if (threshold != UTILS_TEMP_INVALID)
        {
            /* Change Cold Threshold first before Hot for a cold event
             * to make sure the cold event is not generated when the
             * interrupt is enabled.
             */
            Utils_tempChangeColdThreshold(threshold - Utils_tempGetStepSize(PMHAL_PRCM_VD_CORE));
            Utils_tempChangeHotThreshold(threshold + Utils_tempGetStepSize(PMHAL_PRCM_VD_CORE));
        }
        else
        {
            Vps_printf(" CHAINS: TEMPERATURE: Get Temperature Failed !!\n");
        }
        Vps_printf(" CHAINS: TEMPERATURE:            HOT Threshold = [%d.%d]\n",
             Utils_tempGetHotThreshold(voltId)/1000,
             abs(Utils_tempGetHotThreshold(voltId))%1000);
        Vps_printf(" CHAINS: TEMPERATURE:            COLD Threshold = [%d.%d]\n",
             Utils_tempGetColdThreshold(voltId)/1000,
             abs(Utils_tempGetColdThreshold(voltId))%1000);
        Utils_tempUpdateAllVoltLimpHomeState(UTILS_TEMP_LIMP_HOME_INACTIVE);

    }
}





