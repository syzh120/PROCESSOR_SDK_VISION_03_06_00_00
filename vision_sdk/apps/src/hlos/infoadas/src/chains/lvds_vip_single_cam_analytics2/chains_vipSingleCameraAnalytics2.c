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
#include "chains_vipSingleCameraAnalytics2_priv.h"
#include <src/hlos/common/chains_common.h>
#include <vivi_sca.h>
#include "../../ti-plugins/include/sca_chain.h"

extern Void ChainsCommon_Analytics2_Start(UInt32 isInputModeFile);
extern Void ChainsCommon_Analytics2_Stop(UInt32 isInputModeFile);

extern Void ChainsCommon_Analytics2_SetPrms(
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
        );

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

    chains_vipSingleCameraAnalytics2Obj ucObj;

    Chains_CaptureSrc captureSrc;
    Chains_DisplayType displayType;
} Chains_VipSingleCameraAnalytics2AppObj;

Chains_VipSingleCameraAnalytics2AppObj gChains_vipSingleCameraAnalytics2AppObj;

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
Void chains_vipSingleCameraAnalytics2_SetAppPrms(chains_vipSingleCameraAnalytics2Obj *pUcObj, Void *appObj)
{
    EpLink_CreateParams  *pEndp;
    Chains_VipSingleCameraAnalytics2AppObj *pObj
        = (Chains_VipSingleCameraAnalytics2AppObj*)appObj;

    ChainsCommon_Analytics2_SetPrms(
        &pUcObj->CapturePrm,
        NULL, /* &pUcObj->Alg_SparseOpticalFlowPrm, */
        NULL, /* &pUcObj->Alg_SfmPrm, */
        &pUcObj->Alg_ImagePreProcessPrm,
        &pUcObj->Alg_ImgPyramidPrm,
        &pUcObj->Alg_FPComputePrm,
        &pUcObj->Alg_ObjectDetectionPrm,
        &pUcObj->Alg_ObjectClassificationPrm,
        &pUcObj->Sync_FcwPrm,
        &pUcObj->Alg_FcwPrm,
        &pUcObj->Alg_LaneDetectPrm,
        &pUcObj->Alg_ClrPrm,
        &pUcObj->Sync_algPrm,
        &pUcObj->Alg_ObjectDrawPrm,
        &pUcObj->Sync_objectDetectPrm,
        NULL, /* &pUcObj->Display_VideoPrm, */
        NULL, /* &pUcObj->GrpxSrcPrm, */
        NULL, /* &pUcObj->Display_GrpxPrm, */
        CHAINS_CAPTURE_SRC_OV10635, /* pObj->captureSrc, */
        pObj->displayType,
        pUcObj->Alg_ImgPyramidLinkID,
        pUcObj->Alg_FPComputeLinkID,
        pUcObj->Alg_ObjectDrawLinkID,
        pUcObj->Alg_ObjectClassificationLinkID,
        pUcObj->Alg_LaneDetectLinkID,
        FALSE
        );

    /* We have two epLink in the chain; we will configure it now */
    /* sink1 */
    pEndp = &pUcObj->EpSink_1Prm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = SCA_LVDS_SINGLE_CAM_ANALYTICS2;
    strcpy(pEndp->plugName, SCA_PLUGIN_NAME);
}

Void chains_vipSingleCameraAnalytics2_InitApp(Void)
{
}

Int32 chains_vipSingleCameraAnalytics2_CreateApp(struct vivi_sink *sink, struct vivi_source *source)
{
    Int32 status;
    chains_vipSingleCameraAnalytics2Obj *pUcObj;

    chains_vipSingleCameraAnalytics2_InitApp();


    status = chains_vipSingleCameraAnalytics2_Create(
            &gChains_vipSingleCameraAnalytics2AppObj.ucObj,
            &gChains_vipSingleCameraAnalytics2AppObj);

    /* Let's set the epLink ids now */
    pUcObj = &gChains_vipSingleCameraAnalytics2AppObj.ucObj;
    sink->eplink_id[0] = pUcObj->EpSink_1LinkID;

    return status;
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
 * \param   pObj  [IN] Chains_VipSingleCameraAnalytics2AppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 chains_vipSingleCameraAnalytics2_StartApp(Void)
{

    Int32 status;
    Chains_VipSingleCameraAnalytics2AppObj *pObj
        = (Chains_VipSingleCameraAnalytics2AppObj *)&gChains_vipSingleCameraAnalytics2AppObj;

    /* Initialize the sytem to take up temprature events */
    ChainsCommon_Analytics2_Start(FALSE);

    status = chains_vipSingleCameraAnalytics2_Start(&pObj->ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);
    return (status);
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
 * \param   pObj   [IN]   Chains_VipSingleCameraAnalytics2AppObj
 *
 *******************************************************************************
*/
Int32 chains_vipSingleCameraAnalytics2_StopApp(Void)
{
    Chains_VipSingleCameraAnalytics2AppObj *pObj
        = (Chains_VipSingleCameraAnalytics2AppObj *)&gChains_vipSingleCameraAnalytics2AppObj;
    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    return (chains_vipSingleCameraAnalytics2_Stop(&pObj->ucObj));
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
 * \param   pObj   [IN]   Chains_VipSingleCameraAnalytics2AppObj
 *
 *******************************************************************************
*/
Int32 chains_vipSingleCameraAnalytics2_DeleteApp(Void)
{
    Int32 status;

    Chains_VipSingleCameraAnalytics2AppObj *pObj
        = (Chains_VipSingleCameraAnalytics2AppObj *)&gChains_vipSingleCameraAnalytics2AppObj;

    status = chains_vipSingleCameraAnalytics2_Delete(&pObj->ucObj);

    ChainsCommon_Analytics2_Stop(FALSE);

    return(status);
}

